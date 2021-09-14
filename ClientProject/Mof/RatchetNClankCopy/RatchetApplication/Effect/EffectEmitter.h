#ifndef RATCHET_EFFECT_EFFECT_EMITTER_H
#define RATCHET_EFFECT_EFFECT_EMITTER_H


#include "Effect.h"
#include "EffectPool.h"


namespace ratchet::effect {
	class EffectEmitter {
	private:
		//! �v�[��
		ratchet::effect::EffectPool* _pool;
		//! �G�t�F�N�g
		std::vector<effect::Effect*>* _out_target;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		EffectEmitter();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~EffectEmitter();
		/// <summary>
		/// �Z�b�^�[
		/// </summary>
		void SetPool(ratchet::effect::EffectPool* ptr);
		/// <summary>
		/// �Z�b�^�[
		/// </summary>
		void SetOutputTarget(std::vector<effect::Effect*>* ptr);
		/// <summary>
		/// ���o
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		bool Emit(const ratchet::effect::Effect::Info& info);
	};
}
#endif // !RATCHET_EFFECT_EFFECT_EMITTER_H