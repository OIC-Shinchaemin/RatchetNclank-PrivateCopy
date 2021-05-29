#include "ShipMeshComponent.h"

#include "../MotionComponent.h"


my::ShipMeshComponent::ShipMeshComponent(int priority) :
    super(priority) {
}

my::ShipMeshComponent::ShipMeshComponent(const my::ShipMeshComponent& obj) :
    super(obj) {
}

my::ShipMeshComponent::~ShipMeshComponent() {
}

void my::ShipMeshComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    _ship_mesh = super::GetMeshContainer()->GetMesh()->GetData(1);
}

std::string my::ShipMeshComponent::GetType(void) const {
    return "ShipMeshComponent";
}

bool my::ShipMeshComponent::Render(void) {
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    // �`��
    Mof::CMatrix44 scale, rotate, translate;
    scale.Scaling(super::GetOwner()->GetScale(), scale);
    rotate.RotationZXY(super::GetOwner()->GetRotate());
    translate.Translation(super::GetOwner()->GetPosition(), translate);
    auto world = scale * rotate * translate;

    if (auto motion_com = _motion_com.lock()) {
        auto motion = motion_com->GetMotionData();
        motion->RefreshBoneMatrix(world);
        _ship_mesh->Render(motion, super::GetColor());
    } // if
    return true;
}

std::shared_ptr<my::Component> my::ShipMeshComponent::Clone(void) {
    return std::make_shared<my::ShipMeshComponent>(*this);
}