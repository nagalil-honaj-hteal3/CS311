#include <iostream>
#include <fstream>
using namespace std;
#include "graph.h"

int main()                                                                     

{
  cout << "testing unweighted graph--------------------" << endl;
                                                                               

  graph g(9); //a to i

  ifstream fin;
  fin.open("graph.in");
  int v, u, w; //v --> u
               //  w

  if(!fin)
    cout << "graph.in doesn't exist" << endl;
  else
    {
      fin >> v >> u;
      while(fin)
        {
          g.addEdge(v,u);
          fin >> v >> u;
        }

      cout << "BFS: ";                                                         

      g.BFT(0);                                                                

      cout << "DFS: ";                                                         

      g.DFT(0);
    }                                                                          

  fin.close();

  cout << "testing weighted graph--------------------" << endl;
  graph g2(10); //a to j
  fin.open("graph2.in");
  if(!fin)
    cout << "graph2.in doesn't exist" << endl;
  else
    {
      fin >> v >> u >> w;
      while(fin)
        {
          g2.addEdge(v,u, w);
          fin >> v >> u >> w;
        }

      cout << "BFS: ";
      g2.BFT(0);
      cout << "DFS: ";
      g2.DFT(0);
      cout << "Shortest Path: ";
      g2.shortestPath(3);
    }
  fin.close();    
  
  ///** FOR WEIGHTED GRAPHS, DO I NEED TO MAKE A CONSTRUCTOR? ANSWER: NO **/
  //cout << "testing weighted graph--------------------" << endl;
  //graph g2(10); //a to j
  //fin.open("graph2.in");
  //if(!fin)
  //  cout << "graph2.in doesn't exist" << endl;
  //else
  //  {
  //    fin >> v >> u >> w;
  //    while(fin)
  //      {
  //        g2.addEdge(v,u, w);
  //        fin >> v >> u >> w;
  //      }

  //    cout << "BFS: ";
  //    g2.BFT(0);
  //    cout << "DFS: ";
  //    g2.DFT(0);
  //    cout << "Shortest Path: ";
  //    g2.shortestPath(3);
  //  }
  //fin.close();

  return 0;                                                                    \

}
