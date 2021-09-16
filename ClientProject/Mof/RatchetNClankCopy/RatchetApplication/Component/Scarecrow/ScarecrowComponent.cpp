#include "ScarecrowComponent.h"

#include "Base/Core/Utility.h"
#include "../Collision/CollisionComponentDefine.h"
#include "../Collision/Object/ScarecrowCollisionComponent.h"
#include "../HpComponent.h"
#include "../../Actor/Character/Scarecrow.h"


void ratchet::component::scarecrow::ScarecrowComponent::DamageEffectEmit(std::shared_ptr<ratchet::actor::Actor> actor) {
    auto camera_pos = CGraphicsUtilities::GetCamera()->GetViewPosition();
    auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Scarecrow>(super::GetOwner());
    auto target_pos = actor->GetPosition();
    auto pos = (owner->GetPosition() + target_pos) * 0.5f;
    auto diff = Mof::CVector3(camera_pos - pos);
    diff.Normal(diff);
    pos += diff * super::GetVolume() * 2.0f;
    pos.y += this->GetHeight();

    auto info = ratchet::effect::Effect::Info();
    auto init_pos_offset = Mof::CVector3();
    auto init_scale = Mof::CVector3(1.0f, 1.0f, 1.0f);
    info.init_param.life_duration = 1.0f;
    info.init_param.color = Mof::CVector4(1.0f, 1.0f, 1.0f, 1.0f);
    info.update_param.color = Mof::CVector4(0.0f, 0.0f, 0.0f, -0.02f);
    info.environment_param.use_gravity = false;
    info.environment_param.use_velocity_drag = true;
    info.environment_param.velocity_drag = 0.5f;

    for (int i = 0, n = 5; i < n; i++) {
        info.init_param.transform.position = pos + init_pos_offset;
        info.init_param.transform.scale = init_scale;
        info.update_param.rotate = Mof::CVector3(0.0f, 1.0f, 0.0f);
        owner->GetEffectEmitter()->Emit(info);

        init_pos_offset = Mof::CVector3(
            ut::GenerateRandomF(-1.0f, 1.0f),
            ut::GenerateRandomF(-1.0f, 1.0f),
            ut::GenerateRandomF(-1.0f, 1.0f)
        );
        init_scale = Mof::CVector3(
            ut::GenerateRandomF(0.4f, 0.7f),
            ut::GenerateRandomF(0.4f, 0.7f),
            ut::GenerateRandomF(0.4f, 0.7f)
        );
        info.update_param.velocity = Mof::CVector3(
            ut::GenerateRandomF(-0.3f, 0.3f),
            0.4f,
            ut::GenerateRandomF(-0.3f, 0.3f)
        );
        info.update_param.rotate = Mof::CVector3(
            0.0f, ut::GenerateRandomF(-1.0f, 1.0f), 0.0f
        );
        info.update_param.scale = Mof::CVector3(-0.05f, -0.05f, -0.05f);
        info.environment_param.use_gravity = true;
        info.environment_param.gravity_scale = 0.01f;
    } // for

}

ratchet::component::scarecrow::ScarecrowComponent::ScarecrowComponent(int priority) :
    super(priority),
    _hp_com() {
}

ratchet::component::scarecrow::ScarecrowComponent::ScarecrowComponent(const ScarecrowComponent& obj) :
    super(obj),
    _hp_com() {
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

            this->DamageEffectEmit(in.target.lock());

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