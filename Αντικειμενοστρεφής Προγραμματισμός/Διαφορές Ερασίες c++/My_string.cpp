//
// Created by filipposp on 21/4/2022.
//
#include "iostream"
#include "cstring"

using namespace std;

class MyString
{
private:
    char *str;
    int size;
public:
    MyString() {size=1; str=new char[size]; strcpy(str," ");}
    explicit MyString(const char *string)
    {
        size=strlen(string);
        str=new char[size];
        strcpy(str,string);
    }
    MyString(const MyString &x)
    {
        size=x.size;
        str=new char[size];
        strcpy(str,x.str);
    }
    ~MyString() {delete[] str;}
    const char *get_str() {return str;}
    int get_size() const {return size;}
    bool operator==(const MyString &ob)
    {
        if(strcmp(str,ob.str)==0)
            return true;
        else
            return false;
    }
    bool operator!=(const MyString &ob)
    {
        if(strcmp(str,ob.str)!=0)
            return true;
        else
            return false;
    }
    bool operator>(const MyString &ob)
    {
        if(strcmp(str,ob.str)>0)
            return true;
        else
            return false;
    }
    bool operator<(const MyString &ob)
    {
        if(strcmp(str,ob.str)>0)
            return true;
        else
            return false;
    }
    MyString operator+=(char ch)
    {
        strncat(str,&ch,1);
        return *this;
    }

};

int main()
{

    MyString str4;
    MyString str1("stelios");
    MyString str2("Filippos");
    cout<<"My string1 -> "<<str1.get_str()<<" Size -> "<<str1.get_size()<<endl;
    cout<<"is "<<str2.get_str()<<" == "<<str1.get_str()<<endl;
    if(str1.operator==(str2))
        cout<<"They are"<<endl;
    else if(str1.operator!=(str2))
        cout<<"They are not"<<endl;

    cout<<"Is the "<<str1.get_str()<<" < "<<str2.get_str()<<endl;
    if(str1.operator<(str2))
        cout<<"it is"<<endl;
    else if(str1.operator>(str2))
        cout<<"Its is not"<<endl;

    cout<<"\nis "<<str4.get_str()<<"<"<<" "<<str1.get_str()<<endl;
    if(str1.operator>(str4))
        cout<<"it is"<<endl;
    else
        cout<<"\nIts not"<<endl;



    str1.operator+=('M');
    cout<<str1.get_str()<<endl;
    str2.operator+=('F');
    cout<<str2.get_str()<<endl;
    return 0;
}