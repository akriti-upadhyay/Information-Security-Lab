#include <bits/stdc++.h>
using namespace std;
#define lli long long int

lli power(lli a, lli b, lli P)
{
    if (b == 1)
        return a;
    else
        return (((lli)pow(a, b)) % P);
}

int main()
{
    lli P, G, x, a, y, b, keyAlice, keyBob;
    cout << "\nEnter the value of P (public): ";
    cin >> P;
    // P = 21;

    cout << "\nEnter the value of G (public): ";
    cin >> G;
    // G = 7;

    cout << "\nEnter the private key a for Alice : ";
    cin >> a;
    // a = 4;
    x = power(G, a, P);

    cout << "\nEnter the private key b for Bob : : ";
    cin >> b;
    // b = 3;
    y = power(G, b, P);

    keyAlice = power(y, a, P);
    keyBob = power(x, b, P);
    cout << "\nShared key recieved by Alice is : " << keyAlice;
    cout << "\nShared key recieved by Bob is : " << keyBob;
    return 0;
}