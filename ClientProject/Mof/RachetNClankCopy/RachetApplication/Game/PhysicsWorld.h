#ifndef MY_PHYSIC_WORLD_H
#define MY_PHYSIC_WORLD_H


#include <memory>

#include "../Actor.h"
#include "../Component/Collision/Object/CollisionObject.h"
#include "../Component/Collision/Algolithm/CollisionAlgolithm.h"
#include "../Factory/Factory.h"


namespace my {
class PhysicsWorld {
    using ActorPtr = std::shared_ptr<my::Actor>;
    using ObjectPtr = std::shared_ptr<my::CollisionObject>;
    using ObjectArray = std::vector<ObjectPtr>;
private:
    struct CollisionPair {
        //! 衝突する側
        ObjectArray layers;
        //! 衝突される側
        ObjectArray targets;
        //! どんな風に衝突するか
        std::shared_ptr<my::CollisionAlgolithm> algo;
    };
    //! 衝突処理対象
    std::vector<CollisionPair> _objects;
    //! ファクトリー
    my::Factory<my::CollisionAlgolithm> collision_algolithm_factory;
private:
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    std::shared_ptr<my::CollisionAlgolithm> CreateAlgolithm(const char* type);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PhysicsWorld();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PhysicsWorld();
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
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
#endif // !MY_PHYSIC_WORLD_H