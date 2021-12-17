/****************
Your name: XXXXXXXXXXXXXXXX
Your programmer number: XXXXXX
Any difficulties?: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

SEARCH: Best Complexity: O(1), Worst Complexity: O(n) if tree is LL 
INSERT: Time Complexity: O(h) needs to go bottom
MaxLength: Time Complexity O(n) visit every node/count comparisons, Space O(h) 
REMOVE: Time Complexity O(h)
BFT: Time Complexity O(n) visit every node, Space O(n) for queue; DFT: Time Complexity O(n), Space O(n) for stack
*****************/

#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

//Check your stack_L_T.h if you don't know what to put here.
template <class T>//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
class BST;//used in order to access the private members

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template <class T>//???????????  //make it a templare class
class Node
{
  friend class BST<T>; //BST wants to access private members of Node
private:
  T el;
  Node* right;
  Node* left;
public:
  Node() {right = left = NULL;}; //default constructor. set right and left to NULL
  Node(const T& e){el = e;}; 
  T getEl() const {return el;} //returns el
};

template <class T>//Make it a template class
class BST
{
private:
  Node<T>* root;//???? root; //check stack_L_T.h to see how declared top
  void insertNodeR(Node<T>*& p, const T& e);
  void inOrderPrint(Node<T>* p);
  void preOrderPrint(Node<T>* p);
  void postOrderPrint(Node<T>* p);
  int getMaxLength(Node<T>* p);
  int getMinLength(Node<T>* p);
  int getNumNodes(Node<T>* p);
  Node<T>* searchR(Node<T>* p, const T& e);
  //bool searchR(Node<T>* p, const T& e);
  int getEvenNodes(Node<T>* p);
  void destroy(Node<T>* p);
  //You will need 10 private functions here.  WHY private?
 public:
  BST() {root = NULL;} //implement constructor here --> set the root to be NULL
 ~BST(); //destructor
  void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  int getMaxLength();
  int getMinLength();
  int getNumNodes();
  int getEvenNodes();
  Node<T>* searchI(const T& e);
  Node<T>* searchR(const T& e);
  //?????? searchR(const T& e);
};

//implement the member functions in the header if you are making a template class

//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T> 
BST<T>::~BST()
{
  destroy(root);//traverses through the tree to delete the root
}

template <class T>//template class function
void BST<T>::destroy(Node<T>* p) //private function. WHY?
{
  if(p == NULL)//if there are no roots to be checked
    return;
  destroy(p->left);//goes to the left side of the tree and deletes that side
  destroy(p->right);//goes to the right side of the tree and deletes that side
  delete p;//delete the pointer so it removes the element and the root/subroot inside the tree
  //destroy all nodes
}

//If you don't know how to make the insert function using recursion, check the following.
//CS211 Lecture Notes on BST – insertNode
//CS211 Lecture recording - Lecture 4/26(Mon) - DLL::deleteFront, BST::insert(), search()

template <class T>//used for the elements used in the tree
void BST<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

template <class T>//add a template class used for the insert
void BST<T>::insertNodeR(Node<T>*& p, const T& e) //private function. WHY? -- because it is using the root to direct the tree
{
  if(p == NULL)//if the tree is empty
    p = new Node<T>(e);//add the element passed in and make it the root of the whole binary tree
  else if(e < p->elem)//if the element inserted is less than the element of the root/subroot
    insertNodeR(p->left, e);//move to the left side of the tree
  else//e >= p->elem
    insertNodeR(p->right, e);//move to the right side of the tree 
}


//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
template <class T>
void BST<T>::insertNodeI(const T& e)
{
  Node<T>* newNode = new Node<T>(e);//make a new node.  Check stack_L_T.h to see how you made a new node.
  Node<T>* p = root;//set the pointer to the root
  Node<T>* parent = NULL; //points to the parent of p. 
  //move p to NULL
  while(p != NULL)
    {
      //parent points to the parent node while p points to the left or right child.
      parent = p; 
      if(e < p->el)//if the element passed is less than the element inside of the tree
	p = p->left;//goes to the left side of the tree
      else //p->el <= e -- if the element in the tree is less than or equal to the element passed
	p = p->right;//goes to the right side of the tree
    }

  if(parent == NULL) //tree is empty
    root = newNode;
  else if(e < parent->el) //insert a child as the parent's left child
    parent->left = newNode;
  else //parent->el <= e //insert a child as the parent's left child
    parent->right = newNode;
}

//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void BST<T>::inOrderPrint()
{
  inOrderPrint(root);
}

template <class T> //private function. WHY?
void BST<T>::inOrderPrint(Node<T>* p)
{
  if(p == NULL)//if there are no more elements to check
    return;
  inOrderPrint(p->left);//get the elements from the left
  cout << p->el << "-->";
  inOrderPrint(p->right);//get the elements from the right
}

template <class T>
void BST<T>::preOrderPrint()
{
  preOrderPrint(root);//pre means print parent->left child ->right child
}

template <class T>
void BST<T>::preOrderPrint(Node<T>* p) //private function. WHY?
{
  if(p == NULL)//if the tree is empty
    return;
  cout << p->el << "-->";
  preOrderPrint(p->left);//moves recursively to the left
  preOrderPrint(p->right);//moves recursively to the righ
}

template <class T>
void BST<T>::postOrderPrint()
{
  postOrderPrint(root);//post means left->right->parent last
}

template <class T>
void BST<T>::postOrderPrint(Node<T>* p) //private function. WHY?
{
  if(p == NULL)//if there are no more elements to check when traversing in the tree
    return;
  postOrderPrint(p->left);//moves to the left of the tree
  postOrderPrint(p->right);//moves to the right of the tree
  cout << p->el << "-->";
}

//If you don't know how to make this, check the following
//Lec Notes on BST :: Recursive Functions – getNumNodes
//CS211 Lecture recording - Lecture 4/30(Fri) - BST::getNumNodes, phase 3 of college

template <class T>
int BST<T>::getNumNodes()
{
  return getNumNodes(root);//used to return the amount of elements that are found inside of the tree
}

template <class T>
int BST<T>::getNumNodes(Node<T>* p) //private function WHY?
{
  if(p == NULL)//if there are no nodes inside of the tree, then return the value zero
    return 0;//returns zero if the tree was empty
  else
    return getNumNodes(p->left) + getNumNodes(p->right) + 1;//gets the nodes from the left side of the root added with the number of nodes from the right side of the root and added by one because it is the root, so in total that is the number of nodes that will be found inside of the tree
}

//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int BST<T>::getMaxLength()
{
  return getMaxLength(root);//used in order to access root
}

template <class T>
int BST<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  if(p == NULL)//if the tree is empty
    return 0;
  /*else if(p)
    {
    return 1;
    }*/
 else//if there are nodes inside of the tree
   {
     int left, right;
     left = getMaxLength(p->left) + 1;//includes the elements from the left side of the tree and in the root
     right = getMaxLength(p->right) + 1;//includes the elements from the right side of the tree and in the root
     if(left >= right)//if the left side has the greatest number of elements than the right side
       return left;//returns the left side of the tree
     if(right > left)//if the right side has the greatest number of elements than the left side
       return right;//returns the right side of the tree
   }
}


template <class T>
int BST<T>::getMinLength()
{
  getMinLength(root);//in order to use the root
}

template <class T>
int BST<T>::getMinLength(Node<T>* p) //private function. WHY?
{
  if(p == NULL)//if there are no nodes inside of the tree
    return 0;//returns zero nodes
  else
    {
      int left, right;
      left = getMinLength(p->left) + 1;//the left side of the tree
      right = getMinLength(p->right) + 1;//the right side of the tree
      if(left < right)//if the left side of the tree is less than the right side of the tree
	return left;//returns the left side of the tree
      if(right <= left)//if the right side of the tree is less than or equal to the left side of the tree
	return right;//returns the right side of the tree
    }
}
                   
//This function will return the number of even elements
template <class T>                                                                                    
int BST<T>::getEvenNodes()                                                   
{                                                     
  getEvenNodes(root);
}                                                                           
                         
template <class T>          
int BST<T>::getEvenNodes(Node<T>* p) //private function. WHY?  
{        
  int num = 0;//used to count the number of elements that will be even
  if(p == NULL)//if it is empty or there are no elements that is an even number
    return 0;//zero to show that there are no elements
  else
    {
      if((p->el) % 2 == 0)//check the element to see if it is even
	num++;//increment the count to see that the element in the tree is an even number
      return num + getEvenNodes(p->left) + getEvenNodes(p->right);//adds up the following elements from the left and right and adds in the count of what numbers are even
    }
}                                    
//Make a search function using iteration. Return the pointer to the node having e
//return NULL if e is not found.
//return the pointer to the node with e
//return NULL if e is not found
template <class T>
Node<T>* BST<T>::searchI(const T& e)
{
  Node<T>* p = root;//set the pointer to root
  while(p != NULL)//while the pointer is not done searching inside of the tree
    {
      if(p->el == e || p == NULL)//if the element is found/not found
	return p;//ensures that the tree has fully been checked and that it returns where that it is pointed to
      else if(p->el > e)//if the element inside of the tree is greater than the passed in element
	p = p->left;//shifts to the left
      else//p->el <= e -- if the element in the tree is less than or equal to the passed in element
	p = p->right;//shifts to the right
    }
  //Where do you return NULL? 
}



//Make a search function using recursion.
//Return the pointer to the node having e or return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchR(const T& e)
{
  return searchR(root, e);
}

template <class T>
Node<T>* BST<T>::searchR(Node<T>* p, const T& e) //private function. WHY?
{
  if(p == NULL)//if the element is not in the binary search tree
    return NULL;//once the element wasnt found
  else
    {
      if(p->el == e)//if it is a match in the tree
	return p;//once the element was found
      else if(e < p->el)//if the element is less than the element in the tree
	searchR(p->left, e);//left
      else if(e > p->el)//if the element is greater than the element in the tree
	searchR(p->right, e);//right
    }
}

#endif
