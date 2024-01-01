#pragma once
#include "../Typedefs.h"
#include "../RayTracingStructs.h"

class MaterialBase
{
public:
    MaterialBase() {};

    //Color ka;                            // ambient
    Color kd = Color(1.0,1.0,1.0);       // diffuse
    Color ks = Color(1.0,1.0,1.0);       // specular
    //float shiness;
    //Color ke;       // emission

    float refractive_index = 1.0f;
    bool isTransparent = false;
    bool isReflective = false;
};

