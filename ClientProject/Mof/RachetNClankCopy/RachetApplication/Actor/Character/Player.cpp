#include "Player.h"

#include "../../Gamepad.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"
#include "../../Factory/FactoryManager.h"


my::Player::Player() :
    super(),
    _current_mechanical(),
    _omniwrench(),
    _children(),
    _current_weapon(),
    _player_com(),
    _upp_bone_state(),
    _shop_system_subject("ShopSystem"),
    _quick_change_subject("QuickChange"),
    _notificationable_subject_map(),
    _notificationable_subject_stack() {
    super::SetTag("Player");
    _notificationable_subject_map.emplace("QuickChange", &_quick_change_subject);
    _notificationable_subject_map.emplace("ShopSystem", &_shop_system_subject);
}

my::Player::~Player() {
}

void my::Player::OnNotify(std::shared_ptr<my::Weapon> change) {
    if (auto mechanical = std::dynamic_pointer_cast<my::Mechanical>(change)) {
        _current_mechanical = mechanical;
    } // if
    else {
        _current_mechanical.reset();
    } // else
    _current_weapon = change;
}

void my::Player::OnNotify(const my::QuickChangeSystem::Info& info) {
    if (info.color.a <= 0.0f) {
        super::Activate();
    } // if
    else if (info.color.a >= 1.0f) {
        super::Sleep();
    } // else if
}
/*
void my::Player::OnNotify(const my::ShopSystem::Info& info) {
    if (info.close) {
        this->PopNotificationableSubject();
    } // if
}
*/
my::Observable<bool>* my::Player::GetShopSystemSubject(void) {
    return &this->_shop_system_subject.subject;
}

my::Observable<bool>* my::Player::GetQuickChangeSubject(void) {
    return &this->_quick_change_subject.subject;
}

std::shared_ptr<my::Actor> my::Player::GetChild(const std::string& tag) const {
    auto it = std::find_if(_children.begin(), _children.end(), [&tag](const std::shared_ptr<my::Actor>& ptr) {
        return ptr->GetTag() == tag;
    });
    if (it == _children.end()) {
        return nullptr;
    } // if
    return *it;
}

std::shared_ptr<my::Mechanical> my::Player::GetCurrentMechanical(void) const {
    if (auto weapon = this->_current_mechanical.lock()) {
        return weapon;
    } // if
    return nullptr;
}

void my::Player::AddChild(const std::shared_ptr<my::Actor>& ptr) {
    this->_children.push_back(ptr);
}

void my::Player::PushNotificationableSubject(const std::string& name) {
    auto subject = _notificationable_subject_map.at(name);
    _notificationable_subject_stack.push(subject);
}

void my::Player::PopNotificationableSubject(void) {
    _notificationable_subject_stack.pop();
}
void my::Player::PopNotificationableSubject(const std::string& name) {
    auto& subject = _notificationable_subject_stack.top();
    if (subject->name == name) {
        this->PopNotificationableSubject();
    } // if
}

bool my::Player::Initialize(void) {
    this->Initialize();
    return true;
}

bool my::Player::Initialize(my::Actor::Param* param) {
    super::Initialize(param);

    _player_com = super::GetComponent<my::PlayerComponent>();
    if (auto motion_com = super::GetComponent<my::MotionComponent>(); motion_com) {
        auto motion = motion_com->GetMotionData();
        _upp_bone_state = motion->GetBoneState("UPP_weapon");
    } // if
    return true;
}

bool my::Player::Input(void) {
    super::Input();
    if (!_notificationable_subject_stack.empty()) {
        auto& subject = _notificationable_subject_stack.top();
        if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_Y) || ::g_pInput->IsKeyPush(MOFKEY_LSHIFT)) {
            subject->subject.Notify(true);
        } // if
    } // if
    return true;
}

bool my::Player::Update(float delta_time) {
    super::Update(delta_time);

    // children transform
    Mof::CMatrix44 mat = _upp_bone_state->pBone->GetRotationOffsetMatrix() * _upp_bone_state->BoneMatrix;
    Mof::CVector3 scale, rotate, translate;
    mat.GetScaling(scale); mat.GetRotation(rotate); mat.GetTranslation(translate);

    if (_current_weapon) {
        _current_weapon->SetScale(scale);
        _current_weapon->SetPosition(translate);
        _current_weapon->SetRotate(rotate);
        _current_weapon->Update(delta_time);
    } // if


    /*
    // children update
    if (auto weapon = _current_mechanical.lock()) {
        weapon->Update(delta_time);
        if (weapon->IsAction() && weapon->CanFire()) {
            Mof::CVector3 pos;
            mat.GetTranslation(pos);

            if (auto target = super::GetComponent<my::PlayerComponent>()->GetTarget().lock()) {
                auto target_pos = target->GetPosition();
                auto target_height = 0.5f;
                target_pos.y += target_height;
                weapon->SetLockOnPosition(target_pos);
            } // if
            else {
                weapon->ResetTargetPosition();
            } // else
            weapon->Fire(def::Transform(pos, super::GetRotate()));
        } // if
    } // if
    */
    return true;
}

bool my::Player::Render(void) {
    super::Render();
    if (_current_weapon) {
        _current_weapon->Render();
    } // if

#ifdef _DEBUG
    auto pos = super::GetPosition();
    ::CGraphicsUtilities::RenderString(50.0f, 300.0f, "pos x = %f", pos.x);
    ::CGraphicsUtilities::RenderString(50.0f, 320.0f, "pos y = %f", pos.y);
    ::CGraphicsUtilities::RenderString(50.0f, 340.0f, "pos z = %f", pos.z);

    if (!_notificationable_subject_stack.empty()) {
        auto subject = _notificationable_subject_stack.top();
        if (subject) {
            ::CGraphicsUtilities::RenderString(50.0f, 360.0f, "_notificationable_subject_stack.size() = %d", _notificationable_subject_stack.size());
        } // if
    } // if
#endif // _DEBUG

    return true;
}

bool my::Player::Release(void) {
    super::Release();

    _shop_system_subject.subject.Clear();
    _quick_change_subject.subject.Clear();
    _current_mechanical.reset();
    _omniwrench.reset();
    _children.clear();
    _current_weapon.reset();
    _player_com.reset();;
    _upp_bone_state = nullptr;
    return true;
}