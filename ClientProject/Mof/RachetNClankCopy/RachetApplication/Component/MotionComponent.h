#ifndef RATCHET_MOTION_COMPONENT_H
#define RATCHET_MOTION_COMPONENT_H


#include "UpdateComponent.h"

#include <string>

#include <Mof.h>

#include "../MotionNames.h"


namespace ratchet {
class MotionComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
private:
    //! ���[�V����
    Mof::LPMeshMotionController	_motion;
    //! ���[�V������
    std::weak_ptr<ratchet::MotionNames> _motion_names;
    //! �p�X
    std::string _path;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    /// <param name="speed"></param>
    /// <param name="loop"></param>
    /// <param name="same"></param>
    /// <returns></returns>
    bool ChangeMotionByName(const char* name, float speed = 1.0f, bool loop = true, bool same = true);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    MotionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    MotionComponent(const MotionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~MotionComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
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
    const std::shared_ptr<ratchet::MotionNames> GetMotionInfoMap(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::LPMeshMotionController GetMotionData(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEndMotion(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <typeparam name="Enum"></typeparam>
    /// <param name="type"></param>
    /// <param name="speed"></param>
    /// <param name="loop"></param>
    /// <param name="same"></param>
    /// <returns></returns>
    template<typename Enum>
    bool ChangeMotion(Enum type, float speed = 1.0f, bool loop = true, bool same = true) {
        if (auto motion_names = _motion_names.lock()) {
            return this->ChangeMotionByName(
                motion_names->At(type),
                speed, loop, same);
        } // if
        return false;
    }
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="time"></param>
    /// <returns></returns>
    bool AddTimer(float time);
};
}
#endif // !RATCHET_MOTION_COMPONENT_H