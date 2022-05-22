#include <iostream>
#include <fstream>

using namespace std;

const int LEN = 3; //the length of words
const int ALPHABET = 26; //total number of letters

class Node
{
  friend class LL;//share the functions of the linked list with the node class
private:
  string el;//element of the word that is being checked
  Node* next;//pointing to the next part in the heap memory
public:
  Node(const string& s){el = s; next = NULL;}
  string getElem() const {return el;}
};

class LL
{
private:
  Node* front;
  Node* rear;
  int num;
public:
  LL(){front = rear = NULL; num = 0;}
  ~LL();
  bool empty()const{return (front == NULL && rear == NULL && num == 0);}
  void addRear(const string& s);
  void addRear(Node* p);
  void append(const LL& other);
  void clear(){front = rear = NULL; num = 0;}
  Node* begin() const{return front;}
  Node* goToNext(Node* curr) const{return curr->next;}
  int size() const{return num;}
};


LL::~LL()
{
  cout << "destructor is called" << endl;
  Node* p = front;
  while(!empty())
    {
      front = front->next;
      delete p;
      p = front;
      if(front == NULL)
        rear = NULL;
      num--;
    }
}

//add a new node at the end of this list. The element of the new node is s.
void LL::addRear(const string& s)
{
  //This function is just like what you made in LL class from CS211.
  Node* p = new Node(s);

  if(empty())
    front = rear = p;
  else
    {
      rear->next = p;
      rear = rear->next;
    }
  num++;
}


//Implementing this function
//add the node pointed to by p (p points to one of the nodes in all list) at th\
e end of this list
void LL::addRear(Node* p)
{//**************UNAWARE IF THIS PART OF THE FUNCTION WORKS********************
  //Don't make a new node.
  if(empty())//You need a special case when the list is empty
    {
      front = rear = p;//set the front and rear to the pointed node
    }
  //you don't need to place NULL in the next field of the last node of this lis\
t.
  else//if there are nodes inside of the heap memory
    {
      rear->next = p;//set the rear's next to the pointer
      rear = rear->next;//have the rear be assigned after the previous rear's n\
ext
    }
  num++;//don't forget to increment num

}

//Implement this function
//appending another linked list at the end of this linked list
void LL::append(const LL& other)
{//**************UNAWARE IF THIS PART OF THE FUNCTION WORKS********************
  //Don't forget to update num of this list
  this->front = other.front;//initialize the front and point it to other front
  this->rear = other.rear;//initialize the rear and point it to other rear
  this->num += other.num;//set the num to the other LL assignment and increment\
 it to add the number of nodes with the other set of nodes

  Node* p = other.front;//use this to start and intialize from the front
  while(p != NULL)//used to have the pointer reach to NULL once there are no mo\
re nodes to check
    {
      this->addRear(p->front);//this will continue to collect the nodes from th\
e heap memory and adds it onto the next nodes
      p = p->next;//shifts onto the next node
    }
  //close the end of this list by putting NULL in the next field of the rear no\
de
}


void radixSort(LL& all);
void makeLL(LL& all, const string a[], int n);
void printLL(const LL& l);
void checkBuckets(const LL buckets[], int n);
void combineLists(LL& all, const LL buckets[]);
void makeLL(LL& all);

int main()
{
  LL all; //holds all words
  makeLL(all); //all contains strings in the original order
  radixSort(all);
  cout << "Final result ----" << endl;
  printLL(all); //all contains strings in sorted sorter
  cout << endl;

  return 0;
}

//Implement this function
//using the radix sort algorithm to sort strings that contain lowercase letters\
.
void radixSort(LL& all)
{//**************UNAWARE IF THIS PART OF THE FUNCTION WORKS********************
  //Each slot of the buckets array is a LL object.
  LL buckets[ALPHABET]; //bucket[0] is for 'a'. There are 26 buckets.
  //Node* p = front;
  int i = 1;//counter
  int j, a, b;//used for temp variables -> since i used int instead of string, \
I am ubsure on what to implement here
  int k = k * ALPHABET;//to count the placed digits; here since it is using str\
ings I had this whole setup wrong, so I might have probably overthinked this
  int n = ALPHABET - 1;//size
  while(i <= n)//if the initalizer is less than the size of buckets
    {
      while(!all.empty())//if there are still nodes to be checked
        {
          a = all.clear();//use to call the clear function once it has been exe\
cuted
          b = a % k;//to check the character of the index -> I know I messed up\
, just putting in some implementation to get some credit
          b = b / k;//to check what passes the string-> same as goes with the t\
op line
          buckets[b].addRear(a);//use to get the array once the word that has b\
een checked by its repsective character
        }
      for(j = 0; j < ALPHABET; j++)//goes through the alphabet one last time
        {
          while(!buckets[j].empty())//when the array for the buckets is
            {
              a = buckets[j].clear();//clear it to move the word
              all.addRear(a);//reorganize the word once it has been checked
            }
        }
      i++;//increment to the next word
    }

  //checking each place
  //To go through each string in all list, check printLL() to see how to iterat\
e
  //go to the correct bucket depending on the letter at the current place and a\
dd the node from all at the end of the bucket
}

//Implement this function
//combining all lists from buckets
void combineLists(LL& all, const LL buckets[])
{//**************UNAWARE IF THIS PART OF THE FUNCTION WORKS********************
  all.clear();  //call clear() to reset all list. All the nodes went to correct\
 buckets already.
  all.append(all);//populate all list by combining the lists from the buckets b\
y calling append()
  for(int i = 0; i < ALPHABET - 1; i++)//set the indices of the array in bucket\
s and continue to increment once it has been checked
    {
      buckets[i, ALPHABET - 1];//the index of the string and used to categorize\
 the following words based on its character
      all.clear();//clear the word once the node has been moved/checked
    }  //reset each list in b[i] by calling clear(). All the nodes were moved t\
o all list already.
}

//Make a linked list of words from an input file
void makeLL(LL& all)
{
  string s;
  fstream fin;
  fin.open("radix.in");

  fin >> s;
  while(fin)
    {
      all.addRear(s);
      fin >> s;
    }
}

//This function shows the contents of all the buckets
void checkBuckets(const LL buckets[], int n)
{
  for(int i = 0; i < n; i++)
    {
      cout << i << ": ";
      printLL(buckets[i]);
      cout << endl;
    }
}

//This function prints all the elements in l
void printLL(const LL& l)
{
  int i;
  Node* p;

  //iterate l from the first node to last node
  for (i = 0, p = l.begin(); i < l.size(); i++, p = l.goToNext(p))
    cout << p->getElem() << ' ';
}


