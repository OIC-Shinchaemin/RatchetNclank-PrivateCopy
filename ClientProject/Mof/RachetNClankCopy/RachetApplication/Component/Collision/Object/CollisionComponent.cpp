#include "CollisionComponent.h"

#include "My/Core/Utility.h"


void my::CollisionComponent::AddCollisionFunc(const std::string& target, const CollisionFunc& obj, std::unordered_map<std::string, FuncArray>& out) {
    if (auto it = out.find(target); it == out.end()) {
        out.emplace(target, FuncArray());
    } // if
    out.at(target).push_back(obj);
}

bool my::CollisionComponent::ExecuteFunction(const std::string& key, const my::CollisionInfo& info, const std::unordered_map<std::string, FuncArray>& in) {
    auto it = in.find(key);
    if (it != in.end()) {
        for (const auto& func : it->second) {
            func.Execute(info);
        } // for
        return true;
    } // if
    return false;
}

my::CollisionComponent::CollisionComponent(int priority) :
    super(priority),
    _collisioned(),
    _on_enter(),
    _on_stay(),
    _on_exit() {
}

my::CollisionComponent::~CollisionComponent() {
}

void my::CollisionComponent::AddCollisionedObject(const std::shared_ptr<my::CollisionComponent>& ptr) {
    _collisioned.push_back(ptr);
}

void my::CollisionComponent::RemoveCollisionedObject(const std::shared_ptr<my::CollisionComponent>& ptr) {
    ut::EraseRemove(_collisioned, [ptr](const std::weak_ptr<my::CollisionComponent>& weak) {
        return weak.expired() || weak.lock() == ptr;
    });
}

bool my::CollisionComponent::ExistCollisionedObject(const std::shared_ptr<my::CollisionComponent>& ptr) {
    auto it = std::find_if(_collisioned.begin(), _collisioned.end(), [ptr](const std::weak_ptr<my::CollisionComponent>& weak) {
        return !weak.expired() && weak.lock() == ptr;
    });
    if (it != _collisioned.end()) {
        return true;
    } // if
    return false;
}

void my::CollisionComponent::AddCollisionFunc(CollisionFuncType type, const std::string& target, const CollisionFunc& obj) {
    switch (type) {
        case my::CollisionComponent::CollisionFuncType::Enter:
            this->AddCollisionFunc(target, obj, _on_enter);
            break;
        case my::CollisionComponent::CollisionFuncType::Stay:
            this->AddCollisionFunc(target, obj, _on_stay);
            break;
        case my::CollisionComponent::CollisionFuncType::Exit:
            this->AddCollisionFunc(target, obj, _on_exit);
            break;
        default:
            break;
    } // switch
}

bool my::CollisionComponent::ExecuteEnterFunction(const std::string& key, const my::CollisionInfo& info) {
    return this->ExecuteFunction(key, info, _on_enter);
}

bool my::CollisionComponent::ExecuteStayFunction(const std::string& key, const my::CollisionInfo& info) {
    return this->ExecuteFunction(key, info, _on_stay);
}

bool my::CollisionComponent::ExecuteExitFunction(const std::string& key, const my::CollisionInfo& info) {
    return this->ExecuteFunction(key, info, _on_exit);
}

void my::CollisionComponent::CollisionStage(Mof::LPMeshContainer mesh) {
}