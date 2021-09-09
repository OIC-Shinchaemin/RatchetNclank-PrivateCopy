#include "OptionSystem.h"

#include "../../UI/OptionSystemMenu.h"
#include "../../Gamepad.h"


ratchet::game::gamesystem::OptionSystem::OptionSystem() :
    super(),
    _infomation(),
    _info_subject(),
    _item(),
    _item_index(),
    _title_menu_subject() {
    _infomation.items = &_item;
}

ratchet::game::gamesystem::OptionSystem::~OptionSystem() {
}

void ratchet::game::gamesystem::OptionSystem::OnNotify(bool flag) {
    super::OnNotify(flag);
    _item_index = 0;
    _title_menu_subject.Notify(false);
    _infomation.enter = true;
    _info_subject.Notify(_infomation);
    _infomation.enter = false;
}

base::core::Observable<const ratchet::game::gamesystem::OptionSystem::Info&>* ratchet::game::gamesystem::OptionSystem::GetInfoSubject(void) {
    return &this->_info_subject;
}

base::core::Observable<const ratchet::scene::SceneMessage&>* ratchet::game::gamesystem::OptionSystem::GetSceneMessageSubject(void) {
    return &this->_scene_message_subject;
}
base::core::Observable<bool>* ratchet::game::gamesystem::OptionSystem::GetTitleMenuSubject(void) {
    return &this->_title_menu_subject;
}

void ratchet::game::gamesystem::OptionSystem::AddItem(const std::shared_ptr<ElemType>& elem) {
    _item.push_back(elem);
    _info_subject.Notify(_infomation);
}

bool ratchet::game::gamesystem::OptionSystem::Initialize(void) {
    _infomation = Info();
    _infomation.items = &_item;

    if (auto canvas = super::GetUICanvas()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    auto menu = std::make_shared< ratchet::ui::OptionSystemMenu>("OptionSystemMenu");
    _info_subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(super::GetResource());
    if (auto resource = super::GetResource()) {
        auto tex = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/ui/black.png");
        menu->SetTexture(tex);
    } // if
    if (auto canvas = super::GetUICanvas()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool ratchet::game::gamesystem::OptionSystem::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_UP) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_DP_UP)) {
        _item_index--;
        if (_item_index < 0) {
            _item_index = 0;
        } // if
        _infomation.index = _item_index;
        _info_subject.Notify(_infomation);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_DOWN) ||
             ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_DP_DOWN)) {
        _item_index++;
        if (_item_index > _item.size() - 1) {
            _item_index = _item.size() - 1;
        } // if
        _infomation.index = _item_index;
        _info_subject.Notify(_infomation);
    } // else if
    if (!_item.empty()) {
        if (::g_pInput->IsKeyPush(MOFKEY_Z) || ::g_pInput->IsKeyPush(MOFKEY_SPACE) || ::g_pInput->IsKeyPush(MOFKEY_RETURN) ||
            ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START)) {
            _execute_list.push_back(_item.at(_item_index));
        } // if
    } // if
    return true;
}
bool ratchet::game::gamesystem::OptionSystem::Update(float delta_time) {
    this->Input();
    if (!_execute_list.empty()) {
        for (auto ptr : _execute_list) {
            if (ptr->Execute()) {
            } // if
            this->Hide();
        } // for
        _infomation.Reset();
        _info_subject.Notify(_infomation);
        _execute_list.clear();
        return false;
    } // if
    return true;
}

bool ratchet::game::gamesystem::OptionSystem::Release(void) {
    _item.clear();
    _info_subject.Clear();
    _title_menu_subject.Clear();
    if (auto canvas = super::GetUICanvas()) {
        canvas->RemoveElement("OptionSystemMenu");
    } // if
    return true;
}

void ratchet::game::gamesystem::OptionSystem::Hide(void) {
    _infomation.end = true;
    _info_subject.Notify(_infomation);
}

ratchet::game::gamesystem::OptionSystemItem::OptionSystemItem() {
}

ratchet::game::gamesystem::OptionSystemItem::OptionSystemItem(std::function<bool(void)> func) :
    _on_enter(func) {
}

ratchet::game::gamesystem::OptionSystemItem::~OptionSystemItem() {
}

void ratchet::game::gamesystem::OptionSystemItem::SetText(const char* text) {
    this->_text = text;
}

std::string ratchet::game::gamesystem::OptionSystemItem::GetText(void) const {
    return this->_text;
}

bool ratchet::game::gamesystem::OptionSystemItem::Execute(void) {
    return _on_enter();
}