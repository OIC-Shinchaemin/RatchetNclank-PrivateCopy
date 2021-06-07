#include "TitleInfoMenu.h"


my::TitleInfoMenu::TitleInfoMenu(const char* name) :
    super(name),
    _show(true),
    _resource(),
    _ui_canvas() {
}

void my::TitleInfoMenu::OnNotify(bool show) {
    if (show) {
        super::Notify(shared_from_this(), "Enable");
    } // if
    _show = show;
}

void my::TitleInfoMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::TitleInfoMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::TitleInfoMenu::Initialize(void) {
    super::Initialize();
    super::_position = Mof::CVector2(500.0f, 300.0f);
    return true;
}

bool my::TitleInfoMenu::Update(float delta_time) {
    //super::Update(delta_time);
    return true;
}

bool my::TitleInfoMenu::Render(void) {
    if (!_show) {
        return false;
    } // if
    super::Render();
    if (auto resource = _resource.lock()) {
        //auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-アナログテレビフォント");
        auto text = "Please Press   Start Button or \n                    Enter Key !";
        ::CGraphicsUtilities:: RenderString(220.0, 400.0f, def::color_rgba_u32::kGreen, text);
    } // if
    return true;
}