#pragma once
#include "GimmickBase.h"
#include "Base/Core/ServiceLocator.h"
#include "../../Actor/Actor.h"
#include "../../Camera/CameraController.h"
#include "../../Component/CameraComponent.h"
#include "../../Event/EventManager.h"


struct ElevatorArrivalMessage {
};
using ElevatorArrivalMessageSubject = base::core::Observable<const ElevatorArrivalMessage&>;
using ElevatorArrivalMessageListener = base::core::Observer<const ElevatorArrivalMessage&>;

class Elevator : public GimmickBase {
private:
    /// <summary>
    /// �C�x���g�J�n
    /// </summary>
    /// <param name=""></param>
    void EnemyViewEventStart(void);
protected:
    //! �J�n�ʒu
    Vector3 _start_pos;
    //! �I���ʒu
    Vector3 _end_pos;
    //! ���݂̎���
    float _now_timer;
    //! ���v����
    float _request_time;
    //! �J�n�t���O
    bool _start_flag;
    //! �I���t���O
    bool _end_flag;
    //! �ʒu
    Mof::CVector3 _preview_position;
    //! �ʒu
    Mof::CVector3 _initial_position;
    //! �t���O
    bool _first_initialized;
    //! �v���C���[�J����
    base::core::ServiceLocator<ratchet::camera::CameraController>* _camera_controller;
    //! �v���C���[�ʒm�p    
    ElevatorArrivalMessageSubject _elevator_arrival_message_subject;
    //! �C�x���g
    std::weak_ptr<ratchet::event::EventManager> _event_manager;
    //! �v���C���[�J����
    std::weak_ptr<ratchet::component::CameraComponent> _player_camera_component;
    //! ���ʊp,�p
    Mof::CVector3 _camera_angle_start;
public:
    Elevator(Vector3 end, float request, bool enable = true, bool collision = true,
             StageObjectType type = StageObjectType::None, std::string name = "",
             int mesh_no = -1,
             Vector3 pos = Vector3(),
             Vector3 scale = Vector3(1, 1, 1),
             Vector3 rotate = Vector3());
    virtual ~Elevator(void);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayerCamera(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(const std::shared_ptr<ratchet::event::EventManager>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayerCameraComponent(const std::shared_ptr<ratchet::component::CameraComponent>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetElevatorArrivalMessageSubject(void) {
        return &this->_elevator_arrival_message_subject;
    };
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetPreviewPosition(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetRequestTime(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetMoveValue(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetVolume(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetHeight(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetStartPositionSphere(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetEndPositionSphere(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    virtual void Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta"></param>
    virtual void Update(float delta) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    virtual void ActionStart(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsStart(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Vector3 GetEndPos(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRequest(void) const;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    virtual void SetPosition(const Vector3& pos) override;
    /// <summary>
    /// �ď�����
    /// </summary>
    /// <param name=""></param>
    virtual void ReInitialize(void) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="enable"></param>
    /// <param name="collision"></param>
    /// <param name="type"></param>
    /// <param name="name"></param>
    /// <param name="mesh_no"></param>
    /// <param name="pos"></param>
    /// <param name="scale"></param>
    /// <param name="rotate"></param>
    virtual void SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no,
                                    Vector3 pos, Vector3 scale, Vector3 rotate) override;

    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void) override;
#ifdef STAGEEDITOR
    float* GetStartPosPointer(void);
    float* GetEndPosPointer(void);
    float* GetRequestPointer(void);
#endif//STAGEEDITOR
};

