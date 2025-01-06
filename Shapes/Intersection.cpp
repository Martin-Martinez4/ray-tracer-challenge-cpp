
#include "Intersection.h"
#include <algorithm>
#include <cstddef>
#include <vector>

void Intersections::add(Intersection value){
 // loop through
  // if current t is less than [i].t insert before [i].t 
  // loop finsihes push to back
  for(size_t i = 0; i < inters.size(); ++i){
    if(value.t < inters[i].t){
      inters.insert(inters.begin()+i, value);
      return;
    }
  }

  inters.push_back(value);
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


