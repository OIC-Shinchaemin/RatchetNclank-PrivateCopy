#include "UserActionHelper.h"

#include "../../../UI/UserActionHelperMenu.h"


ratchet::game::gamesystem::user::UserActionHelper::UserActionHelper() :
    super(),
    _ui_creator() {
}

ratchet::game::gamesystem::user::UserActionHelper::~UserActionHelper() {
}

void ratchet::game::gamesystem::user::UserActionHelper::OnNotify(const actor::character::CharacterTalkableMessage& message) {
    if (message.can) {
        _ui.lock()->SetText("Vキーで話しかけられます");
    } // if
    else {
        //_ui.lock()->SetText("Nキーで攻撃できます");
        _ui.lock()->SetText("");
    } // else
}

bool ratchet::game::gamesystem::user::UserActionHelper::RegisterUI(void) {
    _ASSERT_EXPR(super::GetUICanvas(), L"無効なポインタを保持しています");
    _ASSERT_EXPR(super::GetResource(), L"無効なポインタを保持しています");
    _ui_creator = std::make_unique<ratchet::ui::UICreator<ratchet::ui::UserActionHelperMenu> > (typeid(decltype(_ui_creator)).name());
    _ui = _ui_creator->Create(super::GetUICanvas(), super::GetResource());
    _ui.lock()->Notify(_ui.lock(), "Enable");
    return true;
}

bool ratchet::game::gamesystem::user::UserActionHelper::DisposeUI(void) {
    _ui_creator.reset();
    return true;
}