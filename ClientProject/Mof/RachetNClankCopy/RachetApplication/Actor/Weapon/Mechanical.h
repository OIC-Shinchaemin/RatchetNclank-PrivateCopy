#ifndef MY_MECHANICAL_H
#define MY_MECHANICAL_H


#include "Weapon.h"


namespace my {
class Mechanical : public my::Weapon {
    using super = my::Weapon;
protected:
    //! 速さ
    float _shot_speed;
    //! 間隔
    float _interval;
    //! 間隔
    float _interval_max;
    //! サイズ
    int _bullet_count;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Mechanical();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Mechanical();
    /// <summary>
    /// 入力判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsAction(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool CanFire(void) const;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 発射
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Fire(const def::Transform& transform);
};
}
#endif // !MY_MECHANICAL_H