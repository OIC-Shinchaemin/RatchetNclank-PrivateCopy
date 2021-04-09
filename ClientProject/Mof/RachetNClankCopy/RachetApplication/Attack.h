#ifndef MY_ATTACK_H
#define MY_ATTACK_H


#include "Action.h"

#include <Mof.h>


namespace my {
class Attack : public my::Action {
    using super = my::Action;
private:
    //! 攻撃範囲
    float _range;
    //! サイズ
    float _volume;
    //! モーションポインタを参照する管理はしない
    Mof::LPMeshMotionController _motion;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool InactiveCondition(void) const override;
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Execute(float delta_time) override;
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
    /// <param name="ptr"></param>
    void SetMotion(Mof::LPMeshMotionController ptr);
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
    Mof::CSphere GetCanAttackRangeSphere(void) const;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// 無効化
    /// </summary>
    void Inactive(void);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void);
};
}
#endif // !MY_ATTACK_H