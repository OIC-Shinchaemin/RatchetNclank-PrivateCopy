#ifndef RATCHET_GAMEPAD_H
#define RATCHET_GAMEPAD_H


#include <memory>

#include <Mof.h>


namespace ratchet {
class Gamepad {
private:
    //! 初期化フラグ
    bool _initialized;
    //! ゲームパッド
    std::shared_ptr<Mof::CXGamePad>_gamepad;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Gamepad();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Gamepad();
public:
    /// <summary>
    /// シングルトン
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static ratchet::Gamepad& GetInstance(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CXGamePad>GetGamepad(void) const;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Create(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void RefreshKey(void);
};
}
#define g_pGamepad ratchet::Gamepad::GetInstance().GetGamepad()
#endif // !RATCHET_GAMEPAD_H