#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

//	040210078 - Kerem Bal

#define MAXSIZE 100 // We define a MAXSIZE value to determine maximum capacity of matrix and arrays.
					// Our aim to do that is prevent uncertainity on size of 1D & 2D arrays.
					// Program must allocate a memory for arrays. If the program would not know how much memory must be allocated, there will be a problem.

double rand_double() // Function which creates random number on double type.
{
	return ((double)rand())/((double)RAND_MAX);
}

void RandomAssignMatrix(double *ptr, int *row, int *column) // Random assigning function for matrix, which takes pointer type and dimension of matrix A.
															// We prefered to seperate the assigning a random number job as for matrix and for array.
{
	int i,j;
	for(i=0; i<*column; i++)
	{
        for(j=0; j<*row; j++)
		{
            if (i==j)								// We are solving equations for only diagonal matrixes. So we have to access any diagonal element. 
				*(ptr+i*(*column)+j)=rand_double();	// Accessing an element on matrix with "*(ptr+i*(*column)+j)" command.
			else
				*(ptr+i*(*column)+j)=0;				// Elements which is not diagonal must be 0.
        }
    }
}

void RandomAssignArray(double *ptr1, int *dArr) // Random assigning function for matrix, which takes pointer type and dimension of array b.
{
	int i;
	for(i=0; i<*dArr; i++)
		*(ptr1+i)=rand_double();				// Accessing an element on matrix with "*(ptr1+i)" command.
}

double *ByHandMatrix(double *matrix, int *row, int *column, int *flag)	//	Function which is used for getting values of matrix A from user.
																		//	Takes matrix and its dimensons as input.
																		//	Additionally, the *flag input is used for determine that matrix has a unique solution.
{
	int i,j;
	*flag=1;															//	Initial value of flag is 1, meaning unique solution exist.
	
	for(i=0; i<*column; i++)
	{
        for(j=0; j<*row; j++)
		{
			if(i==j)													//	Asks user only diagonal elements of matrix.
			{
				printf("Please enter value of matrix[%d][%d] :",i,j);
				scanf("%lf", (matrix+i*(*column)+j));
        	}
			else
				*(matrix+i**column+j)=0;								//	Non-diagonal elements must be 0.
		}
	}

	for(i=0; i<*column; i++)											//	A nested for loop to determine value of flag.
	{
        for(j=0; j<*row; j++)
		{
			if(i==j)													//	Checks only diagonal elemets.
			{
				if(*(matrix+i**column+j)==0)
				{
					*flag=0;
					break;												//	This break command means that if any of diagonal element is 0,
																		//	it is obvious that unique solution does not exist for that matrix. No need to continue.
				}
				else
					continue;
        	}
		}
	}

	return matrix;														//	Returning an array is possible due to the pointer function.
																		//	We used this return as input of our another function.
}

double *ByHandArray(double *arr, int *dArr)	//	Function which is used for getting values of matrix A from user, similar to previous function.
{
	int i;
    for(i=0; i<*dArr; i++)
	{				
		printf("Please enter value of array[%d] :",i);
		scanf("%lf", (arr+i));
    }

    return arr;
}

void *PrintMatrix(double *matrix, int *row, int *column)	//	Function that helps us to print matrix A easily.
{
	int i,j;
	printf("Matrix A:\n");
    for(i=0; i<*column; i++)
	{
        for(j=0; j<*row; j++)
           printf("%lf ", *(matrix+i**column+j)); 
        printf("\n");
    }
}

void *PrintArray(double *arr, int *dArr)	//	Function that helps us to print array b easily.
											//	Seperating functions as for matrix A and for array b is provide to avoid complexity on inputs and code lines.
{
	int i;
	printf("Array b:\n");
	for(i=0; i<*dArr; i++) 
		printf("%lf\n", *(arr+i));
	printf("\n");
}

void equationSolver(double *matrix, double *arr, double *solutionArr, int *row, int *column, int *dArr)	// Function that solves equation and prints solution array.
{
	int i,j;
	for(i=0; i<*column; i++)
	{
        for(j=0; j<*row; j++)
        {
        	if(i==j)														//	Deal with only diagonal elements. That is also provide optimization on program.
				*(solutionArr+i)=(*(arr+i))*(1/(*(matrix+i**column+j)));	//	Multiplying array b and inverse of matrix A and assigning to solution array.
		}
	}

	printf("Solution Array:\n");
	for(i=0; i<*dArr; i++)
		printf("%lf\n", *(solutionArr+i));
	printf("\n");
}

int main()
{
	srand(time(0));

	int flag=1;										//	Initial value of flag is 1, meaning unique solution exist.
    int ans1, ans2; 								//	We initialized ans1 and ans2 variables to use for after questions.
	int row=MAXSIZE, column=MAXSIZE, dArr=MAXSIZE;	//	Assigning MAXSIZE, defined in the beggining on code lines, to the row, column and dimension of arrays.
	int *r, *c, *d, *f;								//	Creating pointers row, column, dArr and flag variables.
	
	f=&flag;	// Assigning pointers to adresses of variables.
	r=&row; 
    c=&column;
    d=&dArr;

    double mat[*r][*c], Arr[*d], sArray[*d];	//	We initialized a 2D array for matrix A, an array for array b and another array for solution array.
    double *ptr=&mat[0][0], *ptr1=&Arr[0];		//	We assigned two pointers for assigning address of first elements of 2D array and 1D array.
	double *ptr2, *ptr3;						//	We created two null pointers to use for assign if it will be necessary.
	

	printf("**Linear Equation Solver**\n\n");	//	A fancy title for program that greet the user.

	while(1)	//	Provides the program flows forever.
	{
		printf("What do you want to do? Insert '1' for Equation Solver, '2' for Exit.:");
		scanf("%d",&ans1);

		while(ans1!=1 && ans1!=2)
		{
			printf("Please enter a appropriate value.\n'1' for Equation Solver, '2' for Exit.: ");
			scanf("%d",&ans1);
		}

		if(ans1==1)
		{
			printf("Please enter dimensions of matrix A (row,col): \n");
			scanf("%d %d",&row,&column);
			while(row!=column)	//	Matrix has to be square.
			{
				printf("Please re-enter dimensions of matrix A (row,col): \n");
				scanf("%d %d",&row,&column);
			}

			printf("Please enter dimension of array b: \n");
			scanf("%d",&dArr);
			while(dArr!=column)	//	Dimensions of array b and matrix A have to be appropriate to each other.
			{
				printf("Dimensions you have entered are not appropriate.\n");
				printf("Please enter dimension of array b: \n");
				scanf("%d",&dArr);
			}

			printf("For the Random Assignment insert '1'. For the Manual Assigment insert '2':\n");
			scanf("%d",&ans2);

			bool random,byhand;	//	Creating two variables in type of bool, which provides us to know that user selected random or manuel assignment.

			while(ans2!=1 && ans2!=2)
			{
				printf("Please enter a appropriate value.\n");
				printf("For the Random Assignment insert '1'. For the Manual Assigment insert '2':\n");
				scanf("%d",&ans2);
			}
			if(ans2==1)
			{
				RandomAssignMatrix(ptr, &row, &column);	//	Calling random assign functions to assign values for matrix A and array b.
				RandomAssignArray(ptr1, &dArr);
				random=true;							//	Assigning '1' to the random variable and '0' to the byhand operator
				byhand=false;							//	to understand what we are going to do.
			}
			if(ans2==2)
			{
				ptr2=ByHandMatrix((double *)mat, &row, &column, &flag);	//	Assigning returns of ByHand functions, which are kind of array.
				ptr3=ByHandArray((double *)Arr, &dArr);
				random=false;											//	Assigning '0' to the random variable and '1' to the byhand operator.
				byhand=true;
			}

			while(flag==0)	//	(flag==0) means that unique solution does not exist. So we have to turn back and ask values to user. 
			{
				flag=1;		//	Objective of this code is preventing bugs by reason of that the flag variable only change in ByHandMatrix function.
							//	This while loop may not be go back to ByHandMatrix loop.
							//	Then, a prompt will be appear even an initialization which has unique solution because flag is still 0.
				printf("\nUnique solution does not exist for your values. Please re-initialize matrix A and array b.\n\n");
				printf("For the Random Assignment insert '1'. For the Manual Assigment insert '2'. For the Exit insert any other:\n");
				scanf("%d",&ans2);
				
				while(ans2!=1 && ans2!=2)
				{
					printf("Please enter a appropriate value.\n");
					printf("For the Random Assignment insert '1'. For the Manual Assigment insert '2':\n");
					scanf("%d",&ans2);
				}
				if(ans2==1)
				{
					RandomAssignMatrix(ptr, &row, &column);
					RandomAssignArray(ptr1, &dArr);
					random=true;
					byhand=false;
				}
				if(ans2==2)
				{
					ptr2=ByHandMatrix((double *)mat, &row, &column, &flag);
					ptr3=ByHandArray((double *)Arr, &dArr);
					random=false;
					byhand=true;
				}
			}
			//	Calling Print functions.
			if(byhand)	//	The difference between byhand and random options on the if statements is matrix inputs for Print functions.
			{
				printf("\n");
				PrintMatrix(ptr2, &row,&column);	//	ptr2 and ptr3 were assigned with returns of ByHand functions's returns.
				printf("\n\n");						//	So, we have to use those pointers (arrays) if user chose manuel assignment option.
				PrintArray(ptr3, &dArr);
				printf("\n");
				equationSolver(ptr2, ptr3, sArray, &row, &column, &dArr);
			}
			else if(random)
			{
				printf("\n");
				PrintMatrix(ptr, &row,&column);		//	ptr and ptr1 were initially assigned with mat[0][0] and Arr[0] on the line 149.
				printf("\n\n");						//	So, we do not have to change anything if user chose random assignment option.
				PrintArray(ptr1, &dArr);
				printf("\n");
				equationSolver(ptr, ptr1, sArray, &row, &column, &dArr);
			}
		}
		else if(ans1==2)
		{
			printf("Exiting the program...");
			break;	//	Provides us to break the while(1) loop to exit program.
		}
	}
    return 0;
}
