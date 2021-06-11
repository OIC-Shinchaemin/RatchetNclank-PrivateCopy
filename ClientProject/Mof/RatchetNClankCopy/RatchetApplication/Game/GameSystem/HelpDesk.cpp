#include "HelpDesk.h"

#include "../../UI/HelpDeskMenu.h"


ratchet::HelpDesk::HelpDesk() :
    _info(),
    _prev_info(),
    _subject(),
    _resource(),
    _ui_canvas() {
}

ratchet::HelpDesk::~HelpDesk() {
}

void ratchet::HelpDesk::OnNotify(const ratchet::GameQuest& quest) {
    auto info = Info();
    if (quest.GetType() == ratchet::GameQuest::Type::EnemyDestroy) {
        info.text = "敵をすべて倒せ！";
        _info.text = info.text;
    } // if
    else if (quest.GetType() == ratchet::GameQuest::Type::GoHome) {
        info.text = "船に乗ってゲームクリア！";
        _info.text = info.text;
    } // else if
    else if (quest.GetType() == ratchet::GameQuest::Type::ToFront) {
        if (_info.text != "船に乗ってゲームクリア！") {
            info.text = "前に進め";
            _info.text = info.text;
        } // if
    } // else if
    else if (quest.GetType() == ratchet::GameQuest::Type::ShopAccessStart) {
        _prev_info.text = _info.text;
        info.text = "Shiftキー/Yボタンでショップにアクセス";
    } // else if
    else if (quest.GetType() == ratchet::GameQuest::Type::ShopAccessEnd) {
        info.text = _prev_info.text;
    } // else if
    _subject.Notify(info);
}

void ratchet::HelpDesk::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::HelpDesk::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool ratchet::HelpDesk::Initialize(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    auto menu = std::make_shared< ratchet::HelpDeskMenu>("HelpDeskMenu");
    _subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool ratchet::HelpDesk::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    return true;
}