#include "string"
#include "vector"
#include "course.h"

using namespace std;


class STUDENT
{
	private:
	     char *am;
	     string name;
	     unsigned int sem;
	     //Νέα atributes-------
         vector<course> pin;
         vector<pair<course ,float>> grades;
	public:
         STUDENT();
	     STUDENT(const char *_am,string _name,unsigned int _sem=1);
	     void set_am(const char *_am);
	     void set_name(string _name);
	     void set_sem(unsigned int _sem);
	     void display(ostream &a);
	     char *get_am()const;
	     string get_name()const;
	     unsigned int get_sem()const;
         void reis_sem();
	     //Νεες Συναρτήσεις-----------
         void operator+=(const course &ob);
         void set_grades();
         float get_grade(int pos)const;
         course get_course(int pos);
         int get_course_size()const;
         int get_grades_size()const;
         string get_code(int pos)const;
         string get_lec(int pos)const;
         unsigned int get_sem(int pos)const;
         STUDENT &operator=(const STUDENT &ob);
         bool operator==(const STUDENT &ob) const;
         bool operator!=(const STUDENT &ob) const;
         bool operator<(const STUDENT &ob) const;
         bool operator<=(const STUDENT &ob) const;
         bool operator>(const STUDENT &ob) const;
         bool operator>=(const STUDENT &ob) const;
         double MO()const;
};
