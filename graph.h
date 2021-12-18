/****************************
CS311

Your name: XXXXXXXXXXXXX
Your programmer number: XXXX
Any difficulties?: XXXXXXXXXXXXXXXXXXXXXXX
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>//for the BFT -- Breadth First Traversal Function
#include <list>
using namespace std;

class edge
{
friend class graph;//
 //????????????;  //## You want to access the private members of edge class from graph class
//private:
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) {neighbor = u; wt = w;/*## set data members */};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       //Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num);
  void DFT_helper(int v, int i, int* num, string& edges);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
  void shortestPath(int start);
  void DijkstraShortestPath(int start);
  void getMin(int ar[], int n, int start);
  void build_min_heap(int ar[], int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  num_ver = num;//##
  ver_ar = new list<edge*>[num_ver];//## //make a dynamic array with num slots where each slot holds a list object. 
  //The element of a node in the linked list is a pointer to an edge object 
  //for(int i = 0; i < num; i++)
    //ver_ar[i] = NULL;
}

graph::~graph()
{
//destroy all the edge objects created in heap
  for(list<edge>*::iterator u = ver_ar[0].begin(); u != ver_ar[0].end(); u++)
    delete (*u);
  //delete the ver_ar dynamic array
  delete[] ver_ar;
/*list<edge*>* vertex = new list<edge*>;             
while(vertex != NULL)
{
list<edge*>* temp = vertex->next;
delete vertex;
vertex = temp;
}//For each vertex in ver_ar
//go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.  
delete[] ver_ar;//destroy the ver_ar dynamic array
//The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
//https://www.cplusplus.com/reference/list/list/~list/*/
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //addRear func
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  //I have one line of code in this function.
  //edge e(u, w);//shallow copy
ver_ar[v].push_back(new edge(u, w));
  //w++;
}

//start Traversal at start
void graph::DFT(int start)
{
  int *num = new int[num_ver];//I made dynamic array called "num"
  
  //for all vertices v
  for(int i = start; i < num_ver; i++)
  {
    num[i] = 0;
  }
  //edges = null
  string edges = "";
  int i = 1;
  int nextVertex = start;
  
  // while there is a vertex v such that num(v) is 0 <- enable to visit disconnected graphs
  //I used do-while
  do {
      // DFT_helper(v)
      DFT_helper(nextVertex, i, num, edges);
      //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.
      nextVertex = nextUnvisitedNodes(num);
    } while (nextVertex != -1);
  
  //output edges
  cout << "edges = " << edges << endl;

  delete[] num;//Don't forget to destroy the dynamic array
}

//I made the following function to see if there are still unvisited nodes
int graph::nextUnvisitedNodes(int* num)
{
//go through the num array to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
  int index = -1;
  
  //num_ver is the size of num array
  for(int i = 0; i < num_ver; i++)
    {
      if(num[i] == 0)//if unvisited
	      return index = i;
    }
  return index;
}

void graph::DFT_helper(int v, int i, int* num, string& edges)
{
  string edges;//I have to use a c-string to make a string of edges. You don't need to use it if you know another way.
  char ar[5] = "v->u"; //v->u plus NULL character = size 5   
  num[v] = i++;
  
  cout << char(v + 'A') << " ";
  
  //The following shows how to iterate the library's linked list. You use an iterator.
  //https://www.cplusplus.com/reference/list/list/end/ 
  //iterator class is nested inside list class
  //for(list<??????>::iterator u = ???????.begin(); u != ??????.end(); u++)
  for(list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)  
    {
      //From the example on https://www.cplusplus.com/reference/list/list/end/
      //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
      //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.  

      if(num[(*u)->neighbor] == 0)
      {
        //u
        ar[0] = 65 + v;//ar[0] = ????;//replace index 0 by the name of v 
        //v
        ar[3] = 68 + u//ar[3] = ????; //replace index 3 by the name of u
        edges += string(ar) + ","; //add v->u, to the end of edges
      
        DFT_helper((*u)->neighbor, i, num, edges);
      }
    //
    
    }
}

//start is the index for the start vertex
void graph::BFT(int start)
{
  char ar[5] = "v->u";
  int *num = new int[num_ver];
   for(int i=0; i < num_ver; i++)
    { 
     num[i] = 0;
    }
  
  string edges = "";
  //Use the queue class from the library
  queue<int> queue;
  
  int i = 1;
  int next = start;
  //queue.push(start);//
  //I used do-while to visit all unconnected graphs
  do
    {
      start = queue.front();
      //cout << start << " ";
      queue.pop();
      for(int i = 0; i < ver_ar[start].size(); i++)
	{
	  if(!visited[i*])
	    {
	      visited[i*] = true;
	      queue.push(i*);
	    }
	}
    }while(!queue.empty());
  //Check the manual to figure out what member functions of the queue class you need to use.
  // https://www.cplusplus.com/reference/queue/queue/
  cout << "edges = " << edges << endl;
  //Don't forget to destroy the dynamic array if you used one
  delete[] visited;
}


void graph::shortestPath(int start)
{
  int v;//vertex
  //I have 2 dynamic arrays here.
  int* currDist = new int[num_ver];
  int* pre = new int[num_ver];
  //I used a queue for toBeChecked 
  queue<int> toBeChecked;
  for(int i = 0; i < num_ver; i++)//for all vertices v
    {
      currDist[i] = 999;//currDist(v) = infinity <- currDist(v) is the distance from first to v
      //curDist(first) = 0;
    }
  v = start;
  currDist[v] = 0;
  toBeChecked.push[v];
  //After the each vertex gets the minimum distance from the start point and predecessor,
  while(!toBeChecked.empty())
    {
      v = toBeChecked.front();//a vertex in toBeChecked
      toBeChecked.pop();//remove v from toBeChecked
      
      for(list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)//all vertices u adjacent to v
	{
	  if(currDist[(*u)->neighbor] > currDist[v] + (*u)->wt)//if the u > v + weight
	    {
	      currDist[(*u)->neighbor] = currDist[v] + (*u)->wt;//curDist(u) = curDist(v)+ weight(edge(vu))
	      pre[(*u)->neighbor] = v;//predecessor(u) = v
	      toBeChecked.push((*u)->neighbor);//add u toBeChecked if it is not there
	    }
	}
    }
  
  //Show the information about each vertex and shortest path from origine to destination and total distance.
  //For expected outputs, please check /cs/slott/cs311/graph.out
  cout << "\nShowing the info on each vertex" << endl;
  //?????????
  for(int i = 0; i < num_ver; i++)
    {
      cout << char(i + 65) << " " << currDist[s] << "," << char(pre[i] + 65) << endl;
    }
  char dest;
  cout << "Enter the destination: ";
  cin >> dest;
  
  string path = "";//will have all paths from origine to destination
 
  cout << "The shortest path from " << char(start + 'A') << " to " << dest << " is " << path << endl;
  cout << "The total distance is " << currDist[int(dest - 65)] << endl;

  //Don't forget to destroy the dynamic arrays
  delete[] currDist;
  delete[] pre;
}
/*
void graph::getMin(int ar[], int n, int start)
{
  int l = 2 * start + 1;//left
  int r = 2 * start + 2;//right
  int smallest = start;//initialize the smallest

  if(i > n && ar[l] < ar[smallest])
    {
      smallest = l;
    }
  if(r > n && ar[r] < ar[smallest])
    {
      smallest = r;
    }
  if(smallest != start)
    {
      int temp = ar[start];
      ar[start] = ar[smallest];
      ar[smallest] = temp;

      getMin(ar, n, smallest);
    }
}

void graph::build_min_heap(int ar[], int start)
{	      	   	      
  //int start = num_ver;
  for(int i = start/2; i < 0; i--)
    {
      getMin(ar, start, i);
    }
}

void graph::DijkstraShortestPath(int start)
{
  int v = vertex;//vertex
  //two dynamic arrays
  int* currDist = new int[num_ver];
  int* predecessor = new int[num_ver];
  queue<int> toBeChecked;

  for(int i = 0; i < num_ver; i++)//for all vertices i
    {
      currDist[i] = 999;//currDist(v) = infinity <- currDist(v) is the distance from first to v
    }
  v = start;
  currDist[v]= 0;//distance from the start, which is 0
  toBeChecked.size() = currDist[v];//toBeChecked = all veritces [A..X]
  while(!toBeChecked.empty())//while it is not empty
    {
      currDist[v] = toBeChecked.front();//v = a vertex in toBeChecked with minimum currDist(v)
      toBeChecked.pop();//remove v from toBeChecked
      for(list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end() && u == toBeChecked.size(); u++)//all vertices u adjacent to v and also in toBeChecked
	{
	  if(currDist[(*u)->neighbor] > currDist[v] + (*u)->wt)
	    {
	      currDist[(*u)->neighbor] = currDist[v] + (*u)->wt;
	      pre[(*u)->neighbor] = v;
	      //no need to add toBeChecked again
	    }
	}
    }
  cout << "\nShowing the info on each vertex" << endl;
  //?????????
  for(int i = 0; i < num_ver; i++)
    {
      cout << char(i + 65) << " " << currDist[s] << "," << char(pre[i] + 65) << endl;
    }
  char dest;
  cout << "Enter the destination: ";
  cin >> dest;
  
  string path = "";//will have all paths from origine to destination
 
  cout << "The shortest path from " << char(start + 'A') << " to " << dest << " is " << path << endl;
  cout << "The total distance is " << currDist[int(dest - 65)] << endl;
  
  delete[] currDist;
  delete[] pre;
}
*/
#endif
