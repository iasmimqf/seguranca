#include <iostream>
#include <string>

using namespace std;

string descript_desloc(string& ciphertext, int k){
    string plaintext;
    for(char c : ciphertext){
        plaintext += (c-'a'+26-k) % 26 + 'a';
    }
    return plaintext;
}

int main(){
    cout << "Digite a chave: ";
    int k;
    cin >> k;

    string ciphertext;
    cout << "Digite a mensagem a ser descriptografada : \n";
    cin >> ciphertext;

    // transforma o ciphertext em plaintext
    string plaintext = descript_desloc(ciphertext, k);

    cout << plaintext << "\n";

    return 0;
}