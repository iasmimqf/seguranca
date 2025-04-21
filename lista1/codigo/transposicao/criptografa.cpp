#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

string criptTransposicao(string k, string plaintext){
    //gerador de numero aleatório
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int keySz = (int)k.size();

    // organizando o plaintext na matriz já transposta
    // cada string do vetor representa uma coluna
    vector<string> matriz(keySz, "");
    for(int i=0; i < (int)plaintext.size(); i++){
        matriz[i%keySz] += plaintext[i];
    }

    // ordenando as colunas pela chave
    vector<pair<char, int>> ordKey;
    for(int i=0; i < keySz; i++) ordKey.emplace_back(k[i], i);
    sort(ordKey.begin(), ordKey.end());

    // criando o cyphertext
    string ciphertext = "";
    for(auto [c, pos] : ordKey){
        ciphertext += matriz[pos];
        // quando a palavra eh menor do que o padrao, completar com um caracter aleatorio
        if((int)matriz[pos].size() < ((int)plaintext.size()+keySz-1)/keySz) 
            ciphertext += 'a' + (rng()%26);
    }
    return ciphertext;
}

int main(){
    cout << "Digite a chave : ";
    string k;
    cin >> k;

    string plaintext;
    cout << "Digite a mensagem a ser criptografada : \n";
    cin >> plaintext;

    string ciphertext = criptTransposicao(k, plaintext);   

    cout << ciphertext << "\n";
}