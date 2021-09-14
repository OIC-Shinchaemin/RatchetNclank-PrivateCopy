#include "King.h"

#include "../../Component/VelocityComponent.h"
#include "../../Component/MeshComponent.h"


ratchet::actor::character::King::King() :
	super() {
}

ratchet::actor::character::King::~King() {
}

void ratchet::actor::character::King::OnNotify(const ratchet::actor::character::ScarecrowEndMessage&) {
	auto message = ratchet::game::gamesystem::text::TextSystemMessage();
	message.type = decltype(message.type)::EventNo0;
	_text_system_message_subject.Notify(message);
}

void ratchet::actor::character::King::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
	this->_question_texture = ptr;
}
bool ratchet::actor::character::King::Initialize(ratchet::actor::Actor::Param* param) {
	super::Initialize(param);

	auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
	velocity->Inactivate();
	velocity->SetUseGravity(false);

	auto mesh = super::GetComponent<ratchet::component::MeshComponent>();
	auto motion = mesh->GetMeshContainer()->CreateMotionController();
	auto count = motion->GetMotionCount();
	return true;
}

bool ratchet::actor::character::King::Update(float delta_time) {
	super::Update(delta_time);

	/*
	if (::g_pInput->IsKeyPush(MOFKEY_O)) {
		auto message = ratchet::game::gamesystem::text::TextSystemMessage();
		message.type = decltype(message.type)::EventNo0;
		_text_system_message_subject.Notify(message);
	} // if
	*/
	return true;
}

bool ratchet::actor::character::King::Render(void) {
	super::Render();

	// •`‰æ
	auto pos = super::GetPosition();
	float height = 2.4f;
	auto transform = def::Transform(Mof::CVector3(pos.x, pos.y + height, pos.z));
	if (auto tex = _question_texture.lock(); tex) {
		Mof::CMatrix44 scale, rotate, translate;
		Mof::CQuaternion quat; quat.Rotation(transform.rotate);

		scale.Scaling(transform.scale, scale);
		quat.ConvertMatrixTranspose(rotate);
		translate.Translation(transform.position, translate);

		Mof::CMatrix44 world = scale * rotate * translate;
		auto camera = ::CGraphicsUtilities::GetCamera();
		tex->Render(camera->GetBillBoardMatrix() * world);

		//CGraphicsUtilities::RenderTexture();
		//tex->Render(world, _rectangle.value());
	} // if
	return true;
}

void ratchet::actor::character::King::Talk(void) {
	static int a = 0;
	if (a == 0) {
		auto message = ratchet::game::gamesystem::text::TextSystemMessage();
		message.type = decltype(message.type)::EventNo0;
		_text_system_message_subject.Notify(message);
	} // if
	else {
		auto message = ratchet::game::gamesystem::text::TextSystemMessage();
		message.type = decltype(message.type)::EventNo1;
		_text_system_message_subject.Notify(message);
	} // else
	a++;
}