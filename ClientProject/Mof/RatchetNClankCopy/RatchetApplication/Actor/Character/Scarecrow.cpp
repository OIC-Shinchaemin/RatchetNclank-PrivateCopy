#include "Scarecrow.h"

#include "../../Component/VelocityComponent.h"


ratchet::actor::character::Scarecrow::Scarecrow() :
	super() {
}

ratchet::actor::character::Scarecrow::~Scarecrow() {
}

void ratchet::actor::character::Scarecrow::End(void) {
	super::End();

	auto message = ScarecrowEndMessage();
	message.end = true;
	_end_message_subject.Notify(message);
}

bool ratchet::actor::character::Scarecrow::Initialize(ratchet::actor::Actor::Param* param) {
	super::Initialize(param);

	auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
	velocity->Inactivate();
	velocity->SetUseGravity(false);
	return true;
}

bool ratchet::actor::character::Scarecrow::Update(float delta_time) {
	super::Update(delta_time);
	/*
	if (::g_pInput->IsKeyPush(MOFKEY_O)) {
		auto message = ratchet::game::gamesystem::text::TextSystemMessage();
		message.type = decltype(message.type)::EventNo0;
		_text_system_message_subject.Notify(message);
	} // if
	*/

	if (::g_pInput->IsKeyPush(MOFKEY_U)) {
		this->End();
	} // if
	return true;
}

bool ratchet::actor::character::Scarecrow::Render(void) {
	super::Render();

	//// •`‰æ
	//auto pos = super::GetPosition();
	//float height = 2.4f;
	//auto transform = def::Transform(Mof::CVector3(pos.x, pos.y + height, pos.z));
	//if (auto tex = _question_texture.lock(); tex) {
	//	Mof::CMatrix44 scale, rotate, translate;
	//	Mof::CQuaternion quat; quat.Rotation(transform.rotate);

	//	scale.Scaling(transform.scale, scale);
	//	quat.ConvertMatrixTranspose(rotate);
	//	translate.Translation(transform.position, translate);

	//	Mof::CMatrix44 world = scale * rotate * translate;
	//	auto camera = ::CGraphicsUtilities::GetCamera();
	//	tex->Render(camera->GetBillBoardMatrix() * world);

	//	//CGraphicsUtilities::RenderTexture();
	//	//tex->Render(world, _rectangle.value());
	//} // if
	return true;
}