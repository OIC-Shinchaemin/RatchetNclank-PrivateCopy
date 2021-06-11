#include "GamePauseSystemMenu.h"


ratchet::GamePauseSystemMenu::GamePauseSystemMenu(const char* name) :
    super(name) {

    super::_position = Mof::CVector2(500.0f, 400.0f);
}

void ratchet::GamePauseSystemMenu::OnNotify(const ratchet::GamePauseSystem::Info& info) {
    this->_infomation = info;
    if (info.enable) {
        super::_position = Mof::CVector2(500.0f, 400.0f);
        super::Notify(shared_from_this(), "Enable");
    } // if
    /*
    else if (info.push_item) {
        this->AddItem(**(info.items->end() - 1));
    } // else if
    */
    
    else if (info.items && info.items->size() != super::_items.size()) {
        this->_items.clear();
        for (auto item : *info.items) {
            this->AddItem(*item);
        } // for
        //this->AddItem(**(info.items->end() - 1));
    } // else if

    
    else if (info.items->empty()) {
        this->_items.clear();
    } // else if


}

void ratchet::GamePauseSystemMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::GamePauseSystemMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void ratchet::GamePauseSystemMenu::AddItem(const ratchet::GamePauseSystemItem& in) {
    auto elem = std::make_shared<ElemType>(in.GetText().c_str());
    elem->SetText(in.GetText());
    elem->SetPosition(super::_position);
    super::_position.y -= 20.0f;

    super::AddElement(elem);
}

bool ratchet::GamePauseSystemMenu::Initialize(void) {
    return true;
}

bool ratchet::GamePauseSystemMenu::Update(float delta_time) {
    if (!_infomation.enable) {
        return false;
    } // if

    int index = 0;
    for (auto elem : super::_items) {
        elem->SetColor(def::color_rgba::kGreen);
        if (_infomation.index.has_value() && index == _infomation.index) {
            elem->SetColor(def::color_rgba::kRed);
        } // if
        index++;
    } // for

    return true;
}

bool ratchet::GamePauseSystemMenu::Render(void) {
    super::Render();
    return true;
}

ratchet::GamePauseSystemMenuItem::GamePauseSystemMenuItem(const char* name) :
    super(name),
    _text() {
}

ratchet::GamePauseSystemMenuItem::~GamePauseSystemMenuItem() {
}

void ratchet::GamePauseSystemMenuItem::SetText(const std::string& text) {
    this->_text = text;
}

bool ratchet::GamePauseSystemMenuItem::Input(void) {
    return true;
}

bool ratchet::GamePauseSystemMenuItem::Update(float delta_time) {
    return true;
}

bool ratchet::GamePauseSystemMenuItem::Render(void) {
    auto pos = super::_position;
    auto color = super::_color.ToU32Color();
    ::CGraphicsUtilities::RenderString(
        pos.x, pos.y, color, _text.c_str());
    return true;
}
