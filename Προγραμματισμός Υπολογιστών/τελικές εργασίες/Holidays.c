#include <stdio.h>
#include <stdbool.h>

bool disekto(int e);
int imera(int h, int m, int e);
void emfanisi_imeras(int h, int m, int e);

int main(void)
{
	int etos;
	printf("Dose etos: ");
	scanf("%d",&etos);
	emfanisi_imeras(1,1,etos);
	emfanisi_imeras(6,1,etos);
	emfanisi_imeras(25,3,etos);
	emfanisi_imeras(15,8,etos);
	emfanisi_imeras(28,10,etos);
	emfanisi_imeras(25,12,etos);
	emfanisi_imeras(26,12,etos);
	return 0;
}

// Επιστρέφει τον α/α της ημέρας μιας ημερομηνίας h/m/e
// 0->Κυριακή, 1->Δευτέρα, .... , 6->Σάββατο
int imera(int h, int m, int e)
{
 	int a,b1,b2,b3,g,s,d,x;
	a=365*(e-1);
	b1=(e-1)/4;
	b2=-(e-1)/100;
	b3=(e-1)/400;
	g=(367*m-362)/12;
	if (m<=2)
		d=0;
	else if (m>2 && disekto(e))
		d=-1;
	else
		d=-2;
	s=a+b1+b2+b3+g+h+d;
	x=s%7;
	return x;
}

// Επιστρέφει τιμή true αν το έτος e είναι δίσεκτο, διαφορετικά false
bool disekto(int e)
{
	if ((e%4==0 && e%100!=0) || e%400==0)
		return true;
	else
		return false;
}


// Εμφανίζει ολογράφως την ημέρα μιας ημερομηνίας h/m/e
void emfanisi_imeras(int h, int m, int e)
{
	int ar_im;
	ar_im=imera(h,m,e);
	switch(ar_im)
	{
		case 0:
			printf("H hmera stis %d/%d/%d einai Kyriaki\n",h,m,e);
			break;
		case 1:
			printf("H hmera stis %d/%d/%d einai Deytera\n",h,m,e);
			break;
		case 2:
			printf("H hmera stis %d/%d/%d einai Triti\n",h,m,e);
			break;
		case 3:
			printf("H hmera stis %d/%d/%d einai Tetarti\n",h,m,e);
			break;
		case 4:
			printf("H hmera stis %d/%d/%d einai Pempti\n",h,m,e);
			break;
		case 5:
			printf("H hmera stis %d/%d/%d einai Paraskevi\n",h,m,e);
			break;
		case 6:
			printf("H hmera stis %d/%d/%d einai Savvato\n",h,m,e);
			break;
	}
}
