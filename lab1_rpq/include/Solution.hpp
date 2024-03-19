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

  void loadData(std::string name);
  void printData();
  int calculateCMax();
  void printCMax();
  virtual void solve();
};

class SortR : public Solution{
  public:
  void solve() override;
};

class Schrage : public Solution{
  public:
  void solve() override;
  private:
};