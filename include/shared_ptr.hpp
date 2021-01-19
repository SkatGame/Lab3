// Copyright 2021 Новожильцев Яков xaxaxaxa232@mail.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <atomic>
#include <utility>

using std::move;
using std::atomic_uint;

template <typename T>
class SharedPtr {
 public:
 SharedPtr(): pointer(nullptr), counter(nullptr){}

  explicit SharedPtr(T* newPointer) {
    pointer=newPointer;
    if (newPointer == nullptr){
      counter = nullptr;
    } else {
      counter = new std::atomic_uint ;
      *counter=1;
    }
  };

  SharedPtr(const SharedPtr& sharedPtr){
    if (sharedPtr.pointer){
      pointer = sharedPtr.pointer;
      counter = sharedPtr.counter;
      if  (pointer){
        *counter = *counter+1;
      } else {
        counter = nullptr;
      }
    }
  };

  SharedPtr(SharedPtr&& sharedPtr) noexcept {
    if (sharedPtr.pointer) {
      sharedPtr.pointer = nullptr;
      sharedPtr.counter = nullptr;
      pointer = move(sharedPtr.pointer);
      counter = move(sharedPtr.counter);
    }
  };

  SharedPtr& operator=(const SharedPtr& sharedPtr){
    if (this != &sharedPtr) {
      pointer = sharedPtr.pointer;
      counter = sharedPtr.counter;
      if  (pointer){
        *counter = *counter+1;
      } else {
        counter = nullptr;
      }
    }
    return *this;
  };

  SharedPtr& operator=(SharedPtr&& sharedPtr) noexcept {
    if (this != &sharedPtr) {
      pointer = move(sharedPtr.pointer);
      counter = move(sharedPtr.counter);
    }
    return *this;
  };

  ~SharedPtr(){
    if(counter){
      if(*counter==1) {
        delete pointer;
        delete counter;
      } else {
        *counter = *counter-1;
      }
    }
    pointer = nullptr;
    counter = nullptr;
  }

  operator bool() const{
    if(pointer)
      return true;
    else {
      return false;
    }
  }

  T& operator*() const {
    if(pointer)
      return *pointer;
    else
      return nullptr;
  }

  T* operator->() const{
    return pointer;
  }

  T* get() {
    return pointer;
  }

  void reset() {
    if(*counter==1){
      delete pointer;
      delete counter;
    }else{
      *counter=*counter-1;
    }
    pointer=nullptr;
    counter=nullptr;
  }

  void reset(T* point){
    if(*counter==1){
      delete pointer;
      delete counter;
    }else {
      *counter = *counter - 1;
    }
    pointer=point;
    if(point==nullptr){
      counter=nullptr;
    }else{
      counter=new atomic_uint;
      *counter=1;
    }
  };

  void swap(SharedPtr& sharedPtr){
    T* tmpPointer = sharedPtr.pointer;
    sharedPtr.pointer = pointer;
    pointer = tmpPointer;
    atomic_uint* tmpCounter = sharedPtr.counter;
    sharedPtr.counter = counter;
    counter = tmpCounter;
  };

[[nodiscard]] size_t use_count() const{
  if(counter){
    return *counter;
  }else{
    return 0;
  }
}

 private:
  T* pointer;
  atomic_uint* counter;
};

#endif // INCLUDE_HEADER_HPP_
