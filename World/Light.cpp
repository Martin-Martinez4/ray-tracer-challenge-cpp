#include "Light.h"
#include "Material.h"
#include <cmath>
#include <iostream>
#include "Color.h"

Color lighting(Material material, Light light, Tuple point, Tuple eyeVec, Tuple normalVec, bool inShadow){

  Color effectiveColor = material.color.multiply(light.intensity);
  
  Tuple temp = light.position.subtractTuple(point);
  Tuple lightVec = normalize(temp);
  Color ambient = effectiveColor.scalarMultiply(material.ambient);
  float lightDotNormal = lightVec.dot(normalVec);


  Color diffuse;
  Color specular;


  if(lightDotNormal < 0){
    diffuse = Color(0,0,0);
    specular = Color(0,0,0);
  }else{
    diffuse = effectiveColor.scalarMultiply(material.diffuse).scalarMultiply(lightDotNormal);
    
  
    Tuple reflectVec = lightVec.negate();
    reflectVec = reflectVec.reflectBy(normalVec);

    float reflectDotEye = reflectVec.dot(eyeVec);

    if(reflectDotEye <= 0){
      specular = Color(0,0,0);
    }else{

      // seems expensive
      float factor = pow(reflectDotEye, material.shininess);
      specular = light.intensity.scalarMultiply(material.specular).scalarMultiply(factor);
    }
  }
  return ambient.add(diffuse).add(specular);
}


