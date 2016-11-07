#include <cstdint>
#include <vector>

namespace minmaxheap
{

class mmheap
{
public:
  mmheap (uint32_t capacity);
  virtual ~mmheap ();
  void buildHeap (const std::vector<int32_t> &vals);
  int32_t getMin () const;
  int32_t getMax () const;
  void insert (int32_t val);
  void deleteMin ();
  void deleteMax ();

private:
  bool isAtMinLevel (uint32_t index) const;
  void percolateDown (uint32_t index);
  void percolateDownMin (uint32_t index);
  void percolateDownMax (uint32_t index);
  void percolateUp (uint32_t index);
  void percolateUpMin (uint32_t index);
  void percolateUpMax (uint32_t index);
  // add your own private functions here, if any
  void resize();
  void swap(uint32_t index1, uint32_t index2);
  uint32_t smallestDescendent(uint32_t index);
  uint32_t biggestDescendent(uint32_t index);
  bool isGrandchild(uint32_t smallest, uint32_t grandparent);
private:
  int32_t *_arr;
  uint32_t _capacity;
  uint32_t _size;
};

} /* minmaxheap */ 
