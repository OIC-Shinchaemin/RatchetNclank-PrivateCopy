#include "GamePauseSystemMenu.h"


my::GamePauseSystemMenu::GamePauseSystemMenu(const char* name) :
    super(name) {

    super::_position = Mof::CVector2(500.0f, 400.0f);
}

void my::GamePauseSystemMenu::OnNotify(const my::GamePauseSystem::Info& info) {
    this->_infomation = info;
    if (info.enter) {
        super::Notify(shared_from_this(), "Enable");
    } // if
    else if (info.push_item) {
        this->AddItem(**(info.items->end() - 1));
    } // else if
}

void my::GamePauseSystemMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::GamePauseSystemMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void my::GamePauseSystemMenu::AddItem(const my::GamePauseSystemItem& in) {
    auto elem = std::make_shared<ElemType>(in.GetText().c_str());
    elem->SetText(in.GetText());
    elem->SetPosition(super::_position);
    super::_position.y -= 20.0f;

    super::AddElement(elem);
}

bool my::GamePauseSystemMenu::Initialize(void) {
    return true;
}

bool my::GamePauseSystemMenu::Update(float delta_time) {
    if (_infomation.exit) {
        return false;
    } // if

    int index = 0;
    for (auto elem : super::_items) {
        elem->SetColor(def::color_rgba::kGreen);
        if (index == _infomation.index) {
            elem->SetColor(def::color_rgba::kRed);
        } // if
        index++;
    } // for

    return true;
}

bool my::GamePauseSystemMenu::Render(void) {
    super::Render();
    return true;
}

my::GamePauseSystemMenuItem::GamePauseSystemMenuItem(const char* name) :
    super(name),
    _text() {
}

my::GamePauseSystemMenuItem::~GamePauseSystemMenuItem() {
}

void my::GamePauseSystemMenuItem::SetText(const std::string& text) {
    this->_text = text;
}

bool my::GamePauseSystemMenuItem::Input(void) {
    return true;
}

bool my::GamePauseSystemMenuItem::Update(float delta_time) {
    return true;
}

bool my::GamePauseSystemMenuItem::Render(void) {
    auto pos = super::_position;
    auto color = super::_color.ToU32Color();
    ::CGraphicsUtilities::RenderString(
        pos.x, pos.y, color, _text.c_str());
    return true;
}
