#include "HpComponent.h"

#include "../State/AI/AIPatrolState.h"
#include "../State/AI/AICombatState.h"
#include "../UI/NanotechMenu.h"


my::HpComponent::HpComponent(int priority) :
    super(priority),
    _hp_max(4),
    _hp(_hp_max),
    _ui_remove(false) {
}

my::HpComponent::HpComponent(const HpComponent& obj) :
    super(obj),
    _hp_max(obj._hp_max),
    _hp(obj._hp),
    _ui_remove(obj._ui_remove) {
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
    _hp = _hp_max;

    auto tag = super::GetOwner()->GetTag();
    if (tag == "Player") {
        if (auto canvas = super::_ui_canvas.lock()) {
            canvas->RemoveElement("NanotechMenu");
            _ui_remove = true;
            auto menu = std::make_shared<my::NanotechMenu>("NanotechMenu");
            _observable.AddObserver(menu);
            menu->SetPosition(Mof::CVector2(512.0f - 32.0f * 2.0f - 16.0f, 50.0f));
            menu->SetColor(Mof::CVector4(0.1f, 0.3f, 0.5f, 0.5f));
            canvas->AddElement(menu);
        } // if
    } // if
    return true;
}

bool my::HpComponent::Update(float delta_time) {
    return false;
}

bool my::HpComponent::Release(void) {
    super::Release();
    if (_ui_remove) {
        if (auto canvas = super::_ui_canvas.lock()) {
            canvas->RemoveElement("NanotechMenu");
        } // if
    } // if
    return true;
}

std::shared_ptr<my::Component> my::HpComponent::Clone(void) {
    return std::make_shared<my::HpComponent>(*this);
}

void my::HpComponent::Heal(int value) {
    _hp += value;
    if (_hp > _hp_max) {
        _hp = _hp_max;
    } // if
    _observable.Notify(_hp);
}

void my::HpComponent::Damage(int value) {
    _hp -= value;
    if (_hp <= 0) {
        _hp = 0;
        super::GetOwner()->End();
    } // if
    _observable.Notify(_hp);
}