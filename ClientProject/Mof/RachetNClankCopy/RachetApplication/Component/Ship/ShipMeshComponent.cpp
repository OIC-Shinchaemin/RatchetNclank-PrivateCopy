#include "ShipMeshComponent.h"

#include "../MotionComponent.h"


my::ShipMeshComponent::ShipMeshComponent(int priority) :
    super(priority) {
}

my::ShipMeshComponent::ShipMeshComponent(const my::ShipMeshComponent& obj) :
    super(obj){
}

my::ShipMeshComponent::~ShipMeshComponent() {
}

std::string my::ShipMeshComponent::GetType(void) const {
    return "ShipMeshComponent";
}

bool my::ShipMeshComponent::Render(void) {
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    // •`‰æ
    if (auto r = _mesh.lock()) {
        Mof::CMatrix44 scale, rotate, translate;
        scale.Scaling(super::GetOwner()->GetScale(), scale);
        rotate.RotationZXY(super::GetOwner()->GetRotate());
        translate.Translation(super::GetOwner()->GetPosition(), translate);
        auto world = scale * rotate * translate;

        auto mesh = r->GetMesh()->GetData(1);
        if (auto motion_com = _motion_com.lock()) {
            auto motion = motion_com->GetMotionData();
            motion->RefreshBoneMatrix(world);
            // ˆø”‚ÉUV‚ª‚ ‚é‚Ì‚Å‚±‚ê‚ð‘‚â‚µ‚Ä‚¢‚­
            mesh->Render(motion, _color);
        } // if
        else {
            mesh->Render(world);
        } // else
    } // if
    return true;
}

std::shared_ptr<my::Component> my::ShipMeshComponent::Clone(void) {
    return std::make_shared<my::ShipMeshComponent>(*this);
}