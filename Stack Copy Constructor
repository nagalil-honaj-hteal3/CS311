# CS311
Data Structures and Algorithms - CSUSM

Copy Constructor for Stack LL
template <class T>
void Stack<T>::copy(const Stack<T>& source)
{
  this->top = new Node<T> (source.top->elem);//stores the top with the passed in element
  this->size++;//starts the size by one
  Node<T>* p = source.top->next;//this will be used to initialize the source to continue down the stack
  while(p != NULL)//once the pointer has went to all the other pointers inside the memory
    {
      Node<T>* n = source.top;//points n to the top and will be used inside the while loop
      n->next = new Node<T>(p->elem);//this would be used to store the elements
      this->size++;//incrementing the size inside the stack
      p = p->next;//shifts the p to the other parts in the stack from top
      n = n->next;//shifts the n to the other parts in the stack with the elements stored
    }
}
