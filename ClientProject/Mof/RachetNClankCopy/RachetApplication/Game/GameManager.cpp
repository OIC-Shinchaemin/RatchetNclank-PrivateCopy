#include "GameManager.h"

#include "My/Core/Trait.h"
#include "My/Core/Utility.h"


void my::GameManager::AddElement(const std::shared_ptr<my::Character>& ptr) {
    if (ty::has_func_render<std::shared_ptr<my::Character>>()) {
        _renderer.AddElement(ptr);
    } // if
}

void my::GameManager::RemoveElement(const std::shared_ptr<my::Character>& ptr) {
    if (ty::has_func_render<std::shared_ptr<my::Character>>()) {
        _renderer.RemoveElement(ptr);
    } // if
}

my::GameManager::GameManager() :
    _character(){
}

my::GameManager::~GameManager() {
}

bool my::GameManager::Initialize(void) {
    _character = std::make_shared<my::Character>();
    _character->Initialize();

    return true;
}

bool my::GameManager::Input(void) {
    return true;
}

bool my::GameManager::Update(float delta_time) {
    return true;
}

bool my::GameManager::Render(void) {
    return true;
}

bool my::GameManager::Release(void) {
    _character->Release();
    return true;
}