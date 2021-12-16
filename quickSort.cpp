/**********************************
Templated created by Kazumi Slott
CS311

Your name: XXXXXXXXXXXXXXXXXXXXXX
Your programmer number: XXXX
Any difficulties?: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
***********************************/
#include <iostream>
using namespace std;

/***********************************
The printAr function outputs the following elements that are inside of the array and uses a for loop to look at the indexes with the elements and outputs the following with the cout statements below.
***********************************/
void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}
/***********************************
In the swap function, it will have two passed by reference values since it will be swapping the left and right value. Since it will be use to partition, if the left value is not less than the pivot, then it will continue to find an element that is less than the pivot, then will swap the first element from the left to the element that is less than the pivot. And if there is an element that the pivot is not less than to inside of the array, then the pivot will switch spots with the first element it checks on. I tried using the function without the array, but it would not be swapping, but maybe it will, but in a different method that I can implement later in the future.
***********************************/
//It is good have the swap function so partition() won't get crowded. 
void swap(int a[], int a1, int b/*int& a, int& b*/)
{
  int temp;//sets the temporary variable to swap 
  temp = a[b];//set the temp to the array of the current index
  //where the swap begins
  a[b] = a[a1];//setting the current index with the index that it is being compared to from another function and will set the left value to the right value
  a[a1] = temp;//setting the right value with the left value
  /*
  int temp;//set a temporary variable to swap
  temp = a;//set the empty value with the left number
  //where the swap begins
  a = b;//set the original with left value to the right value 
  b = temp;//setting the right value with the left value
  */
}
/***********************************
The partition function is used to look over the arrays that it will be used to compare different elements inside of the array. This means that it will use the end or the pivot to compare the pivot and the current index at the start to see if the element will swap so for example is the pivot is 6 and the first element in the list is 10, then it will not swap since 10 is not less than 6, but if it reads an element less than 6, it will swap the first element 10 with the element less than 6, but the pivot stays there.
***********************************/
int partition(int ar[], int start, int end)
{
  int pivot = end;//this is used to set the pivot at the end of the array when comparing elements inside the array
  int swapIndex = start;//used for swapping purposes when going through the array
  for(int j = start; j <= pivot - 1; j++)//set a for loop where it starts from the start of the array and checks all the way until the end of the array 
    {
      if(ar[j] < ar[pivot])//if the index of the array is equal to the pivot or less than the pivot
	{
	  swap(ar, swapIndex, j);//swap(ar[i], ar[j]);//swaps both elements so it will be sorted
	  swapIndex++;//moves the left to the next index 
	}
    } 
  swap(ar, swapIndex, pivot);//swap the elements onto the correct order
  return swapIndex;//return the element to sort it into the correct order
//I have 3 variables: pivot, i and swap_index. You may have any local variables.
  //For implementation of this function, refer to my lecture notes "quick sort"
}
/***********************************
The quickSort function will be used recursively when looking from the start to finish inside of the array to sorting the elements in the correct order. While it is set to have an if statement, it is important to be used once the array is completed once it is sorted. Since the partition is used, it is going to sort by the order it is going to read the elements, and output the elements that are going to be shown in display. It will have two quickSort functions to get the left side of the array and get the right side of the array once it is completed on checking the sorting algorithm and once checking each part of the array, it will now finish the sorting and has the sorted array from there.
***********************************/
void quickSort(int ar[], int start, int end)
{
  //int t = partition(ar, start, end);//call partition.
  if(start < end) //If the partition has only one element or none, return. 
                   //In other words, if the partition has at least 2 elements, go inside the if.
            //use start and end to figure out.
    {
      int t = partition(ar, start, end);//call partition.
      quickSort(ar, start, t - 1);//quickSort on the left partition
      quickSort(ar, t + 1, end);//quickSort on the right partition
    }
  
}

int main()
{
  int ar[] = {15, 10, 5, 7, 1, 4, 12, 8, 6};
  quickSort(ar, 0, 8);
  printAr(ar, 9); //1 4 5 6 7 8 10 12 15

  int ar1[] = {1, 7, 5, 3, 9, 4};
  quickSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quickSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
