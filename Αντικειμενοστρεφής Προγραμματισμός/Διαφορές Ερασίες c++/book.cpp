//
// Created by filipposp on 20/4/2022.
//

#include "iostream"
#include "string"
#include "vector"

using namespace std;

class book
{
protected:
    string name;
    int pages;
    int year;
    string title;
public:
    book(string _name,int _pages,int _year,string _title)
    {
        name=move(_name);
        pages=_pages;
        year=_year;
        title=move(_title);
    }
    virtual void display()=0;
    virtual int PriceClac()=0;
    virtual ~book()
    { }
};

class Printedbook:public book
{
public:
    Printedbook(string _name,int _pages,int _year,string _title):book(move(_name),_pages,_year,move(_title))
    { }
    void display()override
    {
        cout<<"Name -> "<<name<<endl;
        cout<<"Pages -> "<<pages<<endl;
        cout<<"Year of publich -> "<<year<<endl;
        cout<<"Title of book -> "<<title;
        cout<<endl;
    }
    int PriceClac()
    {
        if(year<1990)
        {
            if(pages<300)
                return 20;
            else if(pages>=300 && pages<600)
                return 30;
            else
                return 40;
        }
        else
        {
            if(pages<300)
                return 10;
            else if(pages>=300 && pages<600)
                return 20;
            else
                return 30;
        }

    }
};

class Ebook:public book
{
private:
    string book_type;
public:
    Ebook(string _name,int _pages,int _year,string _title,string _book_type):book(move(_name),_pages,_year,move(_title))
    { book_type=move(_book_type);}
    void display()override
    {
        cout<<"Name -> "<<name<<endl;
        cout<<"Pages -> "<<pages<<endl;
        cout<<"Year of publich -> "<<year<<endl;
        cout<<"Title of book -> "<<title<<endl;
        cout<<"Book type -> "<<book_type<<endl;
        cout<<endl;
    }
    int PriceClac()override
    {
        if(book_type=="PDF")
        {
            if(pages<300)
                return 30;
            else if(pages>=300 && pages<600)
                return 40;
            else
                return 50;
        }
        else if(book_type=="MSWORD")
        {
            if(pages<300)
                return 10;
            else if(pages>=300 && pages<600)
                return 20;
            else
                return 30;
        }

    }
};


class booksale {
    string name;
    vector<Ebook> pin;
    vector<Printedbook> pin2;
    vector<book> pin3;
public:
    booksale(string _name):name(_name)
    { }
    void add_sale(const Ebook &ob) {
        pin.push_back(ob);
    }
    void add_sale(const Printedbook &ob)
    {
      pin2.push_back(ob);
    }
    void display()
    {
        cout<<"Name of LIBRARY : "<<name<<endl;
        cout<<"Book sold!"<<endl;
        cout<<"---EBOOKS------"<<endl;
        for(unsigned long int i=0; i<pin.size(); i++)
            pin[i].display();
        cout<<"---PRINTED BOOK----"<<endl;
        for(unsigned long int i=0; i<pin2.size(); i++)
            pin2[i].display();
    }
    int Gettotalcost_ebook()
    {
        int sum=0;
        for(auto & i : pin)
        {
            sum+=i.PriceClac();
        }
        return sum;
    }
    int Gettotalcost_printed()
    {
        int sum=0;
        for(auto & i : pin2)
        {
            sum+=i.PriceClac();
        }
        return sum;
    }
    int total_cost()
    {
        return Gettotalcost_ebook()+Gettotalcost_printed();
    }
    bool operator<(booksale &ob2)
    {
        if(total_cost()<ob2.total_cost())
            return true;
        else
            return false;
    }
    void profit()
    {
        if(Gettotalcost_printed()>Gettotalcost_ebook())
            cout<<"Μεγαλύτερο κέρδος είχαν τα PRINTED!"<<endl;
        else
            cout<<"Μεγαλυτερο κέρδος είχαν τα ΕBOOKS"<<endl;
    }
};

int type_book(const string &type);


int main()
{
    booksale b("TZIOLA");
    char ch;
    string type,etype;
    string name,title;
    int year,pages;
    while(1)
    {
        cout<<"Εκχωρησέ δεδομένα βιβλίων!"<<endl;
        cout<<"Όνομα -> ";
        cin>>name;
        cout<<"Τίτλος -> ";
        cin>>title;
        cout<<"Σέλιδες -> ";
        cin>>pages;
        cout<<"Χρονολογία -> ";
        cin>>year;
        do{
            cout<<"Δώσε τύπο βιβλιού: ";
            cin>>type;
        }while(!type_book(type));
        if(type=="ebook")
        {
            cout<<"PDF OR WORD :";
            cin>>etype;
            Ebook EBook(name,pages,year,title,etype);
            b.add_sale(EBook);
        }
        else
        {
            Printedbook Pbook(name,pages,year,title);
            b.add_sale(Pbook);
        }
        cout<<"Συνεχίσε [y/n]";
        cin>>ch;
        if(ch=='n' || ch=='N')
            break;
    }
    b.display();
    b.profit();
    cout<<"\n\nTotal Cost spend -> "<<b.total_cost()<<endl;

    return 0;
}

int type_book(const string &type)
{
    if(type=="ebook" || type=="printed")
        return 1;
    else
        return 0;
}
