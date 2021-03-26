#ifndef MY_QUICK_CHANGE_SYSTEM_H
#define MY_QUICK_CHANGE_SYSTEM_H


#include <Mof.h>

#include "ResourceLocator.h"


namespace my {
class QuickChangeItem {
};
class QuickChangeSystem : public my::ResourceLocator {
    enum class State {
        Enter,
        Exit
    };
private:
    //! 名前
    std::string _name;
    //! 背景
    std::weak_ptr<Mof::CTexture> _texture;
    //! 位置
    Mof::CVector2 _position;
    //! 色
    Mof::CVector4 _color;
    //! 状態
    State _state;
    //! アルファ
    float _alpha;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    QuickChangeSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~QuickChangeSystem();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    bool Initialize(Mof::CVector2 pos);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    bool Render(void);
};
}
#endif // !MY_QUICK_CHANGE_SYSTEM_H