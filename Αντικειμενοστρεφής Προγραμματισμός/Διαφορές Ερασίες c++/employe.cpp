#include <iostream>
#include <vector>
#include <string>

using namespace std;

class EMPLOYE
{
protected:
     string name;
public:
      EMPLOYE();
      EMPLOYE(string name);
      void set_name(string name);
      string getname()const;	
      virtual int PAY_DAY(int days)=0;
      virtual void display()=0;
      virtual ~EMPLOYE()
      { }
};

EMPLOYE::EMPLOYE()
{name="N/A";}
EMPLOYE::EMPLOYE(string name)
{this->name=name;}

void EMPLOYE::set_name(string name)
{this->name=name;}

string EMPLOYE::getname()const
{return name;}

class EPOXIKOS:public EMPLOYE
{
private:
    int wage;
public:
    EPOXIKOS()
    {
     wage=0;
     name="N/A";
     }
    EPOXIKOS(int _wage,string name):EMPLOYE(name)
    {wage=_wage;}
    int PAY_DAY(int days)
    {return days*wage-2*wage;}    
	void set_wage(int _wage)
	{wage=_wage;}
	int get_wage()const
	{return wage;}
	void display()
	{
		cout<<"EPOXIKOS"<<endl;
		cout<<"Name-> "<<name<<endl;
		cout<<"Wage-> "<<wage<<endl;
	}
};

class MISTHOTOS:public EMPLOYE
{
protected:
	int wage;
public:	
    MISTHOTOS()
    {
      wage=0;
      name="N/A";
    }
    MISTHOTOS(int _wage,string name):EMPLOYE(name)
    {wage=_wage;}
    int PAY_DAY(int days)
    {return days*wage;}
   	void display()
	{
		cout<<"MISTHOTOS"<<endl;
		cout<<"Name-> "<<name<<endl;
		cout<<"Wage-> "<<wage<<endl;
	}	
	bool operator!()
	{
		if(wage<100)
		 return true;
		else
		 return false; 
	}
};

class MANAGER:public MISTHOTOS
{
private:
    int bonus;
public:
    MANAGER()
    {bonus=0;}
    MANAGER(int _bonus,int wage,string name):MISTHOTOS(wage,name)
    {bonus=_bonus;}
    int PAY_DAY(int days)
    {return days*wage+bonus;}
  	void display()
	{
		cout<<"MANAGER"<<endl;
		cout<<"Name-> "<<name<<endl;
		cout<<"Wage-> "<<wage<<endl;
		cout<<"Bonus-> "<<bonus<<endl;
	}
};

ostream &operator<<(ostream &,MISTHOTOS &ob);

int main()
{
    vector<EMPLOYE *> pin;
    EMPLOYE *ob1;
    EMPLOYE *ob2;
    EMPLOYE *ob3;
    ob1=new EPOXIKOS(4,"stelios");
    ob2=new MISTHOTOS(3,"filippos");
    ob3=new MANAGER(100,5,"Alexis");
    pin.push_back(ob1);
    pin.push_back(ob2);
    pin.push_back(ob3);

    int sum=0;

    for(unsigned long int i=0; i<pin.size(); i++)
    {
    	pin[i]->display();
    	cout<<"Summurize wage: "<<pin[i]->PAY_DAY(7)<<endl;
    	cout<<"---------------------------"<<endl;
    	sum+=pin[i]->PAY_DAY(7);
    }

    cout<<"ALL WAGES-> "<<sum<<endl;
    if(!ob2)
      cout<<"wage<100"<<endl;
    else
      cout<<"wage>100"<<endl;   
    
    
	return 0;
}

ostream &operator<<(ostream &left,MISTHOTOS &ob)
{
	if(!ob)
	 left<<"Wage>100"<<endl;
	else
	 left<<"wage<100"<<endl;

	return left; 
}
