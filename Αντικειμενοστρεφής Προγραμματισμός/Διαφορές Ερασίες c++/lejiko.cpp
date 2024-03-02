#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

class limma
{
private:
    string oros;
    string simasia;
public:
    limma()
    {
        oros="N/A";
        simasia="N/A";
    }
    limma(string _sim,string _oros)
    {
        oros=_oros;
        simasia=_sim;
    }
    string get_oros()const
    {return oros;}
    string get_sim()const
    {return simasia;}
    void set_oros(const string _oros)
    {oros=_oros;}
    void set_simasia(const string _sim)
    {simasia=_sim;}
    void show_dat()
    {
        cout<<"oros: "<<oros<<endl;
        cout<<"simasia: "<<simasia<<endl;
    }
};

class lejiko
{
private:
    list<limma *> LEXIKO;
public:
    void Add_lej(limma * L)
    {
       LEXIKO.push_back(L);
    }
    void erase_lex(int pos)
    {
        list<limma *>::iterator ob;
        ob=LEXIKO.begin();
        advance(ob,pos);
        LEXIKO.erase(ob);
    }
    void show_lejeis()
    {
        cout << "LEXEIS "<<LEXIKO.size()<<"STO LEJIKO: "<<endl;
        list<limma *>::iterator it;
        for(it=LEXIKO.begin(); it!=LEXIKO.end(); it++)
            cout<<"Oros: "<<(*it)->get_oros()<<", Simasia: "<<(*it)->get_sim()<<endl;
    }
    bool find_lex(limma * L)
    {
        list<limma *>::iterator it;
        for(it=LEXIKO.begin(); it!=LEXIKO.end(); it++)
        {
            if(*it==L)
                return true;
        }
        return false;
    }
    void write_files()
    {
        ofstream outfile;
        outfile.open("LEXIKO.txt",ios::binary|ios::app);
        outfile.write(reinterpret_cast<char *>(this),sizeof(*this));
        outfile.close();
    }
    /*void read_file()
    {
        ifstream infile;
        infile.open("LEXIKO.txt",ios::binary);
        if(!infile)
        {
            cout<<"La8os sto anogma arxeiou"<<endl;
            return;
        }
        while(!infile.eof())
        {
            if(infile.read(reinterpret_cast<char *>(this),sizeof(*this)))
            {
                show_lejeis();
            }
        }
    }*/
};


int main()
{
    lejiko pin;
    limma *ob1=new limma("gabgizei","skilos");
    limma *ob2=new limma("niaourizei","gata");
    limma *ob3=new limma("mouggizei","aggelada");

    pin.Add_lej(ob1);
    pin.Add_lej(ob2);
    pin.Add_lej(ob3);

    pin.show_lejeis();

    pin.erase_lex(0);

    cout<<endl<<endl;
    pin.show_lejeis();
    string oros,siamsia;
    cout<<"psace mia leji: ";
    limma *temp=new limma();
    cout<<"Dwse oro-> ";
    cin>>oros;
    cout<<"Dwse simasia-> ";
    cin>>siamsia;
    temp->set_oros(oros);
    temp->set_simasia(siamsia);
    if(pin.find_lex(temp))
        cout<<"brethike"<<endl;
    else
        cout<<"Den brethike"<<endl;


   pin.write_files();
   //pin.read_file();


    return 0;
}
