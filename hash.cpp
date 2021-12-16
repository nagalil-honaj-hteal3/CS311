/************************
Your name: XXXXXXXXXXXXXXXXXXXXXX
Your programmer number: XXX
Any difficulties?: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*********************/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

//unsigned for positive numbmers or zero only. long takes up 4 bytes. 0-2^32(4294967295)
unsigned long hashNum(const string& key);

class entry //this is basically a node
{
  //What do you do if hashTbl needs to access the private members of entry?
  //If you don't say private or public, it is private by default.
  friend class hashTbl;
  //private:
  string ID;
  string name;
  int age;
  double GPA;
  entry* next;//????? next; //points to the next entry

public:
  entry() { ID = name = "", age = -999, GPA = -999.0, next = NULL; }
  entry(const string& ID, const string& name, int age, double GPA ) { this->ID = ID, this->name = name, this->age = age, this->GPA = GPA, next = NULL; }
  string getID()const { return ID; }
  string getName()const { return name; }
  int getAge()const { return age; }
  double getGPA()const { return GPA; }
  entry* getNext()const { return next; }
};

class hashTbl
{
  entry** table;//????? table;   //table points to a dynamic array. Each slot points to an entry, which points to the next entry, ...
  int size; //size of the array
public:
  hashTbl(int size);
  ~hashTbl();
  void put(entry* e); //add a new entry to the table
  entry* get(const string& key)const; //look up a key
  entry remove(const string& key); //remove an entry
  entry** getTbl()const{return table;}//return the pointer to table
  class underflow //exception class - used when key wasn't found
  {
    string message;
  public:
    underflow(const string& mes) { message = mes; }
    string getMessage() { return message; }
  };
};

//constructor
//s is the size of the table
hashTbl::hashTbl(int s)
{
  size = s;//set private member size
  table = new entry*[size];//make a dynamic array that has s slots
  //table = NULL;//put NULL in each slot of the array. Remember Each slot contains a pointer to an entry.
  //int index;
  for(int i = 0; i < s; i++)
    table[i] = NULL;
}

//destructor
hashTbl::~hashTbl()
{
  //you need to destroy everythin created using new
  //destroy all the entries belong to each slot of the table
  entry* slot;//used to store a memory slot within the table
  entry* newSlot;//set a temporary to move onto the next slot within the table
  for(int i = 0; i < size; i++)//iterates through each slot in the hash table
    {
      slot = table[i];//slot will be the index of the table
      while(slot != NULL)//if the slot is not empty -- used to delete any entries that are inside of the table
	{
	  newSlot = slot->next;//set the new slot with another slot in the table
	  delete slot;//deletes the slot inside of the hash table
	  slot = newSlot;//set the slot with the newSlot to traverse in the hash table
	}
    }
   //don't forget to destroy the dynamic array
  delete[] table;
}
  /*while(size == 0)
    {
      remove(table);
    }//set private member size
  */
//^^ from the destructor function

//___________________________________________________________________________________________

//insert an entry to the table
//e is a pointer to an entry
void hashTbl::put(entry* e)
{
  //This function is like LL::addFront() from CS211  
  //MY ORIGINAL CODE

  //string key = e->ID; <- do not use that because ID is a private member, so using one of the get functions is the most ideal way to get the ID  
  //int index = (hashNum(key)) % (table->size);//(call hashNum with key) % (table size); 
  //entry* cur = e->key;//make cur point to the first entry
  /*  if(cur == NULL)//if there are no entrys inside of the heap
    {
      table = new entry;//create a new node
      table->key = cur->key;//set the current key
    }
  else
    {
      p = new entry;//creates a new entry
      p->key = key;//use the current key and set it to a key
      cur->next = cur->next->next;//set the next value to the cur next next 
      cur->next->next = p;//move the added entry before the entry inside of the heap memory
    }
  size++;//increment the size of the entry
  */
  string key = e->getID();//use ID for key
  int index = hashNum(key) % this->size;//int index = (call hashNum with key) % (table size)
  entry* cur = table[index];//entry* cur = make cur point to the first entry

  //add the entry at the beginning of the list coming out of index	
  //This will have the first element of the array at the given index, so since it is a linked list, it must set next entry first.
  e->next = cur;//have the current be the next pointed entry
  table[index] = e;//the table's element is e in the hash table
}
//entry* hashTbl::get(const string& key) const
  //This function is like LL::search() from CS211
  //string key = e->ID;//use ID for key 
  /*  int index = (hashNum(key)) % (table->size);
  entry* cur = e->key;//make cur point to the first entry
  //perhaps you could mimic some code from put
  while(cur != NULL)//once the entry is still being searched
    {
      if(cur->key != key)//if there is no element that matches
	throw underflow(key);//outputs the following error message
      else//if the key has been found inside the heap
	{
	  return cur->key;//returns the current key inside of the entry
	}
      cur = cur->next;//go through the table
      size++;//increment through the entry once it has been found
    }
  //returns a pointer
  //look for key in the linked list. Return the pointer to the entry with key.
  //After traversed the list, if key wasn't found, throw exception just like above where the slot was empty
  */
//look up key and return the pointer to it. Assume keys are unique.
entry* hashTbl::get(const string& key) const
{
  //This function is like LL::search() from CS211
  int index = hashNum(key) % this->size;
  entry* slot = table[index];
  //if(the slot is empty)
  if(slot == NULL)//if there is nothing to search or it is not found
    throw underflow(key);
  //look for key in the linked list. Return the pointer to the entry with key.
  entry* p = slot;
  while(p != NULL)
    {
      if(p->ID == key)//if the ID matches the key inside of the table
	return p;//return the pointer, which has the element that has been searched
      p = p->getNext();//traverses through the table if the element has not been found
    }

  //After the table has been checked, if it has not been found, throw an exception
  if(p == NULL)
    throw underflow(key);
  return p;//return that the element has not been found for what was searched

}

/*entry hashTbl::remove(const string& key)
{
  //This function is like LL::remove() from CS211
  string key = e->ID;//use ID for key 
  entry* cur = e->key;//make cur point to the first entry
  entry* f;//pointer for reference front
  entry* d;//pointer for reference delete
  int index = (hashNum(key)) % (table->size);
  //mimic put and get
  while()
    {
      if(cur == NULL)//if there are no entry inside of the heap memory
	throw underflow(key);
      if(cur->key != key)//if there is no matching element to be deleted inside of the heap memory
	throw underflow();
      if(cur->key == key)//if the entry has been found inside of the heap memory
	{
	  if(size == 1)
	    {
	      string temp = cur->key;//stored to return this key as the most recent deleted value 
	      delete cur;//remove the current spot
	      cur = NULL;//prevent any roaming space in the heap
	      size--;//decrement the heap memory
	      return temp;//the contents of the current key to be returned
	    }
	  else
	    {
	      entry* newCur = cur->next;//set a new current pointer once the current is deleted
	      string temp = cur->key;//sets the current value of key into the temp variable
	      delete cur;//deletes the current pointer
	      cur = newCur;//sets that pointer to a different pointer inside of the heap memory
	      size--;//decrement once the element is deleted
	      return temp;//returns the contents of the element inside of the heap
	    }	  
	}
    }
  //return the entry found

  }*/
//remove the entry with key. Assume keys are unique.
entry hashTbl::remove(const string& key)
{
  //This function is like LL::remove() from CS211
  //Don't forget to return the entry that has been found
  int index = hashNum(key) % size;
  entry* slot = table[index];
  //No entry in hashtable location
  if(slot == NULL)
    throw underflow(key);

  entry remove;
  entry* prev;
  //We don't know how many entries are in each slot
  while(slot != NULL)//if the slot is not empty
    {
      //if there is a match to remove
      if(slot->ID == key)
	{
	  remove = *slot;
	  //if only one entry
	  if(slot->next == NULL)//logical since there will not be any slots pointing at that direction since there is only one
	    {
	      //DO NOT NULLIFY table[index] --> table[index] = NULL
	      slot = NULL;//set that whole slot pointer to NULL
	    }
	  else//more than one entry
	    {
	      prev->next = slot->next;//set the previous of the slot to the next slot
	      slot = NULL;//used to be deleted in the destructor
	    }
	  return remove;
	}
      //no matching key found and will check the next slot
      prev = slot;
      slot = slot->getNext();
    }
  //gets a n omatch founded in the list
  if(slot->ID != key)
    {
      throw underflow(key);
    }
  return remove;

}
//well known hash function called djb2
//http://www.cse.yorku.ca/~oz/hash.html
//For explanation of bit shifting, http://www.cplusplus.com/forum/beginner/95670/
unsigned long hashNum(const string& key)
{
  const char* cstr = key.c_str(); //converting C++ string to c-string. A c-string is a character array that is terminated by a '\0' (NULL terminator).
  
  unsigned long hash = 5381;
  int c;
  while (c = *cstr++) //checking each character until it reaches '\0'
    {
      hash = ((hash << 5) + hash) + c;//hash * 33 + c;
    }
  return hash;
}

void showInfo(const entry& e);
void showTable(const int count[], const hashTbl& students);
//unsigned for positive numbers only. long takes up 4 bytes. 0-2^32(4294967295)
unsigned long hashNum(const string& key);

const int SIZE = 1327; //prime number for a table size and why 1327?

int main()
{
  //make a hash table object with SIZE slots 
  hashTbl students(SIZE);
  int count[SIZE] = {0};//set all slots to 0. Used to see count in each index

  ifstream fin;
  fin.open("hash.in");
  string id, name;
  int age;
  double gpa;

  //adding entries from the input file
  fin >> id >> name >> age >> gpa;
  while(fin)
    {
      count[hashNum(id)%SIZE]++;//trying to see how many entries go into each slot
      students.put(new entry(id, name, age, gpa));
      fin >> id >> name >> age >> gpa;
    }
  //show the statistic about the table
  showTable(count, students);

  //put entries into the table
  //students.put(new entry("T1234567891", "Tom", 23, 4.0));
  //students.put(new entry("F5432112345", "Fred", 45, 3.5));
  //students.put(new entry("L1357915987", "Linsey", 48, 2.0));


  //searches and returns students in table without removing
  try
    {
      cout << "trying to search" << endl;
      showInfo(*(students.get("P1429911332")));//middle at index 377
      showInfo(*(students.get("Y1098431884")));//first entry at index 377
      showInfo(*(students.get("V1025438181")));//last entry at index 377
      showInfo(*(students.get("A1234567891")));//probably does not exist      
      //search for key and show their info
    }
  catch (hashTbl::underflow obj)
    {
      cout << "Student with ID: " << obj.getMessage() << " could not be found" << endl;
    }
  try
    {
      cout << "trying to remove" << endl;
      showInfo((students.remove("P1429911332")));//third entry at index 377
      showInfo((students.remove("V1025438181")));//last entry (now fourht) at index 377
      showInfo((students.remove("Y1098431884")));//first entry at index 377
      showInfo((students.remove("A1234567891")));//probably does not exist       
    }
  catch(hashTbl::underflow obj)
    {
      cout << "Student with ID: " << obj.getMessage() << " could not be removed" << endl;
    }
  //Try to remove a student from table
  //use try-catch

  return 0;
}

//Show the information about an entry
void showInfo(const entry& e)
{
  cout << e.getID() << " " << e.getName() << " " << e.getAge() << " " << e.getGPA() << endl;
}

//Show the statistic about the hash table
void showTable(const int count[], const hashTbl& students)
{
  //we want to know the highest, lowest and empty counts
  int lowest = 1001;
  int highest = -1;
  int empty = 0;
  int hi_i;//index of the highest count

  cout << "print table" << endl;
  for(int i = 0; i < SIZE; i++)
    {
      if(count[i] < lowest)
	lowest = count[i];
      if(count[i] > highest)
	{
	  highest = count[i];
	  hi_i = i;//set the highest index to that index of that located highest number
	}
      //highest = count[i];
      if(count[i] == 0)
	empty++;
      
      cout << setw(3) << count[i];
      if((i + 1) % 50 == 0)//Show 50 numbers per line
	cout << endl;
    }
  cout << endl << endl << "lowest is " << lowest << " highest is " << highest << " empty is " << empty << endl;

  cout << "highest count is at " << hi_i << endl;
  //Show the entries at the index that has the highest count
  entry* p = students.getTbl()[hi_i];
  while(p != NULL)
    {
      showInfo(*p);
      p = p->getNext();//traverse through the indexes
    }
  cout << endl;
}
