#include "engine.hpp"

Engine::Engine() {
    this->camera = new Camera();
}

Engine::~Engine() {
    delete this->camera;
}

void Engine::Start() {

}
