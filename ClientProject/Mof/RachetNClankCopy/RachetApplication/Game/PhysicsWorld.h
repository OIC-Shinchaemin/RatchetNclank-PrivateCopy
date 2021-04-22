#ifndef MY_PHYSIC_WORLD_H
#define MY_PHYSIC_WORLD_H


#include <memory>

#include "../Actor.h"
#include "../Component/Collision/Object/CollisionComponent.h"
#include "../Component/Collision/Algolithm/CollisionAlgolithm.h"
#include "../Factory/Factory.h"
#include "../Stage/Stage.h"


namespace my {
class PhysicsWorld {
    using ActorPtr = std::shared_ptr<my::Actor>;
    using ObjectPtr = std::shared_ptr<my::CollisionComponent>;
    using ObjectArray = std::vector<ObjectPtr>;
private:
    struct CollisionLayer {
        //! �Փ˂��鑤
        ObjectArray objects;
        //! �Փ˂���鑤
        ObjectArray targets;
        //! �ǂ�ȕ��ɏՓ˂��邩
        std::shared_ptr<my::CollisionAlgolithm> algo;
    };
    //! �Փˏ����Ώ�
    std::vector<CollisionLayer> _layers;
    //! �t�@�N�g���[
    my::Factory<my::CollisionAlgolithm> collision_algolithm_factory;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void GenerateLayer(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PhysicsWorld();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PhysicsWorld();
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="actor"></param>
    void AddActor(const ActorPtr& actor);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="actor"></param>
    void RemoveActor(const ActorPtr& actor);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="stage"></param>
    void CollisionStage(Stage* stage);
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !MY_PHYSIC_WORLD_H