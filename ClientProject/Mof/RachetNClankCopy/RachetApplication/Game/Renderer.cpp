#include "Renderer.h"

#include "My/Core/Utility.h"
#include "../Component/MeshComponent.h"


my::Renderer::Renderer() :
    _actors() {
}

my::Renderer::~Renderer() {
}

void my::Renderer::AddElement(const std::shared_ptr<my::Actor>& ptr) {
    _actors.push_back(ptr);
}

void my::Renderer::RemoveElement(const std::shared_ptr<my::Actor>& ptr) {
    ut::SwapPopback(_actors, ptr);
}

bool my::Renderer::Render(void) {
    for (auto ptr : _actors) {
        ptr->Render();
        ptr->RenderDebug();
    } // for
    return true;
}