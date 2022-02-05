#include<iostream>
#include<vector>
#include<string>
using namespace std;
#define SIZEX 19
#define SIZEY 22
#define SIZEZ 23


// GETTING CHARACTER FROM DECIMAL VAL (Bin -> Dec)
char getCharacter(string binary){
    char reqChar;
    // Bin -> Dec
    int dec_val = 0;
    // initial val of base = 1 (2^0)
    int base = 1; 
    int temp = stoi(binary);
    while(temp){
        int last_digit = temp%10;
        temp /= 10;
        dec_val += last_digit * base;
        base *= 2;
    }
    reqChar = char(dec_val);
    return reqChar;
}



// converting Binary (7 bits) to corresponding ASCII character
string BinToChar(string stream){
    string msg = "";
    int i=0;
    while(i<stream.size()){
        // combining 7 bits at a time to retrieve the corresponding character from the binary form (0-125)
        string binOfChar = "";
        for(int j=i; j<i+7; j++){
            binOfChar += stream[j];
        }
        i = i+7;
        msg += getCharacter(binOfChar);
    }
    return msg;
}


// Generate a random 64-bit key
string generatekey(){
    string key = "";
    for(int i=0; i<64; i++)
        key += to_string(rand()%2);
    return key;
}




// Print the registers
void printRegister(vector<int> reg){
    for(int i=0; i<reg.size(); i++)
        cout<<reg[i]<<" ";
    cout<<"\n";
}




// Allocating registers with Key
void allocateRegisters(vector<int> &x, vector<int> &y, vector<int> &z, string key){
    // x
    for(int i=0; i<SIZEX; i++)
        x[i] = key[i]-'0';
    // y
    for(int i=19; i<SIZEY+19; i++)
        y[i-19] = key[i]-'0';
    // z
    for(int i=41; i<SIZEZ+41; i++)
        z[i-41] = key[i]-'0';
    
}




// Majority vote function
int majorityVote(int x, int y, int z){
    int m;
    if(x == 0){
        if(y == 0 || z == 0)
            m = 0;
        else
            m = 1;
    }
    else{
        if(y == 1 || z == 1)
            m = 1;
        else
            m = 0;
    }
    return m;
}




// Shifting registers by 1 position (towards Right)
void shiftRegister(vector<int> &reg, const int t){
    for(int j=reg.size()-1; j>=0; j--){
        if(j == 0)
            reg[j] = t;
        else
            reg[j] = reg[j-1];
    }
}




// Functioning of registers X, Y, Z
void registerFunctioning(vector<int> &x, vector<int> &y, vector<int> &z, const int m){
    if(x[8] == m){
        int t = x[13] ^ x[16] ^ x[17] ^ x[18];
        shiftRegister(x, t);        
    }
    if(y[10] == m){
        int t = y[20] ^ y[21];
        shiftRegister(y, t);        
    }
    if(z[10] == m){
        int t = z[20] ^ z[21] ^ z[22];
        shiftRegister(z, t);        
    }
}




// Converting ASCII (decimal number) to 8-bit Binary string
string asciiToBin(int num){
    string bin = "";
    for(int i = 1<<6; i>0; i=i/2){
        if((num & i) != 0)
            bin += to_string(1);
        else
            bin += to_string(0);
    }
    return bin;
}




// Convert Msg string to Binary stream
string generateMsgStream(string msg){
    string stream = "";
    cout<<"\n";
    for(int i=0; i<msg.size(); i++){
        int ascii = (int)msg[i];
        string temp = asciiToBin(ascii);
        stream += temp;
        cout<<msg[i]<<" => "<<ascii<<" => "<<temp<<endl;
    }
    return stream;
}




// COMPUTATION INVOLVED IN ENCRYPTION/DECRYPTION
string computation(string input_stream, vector<int>x, vector<int>y, vector<int>z){
    string output_stream = "";
    for(int i=0; i<input_stream.size(); i++){
        int m = majorityVote(x[8], y[10], z[10]);

        // doing operations on Array
        registerFunctioning(x, y, z, m);
            
        // keyStreamBit
        int s = x[18] ^ y[21] ^ z[22];

        // XOR of keystream bit and cipher character bit
        output_stream += ((input_stream[i]-'0') ^ s)+'0';
    }
    return output_stream;
}




// ENCRYPTION
string encryption(const string msg, vector<int> &x, vector<int> &y, vector<int> &z, const string key){
    cout<<"\nPlain Text: "<<msg<<endl;
    string msgStream = generateMsgStream(msg);
    cout<<"\nPlain Text as Binary stream: \n"<<msgStream<<"\n";

    // allocating registers x, y, z with key
    allocateRegisters(x,y,z,key);        
    cout<<"\n\nIntially Registers are (Encryption):\n";
    cout<<"X:\n";
    printRegister(x);
    cout<<"Y:\n";
    printRegister(y);
    cout<<"Z:\n";
    printRegister(z);
        
    cout<<"\nEncrypting.......\n";
    // encrypting
    string cipherStream = computation(msgStream,x,y,z);
    cout<<"\nCipher Stream:\n"<<cipherStream<<endl;
    string cipherText = BinToChar(cipherStream);
    return cipherText;
}




// DECRYPTION
string decryption(const string cipherText, vector<int> &x, vector<int> &y, vector<int> &z, const string key){
    cout<<"\nCipher Text: "<<cipherText<<endl;
    string cipherStream = generateMsgStream(cipherText);
    cout<<"\nCipher Text as Binary stream: "<<cipherStream<<endl;

    // allocating registers x, y, z with key
    allocateRegisters(x,y,z,key);
    cout<<"\n\nIntially Registers are (Decryption):\n";
    cout<<"X:\n";
    printRegister(x);
    cout<<"Y:\n";
    printRegister(y);
    cout<<"Z:\n";
    printRegister(z);


    cout<<"\nDecrypting.......\n";
    // decrypting
    string msgStream = computation(cipherStream,x,y,z);
    cout<<"\nMessage Stream:\n"<<msgStream<<endl;
    string plainText = BinToChar(msgStream);
    return plainText;
}




int main(){
    while(1){
        string msg;
        cout<<"\nEnter the Message: \n";
        cin.ignore();
        getline(cin, msg);

        // Linear feedback shift registers (LFSRs)
        vector<int> x(SIZEX), y(SIZEY), z(SIZEZ);

        // Key (64 bit)
        string k;
        k = generatekey();
        cout<<"\nKey (64 Bit): \n"<<k<<endl;
        cout<<"_________________________________________________________________________________________";

        // Encryption
        cout<<"\nENCRYPTION:\n";
        string encrypt = encryption(msg,x,y,z,k);
        cout<<"\nCipher Text: "<<encrypt<<endl;
        cout<<"_________________________________________________________________________________________";

        // Decryption
        cout<<"\nDECRYPTION:\n";
        string decrypt = decryption(encrypt,x,y,z,k);
        cout<<"\nPlain Text: "<<decrypt<<endl;
        cout<<"_________________________________________________________________________________________";

        cout<<"\n\nOriginal Message: "<<msg;
        cout<<"\nEncrypted Message: "<<encrypt;
        cout<<"\nDecrypted Message: "<<decrypt;
        cout<<"\n_________________________________________________________________________________________";

        char choice;
        cout<<"\nDo you want to continue? (y/n)\n";
        cin>>choice;
        if(choice == 'n' || choice == 'N')
            break;
    }
    return 0;
}

// First input should start with " Hello" (an extra space), as cin.ignore() ignore the first character of msg (needed to ignore '\n')