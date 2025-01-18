#include "Light.h"
#include <cmath>
#include <iostream>
#include "Color.h"

Color lighting(Material material, Shape* shape, Light light, Tuple point, Tuple eyeVec, Tuple normalVec, bool inShadow){

  Color color;

  if(shape->getMaterial().pattern == nullptr){
    color = material.color;
    
  }else{
    color = shape->patternAtShape(point);
  }


  Color effectiveColor = material.color.multiply(light.intensity);
  
  Tuple temp = light.position - point;
  Tuple lightVec = normalize(temp);
  Color ambient = effectiveColor * material.ambient;
  float lightDotNormal = lightVec.dot(normalVec);


  Color diffuse;
  Color specular;


  if(lightDotNormal < 0){
    diffuse = Color(0,0,0);
    specular = Color(0,0,0);
  }else{
    diffuse = effectiveColor * material.diffuse;
    diffuse = diffuse * lightDotNormal;
    
  
    Tuple reflectVec = lightVec.negate();
    reflectVec = reflectVec.reflectBy(normalVec);

    float reflectDotEye = reflectVec.dot(eyeVec);

    if(reflectDotEye > 0){
      float factor = pow(reflectDotEye, material.shininess);
      specular = light.intensity * material.specular * factor;
    }
  }

  if(inShadow){
    return ambient;
  }
  return ambient.add(diffuse.add(specular));
}


