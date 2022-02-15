#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
#define lli long long int

// Print vector
void printVector(vector<lli> v){
    for(int i=0; i<v.size(); i++)
        cout<<v[i]<<" ";
    cout<<"\n";
}

// GCD(a,b), where a>b
int gcd(int a, int b){
    if(a<b)
        return gcd(b,a);
    if(b==0)
        return a;
    return gcd(b, a%b);
}

// Extended Euclidean Algorithm 
lli gcdExtended(lli a, lli b, lli *x, lli *y) 
{ 
    // Base Case 
    if (a == 0) 
    { 
        *x = 0, *y = 1; 
        return b; 
    } 
    // To store results of recursive call 
    lli x1, y1; 
    lli gcd = gcdExtended(b%a, a, &x1, &y1); 
  
    // Update x and y using results of recursive call 
    *x = y1 - (b/a) * x1; 
    *y = x1; 
  
    return gcd; 
}

// Function to find modulo inverse of a 
lli mulInverse(lli a, lli m) 
{ 
    lli x, y; 
    lli g = gcdExtended(a, m, &x, &y); 
    if (g != 1) 
        return -1; 
    else
    { 
        // m is added to handle negative x 
        int res = (x%m + m) % m; 
        return res; 
    } 
} 

// Power function implementation
lli power(lli x, lli y)
{
    lli result = 1;
    while(y>0) {
        // y is even
        if(y%2 == 0) 
        {
            x = x * x;
            y = y / 2;
        }
        // y is odd
        else 
        {
            result = result * x;
            y = y - 1;
        }
    }
    return result;
}

// Converting ASCII values vector to string
string ASCIItoChar(vector<lli> v){
    string text = "";
    for(int i=0; i<v.size(); i++){
        text += (char)v[i];
        cout<<v[i]<<" => "<<(char)v[i]<<endl;
    }
    return text;
}

// Encryption
vector<lli> encryption(vector<lli> plainText, lli e, lli n){
    vector<lli> cipher;
    for(int i=0; i<plainText.size(); i++){
        cout<<"pow: "<<power(plainText[i], e)<<endl;
        cipher.push_back(power(plainText[i], e) % n);
    }
    return cipher;
}

// Decryption
vector<lli> decryption(vector<lli> cipherText, lli d, lli n){
    vector<lli> decryptedPT;
    for(int i=0; i<cipherText.size(); i++){
        cout<<"pow:"<<power(cipherText[i], d)<<endl;
        decryptedPT.push_back(power(cipherText[i], d) % n);
    }
    return decryptedPT;
}

int main(){
    while(1){
        // Taking plain text from user
        string msg;
        cout<<"\nEnter the Message: \n";
        cin.ignore();
        getline(cin, msg);
        // store ASCII value of plain text chars in array
        vector<lli> ptChars = {19};
        // for(lli i=0; i<msg.size(); i++)
        //     ptChars.push_back(msg[i]);
        printVector(ptChars);


        // STEP 1: 
        // take large prime numbers: p, q
        lli p = 3;
        lli q = 11;
        
        // STEP 2: 
        // n = p * q
        lli n = p*q;

        // STEP 3: 
        // z = (p-1)*(q-1);
        lli z = (p-1)*(q-1);

        // STEP 4: 
        // choose (e) relative prime to z (ie, GCD(e, z) = 1)
        // collection of relative primes of z
        vector<lli> relativePrimesOfZ;
        for(lli i=1; i<z; i++){
            if(gcd(i,z) == 1)
                relativePrimesOfZ.push_back(i);
        }
        // randomly selecting one coprime (e)
        lli e = relativePrimesOfZ[rand() % relativePrimesOfZ.size()];

        // STEP 5:
        // find d (multiplicative inverse of e % z), ie, (e*d)%z = 1
        lli d = mulInverse(e,z);

        cout<<"\np: "<<p<<"\nq: "<<q<<"\nn: "<<n<<"\nz: "<<z<<"\ne: "<<e<<"\nd: "<<d;

       
       
        // ENCRYPTION
        // Public key: {n, e}
        // C = P^e % n
        cout<<"\n___________________________________________________________";
        cout<<"\nENCRYPTION:\n";
        vector<lli> encryptASCII = encryption(ptChars, e, n);
        printVector(encryptASCII);
        string encrypt = ASCIItoChar(encryptASCII);
        cout<<"\nCipher text: "<<encrypt;
        
       
       
        // DECRYPTION
        // Private key: {n, d}
        // P = C^d % n
        cout<<"\n___________________________________________________________";
        cout<<"\nDECRYPTION:\n";
        vector<lli> decryptASCII = decryption(encryptASCII, d, n);
        printVector(decryptASCII);
        string decrypt = ASCIItoChar(decryptASCII);
        cout<<"\nDecrypted plain text: "<<decrypt;



        // OUTPUT
        cout<<"\n____________________________________________________________";
        cout<<"\n\nOriginal Message: "<<msg;
        cout<<"\nEncrypted Message: "<<encrypt;
        cout<<"\nDecrypted Message: "<<decrypt;
        cout<<"\n____________________________________________________________";

        char choice;
        cout<<"\nDo you want to continue? (y/n)\n";
        cin>>choice;
        if(choice == 'n' || choice == 'N')
            break;
    }
    return 0;
}

// First input should start with " Hello" (an extra space), as cin.ignore() ignore the first character of msg (needed to ignore '\n')