#include "GamePauseSystemMenu.h"


rachet::GamePauseSystemMenu::GamePauseSystemMenu(const char* name) :
    super(name) {

    super::_position = Mof::CVector2(500.0f, 400.0f);
}

void rachet::GamePauseSystemMenu::OnNotify(const rachet::GamePauseSystem::Info& info) {
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

void rachet::GamePauseSystemMenu::SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void rachet::GamePauseSystemMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void rachet::GamePauseSystemMenu::AddItem(const rachet::GamePauseSystemItem& in) {
    auto elem = std::make_shared<ElemType>(in.GetText().c_str());
    elem->SetText(in.GetText());
    elem->SetPosition(super::_position);
    super::_position.y -= 20.0f;

    super::AddElement(elem);
}

bool rachet::GamePauseSystemMenu::Initialize(void) {
    return true;
}

bool rachet::GamePauseSystemMenu::Update(float delta_time) {
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

bool rachet::GamePauseSystemMenu::Render(void) {
    super::Render();
    return true;
}

rachet::GamePauseSystemMenuItem::GamePauseSystemMenuItem(const char* name) :
    super(name),
    _text() {
}

rachet::GamePauseSystemMenuItem::~GamePauseSystemMenuItem() {
}

void rachet::GamePauseSystemMenuItem::SetText(const std::string& text) {
    this->_text = text;
}

bool rachet::GamePauseSystemMenuItem::Input(void) {
    return true;
}

bool rachet::GamePauseSystemMenuItem::Update(float delta_time) {
    return true;
}

bool rachet::GamePauseSystemMenuItem::Render(void) {
    auto pos = super::_position;
    auto color = super::_color.ToU32Color();
    ::CGraphicsUtilities::RenderString(
        pos.x, pos.y, color, _text.c_str());
    return true;
}
