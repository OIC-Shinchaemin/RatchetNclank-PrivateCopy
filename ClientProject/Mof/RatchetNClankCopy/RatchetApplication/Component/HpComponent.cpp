#include "HpComponent.h"

#include "../State/AI/AIPatrolState.h"
#include "../State/AI/AICombatState.h"
#include "../UI/NanotechMenu.h"


ratchet::HpComponent::HpComponent(int priority) :
    super(priority),
    _hp_max(0),
    _hp(_hp_max),
    _ui_remove(false) {
}

ratchet::HpComponent::HpComponent(const HpComponent& obj) :
    super(obj),
    _hp_max(obj._hp_max),
    _hp(_hp_max),
    _ui_remove(obj._ui_remove) {
}

ratchet::HpComponent::~HpComponent() {
}

void ratchet::HpComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* hp_max = "hp_max";

    _ASSERT_EXPR(param.HasMember(hp_max), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[hp_max].IsInt(), L"パラメータの指定された型でありません");
    this->_hp_max = param[hp_max].GetInt();
}

std::string ratchet::HpComponent::GetType(void) const {
    return "HpComponent";
}

int ratchet::HpComponent::GetHp(void) const {
    return this->_hp;
}

bool ratchet::HpComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    _hp = _hp_max;

    auto tag = super::GetOwner()->GetTag();
    if (tag == "Player") {
        if (auto canvas = super::_ui_canvas.lock()) {
            canvas->RemoveElement("NanotechMenu");
            _ui_remove = true;
            auto menu = std::make_shared<ratchet::ui::NanotechMenu>("NanotechMenu");
            _observable.AddObserver(menu);
            menu->SetResourceManager(_resource_manager);
            menu->SetColor(Mof::CVector4(0.1f, 0.3f, 0.5f, 0.5f));
            canvas->AddElement(menu);
            _observable.Notify(_hp);
        } // if
    } // if
    return true;
}

bool ratchet::HpComponent::Update(float delta_time) {
    return false;
}

bool ratchet::HpComponent::Release(void) {
    super::Release();
    if (_ui_remove) {
        if (auto canvas = super::_ui_canvas.lock()) {
            canvas->RemoveElement("NanotechMenu");
        } // if
    } // if
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::HpComponent::Clone(void) {
    return std::make_shared<ratchet::HpComponent>(*this);
}

void ratchet::HpComponent::Heal(int value) {
    _hp += value;
    if (_hp > _hp_max) {
        _hp = _hp_max;
    } // if
    _observable.Notify(_hp);
}

void ratchet::HpComponent::Damage(int value) {
    _hp -= value;
    if (_hp <= 0) {
        _hp = 0;
    } // if
    _observable.Notify(_hp);
}