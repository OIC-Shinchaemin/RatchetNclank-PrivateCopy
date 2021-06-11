#include "Actor.h"

#include "Base/Core/Math.h"
#include "Base/Core/Utility.h"
#include "Component/Component.h"
#include "Factory/Builder/IBuilder.h"


void ratchet::Actor::Activate(void) {
    this->_state = ratchet::ActorState::Active;
}
void ratchet::Actor::Sleep(void) {
    this->_state = ratchet::ActorState::Sleep;
}
void ratchet::Actor::Pause(void) {
    this->_state = ratchet::ActorState::Pause;
}

ratchet::Actor::Actor() :
    _state(ratchet::ActorState::Active),
    _name(),
    _tag(),
    _transform(),
    _initial_transform(),
    _components(),
    _input_components(),
    _update_components(),
    _render_components() {
}

ratchet::Actor::~Actor() {
}

void ratchet::Actor::SetName(const char* name) {
    this->_name = name;
}

void ratchet::Actor::SetTag(const char* tag) {
    this->_tag = tag;
}

void ratchet::Actor::SetPosition(Mof::CVector3 position) {
    this->_transform.position = position;
}

void ratchet::Actor::SetRotate(Mof::CVector3 rotate) {
    this->_transform.rotate = rotate;
}

void ratchet::Actor::SetScale(Mof::CVector3 scale) {
    this->_transform.scale = scale;
}

void ratchet::Actor::SetParentTransform(std::optional<Mof::CMatrix44> transform) {
    this->_parent_transform = transform;
}

std::string ratchet::Actor::GetName(void) const {
    return this->_name;
}

std::string ratchet::Actor::GetTag(void) const {
    return this->_tag;
}

Mof::CVector3 ratchet::Actor::GetPosition(void) const {
    return this->_transform.position;
}

Mof::CVector3 ratchet::Actor::GetRotate(void) const {
    return this->_transform.rotate;
}

Mof::CVector3 ratchet::Actor::GetScale(void) const {
    return this->_transform.scale;
}

Mof::CVector3 ratchet::Actor::GetInitialPosition(void) const {
    return this->_initial_transform.position;
}

std::optional<Mof::CMatrix44> ratchet::Actor::GetParentTransform(void) const {
    return this->_parent_transform;
}

ratchet::ActorState ratchet::Actor::GetState(void) const {
    return this->_state;
}

bool ratchet::Actor::InCameraRange(void) const {
    const int camera_range = 30.0f;
    auto pos = ::CGraphicsUtilities::GetCamera()->GetViewPosition();
    auto sphere = Mof::CSphere(pos, camera_range);
    return sphere.CollisionPoint(this->GetPosition());
}

bool ratchet::Actor::InFrustum(void) const {
    auto box = Mof::CBoxAABB();


    return false;
}

void ratchet::Actor::AddComponent(const ComPtr& component) {
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

void ratchet::Actor::CloneToComponents(const ComArray& com_array) {
    std::transform(com_array.begin(), com_array.end(), std::back_inserter(_components), [](const std::shared_ptr<ratchet::Component>& component) {
        return component->Clone();
    });
}

void ratchet::Actor::RemoveComponent(const ComPtr& component) {
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

void ratchet::Actor::End(void) {
    this->_state = ratchet::ActorState::End;
    Observable::Notify("DeleteRequest", shared_from_this());
}

bool ratchet::Actor::Initialize(void) {
    _state = ratchet::ActorState::Active;
    _transform = _initial_transform;

    // コンポーネントの初期化
    for (auto& com : _components) {
        com->Initialize();
    } // for
    return true;
}

bool ratchet::Actor::Initialize(ratchet::Actor::Param* param) {
    _state = ratchet::ActorState::Active;
    _name = param->name;
    _transform = param->transform;
    _initial_transform = _transform;

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

bool ratchet::Actor::Input(void) {
    for (auto& com : _input_components) {
        if (com->IsActive()) {
            com->Input();
        } // if
    } // for
    return true;
}

bool ratchet::Actor::Update(float delta_time) {
    for (auto& com : _update_components) {
        if (com->IsActive()) {
            com->Update(delta_time);
        } // if
    } // for
    return true;
}

bool ratchet::Actor::Render(void) {
    bool re = false;
    for (auto& com : _render_components) {
        if (com->IsActive()) {
            com->Render();
#ifdef _DEBUG
            com->DebugRender();
#endif // _DEBUG
            re = true;
        } // if
    } // for
    return re;
}

bool ratchet::Actor::Release(void) {
    _input_components.clear();
    _update_components.clear();
    _render_components.clear();
    for (auto& com : _components) {
        com->Release();
    } // for
    _components.clear();
    return true;
}

void ratchet::Actor::Construct(const std::shared_ptr<ratchet::IBuilder>& builder) {
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