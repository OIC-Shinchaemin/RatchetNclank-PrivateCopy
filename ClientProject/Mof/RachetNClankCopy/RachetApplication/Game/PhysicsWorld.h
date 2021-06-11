#ifndef RACHET_PHYSIC_WORLD_H
#define RACHET_PHYSIC_WORLD_H


#include <memory>

#include "../Actor.h"
#include "../Component/Collision/Object/CollisionComponent.h"
#include "../Component/Collision/Algolithm/CollisionAlgolithm.h"
#include "../Factory/Factory.h"
#include "../Stage/Stage.h"


namespace rachet {
class PhysicsWorld {
    using ActorPtr = std::shared_ptr<rachet::Actor>;
    using ObjectPtr = std::shared_ptr<rachet::CollisionComponent>;
    using ObjectArray = std::vector<ObjectPtr>;
private:
    struct CollisionLayer {
        //! 衝突する側
        ObjectArray objects;
        //! 衝突される側
        ObjectArray targets;
        //! どんな風に衝突するか
        std::shared_ptr<rachet::CollisionAlgolithm> algo;
    };
    //! 衝突処理対象
    std::vector<CollisionLayer> _layers;
    //! ファクトリー
    rachet::Factory<rachet::CollisionAlgolithm> collision_algolithm_factory;
    //! ステージとぶつける用
    ObjectArray _list_for_stage;

    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    void GenerateLayer(void);
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
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="stage"></param>
    void CollisionStage(Stage* stage);
    /// <summary>
    /// リセット
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !RACHET_PHYSIC_WORLD_H