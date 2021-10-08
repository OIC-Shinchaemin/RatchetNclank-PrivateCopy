#include "QueenComponent.h"

#include "../VelocityComponent.h"
#include "../../Component/Collision/Object/QueenCollisionComponent.h"
#include "../../Component/BillboardComponent.h"

ratchet::component::queen::QueenComponent::QueenComponent(int priority) :
    super(priority) {
}

ratchet::component::queen::QueenComponent::QueenComponent(const QueenComponent& obj) :
    super(obj) {
}

ratchet::component::queen::QueenComponent::~QueenComponent() {
}

std::string ratchet::component::queen::QueenComponent::GetType(void) const {
    return "QueenComponent";
}

bool ratchet::component::queen::QueenComponent::Initialize(void) {
    super::Initialize();
    super::Activate();


    auto velocity = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    velocity->Inactivate();
    velocity->SetUseGravity(false);

    auto billboard = super::GetOwner()->GetComponent<ratchet::component::BillboardComponent>();
    billboard->Activate();
    auto pos = Mof::CVector3();
    pos.y += 3.0f;
    billboard->SetOffsetPosition(pos);
    billboard->SetOffsetRotation(-super::GetOwner()->GetRotate());

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::QueenCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto billboard = super::GetOwner()->GetComponent<component::BillboardComponent>();
        //billboard->Activate();
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Exit,
                               ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto billboard = super::GetOwner()->GetComponent<component::BillboardComponent>();
        //billboard->Inactivate();
        return true;
    }));
    return true;
}

bool ratchet::component::queen::QueenComponent::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::component::queen::QueenComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::queen::QueenComponent::Clone(void) {
    return std::make_shared<ratchet::component::queen::QueenComponent>(*this);
}