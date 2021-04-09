#ifndef MY_ATTACK_H
#define MY_ATTACK_H


#include "Action.h"

#include <Mof.h>


namespace my {
class Attack : public my::Action {
    using super = my::Action;
private:
    //! �U���͈�
    float _range;
    //! �T�C�Y
    float _volume;
    //! ���[�V�����|�C���^���Q�Ƃ���Ǘ��͂��Ȃ�
    Mof::LPMeshMotionController _motion;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool InactiveCondition(void) const override;
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Execute(float delta_time) override;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Attack();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Attack();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetMotion(Mof::LPMeshMotionController ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRange(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetVolume(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetSphere(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetCanAttackRangeSphere(void) const;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// ������
    /// </summary>
    void Inactive(void);
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void);
};
}
#endif // !MY_ATTACK_H