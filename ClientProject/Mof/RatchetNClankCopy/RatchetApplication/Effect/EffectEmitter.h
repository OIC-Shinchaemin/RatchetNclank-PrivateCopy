#ifndef RATCHET_EFFECT_EFFECT_EMITTER_H
#define RATCHET_EFFECT_EFFECT_EMITTER_H


#include "Effect.h"
#include "EffectPool.h"


namespace ratchet::effect {
	class EffectEmitter {
	private:
		//! プール
		ratchet::effect::EffectPool* _pool;
		//! エフェクト
		std::vector<effect::Effect*>* _out_target;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		EffectEmitter();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~EffectEmitter();
		/// <summary>
		/// セッター
		/// </summary>
		void SetPool(ratchet::effect::EffectPool* ptr);
		/// <summary>
		/// セッター
		/// </summary>
		void SetOutputTarget(std::vector<effect::Effect*>* ptr);
		/// <summary>
		/// 放出
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		bool Emit(const ratchet::effect::Effect::Info& info);
	};
}
#endif // !RATCHET_EFFECT_EFFECT_EMITTER_H