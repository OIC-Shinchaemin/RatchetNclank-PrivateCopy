#include "Actor.h"

#include "Base/Core/Math.h"
#include "Base/Core/Utility.h"
#include "Component/Component.h"
#include "Factory/Builder/IBuilder.h"


void rachet::Actor::Activate(void) {
    this->_state = rachet::ActorState::Active;
}
void rachet::Actor::Sleep(void) {
    this->_state = rachet::ActorState::Sleep;
}
void rachet::Actor::Pause(void) {
    this->_state = rachet::ActorState::Pause;
}

rachet::Actor::Actor() :
    _state(rachet::ActorState::Active),
    _name(),
    _tag(),
    _transform(),
    _initial_transform(),
    _components(),
    _input_components(),
    _update_components(),
    _render_components() {
}

rachet::Actor::~Actor() {
}

void rachet::Actor::SetName(const char* name) {
    this->_name = name;
}

void rachet::Actor::SetTag(const char* tag) {
    this->_tag = tag;
}

void rachet::Actor::SetPosition(Mof::CVector3 position) {
    this->_transform.position = position;
}

void rachet::Actor::SetRotate(Mof::CVector3 rotate) {
    this->_transform.rotate = rotate;
}

void rachet::Actor::SetScale(Mof::CVector3 scale) {
    this->_transform.scale = scale;
}

void rachet::Actor::SetParentTransform(std::optional<Mof::CMatrix44> transform) {
    this->_parent_transform = transform;
}

std::string rachet::Actor::GetName(void) const {
    return this->_name;
}

std::string rachet::Actor::GetTag(void) const {
    return this->_tag;
}

Mof::CVector3 rachet::Actor::GetPosition(void) const {
    return this->_transform.position;
}

Mof::CVector3 rachet::Actor::GetRotate(void) const {
    return this->_transform.rotate;
}

Mof::CVector3 rachet::Actor::GetScale(void) const {
    return this->_transform.scale;
}

Mof::CVector3 rachet::Actor::GetInitialPosition(void) const {
    return this->_initial_transform.position;
}

std::optional<Mof::CMatrix44> rachet::Actor::GetParentTransform(void) const {
    return this->_parent_transform;
}

rachet::ActorState rachet::Actor::GetState(void) const {
    return this->_state;
}

bool rachet::Actor::InCameraRange(void) const {
    const int camera_range = 30.0f;
    auto pos = ::CGraphicsUtilities::GetCamera()->GetViewPosition();
    auto sphere = Mof::CSphere(pos, camera_range);
    return sphere.CollisionPoint(this->GetPosition());
}

bool rachet::Actor::InFrustum(void) const {
    auto box = Mof::CBoxAABB();


    return false;
}

void rachet::Actor::AddComponent(const ComPtr& component) {
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

void rachet::Actor::CloneToComponents(const ComArray& com_array) {
    std::transform(com_array.begin(), com_array.end(), std::back_inserter(_components), [](const std::shared_ptr<rachet::Component>& component) {
        return component->Clone();
    });
}

void rachet::Actor::RemoveComponent(const ComPtr& component) {
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

void rachet::Actor::End(void) {
    this->_state = rachet::ActorState::End;
    Observable::Notify("DeleteRequest", shared_from_this());
}

bool rachet::Actor::Initialize(void) {
    _state = rachet::ActorState::Active;
    _transform = _initial_transform;

    // コンポーネントの初期化
    for (auto& com : _components) {
        com->Initialize();
    } // for
    return true;
}

bool rachet::Actor::Initialize(rachet::Actor::Param* param) {
    _state = rachet::ActorState::Active;
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

bool rachet::Actor::Input(void) {
    for (auto& com : _input_components) {
        if (com->IsActive()) {
            com->Input();
        } // if
    } // for
    return true;
}

bool rachet::Actor::Update(float delta_time) {
    for (auto& com : _update_components) {
        if (com->IsActive()) {
            com->Update(delta_time);
        } // if
    } // for
    return true;
}

bool rachet::Actor::Render(void) {
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

bool rachet::Actor::Release(void) {
    _input_components.clear();
    _update_components.clear();
    _render_components.clear();
    for (auto& com : _components) {
        com->Release();
    } // for
    _components.clear();
    return true;
}

void rachet::Actor::Construct(const std::shared_ptr<rachet::IBuilder>& builder) {
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