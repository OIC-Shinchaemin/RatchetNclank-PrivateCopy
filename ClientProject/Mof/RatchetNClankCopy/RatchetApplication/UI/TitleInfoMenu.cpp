#include "TitleInfoMenu.h"


ratchet::ui::TitleInfoMenu::TitleInfoMenu(const char* name) :
    super(name),
    _show(true),
    _resource(),
    _ui_canvas(),
    _show_timer(),
    _start(false),
    _blinking_on_timer(),
    _blinking_off_timer(),
    _blinking_on(false),
    _texture_path("../Resource/texture/ui/text/press_button_text.png") {

    int w = ::g_pFramework->GetWindow()->GetWidth();
    if (w == ratchet::kWindowWidth) {
        super::_position = Mof::CVector2(260.0f, 920.0f);
    } // if
    else {
        super::_position = Mof::CVector2(260.0f, 720.0f);
    } // else


    _blinking_on_timer.Initialize(2.0f, true);
    _blinking_off_timer.Initialize(0.5f, true);
}

ratchet::ui::TitleInfoMenu::~TitleInfoMenu() {
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

    if (_blinking_on && _blinking_on_timer.Tick(delta_time)) {
        _blinking_on = false;
    } // if
    else if (!_blinking_on && _blinking_off_timer.Tick(delta_time)) {
        _blinking_on = true;
    } // else if
    return true;
}

bool ratchet::ui::TitleInfoMenu::Render(void) {
    if (!_show) {
        return false;
    } // if

    if (_start) {
        if (_blinking_on) {
            super::Render();
            if (auto resource = _resource.lock()) {
                auto center = Mof::CVector2(::g_pFramework->GetWindow()->GetWidth() * 0.5f, ::g_pFramework->GetWindow()->GetHeight() * 0.5f);
                float scale = 0.5f;
                auto tex = resource->Get<std::shared_ptr< Mof::CTexture>>(_texture_path.c_str());
                auto size = Mof::CVector2(tex->GetWidth(), tex->GetHeight()) * scale;
                auto half_size = size * 0.5f;
                _position = Mof::CVector2(center.x - half_size.x, _position.y);
                tex->RenderScale(_position.x, _position.y, scale, Mof::TextureAlignment::TEXALIGN_BOTTOMLEFT);
            } // if
        } // if
    } // if
    return true;
}