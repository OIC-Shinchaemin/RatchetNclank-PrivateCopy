#ifndef RACHET_GAMEPAD_H
#define RACHET_GAMEPAD_H


#include <memory>

#include <Mof.h>


namespace rachet {
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
    static rachet::Gamepad& GetInstance(void);
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
#define g_pGamepad rachet::Gamepad::GetInstance().GetGamepad()
#endif // !RACHET_GAMEPAD_H