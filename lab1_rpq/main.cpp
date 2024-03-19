#include "src/Solution.cpp"
#include <filesystem>
#include <memory>

constexpr int NUMBER_OF_FILES = 4;

std::vector<std::string> loadDataFromFiles() {
  std::vector<std::string> allData;
  std::filesystem::path currentFile(__FILE__);
  std::filesystem::path currentFileDir = currentFile.parent_path();

  for (int i = 0; i < NUMBER_OF_FILES; i++) {
    string temp =
        currentFileDir.string() + "/data/dane" + to_string(i + 1) + ".txt";
    allData.push_back(temp);
  }
  return allData;
}

void process(std::unique_ptr<Solution> results, string data, int i) {
  results->loadData(data);
  results->solve();
  cout << "\ndane" + to_string(i + 1) + ".txt" << endl;
  results->printData();
  cout << "\n----------------\n";
  results->printCMax();
}

void solveSortR(string data, int i) {
  std::unique_ptr<Solution> results = std::make_unique<SortR>();
  process(std::move(results), data, i);
}

void solveSchrage(string data, int i) {
  std::unique_ptr<Solution> results = std::make_unique<Schrage>();
  process(std::move(results), data, i);
}

void SolveForAllData(int method) {
  std::vector<std::string> allData = loadDataFromFiles();
  for (size_t i = 0; i < NUMBER_OF_FILES; i++) {
    switch (method) {
    case sortR:
      solveSortR(allData.at(i), i);
      break;
    case schrage:
      solveSchrage(allData.at(i), i);
      break;
    default:
      break;
    }
  }
}

int main() {

  SolveForAllData(sortR);

  return 0;
}

/*
----------------------------------------------------------------
             123   SortR  SortRQ Schrage   Potts    C100 Carlier
data:1     25994   14239   13862   13981   13862   13862   13862
data:2     33465   33465   21176   21529   21480   20924   20917
data:3     57403   40042   33424   31683   31346   31465   31343
data:4     51444   39616   33878   34444   33901   33878   33878
----------------------------------------------------------------
suma:     168306  127362  102340  101637  100589  100129  100000


ocena        2.5     3.0     3.5     4.0     4.5     5.0     5.5
----------------------------------------------------------------
suma:     168306  127362  103378  100926  100381  100010  100000
*/
