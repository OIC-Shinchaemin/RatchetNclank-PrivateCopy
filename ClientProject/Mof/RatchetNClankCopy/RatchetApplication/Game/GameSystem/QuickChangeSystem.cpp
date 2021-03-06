#include "QuickChangeSystem.h"

#include "Base/Core/Math.h"
#include "Base/Core/Utility.h"
#include "../../Gamepad.h"
#include "../../UI/QuickChangeMenu.h"


void ratchet::game::gamesystem::QuickChangeSystem::Open(void) {
    _infomation.color = Mof::CVector4(1.0f, 1.0f, 1.0f, 0.0f);
    _state = State::Enter;
}

void ratchet::game::gamesystem::QuickChangeSystem::Close(void) {
    // notify target weapon name
    if (_infomation.current_index.has_value()) {
        auto& item = _items.at(_infomation.current_index.value() * 45);
        auto weapon_name = item.GetWeapon();
        _current.Notify(weapon_name);
    } // if
    _infomation.current_index.reset();
    _state = State::Exit;
}

ratchet::game::gamesystem::QuickChangeSystem::QuickChangeSystem() :
    _infomation(),
    _state(State::Exit),
    _alpha(0.08f),
    _distance(128.0f),
    _angles(8)
//    ,
//    _resource(),
//    _ui_canvas() 
{
}

ratchet::game::gamesystem::QuickChangeSystem::~QuickChangeSystem() {
}

void ratchet::game::gamesystem::QuickChangeSystem::OnNotify(bool flag) {
    super::OnNotify(flag);
    this->Open();
}

Mof::CVector4 ratchet::game::gamesystem::QuickChangeSystem::GetColor(void) const {
    return this->_infomation.color;
}

void ratchet::game::gamesystem::QuickChangeSystem::AddWeaponObserver(const std::shared_ptr<base::core::Observer<const std::string&>>& ptr) {
    _current.AddObserver(ptr);
}

void ratchet::game::gamesystem::QuickChangeSystem::AddInfoObserver(const std::shared_ptr<base::core::Observer<const ratchet::game::gamesystem::QuickChangeSystem::Info&>>& ptr) {
    _info_subject.AddObserver(ptr);
}

bool ratchet::game::gamesystem::QuickChangeSystem::Initialize(const std::shared_ptr<ratchet::game::gamesystem::WeaponSystem>& weapon_system) {
    //_ASSERT_EXPR(!_resource.expired(), L"無効なポインタを保持しています");
    _ASSERT_EXPR(super::GetResource(), L"無効なポインタを保持しています");

    int n = 0;
    std::generate(_angles.begin(), _angles.end(), [&n]() {
        int angle = n;
        n += 45;
        return angle;
    });
    for (auto& degree : _angles) {
        _items.emplace(degree, std::move(ratchet::game::gamesystem::QuickChangeItem()));
    } // for

    // ui
    if (auto canvas = super::GetUICanvas()) {
        canvas->RemoveElement("QuickChangeMenu");
    } // if
    auto menu = std::make_shared< ratchet::ui::QuickChangeMenu>("QuickChangeMenu");
    _info_subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(super::GetResource());
    if (auto canvas = super::GetUICanvas()) {
        canvas->AddElement(menu);
    } // if

    // generate
    std::vector<std::string> work;
    weapon_system->CreateAvailableMechanicalWeaponNames(work);
    for (uint32_t i = 0, n = work.size(); i < n; i++) {
        auto& item = _items.at(i * 45);
        item.SetWeapon(work.at(i).c_str());
        menu->AddWeaponInfo(i, work.at(i).c_str());
    } // for

    _infomation.color = Mof::CVector4(1.0f, 1.0f, 1.0f, 0.0f);
    _info_subject.Notify(_infomation);
    return true;
}

bool ratchet::game::gamesystem::QuickChangeSystem::Update(float delta_time) {
    // open close
    if (::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_Y) || ::g_pInput->IsKeyPull(MOFKEY_LSHIFT) || ::g_pInput->IsKeyPull(MOFKEY_RSHIFT)) {
        this->Close();
    } // else if

    // index
    float x = g_pGamepad->GetStickHorizontal();
    float y = g_pGamepad->GetStickVertical();
    float threshold = 0.5f;
    if (threshold < std::sqrt(x * x + y * y)) {
        int degree = math::ToDegree(std::atan2f(y, x));
        if (degree < 0) {
            degree += math::ToDegree(math::kTwoPi);
        } /// if
        float current_angle = ut::Approximate(_angles, degree);
        _infomation.current_index = current_angle / 45.0f;
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_0)) {
        _infomation.current_index = 0;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_1)) {
        _infomation.current_index = 1;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_2)) {
        _infomation.current_index = 2;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_3)) {
        _infomation.current_index = 3;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_4)) {
        _infomation.current_index = 4;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_5)) {
        _infomation.current_index = 5;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_6)) {
        _infomation.current_index = 6;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_7)) {
        _infomation.current_index = 7;
    } // else if


    // update color
    if (_state == State::Enter) {
        _infomation.color.a += _alpha;
        if (_infomation.color.a > 1.0f) {
            _infomation.color.a = 1.0f;
        } // if
        _info_subject.Notify(_infomation);
    } // if
    else if (_state == State::Exit) {
        _infomation.color.a -= _alpha;
        _info_subject.Notify(_infomation);
        if (_infomation.color.a <= 0) {
            return false;
        } // if
    } // else if
    return true;
}

bool ratchet::game::gamesystem::QuickChangeSystem::Release(void) {
    _items.clear();
    if (auto canvas = super::GetUICanvas()) {
        canvas->RemoveElement("QuickChangeMenu");
    } // if
    return true;
}

void ratchet::game::gamesystem::QuickChangeItem::SetWeapon(const char* name) {
    this->_weapon = name;
}

const char* ratchet::game::gamesystem::QuickChangeItem::GetWeapon(void) const {
    return this->_weapon.c_str();
}