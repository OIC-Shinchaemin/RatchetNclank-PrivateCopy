#include "OptionSystemMenu.h"


my::OptionSystemMenu::OptionSystemMenu(const char* name) :
    super(name),
    _infomation(),
    _resource(),
    _ui_canvas() {
}

void my::OptionSystemMenu::OnNotify(const my::OptionSystem::Info& info) {
    _infomation = info;
    if (info.enter) {
        super::Notify(shared_from_this(), "Enable");
    } // if

    if (info.items->size() != super::_items.size()) {
        this->AddItem(**(info.items->end() - 1));
    } // if
}

void my::OptionSystemMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::OptionSystemMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void my::OptionSystemMenu::AddItem(const my::OptionSystemItem& in) {
    auto elem = std::make_shared<my::OptionSystemMenuItem>(in.GetText().c_str());
    elem->SetText(in.GetText());
    elem->SetPosition(super::_position);
    super::_position.y += 20.0f;

    super::AddElement(elem);
}

bool my::OptionSystemMenu::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::OptionSystemMenu::Update(float delta_time) {
    int index = 0;
    for (auto elem : super::_items) {
        elem->SetColor(def::color_rgba::kGreen);
        if (index == _infomation.index) {
            elem->SetColor(def::color_rgba::kRed);
        } // if
        index++;
    } // for

    std::cout << "_infomation.index = " << _infomation.index << "\n";
    return true;
}

bool my::OptionSystemMenu::Render(void) {
    super::Render();
    return true;
}

my::OptionSystemMenuItem::OptionSystemMenuItem(const char* name) :
    super(name),
    _text() {
}

my::OptionSystemMenuItem::~OptionSystemMenuItem() {
}

void my::OptionSystemMenuItem::SetText(const std::string& text) {
    this->_text = text;
}

bool my::OptionSystemMenuItem::Input(void) {
    return false;
}

bool my::OptionSystemMenuItem::Update(float delta_time) {
    //super::Update(delta_time);
    return true;
}

bool my::OptionSystemMenuItem::Render(void) {
    auto pos = super::_position;
    auto color = super::_color.ToU32Color();
    ::CGraphicsUtilities::RenderString(
        pos.x, pos.y, color, _text.c_str());
    return true;
}