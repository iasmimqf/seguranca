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

void quebraBruteForces_desloc(string&  ciphertext){
    // brutando para descobrir o plaintext, com todos os 25 possíveis k's
    for(int i=25; i > 0; i--){
        string plaintext = descript_desloc(ciphertext, i);
        cout << "Chave : " << 26-i << " -> " << plaintext << "\n";
    }
}

int main(){
    string ciphertext;
    cout << "Digite a mensagem criptografada : \n";
    cin >> ciphertext;

    quebraBruteForces_desloc(ciphertext);

    return 0;
}