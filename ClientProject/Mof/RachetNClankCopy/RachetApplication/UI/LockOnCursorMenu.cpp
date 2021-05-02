#include "LockOnCursorMenu.h"


my::LockOnCursorMenu::LockOnCursorMenu(const char* name) :
    super(name),
    _position(),
    _resource_manager() {
}

void my::LockOnCursorMenu::OnNotify(std::optional<Mof::CVector3> position) {
    _position = position;
}

void my::LockOnCursorMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    _resource_manager = ptr;
}

bool my::LockOnCursorMenu::Render(void) {
    if (_position.has_value()) {
        if (auto r = _resource_manager.lock()) {
            auto tex = r->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/lock_on_cursor/cursor.png");

            auto trans = Mof::CMatrix44();
            trans.Translation(_position.value());
            if (tex) {
                tex->Render(::CGraphicsUtilities::GetCamera()->GetBillBoardMatrix() * trans);
            } // if
        } // if
    } // if
    return true;
}