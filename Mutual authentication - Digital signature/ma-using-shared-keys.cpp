#include<iostream>
#include<string>
using namespace std;
// shared key
int k_ab;
// random challenges
string R1, R2;


// caesar-cipher encryption
string encryption(string msg){
    for(int i=0; i<msg.size(); i++){
        //encrypting lower case letters
        if(msg[i]>='a' && msg[i]<='z'){
            msg[i] = (((msg[i]-'a') + k_ab) % 26) + 'a';
        }
        //encrypting upper case letters
        else if(msg[i]>='A' && msg[i]<='Z'){
            msg[i] = (((msg[i]-'A') + k_ab) % 26) + 'A';
        }
    }
    return msg;
}


// caesar-cipher decryption
string decryption(string msg){
    for(int i=0; i<msg.size(); i++){
        //decrypting lower case letters
        if(msg[i]>='a' && msg[i]<='z'){
            msg[i] = ((((msg[i]-'a') - k_ab) + 26) % 26) + 'a';
        }
        //encrypting upper case letters
        else if(msg[i]>='A' && msg[i]<='Z'){
            msg[i] = ((((msg[i]-'A') - k_ab) + 26) % 26) + 'A';
        }                
    }
    return msg;
}

void generateKey(){
    cout<<"\nEnter the key: ";
    cin>>k_ab;
}

// verifying username
bool verifyUser(string username){
    if(username == "alice")
        return true;
    return false;
}

string sendToBob(string E_R1){
    // STEP 5:
    // Bob decrypts encrypted R1 and compares its value with his own R1
    // D(E(R1)) = R1
    string D_E_R1 = decryption(E_R1);
    if(R1 == D_E_R1)
        cout<<"\nBob verifies R1";
    else
        cout<<"\nBob doesn't verify R1";

    // STEP 6:
    // Bob encrypts R2 using shared key and send to Alice
    string E_R2 = encryption(R2);
    return E_R2;
}

string sendToAlice(){
    // STEP 3:
    // Alice generates R2, which she'll send to Bob
    cout<<"\nEnter a text random challenge R2: ";
    cin>>R2;
  
    // STEP 4:
    // Alice encrypts R1 using shared key and send to Bob, along with R2
    string E_R1 = encryption(R1); 
    string E_R2 = sendToBob(E_R1);

    return E_R2;
}

// main
int main(){
    // generate shared key
    cout<<"\nGenerating shared key for Alice and Bob: ";
    generateKey();


    // STEP 1:
    string username = "alice";
    // if user is not verified => end the process
    if(!verifyUser(username))
        return 0;


    // STEP 2:
    // Bob generates R1 and send to Alice
    cout<<"_______________________________________________________________";
    cout<<"\nEnter a text random challenge R1: ";
    cin>>R1;
    string E_R2 = sendToAlice();

    // STEP 7:
    // Alice decrypts encrypted R2 and compares its value with her own R2
    // D(E(R2)) = R2 
    string D_E_R2 = decryption(E_R2);
    if(R2 == D_E_R2)
        cout<<"\nAlice verifies R2";
    else
        cout<<"\nALice doesn't verify R2";
    
    return 0;  
}

/*
Generating shared key for Alice and Bob:
Enter the key: 3
_______________________________________________________________
Enter a text random challenge R1: Hello

Enter a text random challenge R2: Akriti

Bob verifies R1
Alice verifies R2
*/