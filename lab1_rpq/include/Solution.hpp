#include <string>
#include <vector>
using namespace std;

class Task {
public:
  Task(int id, int r, int p, int q);
  Task();
  Task(const Task &other);

  int id;
  int R; // czas przygotowania
  int P; // czas wykonywania
  int Q; // czas dostareczenia
};
class Problem {
public:
  vector<Task> tasks;
  vector<int> solution;

  Problem();
  Problem(const vector<Task> &tasks, const vector<int> &sol);
  Problem(const vector<Task> &tasks);
  void loadData(std::string name);
  void printData();
  void printSolution();
  int calculateCMax();
  void printCMax();
  virtual void solve();
  int new_calculateCMax();
};

class SortR : public Problem {
public:
  void solve() override;
};

class Schrage : public Problem {
public:
  Schrage();
  Schrage(const vector<Task> &tasks);

  void solve() override;
  vector<Task> sortedList;

private:
  int t{0};
  int Cmax{0};
  Task e;
  vector<Task> readyQueue;
  int minR();
  void addToReadyQueue();
  void addToSortedList();
};

class TabuSearch : public Problem {
public:
  TabuSearch(int maxIter, int tabu_list_size, int current_data);

  vector<int> search();
  int evaluateSolution(const vector<int> &sol);
  std::vector<std::vector<int>> get_neighbors(const std::vector<int> &solution);

private:
  int maxIterations;
  vector<vector<int>> tabuList;
  vector<int> bestSolution;
  int bestCost;
  int tabuListSize;
  vector<int> generateRandomSolution(int n);
  vector<int> generateRandomSolution2();
  int currentData;
};