#include "GamePauseSystemMenu.h"


ratchet::ui::GamePauseSystemMenu::GamePauseSystemMenu(const char* name) :
    super(name) {
    super::_position = Mof::CVector2(500.0f, 400.0f);
}

void ratchet::ui::GamePauseSystemMenu::OnNotify(const ratchet::game::gamesystem::GamePauseSystem::Info& info) {
    this->_infomation = info;
    if (info.enable) {
        super::_position = Mof::CVector2(500.0f, 400.0f);
        super::Notify(shared_from_this(), "Enable");
    } // if
    else if (info.items && info.items->size() != super::_items.size()) {
        this->_items.clear();
        for (auto item : *info.items) {
            this->AddItem(*item);
        } // for
    } // else if
    else if (info.items->empty()) {
        this->_items.clear();
    } // else if
}

void ratchet::ui::GamePauseSystemMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::ui::GamePauseSystemMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

std::shared_ptr<Mof::CTexture> ratchet::ui::GamePauseSystemMenu::GetTexture(const std::string& type) {
    auto resouce = _resource.lock();
    std::string path = "";
    if (type == "操作説明") {
        path = "../Resource/texture/ui/text/how_to_play.png";
    } // if
    else if (type == "リトライ") {
        path = "../Resource/texture/ui/text/how_to_play.png";
    } // else if
    else if (type == "もどる") {
        path = "../Resource/texture/ui/text/back_to_game.png";
    } // else if
    else if (type == "ゲームに戻る") {
        path = "../Resource/texture/ui/text/back_to_game.png";
    } // else if
    else if (type == "タイトルに戻る") {
        path = "../Resource/texture/ui/text/go_to_title.png";
    } // else if

    return resouce->Get<std::shared_ptr<Mof::CTexture>>(path.c_str());
}

void ratchet::ui::GamePauseSystemMenu::AddItem(const ratchet::game::gamesystem::GamePauseSystemItem& in) {
    auto elem = std::make_shared<ElemType>(in.GetText().c_str());
    elem->SetText(in.GetText());
    elem->SetTexture(this->GetTexture(in.GetText()));

    float s = ratchet::kWindowPerXGA * 0.8f;
    elem->SetScale(Mof::CVector2(s, s));

    elem->SetPosition(super::_position);
    
    super::_position.y += elem->GetSize().y * s;
    super::AddElement(elem);
}

bool ratchet::ui::GamePauseSystemMenu::Initialize(void) {
    return true;
}

bool ratchet::ui::GamePauseSystemMenu::Update(float delta_time) {
    if (!_infomation.enable) {
        return false;
    } // if

    int index = 0;
    for (auto elem : super::_items) {
        elem->SetColor(def::color_rgba::kGray);
        if (_infomation.index.has_value() && index == _infomation.index) {
            elem->SetColor(def::color_rgba::kWhite);
        } // if
        index++;
    } // for

    return true;
}

bool ratchet::ui::GamePauseSystemMenu::Render(void) {
    super::Render();
    return true;
}

ratchet::ui::GamePauseSystemMenuItem::GamePauseSystemMenuItem(const char* name) :
    super(name),
    _text() {
}

ratchet::ui::GamePauseSystemMenuItem::~GamePauseSystemMenuItem() {
}

void ratchet::ui::GamePauseSystemMenuItem::SetText(const std::string& text) {
    this->_text = text;
}

Mof::CVector2 ratchet::ui::GamePauseSystemMenuItem::GetSize(void) const {
    auto tex = this->GetTexture();
    return Mof::CVector2(tex->GetWidth(), tex->GetHeight());
}

std::shared_ptr<Mof::CTexture> ratchet::ui::GamePauseSystemMenuItem::GetTexture(void) const {
    if (auto tex = super::_texture.lock()) {
        return tex;
    } // if
    return nullptr;
}

bool ratchet::ui::GamePauseSystemMenuItem::Input(void) {
    return true;
}

bool ratchet::ui::GamePauseSystemMenuItem::Update(float delta_time) {
    return true;
}

bool ratchet::ui::GamePauseSystemMenuItem::Render(void) {
    auto pos = super::_position;
    auto color = super::_color.ToU32Color();
    auto s = super::GetScale();

    if (auto tex = super::_texture.lock()) {
        tex->RenderScale(pos.x, pos.y, s.x, s.y, color);
//        tex->Render(pos.x, pos.y, color);
    } // if

    if (debug::DebugManager::GetInstance().IsDebugMode()) {
        ::CGraphicsUtilities::RenderString(
            pos.x, pos.y, color, _text.c_str());

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
