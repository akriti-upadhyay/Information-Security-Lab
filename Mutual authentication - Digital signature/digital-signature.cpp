#include<iostream>
#include<vector>
using namespace std;
// keys for alice
pair<int, int> k_r, k_u;

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
void rsa(){
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
    k_r = {n, e};
    k_u = {n, d};
}

int sendToBob(int E_order){
    // STEP 4:
    // Bob decrypts the encrypted order using ALice's public key
    int D_order = decryption(E_order, k_u.second, k_u.first);
    return D_order;
}

// main
int main(){
    cout<<"\nGenerating public and private keys for Alice: ";
    rsa();

    // STEP 1:
    int order;
    cout<<"\nEnter the no. of shares Alice wants to order: ";
    cin>>order;

    // STEP 2:
    // alice encrypts the order using her private key
    int E_order = encryption(order, k_r.second, k_r.first);

    // STEP 3:
    // alice sends the encrypted order to Bob
    int D_order = sendToBob(E_order);

    // STEP 5:
    // Alice is authenticated
    if(order == D_order)
        cout<<"\nThe order was send by Alice\n";
    else    
        cout<<"\nThe order was NOT send by Alice\n";
    return 0;
}

/*
Generating public and private keys for Alice: 
Enter p: 3
Enter q: 7

Enter the no. of shares Alice wants to order: 14

The order was send by Alice
*/