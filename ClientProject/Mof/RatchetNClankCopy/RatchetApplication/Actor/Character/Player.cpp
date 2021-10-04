#include "Player.h"

#include "../../Gamepad.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"
#include "../../Factory/FactoryManager.h"
#include "../../Event/EventReferenceTable.h"
#include "../../Factory/ActorFactory.h"
#include "../../Component/BillboardComponent.h"
#include "../Effect/SenseEffect.h"

ratchet::actor::character::Player::Player() :
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
    _notificationable_subject_stack(),
    //_character_talkable_message_subject(std::make_shared<actor::character::CharacterTalkableMessageSubject>()){
    _character_talkable_message_subject(){
    super::SetTag("Player");
    _notificationable_subject_map.emplace("QuickChange", &_quick_change_subject);
    _notificationable_subject_map.emplace("ShopSystem", &_shop_system_subject);
}

ratchet::actor::character::Player::~Player() {
}

void ratchet::actor::character::Player::OnNotify(std::shared_ptr<ratchet::actor::weapon::Weapon> change) {
    if (auto mechanical = std::dynamic_pointer_cast<ratchet::actor::weapon::Mechanical>(change)) {
        _current_mechanical = mechanical;
    } // if
    else {
        _current_mechanical.reset();
    } // else

    if (_current_weapon) {
        _current_weapon->SetScale(math::vec3::kZero);
    } // if
    _current_weapon = change;
}

void ratchet::actor::character::Player::OnNotify(const ratchet::game::gamesystem::QuickChangeSystem::Info& info) {
    if (info.color.a <= 0.0f) {
        super::Activate();
    } // if
    else if (info.color.a >= 1.0f) {
        super::Sleep();
    } // else if
}

void ratchet::actor::character::Player::OnNotify(const ratchet::game::gamesystem::text::TextSystemClosedMessage& message) {
    if (message.close) {
        super::Activate();
    } // if
}

void ratchet::actor::character::Player::OnNotify(const ElevatorArrivalMessage& message) {
    super::Activate();
}

void ratchet::actor::character::Player::SetEffectContainer(const std::shared_ptr<ratchet::effect::EffectContainer >& ptr) {
    this->_effect_container = ptr;
}

base::core::Observable<bool>* ratchet::actor::character::Player::GetShopSystemSubject(void) {
    return &this->_shop_system_subject.subject;
}

base::core::Observable<bool>* ratchet::actor::character::Player::GetQuickChangeSubject(void) {
    return &this->_quick_change_subject.subject;
}

base::core::Observable<const ratchet::game::gamesystem::GameQuest&>* ratchet::actor::character::Player::GetQuestSubject(void) {
    return &this->_quest_subject;
}

std::shared_ptr<ratchet::actor::Actor> ratchet::actor::character::Player::GetChild(const std::string& tag) const {
    auto it = std::find_if(_children.begin(), _children.end(), [&tag](const std::shared_ptr<ratchet::actor::Actor>& ptr) {
        return ptr->GetTag() == tag;
    });
    if (it == _children.end()) {
        return nullptr;
    } // if
    return *it;
}

std::shared_ptr<ratchet::actor::weapon::Mechanical> ratchet::actor::character::Player::GetCurrentMechanical(void) const {
    if (auto weapon = this->_current_mechanical.lock()) {
        return weapon;
    } // if
    return nullptr;
}

std::shared_ptr<ratchet::effect::EffectContainer> ratchet::actor::character::Player::GetEffectContainer(void) const {
    if (auto ptr = _effect_container.lock()) {
        return ptr;
    } // if
    return nullptr;
}

void ratchet::actor::character::Player::AddChild(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    this->_children.push_back(ptr);
}

void ratchet::actor::character::Player::PushNotificationableSubject(const std::string& name) {
    auto subject = _notificationable_subject_map.at(name);
    _notificationable_subject_stack.push(subject);
}

void ratchet::actor::character::Player::PopNotificationableSubject(void) {
    _notificationable_subject_stack.pop();
}
void ratchet::actor::character::Player::PopNotificationableSubject(const std::string& name) {
    auto& subject = _notificationable_subject_stack.top();
    if (subject->name == name) {
        this->PopNotificationableSubject();
    } // if
}

void ratchet::actor::character::Player::End(void) {
    if (_current_weapon) {
        _current_weapon->SetScale(math::vec3::kZero);
    } // if
    super::End();
    ratchet::event::EventReferenceTable::Singleton().Dispose(super::GetName());
    ratchet::event::EventReferenceTable::Singleton().Dispose("CameraComponent");
}

bool ratchet::actor::character::Player::Initialize(void) {
    this->Initialize();
    return true;
}

bool ratchet::actor::character::Player::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);

    _player_com = super::GetComponent<ratchet::component::player::PlayerComponent>();
    if (auto motion_com = super::GetComponent<ratchet::component::MotionComponent>(); motion_com) {
        auto motion = motion_com->GetMotionData();
        _upp_bone_state = motion->GetBoneState("UPP_weapon");
    } // if

    auto tag = ratchet::Tag();
    tag = "TitleElement";
    auto& holder = super::GetTagHolder();
    auto it = std::find_if(holder.tags.begin(), holder.tags.end(), [&tag](auto t) {
        return t == tag;
    });
    if (it == holder.tags.end()) {
        auto sense_effect_param = Actor::Param();
        sense_effect_param.name = "sense_effecr";
        sense_effect_param.tag = "sense";

        auto sense_effect_child_actor = ratchet::factory::FactoryManager::Singleton().CreateActor<actor::effect::SenseEffect>("builder/sense_effect.json", &sense_effect_param);
        _sense_effect_child_actor = sense_effect_child_actor;

        this->GetComponent<component::SightRecognitionComponent>()->GetFindEnemyMessageSubject()->AddObserver(
            std::dynamic_pointer_cast<effect::SenseEffect>(_sense_effect_child_actor));
    }

    return true;
}

bool ratchet::actor::character::Player::Input(void) {
    super::Input();
    if (!_notificationable_subject_stack.empty()) {
        auto& subject = _notificationable_subject_stack.top();
        if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_Y) || ::g_pInput->IsKeyPush(MOFKEY_LSHIFT)) {
            subject->subject.Notify(true);
        } // if
    } // if
    return true;
}

bool ratchet::actor::character::Player::Update(float delta_time) {
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

    if (_sense_effect_child_actor) {
        _sense_effect_child_actor->SetScale(math::vec3::kOne);
        auto pos = super::GetPosition();
//        pos.y += 2.0f;
        _sense_effect_child_actor->SetPosition(pos);
        _sense_effect_child_actor->SetRotate(math::vec3::kZero);
        _sense_effect_child_actor->Update(delta_time);
    } // if
    return true;
}

bool ratchet::actor::character::Player::Render(void) {
    super::Render();
    if (_current_weapon) {
        _current_weapon->Render();
    } // if

    if (_sense_effect_child_actor) {
        auto state = _sense_effect_child_actor->GetState();
        if (state != decltype(state)::Hide) {
            _sense_effect_child_actor->Render();
        } // if
    } // if


//#ifdef _DEBUG
    if (debug::DebugManager::GetInstance().IsDebugMode()) {
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
    } // if
//#endif // _DEBUG
    return true;
}
#include "../../Event/EventReferenceTable.h"
bool ratchet::actor::character::Player::Release(void) {
    super::Release();

    if (event::EventReferenceTable::Singleton().Exist("")) {
    } // if

    _quest_subject.Clear();
    _shop_system_subject.subject.Clear();
    _quick_change_subject.subject.Clear();
    _current_mechanical.reset();
    _omniwrench.reset();
    _children.clear();
    _sense_effect_child_actor.reset();
    _current_weapon.reset();
    _player_com.reset();;
    _upp_bone_state = nullptr;
    return true;
}