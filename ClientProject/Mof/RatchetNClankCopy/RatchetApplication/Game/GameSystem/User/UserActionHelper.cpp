#include "UserActionHelper.h"

#include "../../../UI/UserActionHelperMenu.h"


ratchet::game::gamesystem::user::UserActionHelper::UserActionHelper() :
    super(),
    _ui_creator(typeid(decltype(_ui_creator)).name()) {
}

ratchet::game::gamesystem::user::UserActionHelper::~UserActionHelper() {
}

void ratchet::game::gamesystem::user::UserActionHelper::OnNotify(const actor::character::CharacterTalkableMessage& message) {
    if (message.can) {
        _ui.lock()->SetText("asfafas");
    } // if
    else {
        _ui.lock()->SetText("あいうえお");
    } // else
}

//void ratchet::game::gamesystem::user::UserActionHelper::OnNotify(actor::character::CharacterTalkableMessageListener::Message message) {
//}

bool ratchet::game::gamesystem::user::UserActionHelper::RegisterUI(void) {
    _ASSERT_EXPR(super::GetUICanvas(), L"無効なポインタを保持しています");
    _ASSERT_EXPR(super::GetResource(), L"無効なポインタを保持しています");

    _ui = _ui_creator.Create(super::GetUICanvas(), super::GetResource());
    //super::Notify(shared_from_this(), "Enable");
    _ui.lock()->Notify(_ui.lock(), "Enable");
    //_info_subject.AddObserver(_ui.lock());

    /*
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("GameMoneyMenu");
    } // if
    auto menu = std::make_shared< ratchet::ui::UserActionHelperMenu>("UserActionHelperMenu");
    //_subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    menu->Initialize();
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    */
    return true;
}