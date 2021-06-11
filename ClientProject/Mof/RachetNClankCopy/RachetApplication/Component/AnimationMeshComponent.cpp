#include "AnimationMeshComponent.h"

#include "MotionComponent.h"


rachet::AnimationMeshComponent::AnimationMeshComponent(int priority) :
    super(priority),
    _motion_com() {
}

rachet::AnimationMeshComponent::AnimationMeshComponent(const rachet::AnimationMeshComponent& obj) :
    super(obj),
    _motion_com() {
}

rachet::AnimationMeshComponent::~AnimationMeshComponent() {
}

std::string rachet::AnimationMeshComponent::GetType(void) const {
    return "AnimationMeshComponent";
}

bool rachet::AnimationMeshComponent::Initialize(void) {
    super::Initialize();
    _motion_com = super::GetOwner()->GetComponent<rachet::MotionComponent>();
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

bool rachet::AnimationMeshComponent::Render(void) {
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

bool rachet::AnimationMeshComponent::Release(void) {
    super::Release();
    _motion_com.reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::AnimationMeshComponent::Clone(void) {
    return std::make_shared<rachet::AnimationMeshComponent>(*this);
}