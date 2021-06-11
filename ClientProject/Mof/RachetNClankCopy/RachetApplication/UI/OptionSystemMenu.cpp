#include "OptionSystemMenu.h"


my::OptionSystemMenu::OptionSystemMenu(const char* name) :
    super(name),
    _infomation(),
    _resource(),
    _ui_canvas(),
    _font() {
    bool loaded_font = _font.Create(34, "");
    _ASSERT_EXPR(loaded_font, L"フォントを作成できませんでした");

    this->SetPosition(Mof::CVector2(440.0f, 420.0f));
    
}

my::OptionSystemMenu::~OptionSystemMenu() {
    _font.Release();
}

void my::OptionSystemMenu::OnNotify(const my::OptionSystem::Info& info) {
    _infomation = info;
    if (info.enter) {
        super::Notify(shared_from_this(), "Enable");
    } // if

    if (info.items->size() != super::_items.size()) {
        this->AddItem(**(info.items->end() - 1));
    } // if
    else if (info.items->empty()) {
        _items.clear();
    } // else if
}

void my::OptionSystemMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::OptionSystemMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void my::OptionSystemMenu::AddItem(const my::OptionSystemItem& in) {
    auto elem = std::make_shared<my::OptionSystemMenuItem>(in.GetText().c_str());
    elem->SetFont(&_font);
    elem->SetText(in.GetText());

    auto screen_center = Mof::CVector2(def::kWindowWidthF, def::kWindowHeightF) * 0.5f;
    auto half_size = elem->GetSize() * 0.5f;
    auto pos = Mof::CVector2(screen_center.x - half_size.x, super::_position.y);
    elem->SetPosition(pos);
    super::_position.y += 40.0f;

    super::AddElement(elem);
}

bool my::OptionSystemMenu::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::OptionSystemMenu::Update(float delta_time) {
    int index = 0;


    for (auto elem : super::_items) {
        elem->SetColor(def::color_rgba::kWhite);
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
    _text(),
    _font() {
}

my::OptionSystemMenuItem::~OptionSystemMenuItem() {
    _font = nullptr;
}

void my::OptionSystemMenuItem::SetText(const std::string& text) {
    this->_text = text;
}

void my::OptionSystemMenuItem::SetFont(Mof::CFont* ptr) {
    this->_font = ptr;
}

Mof::CVector2 my::OptionSystemMenuItem::GetSize(void) const {
    return Mof::CVector2(my::kTextWidth * _text.size(), my::kTextWidth);
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
        pos.x + 1, pos.y + 1, def::color_rgba_u32::kBlack, _text.c_str());
    ::CGraphicsUtilities::RenderString(
        pos.x, pos.y, color, _text.c_str());


#ifdef _DEBUG
    auto rect = Mof::CRectangle(0.0f, 0.0f, this->GetSize().x, this->GetSize().y);
    rect.Translation(pos);
    ::CGraphicsUtilities::RenderRect(rect, def::color_rgba_u32::kRed);
#endif // _DEBUG

    return true;
}