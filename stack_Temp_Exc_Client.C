#include <iostream>
using namespace std;
#include "stack_Temp_Exc.h"

int main()
{
  Stack<int> s;
  int elem; //place holder to store a popped element

  try
    {
      s.pop(elem);

      s.push(1);
      s.push(2);
      s.push(3);
      s.push(4);
    }
  //  catch(const char* m)
  catch(Stack<int>::Underflow)
    {
      cout << "Error: trying to pop when the stack is empty" << endl;
      //cout << m << endl;
    }
  /*  catch(Stack<int>::Overflow)
    {
      cout << "Error: trying to push when the stack is full" << endl;
      //cout << m << endl;
      }*/
  catch(Stack<int>::Overflow e)
    {
      cout << "Error: trying to push when the stack is full. Couldn't insert " << e.getElem() << endl;
      //cout << m << endl;
    }



  cout << "AFTER" << endl;

  s.displayAll();

  return 0;
}
