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



struct dane{
    int indeks;
    int R;
    int P;
    int Q;


};

void loadData( string fname, int maxLines){
    fstream file (fname, ios::in);
    int i=0;
    if(file.is_open())
    {
        string line, word;

        while(getline(file, line) and i < maxLines)
        {
            vector<string> row;
            stringstream str(line);

            while(getline(str, word, ',')) {
                row.push_back(word);
                cout << row.back();
            }
        }
    
    }
    else {
        cout << "Could not open the file\n";
    }
}


int main(){

    // fstream plik;
    // plik.open("dane1.txt");

    vector<dane> tablica;
    string fname = "/Users/zet/Studia/KZW/24_dane1.txt";
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

            while(getline(str, word, ' ')) {
                row.push_back(word);
                
            }
            dane temp;
            temp.indeks = i+1;
            temp.R = stoi(row.at(0));
            temp.P = stoi(row.at(1));
            temp.Q = stoi(row.at(2));
            tablica.push_back(temp);
            i++;
        }
    
    }
    else {
        cout << "Could not open the file\n";
    }

    for (int i = 0; i < maxLines; i++) {
        cout << tablica.at(i).indeks << " " << tablica.at(i).R << " " << tablica.at(i).P << " " << tablica.at(i).Q << endl;
    }  

    sort(tablica.begin(), tablica.end(), [](dane a, dane b) {
        return a.R < b.R;
    });

    cout << "----------\n";

    for (int i = 0; i < maxLines; i++) {
        cout << tablica.at(i).indeks << " "; // << " " << tablica.at(i).czas_dostarczenia << " " << tablica.at(i).czas_trwania << " " << tablica.at(i).czas_stygniecia << endl;
    }  


    return 0;
}