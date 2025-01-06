
#include "Intersection.h"
#include <algorithm>
#include <cstddef>
#include <vector>
#include <iostream>

class Shape;

void Intersections::add(Intersection value){
 // loop through
  // if current t is less than [i].t insert before [i].t 
  // loop finsihes push to back
  // std::sort(inters.begin(), inters.end(), [&](Intersection a, Intersection b){return a.t < b.t;});
  for(size_t i = 0; i < inters.size(); ++i){
    if(value.t < inters[i].t){
      inters.insert(inters.begin()+i, value);
      return;
    }
  }
 
  inters.push_back(value);
  
}

Intersection Intersections::get(size_t i) const {
  return inters[i];
};

size_t Intersections::size() const{
  return inters.size();
}

Intersection* Intersections::hit(){
  if(inters.size() == 0){
    return nullptr;
  }

  if(inters[0].t < 0 && inters[inters.size() - 1].t < 0){
    return nullptr;
  }

  for(size_t i = 0; i < inters.size(); ++i){
    if(inters[i].t >= 0){
      return &(inters[i]);
    }
  }

  return nullptr;
}

bool Intersections::equal(Intersections const& other) const{
  size_t s = size();
  if(s != other.size()){
    return false;
  }

  for(size_t i = 0; i < s; ++i){
    if((get(i).t != other.get(i).t) || (get(i).s != other.get(i).s)){
      return false;
    }
  }

  return true;

}


