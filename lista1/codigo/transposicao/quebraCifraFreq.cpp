#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "tabela_trigrafos.hpp"
#include "tabela_digrafos.hpp"

using namespace std;

typedef tuple<double, vector<int>, vector<int>> combo;

void quebra(vector<int>& sequencia, string& ciphertext, int keySz){
    // ordenando as colunas pela chave
    vector<pair<int, int>> ordKey;
    for(int i=0; i < keySz; i++) ordKey.emplace_back(sequencia[i], i);
    sort(ordKey.begin(), ordKey.end());

    //quebrando o ciphertext
    int columnSz = (int)ciphertext.size()/keySz;
    vector<char> plaintext((int)ciphertext.size());
    for(int i=0; i < keySz; i++){
        for(int j=0; j < columnSz; j++){
            plaintext[ordKey[i].second+keySz*j] = ciphertext[i*columnSz + j];
        }
    }

    for(char c : plaintext) cout << c;
    cout << endl;
}

// cria os 10 chaves mais provaveis
vector<combo> novaLista(int keySz, vector<combo>& lastList, vector<vector<double>>& dupla_prob, vector<vector<vector<double>>>& trio_prob){
    // verifica se o tamanho da possivel chave eh igual ao tamanho da chave
    if((int)(get<1>(lastList[0])).size() == keySz) return lastList;
    vector<tuple<int, vector<int>, vector<int>>> newList;
    for(auto [probabilidade, ordem, visited] : lastList){
        for(int i=0; i < keySz; i++){
            // verifica se o elemento nao esta presente na lista
            if(find(visited.begin(), visited.end(), i) == visited.end()){
                int szOrdem = (int)ordem.size();
                // soma a probabilidade da nova coluna com a ultima coluna
                double new_prob = probabilidade + dupla_prob[ordem[szOrdem-1]][i];
                if(szOrdem > 1) new_prob += trio_prob[ordem[szOrdem-2]][ordem[szOrdem-1]][i];
                vector<int> new_ordem = ordem;
                new_ordem.push_back(i);
                vector<int> new_visited = visited;
                new_visited.push_back(i);
                sort(new_visited.begin(), new_visited.end());
                newList.emplace_back(new_prob, new_ordem, new_visited);
            }
        }
    }
    sort(newList.begin(), newList.end(), [](const auto& a, const auto& b) {
        return get<0>(a) > get<0>(b);  // ordem descrescente
    });
    //mantem os 10 primeiros arranjos com maior probabilidade de estarem certos
    lastList = vector<combo>(newList.begin(), newList.begin()+min(10, (int)newList.size()));
    return novaLista(keySz, lastList, dupla_prob, trio_prob);
}

// imprimi todos os cyclic shifts possiveis das 10 combinacoes mais provaveis
// complexidade O(10*keySz*|ciphertext|)
void quebraFreq(int keySz, string& ciphertext, vector<vector<double>>& dupla_prob, vector<vector<vector<double>>> trio_prob){
    // probabilidade do arranjo, vetor das colunas na ordem colocada, vetor das colunas em ordem crescente
    vector<combo> listaArranjos = {{0, {0}, {0}}};
    listaArranjos = novaLista(keySz, listaArranjos, dupla_prob, trio_prob);
    // percorrendo os 10 melhores arranjos
    for(auto [prob, ordem, visited] : listaArranjos){
        // chamando a funcao quebra para cada posicao do vetor ordem sendo a inicial
        for(int i=0; i < keySz; i++){
            quebra(ordem, ciphertext, keySz);
            //cyclic shifted do vetor ordem
            rotate(ordem.begin(), ordem.begin() + 1, ordem.end());
        }
    }
}

// precalcula a probabilidade de cada trio de colunas
vector<vector<vector<double>>> precalc_trigrafos_prob(int keySz, int columnSz, vector<vector<int>>& ciphermatriz){
    vector<vector<vector<double>>> trio_probabilidade(keySz, vector<vector<double>>(keySz, vector<double>(keySz, 0)));
    // complexidade O(keySz^3*columnSz) == O(|cipherText|*keySz^2) 
    for(int i=0; i < keySz; i++){
        for(int j=0; j < keySz; j++){
            if(i == j) continue;
            for(int k=0; k < keySz; k++){
                if(k == i || k == j) continue;
                for(int z=0; z < columnSz; z++){
                    trio_probabilidade[i][j][k] += trigrafos[ciphermatriz[z][i]][ciphermatriz[z][j]][ciphermatriz[z][k]];
                }
            }
        }
    }
    return trio_probabilidade;
}

// precalcula a probabilidade de cada dupla de colunas
vector<vector<double>> precalc_digrafos_prob(int keySz, int columnSz, vector<vector<int>>& ciphermatriz){
    vector<vector<double>> dupla_probabilidade(keySz, vector<double>(keySz, 0));
    //complexidade O(keySz^2*columnSz) == O(|cipherText|*keySz) 
    for(int i=0; i < keySz; i++){
        for(int j=0; j < keySz; j++){
            if(i == j) continue;
            for(int k=0; k < columnSz; k++){
                dupla_probabilidade[i][j] += digrafos[ciphermatriz[k][i]][ciphermatriz[k][j]];
            }
        }
    }
    return dupla_probabilidade;
}

// monta a matriz de transposição do ciphertext
vector<vector<int>> matriz_transposicao(int keySz, string ciphertext){
    int columnSz = (int)ciphertext.size()/keySz;
    vector<vector<int>> ciphermatriz(columnSz, vector<int>(keySz));
    //complexidade O(cipherText.size())
    for(int i=0; i < keySz; i++){
        for(int j=0; j < columnSz; j++){
            ciphermatriz[j][i] = ciphertext[i*columnSz+j]-'a';
        }
    }
    return ciphermatriz;
}



int main(){
    inicializar_trigrafos();
    
    string ciphertext;
    cout << "Digite a mensagem a ser descriptografada : \n";
    cin >> ciphertext;

    // chave de tamanho fixo igual ao teto da raiz do tamanho do texto
    int keySz = 1;
    for(int i=(int)ciphertext.size(); keySz*keySz < i; keySz++);

    // montando a matriz de transposicao da chave cifrada
    int columnSz = (int)ciphertext.size()/keySz;
    vector<vector<int>> ciphermatriz = matriz_transposicao(keySz, ciphertext);

    // precalculando a probabilidade de cada dupla de colunas
    vector<vector<double>> dupla_probabilidade = precalc_digrafos_prob(keySz, columnSz, ciphermatriz);

    // precalculando a probabilidade de cada trio de colunas
    vector<vector<vector<double>>> trio_probabilidade = precalc_trigrafos_prob(keySz, columnSz, ciphermatriz);
    
    // funcao para imprimir todos os cyclic shifts possíveis das 10 combinações mais provaveis
    quebraFreq(keySz, ciphertext, dupla_probabilidade, trio_probabilidade);

    return 0;
}

//zuosvxi
//daomcjaurucymmviooleeqsrupevmgnrlaefoozaoa
//olamundoeumprazerveloaquivamoscomecaryogfj

//kqolmpnecr
//vsesvasdyleselmomvdrrfarcsseltiroppinuieeblroooatoexussoacarmmfvcvnsleesesiirpoeaecepeseeh
//desenvolversolucoescriativaseeficientespararesolverproblemascomplexosesempreumdesafiossvyh

//qdoziuajgzrhn
//eirtmlraofvsyoadafeosonblotearnaooecsetdevueecsooejwfoasrirosrtdznnioepsdtoodoerimsnoemssaqefodennimtjtsasadasceaaoudrpiaaauapnrejrsceaaavmoiobniserctneeeaoastntrlrmoess
//aoenfrentardesafiosinesperadosacriatividadesetornaumaferramentaessencialparaencontrarsolucoesinovadoraseaomesmotempomanterofoconosobjetivoseresultadosdesejadosozbyotsjwq