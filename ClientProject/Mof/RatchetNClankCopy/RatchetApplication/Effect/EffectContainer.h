#ifndef RATCHET_EFFECT_EFFECT_CONTAINER_H
#define RATCHET_EFFECT_EFFECT_CONTAINER_H


#include <array>

#include <Mof.h>

#include "Effect.h"
#include "EffectPool.h"
#include "EffectEmitter.h"


namespace ratchet::effect {
	class EffectContainer {
	private:
		//! ���\�[�X
		std::weak_ptr<ratchet::ResourceMgr> _resource;
		//! �v�[��
		ratchet::effect::EffectPool _pool;
		//! �G�~�b�^�[
		std::shared_ptr<ratchet::effect::EffectEmitter> _emitter;
		//! �G�t�F�N�g
		std::vector<effect::Effect*> _effects;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		EffectContainer();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~EffectContainer();
		/// <summary>
		/// �Z�b�^�[
		/// </summary>
		/// <param name="ptr"></param>
		void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr) {
			this->_resource = ptr;
		}
		/// <summary>
		/// �쐬
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		std::shared_ptr<ratchet::effect::EffectEmitter> CreateEmitter(void);
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="delta_time"></param>
		bool Update(float delta_time);
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name=""></param>
		bool Render(void);
	};
}
#endif // !RATCHET_EFFECT_EFFECT_CONTAINER_H