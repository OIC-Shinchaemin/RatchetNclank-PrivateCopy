#include "ScarecrowComponent.h"

#include "../Collision/CollisionComponentDefine.h"
#include "../Collision/Object/ScarecrowCollisionComponent.h"
#include "../HpComponent.h"


ratchet::component::scarecrow::ScarecrowComponent::ScarecrowComponent(int priority) :
    super(priority),
    _hp_com() {
}

ratchet::component::scarecrow::ScarecrowComponent::ScarecrowComponent(const ScarecrowComponent& obj) :
    super(obj) {
}

ratchet::component::scarecrow::ScarecrowComponent::~ScarecrowComponent() {
}

std::string ratchet::component::scarecrow::ScarecrowComponent::GetType(void) const {
    return "ScarecrowComponent";
}

bool ratchet::component::scarecrow::ScarecrowComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _hp_com = super::GetOwner()->GetComponent<ratchet::component::HpComponent>();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::ScarecrowCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kOmniWrenchCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {

        if (auto hp_com = _hp_com.lock()) {
            hp_com->Damage(1);

            if (hp_com->GetHp() <= 0) {
                super::GetOwner()->End();
            } // if
        } // if
        return true;
    }));


    //coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
    //	ratchet::component::collision::CollisionComponentType::kShipCollisionComponent,
    //	ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
    //		if (auto canvas = _ui_canvas.lock()) {
    //			canvas->RemoveElement("EquipmentWeaponMenu");
    //			canvas->RemoveElement("QuickChangeMenu");
    //		} // if


    //		super::GetOwner()->End();
    //		return true;
    //		}));

    //coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
    //	ratchet::component::collision::CollisionComponentType::kWaterFlowCollisionComponent,
    //	ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
    //		if (this->GetNextTerrain() == "WaterFlow") {
    //			auto owner = super::GetOwner();
    //			auto velocity_com = owner->GetComponent<ratchet::component::VelocityComponent>();
    //			auto velocity = velocity_com->GetVelocity() * def::kDeltaTime;
    //			velocity.y = 0.0f;
    //			owner->SetPosition(owner->GetPosition() - velocity);
    //		} // if
    //		return true;
    //		}));

    return true;
}

bool ratchet::component::scarecrow::ScarecrowComponent::Update(float delta_time) {
    return true;
}

bool ratchet::component::scarecrow::ScarecrowComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::scarecrow::ScarecrowComponent::Clone(void) {
    return std::make_shared<ratchet::component::scarecrow::ScarecrowComponent>(*this);
}