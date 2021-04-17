#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// �J��������N���X
/// </summary>
// ********************************************************************************
class CameraController {
public:

    template<class T >
    struct Controll {
        bool    trigger_flag;
        T       move;
    };

    struct Controller {
        Controll<Vector3>   rotation;
        Controll<float>     zoom;
        Controll<Vector3>   track;
    };

private:

    //! ���䂷��J�����|�C���^
    CCamera* _camera_pointer{ nullptr };

    //! �J�����̃Y�[����
    float _zoom_ratio{ 1.0f };

    // ********************************************************************************
    /// <summary>
    /// �J�����̃p��(���E)�ƃe�B���g(�㉺)����
    /// </summary>
    /// <param name="rotation">��]��</param>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    void PanTilt(const Controll<Vector3>& rotation);

    // ********************************************************************************
    /// <summary>
    /// �J�����̃Y�[��
    /// </summary>
    /// <param name="zoom">�Y�[����</param>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    void Zoom(const Controll<float>& zoom);

    // ********************************************************************************
    /// <summary>
    /// �J�����̃g���b�N
    /// </summary>
    /// <param name="track">�ړ���</param>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    void Track(const Controll<Vector3>& track);

public:

    // ********************************************************************************
    /// <summary>
    /// �J�����̐ݒ�
    /// </summary>
    /// <param name="camera_pointer">���䂷��J�����|�C���^</param>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    void SetCamera(CCamera* camera_pointer);

    // ********************************************************************************
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="camera_pointer">���䂷��J�����|�C���^</param>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    void Initialize(CCamera* camera_pointer);

    // ********************************************************************************
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="controller">����f�[�^</param>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    void Update(const Controller& controller);

};

