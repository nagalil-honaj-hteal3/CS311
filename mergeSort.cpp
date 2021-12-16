/**********************************
Your name: XXXXXXXXXXXXXXXXXXXXXXXX
Your programmer number: XXXXX
Any difficulties?: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Best Complexity: O(NlgN)
Worst Complexity: O(NlgN)
Auxillary Space: O(n)
Space/Runtime Stack: O(lgN)
Not In-place; stable
***********************************/
#include <iostream>
using namespace std;

/***********************************
This print array is used to output the following elements in the sorted algorithm from the array and will have a space to separate the following elements.
***********************************/
void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}
/***********************************
The merge function is used to scan the array and split it into twos, to get the left side and right side, and use the left and right fingers to initialize the locations of the array. It would be split by having a middle varaiable that would half the array and continue to half until the size of the array left to compare is 1, it will merge the following elements into a dynamic array, which would be a new array with a new sorting array from least to greatest. Once it completes merging, it will go back to the other elements that are not merged and will continue the same process until all the elements are stored into the temp array in the correct order.
***********************************/
void merge(int ar[], int first, int last)
{
  int* temp = new int[first + last];//make a dynamic array named temp that would fill numbers from left and right halves in order
  int mid = (first + last) / 2;
  int right = mid + 1;//right finger points to the first slot of right half
  int left = first;//left finger points to the first slot of the left half
  int start = 0;//used for an initial value for a counter

  while(left <= mid && right <= last)//when the first half of the array is less than or equal to the middle index of the array and the second half of the array is less than or equal to the last index of the array
    {
      if(ar[left] <= ar[right])//if the left element is less than the right element
	temp[start++] = ar[left++];//set the array to the left, if it needs sorting
      else
	temp[start++] = ar[right++];//set the array to the right, if it needs sorting
    }
  while(left <= mid)//comparing the left (first half) with the middle
    {
      temp[start++] = ar[left++];//setting the original array with the temporary array that will be used for sorting on the left side
    }
  while(right <= last)//comparing the second half with the last index of the array
    {
      temp[start++] = ar[right++];//same as the while loop above but with the right side/second half of the array
    }
  start--;//decrement once that part of the array/index was sorted and merged
  while(start >= 0)//when there are other parts of the array to be checked 
    {
      ar[start + first] = temp[start];//starts to merge with the index that is being located 
      start--;//decrements once the element has been sorted at the correct spot
    }
  //For implementation of this function, refer to my lecture notes "merge sort"
  //If you are using a different technique, I assume you cheated and will give you zero points.
}
/***********************************
The mergeSort function is used to be set recursively when going through the array and will check each sides of the array to get the element from the merge function once it checks the position of the sorted array. It will have a variable called mid that will be used to locate the middle of the array and set it for the two following mergeSort functions to have the elements be sorted out. Once completed with one part of the portion, it will continue to merge until every part of the array has been sorted completely.
***********************************/
void mergeSort(int ar[], int first, int last)
{
  int mid;
  if(first < last)//if the first element is less than the last element of the array
    {
      mid = (first + last) / 2;//get the mid value of the array
      mergeSort(ar, first, mid);//on left half
      mergeSort(ar, mid + 1, last);//on right half
      merge(ar, first, last);//merge the left and right halves into one sorted array
    }
  //For implementation of this function, refer to my lecture notes "merge sort"
}

int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
