#ifndef MY_ENEMY_COLLISION_OBJECT_H
#define MY_ENEMY_COLLISION_OBJECT_H


#include "CollisionObject.h"

#include <optional>
#include <memory>

#include <Mof.h>


namespace my {
class EnemyCollisionObject : public my::CollisionObject {
    using super = my::CollisionObject;
private:
    //! ���L��
    //std::weak_ptr<class Enemy> _owner;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyCollisionObject(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyCollisionObject(const EnemyCollisionObject& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyCollisionObject();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="owner"></param>
    //virtual void SetOwner(std::any owner) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual std::any GetOwner(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CSphere> GetSphere(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CBoxAABB> GetBox(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetRay(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<my::SightObject> GetSightObject(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_ENEMY_COLLISION_OBJECT_H