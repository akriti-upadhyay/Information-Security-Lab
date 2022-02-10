#include<iostream>
#include<vector>
#include<string>
using namespace std;


void printVector(vector<int> v){
    for(int i=0; i<v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

int main(){
    while(1){
        // Input Plain Text
        string msg;
        cout<<"\nEnter Plain Text: \n";
        cin.ignore();
        getline(cin, msg);

        int ptSize = msg.size();
        vector<int> plainTextArray(ptSize);
        for(int i=0; i<ptSize; i++){
            plainTextArray[i] = msg[i];
        }
        
        // Input Key
        string key;
        cout<<"\nEnter Key: \n";
        cin>>key;
        int keySize = key.size();
        // size(keyArray) = size(plainTextArray)
        vector<int> keyArray(ptSize);
        for(int i=0; i<ptSize; i++){
            keyArray[i] = key[i%keySize];
        }



        
        cout<<"_________________________________________________________________________________________";
        cout<<"\nBEHIND THE SCENES:\n";
        

        cout<<"\nPlain Text Array:\n";
        printVector(plainTextArray);
        cout<<"\nKey Array:\n";
        printVector(keyArray);
               

        // CREATING THE TABLE
        // S[] - state vector
        // T[] - key vector (Temporary array)
        // size(S) = size(T)
        // Assume size of S (let it be double of KeyArray)
        vector<int> S(keyArray.size()*2);
        vector<int> T(S.size());
        // Intialising S array
        for(int i=0; i<S.size(); i++){
            S[i] = i;
        }
        // Initialising T array with key
        for(int i=0; i<T.size(); i++){
            T[i] = keyArray[i % keyArray.size()];
        }
        cout<<"\nStateVector(S):\n";
        printVector(S);
        cout<<"\nTempArray(T):\n";
        printVector(T);
      


        // Step 1: KEY SCHEDULING
        // No. of Iterations = size of state(S) array
        for(int i=0, j=0; i<S.size(); i++){
            j = (j + S[i] + T[i]) % S.size();
            swap(S[i], S[j]);
        }
        cout<<"\nS after step 1 (key scheduling):\n";
        printVector(S);


        
        // Step 2: STREAM GENERATION
        // No. of Iterations = size of key
        vector<int> newKeyArray(keyArray.size());
        // New key - used for encryption and decryption
        int i=0, j=0;
        while(i<keyArray.size()){
            i = (i + 1) % S.size();
            j = (j + S[i]) % S.size();
            swap(S[i], S[j]);
            int t = (S[i]+S[j]) % S.size();
            newKeyArray[i] = S[t];
            i++;
        }
        cout<<"\nS after step 2 (stream generation):\n";
        printVector(S);
        cout<<"\nnewKeyArray:\n";
        printVector(newKeyArray);
       
        
        
        // Step 3: Encryption
        // PT XOR NewKey = CT
        cout<<"_________________________________________________________________________________________";
        cout<<"\nEncrypting......\n";
        vector<int> cipherText(plainTextArray.size());
        for(int i=0; i<plainTextArray.size(); i++){
            cipherText[i] = plainTextArray[i] ^ newKeyArray[i];
        }
        cout<<"\nCipher Text Array:\n";
        printVector(cipherText);
        string cipher = "";
        for(int i=0; i<cipherText.size(); i++){
            cipher += char(cipherText[i]);
        }
        cout<<"\nCipher Text: "<<cipher<<endl;
        


        // Step 3: Decryption
        // CT XOR NewKey = PT
        cout<<"_________________________________________________________________________________________";
        cout<<"\nDecrypting......\n";
        vector<int> decryptedPlainTextArray(cipherText.size());
        for(int i=0; i<cipherText.size(); i++){
            decryptedPlainTextArray[i] = cipherText[i] ^ newKeyArray[i];
        }
        cout<<"\nPlain text Array (After Decryption):\n";
        printVector(decryptedPlainTextArray);
        string decrypt = "";
        for(int i=0; i<decryptedPlainTextArray.size(); i++){
            decrypt += char(decryptedPlainTextArray[i]);
        }
        cout<<"\nDecrypted Plain Text: "<<decrypt;
        
        cout<<"\n_________________________________________________________________________________________";
        cout<<"\n\nOriginal Message: "<<msg;
        cout<<"\nEncrypted Message: "<<cipher;
        cout<<"\nDecrypted Message: "<<decrypt;

        char choice;
        cout<<"\n\nDo you want to continue? (y/n)\n";
        cin>>choice;
        if(choice == 'n' || choice == 'N')
            break;
    }
    return 0;
}