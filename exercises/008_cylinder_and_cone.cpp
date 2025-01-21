
#include "008_cylinder_and_cone.h"
#include "Camera.h"
#include "Canvas.h"
#include "Checker.h"
#include "Color.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Pattern.h"
#include "Plane.h"
#include "Ring.h"
#include "Shape.h"
#include "Sphere.h"
#include "Light.h"
#include "Stripes.h"
#include "World.h"
#include <array>
#include <memory>
#include <cmath>
#include <vector>
#include "Constants.h"


Canvas Ex008(){
  
  Color white = Color(1,1,1);
  Color faluRed = Color(0.47f, 0.125f, 0.0889f);
  Color bbPowder = Color(0.98f, 0.992f, 0.965f);
  Color moonStone = Color(0.2745f, 0.6745f, 0.76f);

  auto ringPattern = std::shared_ptr<Pattern> (new Ring(faluRed, bbPowder));
  ringPattern->setTransforms({
    Matrix::scale(0.25, 0.25, 0.25),
    Matrix::rotationAlongX(M_PI_2),
  });

  auto stripesPattern = std::shared_ptr<Pattern> (new Stripes(moonStone, bbPowder));
  stripesPattern->setTransform({
    Matrix::scale(0.2f, 0.2f, 0.2f)
  });

  auto checkerPattern = std::shared_ptr<Pattern>(new Checker(faluRed, moonStone));

  Material floorMat = Material(bbPowder, stripesPattern);
  std::shared_ptr<Shape> floor (new Plane(floorMat));
 
  Material middMat = Material(Color(0.1f, 1, 0.5f));
  middMat.diffuse = 0.7f;
  middMat.specular = 0.3f;
  middMat.pattern = ringPattern;
  std::shared_ptr<Shape> middleSphere (new Cylinder(middMat, 1 ,2, true));
  //middleSphere->setTransform(Matrix::rotationAlongX(M_PI_2));
  middleSphere->setTransform(Matrix::translate(0, -.95f, 0));

  Material rightMat = Material(Color(0.5f, 2, 0.1f), checkerPattern);
  rightMat.diffuse = 0.7f;
  rightMat.specular = 0.3f;
  std::shared_ptr<Shape> rightSphere (new Cone(rightMat, 1, 2));
  rightSphere->setTransform(Matrix::scale(0.5f, 0.5f, 0.5f));
  rightSphere->setTransform(Matrix::translate(1.5f, 0.5f, -0.5f));

  Material leftMat = Material(Color(1, 0.8f, 0.1f));
  leftMat.diffuse = 0.7f;
  leftMat.specular = 0.3f;
  std::shared_ptr<Shape> leftSphere (new Sphere(leftMat));
  leftSphere->setTransform(Matrix::scale(0.33f, 0.33f, 0.33f));
  leftSphere->setTransform(Matrix::translate(-1.5f, 0.33f, -0.75f));


  Light l = Light(std::array<float, 3>{-10, 10, -10}, std::array<float, 3>{1, 1, 1});
  
  //World w = World({floor, middleSphere, rightSphere, leftSphere}, l);

  World w = World({floor, middleSphere, rightSphere, leftSphere}, l);
  
  Camera camera = Camera(1000, 500, M_PI/1.5);
  camera.setTransform(Matrix::viewTransform(point(0,1.5,-5), point(0,1,0), vector(0,1,0)));
  
  return render(camera, w);


}
