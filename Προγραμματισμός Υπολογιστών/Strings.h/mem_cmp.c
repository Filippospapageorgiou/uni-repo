#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mem_cmp(const void *ptr1,const void *ptr2,int size);

int main(void)
{
	char str1[100],str2[100];
	int num;
	
	printf("Enter text: ");
	gets(str1);
	
	printf("Enter text: ");
	gets(str2);
	
	printf("Enter char to compare: ");
	scanf("%d",&num);
	
	printf("%d",mem_cmp(str1,str2,num));
}


int mem_cmp(const void *ptr1,const void *ptr2,int size)
{
	char *p1,*p2;
	
	p1=(char*)ptr1;
	p2=(char*)ptr2;
	while(size!=0)
	{
		if(*p1!=*p2)
		 return *p1-*p2;
		p1++;
		p2++;
		size--; 
	}
	return 0;
}
