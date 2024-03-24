#include "../include/Solution.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
using namespace std;
enum metoda { sortR, schrage, tabuSearch };

Task::Task() {}

Task::Task(int id, int r, int p, int q) : id(id), R(r), P(p), Q(q) {}

Task::Task(const Task &other)
    : id(other.id), R(other.R), P(other.P), Q(other.Q) {}

Problem::Problem() {}

Problem::Problem(const vector<Task> &newTasks)
    : tasks{newTasks}, initiallyOrderedTasks{newTasks} {}

Problem::Problem(const vector<Task> &newTasks, const vector<int> &sol)
    : tasks{newTasks}, solution{sol}, initiallyOrderedTasks{newTasks} {}

void Problem::loadData(string name) {
  fstream file(name, ios::in);
  int maxLines{24};

  if (file.is_open()) {
    int i{0};
    string line, word;

    while (getline(file, line) and i < maxLines) {
      vector<string> row;
      stringstream str{line};
      while (getline(str, word, ' ')) {
        row.push_back(word);
      }
      if (row.size() == 1) {
        maxLines = stoi(row.at(0)) + 1;
      } else {
        tasks.push_back(
            Task(i, stoi(row.at(0)), stoi(row.at(1)), stoi(row.at(2))));
      }
      i++;
    }
    initiallyOrderedTasks = tasks;
  } else {
    cout << "Could not open the file" << endl;
  }
}

void Problem::printSolution() {
  cout << "Solution: " << endl;
  for (const auto &sol : solution) cout << sol << " ";
  cout << endl;
}

int Problem::getCMax() {
  int currentTime{0};
  int Cmax{0};

  for (const auto &sol : solution) {
    int taskId{sol - 1};
    currentTime = std::max(currentTime, initiallyOrderedTasks[taskId].R) +
                  initiallyOrderedTasks[taskId].P;
    Cmax = std::max(Cmax, currentTime + initiallyOrderedTasks[taskId].Q);
  }
  return Cmax;
}

void Problem::solve() {}

void SortR::solve() {
  std::sort(tasks.begin(), tasks.end(),
            [&](const Task &a, const Task &b) { return a.R < b.R; });

  std::transform(tasks.begin(), tasks.end(), std::back_inserter(solution),
                 [&](const Task &task) { return task.id; });
}

Schrage::Schrage() {}
Schrage::Schrage(const vector<Task> &tasks) : Problem(tasks) {}

int Schrage::minR() {
  return (*std::min_element(tasks.begin(), tasks.end(),
                            [&](const Task &i, const Task &j) {
                              return (i.R != j.R) ? (i.R < j.R) : (i.P < j.P);
                            }))
      .R;
}

void Schrage::addTaskToReadyQueue() {
  auto min_element_r = std::min_element(
      tasks.begin(), tasks.end(), [&](const Task &i, const Task &j) {
        return (i.R != j.R) ? (i.R < j.R) : (i.P < j.P);
      });

  if (min_element_r != tasks.end()) {
    e = *min_element_r;
    readyQueue.push_back(e);
    tasks.erase(min_element_r);
  }
}

void Schrage::addTaskToSolution() {
  auto max_element_q = std::max_element(
      readyQueue.begin(), readyQueue.end(), [&](const Task &i, const Task &j) {
        return (i.Q != j.Q) ? (i.Q < j.Q) : (i.P < j.P);
      });

  if (max_element_q != readyQueue.end()) {
    e = *max_element_q;
    readyQueue.erase(max_element_q);
    solution.push_back(e.id);
  }
}

void Schrage::solve() {
  int t{0};
  while (not readyQueue.empty() or not tasks.empty()) {
    while (not tasks.empty() and minR() <= t) addTaskToReadyQueue();

    if (readyQueue.empty()) {
      t = minR();
      continue;
    }
    addTaskToSolution();
    t += e.P;
  }
}

TabuSearch::TabuSearch(int max_iterations, int tabu_list_size, int current_data)
    : maxIterations(max_iterations),
      tabuListSize(tabu_list_size),
      currentData(current_data),
      bestCost(std::numeric_limits<int>::max()) {}

int TabuSearch::evaluateSolution(const vector<int> &newSolution) {
  int currentTime{0};
  int Cmax{0};

  for (const auto &sol : newSolution) {
    int taskId{sol - 1};
    currentTime = std::max(currentTime, initiallyOrderedTasks[taskId].R) +
                  initiallyOrderedTasks[taskId].P;
    Cmax = std::max(Cmax, currentTime + initiallyOrderedTasks[taskId].Q);
  }
  return Cmax;
};

vector<vector<int>> TabuSearch::generateSolutions(const vector<int> &sol) {
  vector<vector<int>> solutions;

  for (size_t i{0}; i < sol.size(); ++i) {
    for (size_t j{i + 1}; j < sol.size(); ++j) {
      vector<int> modifiedSolution = sol;
      std::swap(modifiedSolution[i], modifiedSolution[j]);
      solutions.push_back(modifiedSolution);
    }
  }
  return solutions;
}

void TabuSearch::generateInitialSolution(Problem &currentSolution) {
  if (currentData != 3)
    currentSolution.solution = generateRandomInitialSolution();
  else
    currentSolution.solution = generateSchrageAsInitialSolution();
}

void TabuSearch::compareWithBestSolution(const vector<int> &currentBestSolution,
                                         int currentBestSolutionCost) {
  if (currentBestSolutionCost < bestCost) {
    bestSolution = currentBestSolution;
    bestCost = currentBestSolutionCost;
  }
}
void TabuSearch::checkCurrentTabuListSize() {
  if (tabuList.size() > tabuListSize) tabuList.erase(tabuList.begin());
}

bool TabuSearch::solutionIsNotInTabuList(const vector<int> &solution) {
  return std::none_of(tabuList.begin(), tabuList.end(),
                      [&](const auto &element) { return element == solution; });
}

void TabuSearch::solve() {
  Problem currentSolution(this->tasks);
  generateInitialSolution(currentSolution);

  for (size_t i{0}; i < maxIterations; ++i) {
    vector<vector<int>> solutions{generateSolutions(currentSolution.solution)};
    vector<int> currentBestSolution;
    int currentBestSolutionCost{std::numeric_limits<int>::max()};

    for (const auto &solution : solutions) {
      if (solutionIsNotInTabuList(solution)) {
        int solutionCost{evaluateSolution(solution)};
        if (solutionCost < currentBestSolutionCost) {
          currentBestSolution = solution;
          currentBestSolutionCost = solutionCost;
        }
      }
    }
    currentSolution.solution = currentBestSolution;
    tabuList.push_back(currentBestSolution);

    checkCurrentTabuListSize();
    compareWithBestSolution(currentBestSolution, currentBestSolutionCost);
  }
  this->solution = bestSolution;
}

vector<int> TabuSearch::generateRandomInitialSolution() {
  vector<int> sol(initiallyOrderedTasks.size());
  for (size_t i{0}; i < sol.size(); ++i) sol[i] = i + 1;
  random_shuffle(sol.begin(), sol.end());
  return sol;
}

vector<int> TabuSearch::generateSchrageAsInitialSolution() {
  Schrage initialSolution(tasks);
  initialSolution.solve();
  vector<int> sol = initialSolution.solution;
  return sol;
}
