#include "HelpDesk.h"

#include "../../UI/HelpDeskMenu.h"


my::HelpDesk::HelpDesk() :
    _info(),
    _prev_info(),
    _subject(),
    _resource(),
    _ui_canvas() {
}

my::HelpDesk::~HelpDesk() {
}

void my::HelpDesk::OnNotify(const my::GameQuest& quest) {
    auto info = Info();
    if (quest.GetType() == my::GameQuest::Type::EnemyDestroy) {
        info.text = "�G�����ׂē|���I";
        _info.text = info.text;
    } // if
    else if (quest.GetType() == my::GameQuest::Type::GoHome) {
        info.text = "�D�ɏ���ăQ�[���N���A�I";
        _info.text = info.text;
    } // else if
    else if (quest.GetType() == my::GameQuest::Type::ToFront) {
        if (_info.text != "�D�ɏ���ăQ�[���N���A�I") {
            info.text = "�O�ɐi��";
            _info.text = info.text;
        } // if
    } // else if
    else if (quest.GetType() == my::GameQuest::Type::ShopAccessStart) {
        _prev_info.text = _info.text;
        info.text = "Shift�L�[/Y�{�^���ŃV���b�v�ɃA�N�Z�X";
    } // else if
    else if (quest.GetType() == my::GameQuest::Type::ShopAccessEnd) {
        info.text = _prev_info.text;
    } // else if
    _subject.Notify(info);
}

void my::HelpDesk::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::HelpDesk::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::HelpDesk::Initialize(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    auto menu = std::make_shared< my::HelpDeskMenu>("HelpDeskMenu");
    _subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool my::HelpDesk::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    return true;
}