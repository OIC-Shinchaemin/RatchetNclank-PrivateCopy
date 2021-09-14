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
		//! リソース
		std::weak_ptr<ratchet::ResourceMgr> _resource;
		//! プール
		ratchet::effect::EffectPool _pool;
		//! エミッター
		std::shared_ptr<ratchet::effect::EffectEmitter> _emitter;
		//! エフェクト
		std::vector<effect::Effect*> _effects;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		EffectContainer();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~EffectContainer();
		/// <summary>
		/// セッター
		/// </summary>
		/// <param name="ptr"></param>
		void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr) {
			this->_resource = ptr;
		}
		/// <summary>
		/// 作成
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		std::shared_ptr<ratchet::effect::EffectEmitter> CreateEmitter(void);
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="delta_time"></param>
		bool Update(float delta_time);
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name=""></param>
		bool Render(void);
	};
}
#endif // !RATCHET_EFFECT_EFFECT_CONTAINER_H