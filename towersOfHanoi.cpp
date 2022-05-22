#include <iostream>
using namespace std;

void towersOfHanoi(int n, int from, int to, int spare)
{
  if(n == 1)
    cout << "Moving the disk from " << from << " to " << to;
  else
    {
      towersOfHanoi(n-1, from, spare, to);
      towersOfHanoi(1, from, to, spare);
      towersOfHanoi(n-1, spare, to, from);
    }
}

int main()
{
  moves = 0;
  cout << towersOfHanoi() << endl;
}

