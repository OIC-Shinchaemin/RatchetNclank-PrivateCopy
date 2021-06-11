#include "LockOnCursorMenu.h"


rachet::LockOnCursorMenu::LockOnCursorMenu(const char* name) :
    super(name),
    _position(),
    _resource_manager() {
}

void rachet::LockOnCursorMenu::OnNotify(std::optional<Mof::CVector3> position) {
    super::Notify(shared_from_this(), "Enable");

    _position = position;
}

void rachet::LockOnCursorMenu::SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr) {
    _resource_manager = ptr;
}

bool rachet::LockOnCursorMenu::Render(void) {
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