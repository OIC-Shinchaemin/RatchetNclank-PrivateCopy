#include "OptionSystemMenu.h"


std::shared_ptr<Mof::CTexture> ratchet::ui::OptionSystemMenu::GetTexture(const std::string& type) {
    auto resouce = _resource.lock();
    std::string path = "";
    if (type == "操作説明") {
        path = "../Resource/texture/ui/text/how_to_play.png";
    } // if
    else if (type == "ゲームスタート") {
        path = "../Resource/texture/ui/text/game_start.png";
    } // else if
    else if (type == "終了") {
        path = "../Resource/texture/ui/text/exit_game.png";
    } // else if
    return resouce->Get<std::shared_ptr<Mof::CTexture>>(path.c_str());
}

ratchet::ui::OptionSystemMenu::OptionSystemMenu(const char* name) :
    super(name),
    _infomation(),
    _resource(),
    _ui_canvas(),
    _font(),
    _element_margin_y(4.0f),
    _enable(false) {
    bool loaded_font = _font.Create(34, "");
    _ASSERT_EXPR(loaded_font, L"フォントを作成できませんでした");
    this->SetPosition(Mof::CVector2(440.0f, 305.0f));
}

ratchet::ui::OptionSystemMenu::~OptionSystemMenu() {
    _font.Release();
}

void ratchet::ui::OptionSystemMenu::OnNotify(const ratchet::game::gamesystem::OptionSystem::Info& info) {
    _infomation = info;
    if (info.enter) {
        if (!_enable) {
            super::Notify(shared_from_this(), "Enable");
            _enable = true;
        } // if
    } // if

    if (info.items->size() != super::_items.size()) {
        this->AddItem(**(info.items->end() - 1));
    } // if
    else if (info.items->empty()) {
        _items.clear();
    } // else if

    if (info.end) {
        if (_enable) {
            super::Notify(shared_from_this(), "Disable");
            _enable = false;
        } // if
    } // if
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
    elem->SetTexture(this->GetTexture(in.GetText()));

    auto screen_center = Mof::CVector2(ratchet::kWindowWidthF, ratchet::kWindowHeightF) * 0.5f;
    auto half_size = elem->GetSize() * 0.5f;
    auto pos = Mof::CVector2(screen_center.x - half_size.x, super::_position.y);
    elem->SetPosition(pos);
    super::_position.y += elem->GetSize().y + _element_margin_y;

    super::AddElement(elem);
}

bool ratchet::ui::OptionSystemMenu::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::ui::OptionSystemMenu::Update(float delta_time) {
    int index = 0;
    for (auto elem : super::_items) {
        elem->SetColor(def::color_rgba::kGray);
        if (index == _infomation.index) {
            elem->SetColor(def::color_rgba::kWhite);
        } // if
        index++;
    } // for
    return true;
}

bool ratchet::ui::OptionSystemMenu::Render(void) {
    super::Render();
    return true;
}

ratchet::ui::OptionSystemMenuItem::OptionSystemMenuItem(const char* name) :
    super(name),
    _text(),
    _font(),
    _selected(false) {
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

void ratchet::ui::OptionSystemMenuItem::SetSelect(const bool flag) {
    this->_selected = flag;
}

Mof::CVector2 ratchet::ui::OptionSystemMenuItem::GetSize(void) const {
    auto tex = this->GetTexture();
    return Mof::CVector2(tex->GetWidth(), tex->GetHeight());
}

std::shared_ptr<Mof::CTexture> ratchet::ui::OptionSystemMenuItem::GetTexture(void) const {
    if (auto tex = super::_texture.lock()) {
        return tex;
    } // if
    return nullptr;
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


    if (auto tex = super::_texture.lock()) {
        //tex->Render(pos.x, pos.y, color);
        auto s = super::GetScale();
        tex->RenderScale(pos.x, pos.y, s.x, s.y, color);
    } // if

    if (debug::DebugManager::GetInstance().IsDebugMode()) {
        ::CGraphicsUtilities::RenderString(
            pos.x + 1, pos.y + 1, def::color_rgba_u32::kBlack, _text.c_str());
        ::CGraphicsUtilities::RenderString(
            pos.x, pos.y, color, _text.c_str());
        auto rect = Mof::CRectangle(0.0f, 0.0f, this->GetSize().x, this->GetSize().y);
        rect.Translation(pos);
        ::CGraphicsUtilities::RenderRect(rect, def::color_rgba_u32::kRed);
    } // if
    return true;
}