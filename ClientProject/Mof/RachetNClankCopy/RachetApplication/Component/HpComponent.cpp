#include "HpComponent.h"

#include "../State/AIPatrolState.h"
#include "../State/AICombatState.h"
#include "../UI/NanotechMenu.h"

my::HpComponent::HpComponent(int priority) :
    super(priority),
    _hp(4) {
}

my::HpComponent::HpComponent(const HpComponent& obj) :
    super(obj),
    _hp(obj._hp) {
}

my::HpComponent::~HpComponent() {
}

void my::HpComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::HpComponent::GetType(void) const {
    return "HpComponent";
}

bool my::HpComponent::Initialize(void) {
    super::Initialize();
    super::Start();
    auto tag = super::GetOwner()->GetTag();
    if (tag == "Player") {
        if (auto canvas = super::_ui_canvas.lock()) {
            auto menu = std::make_shared<my::NanotechMenu>("NanotechMenu");
            //Observable::AddObserver(menu);
            menu->SetColor(def::color_rgba::kCyan);
            menu->SetPosition(Mof::CVector2());
            canvas->AddElement(menu);
        } // if
    } // if

    return true;
}

bool my::HpComponent::Update(float delta_time) {
    return false;
}

#ifdef _DEBUG
bool my::HpComponent::Render(void) {
    return false;
}
#endif // _DEBUG

bool my::HpComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::HpComponent::Clone(void) {
    return std::make_shared<my::HpComponent>(*this);
}