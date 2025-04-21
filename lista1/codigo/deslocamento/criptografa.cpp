#include <iostream>
#include <string>

using namespace std;

string cript_desloc(string& plaintext, int k){
    string ciphertext;
    for(char c : plaintext){
        ciphertext += (c-'a'+k) % 26 + 'a';
    }
    return ciphertext;
}

int main(){
    cout << "Digite a chave : ";
    int k;
    cin >> k;
    k %= 26;

    string plaintext;
    cout << "Digite a mensagem a ser criptografada : \n";
    cin >> plaintext;

    // transforma o plaintext em ciphertext
    string ciphertext = cript_desloc(plaintext, k);

    cout << ciphertext << "\n";

    return 0;
}