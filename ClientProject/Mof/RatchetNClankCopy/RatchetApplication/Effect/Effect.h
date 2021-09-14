#ifndef RATCHET_EFFECT_EFFECT_H
#define RATCHET_EFFECT_EFFECT_H


#include <Mof.h>

#include <memory>

#include "../GameDefine.h"
#include "EffectDefine.h"
#include "Base/Core/Timer.h"


namespace ratchet::effect {
	class Effect {
	public:
		struct UpdateParam {
			//! 位置
			Mof::CVector3 velocity;
			//! 回転
			Mof::CVector3 rotate;
			//! 拡大
			Mof::CVector3 scale;
			//! 加算色
			Mof::CVector4 color;
		};
		struct EnvironmentParam {
			bool gravity;
		};
		struct BasicParam {
			ratchet::effect::EffectType type;
			//! トランスフォーム
			def::Transform transform;
			//! 色
			Mof::CVector4 color;
			//! 存在期間
			float life_duration;

			BasicParam& operator+=(const ratchet::effect::Effect::UpdateParam& update) {
				this->transform.position += update.velocity;
				this->transform.rotate += update.rotate;
				this->transform.scale += update.scale;
				this->color += update.color;
				return *this;
			}
		};
		struct Info {
			BasicParam init_param;
			UpdateParam update_param;
			EnvironmentParam environment_param;
		};
	private:
		//! 有効
		bool _enable;
		//! 時間
		base::core::Timer _life_timer;
		//! 初期化パラメータ
		std::optional<BasicParam> _initialize_param;
		//! 基本パラメータ
		BasicParam _basic_param;
		//! 更新パラメータ
		ratchet::effect::Effect::UpdateParam _update_param;
		//! 環境パラメータ
		ratchet::effect::Effect::EnvironmentParam _environment_param;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Effect();
		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Effect();
		/// <summary>
		/// 判定
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		bool IsEnable(void) const;
		/// <summary>
		/// ゲッター
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		const ratchet::effect::Effect::BasicParam& GetBasicParam(void) const;
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		bool Initialize(void);
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
		/// <summary>
		/// 開始
		/// </summary>
		/// <param name="info"></param>
		void Start(const ratchet::effect::Effect::Info& info);
	};
}
#endif // !RATCHET_EFFECT_EFFECT_H