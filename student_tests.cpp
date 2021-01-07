#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include <iostream>

#include "catch.hpp"
#include "Vector.hpp"

// This is just a simple example for demonstration
// we will see how to do proper testing in meeting 3
TEST_CASE( "Test default constructor", "[Vector]" )
{
  Vector v;
  REQUIRE(v.getI() == 0);
  REQUIRE(v.getJ() == 0);
  REQUIRE(v.getK() == 0);
}

// Test case to test the parameterized constructor 
TEST_CASE("Test parameterized constructor", "[Vector]") 
{
	// creating random variables to test 
	srand(time(NULL));
	double vx, vy, vz;
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;
	Vector v(vx, vy, vz);
	// testing the function
	REQUIRE(v.getI() == vx);
	REQUIRE(v.getJ() == vy);
	REQUIRE(v.getK() == vz);
}

// Test case to test the get() functions
TEST_CASE("Test get functions", "[Vector]")
{
	Vector v;
	REQUIRE(v.getI() == 0);
	REQUIRE(v.getJ() == 0);
	REQUIRE(v.getK() == 0);

	// creating random variables for testing 
	double vx, vy, vz;
	srand(time(NULL));
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;

	v.setI(vx);
	v.setJ(vy);
	v.setK(vz);

	// testing the function for the random variables
	REQUIRE(v.getI() == vx);
	REQUIRE(v.getJ() == vy);
	REQUIRE(v.getK() == vz);

}

// Test case to test the equal() function 
TEST_CASE("Testing the equal function", "[Vector]")
{
	Vector v1;
	Vector v2;

	REQUIRE(v1.equal(v2));
	REQUIRE(v1.equal(v2));

	// Random variables to test the function
	double vx, vy, vz;
	srand(time(NULL));
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;

	// Using the set funcitons  to set the values of the parameters
	v1.setI(vx);
	v1.setJ(vy);
	v1.setK(vz);

	v2.setI(vx);
	v2.setJ(vy);
	v2.setK(vz);

	// Testin gthe funciton
	REQUIRE(v1.equal(v2));
	REQUIRE(v1.equal(v2));
}

// Test case for the addition funciton 
TEST_CASE("Testing the addition function", "[Vector]")
{
	Vector v1;
	Vector v2;
	Vector v3;

	v3 = v1.add(v2);
	REQUIRE(v3.getI() == 0);
	REQUIRE(v3.getJ() == 0);
	REQUIRE(v3.getK() == 0);

	double vx, vy, vz, vx1, vy1, vz1;
	srand(time(NULL));
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;
	vx1 = rand() % 100 / 10;
	vy1 = rand() % 100 / 10;
	vz1 = rand() % 100 / 10;

	v1.setI(vx);
	v1.setJ(vy);
	v1.setK(vz);

	v2.setI(vx1);
	v2.setJ(vy1);
	v2.setK(vz1);

	v3 = v1.add(v2);

	// Testing the function 
	REQUIRE(v3.getI() == vx + vx1);
	REQUIRE(v3.getJ() == vy + vy1);
	REQUIRE(v3.getK() == vz + vz1);
}

//Test case to test the subtraction function.
TEST_CASE("Testing the subtraction function", "[Vector]")
{
	Vector v1;
	Vector v2;
	Vector v3;

	v3 = v1.sub(v2);
	REQUIRE(v3.getI() == 0);
	REQUIRE(v3.getJ() == 0);
	REQUIRE(v3.getK() == 0);

	double vx, vy, vz, vx1, vy1, vz1;
	srand(time(NULL));
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;
	vx1 = rand() % 100 / 10;
	vy1 = rand() % 100 / 10;
	vz1 = rand() % 100 / 10;

	v1.setI(vx);
	v1.setJ(vy);
	v1.setK(vz);

	v2.setI(vx1);
	v2.setJ(vy1);
	v2.setK(vz1);

	v3 = v1.sub(v2);

	// Testing the funciton
	REQUIRE(v3.getI() == vx - vx1);
	REQUIRE(v3.getJ() == vy - vy1);
	REQUIRE(v3.getK() == vz - vz1);
}

//Test case to test the cross function  
TEST_CASE("Testing the function for Cross-Product", "[Vector]")
{
	Vector v1;
	Vector v2;
	Vector v3;

	v3 = v1.cross(v2);
	REQUIRE(v3.getI() == 0);
	REQUIRE(v3.getJ() == 0);
	REQUIRE(v3.getK() == 0);

	double vx, vy, vz, vx1, vy1, vz1;
	srand(time(NULL));
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;
	vx1 = rand() % 100 / 10;
	vy1 = rand() % 100 / 10;
	vz1 = rand() % 100 / 10;

	v1.setI(vx);
	v1.setJ(vy);
	v1.setK(vz);

	v2.setI(vx1);
	v2.setJ(vy1);
	v2.setK(vz1);

	// Computing the cross product
	v3 = v1.cross(v2);

	// Testing the function 
	REQUIRE(v3.getI() == (vy * vz1 - vy1 * vz));
	REQUIRE(v3.getJ() == -(vx * vz1 - vx1 * vz));
	REQUIRE(v3.getK() == (vx * vy1 - vx1 * vy));
}

// Testing the dot product function
TEST_CASE("Testing teh function for Dot-Product", "[Vector]")
{
	Vector v1;
	Vector v2;
	double dot;

	dot = v1.dot(v2);
	REQUIRE(dot == 0);

	double vx, vy, vz, vx1, vy1, vz1;
	srand(time(NULL));
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;
	vx1 = rand() % 100 / 10;
	vy1 = rand() % 100 / 10;
	vz1 = rand() % 100 / 10;

	v1.setI(vx);
	v1.setJ(vy);
	v1.setK(vz);

	v2.setI(vx1);
	v2.setJ(vy1);
	v2.setK(vz1);

	//Computing the dot product
	dot = v1.dot(v2);

	//Testing the function 
	REQUIRE(dot == (vx * vx1) + (vy * vy1) + (vz * vz1));

}

// Test case for the norm function 
TEST_CASE("Testing the function for calculating norm", "[Vector]")
{
	Vector v;
	REQUIRE(v.norm() == 0);

	double vx, vy, vz;
	srand(time(NULL));
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;

	v.setI(vx);
	v.setJ(vy);
	v.setK(vz);

	double square = (vx * vx + vy * vy + vz * vz);
	double norm;

	//finding the norm 
	norm = v.norm();
	//Testing the function
	REQUIRE(norm == sqrt(square));

}

// Testing the function for angle. 
TEST_CASE("Testing the function for angle", "[Vector]")
{
	Vector v1;
	Vector v2;
	
	REQUIRE(v1.angle(v2) == -1);

	double vx, vy, vz, vx1, vy1, vz1;
	srand(time(NULL));
	vx = rand() % 100 / 10;
	vy = rand() % 100 / 10;
	vz = rand() % 100 / 10;
	vx1 = rand() % 100 / 10;
	vy1 = rand() % 100 / 10;
	vz1 = rand() % 100 / 10;

	v1.setI(vx);
	v1.setJ(vy);
	v1.setK(vz);

	v2.setI(vx1);
	v2.setJ(vy1);
	v2.setK(vz1);

	double angle, angle_check, square_rt;
	square_rt = sqrt(vx * vx + vy * vy + vz * vz) * sqrt(vx1 * vx1 + vy1 * vy1 + vz1 * vz1);

	// Computing the angle without using the function to test 
	angle_check = acos((v1.dot(v2) / square_rt));

	// Computing the angle 
	angle = v1.angle(v2);

	// Testing the function 
	REQUIRE(angle == angle_check);
}