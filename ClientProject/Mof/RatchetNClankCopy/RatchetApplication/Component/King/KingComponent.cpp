#include "KingComponent.h"

#include "../../Component/Collision/Object/KingCollisionComponent.h"
#include "../../Component/BillboardComponent.h"


ratchet::component::king::KingComponent::KingComponent(int priority) :
    super(priority) {
}

ratchet::component::king::KingComponent::KingComponent(const KingComponent& obj) :
    super(obj) {
}

ratchet::component::king::KingComponent::~KingComponent() {
}

std::string ratchet::component::king::KingComponent::GetType(void) const {
    return "KingComponent";
}

bool ratchet::component::king::KingComponent::Initialize(void) {
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

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::KingCollisionComponent>();
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

bool ratchet::component::king::KingComponent::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::component::king::KingComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::king::KingComponent::Clone(void) {
    return std::make_shared<ratchet::component::king::KingComponent>(*this);
}