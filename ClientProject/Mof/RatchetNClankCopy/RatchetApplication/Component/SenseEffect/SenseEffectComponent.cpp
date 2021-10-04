#include "SenseEffectComponent.h"


ratchet::component::effect::SenseEffectComponent::SenseEffectComponent(int priority) :
    super(priority),
    _billboard_render_offset(Mof::CVector3(0.0f, 2.0f, 0.0f)),
    _billboard(),
    _timer() {
}

ratchet::component::effect::SenseEffectComponent::SenseEffectComponent(const SenseEffectComponent& obj) :
    super(obj),
    _billboard_render_offset(obj._billboard_render_offset),
    _billboard(),
    _timer() {
}

ratchet::component::effect::SenseEffectComponent::~SenseEffectComponent() {
}

std::string ratchet::component::effect::SenseEffectComponent::GetType(void) const {
    static std::string name = typeid(*this).name();
    static std::string colon = "::";
    auto it = name.find_last_of(colon, name.size());
    auto substr = name.substr(it + colon.size() - 1);
    return substr;
}

bool ratchet::component::effect::SenseEffectComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _timer.Initialize(1.0f, false);

    auto billboard = super::GetOwner()->GetComponent<ratchet::component::BillboardComponent>();
    _billboard = billboard;
    billboard->Activate();
    billboard->SetOffsetPosition(_billboard_render_offset);
    return true;
}

bool ratchet::component::effect::SenseEffectComponent::Update(float delta_time) {
    super::Update(delta_time);
    if (_timer.Tick(delta_time)) {
        super::GetOwner()->Hide();
    } // if
    if (auto bill = _billboard.lock()) {
        float t = _timer();

        auto c = bill->GetColor();
        c.a = 1.0f - t;
        bill->SetColor(c);
    } // if

    return true;
}

bool ratchet::component::effect::SenseEffectComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::effect::SenseEffectComponent::Clone(void) {
    return std::make_shared<ratchet::component::effect::SenseEffectComponent>(*this);
}

bool ratchet::component::effect::SenseEffectComponent::DebugRender(void) {
    return true;
}

void ratchet::component::effect::SenseEffectComponent::TimerStart(void) {
    _timer.Initialize(1.0f, false);
}