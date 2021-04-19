#include "LockOnCursorMenu.h"


my::LockOnCursorMenu::LockOnCursorMenu(const char* name) :
    super(name),
    _position(),
    _ui_canvas(){
}

void my::LockOnCursorMenu::OnNotify(std::optional<Mof::CVector3> position) {
    _position = position;
}

void my::LockOnCursorMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    _ui_canvas = ptr;
}

bool my::LockOnCursorMenu::Render(void) {
    if (_position.has_value()) {
        ::CGraphicsUtilities::RenderString(600.0f, 200.0f, "Lock on ");
    } // if
    return true;
}