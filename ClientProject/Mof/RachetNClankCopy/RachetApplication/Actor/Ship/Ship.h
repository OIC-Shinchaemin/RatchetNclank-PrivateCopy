#ifndef MY_SHIP_H
#define MY_SHIP_H


#include "../../Actor.h"
#include "My/Core/Observer.h"


namespace my {
class Ship : public my::Actor, public my::Observer<const char*, const std::shared_ptr<my::Actor>&> {
    using super = my::Actor;
public:
    enum class MotionType {
        Default,
        V4,
        CountMax,
    };
private:
    //! 有効化
    bool _enable;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Ship();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Ship();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="type"></param>
    /// <param name="ptr"></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEnable(void) const;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="builder"></param>
    virtual void Construct(const std::shared_ptr<class IBuilder>& builder) override;
};
}
#endif // !MY_SHIP_H