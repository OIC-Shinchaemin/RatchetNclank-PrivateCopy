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
    //! �L����
    bool _enable;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Ship();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Ship();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="type"></param>
    /// <param name="ptr"></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEnable(void) const;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="builder"></param>
    virtual void Construct(const std::shared_ptr<class IBuilder>& builder) override;
};
}
#endif // !MY_SHIP_H