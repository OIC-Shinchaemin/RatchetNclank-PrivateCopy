#include "BulletItemComponent.h"

#include "../../VelocityComponent.h"
#include "../../Collision/CollisionComponentDefine.h"
#include "../../Collision/Object/BulletItemCollisionComponent.h"
#include "../../../Component/Collision/CollisionComponentDefine.h"
#include "../../../Component/Collision/Object/SightCollisionComponent.h"
#include "BulletItemActionStateComponent.h"
#include "../../BillboardComponent.h"


ratchet::component::item::bulletitem::BulletItemComponent::BulletItemComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

ratchet::component::item::bulletitem::BulletItemComponent::BulletItemComponent(const BulletItemComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

ratchet::component::item::bulletitem::BulletItemComponent::~BulletItemComponent() {
}

void ratchet::component::item::bulletitem::BulletItemComponent::SetActorParam(const ratchet::actor::item::BulletItem::Param& param) {
    this->_param = param;
}

std::string ratchet::component::item::bulletitem::BulletItemComponent::GetType(void) const {
    return "BulletItemComponent";
}

const ratchet::actor::item::BulletItem::Param& ratchet::component::item::bulletitem::BulletItemComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<ratchet::actor::Actor> ratchet::component::item::bulletitem::BulletItemComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool ratchet::component::item::bulletitem::BulletItemComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<ratchet::component::item::bulletitem::BulletItemActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto billboard_com = super::GetOwner()->GetComponent<ratchet::component::BillboardComponent>();
    if (auto r = _resource_manager.lock()) {
        std::unordered_map<ratchet::actor::item::BulletItem::Type, std::string> path_map = {
            {ratchet::actor::item::BulletItem::Type::BombGlove, "../Resource/texture/icon/bomb_glove.png"},
            {ratchet::actor::item::BulletItem::Type::Pyrocitor, "../Resource/texture/icon/pyrocitor.png"},
            {ratchet::actor::item::BulletItem::Type::Blaster,   "../Resource/texture/icon/blaster.png"},
        };

        auto tex = r->Get<std::shared_ptr<Mof::CTexture>>(path_map.at(this->_param.type).c_str());

        billboard_com->SetTexture(tex);
    } // if



    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::BulletItemCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    auto sight_coll = super::GetOwner()->GetComponent<ratchet::component::collision::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                                 ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent,
                                 ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
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

bool ratchet::component::item::bulletitem::BulletItemComponent::Update(float delta_time) {
    return true;
}

bool ratchet::component::item::bulletitem::BulletItemComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::bulletitem::BulletItemComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::bulletitem::BulletItemComponent>(*this);
}