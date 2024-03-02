#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define SIZE 80

struct record{
	char name[SIZE];
	char surname[SIZE];
	int age;
	int grade;
	
};




int open(char *filename,FILE **fp,int *num);
int close(FILE **fp);
int add(FILE *fp);
int read(FILE *fp,int num,int rec,struct record *p);
void print(struct record temp);
void print_all(FILE *fp,int num);
int modify(FILE *fp,int num,int rec);

main()
{
	int choice;
	FILE *fp;
	int N;
	char filename[]="Data.dat";
	int check,rec;
	struct record temp;
	
	while(1)
	{
		printf("\n\n\nMENU");
		printf("\n==================");
		printf("\n1.Anoigma arxeoiu");
		printf("\n2.Close file");
		printf("\n3.prosthiki eggrafis");
		printf("\n4.Dibasma mia aggrafis");
		printf("\n5.Ektiposi olon eggrafvn");
		printf("\n6.Modify eggrafi");
		printf("\n7.EXIT");
		printf("\n================");
		printf("\nEpilogi:");
		scanf("%d",&choice);
		
	switch(choice)
	{
		case 1:
			check=open(filename,&fp,&N);
			 if(check)
			  printf("Succed opening file!");
			 else
			 {
			  printf("Error!");
			  exit(0);
		     }
		    break;
		case 2:
		    check=close(&fp);
			if(check){
			 printf("Succed closing file!");
			 N++;	
			}
			 else
			 {
			  printf("Error!");
			  exit(0);
		     }
			break;  
		case 3:
		    check=add(fp);
		    if(check)
			  printf("Succed eggrafi file!");
			 else
			 {
			  printf("Error!");
			  exit(0);
		     }
			break;
		case 4:
			printf("Poia eggrafi 8es:");
			scanf("%d",&rec);
			check=read(fp,N,rec,&temp);
			if(check==FALSE)
			{
				printf("Error");
				continue;
			}
			printf("I eggrafi %d einai",rec);
			print(temp);  
			break;
		case 5:
			print_all(fp,N);
			break;
		case 6:
				printf("Poia eggrafi 8es:");
			scanf("%d",&rec);
			check=modify(fp,N,rec);
			if(check==FALSE)
			{
				printf("Error");
				continue;
		    }
		    break;
		case 7:
		    printf("Buy Buy");
			exit(0);
			break;
		default:
		    printf("Lathos epilogi");	    
	}       
}

}

int open(char *filename,FILE **fp,int *num)
{
	struct record temp;
   (*fp)=fopen(filename,"rb");
   if((*fp)==NULL) //to arxeio den iparxei
   {
   	(*fp)=fopen(filename,"wb+");
   	if((*fp)==NULL)
   	{
   		printf("Error:opening file!");
   		return FALSE;
	   }
	 *num=0;
	 return TRUE;
   }
   else // to arxeio iparxei
   {
   	 fclose(*fp);
   	 (*fp)=fopen(filename,"rb+");
   	    if((*fp)==NULL)
   	    {
   	 	printf("Error:opening file");
   	 	return FALSE;
		}
		(*num)=0;
		while(fread(&temp,sizeof(struct record),1,(*fp))==1)
		  (*num)++; 
		
	return TRUE;   
   }
}

int close(FILE **fp)
{
	if(fclose(*fp)==0)
	 return TRUE;
	else
	 return FALSE; 
}


int add(FILE *fp)
{
	struct record temp;
	printf("Dwse to onoma:");
	scanf("%s",temp.name);
	printf("Dwse to eponimo:");
	scanf("%s",temp.surname);
	printf("Dwse ilikia: ");
	scanf("%d",&temp.age);
	printf("Dwse ton bathmo:");
	scanf("%d",&temp.grade);
	
	fseek(fp,0,SEEK_END);
	if(fwrite(&temp,sizeof(struct record),1,fp)==1)
	  return TRUE;
	else
	   return FALSE;  
	
}

int read(FILE *fp,int num,int rec,struct record *p)
{
	
	if(rec>=0 && rec<=num-1){
	  fseek(fp,rec*sizeof(struct record),SEEK_SET);
	  if(fread(p,sizeof(struct record),1,fp)==1)
	   return TRUE;
	  else
	   return FALSE; 	
	}
	else
	 return FALSE;
	

}

void print(struct record temp)
{
	printf("\n");
	printf("Onona %s\n",temp.name);
	printf("Eponimo %s\n",temp.surname);
	printf("Hilikia %d\n",temp.age);
	printf("Vatmos %d\n",temp.grade);
	
}
void print_all(FILE *fp,int num)
{
	struct record temp;
	int i;
	for(i=0; i<num; i++)
	{
		read(fp,num,i,&temp);
		printf("\nEggrafi %d",i+1);
		printf("\n-------------");
		print(temp);
	}
}


int modify(FILE *fp,int num,int rec)
{
	struct record temp;
	if(rec>=0 && rec<=num-1)
	{
		fseek(fp,rec*sizeof(struct record),SEEK_SET);
		fread(&temp,sizeof(struct record),1,fp);
		printf("I arxiki eggarfi einai:\n");
		print(temp);
		printf("Dwse to onoma:");
	    scanf("%s",temp.name);
	    printf("Dwse to eponimo:");
	    scanf("%s",temp.surname);
	    printf("Dwse ilikia: ");
	    scanf("%d",&temp.age);
	    printf("Dwse ton bathmo:");
	    scanf("%d",&temp.grade);
	    
	    printf("\n------Nea eggrafi:\n");
	    print(temp);
	    
	    fseek(fp,rec*sizeof(struct record),SEEK_SET);
		fwrite(&temp,sizeof(struct record),1,fp);
	    return TRUE;
	}
	else
	 return FALSE;
}




