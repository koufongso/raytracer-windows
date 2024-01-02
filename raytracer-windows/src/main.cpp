#include <iostream>
#include "Scene.h"
#include "Camera.h"
#include "Typedefs.h"
#include "../include/Primitives/Primitives.h"
#include "../include/Lights/Lights.h"
#include <chrono>

int main()
{
    Scene scene1;

    // set up objects
    Sphere* sphere1 = new Sphere(Point(0,0,0),1);
    sphere1->moveTo(Point(0, 2, 0));
    sphere1->material.kd = Color(0.02f, 0.0f, 0.0f);
    sphere1->material.isReflective = true;
    sphere1->material.isTransparent = true;
    sphere1->material.refractive_index = 1.5f;
    scene1.objects.push_back(sphere1);

    Sphere* sphere2 = new Sphere(Point(0, 0, 0), 1);
    sphere2->moveTo(Point(0, -2, 0));
    sphere2->material.kd = Color(0.0, 0.0, 1.0);
    sphere2->material.isReflective = true;
    sphere2->material.ks = Color(1, 1, 1);
    scene1.objects.push_back(sphere2);

    Sphere* sphere3 = new Sphere(Point(0, 0, 0), 1);
    sphere3->moveTo(Point(-2, 0, 0));
    sphere3->material.kd = Color(0.0, 1.0, 0.0);
    sphere3->material.isReflective = true;
    sphere3->material.ks = Color(1, 1, 1);
    scene1.objects.push_back(sphere3);

    Plane* plane1 = new Plane(Vertex(10,-20,0),Vertex(10,20,0),Vertex(-10,20,0));
    plane1->moveTo(Point(0, 0, -2));
    plane1->material.kd = Color(1.0, 1.0, 1.0);
    scene1.objects.push_back(plane1);

    // set up lights
    DirectionalLight* dLight = new DirectionalLight(Vector(-1,  1, -1));
    dLight->color.r = 1.0;
    dLight->color.g = 1.0;
    dLight->color.b = 1.0;
    //scene1.light_sources.push_back(dLight);

    PointLight* pLight = new PointLight(Point(10, -10, 10));
    pLight->color.r = 1.0f;
    pLight->color.g = 1.0f;
    pLight->color.b = 1.0f;
    scene1.light_sources.push_back(pLight);

    // setup cameras
    Camera* cam1 = new Camera();
    cam1->setImageSize(800, 800);
    cam1->setFovy(90);
    cam1->moveToGlobal(Point(5.0f, 0.0f, 0.0f));
    cam1->lootAtPoint(Vector(0, 0, 0));

    // cam1->setCamToWorld(Transformation(0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1));
    scene1.camera_list.push_back(cam1);

    scene1.anti_aliasing = true;
    scene1.sample_per_pixel_anti_aliasing = 10;

    auto t0 = std::chrono::high_resolution_clock::now();
    scene1.render();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(t1 - t0);
    printf("Rending Time:%lld sec\n", duration.count());
    return 0;
}