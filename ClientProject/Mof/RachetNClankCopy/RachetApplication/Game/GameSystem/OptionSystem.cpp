#include "OptionSystem.h"

#include "../../UI/OptionSystemMenu.h"


my::OptionSystem::OptionSystem() :
    super(),
    _infomation(),
    _info_subject(),
    _item(),
    _item_index(),
    _title_menu_subject() {
    _infomation.items = &_item;
}

my::OptionSystem::~OptionSystem() {
}
void my::OptionSystem::OnNotify(bool flag) {
    super::OnNotify(flag);
    _title_menu_subject.Notify(false);
    _infomation.enter = true;
    _info_subject.Notify(_infomation);
    _infomation.enter = false;
}

my::Observable<const my::OptionSystem::Info&>* my::OptionSystem::GetInfoSubject(void) {
    return &this->_info_subject;
}

my::Observable<const my::scene::SceneMessage&>* my::OptionSystem::GetSceneMessageSubject(void) {
    return &this->_scene_message_subject;
}
my::Observable<bool>* my::OptionSystem::GetTitleMenuSubject(void) {
    return &this->_title_menu_subject;
}

void my::OptionSystem::AddItem(const std::shared_ptr<ElemType>& elem) {
    _item.push_back(elem);
    _info_subject.Notify(_infomation);
}

bool my::OptionSystem::Initialize(void) {
    if (auto canvas = super::GetUICanvas()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    auto menu = std::make_shared< my::OptionSystemMenu>("OptionSystemMenu");
    _info_subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(super::GetResource());
    menu->SetPosition(Mof::CVector2(400.0f, 400.0f));
    if (auto resource = super::GetResource()) {
        auto tex = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/ui/black.png");
        menu->SetTexture(tex);
    } // if


    if (auto canvas = super::GetUICanvas()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool my::OptionSystem::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_UP)) {
        _item_index++;
        if (_item_index > _item.size() - 1) {
            _item_index = _item.size() - 1;
        } // if
        _infomation.index = _item_index;
        _info_subject.Notify(_infomation);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_DOWN)) {
        _item_index--;
        if (_item_index < 0) {
            _item_index = 0;
        } // if
        _infomation.index = _item_index;
        _info_subject.Notify(_infomation);
    } // else if

    if (!_item.empty()) {
        if (::g_pInput->IsKeyPush(MOFKEY_Z) || ::g_pInput->IsKeyPush(MOFKEY_SPACE) || ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
            _execute_list.push_back(_item.at(_item_index));
        } // if
    } // if
    return true;
}
bool my::OptionSystem::Update(float delta_time) {
    this->Input();
    if (!_execute_list.empty()) {
        for (auto ptr : _execute_list) {
            if (ptr->Execute()) {
            } // if
        } // for
        _execute_list.clear();
        return false;
    } // if
    /*
    std::vector<std::shared_ptr<ElemType>> remove_list;
    for (auto ptr : _execute_list) {
        if (ptr->Execute()) {
            remove_list.push_back(ptr);
        } // if
    } // for
    
    for (auto ptr : remove_list) {
        ut::EraseRemove(_execute_list, ptr);
    } // for
    remove_list.clear();
    */
    return true;
}

bool my::OptionSystem::Release(void) {
    _item.clear();
    _info_subject.Clear();
    _title_menu_subject.Clear();
    if (auto canvas = super::GetUICanvas()) {
        canvas->RemoveElement("OptionSystemMenu");
    } // if
    return true;
}

my::OptionSystemItem::OptionSystemItem() {
}

my::OptionSystemItem::OptionSystemItem(std::function<bool(void)> func) :
    _on_enter(func) {
}

my::OptionSystemItem::~OptionSystemItem() {
}

void my::OptionSystemItem::SetText(const char* text) {
    this->_text = text;
}

std::string my::OptionSystemItem::GetText(void) const {
    return this->_text;
}

bool my::OptionSystemItem::Execute(void) {
    return _on_enter();
}