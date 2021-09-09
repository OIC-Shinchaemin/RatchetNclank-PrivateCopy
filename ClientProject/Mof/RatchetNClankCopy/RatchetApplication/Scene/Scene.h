#ifndef RATCHET_SCENE_SCENE_H
#define RATCHET_SCENE_SCENE_H


#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include <Mof.h>

#include "SceneDefine.h"
#include "../Actor/Actor.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "Base/Core/Observer.h"
#include "Base/UI/UICanvas.h"


namespace ratchet {
	namespace scene {
		class Scene : public std::enable_shared_from_this<ratchet::scene::Scene>, public base::core::Observer<const char*, const std::shared_ptr<ratchet::actor::Actor>&> {
			using this_type = ratchet::scene::Scene;
		public:
			enum class State {
				Active,
				Sleep,
				Pause,
				End
			};
			enum class TransitionState {
				None,
				In,
				Out,
				End,
			};
			struct Param {
				//! 名前
				std::string name;
				//! パス
				std::string resource;
			};
		protected:
			//! 状態
			this_type::State _state;
			//! 状態
			this_type::TransitionState _transition_state;
			//! カラーリソース
			Mof::CTexture _rendar_target;
			//! デフォルトのレンダーターゲット
			Mof::LPRenderTarget _default;
			//! ポストエフェクト
			std::optional<ratchet::scene::SceneEffect> _effect;
			//! 遷移
			base::core::Observable<const scene::SceneMessage&> _subject;
			//! リソース
			std::weak_ptr<ratchet::ResourceMgr> _resource;
			//! UI
			std::weak_ptr<base::ui::UICanvas> _ui_canvas;
			//! 読み込み済み
			bool _loaded;
			//! 同期
			std::mutex _mutex;
			//! スレッド
			std::optional<std::thread> _load_thread;
		protected:
			/// <summary>
			/// 判定
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			bool IsLoaded(void);
			void LoadComplete(void);

			std::shared_ptr<ratchet::ResourceMgr> GetResource(void) const;
			std::shared_ptr<base::ui::UICanvas> GetUICanvas(void) const;
			Mof::LPRenderTarget GetDefaultRendarTarget(void) const;
			virtual bool LoadingUpdate(float delta_time);
			virtual bool SceneUpdate(float delta_time);
			virtual bool PreRender(void);
			virtual bool LoadingRender(void);
			virtual bool SceneRender(void);
			virtual bool PostRender(void);
		public:
			/// <summary>
			/// コンストラクタ
			/// </summary>
			Scene();
			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~Scene();
			/// <summary>
			/// セッター
			/// </summary>
			/// <param name="ptr"></param>
			void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
			/// <summary>
			/// セッター
			/// </summary>
			/// <param name="ptr"></param>
			void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
			/// <summary>
			/// ゲッター
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual std::string GetName(void) = 0;
			/// <summary>
			/// ゲッター
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			TransitionState GetTransitionState(void) const;
			/// <summary>
			/// セッター
			/// </summary>
			/// <param name="ptr"></param>
			void AddSceneObserver(const std::shared_ptr<base::core::Observer<const scene::SceneMessage&>>& ptr);
			/// <summary>
			/// 初期化
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Load(std::shared_ptr<ratchet::scene::Scene::Param> param);
			/// <summary>
			/// 初期化
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Initialize(void);
			/// <summary>
			/// 入力
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Input(void);
			/// <summary>
			/// 更新
			/// </summary>
			/// <param name="delta_time">時間</param>
			/// <returns></returns>
			virtual bool Update(float delta_time);
			/// <summary>
			/// 描画
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Render(void);
			/// <summary>
			/// 解放
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Release(void);
		};
	}
}
#endif // !RATCHET_SCENE_SCENE_H