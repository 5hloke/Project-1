
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include <cmath>
#include <iostream>

#include "catch.hpp"
#include "RayTracer.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

// Conclusive testing of the genView, the RayTracers constructors, intesection(Sphere), normal(Sphere)
// is being done by the two test cases that have already been written for us 
// Which is why I am not writing test cases for the intersection adn the normal function in the Sphere
// class.

// This is just a simple example for demonstration
TEST_CASE( "Test default constructor", "[RayTracer]" ) {
  RayTracer r;
  r.getScene("scene_default.png");
}

// These two tests do a comprehensive test of the entire program
// they test the genview, intersect, normal methods from the raytracer and the sphere class

TEST_CASE( "Test parameterized constructor", "[RayTracer]" ) {
  Vector light(0,10,0), camera(5,0,0), target(0,0,0);

  //a large magenta sphere with lots of internal light
  std::vector<unsigned char> col = {255,0,255,255};
  Sphere sph(2, Vector(0,0,0), col, 0.5);
  
  RayTracer r(light, camera, target, sph);
  r.getScene("scene_parameterized.png");
}

// Testing if the default contructor in the sphere class generates the required sphere
// the test case also tests the getters of the sphere class that is the radius, ambient, color, and the postion method.
TEST_CASE("Test for the Default Sphere Constructor", "[Sphere]") 
{
	Sphere shape;
	Vector position;
	std::vector<unsigned char> col = shape.color();
	REQUIRE(shape.radius() == 1);
	REQUIRE(shape.ambient() == 0.2);
	REQUIRE(position.equal(shape.position()));
	REQUIRE(col[0] == 255);
	REQUIRE(col[1] == 0);
	REQUIRE(col[2] == 0);
	REQUIRE(col[3] == 255);
}

// Testing the parameterized shpere constructor
TEST_CASE("Test for the parameterized Sphere constructor", "[Sphere]")
{
	// creating random variables to pass in to the sphere parameterized constructor
	srand(time(NULL));
	double rad = rand() % 100 / 10;
	double pos1, pos2, pos3, amb; 
	pos1 = rand() % 100 / 10;
	pos2 = rand() % 100 / 10;
	pos3 = rand() % 100 / 10;
	Vector pos(pos1, pos2, pos3);
	amb = rand() % 100 / 10;;
	std::vector<unsigned char> color = std::vector<unsigned char>(4);
	color[0] = 255;
	color[1] = 100;
	color[2] = 50;
	color[3] = 255;

	// creating the sphere object using the parameterized constructor
	Sphere shape(rad, pos, color, amb);
	REQUIRE(shape.radius() == rad);
	REQUIRE(shape.ambient() == amb);
	REQUIRE(pos.equal(shape.position()));

}

// Testing if the scene renders if the camera is in an invalid position
TEST_CASE("Checking for the invalid camera position", "[RayTracer]") 
{
	Vector light(0, 10, 0), camera(0, 5, 0), target(0, 0, 0);

	//a large magenta sphere with lots of internal light
	std::vector<unsigned char> col = { 255,0,255,255 };
	Sphere sph(2, Vector(0, 0, 0), col, 0.5);

	RayTracer r(light, camera, target, sph);
	bool flag = r.getScene("scene_parameterized2.png");
	REQUIRE(!flag);
}

