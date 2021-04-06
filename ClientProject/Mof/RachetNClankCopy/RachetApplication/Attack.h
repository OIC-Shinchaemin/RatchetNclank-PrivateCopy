#ifndef MY_ATTACK_H
#define MY_ATTACK_H


#include <Mof.h>


namespace my {
class Attack {
private:
    //! 所有者
    std::weak_ptr<class Enemy> _owner;
    //! 攻撃範囲
    float _range;
    //! サイズ
    float _volume;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Attack();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Attack();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="owner"></param>
    void SetOwner(const std::shared_ptr<class Enemy>& owner);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRange(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetVolume(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetSphere(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetRangeSphere(void) const;
    /// <summary>
    /// アクション
    /// </summary>
    /// <param name=""></param>
    void Start(void);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void);
};
}
#endif // !MY_ATTACK_H