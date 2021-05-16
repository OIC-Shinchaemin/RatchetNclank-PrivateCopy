#include "OmniWrench.h"

#include "../../Component/Collision/Object/OmniWrenchCollisionComponent.h"


my::OmniWrench::OmniWrench() :
    super() {
    super::SetTag("OmniWrench");
}

my::OmniWrench ::~OmniWrench() {
}

bool my::OmniWrench::Render(void) {
    super::Render();
    /*
    auto sphere = Mof::CSphere(super::GetPosition(), 0.3f);
    auto com = super::GetComponent<my::OmniWrenchCollisionComponent>();
    ::CGraphicsUtilities::RenderSphere(com->GetSphere().value(), def::color_rgba::kGreen);
    */
    return true;
}