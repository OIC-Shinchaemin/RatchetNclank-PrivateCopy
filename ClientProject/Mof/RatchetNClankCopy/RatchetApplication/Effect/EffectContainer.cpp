#include "EffectContainer.h"
#include "EffectPool.h"
#include "EffectEmitter.h"


ratchet::effect::EffectContainer::EffectContainer() :
	_pool(),
	_effects(),
	_emitter(){
	_emitter = this->CreateEmitter();
}

ratchet::effect::EffectContainer::~EffectContainer() {
}

std::shared_ptr<ratchet::effect::EffectEmitter> ratchet::effect::EffectContainer::CreateEmitter(void) {
	auto re = std::make_shared<ratchet::effect::EffectEmitter>();
	re->SetPool(&_pool);
	re->SetOutputTarget(&_effects);
	return re;
}

bool ratchet::effect::EffectContainer::Update(float delta_time) {
	ut::EraseRemove(_effects, [](auto effect) {
		return !effect->IsEnable();
		});

	if (::g_pInput->IsKeyPush(MOFKEY_E)) {
		auto info = ratchet::effect::Effect::Info();
		info.init_param.life_duration = 2.0f;
		info.init_param.transform.position = Mof::CVector3(5.0f, -5.0f, -5.0f);
		info.init_param.transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);

		info.update_param.velocity = Mof::CVector3(0.001f, 0.0f, 0.0f);
		info.update_param.rotate = Mof::CVector3(1.0f, 0.0f, 0.0f);
		info.update_param.scale = Mof::CVector3(0.001f, 0.0f, 0.0f);

		_emitter->Emit(info);
	} // if

	for (auto& effect : _effects) {
		effect->Update(delta_time);
	} // for
	return true;
}

bool ratchet::effect::EffectContainer::Render(void) {
	for (auto& effect : _effects) {
		if (!effect->IsEnable()) {
			continue;
		} // if

		if (auto resource = _resource.lock()) {
			auto path = _pool.GetResourcePath();
			auto tex = resource->Get<std::shared_ptr<Mof::CTexture>>(path.data());
			auto& param = effect->GetBasicParam();
			if (tex) {
				Mof::CMatrix44 scale, rotate, translate;
				//Mof::CQuaternion quat; quat.Rotation(param.transform.rotate);
				Mof::CQuaternion quat; quat.Rotation(Mof::CVector3());

				scale.Scaling(param.transform.scale, scale);
				quat.ConvertMatrixTranspose(rotate);
				translate.Translation(param.transform.position, translate);

				Mof::CMatrix44 world = scale * rotate * translate;
				auto camera = ::CGraphicsUtilities::GetCamera();
				tex->Render(camera->GetBillBoardMatrix() * world, param.color.ToU32Color());
			} // if

		} // if
	} // for
	return true;
}