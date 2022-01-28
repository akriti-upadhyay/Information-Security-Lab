#include<iostream>
using namespace std;

// GETTING BINARY FORM OF A DECIMAL NUMBER
string getBinary(int num){
    string bin = "";
    for(int i = 1<<5; i>0; i=i/2){
        if((num & i) != 0)
            bin += to_string(1);
        else
            bin += to_string(0);
    }
    return bin;
}

// GENERATING BIT STRING FROM THE MSG
string generateBitString(string msg, string map){
    string bit = "";
    // cout<<"\nBinary representation of message characters:\n";
    for(int i=0; i<msg.length(); i++){
        int index = map.find(msg[i]);
        string binary = getBinary(index);
        bit += binary;
        // cout<<msg[i]<<" => "<<getBinary(index)<<" ("<<index<<")\n";
    }
    return bit;
}

// GENERATING A RANDOM OTP
string generateOTP(int len){
    string otp = "";
    for(int i=0; i<len; i++)
        otp += to_string(rand()%2);
    return otp;
}


// GETTING CHARACTER FROM DECIMAL VAL (Bin -> Dec)
char getCharacter(string binary, string map){
    char reqChar;
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
    reqChar = map[dec_val];
    cout<<binary<<" ("<<dec_val<<") => "<<reqChar<<endl;
    return reqChar;
}


// XOR OF TWO BINARY STRINGS
string getXOR(string msg, string otp){
    string XOR = "";
    for(int i=0; i<msg.size(); i++){
        XOR += to_string((msg[i]-'0') ^ (otp[i]-'0'));
    }
    return XOR;
}

// GENERATE MSG FROM XOR STRING
string XORToMsg(string XOR, string map){
    // getting cipher string from the XOR string obtained
    // 2^6 = 32 (we are representing binary form in 6 bits) (0 - 63)
    string msg = "";
    int i=0;
    while(i<XOR.size()){
        // combining 6 bits at a time to retrieve the corresponding character from the binary form
        string binOfChar = "";
        for(int j=i; j<i+6; j++){
            binOfChar += XOR[j];
        }
        i = i+6;
        msg += getCharacter(binOfChar, map);
    }
    return msg;
}

// ENCRYPTION
string encryption(string msg, string otp, string map){
    string XOR = getXOR(msg, otp);
    cout<<"\nAfter XOR (Encryption Step):\n"<<XOR<<"\n\n";
    
    string output = XORToMsg(XOR, map);
    cout<<"\nEncrypted Message: "<<output<<endl;
    return output;
}

// DECRYPTION
string decryption(string msg, string otp, string map){
    string bitString = generateBitString(msg, map);
    cout<<"\nCipher Text in Bit String form:\n"<<bitString<<endl;

    string XOR = getXOR(bitString, otp);
    cout<<"\nAfter XOR (Decryption Step):\n"<<XOR<<"\n\n";

    string output = XORToMsg(XOR, map);
    cout<<"\nDecrypted Message: "<<output<<endl;
    return output;
}

int main(){
    while(1){
        string map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890. ";
        string msg;
        cout<<"\nEnter The Message: \n";
        cin.ignore();
        getline(cin,msg);

        // generate bit string
        string bitString = generateBitString(msg, map);
        cout<<"\nOriginal message in Bit String form:\n"<<bitString;
        // generate OTP
        string otp = generateOTP(bitString.length());
        cout<<"\n\nOTP: \n"<<otp<<"\n";
       
        cout<<"_________________________________________________________________________________________";
        cout<<"\nENCRYPTION:\n";
        string encrypt = encryption(bitString, otp, map);
        cout<<"_________________________________________________________________________________________";
        cout<<"\nDECRYPTION:\n";
        string decrypt = decryption(encrypt, otp, map);

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
