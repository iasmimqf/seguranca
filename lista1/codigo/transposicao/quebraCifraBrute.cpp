#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void quebra(vector<int>& sequencia, string& ciphertext, int keySz){
    // ordenando as colunas pela chave
    vector<pair<int, int>> ordKey;
    for(int i=0; i < keySz; i++) ordKey.emplace_back(sequencia[i], i);
    sort(ordKey.begin(), ordKey.end());

    //quebrando o ciphertext
    int textsz = (int)ciphertext.size()/keySz;
    vector<char> plaintext((int)ciphertext.size());
    for(int i=0; i < keySz; i++){
        for(int j=0; j < textsz; j++){
            plaintext[ordKey[i].second+keySz*j] = ciphertext[i*textsz + j];
        }
    }

    for(char c : plaintext) cout << c;
    cout << endl;
}

void ordem(int keySz, string& ciphertext){
    vector<int> sequencia;
    for(int i=0; i < keySz; i++) sequencia.push_back(i);
    do{
        quebra(sequencia, ciphertext, keySz);
    }while(next_permutation(sequencia.begin(), sequencia.end()));
}

int main(){
    
    string ciphertext;
    cout << "Digite a mensagem a ser descriptografada : \n";
    cin >> ciphertext;

    // chave de tamanho fixo igual ao teto da raiz do tamanho do texto
    int keySz = 1;
    for(int i=(int)ciphertext.size(); keySz*keySz < i; keySz++);
    
    // complexidade igual ao fatorial do tamanho da chave;    
    ordem(keySz, ciphertext);

    return 0;
}