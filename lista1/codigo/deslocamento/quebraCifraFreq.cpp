#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string descript_desloc(string& ciphertext, int k){
    string plaintext;
    for(char c : ciphertext){
        plaintext += (c-'a'+26-k) % 26 + 'a';
    }
    return plaintext;
}

void quebraDistrFreq_desloc(string &ciphertext){
    // alfabeto ordenado por frequencia
    string alphFreq = "aeosirdntcmuplvgbfqhjzxkwy";
    vector<int> frequence(26, 0);
    for(auto c : ciphertext){
        frequence[c-'a']++;
    }
    
    // vetor para ordenar os caracters do cyphertext por maior frequencia
    vector<pair<char, int>> ordChar;
    for(int i=0; i < 26; i++) ordChar.push_back({'a'+i, frequence[i]});
    sort(ordChar.begin(), ordChar.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        return a.second > b.second;
    });
    
    
    // brutando para descobrir o plaintext, com todos as 26 chaves possíveis, mas seguindo a ordem da maior frequencia
    for(int i=0; i < 26; i++){
        int k = (ordChar[0].first + 26 - alphFreq[i]) % 26;
        string plaintext = descript_desloc(ciphertext, k);
        cout << "Chave : " << k << " -> " << plaintext << "\n";
    }
}

int main(){
    string ciphertext;
    cout << "Digite a mensagem criptografada : \n";
    cin >> ciphertext;

    quebraDistrFreq_desloc(ciphertext);
}