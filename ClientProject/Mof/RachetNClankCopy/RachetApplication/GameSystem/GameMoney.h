#ifndef MY_GAME_MONEY_H
#define MY_GAME_MONEY_H


#include <memory>
#include <string>

#include <Mof.h>

#include "../ResourceLocator.h"


namespace my {
class GameMoney : public my::ResourceLocator {
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
    //State _state;
    //! アルファ
    //float _alpha;
    
    uint32_t _value;
    //! フォント
    Mof::CFont _font;
    //! フォント
    std::size_t _font_size;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameMoney();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameMoney();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::uint32_t GetValue(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    bool Initialize(uint32_t value);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    bool Render(void);
};
}
#endif // !MY_GAME_MONEY_H