#include "OptionSystemMenu.h"


ratchet::ui::OptionSystemMenu::OptionSystemMenu(const char* name) :
    super(name),
    _infomation(),
    _resource(),
    _ui_canvas(),
    _font() {
    bool loaded_font = _font.Create(34, "");
    _ASSERT_EXPR(loaded_font, L"フォントを作成できませんでした");
    this->SetPosition(Mof::CVector2(440.0f, 420.0f));
}

ratchet::ui::OptionSystemMenu::~OptionSystemMenu() {
    _font.Release();
}

void ratchet::ui::OptionSystemMenu::OnNotify(const ratchet::game::gamesystem::OptionSystem::Info& info) {
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

void ratchet::ui::OptionSystemMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::ui::OptionSystemMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void ratchet::ui::OptionSystemMenu::AddItem(const ratchet::game::gamesystem::OptionSystemItem& in) {
    auto elem = std::make_shared<ratchet::ui::OptionSystemMenuItem>(in.GetText().c_str());
    elem->SetFont(&_font);
    elem->SetText(in.GetText());

    auto screen_center = Mof::CVector2(def::kWindowWidthF, def::kWindowHeightF) * 0.5f;
    auto half_size = elem->GetSize() * 0.5f;
    auto pos = Mof::CVector2(screen_center.x - half_size.x, super::_position.y);
    elem->SetPosition(pos);
    super::_position.y += 40.0f;

    super::AddElement(elem);
}

bool ratchet::ui::OptionSystemMenu::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::ui::OptionSystemMenu::Update(float delta_time) {
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

bool ratchet::ui::OptionSystemMenu::Render(void) {
    super::Render();
    return true;
}

ratchet::ui::OptionSystemMenuItem::OptionSystemMenuItem(const char* name) :
    super(name),
    _text(),
    _font() {
}

ratchet::ui::OptionSystemMenuItem::~OptionSystemMenuItem() {
    _font = nullptr;
}

void ratchet::ui::OptionSystemMenuItem::SetText(const std::string& text) {
    this->_text = text;
}

void ratchet::ui::OptionSystemMenuItem::SetFont(Mof::CFont* ptr) {
    this->_font = ptr;
}

Mof::CVector2 ratchet::ui::OptionSystemMenuItem::GetSize(void) const {
    return Mof::CVector2(ratchet::kTextWidth * _text.size(), ratchet::kTextWidth);
}

bool ratchet::ui::OptionSystemMenuItem::Input(void) {
    return false;
}

bool ratchet::ui::OptionSystemMenuItem::Update(float delta_time) {
    return true;
}

bool ratchet::ui::OptionSystemMenuItem::Render(void) {
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