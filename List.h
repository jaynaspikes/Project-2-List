#ifndef DL_LIST_H
#define DL_LIST_H
#include <iostream>
#include <initializer_list>

namespace cop4530 {

    template <typename T>
    class List {
        private:
          // nested Node class
          struct Node {
             T data;
             Node *prev;
             Node *next;
    
             Node(const T & d = T{}, Node *p = nullptr, Node *n = nullptr) 
                : data{d}, prev{p}, next{n} {}
             Node(T && d, Node *p = nullptr, Node *n = nullptr)
                : data{std::move(d)}, prev{p}, next{n} {}
          };
    
       public:
          //nested const_iterator class
          class const_iterator {
             public:
                const_iterator() : current{nullptr}
                {}            // default zero parameter constructor
    
                const T & operator*() const {return retrieve();} // operator*() to return element
     
                // increment/decrement operators
                const_iterator & operator++()
                {
                    current = current->next;
                    return *this;
                }
    
                const_iterator operator++(int)
                {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }
    
                const_iterator & operator--()
                {
                    // TO BE FILLED
                    current = current -> next;
                    return *this;
                }
    
                const_iterator operator--(int)
                {
                    // TO BE FILLED
                    const_iterator replace = *this;
                    --(*this);
                    return replace;
                }
    
                // comparison operators
                bool operator==(const const_iterator &rhs) const
                {
                    return current == rhs.current;
                }
       
                bool operator!=(const const_iterator &rhs) const
                {
                    return !(*this == rhs);
                }
    
             protected:
                Node *current;              // pointer to node in List
    
                // retrieve the element refers to
                T & retrieve() const
                {
                    return current->data;
                }
    
                const_iterator(Node *p) : current{p}    // protected constructor
                {
                }
    
                friend class List<T>;
          };
    
          // nested iterator class
          class iterator : public const_iterator {
             public:
                iterator()
                {}
    
                T & operator*()
                {
                    return const_iterator::retrieve();
                }
    
                const T & operator*() const
                {
                    return const_iterator::operator*();
                }
    
                // increment/decrement operators
                iterator & operator++()
                {
                    this->current = this->current->next;
                    return *this;
                }
    
                iterator operator++(int)
                {
                    iterator old = *this;
                    ++(*this);
                    return old;
                }
    
                iterator & operator--()
                {
                    // TO BE FILLED
                    this->current=this->current->prev;
                    return *this;
                }
    
                iterator operator--(int)
                {
                    // TO BE FILLED
                    iterator elder = *this;
                    --(*this);
                    return elder;
                }
    
             protected:
                iterator(Node *p): const_iterator{p}
                {}
    
                friend class List<T>;
          };
    
       public:
          // constructor, desctructor, copy constructor
    
          // default zero parameter constructor
          List()
          {
              init();
          }
    
          List(const List &rhs)
          {
              init();
              for(auto & x: rhs)
                  push_back(x);
          }
    
          // move constructor
          List(List && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
          {
              rhs.theSize = 0;
              rhs.head = nullptr;
              rhs.tail = nullptr;
          }
           
           //could be this 
          // num elements with value of val
          explicit List(int num, const T& val = T{})
          {
              // TO BE FILLED
              init();
              for(int i = 0; i< num; i++)
              {
                push_back(val);
              }  
          }
           //seg fault
          //constructs with elements [start, end)
          List(const_iterator start, const_iterator end)
          {
              // TO BE FILLED
              init();
              const_iterator createit = start;
              while(createit != end)
              {
                push_back(*createit);
                createit++;
              }
          } 
    
          // constructs with a copy of each of the elements in the initalizer_list
          List (std::initializer_list<T> iList)
          {
              // TO BE FILLED
              init();
              for (auto i: iList)
                push_back(i);
          }
    
          // destructor
          ~List()
          {
              clear();
              delete head;
              delete tail;
          }
    
          // copy assignment operator
          const List& operator=(const List &rhs)
          {
              if(this == &rhs)
                  return *this;
    
              List copy = rhs;
              std::swap(*this, copy);
              // The following should work too.
              List(rhs.begin(), rhs.end());
              return *this;
          }
    
          // move assignment operator
          List & operator=(List && rhs)
          {
              std::swap(theSize, rhs.theSize);
              std::swap(head, rhs.head);
              std::swap(tail, rhs.tail);
              return *this;
          }
    
    	  // sets list to the elements of the initializer_list
          List& operator= (std::initializer_list<T> iList)
          {
              // TO BE FILLED
              init();
              for(auto i : iList)
                push_back(i);
                return *this;

          }
    
    
          // member functions
    
          int size() const {return theSize;}       // number of elements
          bool empty() const {return theSize == 0;}     // check if list is empty
    
          // delete all elements
          void clear() 
          {
              while(! empty())
                  pop_front();
          }
    
          // BONUS POINTS
          // reverse the order of the elements
          void reverse()
          {
            if(theSize <= 1)
                return;
            Node* current = head;

            while(current != nullptr)
            {
               std::swap(current->prev,current->next);
               current = current->prev;
            }
            std::swap(head,tail);
          }
          
    
          T& front(){return *begin();}             // reference to the first element
          const T& front() const{return *begin();}
          T& back(){return *(--end());}              // reference to the last element
          const T& back() const{return *(--end());} 
    
          void push_front(const T & val){insert(begin(), val);} // insert to the beginning
          void push_front(T && val){insert(begin(), std::move(val));}      // move version of insert
          void push_back(const T & val){insert(end(), val);}  // insert to the end
          void push_back(T && val){insert(end(), std::move(val));}       // move version of insert
          void pop_front(){erase(begin());}               // delete first element
          void pop_back(){erase(--end());}                // delete last element
    
          // remove all elements with value = val
          void remove(const T &val)
          {
              // TO BE FILLED
              iterator I = begin();
              for(;I != end(); I++)
              {
                if(*I != val)
                    continue;
                else
                {
                    I = erase(I);
                    I--;
                }
              }
          }
    
    	  // remove all elements for which Predicate pred
          //  returns true. pred can take in a function object
    	  template <typename PREDICATE>
    	  void remove_if(PREDICATE pred)
          {
              // TO BE FILLED
              iterator I = begin();
              for(;I!= end(); I++)
              {
                if(pred(*I))
                {
                    I = erase(I);
                    I--;
                }
                else
                {
                    //I++;
                    continue;
                }
              }
          }
    
          // print out all elements. ofc is deliminitor 
          void print(std::ostream& os, char ofc = ' ') const
          {
              // TO BE FILLED
              if(theSize == 0)
              return;
              const_iterator I = begin();
              os << *I ++;
              for(; I != end(); I++)
                os << ofc << *I;   
          }
    
          iterator begin(){return iterator(head->next);}               // iterator to first element
          const_iterator begin() const{return const_iterator(head->next);}
          iterator end(){return iterator(tail);}                 // end marker iterator
          const_iterator end() const{return const_iterator(tail);} 
    
          // insert val ahead of itr
          iterator insert(iterator itr, const T& val)
          {
              Node *p = itr.current;
              theSize ++;
              return iterator{p->prev = p->prev->next = new Node(val, p->prev, p)};
          }
    
          // move version of insert
          iterator insert(iterator itr, T && val)
          {
              Node *p = itr.current;
              theSize ++;
              return iterator{p->prev = p->prev->next = new Node(std::move(val), p->prev, p)};
          }
    
          // erase one element
          iterator erase(iterator itr)
          {
              Node *p = itr.current;
              iterator I = ++itr;
              p->prev->next = p->next;
              p->next->prev = p->prev;
              theSize --;
              delete p;
              return I;
          }
    
          // erase [start, end)
          iterator erase(iterator start, iterator end)
          {
              iterator I = start;
              while(I != end)
                  I = erase(I);
              return I;
          }
    
    
       private:
          int theSize;           // number of elements
          Node *head;            // head node
          Node *tail;            // tail node
      
          // initialization
          void init(){
              theSize = 0;
              head = new Node;
              tail = new Node;
              head->next = tail;
              tail->prev = head;
          }
    };
    // overloading comparison operators
    template <typename T>
    bool operator==(const List<T> & lhs, const List<T> &rhs)
    {
        if(lhs.size() != rhs.size())
            return false;
        typename List<T>::const_iterator Ir = rhs.begin();
        typename List<T>::const_iterator Il = lhs.begin();
        for(; Il != lhs.end(); Il ++)
        {
            if(*Il != *Ir)
                return false;
            Ir ++;
        }
        return true;
    }
   
    template <typename T>
    bool operator!=(const List<T> & lhs, const List<T> &rhs)
    {
        return ! (lhs == rhs);
    }
    
    // overloading output operator
    template <typename T>
    std::ostream & operator<<(std::ostream &os, const List<T> &l)
    {
        // TO BE FILLED
        l.print(os);
        return os;
    }


} // end of namespace 4530

#endif
