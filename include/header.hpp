// Copyright 2021 Новожильцев Яков xaxaxaxa232@mail.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <atomic> //atomarnie vichislenya
#include <utility>

using std::move;
using std::atomic_uint;

template <typename T> //Dlya raboti so vsemi tipami(shablonnii class)

class SharedPtr {
 public:
  SharedPtr(): pointer(nullptr), counter(0){}//default constructor

  explicit SharedPtr(T* newPointer) { //explicit dlya zapreta neyavnogo privideniya;esh'e odin constructor
    pointer=newPointer;
    if (newPointer == nullptr){
      counter = nullptr;
    } else {
      counter = new std::atomic_uint ;
      *counter=1;
    }
  };

  SharedPtr(const SharedPtr& sharedPtr){ // constructor copy
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

  SharedPtr& operator=(const SharedPtr& sharedPtr){ //peregruska oeratora copy(=)
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

  SharedPtr(SharedPtr&& sharedPtr){ //constructor move
    if (sharedPtr.pointer) {
      pointer = sharedPtr.pointer;
      counter = sharedPtr.counter;
      sharedPtr.pointer = nullptr;
      sharedPtr.counter = nullptr;
    }
  };
  SharedPtr& operator=(SharedPtr&& sharedPtr){ //peregruska oeratora move(=)
    if (this != &sharedPtr) {
      pointer = move(sharedPtr.pointer);
      counter = move(sharedPtr.counter);
    }
    return *this;
  };

  ~SharedPtr(){ //destructor
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

  operator bool() const{ //proverka, ykasivaet li ykazatel' na object
    if(pointer)
      return true;
    else
      return false;
  }

  T& operator*() const { //peregruska rasiminovaniya dlya SharedPtr
    if(pointer)
      return *pointer;
    else
      return nullptr;
  }

  T* operator->() const{  //peregruska obrash'eniya k poly dlya SharedPtr
    return pointer;
  }

  T* get() {  // metod get dlya SharedPtr
    return pointer;
  }

  void reset() { //obnylenie
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
//    T* tmpPointer(move(sharedPtr.pointer));
//    sharedPtr.pointer = move(pointer);             КОД!!!!!!
//    pointer=move(tmpPointer);
    T* tmpPointer = sharedPtr.pointer;
    sharedPtr.pointer = pointer;
    pointer = tmpPointer;
    atomic_uint* tmpCounter = sharedPtr.counter;
    sharedPtr.counter = counter;
    counter = tmpCounter;
  };

size_t use_count() const{ //vosvrash'aet kol-vo object SharedPtr, na odin object
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
