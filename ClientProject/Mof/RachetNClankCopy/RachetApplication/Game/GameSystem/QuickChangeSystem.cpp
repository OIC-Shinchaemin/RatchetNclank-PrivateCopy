#include "QuickChangeSystem.h"

#include "My/Core/Math.h"
#include "My/Core/Utility.h"
#include "../../Gamepad.h"
#include "../../UI/QuickChangeMenu.h"


void my::QuickChangeSystem::Open(void) {
    _info.color = Mof::CVector4(1.0f, 1.0f, 1.0f, 0.0f);
    _state = State::Enter;
}

void my::QuickChangeSystem::Close(void) {
    // notify target weapon name
    if (_info.current_index.has_value()) {
        auto& item = _items.at(_info.current_index.value() * 45);
        auto weapon_name = item.GetWeapon();
        _current.Notify(weapon_name);
    } // if
    _info.current_index.reset();
    _state = State::Exit;
}

my::QuickChangeSystem::QuickChangeSystem() :
    _info(),
    _state(State::Exit),
    _alpha(0.08f),
    _distance(128.0f),
    _angles(8),
    _resource(),
    _ui_canvas() {
}

my::QuickChangeSystem::~QuickChangeSystem() {
}

void my::QuickChangeSystem::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::QuickChangeSystem::SetUICanvas(const std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

Mof::CVector4 my::QuickChangeSystem::GetColor(void) const {
    return this->_info.color;
}

void my::QuickChangeSystem::AddWeaponObserver(const std::shared_ptr<my::Observer<const std::string&>>& ptr) {
    _current.AddObserver(ptr);
}

void my::QuickChangeSystem::AddInfoObserver(const std::shared_ptr<my::Observer<const my::QuickChangeSystem::Info&>>& ptr) {
    _subject.AddObserver(ptr);
}

bool my::QuickChangeSystem::Initialize(const std::shared_ptr<my::WeaponSystem>& weapon_system) {
    _ASSERT_EXPR(!_resource.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");

    int n = 0;
    std::generate(_angles.begin(), _angles.end(), [&n]() {
        int angle = n;
        n += 45;
        return angle;
    });
    for (auto& degree : _angles) {
        _items.emplace(degree, std::move(my::QuickChangeItem()));
    } // for

    // ui
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("QuickChangeMenu");
    } // if
    auto menu = std::make_shared< my::QuickChangeMenu>("QuickChangeMenu");
    _subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    if (auto canvas = _ui_canvas.lock()) {
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

    _info.color = Mof::CVector4(1.0f, 1.0f, 1.0f, 0.0f);
    _subject.Notify(_info);
    return true;
}

bool my::QuickChangeSystem::Update(void) {
    // open close
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_Y) || ::g_pInput->IsKeyPush(MOFKEY_LSHIFT) || ::g_pInput->IsKeyPush(MOFKEY_RSHIFT)) {
        this->Open();
    } // if
    else if (::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_Y) || ::g_pInput->IsKeyPull(MOFKEY_LSHIFT) || ::g_pInput->IsKeyPull(MOFKEY_RSHIFT)) {
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
        _info.current_index = current_angle / 45.0f;
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_0)) {
        _info.current_index = 0;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_1)) {
        _info.current_index = 1;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_2)) {
        _info.current_index = 2;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_3)) {
        _info.current_index = 3;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_4)) {
        _info.current_index = 4;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_5)) {
        _info.current_index = 5;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_6)) {
        _info.current_index = 6;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_7)) {
        _info.current_index = 7;
    } // else if


    // update color
    if (_state == State::Enter) {
        _info.color.a += _alpha;
        if (_info.color.a > 1.0f) {
            _info.color.a = 1.0f;
        } // if
        _subject.Notify(_info);
    } // if
    else if (_state == State::Exit) {
        _info.color.a -= _alpha;
        _subject.Notify(_info);
    } // else if
    return true;
}

bool my::QuickChangeSystem::Release(void) {
    _items.clear();
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("QuickChangeMenu");
    } // if
    return true;
}

void my::QuickChangeItem::SetWeapon(const char* name) {
    this->_weapon = name;
}

const char* my::QuickChangeItem::GetWeapon(void) const {
    return this->_weapon.c_str();
}