#include "../include/Solution.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
enum metoda { None, SortR, SortRQ, Schrage, Potts, C100, Carlie };

Task::Task(int id, int r, int p, int q) : id(id), R(r), P(p), Q(q) {}

void Solution::loadData(string name) {
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

void Solution::sortR() {
  sort(tasks.begin(), tasks.end(),
       [](const Task &a, const Task &b) { return a.R < b.R; });
}

void Solution::sortRQ() { // temu wychodzą czasy jak zwykłemu sortR :((
  sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
    if (a.R == b.R) {
      return a.Q < b.Q;
    }
    return a.R < b.R;
  });
}

AllSolutions::AllSolutions(string folderPath, int n) {
  for (size_t i = 0; i < n; i++) {
    string temp = folderPath + "/data/dane" + to_string(i + 1) + ".txt";
    daneXtxt.push_back(temp);
  }
}

void AllSolutions::solveAll(int metoda) {
  for (size_t i = 0; i < daneXtxt.size(); i++) {
    Solution wyniki;
    wyniki.loadData(daneXtxt.at(i));
    switch (metoda) {
    case None:

      break;
    case SortR:
      wyniki.sortR();
      break;
    case SortRQ:
      wyniki.sortRQ();
      break;
    default:
      break;
    }

    cout << "\ndane" + to_string(i + 1) + ".txt" << endl;
    wyniki.printData();
    cout << "\n----------------\n";
    wyniki.printCMax();
  }
}
