#include <stdio.h>
#include <string.h>
#define N 100
main()
{
   char a[N],b[N];
   

  printf ("Enter a string to check if is palindrome:  ") ;
  gets(a);

  strcpy (b,a) ;  // ��������� ������������� �������
  strrev (b) ;  // ���������� ��� �������������

  if(strcmp(a,b)==0)  // �������� ������������� ������� �� ��� ���������� ������������
   {
   	 printf( "The string is a palindrome.\n" ) ;
   	 puts(a);
   	 puts(b);
	} 
  else
  {
  	printf( "string not a palindrome.\n" ) ;
  	puts(a);
   	puts(b);
  }

}
