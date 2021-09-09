#include "HelpDesk.h"

#include "../../UI/HelpDeskMenu.h"


ratchet::game::gamesystem::HelpDesk::HelpDesk() :
    _info(),
    _prev_info(),
    _subject(),
    _resource(),
    _ui_canvas(),
    _completed(false) {
}

ratchet::game::gamesystem::HelpDesk::~HelpDesk() {
}

void ratchet::game::gamesystem::HelpDesk::OnNotify(const ratchet::game::gamesystem::GameQuest& quest) {
    if (_completed) {
        return;
    } // if
    auto info = Info();
    if (quest.GetType() == ratchet::game::gamesystem::GameQuest::Type::EnemyDestroy) {
        info.text = "敵をすべて倒せ！";
        _info.text = info.text;
    } // if
    else if (quest.GetType() == ratchet::game::gamesystem::GameQuest::Type::GoHome) {
        if (quest.GetType() != ratchet::game::gamesystem::GameQuest::Type::ToFront) {
            info.text = "船に乗ってゲームクリア！";
            _info.text = info.text;
            _completed = true;
        } // if
    } // else if
    else if (quest.GetType() == ratchet::game::gamesystem::GameQuest::Type::ToFront) {
        if (_info.text != "船に乗ってゲームクリア！") {
            info.text = "中央の広場に向かえ！";
            _info.text = info.text;
        } // if
    } // else if
    else if (quest.GetType() == ratchet::game::gamesystem::GameQuest::Type::ShopAccessStart) {
        _prev_info.text = _info.text;
        info.text = "Shiftキー/Yボタンでショップにアクセス";
    } // else if
    else if (quest.GetType() == ratchet::game::gamesystem::GameQuest::Type::ShopAccessEnd) {
        info.text = _prev_info.text;
    } // else if
    _subject.Notify(info);
}

void ratchet::game::gamesystem::HelpDesk::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::game::gamesystem::HelpDesk::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool ratchet::game::gamesystem::HelpDesk::Initialize(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    auto menu = std::make_shared< ratchet::ui::HelpDeskMenu>("HelpDeskMenu");
    _subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    _completed = false;
    return true;
}

bool ratchet::game::gamesystem::HelpDesk::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    return true;
}

void ratchet::game::gamesystem::HelpDesk::Show(void) {
    auto info = Info();
    info.show = true;
    _subject.Notify(info);
}