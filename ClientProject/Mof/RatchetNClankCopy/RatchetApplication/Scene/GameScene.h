#ifndef RATCHET_SCENE_GAME_SCENE_H
#define RATCHET_SCENE_GAME_SCENE_H


#include "Scene.h"

#include <memory>
#include <vector>

#include "../Game/GameManager.h"
#include "../Event/EventManager.h"
#include "../Game/GameWorld.h"
#include "../Game/Renderer.h"
#include "../Game/PhysicsWorld.h"
#include "../Stage/Stage.h"
#include "../Game/GameSystem/ShopSystem.h"
#include "../Actor/Character/Player.h"
#include "../Actor/Character/Character.h"
#include "../Game/GameSystem/Text/TextSystem.h"
#include "../Event/StageViewEvent.h"
#include "../Effect/EffectContainer.h"
#include "../Component/SightRecognitionComponent.h"
#include "../Event/ShipEvent.h"
#include "../MessageObservationManager.h"
#include "DescriptionScene.h"


namespace ratchet::scene {
class GameScene :
    public ratchet::scene::Scene,
    public base::core::Observer<const ratchet::game::gamesystem::ShopSystem::Info&>,
    public event::StageViewEventMessageListener,
    public ratchet::actor::character::CharacterDamageApplyMessageListener,
    public ContactEnemyMessageListener,
    public event::ShipEventEndMessageListener,
    public ratchet::game::gamesystem::text::TextSystemOpenMessageListener,
    public ratchet::game::gamesystem::text::TextSystemClosedMessageListener {
    using super = ratchet::scene::Scene;
    friend class GameSceneInitializer;
private:
    //! 追加
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _created_actors;
    //! 削除
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _delete_actors;
    //! ゲーム
    ratchet::game::GameWorld _game_world;
    //! レンダラー
    ratchet::game::Renderer _renderer;
    //! コリジョン
    ratchet::game::PhysicsWorld _physic_world;
    //! ステージ
    Stage _stage;
    //! 再初期化
    bool _re_initialize;
    //! 再初期化
    bool _player_dead;
    //! メニュー
    base::core::Observable<bool> _pause_menu_subject;
    //! テキスト 
    std::shared_ptr<game::gamesystem::text::TextSystem> _text_system;
    //! ゲーム
    std::weak_ptr<ratchet::game::GameManager> _game;
    //! イベント
    std::weak_ptr<ratchet::event::EventManager> _event;
    //! エフェクト
    std::shared_ptr<effect::EffectContainer> _effect;
    //! カウンター
    base::core::Timer _loading_counter;
    //! カウンター
    int _loading_dot_count;
    //! 経過時間 / 所要時間
    float _loading_progress;
    //! 表示
    bool _show_how_to_play;
public:
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// 再初期化
    /// </summary>
    void ReInitialize(void);
protected:
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool SceneUpdate(float delta_time) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool LoadingUpdate(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool SceneRender(void) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool LoadingRender(void) override;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameScene();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameScene();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::ShopSystem::Info& info) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::event::StageViewEventMessage& message) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::event::ShipEventEndMessage& message) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::actor::character::CharacterDamageApplyMessage& message) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ContactEnemyMessage& message) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(game::gamesystem::text::TextSystemOpenMessageListener::Message message) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(game::gamesystem::text::TextSystemClosedMessageListener::Message message) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) override;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Load(std::shared_ptr<super::Param>  param) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RATCHET_SCENE_GAME_SCENE_H