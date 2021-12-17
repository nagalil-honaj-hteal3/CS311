/****************
Your name: XXXXXXXXXXXXXXXXXXXXX
Your programmer number: XXXX
Any difficulties?: XXXXXXXXXXXXXXXXXXXXXX


Insert Time Complexity O(lgN)
*****************/

#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>//for the BFT -- Breadth First Traversal Print Function
//#include <stack>//for the DFT -- Depth First Traversal Print Function
using namespace std;

//Check your stack_L_T.h if you don't know what to put here.
template <class T>//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
class AVL;//used in order to access the private members

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template <class T>//???????????  //make it a templare class
class Node
{
  friend class AVL<T>; //AVL wants to access private members of Node
private:
  T el;
  Node<T>* right;
  Node<T>* left;
  Node<T>* up;
  int BF;
public:
  Node() {right = left = up = NULL; BF = 0;}; //default constructor. set right and left to NULL
  Node(const T& e){el = e; /*right = left = up = NULL; BF = 0;*/}; 
  T getEl() const {return el;} //returns el
};

template <class T>//Make it a template class
class AVL
{
private:
  Node<T>* root;//???? root; //check stack_L_T.h to see how declared top
//void insertNodeR(Node<T>*& p, const T& e);
  void inOrderPrint(Node<T>* p);
  void destroy(Node<T>* p);
  int getMaxLength(Node<T>* p);
  Node<T>* rightRotation(Node<T>* P);//NEW
  Node<T>* leftRotation(Node<T>* P);//NEW
  void balanceTree(Node<T>* newNode);//NEW
  Node<T>* updateBF(Node<T>* Q);//NEW
//void preOrderPrint(Node<T>* p);
//void postOrderPrint(Node<T>* p);
//int getMinLength(Node<T>* p);
//int getNumNodes(Node<T>* p);
//Node<T>* searchR(Node<T>* p, const T& e);
  //bool searchR(Node<T>* p, const T& e);
  //int getEvenNodes(Node<T>* p);
//void remove(Node<T>*& p); //private function
//You will need 10 private functions here.  WHY private?
public:
  AVL() {root = NULL;} //implement constructor here --> set the root to be NULL
 ~AVL(); //destructor
//void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void BFTprint();
  int getMaxLength();
//void preOrderPrint();
//void postOrderPrint();
//int getMinLength();
//int getNumNodes();
//int getEvenNodes();
//Node<T>* searchI(const T& e);
//Node<T>* searchR(const T& e);  //?????? searchR(const T& e);
//bool remove(const T& e);
//void DFTprint();
};

//implement the member functions in the header if you are making a template class

//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T> 
AVL<T>::~AVL()
{
  destroy(root);//traverses through the tree to delete the root
}

template <class T>//template class function
void AVL<T>::destroy(Node<T>* p) //private function. WHY?
{
  if(p == NULL)//if there are no roots to be checked
    return;
  destroy(p->left);//goes to the left side of the tree and deletes that side
  destroy(p->right);//goes to the right side of the tree and deletes that side
  delete p;//delete the pointer so it removes the element and the root/subroot inside the tree
//destroy all nodes
}

//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.

template <class T>
void AVL<T>::insertNodeI(const T& e)
{
  Node<T>* newNode = new Node<T>;//make a new node.  Check stack_L_T.h to see how you made a new node.
  newNode->el = e;//set the passed element with the newNode el
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
    {
      root = newNode;//set the root with the added new node with an element 
      //balanceTree(root);//call the balanceTree func when a new node was added
    }
  else if(e < parent->el) //insert a child as the parent's left child
    {
      parent->left = newNode;//set the parent's left with an added node
      newNode->up = parent;//point the new node's up with the parent since it is new
      balanceTree(newNode);//set that part of the tree with new node added
    }
  else //parent->el <= e //insert a child as the parent's right child
    {
      parent->right = newNode;//set the parent's right child as the added node
      newNode->up = parent;//point the new node's up with the parent
      balanceTree(newNode);//set that part of the tree with new node added
    }
}

//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void AVL<T>::inOrderPrint()
{
  inOrderPrint(root);
}

template <class T> //private function. WHY?
void AVL<T>::inOrderPrint(Node<T>* p)
{
  if(p == NULL)//if there are no more elements to check
    return;
  inOrderPrint(p->left);//get the elements from the left
  cout << p->el << " " << p->BF << "-->";
  inOrderPrint(p->right);//get the elements from the right
}

template <class T>
void AVL<T>::BFTprint()//this function is used for printing out nodes based on its respective level or depth.
{
  //Use the library's queue.
  //Make sure to include <queue> at the top
  Node<T>* temp = root;//set the root to a p pointer
  queue<Node<T>*> q;//create a queue obj of pointers to Nodes
  //if(root == NULL)//if the BST is empty
  //return;
  if(temp != NULL)//if the tree is not empty
  //{
    q.push(temp);//push root in the queue
  //NOTICE
  while(!q.empty())//if the AVL is not empty
    {
      temp = q.front();//front() gives you the front element but it doesn't remove it from the queue
      if(temp != NULL)//if the tree is not empty
	{
	  if(temp->up == NULL)//if the up pointer is empty
	    cout << temp->el << " " << temp->BF << " -->";//outputs the element and the balance factor that is in the tree
	  else//if it is not empty -- the up pointer
	    cout << temp->el << " " << temp->BF << " " << temp->up->el << "-->";//used to output the elements that are from the root and upper to check the balance factor within the avl tree
	  q.pop();//pops the top element of the tree
	  
	  if(temp->left != NULL)//if the root's left child has any pointers open
	    q.push(temp->left);//push to the left side
	  if(temp->right != NULL)//if the root's right has any nodes nodes available
	    q.push(temp->right);//push to the right side
	}
      //q.pop();//pop() remmoves the front element
    }
  //}
}

template <class T>
void AVL<T>::balanceTree(Node<T>* newNode)//NEW FUNC -- newNode points to the newly added node
{
  Node<T>* vNode = updateBF(newNode);//call updateBF()
  if(vNode == NULL)//if updateBF() returns NULL, no need to balance the tree
    {
      return;//if the tree is already balanced
    }
  else if(vNode != NULL) //not balanced
      //There are four types of violations -- LL, LR, RL, RR -- and for each rotation, call rotateRight(), rotateLeft() or both.
    {
      Node<T>* parent = vNode->up;//set the parent of the vNode's up pointer
      Node<T>* temp;//needed when having two rotations on the violations
      bool rightChild;//the location for where the vNode will come from (parent->right) 

      if(parent != NULL)
	{
	  if(parent->right == vNode)//if the right is the violation to update the balance factor
	    rightChild = true;//that the violation is found on the right
	  else//parent->left == vNode
	    rightChild = false;//violation is found on the left
	}
      
      if(vNode->BF == 2 && vNode->left != NULL && vNode->left->BF == 1)//LL violation -- if(P->BF == 2 && P->left != NULL && P->left->BF == 1)
	{
	  //right rotation must be made when it is this violation
	  vNode = rightRotation(vNode);
	}
      else if(vNode->BF == 2 && vNode->left != NULL && vNode->left->BF == -1)//LR violation
	{
	  //makes a left then right rotation for this violation
	  temp = leftRotation(vNode->left);//have the vNode point to the left to make the rotation
	  temp->up = vNode;//have that node's up be the violation
	  vNode->left = temp;//let the violation node point directly to the temp
	  //set the vNode to the right rotation after the left rotation
	  vNode = rightRotation(vNode);
	}
      else if(vNode->BF == -2 && vNode->right != NULL && vNode->right->BF == 1)//RL
	{
	  //makes a right then left rotation
	  temp = rightRotation(vNode->right);
	  temp->up = vNode;
	  vNode->right = temp;
	  //left rotation once the right rotation is completed
	  vNode = leftRotation(vNode);
	}
      else if(vNode->BF == -2 && vNode->right != NULL && vNode->right->BF == -1)//RR
	{
	  //make a left rotation when its this violation
	  vNode = leftRotation(vNode);
	}

      if(parent == NULL)//if the root was the violation in the AVL tree
	{
	  vNode->up = NULL;//set this to be empty
	  root = vNode;//since it was at the root, this will be the new root of the AVL tree
	}
      else
	{
	  if(rightChild == true)//if the vNode's root points to a new child
	    parent->right = vNode;
	  //same as the above but for the left
	  else
	    parent->left = vNode;
	  //update the up pointer once it has been made
	  vNode->up = parent;
	}      
    }
}

template <class T>
Node<T>* AVL<T>::rightRotation(Node<T>* P)//NEW
{
//Don't forget to change up and BF as well appropriate pointers.
//This function returns the new root.
/*  Node<T>* temp = P->right;//have a pointer point to the right of P/root
  P->right = temp->left;//set the right of P/root to the left of temp -- swap
  temp->left = P;//have the left point towards the P/root
  //getMax
  return temp;//return the new root once the right rotation is complete.*/
  Node<T>* L = P->left;//have it point to the left to start the rotation since it will shift right
  //L->up = NULL;//since this is a new node, it will need the up node to be stored in an empty space
  L->up = P->up;
  Node<T>* R = L->right;//have it point to the parent's left's right to pointing to the child

  L->right = P;//assign the root or parent as the root or parent to get the next rotation
  P->up = L;//set the root/parent's up with the root's left
 
  P->left = R;//have the root's left equal the the tempR
  if(R != NULL)
    R->up = P;//have that point to the root 

  if(L->up != NULL)
    L->up->right = L;

  P->BF = getMaxLength(P->left) - getMaxLength(P->right);
  L->BF = getMaxLength(L->left) - getMaxLength(L->right); 
  
  return L;//returns the rotation of the right
}

template <class T>
Node<T>* AVL<T>::leftRotation(Node<T>* P)//NEW
{
  //Don't forget to change up and BF as well appropriate pointers.
  //This function returns the new root.
  /*Node<T>* temp = P->left;//point it to the left side of the P/root
  P->left = temp->right;//set the left of P/root to the right of temp so it swaps
  temp->right = P;//set the right part to the root/P
  return temp;//return the new root once the left rotation is complete.*/
  Node<T>* R = P->right;//point it to the right of the root to start the rotation that will shift to the left
  R->left = P;//as different with the right rotation, it would be logical to have set the parent/root with the parent's right's left as the parent
  
  R->up = P->up;//have the parent's right's up be equal with the root's up
  P->up = R;//set the root's up with the parent's right
  P->right = NULL;
  
  if(R->up != root)
    R->up->right = R;
  R->up->left = R;
  //  R->up->right = R;
  //update the balance factor
  R->BF = getMaxLength(R->left) - getMaxLength(R->right);
  P->BF = getMaxLength(P->left) - getMaxLength(P->right);

  return R;
}

template <class T>
Node<T>* AVL<T>::updateBF(Node<T>* Q)//NEW
{
  Node<T>* vNode = NULL;
  Node<T>* parent = NULL;//parent of Q

  if(Q->up != NULL)//if the passed in node is not empty
    parent = Q->up;
    
      if(Q->el < parent->el && Q == parent->left)//if the passed in root is equal to the left child
	{
	  parent->BF++;//increment the balance factor by one
	}
      else//if the passed in root is equal to the right child
	{
	  parent->BF--;//decrement the balance factor by one
	}

      while(parent != root && (parent->BF > -2 && parent->BF < 2))
	{
	  Q = parent;
	  parent = parent->up;
  
	  if(Q->BF == 0)
	    return vNode;

	  if(Q->el < parent->el && Q == parent->left)
	    parent->BF++;
	  else
	    parent->BF--;
	}
      
      if(parent->BF == 2 || parent->BF == -2)
	vNode = parent;
      return vNode;
}
  /*
  if(Q == P->left && Q->el < P->el)//if Q is the left child of P or element of Q is less than the P element
    P->BF++;//adds onto the balance factor or the left of the tree to inform the user that it increased by one or LEFT HEAVY
  else//Q == P->right && Q->el > P->el
    P->BF--;//subtracts onto the balance factor or the right of the tree to inform the user that it subtracted by one or RIGHT HEAVY
  
  while(P != root && (P->BF > -2 && P->BF < 2))//if the balance factor is finding violations for the AVL tree
    {
      Q = P;
      P = P->up;//set p as the parent's p
      
      if(Q->BF == 0)//if the balance factor is zero
	return V;//the tree is already balanced after insertion therefore the child under this node (the new inserted node) completed this parent node.
      if(Q == P->left && Q->el < P->el)//if the Q pointer is right heavy
	P->BF++;//shift it to the left
      else//if the Q pointer is left heavy
	P->BF--;//shift it to the right
    }
  
  if(P->BF == -2 || P->BF == 2)
    V = P;//set the violation with P
  return V;//return the pointer of the violation or return NULL if there is no violation
  */

//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int AVL<T>::getMaxLength()
{
  return getMaxLength(root);//used in order to access root
}

template <class T>
int AVL<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  if(p == NULL)//if the tree is empty
    return 0;
  //else if(p)
    //{
      //return 1;
    //}
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
//If you don't know how to make the insert function using recursion, check the following.
//CS211 Lecture Notes on BST – insertNode
//CS211 Lecture recording - Lecture 4/26(Mon) - DLL::deleteFront, BST::insert(), search()
/*
template <class T>//used for the elements used in the tree
void AVL<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

template <class T>//add a template class used for the insert
void AVL<T>::insertNodeR(Node<T>*& p, const T& e) //private function. WHY? -- because it is using the root to direct the tree
{
  if(p == NULL)//if the tree is empty
    p = new Node<T>(e);//add the element passed in and make it the root of the whole binary tree
  else if(e < p->el)//if the element inserted is less than the element of the root/subroot
    insertNodeR(p->left, e);//move to the left side of the tree
  else//e >= p->elem
    insertNodeR(p->right, e);//move to the right side of the tree 
}

template <class T>
void AVL<T>::preOrderPrint()
{
  preOrderPrint(root);//pre means print parent->left child ->right child
}

template <class T>
void AVL<T>::preOrderPrint(Node<T>* p) //private function. WHY?
{
  if(p == NULL)//if the tree is empty
    return;
  cout << p->el << "-->";
  preOrderPrint(p->left);//moves recursively to the left
  preOrderPrint(p->right);//moves recursively to the righ
}

template <class T>
void AVL<T>::postOrderPrint()
{
  postOrderPrint(root);//post means left->right->parent last
}

template <class T>
void AVL<T>::postOrderPrint(Node<T>* p) //private function. WHY?
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
int AVL<T>::getNumNodes()
{
  return getNumNodes(root);//used to return the amount of elements that are found inside of the tree
}

template <class T>
int AVL<T>::getNumNodes(Node<T>* p) //private function WHY?
{
  if(p == NULL)//if there are no nodes inside of the tree, then return the value zero
    return 0;//returns zero if the tree was empty
  else
    return getNumNodes(p->left) + getNumNodes(p->right) + 1;//gets the nodes from the left side of the root added with the number of nodes from the right side of the root and added by one because it is the root, so in total that is the number of nodes that will be found inside of the tree
}

template <class T>
int AVL<T>::getMinLength()
{
  getMinLength(root);//in order to use the root
}

template <class T>
int AVL<T>::getMinLength(Node<T>* p) //private function. WHY?
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
int AVL<T>::getEvenNodes()                                                   
{                                                     
  getEvenNodes(root);
}                                                                           
                         
template <class T>          
int AVL<T>::getEvenNodes(Node<T>* p) //private function. WHY?  
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
Node<T>* AVL<T>::searchI(const T& e)
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
Node<T>* AVL<T>::searchR(const T& e)
{
  return searchR(root, e);
}

template <class T>
Node<T>* AVL<T>::searchR(Node<T>* p, const T& e) //private function. WHY?
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
*/

/*
template <class T>
void AVL<T>::DFTprint()
{
  //use library's stack class
  //Make sure to include <stack> at the top
  stack<Node<T>*> s;//make a stack object
  if(root == NULL)//if DFT is empty
    return;
  
  s.push(root);//push the root inside the stack
  while(!s.empty())//if the stack is not empty
    {
      Node<T>* top = s.top();//set the top element to the top function
      cout << top->el << "-->";//pop top and print
      
      if(top->right != NULL)//if the top's right is not empty
	s.push(top->right);//push right kid if any
      if(top->left != NULL)
	s.push(top->left);//push left kid if any
 
      s.pop();//pop() removes the top element
    }
  //top() will give you the top element but it will not remove it from the stack
}

//This function returns true if e was removed or false if not because it doesn't exist
template <class T>
bool AVL<T>::remove(const T& e)//public function
{
  Node<T>* del = root;//del will point to the node to be deleted
  Node<T>* parent = NULL;//parent will point to the parent node of the node to be deleted
  //look for e in the tree
  while(del != NULL && del->el != e)//if root is NULL, del is NULL to start with while won't be entered and return false down below.
    {
      if(del->el > e)//if del's element is greater than the passed in element. Moves to the left side
	del = del->left;
      else//del->el <= e -- moves to the right if the element in the tree is less than the passed in element
	del = del->right;
      //del will eventually point to the node to be deleted.
      parent = del;//parent follows del. In other words, del is ahead of parent. --> you did something similar in insertI()
    }
  //e doesn't exist or tree is empty.
  if(del == NULL)
    return false;

  //check to see if root shhould be removed
  if(root->el == e)
    remove(root);//root will change. call the other remove function down below
  //We are deleting a node other than the root node. Figure out if del's node is left or right child of parent's node
  else if(parent->right->el == e) //parent's left child to be removed
    remove(parent->left);
  else //parent's right child to be removed
    remove(parent->right);
  
  //deleted the node with e
  return true;
}

template <class T>
//p coming out of the parent node and points to the node to be deleted OR p points to root node if root node is the one to be deleted.
//p will eventually point to the grandchild (child node of the node to be deleted) or NULL if p is root or the node to be deleted has no children. p will chage. That is why we need to use &.
void AVL<T>::remove(Node<T>*& p) //private function
{
  Node<T>* temp = p; //temp points to the node to be deleted initially
  Node<T>* t_parent; //t_parent will point to the parent node of temp's node
  //the node to be deleted has no right child (Check Diagram1 in the homework document "HMWK BST - BFT, DFT and remove" under "Assignments")
//If the node to be deleted has no children, the following if will be executed.(Check Diagram2)
  if(p->right == NULL)
    p = p->left; //p(The left or right coming out of parent of del's node) now points to the root of the left subtree under del's node. DONE.  If the node to be deleted has no children, p is set to NULL because p->left is NULL.
  //the node to be deleted has no left child (Check Diagram 3)
  else if(p->left == NULL)
    p = p->right;//p(The left or right coming out of parent of del's node) now points to the root of the right subtree under del's node. DONE.
  //If the node to be deleted has 2 children
  else
    {
      //we are going to replace e by the largest value in the left subtree
      temp = p->left; //temp points to the root of the left subtree under the node to be deleted to start with
      t_parent = p; //t_parent points to the node to be deleted to start with
//go to the largest value in the left subtree under the node to be deleted by going all the way down to right
      while(temp != NULL)
	{
	  t_parent = temp; //temp is ahead of t_parent
	  temp = temp->right; //temp will eventually point to the largest value
	}
      //copy the largest value into the node to be deleted
      temp = temp->right;
      if(t_parent->el < temp->el)//the largest value is the direct left child of the node whose value was replaced by the largest (Diagram 4)
	t_parent->left;//connect the left of the node whose value was replaced by the largest value to the left child of the node that has the largest value
      else//the largest value is NOT the direct left child of the node whose value was replaced by the largest (Diagram 5)
	t_parent->right;//If the node with the largest value doesn't have any children, t_parent->right is set tot NULL.
    }
  //finally delete temp;
  delete temp;
}
*/
#endif
