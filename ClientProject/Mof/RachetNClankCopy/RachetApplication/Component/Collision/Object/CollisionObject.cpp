#include "CollisionObject.h"

#include "My/Core/Utility.h"


my::CollisionObject::CollisionObject(int priority) :
    super(priority),
    _collisioned(),
    _on_enter(),
    _on_stay(),
    _on_exit() {
}

my::CollisionObject::~CollisionObject() {
}

void my::CollisionObject::AddCollisionedObject(const std::shared_ptr<my::CollisionObject>& ptr) {
    _collisioned.push_back(ptr);
}

void my::CollisionObject::RemoveCollisionedObject(const std::shared_ptr<my::CollisionObject>& ptr) {
    ut::EraseRemove(_collisioned, [ptr](const std::weak_ptr<my::CollisionObject>& weak) {
        return weak.expired() || weak.lock() == ptr;
    });
}

bool my::CollisionObject::ExistCollisionedObject(const std::shared_ptr<my::CollisionObject>& ptr) {
    auto it = std::find_if(_collisioned.begin(), _collisioned.end(), [ptr](const std::weak_ptr<my::CollisionObject>& weak) {
        return !weak.expired() && weak.lock() == ptr;
    });
    if (it != _collisioned.end()) {
        return true;
    } // if
    return false;
}

void my::CollisionObject::AddCollisionFunc(CollisionFuncType type, const std::string& key, CollisionFunc lambda) {
    switch (type) {
        case my::CollisionObject::CollisionFuncType::Enter:
            _on_enter.emplace(key, lambda);
            break;
        case my::CollisionObject::CollisionFuncType::Stay:
            _on_stay.emplace(key, lambda);
            break;
        case my::CollisionObject::CollisionFuncType::Exit:
            _on_exit.emplace(key, lambda);
            break;
        default:
            break;
    } // switch
}

bool my::CollisionObject::ExecuteEnterFunction(const std::string& key, const my::CollisionInfo& info) {
    auto it = _on_enter.find(key);
    if (it != _on_enter.end()) {
        it->second.Execute(info);
        return true;
    } // if
    return false;
}

bool my::CollisionObject::ExecuteStayFunction(const std::string& key, const my::CollisionInfo& info) {
    auto it = _on_stay.find(key);
    if (it != _on_stay.end()) {
        it->second.Execute(info);
        return true;
    } // if
    return false;
}

bool my::CollisionObject::ExecuteExitFunction(const std::string& key, const my::CollisionInfo& info) {
    auto it = _on_exit.find(key);
    if (it != _on_exit.end()) {
        it->second.Execute(info);
        return true;
    } // if
    return false;
}