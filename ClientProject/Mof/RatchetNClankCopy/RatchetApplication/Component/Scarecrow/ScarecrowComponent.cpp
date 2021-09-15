#include "ScarecrowComponent.h"

#include "Base/Core/Utility.h"
#include "../Collision/CollisionComponentDefine.h"
#include "../Collision/Object/ScarecrowCollisionComponent.h"
#include "../HpComponent.h"
#include "../../Actor/Character/Scarecrow.h"


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


            {
                auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Scarecrow>(super::GetOwner());
                auto pos = owner->GetPosition();
                pos.y += this->GetHeight();
                pos.x += ut::GenerateRandomF(-1.0f, 1.0f);
                pos.z += ut::GenerateRandomF(-1.0f, 1.0f);


                auto info = ratchet::effect::Effect::Info();
                info.init_param.life_duration = 1.0f;
                info.init_param.transform.position = pos;
                info.init_param.color = Mof::CVector4(1.0f, 1.0f, 1.0f, 1.0f);
                info.update_param.color = Mof::CVector4(0.0f, 0.0f, 0.0f, -0.02f);
                owner->GetEffectEmitter()->Emit(info);
            }



            if (hp_com->GetHp() <= 0) {
                super::GetOwner()->End();
            } // if
        } // if
        return true;
    }));
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