#include<iostream>
#include<vector>
using namespace std;
// keys for alice and bob
pair<int, int> k_ra, k_ua;
pair<int, int> k_rb, k_ub;
// random challenges
// R1 = 12;
// R2 = 11;
int R1, R2;

// function to find GCD using Euclid algorithm
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// function to find modular multiplicative inverse
int euclideanAlgo(int z, int e1)
{
    int x1 = 1, x2 = 0, x3 = z;
    int y1 = 0, y2 = 1, y3 = e1;
    int q;
    vector<int> temp(3);
    while (y3 != 1)
    {
        q = x3 / y3;
        temp[0] = y1;
        temp[1] = y2;
        temp[2] = y3;
        y1 = x1 - y1 * q;
        y2 = x2 - y2 * q;
        y3 = x3 - y3 * q;
        x1 = temp[0];
        x2 = temp[1];
        x3 = temp[2];
    }
    if (y2 > 0)
        return y2;
    else
        return y2 + z;
}

// binary exponentiation function
int binpow(int a, int b, int m)
{
    a %= m;
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// function for encryption
int encryption(int ptext, int e, int n)
{
    int cipher;
    cipher = binpow(ptext, e, n);
    return cipher;
}

// function for decryption
int decryption(int cipher, int d, int n)
{
    int ptext;
    ptext = binpow(cipher, d, n);
    return ptext;
}

// generating keys using RSA Algo
void rsa(pair<int, int> &k_ra, pair<int, int> &k_ua){
    int p, q;
    cout<<"\nEnter p: ";
    cin >> p;
    cout<<"Enter q: ";
    cin>>q;

    int n = p * q;
    int z = (p - 1) * (q - 1);

    int e;
    for (int i = 2; i < z; i++){
        if (gcd(i, z) == 1){
            e = i;
            break;
        }
    }
    int d = euclideanAlgo(z, e);
    k_ra = {n, e};
    k_ua = {n, d};
}

int sendToAlice(int E_kua, int D_krb){
    // STEP 6:
    if(R2 == D_krb)
        cout<<"\nAlice verifies R2";
    else{ 
        cout<<"\nAlice doesn't verifies R2";
        return 0;
    }
    // STEP 7:
    // decrypting using private key of Bob
    // D_kra(E_kua(R1)) = R1
    int D_kra = decryption(E_kua, k_ra.second, k_ra.first);
    return D_kra;    
}

bool sendToBob(string username, int E_kub){
    if(username == "alice"){
        // STEP 3:
        // decrypting using private key of Bob
        // D_krb(E_kru(R2)) = R2
        int D_krb = decryption(E_kub, k_rb.second, k_rb.first);

        // STEP 4:
        // input R1
        cout<<"\nEnter a numeric random challenge R1: ";
        cin>>R1;

        // encrypt R1 using public key of Alice
        int E_kua = encryption(R1, k_ua.second, k_ua.first);

        // STEP 5 and STEP 8:
        int D_kra = sendToAlice(E_kua, D_krb);
        if(D_kra == R1)
            return true;
    }
    return false;
}

// main
int main(){
    // keys for alice 
    cout<<"\nGenerating public and private keys for Alice (a): ";
    rsa(k_ra, k_ua);

    // keys for bob 
    cout<<"_______________________________________________________________";
    cout<<"\nGenerating public and private keys for Bob (b): ";
    rsa(k_rb, k_ub);


    // STEP 1:
    // R2
    cout<<"_______________________________________________________________";
    cout<<"\nEnter a numeric random challenge R2: ";
    cin>>R2;
    string username = "alice";
    // encrypt R2 using public key of Bob
    int E_kub = encryption(R2, k_ub.second, k_ub.first);

    // STEP 2 and STEP 9:
    if(sendToBob(username, E_kub))
        cout<<"\nBob verifies R1";
    else    
        cout<<"\nBob doesn't verifies R1";

    return 0;  
}

/*
Generating public and private keys for Alice (a): 
Enter p: 3
Enter q: 7
_______________________________________________________________
Generating public and private keys for Bob (b):
Enter p: 3
Enter q: 5
_______________________________________________________________
Enter a numeric random challenge R2: 12

Enter a numeric random challenge R1: 11

Alice verifies R2
Bob verifies R1
*/