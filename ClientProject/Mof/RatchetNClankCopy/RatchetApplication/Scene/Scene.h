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
				//! ���O
				std::string name;
				//! �p�X
				std::string resource;
			};
		protected:
			//! ���
			this_type::State _state;
			//! ���
			this_type::TransitionState _transition_state;
			//! �J���[���\�[�X
			Mof::CTexture _rendar_target;
			//! �f�t�H���g�̃����_�[�^�[�Q�b�g
			Mof::LPRenderTarget _default;
			//! �|�X�g�G�t�F�N�g
			std::optional<ratchet::scene::SceneEffect> _effect;
			//! �J��
			base::core::Observable<const scene::SceneMessage&> _subject;
			//! ���\�[�X
			std::weak_ptr<ratchet::ResourceMgr> _resource;
			//! UI
			std::weak_ptr<base::ui::UICanvas> _ui_canvas;
			//! �ǂݍ��ݍς�
			bool _loaded;
			//! ����
			std::mutex _mutex;
			//! �X���b�h
			std::optional<std::thread> _load_thread;
		protected:
			/// <summary>
			/// ����
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
			/// �R���X�g���N�^
			/// </summary>
			Scene();
			/// <summary>
			/// �f�X�g���N�^
			/// </summary>
			virtual ~Scene();
			/// <summary>
			/// �Z�b�^�[
			/// </summary>
			/// <param name="ptr"></param>
			void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
			/// <summary>
			/// �Z�b�^�[
			/// </summary>
			/// <param name="ptr"></param>
			void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
			/// <summary>
			/// �Q�b�^�[
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual std::string GetName(void) = 0;
			/// <summary>
			/// �Q�b�^�[
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			TransitionState GetTransitionState(void) const;
			/// <summary>
			/// �Z�b�^�[
			/// </summary>
			/// <param name="ptr"></param>
			void AddSceneObserver(const std::shared_ptr<base::core::Observer<const scene::SceneMessage&>>& ptr);
			/// <summary>
			/// ������
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Load(std::shared_ptr<ratchet::scene::Scene::Param> param);
			/// <summary>
			/// ������
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Initialize(void);
			/// <summary>
			/// ����
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Input(void);
			/// <summary>
			/// �X�V
			/// </summary>
			/// <param name="delta_time">����</param>
			/// <returns></returns>
			virtual bool Update(float delta_time);
			/// <summary>
			/// �`��
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Render(void);
			/// <summary>
			/// ���
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			virtual bool Release(void);
		};
	}
}
#endif // !RATCHET_SCENE_SCENE_H