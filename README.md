# raytracer-windows

Raytracing learning project.

## Raytracing methods
Phong shading + trace reflection ray (old implementation)            | (Whitted) Phong shading (only diffuse term) + trace relection ray + trace refraction ray (current implementation)
:-------------------------:|:-------------------------:
![](./raytracer-windows/demo/test_phong.png)  |  ![](./raytracer-windows/demo/test_whitted.png)

## Anti-aliasing

No anti-aliasing (rending time ~7sec)          |  Anti-aliasing with 5 samples/pixel (rendering time ~36sec)
:-------------------------:|:-------------------------:
![](./raytracer-windows/demo/test_no_anti_7sec.png)  |  ![](./raytracer-windows/demo/test_anti5_36sec.png)


