#include "CollisionComponent.h"

#include "My/Core/Utility.h"
#include "../../VelocityComponent.h"


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

bool my::CollisionComponent::CollisionShpereAABB(const Mof::CSphere& sphere, const Mof::CBoxAABB& box) {
    Mof::CVector3 point;
    auto pos = sphere.Position;
    // x
    if (pos.x < box.Position.x - box.Size.x) {
        point.x = box.Position.x - box.Size.x;
    } // if
    else if (box.Position.x + box.Size.x < pos.x) {
        point.x = box.Position.x + box.Size.x;
    } // else if
    else {
        point.x = pos.x;
    } // else
    // y
    if (pos.y < box.Position.y - box.Size.y) {
        point.y = box.Position.y - box.Size.y;
    } // if
    else if (box.Position.y + box.Size.y < pos.y) {
        point.y = box.Position.y + box.Size.y;
    } // else if
    else {
        point.y = pos.y;
    } // else
    // z
    if (pos.z < box.Position.z - box.Size.z) {
        point.z = box.Position.z - box.Size.z;
    } // if
    else if (box.Position.z + box.Size.z < pos.z) {
        point.z = box.Position.z + box.Size.z;
    } // else if
    else {
        point.z = pos.z;
    } // else
    return Mof::CVector3Utilities::Distance(sphere.Position, point) < sphere.r;
}

my::CollisionComponent::CollisionComponent(int priority) :
    super(priority),
    _collisioned(),
    _on_enter(),
    _on_stay(),
    _on_exit(),
    _velocity_com() {
}

my::CollisionComponent::~CollisionComponent() {
}

bool my::CollisionComponent::IsSleep(void) const {
    if (auto velocity_com = _velocity_com.lock())  {
        return velocity_com->IsSleep();
    } // if
    return false;
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

bool my::CollisionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    return true;
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

void my::CollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}

void my::CollisionComponent::CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) {
}