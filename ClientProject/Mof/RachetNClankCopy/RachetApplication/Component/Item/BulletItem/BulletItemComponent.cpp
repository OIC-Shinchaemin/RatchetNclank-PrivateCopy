#include "BulletItemComponent.h"

#include "../../VelocityComponent.h"
#include "../../Collision/Object/CollisionComponentDefine.h"
#include "../../Collision/Object/BulletItemCollisionComponent.h"
#include "../../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../../Component/Collision/Object/SightCollisionComponent.h"
#include "BulletItemActionStateComponent.h"
#include "../../BillboardComponent.h"


rachet::BulletItemComponent::BulletItemComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

rachet::BulletItemComponent::BulletItemComponent(const BulletItemComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

rachet::BulletItemComponent::~BulletItemComponent() {
}

void rachet::BulletItemComponent::SetActorParam(const rachet::BulletItem::Param& param) {
    this->_param = param;
}

std::string rachet::BulletItemComponent::GetType(void) const {
    return "BulletItemComponent";
}

const rachet::BulletItem::Param& rachet::BulletItemComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<rachet::Actor> rachet::BulletItemComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool rachet::BulletItemComponent::Initialize(void) {
    super::Initialize();
    super::Activate();



    _state_com = super::GetOwner()->GetComponent<rachet::BulletItemActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto billboard_com = super::GetOwner()->GetComponent<rachet::BillboardComponent>();
    if (auto r = _resource_manager.lock()) {
        std::unordered_map<rachet::BulletItem::Type, std::string> path_map = {
            {rachet::BulletItem::Type::BombGlove, "../Resource/texture/icon/bomb_glove.png"},
            {rachet::BulletItem::Type::Pyrocitor, "../Resource/texture/icon/pyrocitor.png"},
            {rachet::BulletItem::Type::Blaster,   "../Resource/texture/icon/blaster.png"},
        };





        auto tex = r->Get<std::shared_ptr<Mof::CTexture>>(path_map.at(this->_param.type).c_str());

        billboard_com->SetTexture(tex);
    } // if



    auto coll_com = super::GetOwner()->GetComponent<rachet::BulletItemCollisionComponent>();
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               rachet::CollisionComponentType::kPlayerCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    auto sight_coll = super::GetOwner()->GetComponent<rachet::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Stay,
                                 rachet::CollisionComponentType::kPlayerCollisionComponent,
                                 rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        if (auto state_com = _state_com.lock()) {
            if (state_com->CanTransition(state::BulletItemActionType::kGravitate)) {
                state_com->ChangeState(state::BulletItemActionType::kGravitate);
                _player = in.target;
            } // if
        } // if
        return true;
    }));
    return true;
}

bool rachet::BulletItemComponent::Update(float delta_time) {
    return true;
}

bool rachet::BulletItemComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BulletItemComponent::Clone(void) {
    return std::make_shared<rachet::BulletItemComponent>(*this);
}