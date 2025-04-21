#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

string geradorChaveRandom(int textsz){
    // gerador de numero aleatorio
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // definindo tamanho da chave como o teto da raiz do tamanho do texto
    int keysize=1;
    for(int i=1; i*i < textsz; i++) keysize=i;
    keysize++;

    string key="", alph = "abcdefghijklmnopqrstuvwxyz", newalph;
    
    // criando a chave ordenando aleatoriamente o alfabeto
    while((int)key.size() < keysize){
        newalph = alph;
        shuffle(newalph.begin(), newalph.end(), rng);
        for(int i=0; i < min(26, keysize-(int)key.size()); i++){
            key += newalph[i];
        }
    }
    return key;
}

int main(){
    
    int textsz;
    cin >> textsz;

    string key = geradorChaveRandom(textsz);

    cout << key << endl;
}