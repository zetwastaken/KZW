#include <string>
#include <vector>
using namespace std;

class Task {
 public:
  Task(int id, int r, int p, int q);
  Task();
  Task(const Task &other);

  int id;
  int R;  // czas przygotowania
  int P;  // czas wykonywania
  int Q;  // czas dostareczenia
};
class Problem {
 public:
  Problem();
  Problem(const vector<Task> &tasks, const vector<int> &sol);
  Problem(const vector<Task> &tasks);

  void loadData(std::string name);
  void printSolution();
  int getCMax();
  virtual void solve();

  vector<Task> tasks;
  vector<Task> initiallyOrderedTasks;
  vector<int> solution;
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

 private:
  Task e;
  vector<Task> readyQueue;
  int minR();
  void addTaskToReadyQueue();
  void addTaskToSolution();
};

class TabuSearch : public Problem {
 public:
  TabuSearch(int max_iterations, int tabu_list_size, int current_data);

  void solve() override;

 private:
  int maxIterations;
  vector<vector<int>> tabuList;
  vector<int> bestSolution;
  int bestCost;
  int tabuListSize;
  int currentData;
  vector<int> generateRandomInitialSolution();
  vector<int> generateSchrageAsInitialSolution();
  void generateInitialSolution(Problem &currentSolution);
  int evaluateSolution(const vector<int> &sol);
  vector<vector<int>> generateSolutions(const vector<int> &sol);
  bool solutionIsNotInTabuList(const vector<int> &solution);
  void compareWithBestSolution(const vector<int> &currentBestSolution,
                               int currentBestSolutionCost);
  void checkCurrentTabuListSize();
};