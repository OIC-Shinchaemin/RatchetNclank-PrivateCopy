#ifndef MY_PHYSIC_WORLD_H
#define MY_PHYSIC_WORLD_H


#include "Actor.h"

namespace my {
class PhysicWorld {
    using ActorPtr = std::shared_ptr<my::Actor>;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PhysicWorld();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PhysicWorld();
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
};
}
#endif // !MY_PHYSIC_WORLD_H