#ifndef MY_SIGHT_RECOGNITION_COMPONENT_H
#define MY_SIGHT_RECOGNITION_COMPONENT_H


#include "Component.h"


namespace my {
class SightRecognitionComponent : public my::Component {
    using super = my::Component;
private:
    //! 視野
    float _range;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority">優先度</param>
    SightRecognitionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    SightRecognitionComponent(const SightRecognitionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SightRecognitionComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
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
    bool ContainInRecognitionRange(Mof::CVector3 target);
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_SIGHT_RECOGNITION_COMPONENT_H