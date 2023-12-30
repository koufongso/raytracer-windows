#include <iostream>
#include "Scene.h"
#include "Camera.h"
#include "Typedefs.h"
#include "../include/Primitives/Primitives.h"
#include "../include/Lights/Lights.h"


int main()
{
    Scene scene1;

    // set up objects
    Sphere* sphere1 = new Sphere(Point(0,0,0),1);
    sphere1->moveTo(Point(0, 2, 0));
    BRDF brdf;
    brdf.ka = Color(0.2, 0.2, 0.2);    
    brdf.kd = Color(0.8, 0.0, 0.0);
    brdf.ks = Color(1, 1, 1);
    brdf.kr = Color(1, 1, 1);
    sphere1->setBRDF(brdf);
    sphere1->setShiness(50.0);
    scene1.objects.push_back(sphere1);

    Sphere* sphere2 = new Sphere(Point(0, 0, 0), 1);
    sphere2->moveTo(Point(0, -2, 0));
    brdf.ka = Color(0.2, 0.2, 0.2);
    brdf.kd = Color(0.0, 0.0, 0.8);
    brdf.ks = Color(1, 1, 1);
    brdf.kr = Color(1, 1, 1);
    sphere2->setBRDF(brdf);
    sphere2->setShiness(50.0);
    scene1.objects.push_back(sphere2);

    Sphere* sphere3 = new Sphere(Point(0, 0, 0), 1);
    sphere3->moveTo(Point(-2, 0, 0));
    brdf.ka = Color(0.2, 0.2, 0.2);
    brdf.kd = Color(0.0, 0.8, 0.0);
    brdf.ks = Color(1, 1, 1);
    brdf.kr = Color(1, 1, 1);
    sphere3->setBRDF(brdf);
    sphere3->setShiness(50.0);
    scene1.objects.push_back(sphere3);

    Plane* plane1 = new Plane(Vertex(10,-20,0),Vertex(10,20,0),Vertex(-10,20,0));
    plane1->moveTo(Point(0, 0, -1));
    brdf.ka = Color(0.2, 0.2, 0.2);
    brdf.kd = Color(1.0, 1.0, 1.0);
    brdf.ks = Color(0.2, 0.2, 0.2);
    brdf.kr = Color(0, 0, 0);
    plane1->setBRDF(brdf);
    plane1->setShiness(50.0);
    scene1.objects.push_back(plane1);

    // set up lights
    DirectionalLight* dLight = new DirectionalLight(Vector(-1,  1, -1));
    dLight->color.r = 0.5;
    dLight->color.g = 0.5;
    dLight->color.b = 0.5;
    scene1.light_sources.push_back(dLight);

    PointLight* pLight = new PointLight(Point(10, -10, 10));
    pLight->color.r = 1.0f;
    pLight->color.g = 1.0f;
    pLight->color.b = 1.0f;
    //scene1.light_sources.push_back(pLight);

    // setup cameras
    Camera* cam1 = new Camera();
    cam1->setImageSize(800, 800);
    cam1->setFovy(90);
    cam1->moveToGlobal(Point(5.0f, 0.0f, 0.0f));
    cam1->lootAtDirection(Vector(-1, 0, 0));

    // cam1->setCamToWorld(Transformation(0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1));
    scene1.camera_list.push_back(cam1);

    scene1.render();
    
}