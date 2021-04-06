#ifndef MY_ATTACK_H
#define MY_ATTACK_H


#include <Mof.h>


namespace my {
class Attack {
private:
    //! ���L��
    std::weak_ptr<class Enemy> _owner;
    //! �U���͈�
    float _range;
    //! �T�C�Y
    float _volume;
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
    /// <param name="owner"></param>
    void SetOwner(const std::shared_ptr<class Enemy>& owner);
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
    Mof::CSphere GetRangeSphere(void) const;
    /// <summary>
    /// �A�N�V����
    /// </summary>
    /// <param name=""></param>
    void Start(void);
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void);
};
}
#endif // !MY_ATTACK_H