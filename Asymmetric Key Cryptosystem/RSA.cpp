#include <bits/stdc++.h>
using namespace std;

int n, z, e, d;
// Vector to store ASCII values of characters from A-Z 
vector<int> P;



// GCD(a,b)
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// Print the registers
void printRegister(vector<int> reg){
    for(int i=0; i<reg.size(); i++)
        cout<<reg[i]<<" ";
    cout<<"\n";
}


// ENCRYPTION
string encryption(string plain, int p, int q)
{
    // STEP 2: 
    n = p*q;
        
    // STEP 3: 
    z = (p-1)*(q-1);

    // STEP 4: 
    // choose (e) relative prime to z (ie, GCD(e, z) = 1)        
    for(int i=2;i<z;i++){
        if(gcd(z,i) == 1)
        {
            e = i;
            break;
        }
    }

    // STEP 5:
    // find d (multiplicative inverse of e % z), ie, (e*d)%z = 1     
    for(int i=2;;i++){
        if((e*i)%z == 1)
        {
            d = i;
            break;
        }
    }

    // output values
    cout<<"\ne = "<<e<<",   "<<"n = "<<n<<",   "<<"d = "<<d<<endl;


    // Encrypting
    // Public key: {n, e}
    // C = P^e % n
    string result, res, cipher;
    
    // converting text form of plain text chars to ASCII equivalent (converting range 65-90 to 0-25)
    for(int i=0; i<plain.length(); i++)
    {
        // if char is b/w A-Z
        if((int)plain[i]>64 && (int)plain[i]<91)
            // bringing value in range 0-25
            res.push_back(plain[i]-65);
        // keep space as it is
        if(plain[i]==' ')
            res.push_back(' ');
    }


    // encryption process => P^e % n
    for(int i=0; i<res.length(); i++)
    {
        long long z = 1; // P^e
        if(res[i] == ' ')
        {
            result.push_back(' ');
            P.push_back((int)res[i]);
        }
        else
        {
            // P^e
            for(int j=0; j<e; j++)
                z = ((int)res[i]) * z;
            // store in P to diffentiate b/w numbers like 7, 33, where 7%26 = 33%26 = 7 (storing 1 in P, if z%n > 26 | storing 0, if z%n < 26)
            P.push_back((z % n)/26);
            result.push_back((z % n)%26);
        }
    }
    // cout<<"P VECTOR: ";
    // printRegister(P);


    // changing ASCII values to alphabetic characters (converting range 0-25 to 65-90)
    for(int i=0; i<result.length() ;i++)
    {
        if((int)result[i]>=0 && (int)result[i]<26)
            cipher.push_back(result[i]+65);
        if(result[i]==' ')
            cipher.push_back(' ');
    }
    return cipher;
}



// DECRYPTION
string decryption(string cipher)
{
    // Decryption
    // Private key: {n, d}
    // P = C^d % n  

    string result, res, final;

    // converting text form of cipher text chars to ASCII equivalent (converting range 65-90 to 0-25)
    for(int i=0; i<cipher.length(); i++)
    {
        if(cipher[i]>64 && cipher[i]<91)
            // add P[i]*26 if > 26
            res.push_back((cipher[i]-65) + (P[i]*26));
        if(cipher[i] == ' ')
            res.push_back(' ');
    }

    // decryption process => C^d % n
    for(int i=0; i<res.length(); i++)
    {
        long long z = 1; // C^d
        if(res[i] == ' ')
            result.push_back(' ');
        else
        {
            // C^d
            for(int j=0; j<d; j++)
                z = ((int)res[i]) * z;
            result.push_back(z % n);
        }
    }

    // changing ASCII values to alphabetic characters (converting range 0-25 to 65-90)
    for(int i=0; i<result.length(); i++)
    {
        if((int)result[i]>=0 && (int)result[i]<26)
            final.push_back(result[i] + 65);
        if(result[i] == ' ')
            final.push_back(' ');
    }

    return final;
}



int main()
{
    // Taking plain text from user
    string plain;
    cout<<"\nEnter Plain Text: "<<endl;
    getline(cin,plain);


    // STEP 1: 
    // take large prime numbers: p, q
    int p;
    int q;
    cout<<"\nEnter two prime numbers p and q (such that, 25 < p*q < 40): \n";
    // possible values (3,11) (3,13) (5,7)
    cin>>p>>q;
        
    // Encryption
    string cipher = encryption(plain,p,q);
    cout<<"\nCipher Text: "<<cipher<<endl;

    // Decryption
    string decrypt = decryption(cipher);
    cout<<"Decrypted Plain Text: "<<decrypt<<"\n\n";

    return 0;
}