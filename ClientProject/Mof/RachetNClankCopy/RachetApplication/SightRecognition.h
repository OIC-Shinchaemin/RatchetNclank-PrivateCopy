#ifndef MY_SIGHT_RECOGNITION_H
#define MY_SIGHT_RECOGNITION_H


#include <memory>

#include <Mof.h>
//#include "Character/Enemy.h"


namespace my {
class SightRecognition {
private:
    //! ���L��
    std::weak_ptr<class Enemy> _owner;
    //! ����
    float _range;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SightRecognition();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SightRecognition();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="owner"></param>
    void SetOwner(const std::shared_ptr<class my::Enemy>& owner);
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
    //bool ContainInRecognitionRange(Mof::CSphere volume);
    bool ContainInRecognitionRange(Mof::CVector3 target);
};
}
#endif // !MY_SIGHT_RECOGNITION_H