//
// Created by filipposp on 30/5/2022.
//
#include <iostream>
#include <list>

using namespace std;

class person;

class doctor
{
private:
    string name;
    string thl;
    string spec;
    list<person *>pelates;
public:
    doctor(string name,string thl,string spec)
    {
        this->name=name;
        this->thl=thl;
        this->spec=spec;
    }
    void display()
    {
        cout<<"Doctor Status: "<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"THl: "<<thl<<endl;
        cout<<"Spec: "<<spec<<endl;
        cout<<"-----------------"<<endl;
    }
    void addperson(person * P)
    {
        pelates.push_back(P);
    }
    void show_clinets();
    
};


class person
{
private:
    string afm;
    string name;
    int age;
    list<doctor *>giatroi;
public:
    person(string afm,string name,int age)
    {
        this->name=name;
        this->afm=afm;
        this->age=age;
    }
    void addDoctor(doctor * D)
    {
        giatroi.push_back(D);
    }
    void show_mydoc()
    {
        cout<<"Oi giatroi mou "<<endl;
        list<doctor *>::iterator it;
        for(it=giatroi.begin(); it!=giatroi.end(); it++)
            (*it)->display();
    }
    void display()
    {
        cout<<"Pelatis Status: "<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"AFM: "<<afm<<endl;
        cout<<"AGE: "<<age<<endl;
        cout<<"-----------------"<<endl;
    }
    string get_name()const
    {return name;}
    int set_age(int _age)
    {
         try
        {
          age=_age;
          if(_age<0)
              throw -1;
          else if(_age>0 && _age<18)
              throw 'a';
          else
              throw 2.2;
        }
        catch(int a)
        {
           cout<<"arinitik timi"<<endl;
        }
        catch(char ch)
        {
            cout<<"anlikos"<<endl;
        }
        catch(float e)
        {
            cout<<"enilikos"<<endl;
        }
        return 1;
    }
    int get_age()
    {return age;}
    void operator<(person * ob)
    {
    	if(age<ob->get_age())
    	 cout<<"Name: "<<name;
    	else
    	 cout<<"Name: "<<ob->get_name();
    }
};

void doctor::show_clinets()
{
  cout<<"Oi pelates mou"<<endl;
  list<person *>::iterator it;
  for(it=pelates.begin(); it!=pelates.end(); it++)
    (*it)->display();	
}




int main()
{

    person *ob1=new person("2134723","stelios",19);
    person *ob2=new person("2351673","maria",20);
    person *ob3=new person("3333123","filippos",32);
    person *ob4=new person("1341412","Alexandors",55);

    doctor *doc1=new doctor("makis","2136218","kardiologos");
    doctor *doc2=new doctor("xristos","3232132","kardiologos");
    doctor *doc3=new doctor("giannis","69875122","psixiatros");

    
    doc1->addperson(ob1);
    doc1->show_clinets();
    doc2->addperson(ob2);
    doc2->show_clinets();
    doc3->addperson(ob3);
    doc3->show_clinets();

    ob1->addDoctor(doc1);
    ob1->show_mydoc();
    ob2->addDoctor(doc2);
    ob2->show_mydoc();
    ob3->addDoctor(doc3);
    ob3->show_mydoc();
    ob4->addDoctor(doc1);
    ob4->show_mydoc();

    cout<<endl;
    *ob1<ob2;

     ob1->set_age(7); 
    

    return 0;
}
