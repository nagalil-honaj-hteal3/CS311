/**********************************
CS311 Kazumi Slott

Your name: XXXXXXXXXXXXXXXXXX
Your program number: XXXX
Describe any difficulties here: XXXXXXXXXXX
*********************************/

/********************************************************************
//Make your own test client and test your functions thorougly.
//You will submit this header file only. My test client will test your functions.
********************************************************************/


//What is the runntime complexity of this algorithm? O(n^3)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above.
/********************************************************************
In algoA, this function is used to compute the sum of every subarray that is tracked and making sure if there is a sum with a higher max value. The sum will continue to compare with other sums to see which sum has the highest max value and returns that integer element. Based on the implementation that I created on the function, it looks like the time complexity is n^3 because with the following loops, counting the loops doesn't make the big-O to be n^3, but looking at the assignment for having the size be declared with the different int variables, it does not specifically clarify how long the size is within the array, so it can be hard to verify how vast the elements are within the array.
********************************************************************/
int algoA(const int a[], int sz)//Don't change the function headers
{
  int sum1 = 0;//the new sum to be totaled up
  int sum = 0;//declare the sum as 0 -- max value
  for(int s = 1; s <= sz; s++)//used to increment the size of the subarray by one to look at the other subarrays once it is done traversing
    {
      for(int i = 0; i < sz; i++)//to look into the array and shift the index of once the subarray is completed inside of the array's index.
	{
	  for(int j = i; j <= s-1; j++)//this traverses with the array from the subarray to look at the elements inside of the subarray.
	    {
	      sum1 += a[j];//this collects the sum with what is computed and 
	    }
	  if(sum1 >= sum)//if the new sum that was computed has a large maximum sum than the original sum
	    sum = sum1;//sum has to be set to the newest sum that was recorded.
	  sum1 = 0;//resets it to zero to revisit the elements of the subarray.
	}
    }
  return sum;//returns the highest value of sum to 
}

//What is the runntime complexity of this algorithm? O(n^2)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
/********************************************************************
In algoB, this function is as similar to algoA, however the difference between this algorithm and with algoA is that each of the subarray has to start at index 0. With the following function that I implemented, based on the following, I assume that it will be n^2 because there are two different variables that are assigned and assuming that the size changes, the worst case for the function is that it will loop around twice to getting the element within the subarray and in the array to increment once the index is completed to grab. 
********************************************************************/
int algoB(const int a[], int sz)
{
  //int sum1;//used to compare another sum
  int max = 0;//max sum
  int sum, i;
  for(sum = 0, i = 0; i < sz; i++)//s is used for the subarray to record the sum of the array; everything in accordance to i, it will be used to invrement the index once the subarray has been done 
    {
      for(int j = i; j <= sz; j++)//The index will be starting at zero in accordance with i which is part of the array, and will be having a comparison with size to complete the run inside of the subarray.
	{
	  sum += a[j];//gets the subarray and records the sum of the elements stored within the subarray and will be used to compare the other sums on what is the highest value of max sum.
	  if(sum >= max)//if the newest sum is greater than or equal to temporary sum
	    max = sum;//set the temp sum to the original sum in order to return the element that was stored
	}
      sum = 0;//this is to reset the value in order to view on the next index
    }
  return max;//to return the value that has been totaled for the high max value
}

//What is the runntime complexity of this algorithm? O(n)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
/********************************************************************
In algoC, this function will compute the sums of all subarrays starting from index 0 and if the sum is negative, the sum of all subarrays starting from the next index in the array will start computing. I am unsure if the implementation on this function is correct, but it mentions that using algoB is what is crucial to adding the rest of the elements within the subarrays and arrays, but when focusing on the time complexity, it will most likely be relied on one a linear type of motion when it is going to find the subarrays within the array. It also has one for loop that assigns the index to only the size and checks on the length for how much indexes it has to view on once it gets passed onto the function to get access of the subarrays.
********************************************************************/
int algoC(const int a[], int sz)
{
  int sum = 0;//sets sum to be zero -- or max
  int sum1 = 0;//the sum within the subarray
  int s;//the start index for intitalizing the sum
  for(int i = 0; i < sz; i++)//iterates when going through the array
    {
      sum1 += a[s];//add all values from the subarray -- the AlgoB efficiency note
      if(sum1 < 0)//if the sum is negative, start computing the sum of all of sum1 
	{
	  s = i++;//move the initial start to the next index of that array
	  sum1 = 0;//have it set to zero once that array has been summed up
	}
      //efficacy note from algoB
      //algoB(i, sz);//goes to this function to repeat the sum when starting from index 0
      if(sum1 >= sum)//if the sum computed is larger than the initial max sum
	sum = sum1;//it becomes the max sum
    }
  return sum;//returns the array of the index within algoB
}
