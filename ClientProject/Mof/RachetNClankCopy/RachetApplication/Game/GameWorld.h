#ifndef MY_GAME_WORLD_H
#define MY_GAME_WORLD_H


#include <memory>
#include <vector>

#include "../Actor.h"


namespace my {
class GameWorld {
    using ActorPtr = std::shared_ptr<my::Actor>;
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
    my::GameWorld::ActorPtr GetActor(uint32_t index) const;
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
#endif // !MY_GAME_WORLD_H