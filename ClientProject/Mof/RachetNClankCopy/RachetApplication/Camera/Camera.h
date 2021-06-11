#ifndef RATCHET_CAMERA_H
#define RATCHET_CAMERA_H


#include <Mof.h>


namespace ratchet {
class Camera {
private:
    //! �J����
    Mof::CCamera _camera;
    //! �ʒu
    Mof::CVector3 _position;
    //! �Ώ�
    Mof::CVector3 _target;
    //! �����
    Mof::CVector3 _up;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Camera();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Camera();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Mof::CVector3 position);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="target"></param>
    void SetTarget(Mof::CVector3 target);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    Mof::CVector3 GetPosition(void) ;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetTarget(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetViewFront(void) ;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    bool Update(void);
    /// <summary>
    /// �O���[�o���J�����ɓo�^
    /// </summary>
    /// <param name=""></param>
    void RegisterGlobalCamera(void);
};
}
#endif // !RATCHET_CAMERA_H