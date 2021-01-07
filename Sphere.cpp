//your code here
#include "Sphere.hpp"
#include "RayTracer.hpp"
#include <cmath>
// Default constructor to create a red sphere at the position 0,0,0
// and witha an ab=mbience of 0.2 and radius 1

Sphere::Sphere() {
	rad = 1.0;
	amb = 0.2;
	pos.setI(0.0);
	pos.setJ(0.0);
	pos.setK(0.0);

	col[0] = 255; // r
	col[1] = 0; // g
	col[2] = 0; // b
	col[3] = 255; // a
}

// Parameterized constructor to create a sphere with user supplied information 

Sphere::Sphere(double rad, Vector pos, std::vector<unsigned char> col, double amb)
{
	// Setting the variables to the given argument values
	this->rad = rad;
	this->pos.setI(pos.getI());
	this->pos.setJ(pos.getJ());
	this->pos.setK(pos.getK());
	this->amb = amb;
	this->col[0] = col[0];
	this->col[1] = col[1];
	this->col[2] = col[2];
	this->col[3] = col[3];
}

// function to return the color of the sphere 
std::vector<unsigned char> Sphere::color() const
{
	return col; 
}

// function to return the position of the sphere. 
Vector Sphere::position() const
{
	return pos;
}

// function to return the ambient of the sphere.
double Sphere::ambient() const
{
	return amb;
}

// the function to find the intersection of the sphere and the ray 
// the function returns a vector. 
Vector Sphere::intersect(const Vector& s, const Vector& d) const
{
	Vector v_diff, intersection, y1, y2, y, diff1, diff2;
	double t, t1, t2;
	// v_diff is the difference vector betweeen the position of the sphere and the observer
	v_diff = s.sub(pos);
	
	//The codition for intersection 
	if ((v_diff.dot(d) * v_diff.dot(d)) - ((v_diff.norm()*v_diff.norm()) - (rad * rad)) > 0.0) {
		// calculating the value of t to find the intersection point 
		t1 = -(v_diff.dot(d)) + sqrt(pow(v_diff.dot(d), 2) - (pow(v_diff.norm(), 2) - pow(rad, 2)));
		t2 = -(v_diff.dot(d)) - sqrt(pow(v_diff.dot(d), 2) - (pow(v_diff.norm(), 2) - pow(rad, 2)));
		//finding the first intersection point using t1
		y1.setI(s.getI() + (t1 * (d.getI())));
		y1.setJ(s.getJ() + (t1 * (d.getJ())));
		y1.setK(s.getK() + (t1 * (d.getK())));

		//finding the second intersection point using t2
		y2.setI(s.getI() + (t2 * (d.getI())));
		y2.setJ(s.getJ() + (t2 * (d.getJ())));
		y2.setK(s.getK() + (t2 * (d.getK())));

		// calculating the difference between the possibke intersection point and the observer
		// to check which one is closer 
		diff1 = s.sub(y1);
		diff2 = s.sub(y2);
		//checking for the closest intersection point 
		if (diff1.norm() > diff2.norm()) {
			y = y2;
		}
		else {
			y = y1;
		}
	}
	else {
		// if intersection does not exist then intersection point is (inf, inf, inf)
		y.setI(INFINITY);
		y.setJ(INFINITY);
		y.setK(INFINITY);
	}

	// returns the intersection point
	return y;
}

// Teh function returns the unit normal vector on the suface of the sphere at the intersection point
Vector Sphere::normal(const Vector& position) const
{
	Vector normal, unit_normal;
	// Calculates the difference between the intersection point on the sphere and the center of the sphere
	normal = position.sub(this->pos);

	// Normalizing the normal vector calculate above
	unit_normal.setI(normal.getI() / normal.norm());
	unit_normal.setJ(normal.getJ() / normal.norm());
	unit_normal.setK(normal.getK() / normal.norm());

	// returning the unit_normal
	return unit_normal; 
}


// returns the radius of the sphere. 
double Sphere::radius() const
{
	return rad;
}