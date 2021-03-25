#ifndef MY_ACTOR_H
#define MY_ACTOR_H


#include <memory>
#include <string>

#include <Mof.h>

#include "My/Core/Define.h"


namespace my {
class Actor : public std::enable_shared_from_this<my::Actor> {
private:
    //! トランスフォーム
    def::Transform _transform;
public:    
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Actor();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Actor();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector3 position);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="rotate"></param>
    void SetRotate(Mof::CVector3 rotate);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>名前</returns>
    std::string GetName(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetRotate(void) const;
};
}
#endif // !MY_ACTOR_H