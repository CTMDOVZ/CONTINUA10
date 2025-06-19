#pragma once
#include <string>
#include <vector>
#include <unordered_map>

std::vector<int> buscarInocente(const std::string& texto, const std::string& patron) {
    std::vector<int> ocurrencias;
    size_t n = texto.size();
    size_t m = patron.size();

    for (size_t i = 0; i + m <= n; ++i) {
        size_t j = 0;
        while (j < m && texto[i + j] == patron[j]) ++j;
        if (j == m) ocurrencias.push_back(i);
    }
    return ocurrencias;
}

std::vector<int> buscarBoyerMoore(const std::string& texto, const std::string& patron) {
    std::vector<int> ocurrencias;
    int n = texto.size();
    int m = patron.size();
    if (m == 0) return ocurrencias;

    std::unordered_map<char, int> badChar;
    for (int i = 0; i < m; ++i) {
        badChar[patron[i]] = i;
    }

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && patron[j] == texto[s + j]) --j;
        if (j < 0) {
            ocurrencias.push_back(s);
            s += (s + m < n) ? m - badChar[texto[s + m]] : 1;
        } else {
            s += std::max(1, j - badChar[texto[s + j]]);
        }
    }
    return ocurrencias;
}

std::vector<int> buscarSuffixTree(const std::string& texto, const std::string& patron) {
    std::vector<int> ocurrencias;
    size_t pos = texto.find(patron);
    while (pos != std::string::npos) {
        ocurrencias.push_back(pos);
        pos = texto.find(patron, pos + 1);
    }
    return ocurrencias;
}
