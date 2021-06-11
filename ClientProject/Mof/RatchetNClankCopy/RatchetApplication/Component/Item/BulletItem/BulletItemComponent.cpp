#include "BulletItemComponent.h"

#include "../../VelocityComponent.h"
#include "../../Collision/Object/CollisionComponentDefine.h"
#include "../../Collision/Object/BulletItemCollisionComponent.h"
#include "../../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../../Component/Collision/Object/SightCollisionComponent.h"
#include "BulletItemActionStateComponent.h"
#include "../../BillboardComponent.h"


ratchet::BulletItemComponent::BulletItemComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

ratchet::BulletItemComponent::BulletItemComponent(const BulletItemComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

ratchet::BulletItemComponent::~BulletItemComponent() {
}

void ratchet::BulletItemComponent::SetActorParam(const ratchet::actor::item::BulletItem::Param& param) {
    this->_param = param;
}

std::string ratchet::BulletItemComponent::GetType(void) const {
    return "BulletItemComponent";
}

const ratchet::actor::item::BulletItem::Param& ratchet::BulletItemComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<ratchet::actor::Actor> ratchet::BulletItemComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool ratchet::BulletItemComponent::Initialize(void) {
    super::Initialize();
    super::Activate();



    _state_com = super::GetOwner()->GetComponent<ratchet::BulletItemActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto billboard_com = super::GetOwner()->GetComponent<ratchet::BillboardComponent>();
    if (auto r = _resource_manager.lock()) {
        std::unordered_map<ratchet::actor::item::BulletItem::Type, std::string> path_map = {
            {ratchet::actor::item::BulletItem::Type::BombGlove, "../Resource/texture/icon/bomb_glove.png"},
            {ratchet::actor::item::BulletItem::Type::Pyrocitor, "../Resource/texture/icon/pyrocitor.png"},
            {ratchet::actor::item::BulletItem::Type::Blaster,   "../Resource/texture/icon/blaster.png"},
        };





        auto tex = r->Get<std::shared_ptr<Mof::CTexture>>(path_map.at(this->_param.type).c_str());

        billboard_com->SetTexture(tex);
    } // if



    auto coll_com = super::GetOwner()->GetComponent<ratchet::BulletItemCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    auto sight_coll = super::GetOwner()->GetComponent<ratchet::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Stay,
                                 ratchet::CollisionComponentType::kPlayerCollisionComponent,
                                 ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
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

bool ratchet::BulletItemComponent::Update(float delta_time) {
    return true;
}

bool ratchet::BulletItemComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BulletItemComponent::Clone(void) {
    return std::make_shared<ratchet::BulletItemComponent>(*this);
}