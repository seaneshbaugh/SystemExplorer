#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include "camera.hpp"

class Engine
{
public:
    Engine();
    ~Engine();
    void Start();
private:
    Camera* camera;
};

#endif
