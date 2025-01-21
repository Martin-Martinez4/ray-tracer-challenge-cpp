
#include "Intersection.h"
#include "Floats.h"
#include "Ray.h"
#include <cstddef>
#include <memory>
#include <vector>
#include <iostream>
#include <ostream>

class Shape;



Computations::Computations(Ray ray, Intersection intersection, std::shared_ptr<Intersections> xs){
  t = intersection.t; 
  object = intersection.s;
  point = ray.position(intersection.t);
  eyeV = ray.direction.negate();
  Tuple temp = ray.position(intersection.t);
  normalV = object->normalAt(temp, &intersection);


  if(normalV.dot(eyeV) < 0){
    inside = true;
    normalV = normalV.negate();
  }else{
    inside = false;
  }
  
  
  Tuple nvEp = normalV * EPSILON;
  reflectV = ray.direction.reflectBy(normalV);

  overPoint = point + nvEp;
  underPoint = point - nvEp;

  std::vector<const void *> container;
  
  for (std::size_t i = 0; i < xs->size(); ++i) {
    Intersection x = xs->get(i);
    if (intersection == x) {
      if (container.size() == 0) {
        n1 = 1.0f;
      } else {
        Shape *s = (Shape *)container.back();
        n1 = s->getMaterial().refractiveIndex;
      }
    }

    std::vector<const void *>::iterator it
      = std::find(container.begin(), container.end(), x.s);
    if (it != container.end()) {
      container.erase(it);
    } else {
      container.push_back(x.s);
    }

    if (intersection == x) {
      if (container.size() == 0) {
        n2 = 1.0f;
      } else {
        Shape *s = (Shape *)container.back();
        n2 = s->getMaterial().refractiveIndex;
      }
      return;
    }
  }



}

std::ostream& operator<<(std::ostream &os, const Intersection& i){
  return os << "t: " << i.t << " s: " << i.s << "\n";
}

std::ostream& operator<<(std::ostream &os, const Intersections& is){
  for(size_t i = 0; i < is.size(); ++i){
    os << is.inters[i] << "\n";
  }

  return os;
}

std::ostream& operator<<(std::ostream &os, const Computations& c){
 return os 
  << "t: " << c.t << "\n" 
  << "object: " << c.object << "\n" 
  << "point: " << c.point << "\n" 
  << "eyeV: " << c.eyeV << "\n" 
  << "normalV: " << c.normalV << "\n" 
  << "overPoint: " << c.overPoint << "\n"
  << "underPoint: " << c.underPoint << "\n"
  << "inside: " << c.inside << "\n"
  << "refelctV: " << c.reflectV << "\n" 
  << "n1: " << c.n1 << "\n" 
  << "n2: " << c.n2 << "\n";  
}


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

void Intersections::rayShapeIntersect(Ray ray, std::shared_ptr<Shape> shape){
  std::shared_ptr<Intersections> inters = shape->intersect(ray);

  if(inters == nullptr){
    return;
  }

  for(size_t i = 0; i < inters->size(); ++i){
    add(inters->get(i));
  }
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

