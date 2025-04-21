#include <iostream>
#include <string>
using namespace std;

double calcularMatching(const string& str1, const string& str2) {
    int matches = 0;

    for (size_t i = 0; i < str1.length(); i++) {
        if (str1[i] == str2[i]) {
            matches++;
        }
    }

    // retorna o valor do matching (matches / tamanho da string)
    return (matches*1.0) / (double)str1.length();
}

int main() {
    double maxMatching=0;
    string str1, str2, strM="";

    cin >> str1;
    while(cin >> str2){
        double matching = calcularMatching(str1, str2);
        if(matching > maxMatching){
            strM = str2;
            maxMatching = matching;
        }
    }


    cout << maxMatching*100 << endl;
    cout << strM << endl;

    return 0;
}