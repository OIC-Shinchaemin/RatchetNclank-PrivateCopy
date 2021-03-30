#ifndef MY_SIGHT_RECOGNITION_H
#define MY_SIGHT_RECOGNITION_H


#include <memory>

#include <Mof.h>
//#include "Character/Enemy.h"


namespace my {
class SightRecognition {
private:
    //! 所有者
    std::weak_ptr<class Enemy> _owner;
    //! 視野
    float _range;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SightRecognition();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SightRecognition();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="owner"></param>
    void SetOwner(const std::shared_ptr<class my::Enemy>& owner);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRange(void) const;
    /// <summary>
    /// 視認可能判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool ContainInRecognitionRange(Mof::CSphere volume);
    bool ContainInRecognitionRange(Mof::CVector3 target);
};
}
#endif // !MY_SIGHT_RECOGNITION_H