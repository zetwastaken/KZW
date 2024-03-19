#include "../include/Solution.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
enum metoda { sortR, sortRQ, schrage, potts, C100, carlie };

Task::Task(int id, int r, int p, int q) : id(id), R(r), P(p), Q(q) {}

void Solution::loadData(std::string name) {
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
      if (row.size() == 1) {
        // cout << row.at(0) << endl;
        maxLines = stoi(row.at(0)) + 1;
      } else {
        tasks.push_back(
            Task(i, stoi(row.at(0)), stoi(row.at(1)), stoi(row.at(2))));
      }
      i++;
    }

  } else {
    cout << "Could not open the file\n";
  }
}

void Solution::printData() {
  for (int i = 0; i < tasks.size(); i++)
    cout << tasks.at(i).id << " ";
}

int Solution::calculateCMax() {
  int currentTime = 0;
  int Cmax = 0;
  for (const Task &task : tasks) {
    currentTime = max(currentTime, task.R) + task.P;
    Cmax = max(Cmax, currentTime + task.Q);
  }
  return Cmax;
}

void Solution::printCMax() { cout << "CMax = " << calculateCMax() << endl; }

void Solution::solve() {}

void SortR::solve() {
  sort(tasks.begin(), tasks.end(),
       [](const Task &a, const Task &b) { return a.R < b.R; });
}

void Schrage::solve() {
}
