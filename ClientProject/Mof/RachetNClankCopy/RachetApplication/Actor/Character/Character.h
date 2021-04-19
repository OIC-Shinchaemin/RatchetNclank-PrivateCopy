#ifndef MY_CHARACTER_H
#define MY_CHARACTER_H


#include "../../Actor.h"


namespace my {
class Character : public my::Actor {
    using super = my::Actor;
protected:
    //! 大きさ
    float _volume;
    //! 高さ
    float _height;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Character();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Character();
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
    float GetHeight(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetSphere(void) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;
};
}
#endif // !MY_CHARACTER_H