#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string descriptTransposicao(string k, string ciphertext){
    // tamanho da chave
    int keySz = (int)k.size();
    
    // ordenando as colunas pela chave
    vector<pair<char, int>> ordKey;
    for(int i=0; i < keySz; i++) ordKey.emplace_back(k[i], i);
    sort(ordKey.begin(), ordKey.end());

    //decifrando o ciphertext
    int columnsz = (int)ciphertext.size()/keySz;
    string plaintext((int)ciphertext.size(), 'a');
    for(int i=0; i < keySz; i++){
        for(int j=0; j < columnsz; j++){
            plaintext[ordKey[i].second+keySz*j] = ciphertext[i*columnsz + j];
        }
    }

    return plaintext;
}

int main(){

    cout << "Digite a chave : ";
    string k;
    cin >> k;

    string ciphertext;
    cout << "Digite a mensagem a ser descriptografada : \n";
    cin >> ciphertext;

    string plaintext = descriptTransposicao(k, ciphertext);
    cout << plaintext << "\n";
}