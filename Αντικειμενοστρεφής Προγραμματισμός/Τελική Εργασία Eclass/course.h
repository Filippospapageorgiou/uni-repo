
#ifndef DOCUMENTS_COURSE_H
#define DOCUMENTS_COURSE_H

#include "string"

using namespace std;

class course{
private:
    string code;
    string lecture;
    unsigned int sem;
public:
    course(string _code,string _lec,int _sem);
    course();
    void set_code(string );
    void set_lecture(string );
    void set_sem(unsigned int);
    string get_code()const;
    string get_lec()const;
    unsigned int get_sem()const;
    void display();
    course &operator=(const course &ob);
};


#endif //DOCUMENTS_COURSE_H
