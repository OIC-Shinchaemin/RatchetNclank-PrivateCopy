#ifndef MY_GAME_PAUSE_SYSTEM_H
#define MY_GAME_PAUSE_SYSTEM_H


#include "GameSystem.h"


namespace my {
class GamePauseSystem : public my::GameSystem {
    using super = my::GameSystem;
    using this_type = my::GamePauseSystem;
public:
    struct Info {
        bool enter = false;
        bool exit = false;
        int index = 0;
        //std::vector<std::shared_ptr<ElemType>>* items = nullptr;
    };
private:
    //! 情報
    this_type::Info _infomation;
    //! 通知用
    my::Observable<const this_type::Info&> _info_subject;
    //! 子供
    //std::vector<std::shared_ptr<ElemType>> _item;
    //! 子供
    //std::vector<std::shared_ptr<ElemType>> _execute_list;
    //! インデックス
    int _item_index;
    //! 通知用
    //my::Observable<const scene::SceneMessage&> _scene_message_subject;
    //! 通知用
    //my::Observable<bool> _title_menu_subject;
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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //my::Observable<const my::scene::SceneMessage&>* GetSceneMessageSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //my::Observable<bool>* GetTitleMenuSubject(void);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="elem"></param>
    /// <returns></returns>
    //void AddItem(const std::shared_ptr<ElemType>& elem);
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