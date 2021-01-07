//your code here
#include "RayTracer.hpp"
#include "lodepng.h"
#include <cmath>
#include "Sphere.hpp"


// Possible improvements: could have called the parameterized constructor in the default contructor 

RayTracer::RayTracer()
{
    // Initialization of all the Vector Objects fir calculation 
    Vector intersection, normal, l, ln;
    Vector infinity(INFINITY, INFINITY, INFINITY);
    double I;
    Vector light(0, 10.0, 0);
    Vector camera(5.0, 0.0, 0.0);
    Vector target(0.0, 0.0, 0.0);
    Sphere shape;
    //Calling the Genview function to create the rays to detect the object 
    genView(camera, target);
    
    
    std::vector<unsigned char> color = shape.color();
    
    // For loop iterating through all the pixels in the image 
    for (long i = 0; i < WIDTH * HEIGHT; i++) {
        
        // Finding the intersection point 
        intersection = shape.intersect(camera, view[i]);
        //Calculation only happens only if intersection is detected by calling the intersect function in 
        // the sphere class
        if (!intersection.equal(infinity)) {
            //Calculating the normal at the point of intersection ny calling the normal function in the
            // Sphere class
            normal = shape.normal(intersection);
            //finding L
            l = light.sub(intersection);
            //normalizing l
            ln.setI(l.getI() / l.norm());
            ln.setJ(l.getJ() / l.norm());
            ln.setK(l.getK() / l.norm());
            if (ln.dot(normal) < 0.0) {
                I = 0.0;
            }
            else {
                // setting I to L
                I = ln.dot(normal);
            }
            // calculation and assigning the pixel colors 
            pixels[4*i] = (color[0] * (shape.ambient() + ((1.0 - shape.ambient()) * I)));
            pixels[4*i + 1] = (color[1] * (shape.ambient() + ((1.0 - shape.ambient()) * I)));
            pixels[4*i + 2] = (color[2] * (shape.ambient() + ((1.0 - shape.ambient()) * I)));
            pixels[4 * i + 3] = 255;// (color[3] * (shape.ambient() + ((1.0 - shape.ambient()) * I)));
            
        }
        else {
            //Setting the pixel colors to white 
            pixels[4*i] = 255;
            pixels[4*i + 1] = 255;
            pixels[4*i + 2] = 255;
            pixels[4*i + 3] = 255;
        }

    } 
    
    // Condition to check if the camera is in the right position
    if (camera.getI() == 0 && camera.getJ() != 0 && camera.getK() == 0) {
        FIN = false; // Setting FIN to false if the camera is on the y axis i.e (0,y,0)
    }
    else {
        FIN = true;
    }
}

RayTracer::RayTracer(Vector light, Vector camera, Vector target, const Shape3D& shape)
{
    //intialization of variables
    Vector intersection, normal, l, ln;
    Vector infinity(INFINITY, INFINITY, INFINITY);
    double I;

    // Calling genView to create the rays for object detection
    genView(camera, target);

    std::vector<unsigned char> color = shape.color();
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        //pixels[i] = 255;
        intersection = shape.intersect(camera, view[i]);
       // intersection.output(std::cout);
        if (!intersection.equal(infinity)) {
            normal = shape.normal(intersection);
            l = light.sub(intersection);
            ln.setI(l.getI() / l.norm());
            ln.setJ(l.getJ() / l.norm());
            ln.setK(l.getK() / l.norm());
            if (ln.dot(normal) < 0) {
                I = 0.0;
            }
            else {
                I = ln.dot(normal);
            }
            pixels[4*i] = (color[0] * (shape.ambient() + ((1.0 - shape.ambient()) * I)));
            pixels[4*i + 1] = (color[1] * (shape.ambient() + ((1.0 - shape.ambient()) * I)));
            pixels[4*i + 2] = (color[2] * (shape.ambient() + ((1.0 - shape.ambient()) * I)));
            pixels[4 * i + 3] = 255;//(color[3] * (shape.ambient() + ((1.0 - shape.ambient()) * I)));
            

        }
        else {

            // Assigning the pixels to white color
            pixels[4*i] = 255;
            pixels[4*i + 1] = 255;
            pixels[4*i + 2] = 255;
            pixels[4*i + 3] = 255;
        }

    }

    //Setting FIN to false if the camera is not in the right position
    if (camera.getI() == 0 && camera.getJ() != 0 && camera.getK() == 0) {
        FIN = false; // Setting FIN equal to false if the camera is on the y axis i.e. (0,y,0)
    }
    else {
        FIN = true;
    }

}

bool RayTracer::getScene(std::string filename)
{
  bool flag = false;
  unsigned error;
    
  //write png

  if(filename.empty())
    error = lodepng::encode("scene.png", pixels, WIDTH, HEIGHT);
  else
    error = lodepng::encode(filename, pixels, WIDTH, HEIGHT);
  if(error == 0 && FIN) // flag is set to true only if FIN is true i.e. camera is in an acceptable position and the scene can be rendered
    flag = true;

  return flag;
}

bool RayTracer::getScene()
{
  bool flag = false;
  unsigned error = lodepng::encode("scene.png", pixels, WIDTH, HEIGHT);
  
  if(error == 0 && FIN) // flag is set to true only if FIN is true i.e. camera is in an acceptable position and the scene can be rendered
    flag = true;

  return flag;
}

std::vector<Vector>& RayTracer::getView()
{
  return view;
}


std::vector<unsigned char>& RayTracer::getPixels()
{
  return pixels;
}

void RayTracer::genView(const Vector& camera, const Vector& target)
{
    Vector w(0, 1, 0);
    Vector viewport, t, b, bn, tn, vn, qx, qy, p11, intsub1, intadd1, bn1, vn1, qx1, qy1, pij;
    double qx_coff, qy_coff;
    double gx, gy;
    gx = HX / 2;
    gy = HY / 2; 
    // The Target vector subtracted from the camera vector gives us t in the formula 
    t = target.sub(camera);
    //t.output(std::cout);
    // Calculating b by finiding the cross product 
    b = t.cross(w);
   
    
    // Calculating the normalized vector of t and b 
    bn.setI(b.getI() / b.norm());
    bn.setJ(b.getJ() / b.norm()); 
    bn.setK(b.getK() / b.norm());
    //bn.output(std::cout);

    tn.setI(t.getI() / t.norm());
    tn.setJ(t.getJ() / t.norm());
    tn.setK(t.getK() / t.norm());
    //tn.output(std::cout);
    // calculating vn
    vn = tn.cross(bn);
    //vn.output(std::cout);
    qx_coff = (2*gx / (WIDTH - 1.0)); 
    qy_coff = (2*gy / (HEIGHT - 1.0)); 
    // calculating qx and qy
    qx.setI(qx_coff * bn.getI());
    qx.setJ(qx_coff * bn.getJ());
    qx.setK(qx_coff * bn.getK());
    //qx.output(std::cout);

    qy.setI(qy_coff * vn.getI());
    qy.setJ(qy_coff * vn.getJ());
    qy.setK(qy_coff * vn.getK());
    //qy.output(std::cout);
    // gx multiplied by vector bn 
    bn1.setI(gx * bn.getI());
    bn1.setJ(gx * bn.getJ());
    bn1.setK(gx * bn.getK());
    //bn1.output(std::cout);
    // gy multiplied by vector vn
    vn1.setI(gy * vn.getI());
    vn1.setJ(gy * vn.getJ());
    vn1.setK(gy * vn.getK());
    //vn1.output(std::cout);
    // intsub holds the valus of p11
    intsub1 = bn1.add(vn1); // bn*gx + vn*gy
    //intsub1.output(std::cout);
    p11 = tn.sub(intsub1); // tn*d - bn*gx -vn*gy
    //p11.output(std::cout);
    //p11.output(std::cout);
    int k = 0;
    for (double j = 1; j <= WIDTH; j++) {
        for (double i = 1; i <= HEIGHT; i++) {

            // Calculating qx(i-1) and storing it in qx1
            qx1.setI((i - 1) * qx.getI());
            qx1.setJ((i - 1) * qx.getJ());
            qx1.setK((i - 1) * qx.getK());

            //Calculatin qy(j-1) and toring it in qy1
            qy1.setI((j - 1) * qy.getI());
            qy1.setJ((j - 1) * qy.getJ());
            qy1.setK((j - 1) * qy.getK());
            //qx1.output(std::cout);
           // qy1.output(std::cout);
            // calculating qx1+qy1 and storing in pij
            intadd1 = qx1.add(qy1); // (i-1)*qx + (j-1)*qy
            pij = p11.add(intadd1);
            //pij.output(std::cout);
            //calculating the unit vector for viewport 
            viewport.setI(pij.getI() / pij.norm());
            viewport.setJ(pij.getJ() / pij.norm());
            viewport.setK(pij.getK() / pij.norm());

           // pij.output(std::cout);
            //view.push_back(viewport);
            view[k] = viewport;
            k++;
        }
        
    }
}


