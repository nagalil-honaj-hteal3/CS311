/*****************************************
Your name: XXXXXXXXXXXXX
Your programmer number: XXXXX
Any difficulties?: XXXXXXXXXXXXXXXXXX

Worst Complexity: O(NlgN)
Space/Auxillary: O(1)
In-place; Not stable
*******************************************/
#include <iostream>
using namespace std;

//print an integer array of size n
void print(int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
  cout << endl;
}

//called from max_heapify and heapSort
/******************************************************************************
In the exchange function, it is similar to the swap function and used three parameters including ar[], which will be used for an array to let the two passed in integers to have access with the elements inside of the array, x is going to be the passed in value of the original root that is set on the heap located at index 0, and y will be the passed in value of the largest element that is found inside of the array.
******************************************************************************/
void exchange(int ar[], int x, int y)
{
  int temp = ar[x];//set a variable for the largest element
  ar[x] = ar[y];//swap the highest element with the original root
  ar[y] = temp;//the root will now be the highest element that was checked
  //I have 3 lines of code here.
}

/******************************************************************************
In the max_heapify function, it will look through the array to see if the root is greater than all the elements inside of the array when pushed in the first index. It will check the following if conditional statements just by checking the elements inside of the array to counter the root element by being greater than the root. This is to mainly check the subroots of the root to make sure that an element is not less than the root, and to also correct the violation of that subtree's root.
******************************************************************************/
//turn a heap into a max-heap rooted at i, assuming the left and right subtrees are already max-heaps.
//n is the size of the heap
void max_heapify(int ar[], int n, int i)
{
  
  int l = 2 * i + 1; //the index of the left child of i
  int r = 2 * i + 2; //the index of the right child of i
  int largest = i;//used to initialize the largest root in the heap

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range. 
  //Recall how you found the largest value among 3 values in CS111.
  //I have 6 lines of code here. You can have more or less.

  if(l < n && ar[l] > ar[largest])//comparing if the left child is larger than the root. The first condition asks if the left is less than the size of the heap. The second condition asks if the element of the left is greater than the initial array of the root element.
    {
      largest = l;//the largest side would be set as the left child
    }
  if(r < n && ar[r] > ar[largest])//comparing if the right child is larger than the root. The first condition asks if the right is less than the size of the heap. The second condition asks if the element from the right is greater than the initial root
    {
      largest = r;//the largest side would be set as the right child
    }
  //The largest is either the right or left child. In other words, it is not the root at i.
  if(largest != i)//if the largest is not a root
    {
      exchange(ar, i, largest);//exchange the 2 values -- swap the root with the largest value -- make sure to not pass in the integer values of the index as an element (ar[i]) only as the integer
      max_heapify(ar, n, largest);//There might be a violation at the position that was exchanged. Call max_heapify to fix it. Will be used recursively****
    }
}
/******************************************************************************
The build_max_heap function is used for splitting up the children from the root from left to right to check which elements are going to be swapped from its respective branches. This function is very imperative for this whole program to assign the correct roots for holding the heap. This will be used to read from the bottom since it will keep checking the root's subroots and will work its way up once the array is sorted with its respectful root, it will be in the correct spot inside of the array.
******************************************************************************/
//turn the entire array/tree into a max heap rooted at 0
//n is the size of the array
void build_max_heap(int ar[], int n)
{
  //2 lines of code in this function
  for(int i = n/2; i >= 0; i--)//each non-leaf node -- this loop will split the heap in half to read the children of the array to check which element has to be swapped from the root inside of the array, if and only if the element of the array is smaller than the largest element.
    {
      max_heapify(ar, n, i);//call max_heapify (turn the smallest subtrees into max-heaps and work your way up)
    }  
}

/******************************************************************************
The heapSort function will be used to read the array of the elements that are either sorted and unsorted based from the build_max_heap function. It will be using a while loop to check when the size, which is n - 1 because it is the size of the array, and once it is greater than or equal to zero, it will finish the sorting algorithm. Inside of the loop it will be swapping elements with the first index (max element) to the last since it will be going from ascending order and will continue to read the array with using the max_heapify function. 
******************************************************************************/
//a is an unordered list to start with
//use max_heapify to sort a
//n is the size of the array
void heapSort(int a[], int n)
{
  //I have 6 lines of code in this function. You can have more or less.
  //build max heap from an unordered list
  build_max_heap(a, n);//call build_max_heap
  int size = n - 1; //size of the unsorted portion of the array
  
  while(size >= 0) //repeat until heap is empty
    {  
      exchange(a, size, 0);//swap max element with last element - max element is at the end of the array
      max_heapify(a, size, 0);//calling this function to get the violations and read from the subroots
      size--;//decrement the size by one
      //discard the last node from heap
      //root may violate max-heap property, but children are max heaps. run max_heapify to fix it.
    }
}

//this function corrects a violiation of max heap by bubbling up an element at i                             
//a is a heap                                                                                                
void bubbleUp(int a[], int i)
{
  //Write this function after you made insert() and while you are making remove.
  int parent = (i-1) / 2;
  //int el = a[i];//element inside of the array
  if(a[i] > a[parent])//if the current index of that element is greater than the parent's then shift
    {
      while(a[i] >= a[parent])//when used to exit the loop once the subroot is less than the parent 
	{
	  exchange(a, parent, i);//swap the elements
	  i = parent;//set to the parent once its been swapped -- index set to the location of parent
	  parent = (i-1) / 2;//cycle this function once the new parent index has been set for i
	  //build_max_heap(a, i);
	}
    }
}
//a is a max heap                                                              
//cap is the capacity of the heap
//n is the number of elements the heap currently has before insertion
//el is the new element to be inserted                                
void insert(int a[], int cap, int& n, int el)
{
  //refer to lecture notes
  //write this function without calling bubbleUp first. When you work on remove, you will see you will
  //have to have the same code there. Move the code into bubbleUp and call it.
  //size = n + 1;
  //bubbleUp(a, el);//sends the element to be inserted to the 
  if(n < cap)//size is less than capacity 
    {
      a[n] = el;//set the element of the size of array to the element
      n++;//increment the size for insertion
      int parent = (n-1) / 2;
      
      if(a[n-1] > a[parent])//if the parent element is less than the current element -- which will be used to bubbleUp since it will change the root/subroot of the heap
	bubbleUp(a, n-1);//the n-1 is the index
	/*while(a[parent] < a[n-1])
	{
	  exchange(a[parent], a[n-1]);
	  max_heapify(a, n, parent/2 - 1);
	  }*/
    }

}

//a is a max heap                                                                                            
//n is the number of elements the heap currently has before deletion, then decrememted after deletion                                         
//el is the element to be removed. Assume all elements are unique                                     
void remove(int a[], int& n, int el)
{
  //refer to lecture notes
  //Call bubbleUp and max_heapify instead of coding the same things.
  //int del = -1;
  int i = 0;
  int left, right, parent;//used for the roots/subroots of heap
  //for(int i = 0; i < n; i++)
  while(i < n && a[i] != el)//searching the element in the heap to delete
    i++;
  if(a[i] == el)//if the element inside of the array is equal to the element passed to be deleted
    {
      exchange(a, n-1, i);//swap the current element with last element
      n--;//decrement the heap by one since we are removing an element inside of heap

      left = (2*i) + 1;//left child
      right = (2*i) + 2;//right child
      parent = (i-2) / 2;//root for the two childs in a heap
    
      if(a[i] <= a[left] || a[i] <= a[right])// when the current index deleted is less than or equal to the left or right
	max_heapify(a, n, i);//checking the max element from that heap
      else if(a[i] > a[parent])//if the current element is greater than the parent element
	bubbleUp(a, i);//moving up in the heap to see the elements
      
    }
  /*if(del != i)//if the variable is 
    {
      int element = a[del];
      int array = a[n-1];
      exchange(a[del], a[n-1]);//swap the elements from 
      n--;

      int parent = del;
      max_heapify(a, n, del);
    }
  
  bubbleUp(a, el);
  max_heapify(a, n, el);
  el = a[n];
  delete el;
  */
}

int main()
{
  int ar[10] = {11, 3, 4, 5, 7, 19, 20, 2, 8, 1};
  int ar2[10] = {5, 3, 10, 4, 7, 9, 11, 2, 8, 1};
  int ar3[2] = {2,1};

  cout << "testing max_heap rooted at index 3" << endl;
  max_heapify(ar, 10, 3); //max-heapify rooted at index 3                                                                                      
  print(ar, 10);//11 3 4 8 7 19 20 2 5 1  --> the tree rooted at 3 is now a max-heap (8 is at root. 2 and 5 are its children)                  

  cout << endl << "testing max_heap rooted at index 1" << endl;
  max_heapify(ar, 10, 1); //max-heapify rooted at index 1                                                                                      
  print(ar, 10);//11 8 4 5 7 19 20 2 3 1  --> the tree rooted at 1 is now a max-heap (8 is at root. 5 and 7 are its children. 5's children are 2 and 3)                                                                                                                                   
  cout << endl << "testing build_max_heap" << endl;
  build_max_heap(ar, 10);
  print(ar, 10);//20 8 19 5 7 11 4 2 3 1                                                                                                       

  cout << endl << "testing heapSort" << endl;
  heapSort(ar2, 10);
  print(ar2, 10);//1 2 3 4 5 7 8 9 10 11                                                                                                       

  cout << endl << "testing heapSort" << endl;
  heapSort(ar3, 2);
  print(ar3, 2);//1 2                                                                                                                          
  
  cout << "testing insert" << endl;
  int ar4[15] = {20, 8, 19, 5, 7, 11, 4, 2, 3, 1, -1, -1, -1, -1, -1}; //max heap with 10 elements already   
  int n = 10; //n is the number of elements in the heap                                                      
  insert(ar4, 15, n, 15); //trying to insert 15                                                              
  print(ar4, n); //20 15 19 5 8 11 4 2 3 1 7                                                                 
  
  cout << "testing remove" << endl;
  remove(ar4, n, 15); //trying to remove 15                                                                  
  print(ar4, n);//20 8 19 5 7 11 4 2 3 1                                                                     

  return 0;
}

