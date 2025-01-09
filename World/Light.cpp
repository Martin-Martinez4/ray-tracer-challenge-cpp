#include "Light.h"
#include "Material.h"
#include <cmath>
#include <iostream>
#include "Color.h"

Color lighting(Material material, Light light, Tuple point, Tuple eyeVec, Tuple normalVec, bool inShadow){
  Color black = Color(0,0,0);
  Tuple t = light.position.subtractTuple(point);
  Color effectiveColor = material.color.multiply(light.intensity);
  Tuple lightVec = normalize(t);
  Color ambient = effectiveColor.scalarMultiply(material.ambient);
  float lightDotNormal = lightVec.dot(normalVec);

  Color diffuse;
  Color specular;

  if(lightDotNormal < 0){
    diffuse = black;
    specular = black;
  }else{
    diffuse = effectiveColor.scalarMultiply(material.diffuse);
    diffuse = diffuse.scalarMultiply(lightDotNormal);
    
    Tuple reflectVec = lightVec.multiplyScalar(-1);
    reflectVec = lightVec.reflect(normalVec);
    float reflectDotEye = reflectVec.dot(eyeVec);

    if(reflectDotEye > 0){
      // seems expensive
      float factor = powf(reflectDotEye, material.shiniess);
      specular = light.intensity.scalarMultiply(material.specular * factor);
    }
  }

  return ambient.add(diffuse.add(specular));

}
