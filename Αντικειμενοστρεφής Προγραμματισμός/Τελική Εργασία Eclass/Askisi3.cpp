#include <iostream>
#include <vector>
#include "Header.h"
#include <fstream>


static int cnt1=0,cnt2=0,cnt3=0;

#define C 6

ostream &operator<<(ostream &,const STUDENT &);
void set_courses(course *);
void show_courses(course *);
void insert_data(STUDENT &ob,STUDENT &ob2);
void erase_student(vector<STUDENT>&);
void raise_sem(vector<STUDENT>&,course *);
void compare_sem(vector<STUDENT>&,int ,int);
void show_Students(vector<STUDENT>&);
STUDENT set_student(course *);
void open_files(ofstream &,ofstream &,ofstream &);
void save_data(ofstream &,ofstream &,ofstream &,vector<STUDENT> &,course *);
void write_students(ofstream &, const STUDENT &);
void write_grades(ofstream &,const STUDENT &);
void write_courses(ofstream &,course [],int ,const STUDENT &);
int search_code(course *,string);

using namespace std;

int main()
{

    ofstream file1,file2,file3;
    open_files(file1,file2,file3);

    course pin[C];
    set_courses(pin);
    //-----------------------Ενδειξη φοιτητολογιου πινακα.--------------------------
    int pos2,pos1,choice,pos3,pos4;
    vector<STUDENT>Students;

    cout<<"\t\t ΦΟΙΤΗΤΟΛΟΓΙΟ ΠΑΔΑ! "<<endl;
    while(1)
    {
        cout<<"1.Δες το Προγραμμά σπουδών."<<endl;
        cout<<"2.Εκχωρήσε Φοιτητή στο φοιτητολόγιο."<<endl;
        cout<<"3.Συκγρινέ δύο Εξαμήνα Φοίτηων."<<endl;
        cout<<"4.Εμφανίσε Δεδομένα φοιτητών."<<endl;
        cout<<"5.Αυξήσε Εξάμηνο Φοιτητή."<<endl;
        cout<<"6.Εκχωρήσε Δεδομένα ενός φοίτητη σε έναν αλλόν."<<endl;
        cout<<"7.Διαγραψέ Φοιτήτη απο το φοιτητολογίο."<<endl;
        cout<<"8.Εξόδος Φοιτητολογίου."<<endl;
        cout<<"---------------------------------------------------"<<endl;
        cout<<"Επιλογή: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                show_courses(pin);
                break;
            case 2:
                Students.push_back(set_student(pin));
                break;
            case 3:
                if(Students.size()<=1)
                {
                    cout<<"Δεν έχει επαρκείς Φοιτητές το Φοιτητολογίο για συκγρισή εξαμήνων."<<endl;
                    break;
                }
                cout<<"Δώσε δύο φοίτητες [0-"<<Students.size()-1<<"]: ";
                cin>>pos1>>pos2;
                compare_sem(Students,pos1,pos2);
                break;
            case 4:
                show_Students(Students);
                break;
            case 5:
                raise_sem(Students,pin);
                break;
            case 6:
                if(Students.size()<=1)
                {
                    cout<<"Δεν έχει επαρκείς  Φοιτητες το φοιτητολόγιο. για εκχωρησή δεδομένων."<<endl;
                    break;
                }
                cout<<"\nΕπέλεξε τον φοίτητη που θες να Εκχώρησεις τα δεδομένα[0-"<<Students.size()-1<<"]: ";
                cin>>pos3;
                cout<<"\nΕπέλεξε τον φοίτητη οπου θες να πάρεις τα δεδόμενα[0-"<<Students.size()-1<<"]: ";
                cin>>pos4;
                insert_data(Students[pos3],Students[pos4]);
                break;
            case 7:
                erase_student(Students);
                break;
            default:
                system("clear");
                break;
        }
        if(choice==8)
        {
            save_data(file1,file2,file3,Students,pin);
            cout<<"Εξόδος...."<<endl;
            break;
        }

    }

    //------------------------------------------------------
    file1.close();
    file2.close();
    file3.close();
    return 0;

}

void save_data(ofstream &file1,ofstream &file2,ofstream &file3,vector<STUDENT> &pin,course *pin2)
{
    unsigned long int i;
    for(i=0; i<pin.size(); i++)
    {
        write_students(file1,pin[i]);
        write_grades(file3,pin[i]);
        write_courses(file2,pin2,C,pin[i]);
    }
    return ;
}


ostream &operator<<(ostream &C1,const STUDENT &ob)
{
    if(ob.get_sem()>1)
    {
        C1<<"Μέσος όρος μαθητής : ";
        C1<<ob.MO()<<endl;
    }
    else
        C1<<"Δεν έχει μεσό όρο ακόμα είναι πρώτο εξάμηνο!"<<endl;
    C1<<"--------------------------------"<<endl;
    return C1;
}


void set_courses(course *pin)
{
    pin[0].set_code("0");
    pin[0].set_lecture("C++");
    pin[0].set_sem(2);
    pin[1].set_code("6");
    pin[1].set_lecture("Java");
    pin[1].set_sem(4);
    pin[2].set_code("1");
    pin[2].set_lecture("Πιθανότητες");
    pin[2].set_sem(2);
    pin[3].set_code("12");
    pin[3].set_sem(1);
    pin[3].set_lecture("C");
    pin[4].set_code("9");
    pin[4].set_lecture("Μαθηματική αναλύση II");
    pin[4].set_sem(2);
    pin[5].set_code("17");
    pin[5].set_lecture("Διακριτά");
    pin[5].set_sem(1);

}

void open_files(ofstream &file1,ofstream &file2,ofstream &file3)
{
    file1.open("DATA_STUDENTS.txt",ios::trunc);
    file2.open("DATA_COURSE.txt",ios::trunc);
    file3.open("DATA_GRADES.txt",ios::trunc);
}

void write_students(ofstream &file, const STUDENT &ob){
    file<<"------ΔΕΔΟΜΕΝΑ "<<cnt1+1<<" ΜΑΘΗΤΗ!------"<<endl;
    file<<"Όνομα : "<<ob.get_name()<<endl;
    file<<"Εξαμήνο : "<<ob.get_sem()<<endl;
    file<<"Αριθμός μητρώου : "<<ob.get_am()<<endl;
    file<<"------------------------------------"<<endl;
    cnt1++;
}

void write_grades(ofstream &file,const STUDENT &ob)
{
    if(ob.get_sem()>1)
    {
        int size;
        size=ob.get_grades_size();
        file<<"------ΔΕΔΟΜΕΝΑ "<<cnt2+1<<"ο ΜΑΘΗΤΗ ΒΑΘΜΟΙ!------"<<endl;
        for(int i=0; i<size; i++)
        {
            file<<i+1<<"o  "<<ob.get_grade(i)<<endl;
        }
        file<<"Μέσος όρος Μάθητη -> "<<ob.MO()<<endl;
        file<<"----------------------------------------------"<<endl;
    }
    else
    {
        file<<"Ο μαθητής "<<cnt2+1<<" Δεν έχει περασμένα μαθήματα γιατί είναι 1ο εξάμηνο. \n";
    }
    cnt2++;
}

void write_courses(ofstream &file,course pin[],int size,const STUDENT &ob)
{
    string code,lec;
    unsigned int sem;
    if(cnt3==0)
    {
        file<<"----ΣΥΝΟΛΟ ΜΑΘΗΜΑΤΩΝ ΠΡΟΓΡΑΜΜΑ ΣΧΟΛΗΣ!-------"<<endl;
        file<<"ΚΩΔΙΚΟΣ \tΕΞΑΜΗΝΟ \tΛΕΚΤΙΚΟ"<<endl;
        for(int i=0; i<size; i++)
        {
            code=pin[i].get_code();
            lec=pin[i].get_lec();
            sem=pin[i].get_sem();
            file<<code<<" | "<<"\t\t"<<sem<<" | "<<"\t\t"<<lec<<endl;
        }
        file<<"----------------------------------------------"<<endl<<endl;
    }
    int size2=ob.get_course_size();
    file<<"------ΔΕΔΟΜΕΝΑ "<<cnt2<<"ο ΜΑΘΗΤΗ ΔΗΛΩΣΗ ΜΑΘΗΜΑΤΩΝ------"<<endl;
    for(int j=0; j<size2; j++)
    {
        file<<"ΚΩΔΙΚΟΣ \tΕΞΑΜΗΝΟ \tΛΕΚΤΙΚΟ"<<endl;
        code=ob.get_code(j);
        lec=ob.get_lec(j);
        sem=ob.get_sem(j);
        file<<code<<"\t\t\t\t"<<sem<<"\t\t\t\t"<<lec<<endl;
    }
    file<<"----------------------------------------------"<<endl<<endl;
    cnt3++;
}

int search_code(course *pin,string code)
{
    for(unsigned long int i=0; i<C; i++)
    {
        if(pin[i].get_code()==code)
            return i;
    }
    return -1;
}

void show_courses(course *pin)
{
    cout<<"----ΣΥΝΟΛΟ ΜΑΘΗΜΑΤΩΝ ΠΡΟΓΡΑΜΜΑ ΣΧΟΛΗΣ!-------"<<endl;
    cout<<"ΚΩΔΙΚΟΣ \tΕΞΑΜΗΝΟ \tΛΕΚΤΙΚΟ"<<endl;
    for(int j=0; j<C; j++)
        cout<<pin[j].get_code()<<" | "<<"\t\t"<<pin[j].get_sem()<<" | "<<"\t\t"<<pin[j].get_lec()<<endl;
    cout<<"----------------------------------------------"<<endl<<endl;
}

STUDENT set_student(course *pin)
{
    unsigned int sem;
    char *str;
    str=new char[80];
    string name,code;
    STUDENT temp;
    int course_cnt;
    int pos;
    cout<<"Δέλωσε Δεδομένα Φοίτητη."<<endl;
    cout<<"ΟΝΟΜΑ: ";
    cin>>name;
    temp.set_name(name);
    cout<<"ΑΡΙΘΜΟ ΜΗΤΡΩΟΥ: ";
    cin>>str;
    temp.set_am(str);
    cout<<"ΕΞΑΜΗΝΟ: ";
    cin>>sem;
    temp.set_sem(sem);
    cout<<"Δήλωσε μάθηματα [1-"<<C<<"]: ";
    cin>>course_cnt;
    while(course_cnt>0)
    {
        cout<<"Δώσε Κώδικο μαθήματος που θες να δηλώσεις: ";
        cin>>code;
        pos=search_code(pin,code);
        if(pos!=-1)
        {
            cout<<"Η αίτηση έγινε επιτυχώς!"<<endl;
            temp+=pin[pos];
            course_cnt--;
        }
        else
            cout<<"Αποτυχια αιτησης λάθος κωδικός."<<endl;

    }
    if(sem>1)
    {
        temp.set_grades();
    }
    return temp;
}

void compare_sem(vector<STUDENT> &pin,int pos1 ,int pos2)
{
    if(pin[pos1]>pin[pos2])
        cout<<"Είναι μεγαλυτερο  εξάμηνο ο"<<pin[pos1].get_name()<<" άπο τον "<<pin[pos2].get_name()<<endl;
    if(pin[pos1]>=pin[pos2])
        cout<<"Είναι μεγαλύτερι ισο εξάημνο ο "<<pin[pos1].get_name()<<" άπο τον "<<pin[pos2].get_name()<<endl;
    if(pin[pos1]<pin[pos2])
        cout<<"Είναι μικροτερο εξαμήνο ο "<<pin[pos1].get_name()<<" άπο τον "<<pin[pos2].get_name()<<endl;
    if(pin[pos1]<=pin[pos2])
        cout<<"Είναι μικρότερο ίσο εξάμηνο ο "<<pin[pos1].get_name()<<" άπο τον "<<pin[pos2].get_name()<<endl;
    if(pin[pos1]==pin[pos2])
        cout<<"Είναι ίδια εξάμηνα ο "<<pin[pos1].get_name()<<" με τον "<<pin[pos2].get_name()<<endl;
    if(pin[pos1]!=pin[pos2])
        cout<<"Είναι διαφορετικά εξάμηνα ο "<<pin[pos1].get_name()<<" με τον "<<pin[pos2].get_name()<<endl;
}

void show_Students(vector<STUDENT>&pin)
{
    if(pin.size()==0)
    {
        cout<<"Δεν υπαρχεί κάνενας Φοιτητής στο φοιτητολόγιο."<<endl;
        return ;
    }
    unsigned long int i;
    cout<<"\nΔΕΔΟΜΕΝΑ ΦΟΙΤΗΤΩΝ"<<endl;
    for(i=0; i<pin.size(); i++)
    {
        cout<<"----------------"<<i+1<<"ος ΦΟΙΤΗΤΗΣ"<<"--------------"<<endl;
        pin[i].display(cout);
        cout<<pin[i];
    }
    return ;
}

void raise_sem(vector<STUDENT>&pin,course *courses)
{
    int course_cnt;
    string code;
    if(pin.size()==0)
    {
        cout<<"Δεν υπαρχεί κάνενας Φοιτητής στο φοιτητολόγιο."<<endl;
        return ;
    }
    int pos,pos2;
    cout<<"\nΔώσε Θέση φοιτήτη που θες να Αυξησείς εξάμηνο [0-"<<pin.size()-1<<"]: ";
    cin>>pos;
    pin[pos].reis_sem();
    cout<<"Το εξάμηνο Αύξηθηκε Επιτυχώς."<<endl;
    cout<<"Δήλωσε μάθηματα [1-"<<C<<"]: ";
    cin>>course_cnt;
    while(course_cnt>0)
    {
        cout<<"Δώσε Κώδικο μαθήματος που θες να δηλώσεις: ";
        cin>>code;
        pos2=search_code(courses,code);
        if(pos2!=-1)
        {
            cout<<"Η αίτηση έγινε επιτυχώς!"<<endl;
            pin[pos]+=courses[pos2];
            course_cnt--;
        }
        else
            cout<<"Αποτυχια αιτησης λάθος κωδικός."<<endl;

    }
}

void insert_data(STUDENT &ob,STUDENT &ob2)
{
    ob=ob2;
    cout<<"Επιτυχής Εκχωρήσει!"<<endl;
}

void erase_student(vector<STUDENT>&pin)
{
    if(pin.size()==0)
    {
        cout<<"Δεν υπαρχεί κάνενας Φοιτητής στο φοιτητολόγιο."<<endl;
        return ;
    }
    int pos;
    cout<<"\nΕπέλεξε τον φοίτητη που θες Διαγραψείς[0-"<<pin.size()-1<<"]: ";
    cin>>pos;
    pin.erase(pin.begin()+pos);
}