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
        int ptSize;
        cout<<"\nEnter the Size of Plain Text Array: \n";
        cin>>ptSize;
        vector<int> plainText(ptSize);
        cout<<"\nEnter the Plain Text Array: \n";
        for(int i=0; i<ptSize; i++){
            int x;
            cin>>x;
            plainText[i] = x;
        }
        
        // Input Key
        // size(key) = size(plainText)
        int keySize;
        vector<int> keyArray(ptSize);
        cout<<"\nEnter the Key Array: \n";
        for(int i=0; i<ptSize; i++){
            int x;
            cin>>x;
            keyArray[i] = x;
        }
        
        cout<<"\nplainText:\n";
        printVector(plainText);
        cout<<"\nkeyArray:\n";
        printVector(keyArray);
        

        
        cout<<"_________________________________________________________________________________________";
        cout<<"\nBEHIND THE SCENES:\n";
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
        vector<int> cipherText(plainText.size());
        for(int i=0; i<plainText.size(); i++){
            cipherText[i] = plainText[i] ^ newKeyArray[i];
        }
        cout<<"\nCipher Text:\n";
        printVector(cipherText);
        


        // Step 3: Decryption
        // CT XOR NewKey = PT
        cout<<"_________________________________________________________________________________________";
        cout<<"\nDecrypting......\n";
        vector<int> decryptedPlainText(cipherText.size());
        for(int i=0; i<cipherText.size(); i++){
            decryptedPlainText[i] = cipherText[i] ^ newKeyArray[i];
        }
        cout<<"\nPlain text:\n";
        printVector(decryptedPlainText);
        
        char choice;
        cout<<"\nDo you want to continue? (y/n)\n";
        cin>>choice;
        if(choice == 'n' || choice == 'N')
            break;
    }
    return 0;
}