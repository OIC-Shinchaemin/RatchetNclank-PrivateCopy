#include "Renderer.h"

#include "Base/Core/Utility.h"

#include "../Game/Graphics/RenderCommandTask.h"


ratchet::game::Renderer::Renderer() :
    _actors() {
    _actors.reserve(64);
    _enable_actors.reserve(64);
}

ratchet::game::Renderer::~Renderer() {
}

void ratchet::game::Renderer::AddElement(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    _actors.push_back(ptr);
    _enable_actors.push_back(ptr);
}

void ratchet::game::Renderer::RemoveElement(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    ut::SwapPopback(_actors, ptr);
    ut::SwapPopback(_enable_actors, ptr);
    ut::SwapPopback(_disable_actors, ptr);
}

bool ratchet::game::Renderer::Render(void) {
    auto command_queue = std::make_shared<game::graphics::RenderCommandTask>();
    for (auto ptr : _enable_actors) {
        // •`‰æ‚µ‚È‚¢”»’è
        if (!ptr->Render(command_queue)) {
            _disable_actors.push_back((ptr));
        } // if
    } // for
    command_queue->Execute();

    for (auto ptr : _disable_actors) {
        ut::SwapPopback(_enable_actors, ptr);
        if (ptr->InCameraRange()) {
            _enable_actors.push_back(ptr);
        } // if
    } // for
    return true;
}

void ratchet::game::Renderer::Reset(void) {
    _actors.clear();
    _enable_actors.clear();
    _disable_actors.clear();
}