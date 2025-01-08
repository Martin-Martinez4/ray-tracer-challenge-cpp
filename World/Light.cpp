#include "Light.h"
#include "Material.h"
#include <iostream>
#include "Color.h"

Color lighting(Material material, Light light, Tuple point, Tuple eyeVec, Tuple normalVec, bool inShadow){
  Color black = Color(0,0,0);
  Color effectiveColor = material.color.multiply(light.intensity);
  Tuple lightVec = normalize(light.position.subtractTuple(point));
  Color ambient = effectiveColor.scalarMultiply(material.ambient);
  float lightDotNormal = lightVec.dot(normalVec);

  Color diffuse;
  Color specular;

  if(lightDotNormal < 0){
    diffuse = black;
    specular = black;
  }else{
    diffuse = effectiveColor.scalarMultiply(material.diffuse).scalarMultiply(lightDotNormal);

    Tuple refelctVec = -lightVec.reflect(normalVec);
    float reflectDotEye = refelctVec.dot(eyeVec);

    if(reflectDotEye <= 0){
      specular = black;
    }else{
      // seems expensive
      float factor = powf(reflectDotEye, material.shiniess);
      specular = light.intensity.scalarMultiply(material.specular * factor);
    }
  }

  return ambient.add(diffuse.add(specular));

}
