#include "Actor.h"

#include "My/Core/Math.h"
#include "My/Core/Utility.h"
#include "Component/Component.h"
#include "Factory/IBuilder.h"


Mof::CVector3 my::Actor::UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity) {
    float sleep_threshold = 0.01f;
    if (sleep_threshold < velocity.Length()) {
        rotate += velocity * delta_time;
    } // if

    if (math::kTwoPi <= rotate.y) {
        rotate.y -= math::kTwoPi;
    } // if
    else if (rotate.y <= 0.0f) {
        rotate.y += math::kTwoPi;
    } // else if
    return rotate;
}

Mof::CVector3 my::Actor::UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity) {
    float sleep_threshold = 0.001f;

    if (sleep_threshold < velocity.Length()) {
        position += velocity * delta_time;
    } // if
    return position;
}

void my::Actor::UpdateTransform(float delta_time) {
    // rotate
    auto rotate = this->UpdateRotate(delta_time, this->GetRotate(), _velocity.GetAngularVelocity());
    this->SetRotate(rotate);
    // position
    auto pos = this->UpdatePosition(delta_time, this->GetPosition(), _velocity.GetVelocity());
    this->SetPosition(pos);
}

my::Actor::Actor() :
    _state(my::ActorState::Active),
    _name(),
    _transform(),
    _components(),
    _input_components(),
    _update_components(),
    _render_components(),
    _collision_objects(),
    _velocity() {
}

my::Actor::~Actor() {
}

void my::Actor::SetName(const char* name) {
    this->_name = name;
}

void my::Actor::SetPosition(Mof::CVector3 position) {
    this->_transform.position = position;
}

void my::Actor::SetRotate(Mof::CVector3 rotate) {
    this->_transform.rotate = rotate;
}

void my::Actor::SetScale(Mof::CVector3 scale) {
    this->_transform.scale = scale;
}

std::string my::Actor::GetName(void) const {
    return this->_name;
}

Mof::CVector3 my::Actor::GetPosition(void) const {
    return this->_transform.position;
}

Mof::CVector3 my::Actor::GetRotate(void) const {
    return this->_transform.rotate;
}

Mof::CVector3 my::Actor::GetScale(void) const {
    return this->_transform.scale;
}

my::ActorState my::Actor::GetState(void) const {
    return this->_state;
}

const std::vector<std::shared_ptr<my::CollisionObject>>& my::Actor::GetCollisionObjects(void) const {
    return this->_collision_objects;
}

void my::Actor::AddComponent(const ComPtr& component) {
    if (component->IsInput()) {
        ut::InsertAscend(_input_components, component);
    } // if
    if (component->IsUpdate()) {
        ut::InsertAscend(_update_components, component);
    } // if
    if (component->IsRender()) {
        ut::InsertAscend(_render_components, component);
    } // if


    // 追加されるComponentが指定の優先度で処理されるようにする
    ut::InsertAscend(_components, component);
    component->SetOwner(shared_from_this());
    component->Initialize();
}

void my::Actor::CloneToComponents(const ComArray& com_array) {
    std::transform(com_array.begin(), com_array.end(), std::back_inserter(_components), [](const std::shared_ptr<my::Component>& component) {
        return component->Clone();
    });
}

void my::Actor::RemoveComponent(const ComPtr& component) {
    if (component->IsInput()) {
        ut::EraseFind(_input_components, component);
    } // if
    if (component->IsUpdate()) {
        ut::EraseFind(_update_components, component);
    } // if
    if (component->IsRender()) {
        ut::EraseFind(_render_components, component);
    } // if


    component->Release();
    ut::EraseFind(_components, component);
}

void my::Actor::End(void) {
    this->_state = my::ActorState::End;
    Observable::Notify("DeleteRequest", shared_from_this());
}

bool my::Actor::Initialize(my::Actor::Param* param) {
    _state = my::ActorState::Active;
    _transform = param->transform;
    _name = param->name;

        // コンポーネントの初期化
    for (auto& com : _components) {
        com->Initialize();
    } // for
    // 優先度順に整列
    std::sort(_components.begin(), _components.end());
    std::sort(_input_components.begin(), _input_components.end());
    std::sort(_update_components.begin(), _update_components.end());
    std::sort(_render_components.begin(), _render_components.end());
    return true;
}

bool my::Actor::Input(void) {
    for (auto& com : _input_components) {
        com->Input();
    } // for
    return true;
}

bool my::Actor::Update(float delta_time) {
    for (auto& com : _update_components) {
        if (com->IsActive()) {
            com->Update(delta_time);
        } // if
    } // for
    return true;
}

bool my::Actor::Render(void) {
    for (auto& com : _render_components) {
        if (com->IsActive()) {
            com->Render();
        } // if
    } // for
    return true;
}

bool my::Actor::Release(void) {
    _collision_objects.clear();
    _input_components.clear();
    _update_components.clear();
    _render_components.clear();
    for (auto& com : _components) {
        com->Release();
    } // for
    _components.clear();
    return true;
}

void my::Actor::Construct(const std::shared_ptr<my::IBuilder>& builder) {
    builder->Construct(shared_from_this());

    auto& coms = _components;
    // 仕分け
    std::copy_if(coms.begin(), coms.end(), std::back_inserter(_input_components), [](ComPtr com) {
        return com->IsInput();
    });
    std::copy_if(coms.begin(), coms.end(), std::back_inserter(_update_components), [](ComPtr com) {
        return com->IsUpdate();
    });
    std::copy_if(coms.begin(), coms.end(), std::back_inserter(_render_components), [](ComPtr com) {
        return com->IsRender();
    });

    for (auto& c : _components) {
        c->SetOwner(shared_from_this());
    } // for
}

void my::Actor::RenderDebug(void) {
}