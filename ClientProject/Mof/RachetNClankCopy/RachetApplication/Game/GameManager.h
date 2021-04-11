#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H

#include <memory>
#include <vector>

#include "My/Core/Observer.h"
#include "GameWorld.h"
#include "Renderer.h"
#include "PhysicsWorld.h"
#include "../GameSystem/GameMoney.h"
#include "../GameSystem/WeaponSystem.h"
#include "../GameSystem/QuickChangeSystem.h"
#include "../Actor/Stage/Stage.h"


namespace my {
class GameManager : public std::enable_shared_from_this<my::GameManager>, public my::Observer<const char*, const std::shared_ptr<my::Actor>&> {
private:
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! 追加
    std::vector<std::shared_ptr<my::Actor>> _created_actors;
    //! 削除
    std::vector<std::shared_ptr<my::Actor>> _delete_actors;
    //! ゲーム
    my::GameWorld _game_world;
    //! レンダラー
    my::Renderer _renderer;
    //! コリジョン
    my::PhysicsWorld _physic_world;
    //! 金
    std::unique_ptr<my::GameMoney>  _game_money;
    //! 武器
    std::shared_ptr<my::WeaponSystem>  _weapon_system;
    //! クイックチェンジ
    std::shared_ptr<my::QuickChangeSystem>  _quick_change;
    //! ステージ
    Stage _stage;
private:
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<my::Actor>& ptr);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameManager();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    //void SetFactoryManager(const std::shared_ptr<class FactoryManager>& ptr);
    void SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_GAME_MANAGER_H