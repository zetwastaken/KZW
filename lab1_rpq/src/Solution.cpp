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

Problem::Problem(const vector<Task> &newTasks) : tasks{newTasks} {}

Problem::Problem(const vector<Task> &newTasks, const vector<int> &sol)
    : tasks{newTasks}, solution{sol} {}

void Problem::loadData(std::string name) {
  fstream file(name, ios::in);
  int maxLines = 24;

  if (file.is_open()) {
    int i = 0;
    string line, word;

    while (getline(file, line) and i < maxLines) {
      vector<string> row;
      stringstream str(line);
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
  } else {
    std::cout << "Could not open the file\n";
  }
}

void Problem::printData() {
  for (int i = 0; i < tasks.size(); i++) std::cout << tasks.at(i).id << " ";
}

void Problem::printSolution() {
  for (int i = 0; i < tasks.size(); i++) std::cout << solution.at(i) + 1 << " ";
}

int Problem::calculateCMax() {
  int currentTime = 0;
  int Cmax = 0;
  for (const Task &task : tasks) {
    currentTime = max(currentTime, task.R) + task.P;
    Cmax = max(Cmax, currentTime + task.Q);
  }
  return Cmax;
}

void Problem::printCMax() { std::cout << "CMax = " << calculateCMax() << endl; }

void Problem::solve() {}

void SortR::solve() {
  sort(tasks.begin(), tasks.end(),
       [](const Task &a, const Task &b) { return a.R < b.R; });
}
// ! SCHRAGE ///////////////////////////////////////////////////////////////////

Schrage::Schrage() {}
Schrage::Schrage(const vector<Task> &tasks) : Problem(tasks) {}

int Schrage::minR() {
  return (*std::min_element(tasks.begin(), tasks.end(),
                            [](const Task &i, const Task &j) {
                              return (i.R != j.R) ? (i.R < j.R) : (i.P < j.P);
                            }))
      .R;
}

void Schrage::addToReadyQueue() {
  auto min_element_r = std::min_element(
      tasks.begin(), tasks.end(), [](const Task &i, const Task &j) {
        return (i.R != j.R) ? (i.R < j.R) : (i.P < j.P);
      });

  if (min_element_r != tasks.end()) {
    e = *min_element_r;
    readyQueue.push_back(e);
    tasks.erase(min_element_r);
  }
}

void Schrage::addToSortedList() {
  auto max_element_q = std::max_element(
      readyQueue.begin(), readyQueue.end(), [](const Task &i, const Task &j) {
        return (i.Q != j.Q) ? (i.Q < j.Q) : (i.P > j.P);
      });

  if (max_element_q != readyQueue.end()) {
    e = *max_element_q;
    readyQueue.erase(max_element_q);
    sortedList.push_back(e);
    solution.push_back((*max_element_q).id);
  }
}

void Schrage::solve() {
  while (not readyQueue.empty() or not tasks.empty()) {
    while (not tasks.empty() and minR() <= t) addToReadyQueue();
	
    if (readyQueue.empty()) {
      t = minR();
      continue;
    }
    addToSortedList();
    t += e.P;
    // Cmax = max(Cmax, t + e.Q);
  }
}

int Problem::new_calculateCMax() {
  int n = tasks.size();
  int currentTime = 0;
  int Cmax = 0;

  for (int i = 0; i < n; ++i) {
    int taskId = solution[i];
    currentTime = max(currentTime, tasks[taskId].R) + tasks[taskId].P;
    Cmax = max(Cmax, currentTime + tasks[taskId].Q);
  }

  return Cmax;
}

TabuSearch::TabuSearch(int max_iterations, int tabu_list_size, int current_data)
    : maxIterations(max_iterations),
      tabuListSize(tabu_list_size),
      currentData(current_data),
      bestCost(numeric_limits<int>::max()) {}

int TabuSearch::evaluateSolution(const vector<int> &sol) {
  int n = tasks.size();
  int currentTime = 0;
  int Cmax = 0;

  for (int i = 0; i < n; ++i) {
    int taskId = sol[i];
    currentTime = max(currentTime, tasks[taskId].R) + tasks[taskId].P;
    Cmax = max(Cmax, currentTime + tasks[taskId].Q);
  }

  return Cmax;
};

std::vector<std::vector<int>> TabuSearch::get_neighbors(
    const std::vector<int> &solution) {  // Added const qualifier
  std::vector<std::vector<int>> neighbors;
  for (size_t i = 0; i < solution.size(); i++) {
    for (size_t j = i + 1; j < solution.size(); j++) {
      std::vector<int> neighbor = solution;
      std::swap(neighbor[i], neighbor[j]);
      neighbors.push_back(neighbor);
    }
  }
  return neighbors;
}

vector<int> TabuSearch::search() {
  Problem currentSolution(tasks);
  if (currentData != 3)
    currentSolution.solution = generateRandomSolution(tasks.size());
  else
    currentSolution.solution = generateRandomSolution2();
  bestSolution = currentSolution.solution;
  bestCost = currentSolution.new_calculateCMax();

  for (int iter = 0; iter < maxIterations; iter++) {
    std::vector<std::vector<int>> neighbors =
        get_neighbors(currentSolution.solution);
    std::vector<int> best_neighbor;  // w każdej iteracji od nowa
    int bestNeighborCost = std::numeric_limits<int>::max();

    for (const auto &neighbor : neighbors) {
      if (std::none_of(
              tabuList.begin(), tabuList.end(),
              [&](const auto &element) { return element == neighbor; })) {
        int neighborCost = evaluateSolution(neighbor);
        if (neighborCost < bestNeighborCost) {
          best_neighbor = neighbor;
          bestNeighborCost = neighborCost;
        }
      }
    }

    currentSolution.solution = best_neighbor;
    tabuList.push_back(best_neighbor);

    if (tabuList.size() > tabuListSize) tabuList.erase(tabuList.begin());

    if (evaluateSolution(best_neighbor) < evaluateSolution(bestSolution))
      bestSolution = best_neighbor;  // current neighbor is better
  }
  solution = bestSolution;
  std::cout << "data" << currentData << ".txt cmax = " << new_calculateCMax()
            << endl;

  return bestSolution;
}

vector<int> TabuSearch::generateRandomSolution(int n) {
  vector<int> solution(n);
  for (int i = 0; i < n; ++i) solution[i] = i;

  random_shuffle(solution.begin(), solution.end());

  return solution;
}

vector<int> TabuSearch::generateRandomSolution2() {
  Schrage initialSolution(tasks);
  initialSolution.solve();
  vector<int> solution;
  std::transform(initialSolution.sortedList.begin(),
                 initialSolution.sortedList.end(), std::back_inserter(solution),
                 [](const Task &task) { return task.id - 1; });
  // cout << " TO JEST WEJŚĆIE DO TABU" << endl;
  // for(auto& sol : solution){
  //   cout << sol << " ";
  // }
  // cout << endl;
  // cout << endl;
  return solution;
}
