#ifndef RACHET_MECHANICAL_H
#define RACHET_MECHANICAL_H


#include "Weapon.h"


namespace rachet {
class Mechanical : public rachet::Weapon {
    using super = rachet::Weapon;
public:
    struct Info {
        //! 弾数
        int bullet_count;
        //! 弾数
        int bullet_count_max;
        //! 弾数
        std::string name;

        Info() = default;
        Info(int size, int max, const char* str) :
            bullet_count(size), 
            bullet_count_max(max),
            name(str) {
        };
    };
protected:
    //! 速さ
    float _shot_speed;
    //! 間隔
    float _interval;
    //! 間隔
    float _interval_max;
    //! サイズ
    int _bullet_count_max;
    //! サイズ
    int _bullet_count;
    //! 対象位置
    std::optional<Mof::CVector3> _lock_on_position;
    //! 通知用
    base::core::Observable<const rachet::Mechanical::Info&> _subject;
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
    /// セッター
    /// </summary>
    /// <param name="position"></param>
    void SetLockOnPosition(Mof::CVector3 position);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetBulletCount(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetBulletCountMax(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetBulletCountDecrased(void) const;
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
    /// 装填
    /// </summary>
    /// <param name="count"></param>
    void AddBullet(std::uint32_t count);
    /// <summary>
    /// 追加
    /// </summary>
    void AddMechanicalInfoObserver(const std::shared_ptr<base::core::Observer<const rachet::Mechanical::Info&>>& ptr);
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
    /// <summary>
    /// リセット
    /// </summary>
    /// <param name=""></param>
    void ResetTargetPosition(void);
};
}
#endif // !RACHET_MECHANICAL_H