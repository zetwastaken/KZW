#include <string>
#include <vector>
using namespace std;

class Task {
public:
  Task(int id, int r, int p, int q);

  int id;
  int R; // czas przygotowania
  int P; // czas wykonywania
  int Q; // czas dostareczenia
};
class Solution {
public:
  vector<Task> tasks;

  void loadData(string name);
  void printData();
  int calculateCMax();
  void printCMax();
  void sortR();
  void sortRQ();
};

class AllSolutions : Solution {
public:
  vector<string> daneXtxt;
  AllSolutions(string folderPath, int n);

  void solveAll(int method);
};