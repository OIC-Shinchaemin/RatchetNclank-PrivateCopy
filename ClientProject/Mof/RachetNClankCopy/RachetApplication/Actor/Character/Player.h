#ifndef MY_PLAYER_H
#define MY_PLAYER_H



#include "Character.h"
#include "My/Core/Observer.h"

#include "../Weapon/Mechanical.h"


namespace my {
class Player : public my::Character, public my::Observer<std::shared_ptr<my::Mechanical>> {
    using super = my::Character;
public:
    enum class MotionType {
        IdleWait,
        MoveRun,
        DamageDown,
        CountMax,
    };
private:
    //! ïêäÌ
    std::weak_ptr<my::Mechanical>_current_mechanical;
public:
    Player();
    ~Player();
    virtual void OnNotify(std::shared_ptr<my::Mechanical> change) override;

    virtual bool Initialize(my::Actor::Param* param) override;
    virtual bool Update(float delta_time) override;
    virtual bool Render(void) override;
    virtual bool Release(void) override;
};
}
#endif // !MY_PLAYER_H