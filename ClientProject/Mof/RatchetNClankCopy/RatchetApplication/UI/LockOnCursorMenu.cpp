#include "LockOnCursorMenu.h"


ratchet::LockOnCursorMenu::LockOnCursorMenu(const char* name) :
    super(name),
    _position(),
    _resource_manager() {
}

void ratchet::LockOnCursorMenu::OnNotify(std::optional<Mof::CVector3> position) {
    super::Notify(shared_from_this(), "Enable");

    _position = position;
}

void ratchet::LockOnCursorMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    _resource_manager = ptr;
}

bool ratchet::LockOnCursorMenu::Render(void) {
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