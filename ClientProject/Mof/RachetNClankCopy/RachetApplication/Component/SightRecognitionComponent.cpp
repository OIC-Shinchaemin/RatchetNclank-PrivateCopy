#include "SightRecognitionComponent.h"

#include "My/Core/Math.h"


my::SightRecognitionComponent::SightRecognitionComponent(int priority) :
    super(priority),
    _range(5.0f) {
}

my::SightRecognitionComponent::SightRecognitionComponent(const SightRecognitionComponent& obj) :
    super(obj._priority),
    _range(obj._range) {
}

my::SightRecognitionComponent::~SightRecognitionComponent() {
}

std::string my::SightRecognitionComponent::GetType(void) const {
    return "SightRecognitionComponent";
}

float my::SightRecognitionComponent::GetRange(void) const {
    return this->_range;
}

bool my::SightRecognitionComponent::ContainInRecognitionRange(Mof::CVector3 target) {
    // ëäéËÇ÷ÇÃÉxÉNÉgÉãÇ∆é©ï™ÇÃëOï˚ÉxÉNÉgÉãÇÃì‡êœÇ™ê≥Åi>ÇOÅjÇÃèÍçáÇÕâsäpÇ≈Ç†ÇËëOï˚ÇXÇOÅãà»ì‡Ç∆îªífÇ≈Ç´ÇÈ
    auto pos = super::GetOwner()->GetPosition();
    auto rotate = super::GetOwner()->GetRotate();

    if (!Mof::CSphere(pos, _range).CollisionPoint(target)) {
        return false;
    } // if


    Mof::CVector3 dir = target - pos;
    Mof::CVector3 front(-math::vec3::kUnitZ);
    Mof::CMatrix33 mat;
    mat.RotationZXY(rotate);
    front *= mat;
    if (front.Dot(dir) > 0.0f) {
        return true;
        /* è·äQï®ñ≥Ç¢Ç»ÇÁå©Ç¶ÇÈÇ‡ÇÃÇ∆Ç∑ÇÈ
        _recognition.push_back(candidate);
        */
    } // if
    return false;
}

std::shared_ptr<my::Component> my::SightRecognitionComponent::Clone(void) {
    return std::make_shared<my::SightRecognitionComponent>(*this);
}