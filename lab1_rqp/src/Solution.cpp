#include "../include/Solution.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
enum metoda { Brak, SortR, SortRQ, Schrage, Potts, C100, Carlie };

void rozwiazanie::loadData(string name) {
  fstream file(name, ios::in);
  int maxLines = 24;

  if (file.is_open()) {
    int i = 0;
    string line, word;

    while (getline(file, line) and i < maxLines) {
      vector<string> row;
      stringstream str(line);
      string n;
      while (getline(str, word, ' ')) {
        row.push_back(word);
      }
      dane temp;
      if (row.size() == 1) {
        // cout << row.at(0) << endl;
        maxLines = stoi(row.at(0)) + 1;
      } else {
        temp.indeks = i;
        temp.R = stoi(row.at(0));
        temp.P = stoi(row.at(1));
        temp.Q = stoi(row.at(2));
        tablica.push_back(temp);
      }
      i++;
    }

  } else {
    cout << "Could not open the file\n";
  }
}

void rozwiazanie::printData() {
  for (int i = 0; i < tablica.size(); i++)
    cout << tablica.at(i).indeks << " ";
}

void rozwiazanie::sortR() {
  sort(tablica.begin(), tablica.end(),
       [](dane a, dane b) { return a.R < b.R; });
}

wszystkieRozwiazania::wszystkieRozwiazania(string folderPath, int n) {
  for (size_t i = 0; i < n; i++) {
    string temp = folderPath + "/data/dane" + to_string(i + 1) + ".txt";
    daneXtxt.push_back(temp);
  }
}
void wszystkieRozwiazania::rozwiazWszystkie(int metoda) {
  for (size_t i = 0; i < daneXtxt.size(); i++) {
    rozwiazanie wyniki;
    wyniki.loadData(daneXtxt.at(i));
    switch (metoda) {
    case Brak:

      break;
    case SortR:
      wyniki.sortR();

      break;
    case SortRQ:

      break;
    default:
      break;
    }

    cout << "\ndane" + to_string(i + 1) + ".txt" << endl;
    wyniki.printData();
    cout << "\n----------------";
  }
}
