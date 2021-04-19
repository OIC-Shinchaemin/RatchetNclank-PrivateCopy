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
        //! �Փ˂��鑤
        ObjectArray layers;
        //! �Փ˂���鑤
        ObjectArray targets;
        //! �ǂ�ȕ��ɏՓ˂��邩
        std::shared_ptr<my::CollisionAlgolithm> algo;
    };
    //! �Փˏ����Ώ�
    std::vector<CollisionPair> _objects;
    //! �t�@�N�g���[
    my::Factory<my::CollisionAlgolithm> collision_algolithm_factory;
private:
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    std::shared_ptr<my::CollisionAlgolithm> CreateAlgolithm(const char* type);
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
};
}
#endif // !MY_PHYSIC_WORLD_H