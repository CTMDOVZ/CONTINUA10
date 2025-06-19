#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "smatching.h"

using namespace std;

const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789   ";

string generarTexto(size_t N) { 
    string resultado;
    resultado.reserve(N);
    for (size_t i = 0; i < N; ++i)
        resultado += alfabeto[rand() % alfabeto.size()];
    return resultado;
}

void medirTiempos(size_t N, const string& patron, ofstream& salidaCSV) {
    string texto = generarTexto(N);

    cout << "N = " << N << endl;

    auto start = chrono::high_resolution_clock::now();
    buscarInocente(texto, patron);
    auto end = chrono::high_resolution_clock::now();
    auto t_inocente = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Inocente: " << t_inocente << " ms" << endl;

    start = chrono::high_resolution_clock::now();
    buscarBoyerMoore(texto, patron);
    end = chrono::high_resolution_clock::now();
    auto t_bm = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Boyer-Moore: " << t_bm << " ms" << endl;

    start = chrono::high_resolution_clock::now();
    buscarSuffixTree(texto, patron);
    end = chrono::high_resolution_clock::now();
    auto t_st = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Suffix Tree: " << t_st << " ms" << endl << endl;

    salidaCSV << N << "," << t_inocente << "," << t_bm << "," << t_st << "\n";
}

int main() {
    srand(time(0));
    string patron = "abc";

    ofstream salida("resultados.csv");
    salida << "N,Inocente,BoyerMoore,SuffixTree\n";

    vector<size_t> tamanos = {10, 100, 1000, 10000, 100000, 1000000, 10000000};

    for (size_t N : tamanos) {
        medirTiempos(N, patron, salida);
    }

    salida.close();
    cout << "Resultados guardados en resultados.csv\n";
    return 0;
}
