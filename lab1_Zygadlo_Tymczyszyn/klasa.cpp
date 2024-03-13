#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
enum metoda{Brak,   SortR,  SortRQ, Schrage,   Potts,    C100, Carlie, InMiddleLongestR};

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


class rozwiazanie{
    public:
    struct dane{
    int indeks;
    int R;
    int P;
    int Q;
    };
    vector<dane> tablica;
    
    void loadData(string name){
    fstream file (name, ios::in);
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
            dane temp;
            if (row.size() == 1)
            {
                //cout << row.at(0) << endl;
                maxLines = stoi(row.at(0))+1;
            }
            else{
            temp.indeks = i;
            temp.R = stoi(row.at(0));
            temp.P = stoi(row.at(1));
            temp.Q = stoi(row.at(2));
            tablica.push_back(temp);
            }
            i++;
        }
    
    }
    else {
        cout << "Could not open the file\n";
    }
    }

    void printData(){
    for (int i = 0; i < tablica.size(); i++) {
        cout << tablica.at(i).indeks << " ";
    } 
    }

    /*
    ###########################
    ## Funkcje do sortowania ##
    ###########################
    */


   
    void sortR(){
        sort(tablica.begin(), tablica.end(), [](dane a, dane b) {
        return a.R < b.R;
    });
    }


    //NIE DZIAŁ
    void sortRQ(){
        sort(tablica.begin(), tablica.end(), [](dane a, dane b){
         if (a.R < b.R) return true;
         if (a.R == b.R) return a.Q < b.Q;
        return false;
        });
    }
    // NOPE nie warto


    void inMiddleLongestR(){
        vector <dane> temp1 = tablica;
        vector <dane> temp2;
        temp2.resize(tablica.size());
        sort(temp1.begin(), temp1.end(), [](dane a, dane b) {
        return a.R < b.R;
         });

        int i = 1;
        int middle = tablica.size()/2;
        temp2.at(middle) = temp1.at(0);
        temp1.erase(temp1.begin());

        while (temp1.size() > 0)
        {
        if (middle+i < tablica.size())
        {
        temp2.at(middle+i) = temp1.at(0);
        temp1.erase(temp1.begin());
        //cout <<"I: " << i << " size+i: " << middle+i  << endl;
        }    
        temp2.at(middle-i) = temp1.at(0);
        temp1.erase(temp1.begin());
        //cout <<"I: " << i << " size-i: " << middle-i  << endl;
        i++;
        }

    


        //sort(temp2.begin(), temp2.end(), [](dane a, dane b) { return a.indeks < b.indeks; });

        // for (size_t i = 0; i < temp2.size(); i++)
        // {
        //     cout << temp2.at(i).indeks << " " << temp2.at(i).R << endl;
        // }
        
        tablica = temp2;
        
    }

};

class wszystkieRozwiazania:rozwiazanie{
    public:
    vector <string> daneXtxt;
    wszystkieRozwiazania(string folderPath, int n){
        for (size_t i = 0; i < n; i++)
        {
            string temp = folderPath+"dane"+to_string(i+1)+".txt";
            daneXtxt.push_back(temp);
        }
    }
    void rozwiazWszystkie(int metoda){
        for (size_t i = 0; i < daneXtxt.size(); i++)
        {
            rozwiazanie wyniki;
            wyniki.loadData(daneXtxt.at(i));
            switch (metoda)
            {
            case Brak:

            break;
            case SortR:
                wyniki.sortR();

            break;
            case SortRQ:
                wyniki.sortRQ();

            break;
            case InMiddleLongestR:
                wyniki.inMiddleLongestR();

            break;
            default:
                break;
            }
            cout << "\n\n----------------\n";
            cout << "dane"+to_string(i+1)+".txt" << endl;;
            wyniki.printData();
            cout << "\n----------------";

        }
    }
};