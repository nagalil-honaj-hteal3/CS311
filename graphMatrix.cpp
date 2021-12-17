/******************************************
Graph of social network implmemented with a matrix

Your name: XXXXXXXXXXXXXX
Your programmer number: XX
Outputs: N/A
Any difficulties?: XXXXXXXXXXXXXXXXXX
********************************************/
#include <iostream>
using namespace std;

const int NUM = 8;
const int MAX = 8;

void printArray(const char ar[], int n)
{
  //This would come in handy
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
  cout << endl;
}

int main()
{
  //This program should still work even if we change NUM to 100 and change the matrix.
  //first [NUM] = i (y axis), second [NUM] = j (x axis)
  //       row column  
  int m[NUM][NUM] = {/*Person A*/{0, 1, 1, 0, 1, 0, 0, 0}, /*Person B*/{1, 0, 1, 0, 0, 1, 1, 0},/*Person C*/{1, 1, 0, 0, 1, 1, 0, 0},/*Person D*/{0, 0, 0, 0, 1, 0, 0, 0},/*Person E*/{1, 0, 1, 1, 0, 1, 0, 1},/*Person F*/{0, 1, 1, 0, 1, 0, 0, 0},/*Person G*/{0, 1, 0, 0, 0, 0, 0, 0},/*Person H*/{0, 0, 0, 0, 1, 0, 0, 0}};  //Mij where i is row and j is column
  //A(0), B(1), ....
  
  if(m[0][5] == 1)//check if A and F are friends
    cout << "Yes" << endl;
  cout << "No" << endl;
  
  //Show all friends of A
  char friends[MAX]; //store all A's direct friends
  //int size = 0;
  int size;
  int j;//column of graph
  int i;//row of graph
  char a;//ascii value of j
  
  for(size = 0, j = 0; j < NUM; j++)//go through the column that finds the following A's friends
    {
      if(m[0][j] == 1)//if inside the array, j = 1
	{
	  a = j + 65;//add the variable as a char
	  friends[size++] = a;
	}
      //Answer: B, C, E
    }
  printArray(friends, size);
  //refer A A's friends' direct friends 
  char refer[MAX]; //store reffered friends for A
  int size2 = 0;//size of the refer
  int f;//index of friends array
  int r;//index of refer array
  bool f1, r1;
  //I made one more function to keep the loop small
  for(f = 0; f < size; f++)//the keys to be used for friend array
    {
      i = friends[f] - 65;//get the char element to be filled as the row
      j = 1;//start on B because it's in the graph and stops until the 

      while(j < NUM)//the column going through the size
	{
	  if(m[i][j] == 1)//if the other parts of the columns are 1
	    {
	      a = 65 + j;
	      r = 0;//set the refer array to zero to traverse through the array
	      r1 = true;//for refer
	      f1 = true;//for friend
	      int l = 0;//only used for the below while loop
	      
	      while(l < size && f1 == true)//when it is in the loop for friends
		{
		  if(/*1 ==*/ friends[l] == a)//if it is the char
		    f1 = false;
		  l++;//increment the size of the 
		}
	      
	      if(f1 == true)//if the friends friend is 1
		{
		  if(size2 > 1)
		    {
		      while(r < size2 && r1 == true)//when it is in the loop for refer
			{
			  if(refer[r] == a)//if it is a friend or duplicate
			    r1 = false;
			  r++;//increment through the array
			}
		    }

		  if(r1 == true)
		    {
		      refer[size2++] = a;
		    }
		}
	    }
	  j++;
	}
    }
  printArray(refer, size2);
  /*for(i = 0; i < NUM; i++)
    {
    if(m[i][j] == 1)
    {
    a = j + 65;
    refer[size++] = a;
    }
    }*/
  
  //Answer: D, F, G, H  (don't repeat the same person. Order doesn't matter)
  
  int m2[NUM][NUM] = {{0, 1, 0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 1, 1, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0}, 
                      {1, 0, 1, 1, 0, 0, 1, 0}, {0, 0, 1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 1, 1, 0}};
 
  if(m2[0][5] == 1)
    cout << "Yes" << endl;
  cout << "No" << endl;
 
  char friends2[MAX]; //store all A's direct friends
 
  for(size = 0, j = 0; j < NUM; j++)
    {
      //size = 0;
      if(m2[0][j] == 1)
	{
	  char a = 65 + j;
	  friends2[size++] = a;
	}
    } 
  printArray(friends2, size);
  //A's friends -> B, D, and E
  
  char refer2[MAX]; //store reffered friends for A
  //the following will be the same as the other array
  for(f = 0; f < size; f++)
    {
      i = friends2[f] - 65;
      j = i;
      
      while(j < NUM)
	{
	  if(m2[i][j] == 1)
	    {
	      a = 65 + j;
	      r = 0;
	      r1 = true;
	      f1 = true;
	      int l = 0;

	      while(l < size && f1 == true)
		{
		  if(friends2[l] == a)
		    f1 = false;
		  l++;
		}
	      
	      if(f1 == true)
		{
		  if(size2 > 1)
		    {
		      while(r < size2 && r1 == true)
			{
			  if(refer2[r] == a)
			    r1 = false;
			  r++;
			}
		    }
		  if(r1 == true)
		    {
		      //cout << "hi " << endl;
		      refer2[size2++] = a;
		    }
		}
	      //cout << "hi " << endl;
	    }
	  j++;
	}
      //cout << "hi " << endl;
    }
  //friends referred to A-> C and G
  //cout << "hi " << endl;
  printArray(refer2, size2);
  
  return 0;
}


