#ifndef RATCHET_GAME_GAME_WORLD_H
#define RATCHET_GAME_GAME_WORLD_H


#include <memory>
#include <vector>

#include "../Actor/Actor.h"


namespace ratchet::game {
class GameWorld {
    using ActorPtr = std::shared_ptr<ratchet::actor::Actor>;
private:
    //! 所持
    std::vector<ActorPtr> _actors;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameWorld();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameWorld();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    ratchet::game::GameWorld::ActorPtr GetActor(uint32_t index) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="actor"></param>
    void AddActor(const ActorPtr& actor);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="actor"></param>
    void RemoveActor(const ActorPtr& actor);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    void UpdateDebug(void);
    /// <summary>
    /// リセット
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !RATCHET_GAME_GAME_WORLD_H