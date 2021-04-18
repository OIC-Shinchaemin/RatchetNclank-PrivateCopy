#include "CollisionObject.h"

#include "My/Core/Utility.h"


void my::CollisionObject::AddCollisionFunc(const std::string& target, const CollisionFunc& obj, std::unordered_map<std::string, FuncArray>& out) {
    if (auto it = out.find(target); it == out.end()) {
        out.emplace(target, FuncArray());
    } // if
    out.at(target).push_back(obj);
}

bool my::CollisionObject::ExecuteFunction(const std::string& key, const my::CollisionInfo& info, const std::unordered_map<std::string, FuncArray>& in) {
    auto it = in.find(key);
    if (it != in.end()) {
        for (const auto& func : it->second) {
            func.Execute(info);
        } // for
        return true;
    } // if
    return false;
}

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

void my::CollisionObject::AddCollisionFunc(CollisionFuncType type, const std::string& target, const CollisionFunc& obj) {
    switch (type) {
        case my::CollisionObject::CollisionFuncType::Enter:
            this->AddCollisionFunc(target, obj, _on_enter);
            break;
        case my::CollisionObject::CollisionFuncType::Stay:
            this->AddCollisionFunc(target, obj, _on_stay);
            break;
        case my::CollisionObject::CollisionFuncType::Exit:
            this->AddCollisionFunc(target, obj, _on_exit);
            break;
        default:
            break;
    } // switch
}

bool my::CollisionObject::ExecuteEnterFunction(const std::string& key, const my::CollisionInfo& info) {
    return this->ExecuteFunction(key, info, _on_enter);
}

bool my::CollisionObject::ExecuteStayFunction(const std::string& key, const my::CollisionInfo& info) {
    return this->ExecuteFunction(key, info, _on_stay);
}

bool my::CollisionObject::ExecuteExitFunction(const std::string& key, const my::CollisionInfo& info) {
    return this->ExecuteFunction(key, info, _on_exit);
}