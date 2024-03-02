#include <stdio.h>


int main(void)
{
	int etos_ar,etos_lij;
	int e,ap,a,b,c,d,f,z;
	
	printf("Dwse etos arxis: ");
	scanf("%d",&etos_ar);
	printf("Dwse etos lijis: ");
	scanf("%d",&etos_lij);
	
	for(e=etos_ar; e<=etos_lij; e++)
	{
		a=e%19;
		b=e%4;
		c=e%7;
		d=(a*19+16)%30;
		z=(2*b+4*c+6*d)%7;
		if((e%4==0 && e%100!=0) || e%400==0) //elexno an einai disekto etos;
		 f=1;
		else 
		 f=0;
		 
		ap=d+z+f+13;
		if(f==1)
		 if(ap<=28)
		  printf("Oi apokries tou %d einai stis %d Febrouariou!\n",e,ap);
		 else
		  printf("Oi apokries tou %d einai stis %d Martiou\n",e,ap-28);
		else
		 if(ap<=29)
		  printf("Oi apokries tou %d einai stis %d febrouariou!\n",e,ap);
		 else  
		  printf("Oi apokries tou %d einai stis %d Martiou!\n",e,ap-29);     
	}
}
