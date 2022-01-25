#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

int main(){
    unordered_map<char,char> map = {
        {'A', 'Q'}, {'B', 'W'}, {'C', 'E'}, {'D', 'R'}, {'E', 'T'}, {'F', 'Y'}, {'G', 'U'}, {'H', 'I'}, {'I', 'O'}, {'J', 'P'}, {'K', 'A'}, {'L', 'S'}, {'M', 'D'}, {'N', 'F'}, {'O', 'G'}, {'P', 'H'}, {'Q', 'J'}, {'R', 'K'}, {'S', 'L'}, {'T', 'Z'}, {'U', 'X'}, {'V', 'C'}, {'W', 'V'}, {'X', 'B'}, {'Y', 'N'}, {'Z', 'M'}, 
        {'a', 'q'}, {'b', 'w'}, {'c', 'e'}, {'d', 'r'}, {'e', 't'}, {'f', 'y'}, {'g', 'u'}, {'h', 'i'}, {'i', 'o'}, {'j', 'p'}, {'k', 'a'}, {'l', 's'}, {'m', 'd'}, {'n', 'f'}, {'o', 'g'}, {'p', 'h'}, {'q', 'j'}, {'r', 'k'}, {'s', 'l'}, {'t', 'z'}, {'u', 'x'}, {'v', 'c'}, {'w', 'v'}, {'x', 'b'}, {'y', 'n'}, {'z', 'm'}, {' ', '$'}
    };
    while(1){
        string msg;
        cout<<"\nEnter the message: \n";
        cin.ignore();
        getline(cin, msg);
        char choice;
        cout<<"What you want to do with the message?\n1. Encrypt message\n2. Decrypt message\n";
        cin>>choice;
        // ENCRYPTION
        if(choice == '1'){
            for(int i=0; i<msg.size(); i++){
                msg[i] = map[msg[i]];
            }
            cout<<"\nEncrypted Message: "<<msg<<"\n\n";
        }
        // DECRYPTION
        else if(choice == '2'){
            for(int i=0; i<msg.size(); i++){
                // find the key in map with value msg[i], and assign it to msg[i]
                for(auto &it:map){
                    if(it.second == msg[i]){
                        msg[i] = it.first;
                        break;
                    }
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