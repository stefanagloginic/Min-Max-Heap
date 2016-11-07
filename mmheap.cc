#include "mmheap.h"

namespace minmaxheap{
  mmheap::mmheap(uint32_t capacity){
    _arr = new int32_t [capacity];
    _size = 0;
    _capacity = capacity;
  }

  mmheap::~mmheap(){
    delete[] _arr;
  }

  void mmheap::buildHeap(const std::vector<int32_t>& vals){
    delete[] _arr;
    _arr = new int32_t[_capacity];
    _size = vals.size();
    
    for(int i = 0; i < vals.size(); ++i){
      _arr[i+1] = vals[i];
    }
    
    uint32_t parent = _size/2;
    
    for(; parent > 0; parent--){
      percolateDown(parent);
    }
    return;
  }

  int32_t mmheap::getMin() const{
    if(_size == 0){ return 0;}

    return _arr[1];
  }

  int32_t mmheap::getMax() const{
    if(_size == 0){return 0;}
    
    else if(_size == 1 || _size == 2){return _arr[_size];}
      if(_arr[2] > _arr[3]){
	return _arr[2];
      }
      
      return _arr[3];
  }
    
    

    void mmheap::insert(int32_t val){
      _size++;
      if(_size == _capacity){
	resize();
      }
      _arr[_size] = val;
      percolateUp(_size);
      
    }

    void mmheap::deleteMin(){
      if(_size == 0){return;}
      if(_size == 1){
	_size--;
	return;
      }

      _arr[1] = _arr[_size];
      _size--;

      percolateDown(1);
      return;
    }

    void mmheap::deleteMax(){
      if(_size == 0){return;}
      if(_size <= 2){
	_size--;
	return;
      }
      else if(_arr[2] > _arr[3]){
	_arr[2] = _arr[_size];
	_size--;
	percolateDown(2);
      }
      else{
	_arr[3] = _arr[_size];
	_size--;
	percolateDown(3);
      }
      return;
    }

    bool mmheap::isAtMinLevel(uint32_t index) const{
      int cnt = 0;
      index/=2;
      while(index != 0){
	++cnt;
	index/=2;
      }
      if(cnt%2 == 0){
	return true;
      }
      return false;
    }

    void mmheap::percolateDown(uint32_t index){
      if(!isAtMinLevel(index)){
	percolateDownMax(index);
      }
      else{
	percolateDownMin(index);
      }
    }

    void mmheap::percolateDownMin(uint32_t index){
      uint32_t smallestChild = smallestDescendent(index);
      if(smallestChild != index){
	if(isGrandchild(smallestChild, index)){//is the value we got a grandchild?
	  if(_arr[smallestChild] < _arr[index]){
	    swap(smallestChild, index);
	    if(_arr[smallestChild] > _arr[smallestChild/2]){//did swap put a value bigger than the max above?
	      int check = smallestChild/2;
	      if(check!=0){swap(smallestChild, smallestChild/2);}
	    }
	    percolateDownMin(smallestChild); //recursive call, need to check further down
	  }
	}
	else{//it is a child
	  if(_arr[smallestChild] < _arr[index]){
	    swap(smallestChild, index);
	  }
	}
      }
      return;
    }

    void mmheap::percolateDownMax(uint32_t index){
      uint32_t biggestChild = biggestDescendent(index);
      if(biggestChild != index){
	if(isGrandchild(biggestChild, index)){
	  if(_arr[biggestChild] > _arr[index]){
	    swap(biggestChild, index);
	    if(_arr[biggestChild] < _arr[biggestChild/2]){
	      int check = biggestChild/2;
	      if(check!=0){swap(biggestChild, biggestChild/2);}
	    }
	    percolateDownMax(biggestChild);
	  }
	}
	else{
	  if(_arr[biggestChild] > _arr[index]){
	    swap(biggestChild, index);
	  }
	}
      }
      return;
    }

    void mmheap::percolateUp(uint32_t index){
      if(index == 1){return;} //can't move up any further

      uint32_t parent = index/2;

      if(!isAtMinLevel(index)){
	if(_arr[index] < _arr[parent]){
	  swap(index, parent);
	  percolateUpMin(parent);
	}
	else{percolateUpMax(index);}
      }
      else{
	if(_arr[index] > _arr[parent]){
	  swap(index, parent);
	  percolateUpMax(parent);
	}
	else{percolateUpMin(index);}
      }
    }

    void mmheap::percolateUpMin(uint32_t index){
      if(index == 1){return;}

      uint32_t grandparent = index/4;

      if(_arr[index] < _arr[grandparent]){
	swap(index, grandparent);
	percolateUpMin(grandparent);
      }
      
      return;
    }

    void mmheap::percolateUpMax(uint32_t index){
      if(index == 1 || index == 2 || index == 3){return;}

      uint32_t grandparent = index/4;

      if(_arr[index] > _arr[grandparent]){
	swap(index, grandparent);
	percolateUpMax(grandparent);
      }

    }

    void mmheap::resize(){
      _capacity*=2;

      int32_t *temp = _arr;

      _arr = new int32_t[_capacity];

      for(int i = 1; i < _size; i++){
	_arr[i] = temp[i];
      }

      delete[] temp;
    }

    void mmheap::swap(uint32_t index1, uint32_t index2){
      int32_t temp = _arr[index1];

      _arr[index1] = _arr[index2];
      _arr[index2] = temp;
      
      return;
      
    }

  uint32_t mmheap::smallestDescendent(uint32_t index){
    uint32_t smallestDescendent = index*2;
    
    if(smallestDescendent > _size){return index;}
    
    if(smallestDescendent+1 > _size){return smallestDescendent;}
    
    if(_arr[smallestDescendent] > _arr[smallestDescendent+1]){smallestDescendent++;}
    
    uint32_t grandchild = index*4;
    
    for(int i = 0; i < 4; ++i){
      if(grandchild > _size){return smallestDescendent;}
      if(_arr[smallestDescendent] > _arr[grandchild]){smallestDescendent = grandchild;}
      grandchild++;
    }
    return smallestDescendent;
  }

  uint32_t mmheap::biggestDescendent(uint32_t index){
    uint32_t biggestDescendent = index*2;

    if(biggestDescendent > _size){return index;}

    if(biggestDescendent+1 > _size){return biggestDescendent;}

    if(_arr[biggestDescendent] <  _arr[biggestDescendent+1]){biggestDescendent++;}
    

    uint32_t grandchild = index*4;

    for(int i = 0; i < 4; ++i){
      if(grandchild > _size){return biggestDescendent;}
      if(_arr[biggestDescendent] < _arr[grandchild]){biggestDescendent = grandchild;}
      grandchild++;
    }
    return biggestDescendent;
  }

  bool mmheap::isGrandchild(uint32_t smallest, uint32_t grandparent){
    if(smallest/4 == grandparent){return true;}
    return false;
  }
}
