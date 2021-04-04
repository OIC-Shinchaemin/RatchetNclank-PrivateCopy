#ifndef MY_PLAYER_COLLISION_OBJECT_H
#define MY_PLAYER_COLLISION_OBJECT_H


#include "CollisionObject.h"

#include <optional>
#include <memory>

#include <Mof.h>


class Player;
namespace my {
class PlayerCollisionObject : public my::CollisionObject {
    using super = my::CollisionObject;
private:
    //! ���L��
    std::weak_ptr<Player> _owner;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerCollisionObject();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerCollisionObject();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="owner"></param>
    virtual void SetOwner(std::any owner) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::any GetOwner(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetType(void) const override;
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
};
}
#endif // !MY_PLAYER_COLLISION_OBJECT_H