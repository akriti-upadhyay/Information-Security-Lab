#include<iostream>
#include<string>
using namespace std;

int main(){
    while(1){
        string msg;
        cout<<"\nEnter the message: \n";
        cin.ignore();
        getline(cin, msg);
        int key;
        cout<<"Enter the key: ";
        cin>>key;
        char choice;
        cout<<"What you want to do with the message?\n1. Encrypt message\n2. Decrypt message\n";
        cin>>choice;
        // ENCRYPTION
        if(choice == '1'){
            for(int i=0; i<msg.size(); i++){
                //encrypting lower case letters
                if(msg[i]>='a' && msg[i]<='z'){
                    msg[i] = (((msg[i]-'a') + key) % 26) + 'a';
                }
                //encrypting upper case letters
                else if(msg[i]>='A' && msg[i]<='Z'){
                    msg[i] = (((msg[i]-'A') + key) % 26) + 'A';
                }
            }
            cout<<"\nEncrypted Message: "<<msg<<"\n\n";
        }
        // DECRYPTION
        else if(choice == '2'){
            for(int i=0; i<msg.size(); i++){
                //decrypting lower case letters
                if(msg[i]>='a' && msg[i]<='z'){
                    msg[i] = ((((msg[i]-'a') - key) + 26) % 26) + 'a';
                }
                //encrypting upper case letters
                else if(msg[i]>='A' && msg[i]<='Z'){
                    msg[i] = ((((msg[i]-'A') - key) + 26) % 26) + 'A';
                }                
            }
            cout<<"\nDecrypted Message: "<<msg<<"\n\n";
        }
        else{
            cout<<"Invalid Choice, Try again!";
        }
        cout<<"Do you want to continue? (y/n)\n";
        cin>>choice;
        if(choice == 'n')
            break;        
    }
    return 0;
}

// First input should start with " Hello" (an extra space), as cin.ignore() ignore the first character of msg (needed to ignore '\n')