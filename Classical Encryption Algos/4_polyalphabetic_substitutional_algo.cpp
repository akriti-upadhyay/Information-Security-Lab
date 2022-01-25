#include <iostream>
#include <string>
using namespace std;

string generateKey(string msg, string keyWord){
    int sizeKeyword = keyWord.size();
    int msgSize = msg.size(); 
    // if keyword is longer than the msg
    if(sizeKeyword > msgSize){
        return keyWord.substr(0, msgSize);
    }
    // msg >= keyword
    for(int i=sizeKeyword; i<msg.size(); i++){
        keyWord.push_back(keyWord[i%sizeKeyword]);
    }
    return keyWord;
}
string encryption(string msg, string key) {
    string output;
    for(int i=0; i<msg.size(); i++){
        // converting to range 0-25
        char x = (msg[i] + key[i]) % 26; 
        // covert to range of ASCII Alphabet (65-90 | A-Z)
        if(msg[i] == ' ')
            x = ' ';
        else
            x = x + 'A';
        output.push_back(x);
    }
    return output;
}
string decryption(string encrypt, string key) {
    string output;
    int j=0;
    for (int i=0; i<encrypt.size(); i++) {
        // converting to range 0-25
        char x = (encrypt[i] - key[i] + 26) % 26;
        // covert to range of ASCII Alphabet (65-90 | A-Z)
        if(encrypt[i] == ' ')
            x = ' ';
        else
            x = x + 'A';
        output.push_back(x);
    }
    return output;
}

int main() {
    while(1){
        string keyWord;
        cout<<"\nEnter the key word (In Capital Letters): \n";
        cin>>keyWord;
        string msg;
        cout<<"\nEnter the Message (In Capital Letters): \n";
        cin.ignore();
        getline(cin,msg);
        string key = generateKey(msg, keyWord);
        string encrypt = encryption(msg, key);
        string decrypt = decryption(encrypt, key);
        cout<<"\nOriginal Message: "<<msg;
        cout<<"\nEncrypted Message: "<<encrypt;
        cout<<"\nDecrypted Message: "<<decrypt;
        char choice;
        cout<<"\nDo you want to continue? (y/n)\n";
        cin>>choice;
        if(choice == 'n' || choice == 'N')
            break;
    }
    return 0;
}