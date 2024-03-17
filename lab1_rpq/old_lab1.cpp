#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

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


class Solution{
    Solution(string name){

    }



};

struct Task{
    int indeks;
    int R;
    int P;
    int Q;


};


int main(){

    // fstream plik;
    // plik.open("dane1.txt");

    vector<Task> tasks;
    string fname = "/Users/zet/Studia/KZW/lab1_264193_264238/24_dane1.txt";
    fstream file (fname, ios::in);
    int maxLines = 24;

    if(file.is_open())
    {
        int i=0;
        string line, word;

        while(getline(file, line) and i < maxLines) 
        {
            vector<string> row;
            stringstream str(line);
            string n;
            while(getline(str, word, ' ')) {
                row.push_back(word);
                
            }
            Task temp;
            temp.indeks = i+1;
            if (row.at(1) != " ")
            {
                cout << row.at(0);
            }
            
            temp.R = stoi(row.at(0));
            temp.P = stoi(row.at(1));
            temp.Q = stoi(row.at(2));
            tasks.push_back(temp);
            i++;
        }
    
    }
    else {
        cout << "Could not open the file\n";
    }

    for (int i = 0; i < maxLines; i++) {
        cout << tasks.at(i).indeks << " " << tasks.at(i).R << " " << tasks.at(i).P << " " << tasks.at(i).Q << endl;
    }  


     cout << "----------\nSortR\n----------\n";
    sort(tasks.begin(), tasks.end(), [](Task a, Task b) {
        return a.R < b.R;
    });
    for (int i = 0; i < maxLines; i++) {
        cout << tasks.at(i).indeks << " "; // << " " << tasks.at(i).czas_dostarczenia << " " << tasks.at(i).czas_trwania << " " << tasks.at(i).czas_stygniecia << endl;
    }  
    cout << "----------\nSortRQ\n----------\n";
    sort(tasks.begin(), tasks.end(), [](Task a, Task b) {
        if (a.R == b.R) {
            return a.Q < b.Q;
        }
        return a.R < b.R;
    });
    for (int i = 0; i < maxLines; i++) {
        cout << tasks.at(i).indeks << " "; // << " " << tasks.at(i).czas_dostarczenia << " " << tasks.at(i).czas_trwania << " " << tasks.at(i).czas_stygniecia << endl;
    }  
   



    return 0;
}