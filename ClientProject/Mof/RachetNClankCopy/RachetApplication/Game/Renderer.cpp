#include "Renderer.h"

#include "Base/Core/Utility.h"
#include "../Component/MeshComponent.h"


ratchet::Renderer::Renderer() :
    _actors() {
    _actors.reserve(64);
    _enable_actors.reserve(64);
}

ratchet::Renderer::~Renderer() {
}

void ratchet::Renderer::AddElement(const std::shared_ptr<ratchet::Actor>& ptr) {
    _actors.push_back(ptr);
    _enable_actors.push_back(ptr);
}

void ratchet::Renderer::RemoveElement(const std::shared_ptr<ratchet::Actor>& ptr) {
    ut::SwapPopback(_actors, ptr);
    ut::SwapPopback(_enable_actors, ptr);
    ut::SwapPopback(_disable_actors, ptr);
}

bool ratchet::Renderer::Render(void) {
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

void ratchet::Renderer::Reset(void) {
    _actors.clear();
    _enable_actors.clear();
    _disable_actors.clear();
}