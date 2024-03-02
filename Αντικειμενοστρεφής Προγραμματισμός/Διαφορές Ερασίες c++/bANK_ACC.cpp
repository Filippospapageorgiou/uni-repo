//
// Created by filipposp on 7/5/2022.
//
#include <iostream>
#include "fstream"
#include <string>

using namespace std;

class account
{
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
private:
    char acc_num[20];
    char firstname[20];
    char lastname[20];
    float total_balance;
};

void account::read_data()
{
	cout<<"\nΔώσε άριθμο λογαργιασμού: ";
	cin>>acc_num;
	cout<<"Δώσε Όνομα λογαργιασμού: ";
	cin>>firstname;
	cout<<"Δώσε Επώνυμο λογαργιασμού: ";
	cin>>lastname;
	cout<<"Δώσε Υπολοίπο Λογαργιασμού: ";
	cin>>total_balance;
	cout<<endl;
}

void account::show_data()
{
    cout<<"\n---------Δεδομένα λογαργιασμού---------"<<endl;
	cout<<"Αριθμός Λογαργιασμού: "<<acc_num<<endl;
	cout<<"Ονομα: "<<firstname<<endl;
	cout<<"Επώνυμο: "<<lastname<<endl;
	cout<<"Υπόλοιπο Λογιαργιασμού: "<<total_balance<<endl;
	cout<<"-----------------------------------------"<<endl;
}

void account::write_rec()
{
	ofstream outfile;
	outfile.open("record.bank",ios::binary|ios::app);
	read_data();
	outfile.write(reinterpret_cast<char *>(this),sizeof(*this));
	outfile.close();
}

void account::read_rec()
{
	ifstream infile;
	infile.open("record.bank",ios::binary);
	if(!infile)
	{
		cout<<"Λαθός στο ανοίγμα αρχείου"<<endl;
		return;
	}
	cout<<"---ΔΕΔΟΜΕΝΑ ΑΡΧΕΙΟΥ----"<<endl;
	
	while(!infile.eof())
	{
		if(infile.read(reinterpret_cast<char *>(this),sizeof(*this)))
		  show_data();
	}
	infile.close();
}

void account::search_rec()
{
	int n;
	ifstream infile;
	infile.open("record.bank",ios::binary);
	if(!infile)
	{
		cout<<"Λαθός στο ανοίγμα αρχείου"<<endl;
		return;
	}
	infile.seekg(0,ios::end);
	int count=infile.tellg()/sizeof(*this);
	cout<<"\nΥπαρχούν "<<count<<" εγγραφές στον φάκελο!"<<endl;
	cout<<"\nΔώσε αριθμό εγγραφής για να ψαξώ: ";
	cin>>n;
	infile.seekg((n-1)*sizeof(*this));
	infile.read(reinterpret_cast<char *>(this),sizeof(*this));
	show_data();
}

void account::edit_rec()
{
	int n;
	fstream iofile;
	iofile.open("record.bank",ios::in|ios::out|ios::binary);
	if(!iofile)
	{
		cout<<"Λαθός στο ανοίγμα αρχείου"<<endl;
		return;
	}
	iofile.seekg(0,ios::end);
	int count=iofile.tellg()/sizeof(*this);
    cout<<"\nΥπαρχούν "<<count<<" εγγραφές στον φάκελο!"<<endl;
	cout<<"\nΔώσε αριθμό εγγραφής για να μορφοποιησούμε: ";
	cin>>n;
	iofile.seekg((n-1)*sizeof(*this));
	iofile.read(reinterpret_cast<char *>(this),sizeof(*this));
	cout<<"Το εγγραφό "<<n<<" έχει τα ακόλουθα δεδομένα"<<endl;
	show_data();
	iofile.close();
	iofile.open("record.bank",ios::out|ios::in|ios::binary);
	iofile.seekp((n-1)*sizeof(*this));
	cout<<"Δώσε δεδομένα για την ρυθμισει εγγραφης"<<endl;
	read_data();
	iofile.write(reinterpret_cast<char *>(this),sizeof(*this));	
}

void account::delete_rec()
{
	int n;
	ifstream infile;
	infile.open("record.bank",ios::binary);
    if(!infile)
	{
		cout<<"Λαθός στο ανοίγμα αρχείου"<<endl;
		return;
	}
	infile.seekg(0,ios::end);	
	int count=infile.tellg()/sizeof(*this);
	cout<<"\nΥπαρχούν "<<count<<" εγγραφές στον φάκελο!"<<endl;
    cout<<"\nΔώσε αριθμό εγγραφής για να διαγραφη: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank",ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0; i<count; i++)
    {
    	infile.read(reinterpret_cast<char *>(this),sizeof(*this));
    	if(i==(n-1))
    	  continue;
    	tmpfile.write(reinterpret_cast<char *>(this),sizeof(*this));  
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank","record.bank");
}

int main()
{
	account bank;
	int choice;
	cout<<"---Τραπέζα Άρχειο Πέλατων!------"<<endl<<endl;
	while(true)
	{
		cout<<"------Δίαλεξε μια έπιλογη-----"<<endl;
		cout<<"Ε1-->Πρόσθεσε εγγαρφή στο αρχείο"<<endl;
		cout<<"Ε2-->Εμφάνισε όλες τις εγγράφες στο αρχείο"<<endl;
		cout<<"Ε3-->Ψάξε για μια εγγραφή στο αρχείο"<<endl;
		cout<<"Ε4-->Ρύθμισε εγγραφή από το αρχείο"<<endl;
		cout<<"E5-->Δίαγραψε εγγράφη από αρχείο"<<endl;
		cout<<"Ε6-->Εξόδος προγγράματος"<<endl;
		cout<<"Επιλογή: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
			    bank.write_rec();
			    break;
			case 2:
			     bank.read_rec();
			     break;
			case 3:
			     bank.search_rec();
			     break;
			 case 4:
			     bank.edit_rec();
			     break;
			 case 5:
			      bank.delete_rec();
			      break;
			  case 6:
			      cout<<"Εξόδος Προγράμματος!!"<<endl;
			      exit(0);
			   default:
			       cout<<"Διάλεξε σωστη επιλογή"<<endl;
			       break;
		}
	}
	return 0;
}



