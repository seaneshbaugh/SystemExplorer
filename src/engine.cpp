#include "engine.hpp"

Engine::Engine() {
    this->camera = new Camera();
}

Engine::~Engine() {
    if (this->camera) {
        delete this->camera;
    }
}

void Engine::Start() {

}
