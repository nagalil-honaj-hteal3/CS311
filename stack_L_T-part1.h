/***********************************
Stack implemented with a LL

Your name here: XXXXXXXXXXXXXXXXXXXX
Your programmer number here: XXXX
Any problems you had? XXXXXXXXXXXXXXXXXXXXXXXX
******************************************************************************************************************/
#ifndef STACK_L_T_H
#define STACK_L_T_H

#include <iostream> 
using namespace std;

template <class T> //forward declaration needed so we can make stack class a friend of node
class Stack;

template <class T> //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const Stack<T>& s);

template <class T>
class Node
{
  friend class Stack<T>; //Stack class accesses the private members of Node
  friend ostream& operator<< <T>(ostream& o, const Stack<T>& s); //operator<< accesses the private members of Node

 private:
  T elem;//the element could be any value
  Node* next;//to shift into different nodes inside the heap memory
 public:
  Node(){Node<T>* top = NULL;} //default constructor
  Node(const T& e){elem = e; next = NULL;}
};

template <class T>
class Stack
{
  friend ostream& operator<< <T>(ostream& o, const Stack& s); //operator<< accesses the private members of Stack
  
 private:
  Node<T>* top;
  int size;
  
  //helper functions - private because they won't be called from client
  void destroy();
  void copy(const Stack& source);

 public:
  Stack() {top = NULL;} //Implement a small function inside the class definition 
  Stack(const Stack& other);
  ~Stack();
  Stack& operator=(const Stack& rhs); //rhs = right hand side of the operator   LHS_obj = RHS_obj
  bool empty() const{return (top == NULL && size == 0);} //implement a small function inside the class definition
  int getSize() const{return size;} //implement here
  void push (const T& val);
  void pop();
  T& getTop(); //Return type is T& so client can change the top value
  const T& getTop() const; //A const object needs to call a const member function

  //Make an exception class here - You need to figure out where to throw an exception - I am throwing in 3 functions.
  //??????????
  class Underflow{};
  class Overflow
  {
  private:
    T val;
  public:
    Overflow(const T& v){val = v;}
    T getElem() const {return val;}
  };
};

/******************************************************************************
This push function will be used to access a passed by reference value to store it inside of a node to be kept inside of the heap memory. As it is used as a stack template class, it will store a new node with using a T for the template class and it will be used as pointer (p) to point the elements, top, and next. It will point to the elements to get the value, the top will be pointed with p to be shown in the heap memory, and the next as NULL to not keep the heap memory unbalanced.
******************************************************************************/

template <class T>
void Stack<T>::push(const T& val)
{
  Node<T>* p = new Node<T>;//p is a pointer that I created
  p->elem = val;//element of the pointer will equal the passed by value from 
  p->next = top;//points to top
  top = p;//the top will be set to p because top will be used for the new added node
  //p->top->next = NULL;//the top's next will be set to NULL since that will be the end barrier of the heap memory
}

/******************************************************************************
The pop function pushes the stack element and deletes whatever is inside of the stack. It will be using two test cases if the stack is empty or not. For the efirst case, it will throw an underflow class so it will go to the client and show the error message by stating that there is nothing inside the stack. As of for the second case, it will find the top element and will shift to the bottom to delete the node or the top. 
******************************************************************************/

template <class T>
void Stack<T>::pop()
{
  if(empty())//no nodes inside of the stack
    throw Underflow();//error message from the client
  else//if there are nodes inside of the stack
    {
      Node<T>* p = top;//no need to add a new node in this line
      top = top->next;//top will be the bottom's top node 
      delete p;//remove the pointer (top)
    }
}

/******************************************************************************
The getTop function will get the element from the top node inside of the stack. It will have a return element of the top and since it is not a void function and is a template return function, it is required to use a return statement and will be used for two cases. One is if there is nothing inside of the stack, so there won't be any complication error and also since it has an underflow class that is being thrown, it will easily have access to output the error message that will be declared inside of the client file. As of for the other function, it will be simply returning the top element of that stack. While this has the & sign next to the template T, it will return any data type of the element whether if it is a decimal, an integer, or a string.
******************************************************************************/

template <class T>
T& Stack<T>::getTop()
{
  if(empty())
    throw Underflow();//error message will show in the client function
  else
    return top->elem; //return the top element. Since the return type is T&, the client can change the to
}

/******************************************************************************
This getTop function will work the same as the previous getTop function but the difference the const, which will just keep the value that was stored inside of the stack and without the constant, the value inside of the stack can change and it will simply confuse the program for what is going to be the value from the top. It will return the top element as before and will continue to print the following values moving forward.
******************************************************************************/
/*
template <class T>
const T& Stack<T>::getTop() const
{
  return top->elem; // same as the getTop() above. We need to provide this so a const object can call getTop(). Recall a const object can only call const member functions.
}
*/
/******************************************************************************
The operator << function will output the following top elements that were on the stack from top to bottom. Since it is an ostream function, it will require two parameters with the ostream o, which will be exaggerated as the cout, and the s, which will be used to access any of the functions from the stack class, so in this function, it will use the empty function to collect all the elements stored inside of the stack. Using the not empty will effectively output all the elements from the top to the bottom and easily access the getTop function that will output the elements inside of the stack.
******************************************************************************/

template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //print from top to bottom.
  cout << "--- Top ---" << endl;
  while(!s.empty())
    o << s.getTop();
  cout << "--- Bottom ---" << endl;
}

/******************************************************************************
This function will be the destructor for the stack class, which will deallocate memory by deleting nodes inside of the class and the object class will be immediately get destroyed based on the function that will be called and in which this case it will be the destroy function.
******************************************************************************/

template <class T>
Stack<T>::~Stack()
{
  destroy(); 
}

/******************************************************************************
The destroy function operates by using the pop function. This function will not have any parameters, since there is a function that can be implemented to consistently remove the nodes more quicker and efficiently, which is the pop function. It will be using a while loop so it will easily delete all the nodes inside of the stack and set it as !empty or not empty so when there are nodes inside of the stack, it will easily remove them with ease.
******************************************************************************/

//helper function - called from destructor and operator=
template<class T>
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  while(!empty())//not empty
    {
      pop();//pop function that takes away the stack element
    }//destroy all nodes
}


/*
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  //good reading from cal tech
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html

  //deep copy
  if(???????) //Check the addresses of the left and right objects. If they are the same, you are trying to assign the same object   s = s;
              //You copy only if the left object is not the same as the right object.
    {
      //destroy any memory space "this" is using. "this" may have elements already. call destroy
      //call copy
    }
  return ???????; //return the "this" object 
}
*/


/*
//helper fuction. called from operator= and copy constructor
template <class T>
void Stack<T>::copy(const Stack& source) //source is the stack object copied from. 
{
  //"this" object ends up having the same values from source
}
*/

/*
//copy constructor
template <class T>
Stack<T>::Stack(const Stack& other)
{
  //This is a copy constructor. This new object will get the same values as the other object. 
  //You still need to initialize the data members.
  ???????
  ???????

  //Then you can call the copy function
}
*/


#endif // end the definition here
