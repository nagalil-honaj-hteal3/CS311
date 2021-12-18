#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

const int MAX = 3;

template<class T>
class Stack
{
 private:
  int top;
  T el[MAX];

 public:
  Stack() {top = -1;}
  bool isEmpty() const {return top == -1;}
  bool isFull() const {return top == MAX - 1;}
  void pop(T& e);
  void push(const T& e);
  void displayAll() const;

  //Exception classes
  class Underflow {};
  //class Overflow {};
  class Overflow
  {
  private:
    T val;
  public:
    //constructor
    Overflow(const T& v){val = v;}
    //get function to access the private data member
    T getElem() const {return val;}
  };
};

template<class T>
void Stack<T>::pop(T& e)
{
  if(isEmpty())
    //throw "Error: trying to pop when the stack is empty";
    throw Underflow();

  e = el[top--];
}

template<class T>
void Stack<T>::push(const T& e)
{
  if(isFull())
    //throw "Error: trying to push when the stack is full";
    //throw Overflow();
    throw Overflow(e); //throws back the element that was tried to be inserted.

  el[++top] = e;
}

template<class T>
void Stack<T>::displayAll() const
{
  if(isEmpty())
    cout << "[empty]" << endl;
  else
    {
     for(int i = top; i >= 0; i--)
       cout << el[i] << endl;
    }
}

#endif
