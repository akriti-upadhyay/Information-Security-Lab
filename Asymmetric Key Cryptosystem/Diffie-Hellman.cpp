#include<iostream>
using namespace std;

// Array of first 26 prime numbers 
// A-Z => 26 alphabets (only Uppercase)
// Pick value of 'g' according to the ASCII value of alphabet character
int g[26]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};


void diffie_helman(string key, int pvtA, int pvtB, int prime)
{
    string a, b, sendToB, sendToA;
    // sendToB = g^x % n
    // b = sendToB ^ y => (g^x % n)^y => shared key of B
    // sendToA = g^y % n
    // a = sendToA ^ x => (g^y % n)^x => shared key of A
    

    // computing, sendToB = g^x % n
    for(int i=0; i<key.length(); i++)
    {
        long long z = 1;  // z = g^x
        // keep spaces as it is
        if(key[i] == ' ')
            sendToB.push_back(' ');
        else
        {
            // if ascii(char) is in range A-Z
            if(key[i]>64 && key[i]<91){
                // g^x 
                for(int j=0; j<pvtA; j++)
                    z = z * g[key[i]-65];
            }
            sendToB.push_back(z % prime);
        }
    }

    // computing b = sendToB ^ y
    for(int i=0; i<sendToB.length(); i++)
    {
        long long z = 1;
        // keep space as it is
        if(sendToB[i] == ' ')
            b.push_back(' ');
        else
        {
            // sendTOB ^ y
            for(int j=0; j<pvtB; j++)
                z = z * sendToB[i];
            // ascii to alphabet
            b.push_back(((z % prime) % 26) + 65);
        }
    }

    // computing, sendToA = g^y % n
    for(int i=0; i<key.length(); i++)
    {
        long long z = 1;
        if(key[i] == ' ')
            sendToA.push_back(' ');
        else
        {
            if(key[i]>64 && key[i]<91){
                // g^y
                for(int j=0; j<pvtB; j++)
                    z = z * g[key[i]-65];
            }
            sendToA.push_back(z % prime);
        }
    }

    // computing a = sendToA ^ x
    for(int i=0; i<sendToA.length(); i++)
    {
        long long z = 1;
        if(sendToA[i] == ' ')
            a.push_back(' ');
        else
        {
            
            for(int j=0; j<pvtA; j++)
                z = z*sendToA[i];
            // ascii to alphabet
            a.push_back(((z % prime) % 26) + 65);
        }
    }
    cout<<"\nFinal shared key of A: "<<a<<endl;
    cout<<"Final shared key of B: "<<b<<endl;
    if(a == b)
        cout<<"Shared keys of A and B are equal\n\n";
    else
        cout<<"Shared keys of A and B are NOT equal\n\n";
}

int main()
{
    // Input the encrypted key
    string key;
    // pvtA - private key of A (x)
    // pvtB - private key of B (y)
    int pvtA, pvtB;
    cout<<"\nEnter the key to be exchanged (UPPERCASE ALPHABETS ONLY): \n";
    getline(cin,key);
    
    // n - prime num
    int n;
    // Bcoz max. value we can handle is 10^100 (otherwise overflow in datatypes)
    cout<<"\nEnter a prime number (less than 100)"<<endl;
    cin>>n; 


    cout<<"\nEnter the private keys of A and B, \nNOTE: \n1. priv_key(A) < priv_key(B)\n2. Both the private keys should be <= 10)\n";
    cout<<"\nEnter private key of A: \n";
    cin>>pvtA;   // x
    cout<<"\nEnter private key of B: \n";
    cin>>pvtB;   // y

    // Key distribution algorith
    diffie_helman(key, pvtA, pvtB, n);
    
    return 0;
}

