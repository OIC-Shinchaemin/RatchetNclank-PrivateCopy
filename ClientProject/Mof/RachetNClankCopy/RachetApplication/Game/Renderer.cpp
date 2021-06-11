#include "Renderer.h"

#include "Base/Core/Utility.h"
#include "../Component/MeshComponent.h"


my::Renderer::Renderer() :
    _actors() {
    _actors.reserve(64);
    _enable_actors.reserve(64);
}

my::Renderer::~Renderer() {
}

void my::Renderer::AddElement(const std::shared_ptr<my::Actor>& ptr) {
    _actors.push_back(ptr);
    _enable_actors.push_back(ptr);
}

void my::Renderer::RemoveElement(const std::shared_ptr<my::Actor>& ptr) {
    ut::SwapPopback(_actors, ptr);
    ut::SwapPopback(_enable_actors, ptr);
    ut::SwapPopback(_disable_actors, ptr);
}

bool my::Renderer::Render(void) {
    for (auto ptr : _enable_actors) {
        // •`‰æ‚µ‚È‚¢”»’è
        if (!ptr->Render()) {
            _disable_actors.push_back((ptr));
        } // if
    } // for

    for (auto ptr : _disable_actors) {
        ut::SwapPopback(_enable_actors, ptr);
        if (ptr->InCameraRange()) {
            _enable_actors.push_back(ptr);
        } // if
    } // for
    return true;
}

void my::Renderer::Reset(void) {
    _actors.clear();
    _enable_actors.clear();
    _disable_actors.clear();
}