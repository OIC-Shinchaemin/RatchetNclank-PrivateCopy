#include "TitleInfoMenu.h"


ratchet::ui::TitleInfoMenu::TitleInfoMenu(const char* name) :
    super(name),
    _show(true),
    _resource(),
    _ui_canvas(),
    _font(),
    _show_timer(),
    _start(false) {
    super::_position = Mof::CVector2(260.0f, 650.0f);
    bool loaded_font = _font.Create(30, "");
    _ASSERT_EXPR(loaded_font, L"フォントを作成できませんでした");
}

ratchet::ui::TitleInfoMenu::~TitleInfoMenu() {
    _font.Release();
}

void ratchet::ui::TitleInfoMenu::OnNotify(bool show) {
    if (show) {
        super::Notify(shared_from_this(), "Enable");
        _start = false;
        _show_timer.Initialize(3.0f, false);
    } // if
    _show = show;
}

void ratchet::ui::TitleInfoMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::ui::TitleInfoMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool ratchet::ui::TitleInfoMenu::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::ui::TitleInfoMenu::Update(float delta_time) {
    if (_show_timer.Tick(delta_time)) {
        _start = true;
    } // if
    return true;
}

bool ratchet::ui::TitleInfoMenu::Render(void) {
    if (!_show) {
        return false;
    } // if

    if (_start) {
        super::Render();
        if (auto resource = _resource.lock()) {
            auto pos = super::_position;
            auto text = "Press Start Button or Enter Key !";
            _font.RenderString(pos.x + 1, pos.y + 1, def::color_rgba_u32::kBlack, text);
            _font.RenderString(pos.x, pos.y, def::color_rgba_u32::kWhite, text);
        } // if
    } // if
    return true;
}