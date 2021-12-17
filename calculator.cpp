/******************************************************************************
CS311

Name: XXXXXXXXXXXXXXXXX
Program number: XX
This is an application of your stack class. You are going to enter an infix expression from the keyboard. Use single-digit numbers instead of variables. To make this application simple, you can assume all numbers are one-digit and there are no spaces in the infix expression entered from the keyboard. The operators we are using are +,-,*,/ and (). 
******************************************************************************/
#include <iostream>
#include "stack_L_T.h"
using namespace std;

int priority(char ch);//function to get an operator and return its priority number
bool isOperand(char ch);//function to check if the token is an operand
bool isOperator(char ch);//function to check if the token is an operator
string infixToPostfix(const string& infix);//function to convert from infix to postfix and returns postfix
int charToInt(char ch);
double evaluatePostfix(const string& postfix);//function to evaluate postfix and returns the answer
double doMath(double operand1, char opt, double operand2);//to evaluate the postfix expression and return the number

int main()
{
  //Stack<char> s;//the whole program will be using characters 
  string infix;
  cin >> infix;//to get the postfix expression

  /*if(s.empty())
    cout << "Empty: There is nothing inside of the stack." << endl;//This is an error message to make sure that there is nothing inside of the stack
  */
  try
    {
      string postfix = infixToPostfix(s, input);//Call function to convert from infix to postfix. Within this function, either Underflow or pop() or "The expression is in a wrong format" could be thrown
      cout << postfix << endl;
      evaluatePostfix(postfix);//Call function to evaluate postfix. This function, either Underflow or pop() or "The expression is in a wrong format" could be thrown
    }
  catch(Stack<char>::Underflow)
    {
      cout << "The expression is in a wrong format." << endl;
    }
  catch(const char* msg)//The expression is in a wrong format is caught here. The expression is in a wrong format is a c-string, which is a character array ended with a null terminator ('\0'). msg of the type char* points to the first character of the c-string, The expression is in a wrong format.
    {
      cout << msg << endl;
    }
  catch
    {
      cout << "The expression is in a wrong format." << endl;
    }
  //cout << infixToPostfix(s, input) << endl;
  //cout << calculate(infixToPostfix(s, input)) << endl;
}

/******************************************************************************
This isOperand function will be used to pass in the elements from the stack. It will only read single digit numbers and will either return the elements as true or false to verify whether the element passed is a number. 
******************************************************************************/

bool isOperand(char ch)
{
  if(ch >= '0' && ch <= '9')
    return true;
  else 
    return false;
}

/******************************************************************************
This isOperator function will be passed to see the elements inside of the stack to see if the character is an operator so it can be used for push and be displayed as a result on the postfix expression and output the following characters on an exception handling case
******************************************************************************/

bool isOperator(char ch)
{
  if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
    return true;
  else
    return false;
}

/******************************************************************************
This priority function will be used as an int function while it passes in a char element because since it the elements picked are from the main. This is used for PEMDAS (Parenthesis, Exponent, Mult, Div, Add, Sub) however for this program, it will not use exponent and will have a return type of integers which will be read for the precedence and will be used inside of the stack.
******************************************************************************/

int priority(char ch)
{
  switch(ch)
  {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
  }
}

/******************************************************************************
This infixToPostfix function is used to make the following input of the stack read what is on the infix (the list of operands and operators the user entered). It would have a local variable called postfix inside of the function to return the following elements combined as one term for it to be outputted for the user to see their output. Most of the other loops inside of this function will contain a variety of stack functions inside of the stack template linked list header file to either push or pop the elements that are viewed. This function will have two parameters including the stack object, which was previously said of its functionalities such as having functions that can access the header file and the input of the user which will be a string and pass in the operands and operations.

I am unsure why this function does not output any operands, but outputs the operations instead.
******************************************************************************/

string infixToPostfix(const string& infix)
{
  Stack<char> s;//stack holding operators
  string postfix = "";//make a local varaible inside the function
  char token;//current token
  
  for(int i = 0; i < input.length(); i++)//this will be used to read the string of the postfix and increment once it checks on the character
	{
    token = infix[i];
    //current token is an operand one-digit
    if(!isOperand(token))
    {
      postfix += token; 
    }
    else if(isOperator(token))
    {
      while(!s.empty() && s.getTop != '(' && getPriority(s.getTop()) >= getPriority(token))
      {
        postfix += s.getTop();
        s.pop();
      }
    }
    else if(token == '(')//current token is (
    {
      s.push(token);
    }
    else if(token == ')')//current token is )
    {
      while(!s.empty() && s.getTop() != '(') 
      {
        postfix += s.getTop();
        s.pop();
      }
      s.pop();
    }
	  else
      throw "The expression is in a wrong format";
  }
	  
  while(!s.empty())//if there are still elements inside of the stack
    {
      if(s.getTop() != '(')
        postfix += s.getTop();//the postfix final answer after the input of infix
      s.pop();//once the postfix is completed
    }

  return postfix;//return the value once it has been collected
}

/******************************************************************************
The calculate function is used to return the postfix evaluated number from the postfix. It will be carrying a parameter of the string the user has entered once it has been processed inside of the infixToPostfix function. The calculate will sort of work similar to the infixToPostfix function but the difference is that it will be collecting the operands in the stack and combine them with the follwoing operators and leave the answer to its evaluated form. It will use some of the following stack functions inside of the header class and gather the operands and operations into the doMath function to get the evaluated number and will continue to do it until there is nothing left inside of the stack. 
******************************************************************************/

double evaluatePostfix(const string& postfix)
{
  Stack<double> s;
  char curItem;
  double o1, o2;//2 operands
  
  double result, finalResult;
  for(int i = 0; i < postfix.length(); i++)
  {
    curItem = postfix[i];
     if(isOperand(curItem))//if operand
       s.push(charToInt(curItem));
     else if(isOperator(curItem))//if operator
     {
       o1 = s.getTop();//pop right
       s.pop();
       o2 = s.getTop();//pop left
       s.pop();
       result = doMath(o2, curItem, o1);
       s.push(result);
     }
     else
       throw "The expression is in a wrong format";
  }
  
  if(!s.empty())
  {
    finalResult = s.getTop();
    s.pop();
    
    if(!s.empty())
      throw "The expression is in a wrong format.";
    else
      return finalResult;
  }
  else
    throw "The expression is in a wrong format";
}

int charToInt(char ch)
{
 return ch - 48; 
}
/******************************************************************************
The doMath function has three parameters to either add, subtract, multiply, or divide two numbers. It will have an exception handling case if it catches one of the operations to be not recognizable and the following operators follow up on the numbers value once it has been evaluted. Since the operation is read as a char since it is a string, the operator as read on the other functions, it will just simply follow the command whether to add, multiply, subtract, or divide.
******************************************************************************/

double doMath(double operand1, char opt, double operand2)
{
   switch(opt)
   {
     case '+': return operand1 + operand2;
     case '-': return operand1 - operand2;
     case '*': return operand1 * operand2;
     case '/': return operand1 / operand2;
   }
}
