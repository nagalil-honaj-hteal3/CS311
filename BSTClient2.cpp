/****************************
Kazumi Slott
CS311

Test client for BST.h
***************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
#include "BST.h"

int main()
{
  //  srand(time(0));
  BST<int> b1, b2;
  int n;
  //ofstream fout;
  //fout.open("BST.in");
  ifstream fin;
  fin.open("BST.in");

  for(int i = 1; i <= 30; i++)
    {
      //n = rand()%100 + 1;
      //fout << n << " ";
      fin >> n;
      b1.insertNodeI(n);
      b2.insertNodeI(n);
    }

  cout << "b1.inOrderPrint()" << endl;
  b1.inOrderPrint();
  cout << "\nb2.inOrderPrint()" << endl;
  b2.inOrderPrint();

  cout << "\n\nb1.preOrderPrint()" << endl;
  b1.preOrderPrint();
  cout << "\n\nb1.postOrderPrint()" << endl;
  b1.postOrderPrint();

  cout << endl << endl << "The max length is " << b1.getMaxLength() << endl;
  cout << "The min length is " << b1.getMinLength() << endl;
  cout << "The total number of nodes is " << b1.getNumNodes() << endl;
  cout << "The total number of even nodes is " << b1.getEvenNodes() << endl;

  cout << "Searching n using Recursion " << b1.searchR(n)->getEl() <<  endl;
  cout << "Searching n using Iteration " << b1.searchI(n)->getEl() << endl;
  cout << "Searching 1000 using Recursion " << b1.searchR(1000) << endl;
  cout << "Searching 1000 using Iteration " << b1.searchI(1000) << endl;


  cout << "\n\nmake a new tree" << endl;
  BST<int> b3;
  b3.insertNodeR(8);
  b3.insertNodeR(5);
  b3.insertNodeR(20);
  b3.insertNodeR(16);
  b3.insertNodeR(10);

  cout << "testing BFTprint()" << endl;
  b3.BFTprint();
  cout << "\ntesting DFTprint()" << endl;
  b3.DFTprint();

  cout << "\nin order print" << endl;
  b3.inOrderPrint();
  cout << "\ntesting removing a node with only left child." << endl;
  b3.remove(20);
  b3.inOrderPrint();

  cout << "\n\nmake a new tree" << endl;
  BST<int> b4;
  b4.insertNodeR(8);
  b4.insertNodeR(5);
  b4.insertNodeR(20);

  b4.inOrderPrint();

  cout << "\ntesting removing a node with no children." << endl;
  b4.remove(20);
  b4.inOrderPrint();

  cout << "\n\nmake a new tree" << endl;
  BST<int> b5;
  b5.insertNodeR(8);
  b5.insertNodeR(5);
  b5.insertNodeR(20);
  b5.insertNodeR(25);
  b5.insertNodeR(22);

  b5.inOrderPrint();

  cout << "\ntesting removing a node with only right child." << endl;
  b5.remove(20);
  b5.inOrderPrint();

  cout << "\n\nmake a new tree" << endl;
  BST<int> b6;
  b6.insertNodeR(8);
  b6.insertNodeR(5);
  b6.insertNodeR(20);
  b6.insertNodeR(16);
  b6.insertNodeR(30);
  b6.insertNodeR(10);

  b6.inOrderPrint();

  cout << "\ntesting removing a node with 2 children. the largest value in the \
left subtree is the direct left child of the node to be deleted" << endl;
  b6.remove(20);
  b6.inOrderPrint();

  cout << "\n\nmake a new tree" << endl;
  BST<int> b7;
  b7.insertNodeR(8);
  b7.insertNodeR(5);
  b7.insertNodeR(20);
  b7.insertNodeR(16);
  b7.insertNodeR(30);
  b7.insertNodeR(10);
  b7.insertNodeR(19);
  b7.insertNodeR(17);

  b7.inOrderPrint();

  cout << "\ntesting removing a node with 2 children. the largest value in the \
left subtree is NOT the direct left child of the node to be deleted" << endl;
  b7.remove(20);
  b7.inOrderPrint();

  cout << "\n\nDestructor is being called" << endl;

  cout << endl;
  return 0;
}
