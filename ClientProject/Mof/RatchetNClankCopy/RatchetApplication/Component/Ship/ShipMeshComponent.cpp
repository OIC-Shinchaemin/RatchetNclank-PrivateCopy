#include "ShipMeshComponent.h"

#include "../MotionComponent.h"


ratchet::ShipMeshComponent::ShipMeshComponent(int priority) :
    super(priority) ,
    _ship_mesh(){
}

ratchet::ShipMeshComponent::ShipMeshComponent(const ratchet::ShipMeshComponent& obj) :
    super(obj) ,
    _ship_mesh(obj._ship_mesh){
}

ratchet::ShipMeshComponent::~ShipMeshComponent() {
}

void ratchet::ShipMeshComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    _ship_mesh = super::GetMeshContainer()->GetMesh()->GetData(1);
}

std::string ratchet::ShipMeshComponent::GetType(void) const {
    return "ShipMeshComponent";
}

bool ratchet::ShipMeshComponent::Render(void) {
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    // •`‰æ
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

bool ratchet::ShipMeshComponent::Release(void) {
    super::Release();
    _ship_mesh = nullptr;
    return false;
}

std::shared_ptr<ratchet::component::Component> ratchet::ShipMeshComponent::Clone(void) {
    return std::make_shared<ratchet::ShipMeshComponent>(*this);
}