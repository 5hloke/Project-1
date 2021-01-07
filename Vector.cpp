#include "Vector.hpp"
#include <cmath>

void Vector::output( std::ostream &out ) const
{
	out << vx << "i + " << vy << "j + " << vz << "k" << std::endl;
}

// The default constructor initialises all the variables to zero 
// vx = 0, vy = 0, vz = 0
// The default constructor takes no parameters and returns nothing 
Vector::Vector() {
	vx = 0;
	vy = 0;
	vz = 0;
}

// The parameterized constructor sets the vector variables to the passed vallues 
// by the user
// The function takes inthe parameters vx, vy, vz
Vector::Vector(double vx, double vy, double vz) {
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
}

// The funciton return the x value of the 3D vector 
// The function takes in no parameters and returns a double value 
double Vector::getI() const {

	return vx;
}

// The funciton return the y value of the 3D vector 
// The function takes in no parameters and returns a double value 
double Vector::getJ() const {

	return vy;
}

// The funciton return the z value of the 3D vector 
// The function takes in no parameters and returns a double value 
double Vector::getK() const {

	return vz;
}

// The function sets the value of the x parameter of the 3D vector to the given value newVx
// The function takes tha parameter <double> newVx and returns nothing
void Vector::setI(double newVx) {

	vx = newVx;
}

// The function sets the value of the y parameter of the 3D vector to the given value newVy
// The function takes tha parameter <double> newVy and returns nothing
void Vector::setJ(double newVy) {

	vy = newVy;
}

// The function sets the value of the z parameter of the 3D vector to the given value newVz
// The function takes tha parameter <double> newVz and returns nothing
void Vector::setK(double newVz) {

	vz = newVz;
}

// The function checks if two vectors are equal to each other. 
// The function takes a const <Vector> rhs as a parameter and return a boolean 
bool Vector::equal(const Vector& rhs) const {

	bool value;
	if (vx == rhs.vx && vy == rhs.vy && vz == rhs.vz) {
		value = true;
	}
	else {
		value = false;
	}
	return value;
}

// The function adds two vectors.
// The function takes in a const <Vector> rhs as a parameter and return the addition of 
// the two vectors as a <Vector>.
Vector Vector::add(const Vector& rhs) const {

	return Vector(vx + rhs.vx, vy + rhs.vy, vz + rhs.vz);
}

// The function subtracts two vectors.
// The function takes in a const <Vector> rhs as a parameter and return the difference of 
// the two vectors as a <Vector>.
Vector Vector::sub(const Vector& rhs) const {

	return Vector(vx - rhs.vx, vy - rhs.vy, vz - rhs.vz);
}

// The function computes the cross product of the two  vectors.
// The function takes in a const <Vector> rhs as a parameter and returns the cross product of 
// the two vectors as a <Vector>.
Vector Vector::cross(const Vector& rhs) const {

	Vector cross_product;
	cross_product.vx = (vy * rhs.vz - rhs.vy * vz);
	cross_product.vy = -(vx * rhs.vz - rhs.vx * vz);
	cross_product.vz = (vx * rhs.vy - rhs.vx * vy);

	return cross_product;
}

// The function computes the dot product of the two  vectors.
// The function takes in a const <Vector> rhs as a parameter and returns the dot product of 
// the two vectors as a <double>.
double Vector::dot(const Vector& rhs) const {

	double dot_product;
	dot_product = (vx * rhs.vx) + (vy * rhs.vy) + (vz * rhs.vz);

	return dot_product;
}

// The function computes the norm of the vector.
// The function takes no parameters and returns the value of the nom of a vector 
// as a <double> 
double Vector::norm() const {

	double square = (vx * vx + vy * vy + vz * vz);
	double norm = sqrt(square);
	if (square < 0) {
		return -1;
	}

	return norm;
}

// The function computes the angle between two vectors.
// The funciton takes in the parameter const <Vector> rhs and returns the value of the angle 
// in radians as a <double> between 0 to 2pi.
double Vector::angle(const Vector& rhs) const {

	double square_rt = sqrt(vx * vx + vy * vy + vz * vz) * sqrt(rhs.vx * rhs.vx + rhs.vy * rhs.vy + rhs.vz * rhs.vz);
	double angle = acos(((vx * rhs.vx) + (vy * rhs.vy) + (vz * rhs.vz)) / (square_rt));
	
	if (square_rt == 0) {
		return -1; 
	}

	return angle; 
}