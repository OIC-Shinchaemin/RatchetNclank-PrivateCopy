#ifndef MY_GAME_PAUSE_SYSTEM_H
#define MY_GAME_PAUSE_SYSTEM_H


#include "GameSystem.h"


namespace my {
class GamePauseSystemMenu;
class GamePauseSystem : public my::GameSystem {
    using super = my::GameSystem;
    using this_type = my::GamePauseSystem;
public:
    struct Info {
        bool enter = false;
        bool exit = false;
        int index = 0;
    };
private:
    //! 情報
    this_type::Info _infomation;
    //! 通知用
    my::Observable<const this_type::Info&> _info_subject;
    //! インデックス
    int _item_index;
    //! UI地蔵
    my::UICreator<class GamePauseSystemMenu> _ui_creator;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GamePauseSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GamePauseSystem();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    [[nodiscard]] virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_GAME_PAUSE_SYSTEM_H