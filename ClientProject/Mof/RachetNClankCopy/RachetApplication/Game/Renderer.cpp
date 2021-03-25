#include "Renderer.h"

#include "My/Core/Utility.h"


my::Renderer::Renderer() :
    _characters(){
}

my::Renderer::~Renderer() {
}

void my::Renderer::AddElement(const std::shared_ptr<my::Character>& ptr) {
    _characters.push_back(ptr);
}

void my::Renderer::RemoveElement(const std::shared_ptr<my::Character>& ptr) {
    ut::EraseRemove(_characters, ptr);
}

bool my::Renderer::Render(void) {
    for (auto ptr : _characters) {
        
    } // for
    return true;
}
