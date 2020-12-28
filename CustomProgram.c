#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
/*include libraries*/

typedef struct
{	/*Create structure with properties or members of integer value and integer visited*/
	int value; /*represents elements of 2D grid that come later on*/
	int visited; /*A variable to simply check if the element has been "visited" or not, 0 means unvisited and 1 means visited */
} gridIndex; /*name of structure*/

/* a struct acting as a member inside another struct
	Simply holds the indexes of the game grid along with the users current row and column. */
typedef struct
{
	gridIndex indexes[8][8]; /*using datatype struct inside another struct*/
	int row;
	int column;
} gameGrid;

typedef struct
{	/*Create structure with properties of character and integer score*/
	char userName[100]; /* stores name of user */
	int score; /* stores the user score */
} user; /*name of structure*/

/*Prototype functions*/
void introPara(char userName[100]); /* Gives the introduction paragraph with instructions. Takes user's name in account.*/
void randomiseGrid(gameGrid *grid, int *score); /* Function to randomise the values of the array, using integer pointer called score */
void displayGrid(gridIndex grid[8][8]); /* Prints out the 2D array */
int handleInput(gameGrid *grid, user *userData); /* gameGrid type pointer called grid passed into function */
int handleInput2(gameGrid *grid, user *userData, char userInput); /* If the user wants to restart the game */

int main() /* main function starts */
{	 
	int i; /* i and j are used for running iterations*/
    int j;	  
	
  	gameGrid grid; /* declare grid as new variable of type gameGrid */
    user userData; /* Creates a new object like variable that inherits values from struct called user */
    char userInput; /* is used to see what character user entered */
	int continueGame=1; /*initialise this to 1 to keep the program running*/
	
	int line=0; 
	char input[512];
	FILE *fpointer; /*make File pointers*/
	FILE *fppointer;
	
	fpointer=fopen("custom.txt","a"); /* 'a' represents amend */
	printf("Please enter your first name: ");
	scanf("%s",&userData.userName);	/* gets user name and store it in u */
	fppointer=fopen("custom.txt","r"); /* 'r' represents read */
	
	while( fgets(input,512,fppointer)) 
	{
		line++;
		printf("%s",input); /* Using while loop to print out the text file, line by line.*/
	}
	fclose(fppointer); /* close file pointer*/
	
	introPara(userData.userName); /*Passes in the member userName of variable userData that we declared earlier using user struct(Example of Call By Value)*/;
	randomiseGrid(&grid, &userData.score); /*Randomises grid, passes arguments e.g grid and memory address of userData.score, to the pointer int *score  */;
	
	while(continueGame != 0) /* using while loop to keep the game going*/
    {	/*while loop starts*/
		printf("\n\nNumber of attractions visited so far is %d\n\n",userData.score); /*Print out score */
		displayGrid(grid.indexes); /* displays the grid by passing variable grid. Which would even have members visited and value and also the 2D array. Another example of call by value*/
		continueGame = handleInput(&grid, &userData); 
		
		/*2 things are happening here. The result of Memory addresses of variables passed into respective pointers,
		and secondly, after the function handleInput has ran it will return a number which will determine
		if the program will run further. Depeneding if the condition of the while loop is satisfied or not */
		
		if(grid.row==7 && grid.column==7) /* check to see if user has reach to the end of the grid, when the grid.row and grid.column is storing 7.*/
		{
			printf("\n\nCongratulations %s, you have reached the end" , userData.userName); /*Gives a message*/
			printf("\nFinal number of attractions visited are %d",userData.score); /*Prints final score*/
			fprintf(fpointer,"%s 	%d\n",userData.userName,userData.score); /*writes name and final score into custom.txt */
			printf("\n \nPlease press h or H to play again. Press any other button to quit: "); 
			scanf(" %c",&userInput);
			
			/* Additional feature: Asks user if they would like to play again without exiting the program. */
			continueGame = handleInput2(&grid, &userData, userInput); /* handleInput2 is the function that will "reset" or quit the game */
			/*parameters passed by referrence to pointers in the function, except userInput
			Whatever value is returned, is stored in continueGame variable to determine the continuity of the program */
			
			if(continueGame == 2) /* if the number 2 is returned we finish the game. */ /*Example of nested if*/
			{ /*if statement start*/
				break; /*break statement*/
			} /*if statement end*/
        }
    } /*while loop ends*/
} /*main function ends*/

void introPara(char userName[100]) /* This function simply receives a copy of the name of the user by value and uses it in the intro paragraph*/
{
	printf("*****************************Welcome to the Manhattan Tourist Problem game.***************************** \n\nDear %s,"
		 "The objective of the game is to go from the top left of the grid to the bottom right of the grid\n"
		 "across the map and visit the maximum number of attractions which are denoted by the numbers.\nYou can only move RIGHT and DOWN " 
		 "using the R or r(to move right)and D or d(to move down)\nPlease note if you quit the program,you will "
		 "lose progres.\nYOU MAY CHECK THE LIST OF SCORES BY SCROLLING UP",userName); /*introduction*/
}

void randomiseGrid(gameGrid *grid, int *score) /* This function is used to create the grid data and fill the grid with "random elements" */
{
	int i; 
	int j;
	grid->row=0;
	grid->column=0;	   
	srand(time(NULL)); /*using time to "randomise" the number*/
	for(i=0;i<8;i++) /*Nested for loop*/
	{
		for(j=0;j<8;j++)
		{
			grid->indexes[i][j].visited=0; /* sets everything in array to "not-visited" or "0"  */
			grid->indexes[i][j].value=rand()%10; 
		}
	} 
	
	grid->indexes[0][0].visited=1; /*first and last element are set to 1 which means they will have pipes besides them, like "|2|"*/
	grid->indexes[7][7].visited=1;
	*score = grid->indexes[0][0].value; /*example of derefencing*/ 
	/*initialising the score to the first element of the array as that is the starting point of our program*/
}

void displayGrid(gridIndex grid[8][8]) /* Displays the grid using nested for loop */
{
	int i,j;
	for(i=0;i<8;i++) /* printing a 2D array*/
	{
	   	printf("\n");
	    for(j=0;j<8;j++)
	    {
			if(grid[i][j].visited==1) /*checks if elements have been "visited"*/
			{
				printf("-|%d|",grid[i][j].value); /*then put a pipe besides them and then print*/
			}
			else
			{
        		printf("- %d ",grid[i][j].value); /*else print without pipes*/
			}
   		}

    	printf("\n  |   |   |   |   |   |   |   |");
	}	 
}

int handleInput(gameGrid *grid, user *userData) /*pointer to grid type(struct) called grid and a pointer using user type(struct) called userData */
{
	/* declare variable to get user input and use it to perform appropriate action */
	char userInput;
    printf("\n \nPlease press r to go right, d to go down, q to quit, h to restart: ");
    scanf(" %c",&userInput);
	
    if((userInput=='r'|| userInput=='R') && grid->column < 7) /*Error handling, if lower case r or upper case R  */
    {	/* Only if the column value is less then 7 then our program will move towards the element on the right. Mainly because our index starts from 0 */
        (grid->column)++; /*add 1 to the value of pointer */
        (userData->score) += grid->indexes[grid->row][grid->column].value; /* score member of userData accumulates score corresponding the value at a specific row/grid */
		grid->indexes[grid->row][grid->column].visited=1;	/*sets the specific element to visited, which means later on it can be printed in pipes*/
		return 1; /*gets stored in the main in continueGame*/
    }
    else if((userInput=='d' || userInput=='D') && grid->row < 7) /*similar pattern follows for row*/
	{
        (grid->row)++; /*add 1 to the value of pointer */
        (userData->score) += grid->indexes[grid->row][grid->column].value;	/* score member of userData accumulates score corresponding the value at a specific row/grid */
		grid->indexes[grid->row][grid->column].visited=1; /*sets the specific element to visited, which means later on it can be printed in pipes*/
		return 1; /*gets stored in the main in continueGame*/
    }
	
	return handleInput2(grid, userData, userInput);	/* Calls handleInput2, which will eventually return back 2.. */
}

int handleInput2(gameGrid *grid, user *userData, char userInput)	/* Function for the user to restart the game */
{
    if(userInput=='q' || userInput=='Q')	/* if user presses q or Q to quit */
    {	
            printf("You chose to quit the program, \nThank you %s, for playing, good bye.",userData->userName);
            return 0;
    }
	else if(userInput=='h' || userInput=='H') /*Once the user decides to replay the game*/
	{
		grid->row=0; /*initialise to 0*/
		grid->column=0;
		introPara(userData->userName); /*call methods*/	      
		randomiseGrid(grid, &userData->score);
		return 1;
	}
	
	return 2;	/* simply returns 2 to main function, if user does not press a valid choice */
}


