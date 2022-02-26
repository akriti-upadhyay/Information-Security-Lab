#include <bits/stdc++.h>
#define ll long long
using namespace std;

// function to find GCD using Euclid algorithm
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// function to find modular multiplicative inverse
ll euclideanAlgo(ll z, ll e1)
{
    ll x1 = 1, x2 = 0, x3 = z;
    ll y1 = 0, y2 = 1, y3 = e1;
    ll q;
    vector<ll> temp(3);
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
ll binpow(ll a, ll b, ll m)
{
    a %= m;
    ll res = 1;
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
ll encryption(int ptext, ll e, ll n)
{
    ll cipher;
    cipher = binpow(ptext, e, n);
    return cipher;
}

// function for decryption
ll decryption(ll cipher, ll d, ll n)
{
    ll ptext;
    ptext = binpow(cipher, d, n);
    return ptext;
}

// main
int main()
{
    ll p, q;

    cout << "\nEnter p: ";
    cin >> p;
    cout << "\nEnter q: ";
    cin >> q;

    ll n = p * q;
    ll z = (p - 1) * (q - 1);

    ll e;
    for (int i = 2; i < z; i++)
    {
        if (gcd(i, z) == 1)
        {
            e = i;
            break;
        }
    }
    cout << "\nValue of e  is: " << e;
    ll d = euclideanAlgo(z, e);

    cout << "\nValue of d  is: " << d;

    ll plainText, encText, decText;
    cout << "\n\nEnter a numeric plain text: ";
    cin >> plainText;

    encText = encryption(plainText, e, n);
    cout << "\nEncrypted number is: " << encText;

    decText = decryption(encText, d, n);
    cout << "\nDecrypted number is: " << decText;
    return 0;
}
// TC
// p = 3
// q = 7
// plainText = 19