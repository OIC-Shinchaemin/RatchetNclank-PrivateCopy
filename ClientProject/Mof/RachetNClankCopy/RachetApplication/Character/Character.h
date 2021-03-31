#ifndef MY_CHARACTER_H
#define MY_CHARACTER_H


#include "../Actor.h"
#include "../ResourceLocator.h"

#include <memory>

#include <Mof.h>

#include "../GameDefine.h"
#include "../Velocity.h"


namespace my {
class Character : public my::Actor, public my::ResourceLocator {
    using super = my::Actor;
protected:
    //! ���b�V��
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! ���[�V����
    Mof::LPMeshMotionController	_motion;
    //! ���x
    my::Velocity _velocity;
    //! �傫��
    float _volume;
    //! ����
    float _height;
protected:
    void InputMoveVelocity(Mof::CVector2 stick, float speed);
    void InputMoveAngularVelocity(Mof::CVector2 stick, float speed);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void UpdateTransform(float delta_time);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Character();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Character();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetSphere(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;
};
}
#endif // !MY_CHARACTER_H