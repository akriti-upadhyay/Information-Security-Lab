#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;

// ENCRYPTION
string encryption(string msg, string key){
    int msgLen = msg.length();
    int keyLen = key.length();

    // creating matrix to store the msg
    int row = ceil(msgLen/(float)keyLen);
    int col = keyLen;
    char matrix[row][col];
    for(int i=0, k=0; i<row; i++){
        for(int j=0; j<col; j++){
            if(k < msgLen)
                matrix[i][j] = msg[k++];
            else    
                matrix[i][j] = '_';
        }
    }

    // Printing the matrix
    cout<<"\n\nMessage in matrix form: \n";
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    // Order of picking the coloumns for cipher text
    vector<int> order(keyLen);
    for(int i=0; i<key.size(); i++){
        order[key[i]-'0'-1] = i;
    }

    // generating cipher text
    string output = "";
    for(int i=0; i<order.size(); i++){
        for(int j=0; j<row; j++){
            if(matrix[j][order[i]] != '_'){
                output += matrix[j][order[i]];
            }
        }
    }
    return output;
}

// DECRYPTION
string decryption(string msg, string key){
    string output = "";
    int msgLen = msg.length();
    int keyLen = key.length();

    // creating matrix to store the msg
    int row = ceil(msgLen/(float)keyLen);
    int col = keyLen;
    int empty_cells = keyLen - (msgLen%keyLen);
    char matrix[row][col];

    // assigning default value to cols which are supposed to be empty
    for(int i=row-1, j=col-1; empty_cells && j>=0; j--){
        matrix[i][j] = '_';
        empty_cells--;
    }

    // Order of storing the encrypted msg coloumn-wise in the matrix
    vector<int> order(keyLen);
    for(int i=0; i<key.size(); i++){
        order[key[i]-'0'-1] = i;
    }

    // storing the encrypted msg in matrix
    for(int i=0, k=0; i<order.size(); i++){
        for(int j=0; j<row; j++){
            if(matrix[j][order[i]] != '_'){
                matrix[j][order[i]] = msg[k++];
            }
        }
    }    

    // Printing the matrix and retrieving orginal msg
    cout<<"\n\nMatrix after decryption: \n";
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cout<<matrix[i][j]<<" ";
            if(matrix[i][j]!='_')
                output += matrix[i][j];
        }
        cout<<endl;
    }
    
    return output;
}

int main(){
    while(1){
        string msg;
        cout<<"\nEnter The Message: \n";
        cin.ignore();
        getline(cin,msg);

        string key;
        cout<<"\nEnter the key: \n";
        cin>>key;

        // Finding the column permutation of the matrix
        transform(key.begin(), key.end(), key.begin(), ::toupper);
        string sortedKey = key;
        sort(sortedKey.begin(), sortedKey.end());
        string colPermutation = "";
        for(int i=0; i<key.size(); i++){
            for(int j=0; j<sortedKey.size(); j++){
                if(key[i] == sortedKey[j])
                    colPermutation += to_string(j+1);
            }
        }
        cout<<"\nColumn Permutation of the matrix will be: \n"<<colPermutation;

        
        string encrypt = encryption(msg, colPermutation);
        string decrypt = decryption(encrypt, colPermutation);
        cout<<"\n\nOriginal Message: "<<msg;
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

// First input should start with " Hello" (an extra space), as cin.ignore() ignore the first character of msg (needed to ignore '\n')
