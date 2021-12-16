/**************************************
Your name: XXXXXXXXXXXXXXXXXXXXXXXX
Your programmer number: XXXXXXX
Any difficulties?: XXXXXXXXXXXXXXXXXXX
**************************************/

#include <iostream>
using namespace std;

void swap(int& data1, int& data2)
{
  int temp = data1;//assign the first variable to an element
  data1 = data2;//assign the parameter to a different parameter to swap
  data2 = temp;//assign the second parameter to the first variable to swap elements
}

void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}

void insertionSort(int ar[], int n)
{
  //https://www.youtube.com/watch?v=ROalU379l3U
  //Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.
  /*  int key;//set to an element in the array
  for(int i = 1; i < n; i++)//goes through the array from left to right
    {
      key = i;//set the key to the index
      while(key > 0 && ar[key] < ar[key - 1])//if the index is greater than zero so it can traverse to the array and if the right element is less than the left element, then swap the elements 
      //while(key > 0 && ar[key - 1] > ar[key])//this is used if the right element is greater than the left element, but will not be used
	{
	  swap(ar[key], ar[key - 1]);//call swap; swapping the elements from the right element to the left element
	  key--;//decrement the key once the elements have been swapped. Without this decrement, the sorting will not happen for the loop to do its comparison
	}
	}*/
  
  for(int i = 1; i < n; i++)//right elements
    {
      int right = i;
      int left = i-1;
      while(ar[right] < ar[left])//left elements
	{
	  swap(ar[right], ar[left]);
	  right--;
	  left--;
	}
    }
}

void selectionSort(int array[], int N)
{
  //Implement selection sort by moving the smallest element to the beginning.
  //call swap
  //You can find more information in my homework document
  int lrgIndx;//set to the large index
  for(int last = N-1; last >= 1; last--)//used to set the last index of the array with the size and decrement once checking the elements to be swapped
    {
      lrgIndx = 0;//set to zero/assume its at zero
      for(int i = 1; i<= last; i++)//used to find the largest element and shifting it to the end of the array and continue to shift once it has been on the correct order
	{
	  if(array[i] > array[lrgIndx])//if the current element is larger, do not change and continue to check in the array
	    lrgIndx = i;//have the largeIndex equal to the index that has the larger element
	}
      swap(array[lrgIndx], array[last]);//swap the elements from the largest index's element with the last item of the array
    }
}
//Implemented by Kazumi Slott
//ar is an integer array of any size
//s is the size of the array
//For more info, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum" 
void bubbleSort(int ar[], int s)
{
  bool done = false; //set to false if there was swapping meaning not done yet.
  int last = s - 2; //last is the index of the left element in the last pair to be checked. In the first step, last should point to the second to last.       
  while(!done) //swapping required in the previous iteration or the first iteration starts                        
    {
      done = true; //no swapping has happened yet when a new step starts.      
      for(int i = 0; i <= last; i++) //check each adjacent pair of items in the unsorted part                     
        {
	  if(ar[i] < ar[i + 1]) //the pair is out of order                     
	    {
	      swap(ar[i], ar[i+1]);
	      done = false; //swapping required. needs to proceed to the next iteration.                            
	    }
        }
      last--; //the area to be checked shurinks down after each iteration      
    }//end of while                                                            
}

int partition(int a[], int start, int end)
{
  int pivot = end;//used to set the pivot to the end of the array when comparing elements inside the array
  int swapElem = start;//used for swapping in the array 
  for(int i = start; i <= pivot - 1; i++)//set a for loop where it starts from the start of the array and checks all the way until the end of the array
    {
      if(a[i] < a[pivot])//if the start of index in the array is less than the pivot of the array
	{
	  swap(a[swapElem], a[i]);//swap both elements based from the pivot
	  swapElem++;//move to the next index inside the array based on the pivot
	}
    }
  swap(a[swapElem], a[pivot]);//swap the elements from the start with the end if the element is greater than the pivot
  return swapElem;//return the element that has been swapped
//copy and paste partition() from your quickSort.cpp
}

void quickSort(int ar[], int start, int end)
{
  if(start < end)//If the partition has one element or none, return. In others words, if the partition has at least 2 elements, go inside the if.
    {
      int t = partition(ar, start, end);//call partition.
      quickSort(ar, start, t-1);//quickSort on the left partition
      quickSort(ar, t+1, end);//quixkSort on the right partition
   }
  //copy and paste quickSort() from your quickSort.cpp   
}

void merge(int ar[], int first, int last)
{
  int* temp = new int[last + 1];//make a dynamic array named temp that would fill numbers from left and right halves in order
  int mid = (first + last) / 2;//set the middle of the index based on the size of the array
  int right = mid + 1;//right finger points to the first slot of right half
  int left = first;//left finger points to the first slot of the left half
  int start = 0;//used for an initial value for a counter

  while(left <= mid && right <= last)//when the first half of the array is less than or equal to the middle index of the array and the second half of the array is less than or equal to the left index of the array
    {
      if(ar[left] <= ar[right])//if the left element is less than the right element
	temp[start++] = ar[left++];//set the array to the left for sorting
      else
	temp[start++] = ar[right++];//set the array to the right for sorting
    }

  while(left <= mid)//comparing the left (first half) with the middle
    {
      temp[start++] = ar[left++];//setting the original array with the temporary array that will be used to sort on the left side of the array
    }
  while(right <= last)//comparing the second half with the last index of the array
    {
      temp[start++] = ar[right++];//setting the original array with the temporary array that will be used to sort for the right side of the array
    }

  start--;//decrement once that part of the array/index was sorted and merged
  while(start >= 0)//when there are other parts of the array to be checked
    {
      ar[start + first] = temp[start];//starts to merge with the index that is being located 
      start--;//decrement once the element has been sorted at the correct spot
    }
  //copy and paste merge() from your mergeSort.cpp   
}

void mergeSort(int ar[], int first, int last)
{
  //int mid;
  if(first < last)//if the first element is less than the last element of the array
    {
     int mid = (first + last) / 2;//gets the mid value of the array
     mergeSort(ar, first, mid);//on left half
     mergeSort(ar, mid + 1, last);//on right half
     merge(ar, first, last);//merge the left and right halves into one sorted array
    }
  //copy and paste mergeSort()from your mergeSort.cpp   
}


