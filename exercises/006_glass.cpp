
#include "006_glass.h"
#include "Camera.h"
#include "Canvas.h"
#include "Checker.h"
#include "Color.h"
#include "Pattern.h"
#include "Plane.h"
#include "Shape.h"
#include "Sphere.h"
#include "Light.h"
#include "World.h"
#include <array>
#include <memory>
#include <cmath>
#include <vector>


Canvas Ex006(){
  
  Color white = Color(1,1,1);
  Color faluRed = Color(0.47f, 0.125f, 0.0889f);
  Color bbPowder = Color(0.98f, 0.992f, 0.965f);
  Color moonStone = Color(0.2745f, 0.6745f, 0.76f);
  
  std::shared_ptr<Pattern> checker (new Checker(moonStone, bbPowder));

  Material floorMat = Material(bbPowder, checker);
  floorMat.specular = 0;
  floorMat.ambient = 0.8f;
  floorMat.diffuse = 0.2f;

  std::shared_ptr<Shape> floor (new Plane(floorMat));
  floor->setTransforms({
    Matrix::rotationAlongX(1.5708f),
    Matrix::translate(0, 0, 10),
  });

  Material biggerMat = Material(Color(1,1,1));
  biggerMat.diffuse = 0;
  biggerMat.ambient = 0;
  biggerMat.shininess = 300;
  biggerMat.reflective = 0.9f;
  biggerMat.transparency = 0.9f;
  biggerMat.specular = 0.9f;
  biggerMat.refractiveIndex = 1.53f;
  
  std::shared_ptr<Shape> bigger (new Sphere(biggerMat));

  Material smallerMat = Material(Color(1,0,0));
  smallerMat.diffuse = 0;
  smallerMat.ambient = 0;
  smallerMat.shininess = 300;
  smallerMat.reflective = 0.9f;
  smallerMat.transparency = 0.9f;
  smallerMat.specular = 0;
  smallerMat.refractiveIndex = 1.034f;

  std::shared_ptr<Shape> smaller (new Sphere(smallerMat));


  Light l = Light(std::array<float, 3>{2, 10, -5}, std::array<float, 3>{1, 1, 1});
  
  World w = World({floor, bigger}, l);
  
  Camera camera = Camera(500, 500, 0.45f);
  camera.setTransform(Matrix::viewTransform(point(0,0,-5), point(0,0,0), vector(0,1,0)));
  
  return render(camera, w);


}

