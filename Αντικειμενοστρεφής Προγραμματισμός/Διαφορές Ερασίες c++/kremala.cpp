//
// Created by filipposp on 19/4/2022.
//
#include "iostream"
#include "string"


using namespace std;

#define MAX 7

int give_hidden(string &str);

int main()
{
    cout<<"  ΚΡΕΜΑΛΑ!! "<<endl;
    string hidden;
    string wrong,correct;

    int len=0;
    int tries=0;

    len=give_hidden(hidden);
    system("CLEAR");
    string word(len-1,'-');

    cout<<hidden<<endl;
    cout<<word;
    return 0;


}

int give_hidden(string &str)
{
    cout<<"Δώσε την κρήμενη λέξη -> ";
    getline(cin,str);
    return str.size();
}
