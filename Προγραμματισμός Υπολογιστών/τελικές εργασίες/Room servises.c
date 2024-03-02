#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 50

main()
{
	int free_rooms[ROWS][COLS]={0},i,j,res,choice,rsvd_rooms,section,room,pl;
	
	rsvd_rooms=0;
	while(1)
	{
		system("cls");
		printf("\tMenu Selections\n");
		printf("------------------------\n");
		printf("1. \tShow information\n");
		printf("2. \tRoom reservetion\n");
		printf("3. \tDecline room reservetion \n");
		printf("4. \tExit\n");
		
		printf("Enter choice: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
		case 1:
			printf("Free rooms remaining: %d\n",(ROWS*COLS)-rsvd_rooms);
		    for(i=0; i<ROWS; i++)
			{
				for(j=0; j<COLS; j++)
				{
					if(free_rooms[i][j]==1)
					printf("%2s","X");
					else
					printf("%2s","#"); 
				}
				printf("\n");
			}
			break;
		case 2:
			if(rsvd_rooms==ROWS*COLS)
			{
		      printf("No free rooms available..!");
		      break;
		    }
			printf("Weclome to our reservesion system!\n");
			printf("For the section [1-3] the price is 40$ a night\n");
			printf("For the section [4-7] the price is 100$ a night\n");
			printf("For the section [8-10] the price is 250$ a night\n");
		    do{
		    	printf("\nEnter the section you would like to stay [1-%d]: ",ROWS);
		    	scanf("%d",&section);
			}while(section<1 || section>ROWS);
			
			 for(j=0; j<COLS; j++)
			{
				if(free_rooms[section][j]==0)
				 {
				 free_rooms[section][j]=1;
				 rsvd_rooms++;
				 printf("Your reservetion confirmed at section_%d and room_%d",section,j);
				 break;
			     }
				 if(free_rooms[section][j] == 1)
				 {
				 	pl++;
				 }
				 if(pl==5)
				  {
				  printf("Chose another section this is all bookced!!");
				  break;
			    }
			case 3:
				printf("You would like to cansel your resrvetion (YES:1)");
				scanf("%d",&choice);
				if(choice==1)
				{
					printf("\nEnter section[1-%d] and room[1-%d]: ",ROWS,COLS);
					scanf("%d %d",&section,&room);
					if(free_rooms[section][room]==0)
					 {
					  printf("This room is not reserverd... try again!");
					  break;
				    }
				    else
				    {
				    	printf("Your cansel is accepted");
				    	rsvd_rooms--;
				    	free_rooms[section][room]=0;
				    	break;
					}
				}
				case 4:
					printf("Thnak you for using our servise :)");
					break;
			    default:
			    	printf("Wrong choice try again");
			}
		
		 	
	
		 	
	   }
	printf("\n\n");
	system("pause");
    }
}
