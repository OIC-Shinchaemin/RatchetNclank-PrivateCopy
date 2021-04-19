#include "QuickChangeSystem.h"

#include "My/Core/Math.h"
#include "My/Core/Utility.h"
#include "../../Gamepad.h"
#include "../../UI/QuickChangeMenu.h"


void my::QuickChangeSystem::Open(void) {
    _color = Mof::CVector4(1.0f, 1.0f, 1.0f, 0.0f);
    _state = State::Enter;
}

void my::QuickChangeSystem::Close(void) {
    // notify target weapon name
    if (_current_angle.has_value()) {
        auto& item = _items.at(_current_angle.value());
        auto weapon_name = item.GetWeapon();
        _current.Notify(weapon_name);
    } // if
    _current_angle.reset();
    _state = State::Exit;
}

my::QuickChangeSystem::QuickChangeSystem() :
    _position(256.0f, 256.0f),
    _color(1.0f, 1.0f, 1.0f, 0.0f),
    _state(State::Exit),
    _alpha(0.08f),
    _distance(128.0f),
    _angles(8),
    _current_angle(),
    _resource(),
    _ui_canvas() {

    int n = 0;
    std::generate(_angles.begin(), _angles.end(), [&n]() {
        int angle = n;
        n += 45;
        return angle;
    });

    for (auto& degree : _angles) {
        auto radian = math::Radian(degree);
        Mof::CVector2 pos = Mof::CVector2(_position + Mof::CVector2(std::cos(radian()) * _distance, -std::sin(radian()) * _distance));

        auto temp = my::QuickChangeItem();
        auto rect = Mof::CRectangle(0.0f, 0.0f, 64.0f, 64.0f);
        temp.SetRectangle(rect);
        temp.SetPosition(pos - rect.GetBottomRight() * 0.5f);
        _items.emplace(degree, std::move(temp));
    } // for

    _tex_names.emplace("BombGlove", "../Resource/texture/icon/bomb_glove.png");
    _tex_names.emplace("Pyrocitor", "../Resource/texture/icon/pyrocitor.png");
    _tex_names.emplace("Blaster", "../Resource/texture/icon/blaster.png");
    _tex_names.emplace("GloveOfDoom", "../Resource/texture/icon/glove_of_doom.png");
    _tex_names.emplace("MineGlove", "../Resource/texture/icon/mine_glove.png");
    _tex_names.emplace("Taunter", "../Resource/texture/icon/taunter.png");
    _tex_names.emplace("SuckCannon", "../Resource/texture/icon/suck_cannon.png");
    _tex_names.emplace("Devastator", "../Resource/texture/icon/devastator.png");
    _tex_names.emplace("Walloper", "../Resource/texture/icon/walloper.png");
    _tex_names.emplace("VisibombGun", "../Resource/texture/icon/visibomb_gun.png");
    _tex_names.emplace("DecoyGlove", "../Resource/texture/icon/decoy_glove.png");
    _tex_names.emplace("DroneDevice", "../Resource/texture/icon/drone_device.png");
    _tex_names.emplace("TeslaClaw", "../Resource/texture/icon/tesla_claw.png");
    _tex_names.emplace("MorphORay", "../Resource/texture/icon/morph_o_ray.png");
    _tex_names.emplace("RYNO", "../Resource/texture/icon/ryno.png");
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
    return this->_color;
}

void my::QuickChangeSystem::AddWeaponObserver(const std::shared_ptr<my::Observer<const std::string&>>& ptr) {
    _current.AddObserver(ptr);
}

bool my::QuickChangeSystem::Initialize(Mof::CVector2 pos, const std::shared_ptr<my::WeaponSystem>& weapon_system) {
    _ASSERT_EXPR(!_resource.expired(), L"無効なポインタを保持しています");

    std::vector<std::string> work;
    weapon_system->CreateAvailableMechanicalWeaponNames(work);

    int i = 0;
    for (auto& name : work) {
        auto& path = _tex_names.at(name);

        auto tex = _resource.lock()->Get<std::shared_ptr<Mof::CTexture> >(path.c_str());

        auto& temp = _items.at(i * 45);

        temp.SetWeapon(name.c_str());
        temp.SetTexture(tex);
        i++;
    } // for


    auto menu = std::make_shared< my::QuickChangeMenu>("QuickChangeMenu");
    Observable::AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetPosition(_position);

    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool my::QuickChangeSystem::Input(void) {
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_Y) || ::g_pInput->IsKeyPush(MOFKEY_LSHIFT) || ::g_pInput->IsKeyPush(MOFKEY_RSHIFT)) {
        this->Open();
    } // if
    else if (::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_Y) || ::g_pInput->IsKeyPull(MOFKEY_LSHIFT) || ::g_pInput->IsKeyPull(MOFKEY_RSHIFT)) {
        this->Close();
    } // else if

    float x = g_pGamepad->GetStickHorizontal();
    float y = g_pGamepad->GetStickVertical();
    float threshold = 0.5f;
    if (threshold < std::sqrt(x * x + y * y)) {
        int degree = math::ToDegree(std::atan2f(y, x));
        if (degree < 0) {
            degree += math::ToDegree(math::kTwoPi);
        } /// if
        _current_angle = ut::Approximate(_angles, degree);
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_0)) {
        _current_angle = 45.0f * 0;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_1)) {
        _current_angle = 45.0f * 1;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_2)) {
        _current_angle = 45.0f * 2;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_3)) {
        _current_angle = 45.0f * 3;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_4)) {
        _current_angle = 45.0f * 4;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_5)) {
        _current_angle = 45.0f * 5;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_6)) {
        _current_angle = 45.0f * 6;
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_7)) {
        _current_angle = 45.0f * 7;
    } // else if
    return true;
}

bool my::QuickChangeSystem::Update(void) {
    if (_state == State::Enter) {
        _color.a += _alpha;
        if (_color.a > 1.0f) {
            _color.a = 1.0f;
        } // if
        Observable::Notify(_color);
    } // if
    else if (_state == State::Exit) {
        _color.a -= _alpha;
        Observable::Notify(_color);
    } // else if

    return true;
}

bool my::QuickChangeSystem::Render(void) {
    for (auto& item : _items) {
        item.second.Render(_color);
    } // for

    // 選択中のものをわかりやすくしたい
    if (_current_angle.has_value()) {
        float current_angle = _current_angle.value();
        auto rect = Mof::CRectangle(0.0f, 0.0f, 64.0f, 64.0f);
        auto radian = math::Radian(current_angle);
        rect.Translation(-rect.GetBottomRight() * 0.5f);
        rect.Translation(_position + Mof::CVector2(std::cos(radian()) * _distance, -std::sin(radian()) * _distance));
        ::CGraphicsUtilities::RenderFillRect(rect, Mof::CVector4(1.0f, 1.0f, 0.0f, _color.a).ToU32Color());
    } // if

    return true;
}

bool my::QuickChangeSystem::Release(void) {
    _items.clear();
    _tex_names.clear();
    return true;
}

void my::QuickChangeItem::SetPosition(Mof::CVector2 pos) {
    this->_position = pos;
}

void my::QuickChangeItem::SetRectangle(Mof::CRectangle rect) {
    this->_rectangle = rect;
}

void my::QuickChangeItem::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_texture = ptr;
}

void my::QuickChangeItem::SetWeapon(const char* name) {
    this->_weapon = name;
}

const char* my::QuickChangeItem::GetWeapon(void) const {
    return this->_weapon.c_str();
}

bool my::QuickChangeItem::Render(Mof::CVector4 color) {
    auto rect = _rectangle;
    auto pos = _position;

    if (auto tex = _texture.lock()) {
        tex->Render(pos.x, pos.y, color.ToU32Color());
    } // if
    rect.Translation(pos);
    ::CGraphicsUtilities::RenderRect(rect, Mof::CVector4(0.0f, 1.0f, 1.0f, color.a).ToU32Color());
    return true;
}