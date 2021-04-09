#ifndef MY_MOTION_COMPONENT_H
#define MY_MOTION_COMPONENT_H


#include "UpdateComponent.h"

#include <string>

#include "../MotionNames.h"


namespace my {
class MotionComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! �A�j���[�V�����f�[�^
    Mof::LPMeshMotionController _motion;
    //! ���[�V����
    my::MotionNames _motion_names;
    //std::unordered_map<std::string, std::string> _motion_names;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    void GenerateMotionNames(void);
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    const char* GetMotionName(const std::string& type);
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    /// <param name="loop"></param>
    /// <param name="speed"></param>
    /// <param name="same"></param>
    /// <returns></returns>
    bool ChangeMotionByName(const char* name, bool loop = true, float speed = 1.0f, bool same = true);
};
}
#endif // !MY_MOTION_COMPONENT_H