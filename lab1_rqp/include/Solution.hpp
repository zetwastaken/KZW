#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct dane {
  int indeks;
  int R;
  int P;
  int Q;
};
class rozwiazanie {
public:
  vector<dane> tablica;

  void loadData(string name);
  void printData();
  void sortR();
};

class wszystkieRozwiazania : rozwiazanie {
public:
  vector<string> daneXtxt;
  wszystkieRozwiazania(string folderPath, int n);

  void rozwiazWszystkie(int metoda);
};