#include "Player.h"

#include "../../Gamepad.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"
#include "../../Factory/FactoryManager.h"


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

bool my::Player::Disable(void) {
    this->_enable = false;
    return true;
}

void my::Player::AddChild(const std::shared_ptr<my::Actor>& ptr) {
    this->_children.push_back(ptr);
}

bool my::Player::Initialize(void) {
    this->Initialize();
    return true;
}

bool my::Player::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    _enable = true;

    _player_com = super::GetComponent<my::PlayerComponent>();
    if (auto motion_com = super::GetComponent<my::MotionComponent>(); motion_com) {
        auto motion = motion_com->GetMotionData();
        _upp_bone_state = motion->GetBoneState("UPP_weapon");
    } // if
    return true;
}

my::Player::Player() :
    super(),
    _current_mechanical(),
    _omniwrench(),
    _children(),
    _current_weapon(),
    _player_com(),
    _upp_bone_state(),
    _enable(true) {
    super::SetTag("Player");

    //auto param = super::Param();
    //param.name = "weapon";
    //param.tag = "OmniWrench";
    //auto omniwrench = my::FactoryManager::Singleton().CreateActor<my::OmniWrench>("builder/omni_wrench.json", &param);
    //this->AddChild(omniwrench);
    //this->_current_weapon = omniwrench;
}

my::Player::~Player() {
}

void my::Player::OnNotify(std::shared_ptr<my::Weapon> change) {
    if (auto mechanical = std::dynamic_pointer_cast<my::Mechanical>(change) ) {
        _current_mechanical = mechanical;
    } // if
    _current_weapon = change;
}

void my::Player::OnNotify(const my::QuickChangeSystem::Info& info) {
    if (info.color.a <= 0.0f) {
        if (auto player_com = _player_com.lock()) {
            player_com->EnableAction();
        } // if
    } // if
    else if (info.color.a >= 1.0f) {
        if (auto player_com = _player_com.lock()) {
            player_com->DisableAction();
        } // if
    } // else if
}

bool my::Player::Update(float delta_time) {
    if (!_enable) {
        return false;
    } // if
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
    if (!_enable) {
        return false;
    } // if
    super::Render();
    if (_current_weapon) {
        _current_weapon->Render();
    } // if


#ifdef _DEBUG
    auto pos = super::GetPosition();
    ::CGraphicsUtilities::RenderString(50.0f, 300.0f, "pos x = %f", pos.x);
    ::CGraphicsUtilities::RenderString(50.0f, 320.0f, "pos y = %f", pos.y);
    ::CGraphicsUtilities::RenderString(50.0f, 340.0f, "pos z = %f", pos.z);
#endif // _DEBUG

    return true;
}

bool my::Player::Release(void) {
    super::Release();
    _current_mechanical.reset();
    _omniwrench.reset();
    _children.clear();
    _current_weapon.reset();
    _player_com.reset();;
    _upp_bone_state = nullptr;
    return true;
}