#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm> 

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int arity;
  PComparator comp;
  
  void heapifyUp(int index);
  void heapifyDown(int index);
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : arity(m), comp(c) {
}
//construc and initialize
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {
}
// deconstruct and clean
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  data.push_back(item);
  heapifyUp(data.size() - 1);
}
//call heapifyy put back in line

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data.front();
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    
    throw std::underflow_error("Heap is empty");
  }
  data.front() = data.back();
  data.pop_back();
  if(!empty()){
    heapifyDown(0);
  }
}
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  return data.empty(); //empty 
}
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return data.size();
}
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyUp(int index) {
  while(index > 0) {
    int parent = (index - 1) / arity;
    if(comp(data[index], data[parent])) {
      std::swap(data[index], data[parent]);
      index = parent;
    } else {
      break;
    }
  }
}
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyDown(int index) {
  int n = data.size();
  while(true) {
    int best = index;
    for (int i = 1; i <= arity; i++) {
      int child = arity * index + i;
      if(child < n && comp(data[child], data[best])) {
        best = child;
      }
    }
    if(best != index) {
      std::swap(data[index], data[best]);
      index = best;
    } else {
      break;
    }
  }
}
#endif

//worked 3/8