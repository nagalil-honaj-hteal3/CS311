#include <iostream>
using namespace std;
#include "AVL.h"

int main()
{
  AVL<int> t;

  cout << "Adding 5------" << endl;
  t.insertNodeI(5);
  t.BFTprint();

  cout << "\nAdding 3------" << endl;
  t.insertNodeI(3);
  t.BFTprint();

  cout << "\nAdding 6------" << endl;
  t.insertNodeI(6);
  t.BFTprint();

  cout << "\nAdding 2------" << endl;
  t.insertNodeI(2);
  t.BFTprint();

  cout << "\nAdding 4------" << endl;
  t.insertNodeI(4);
  t.BFTprint();

  cout << "\nAdding 1: testing LL rotating around root. node that will become new root has 2 children ------" << endl;
  t.insertNodeI(1);
  t.BFTprint();

  cout << "\nAdding 8 ------" << endl;
  t.insertNodeI(8);
  t.BFTprint();

  cout << "\nAdding 10: testing RR rotating around non-root. node that will become new root has 1 child ------" << endl;
  t.insertNodeI(10);
  t.BFTprint();

  cout << "\n\nConstructing a new tree with 8, 5, 10 and 7 ------" << endl;
  AVL<int> t2;
  t2.insertNodeI(8);
  t2.insertNodeI(5);
  t2.insertNodeI(10);
  t2.insertNodeI(7);
  t2.BFTprint();

  cout << "\nAdding 6: RL The violation is not at root --------" << endl; 
  t2.insertNodeI(6);
  t2.BFTprint();

  cout << "\n\nConstructing a new tree with 8 and 4 ------" << endl;
  AVL<int> t3;
  t3.insertNodeI(8);
  t3.insertNodeI(4);
  t3.BFTprint();

  cout << "\nAdding 7: LR. The violation is at root  --------" << endl; 
  t3.insertNodeI(7);
  t3.BFTprint();

  cout << endl;
  return 0;
}
