#include "BulletItemComponent.h"

#include "../../VelocityComponent.h"
#include "../../Collision/Object/CollisionComponentDefine.h"
#include "../../Collision/Object/BulletItemCollisionComponent.h"
#include "../../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../../Component/Collision/Object/SightCollisionComponent.h"
#include "BulletItemActionStateComponent.h"
#include "../../BillboardComponent.h"


my::BulletItemComponent::BulletItemComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

my::BulletItemComponent::BulletItemComponent(const BulletItemComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

my::BulletItemComponent::~BulletItemComponent() {
}

void my::BulletItemComponent::SetActorParam(const my::BulletItem::Param& param) {
    this->_param = param;
}

std::string my::BulletItemComponent::GetType(void) const {
    return "BulletItemComponent";
}

const my::BulletItem::Param& my::BulletItemComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<my::Actor> my::BulletItemComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool my::BulletItemComponent::Initialize(void) {
    super::Initialize();
    super::Activate();



    _state_com = super::GetOwner()->GetComponent<my::BulletItemActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto billboard_com = super::GetOwner()->GetComponent<my::BillboardComponent>();
    if (auto r = _resource_manager.lock()) {
        std::unordered_map<my::BulletItem::Type, std::string> path_map = {
            {my::BulletItem::Type::BombGlove, "../Resource/texture/icon/bomb_glove.png"},
            {my::BulletItem::Type::Pyrocitor, "../Resource/texture/icon/pyrocitor.png"},
            {my::BulletItem::Type::Blaster,   "../Resource/texture/icon/blaster.png"},
        };





        auto tex = r->Get<std::shared_ptr<Mof::CTexture>>(path_map.at(this->_param.type).c_str());

        billboard_com->SetTexture(tex);
    } // if



    auto coll_com = super::GetOwner()->GetComponent<my::BulletItemCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kPlayerCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    auto sight_coll = super::GetOwner()->GetComponent<my::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Stay,
                                 my::CollisionComponentType::kPlayerCollisionComponent,
                                 my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
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

bool my::BulletItemComponent::Update(float delta_time) {
    return true;
}

bool my::BulletItemComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BulletItemComponent::Clone(void) {
    return std::make_shared<my::BulletItemComponent>(*this);
}