#include<iostream>
using namespace std;
#define lli long long int
lli g ,n ;

// power function implementation
lli power(lli x, lli y)
{
    lli result = 1;
    while (y > 0) {
        if (y % 2 == 0) // y is even
        {
            x = x * x;
            y = y / 2;
        }
        else // y isn't even
        {
            result = result * x;
            y = y - 1;
        }
    }
    return result;
}

int main(){
    while(1){
        // string msg;
        // cout<<"\nEnter the Message: \n";
        // cin.ignore();
        // getline(cin, msg);
        cout<<"\nEnter the value of G (public): ";
        cin>>g;
        cout<<"\nEnter the value of N (public): ";
        cin>>n;
        lli x,y;
        cout<<"\nEnter Alice private key: ";
        cin>>x;
        cout<<"\nEnter Bob private key: ";
        cin>>y;
        lli aliceSend,bobSend;
        aliceSend = power(g,x);
        // send to bob
        bobSend = power(g,y);
        // send to alice

        // at Alice end








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