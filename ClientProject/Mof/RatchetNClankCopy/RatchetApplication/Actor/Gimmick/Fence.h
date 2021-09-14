#ifndef RATCHET_ACTOR_GIMMICK_FENCE_H
#define RATCHET_ACTOR_GIMMICK_FENCE_H


#include "../Actor.h"


namespace ratchet::actor::gimmick {
	class Fence : public ratchet::actor::Actor {
		using super = ratchet::actor::Actor;
	private:
		//! メッシュ
		Mof::CMeshContainer _mesh;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Fence();
		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Fence();
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual bool Update(float delta_time) override;
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual bool Render(void) override;
	};
}
#endif // !RATCHET_ACTOR_GIMMICK_FENCE_H