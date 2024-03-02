#include <iostream>
#include <cstring>
#include <vector>
#include "Header.h"
#include "course.h"


using namespace std;

//Σύναρτησεις Students-------------------------------------------------------------
STUDENT::STUDENT()
{
    am=new char[80];
    strcpy(am,"N/A");
    name="N/A";
    sem=0;
}

STUDENT::STUDENT(const char *_am,string _name,unsigned int _sem)
{
    am=new char[80];
    strcpy(am,_am);
    name=_name;
	sem=_sem;
}


void STUDENT::set_am(const char *_am)
{
    strcpy(am,_am);
}

void STUDENT::set_name(string _name)
{ name=_name; }

void STUDENT::set_sem(unsigned int _sem)
{ sem=_sem; }

void STUDENT::display(ostream &a)
{
    unsigned long int i;
    a<<"--------ΔΕΔΟΜΕΝΑ ΜΑΘΗΤΗ!------------------"<<endl;
	a<<"Αριθμός μητρώου : "<<am<<" Ονομα : "<<name
	<<" Τρεχών εξάμηνο : "<<sem<<endl;
    if(sem>1)
    {
        a<<"Επιτυχημένοι Βαθμοί Προηγουμενων μαθηματών"<<endl;
        for(i=0; i<grades.size(); i++)
        {
            a<<"----"<<i+1<<"------"<<endl;
            grades[i].first.display();
            a<<"Βάθμος μαθήματος : "<<grades[i].second<<endl;
        }
    }
    else
    {
        a<<"Είναι άκομα πρώτο έξαμηνο δεν έχει Προήγουμενα μαθήματα!"<<endl;
    }
    a<<"\nΔήλωμενα μαθήματα Τρεχων εξάμηνο"<<endl;
    for(i=0; i<pin.size(); i++)
        pin[i].display();
   cout<<endl;
}


string STUDENT::get_name()const
{return name;}

unsigned int STUDENT::get_sem()const
{return sem;}


void STUDENT::operator+=(const course &ob) {
    pin.push_back(ob);
    return ;
}



STUDENT &STUDENT::operator=(const STUDENT &ob) {
    if(this==&ob)
        return *this;

    delete[] am;
    am=new char[80];
    strcpy(am,ob.am);
    name=ob.name;
    sem=ob.sem;
    pin.clear();
    pin=ob.pin;
    if(ob.get_sem()>1)
    {
        grades.clear();
        grades=ob.grades;
    }
    else
    {
        grades.clear();
    }
    return *this;
}

bool STUDENT::operator==(const STUDENT &ob) const {
    if(sem==ob.sem)
        return true;
    else
        return false;
}

bool STUDENT::operator!=(const STUDENT &ob) const {
    if(sem!=ob.sem)
        return true;
    else
        return false;
}

bool STUDENT::operator<(const STUDENT &ob) const {
    if(sem<ob.sem)
        return true;
    else
        return false;
}

bool STUDENT::operator<=(const STUDENT &ob) const {
    if(sem<=ob.sem)
        return true;
    else
        return false;
}

bool STUDENT::operator>(const STUDENT &ob) const {
    if(sem>ob.sem)
        return true;
    else
        return false;
}

bool STUDENT::operator>=(const STUDENT &ob) const {
    if(sem>=ob.sem)
        return true;
    else
        return false;
}

double STUDENT::MO() const {
    double sum=0;
    for(unsigned long int i=0; i<grades.size(); i++)
    {
        sum+=grades[i].second;
    }
    return sum/grades.size();
}


void STUDENT::set_grades() {
    float grade;
    int size;
    course temp;
    string lec,code;
    unsigned int sem;
    cout<<"\nΔεδομένα βαθμών περασμένων μαθημάτων!! "<<endl;
    cout<<"Πόσα μαθήματα επιτυχώς πέρασες το προηγούμενο εξαμήνο : ";
    cin>>size;
    cout<<endl;
    for(int i=0; i<size; i++)
    {
        cout<<"----Δώσε δεδομένα για το "<<i+1<<" Μάθημα-----"<<endl;
        cout<<"Λεκτικο μαθήματος : ";
        cin>>lec;
        temp.set_lecture(lec);
        cout<<"Κώδικος μαθηματός : ";
        cin>>code;
        temp.set_code(code);
        cout<<"Δώσε εξάμηνο μαθήματος : ";
        cin>>sem;
        temp.set_sem(sem);
        do {
            cout<<"Δώσε επίτυχη βαθμό: ";
            cin>>grade;
        }while(grade<5 || grade>10);
        grades.push_back(make_pair(temp,grade));
        cout<<endl;
    }


}

char *STUDENT::get_am() const {
    return am;
}

int STUDENT::get_course_size() const {
    return pin.size();
}

int STUDENT::get_grades_size() const {
    return grades.size();
}

float STUDENT::get_grade(int pos) const {
    return grades[pos].second;
}

course STUDENT::get_course(int pos)  {
    return grades[pos].first;
}



string STUDENT::get_lec(int pos) const {
    return pin[pos].get_lec();
}

string STUDENT::get_code(int pos) const {
    return pin[pos].get_code();
}

unsigned int STUDENT::get_sem(int pos) const {
    return pin[pos].get_sem();
}

void STUDENT::reis_sem() {
    sem++;
    float grade;
    int flag;
    for(unsigned long int i=0; i<=pin.size(); i++)
    {
        pin[i].display();
        cout<<"Πέρασε με επιτυχώς βαθμό το μάθημα [1->ΝΑΙ] , [0->ΟΧΙ]: ";
        cin>>flag;
        if(flag)
        {
            do {
                cout<<"Δώσε επίτυχη βαθμό: ";
                cin>>grade;
            }while(grade<5 || grade>10);
            grades.push_back(make_pair(pin[i],grade));
        }
        pin.erase(pin.begin()+i);
    }
}

//----------------------------------------------------------------------------
//Σύναρτησεις Course-------------------------------------------------



course::course(string _code, string _lec, int _sem) {
    code=_code;
    lecture=_lec;
    sem=_sem;
}


void course::set_code(string _code)  {
    code=_code;
}

void course::set_lecture(string _lec){
    lecture=_lec;
}

void course::set_sem(unsigned int _sem){
    sem=_sem;
}

course::course() {
    code="N/A";
    lecture="N/A";
    sem=0;
}



void course::display() {
    cout<<"Κώδικος μάθηματος : "<<code<<" Όνομα μαθηματός :"<<lecture<<" Έξαμηνο : "<<sem<<endl;
}

string course::get_code() const {
    return code;
}

string course::get_lec() const {
    return lecture;
}

unsigned int course::get_sem() const {
    return sem;
}

course &course::operator=(const course &ob)
{
    code=ob.code;
    lecture=ob.lecture;
    sem=ob.sem;
    return *this;
}




//---------------------------------------------------------------------------------
