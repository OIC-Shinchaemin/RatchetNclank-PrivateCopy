#include "AnimationMeshComponent.h"

#include "MotionComponent.h"
#include "../Game/Graphics/RenderAnimationMeshCommand.h"


ratchet::component::AnimationMeshComponent::AnimationMeshComponent(int priority) :
    super(priority),
    _motion_com() {
}

ratchet::component::AnimationMeshComponent::AnimationMeshComponent(const ratchet::component::AnimationMeshComponent& obj) :
    super(obj),
    _motion_com() {
}

ratchet::component::AnimationMeshComponent::~AnimationMeshComponent() {
}

std::string ratchet::component::AnimationMeshComponent::GetType(void) const {
    return "AnimationMeshComponent";
}

bool ratchet::component::AnimationMeshComponent::Initialize(void) {
    super::Initialize();
    _motion_com = super::GetOwner()->GetComponent<ratchet::component::MotionComponent>();
#ifdef _DEBUG
    auto mesh = super::GetMeshContainer();
    auto bone_array = mesh->GetBone();
    for (int i = 0, n = bone_array->GetArrayCount(); i < n; i++) {
        auto bone = bone_array->GetData(i);
        std::cout << "bone->GetName() = " << *bone->GetName() << "\n";
    } // for
#endif // _DEBUG
    return true;
}

bool ratchet::component::AnimationMeshComponent::Render(void) {
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    auto owner = super::GetOwner();
    // •`‰æ
    if (auto mesh =  super::GetMeshContainer()) {
        Mof::CMatrix44 scale, rotate, translate;
        Mof::CQuaternion quat; quat.Rotation(owner->GetRotate());

        scale.Scaling(owner->GetScale(), scale);
        quat.ConvertMatrixTranspose(rotate);
        translate.Translation(owner->GetPosition(), translate);
        Mof::CMatrix44 world = scale * rotate * translate;

        if (auto motion_com = _motion_com.lock()) {
            auto motion = motion_com->GetMotionData();
            motion->RefreshBoneMatrix(world);
            mesh->Render(motion, super::GetColor());
        } // if
    } // if
    return true;
}

bool ratchet::component::AnimationMeshComponent::Render(std::shared_ptr<ratchet::game::graphics::RenderCommandTask> out) {
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    auto owner = super::GetOwner();
    // •`‰æ
    if (auto mesh = super::GetMeshContainer()) {
        Mof::CMatrix44 scale, rotate, translate;
        Mof::CQuaternion quat; quat.Rotation(owner->GetRotate());

        scale.Scaling(owner->GetScale(), scale);
        quat.ConvertMatrixTranspose(rotate);
        translate.Translation(owner->GetPosition(), translate);
        Mof::CMatrix44 world = scale * rotate * translate;

        if (auto motion_com = _motion_com.lock()) {
            auto motion = motion_com->GetMotionData();
            motion->RefreshBoneMatrix(world);
//            mesh->Render(motion, super::GetColor());
            auto command = std::make_shared<ratchet::game::graphics::RenderAnimationMeshCommand>(mesh, motion, super::GetColor());
            out->Push(command, _target_layer);
        } // if
    } // if
    return true;
}

bool ratchet::component::AnimationMeshComponent::Release(void) {
    super::Release();
    _motion_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::AnimationMeshComponent::Clone(void) {
    return std::make_shared<ratchet::component::AnimationMeshComponent>(*this);
}