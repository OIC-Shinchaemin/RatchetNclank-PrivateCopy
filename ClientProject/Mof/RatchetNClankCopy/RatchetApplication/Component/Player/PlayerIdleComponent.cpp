#include "PlayerIdleComponent.h"

#include "../../Actor/Character/Player.h"
#include "../../TutorialManager.h"


ratchet::component::player::action::PlayerIdleComponent::PlayerIdleComponent(int priority) :
	super(priority),
	_type_com() {
}

ratchet::component::player::action::PlayerIdleComponent::PlayerIdleComponent(const PlayerIdleComponent& obj) :
	super(obj),
	_type_com() {
}

ratchet::component::player::action::PlayerIdleComponent::~PlayerIdleComponent() {
}

std::string ratchet::component::player::action::PlayerIdleComponent::GetType(void) const {
	return "PlayerIdleComponent";
}

std::string_view ratchet::component::player::action::PlayerIdleComponent::GetStateType(void) const {
	return state::PlayerActionStateType::kPlayerActionIdleState;
}

bool ratchet::component::player::action::PlayerIdleComponent::Initialize(void) {
	super::Initialize();
	_type_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerComponent>();
	return true;
}

bool ratchet::component::player::action::PlayerIdleComponent::Input(void) {
	float horizontal = ::g_pGamepad->GetStickHorizontal();
	float vertical = ::g_pGamepad->GetStickVertical();
	float threshold = 0.5f;
	auto stick = Mof::CVector2(horizontal, vertical);

	if (::g_pInput->IsKeyHold(MOFKEY_W) || ::g_pInput->IsKeyHold(MOFKEY_A) ||
		::g_pInput->IsKeyHold(MOFKEY_S) || ::g_pInput->IsKeyHold(MOFKEY_D) ||
		stick.Length() > threshold) {
		super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMoveState);
	} // if
	else if (::g_pInput->IsKeyPush(MOFKEY_J) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
		if (tutorial::TutorialManager::GetInstance().IsLiberation(tutorial::TutorialManager::TutorialType::Jump)) {
			super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpSetState);
		} // if
	} // else if
	else if (::g_pInput->IsKeyPush(MOFKEY_N) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
		if (tutorial::TutorialManager::GetInstance().IsLiberation(tutorial::TutorialManager::TutorialType::Attack)) {
			super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackOneState);
		} // if
	} // else if
	else if (::g_pInput->IsKeyPush(MOFKEY_V) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_B)) {
		auto type_com = _type_com.lock();
		if (type_com->IsContactMode()) {
			type_com->TalkToTarget();
		} // if
		else {
			auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetOwner());
			if (owner->GetCurrentMechanical()) {
				super::ChangeActionState(state::PlayerActionStateType::kPlayerActionShotAttackState);
			} // if
		} // else
	} // else if
	else if (::g_pInput->IsKeyPush(MOFKEY_B) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_R_BTN)) {
		super::ChangeActionState(state::PlayerActionStateType::kPlayerActionCrouchState);
	} // else if

	return true;
}

bool ratchet::component::player::action::PlayerIdleComponent::Update(float delta_time) {
	return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerIdleComponent::Clone(void) {
	return std::make_shared<ratchet::component::player::action::PlayerIdleComponent>(*this);
}

bool ratchet::component::player::action::PlayerIdleComponent::Start(void) {
	if (this->IsActive()) {
		return false;
	} // if
	super::Start();
	super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionIdleState);
	return true;
}