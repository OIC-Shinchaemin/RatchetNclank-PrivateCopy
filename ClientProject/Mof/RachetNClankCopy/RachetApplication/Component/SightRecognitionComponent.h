#ifndef MY_SIGHT_RECOGNITION_COMPONENT_H
#define MY_SIGHT_RECOGNITION_COMPONENT_H


#include "Component.h"


namespace my {
class SightRecognitionComponent : public my::Component {
    using super = my::Component;
private:
    //! ����
    float _range;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority">�D��x</param>
    SightRecognitionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    SightRecognitionComponent(const SightRecognitionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SightRecognitionComponent();
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
    float GetRange(void) const;
    /// <summary>
    /// ���F�\����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 target);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_SIGHT_RECOGNITION_COMPONENT_H