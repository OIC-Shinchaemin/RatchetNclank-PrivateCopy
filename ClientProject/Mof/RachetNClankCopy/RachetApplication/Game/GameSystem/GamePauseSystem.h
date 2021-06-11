#ifndef MY_GAME_PAUSE_SYSTEM_H
#define MY_GAME_PAUSE_SYSTEM_H


#include "GameSystem.h"

#include <optional>
#include <memory>
#include <vector>


namespace my {
class GamePauseSystemMenu;
class GamePauseSystemItem : public std::enable_shared_from_this<my::GamePauseSystemItem> {
    using this_type = my::GamePauseSystemItem;
private:
    //! テキスト
    std::string _text;
    //! 実行関数
    std::function<bool(void)> _on_enter;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GamePauseSystemItem();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GamePauseSystemItem(std::function<bool(void)> lambda);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GamePauseSystemItem();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="text"></param>
    void SetText(const char* text);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetText(void) const;
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    [[nodiscard]] virtual bool Execute(void);
};
class GamePauseSystem : public my::GameSystem {
    using super = my::GameSystem;
    using this_type = my::GamePauseSystem;
    using ElemType = my::GamePauseSystemItem;
public:
    struct Info {
        bool enable = false;
        //bool enter = false;
        //bool exit = false;
        //bool push_item = false;
        std::optional<int> index = 0;
        std::vector<std::shared_ptr<ElemType>>* items;
        void Reset(void) {
            enable = false;
            //enter = false;
            //exit = false;
            //push_item = false;
            index.reset();
            ///items = nullptr;
        }
    };
private:
private:
    //! 情報
    this_type::Info _infomation;
    //! 通知用
    base::core::Observable<const this_type::Info&> _info_subject;
    //! 子供
    std::vector<std::shared_ptr<ElemType>> _items;
    //! 子供
    std::vector<std::shared_ptr<ElemType>> _execute_list;
    //! インデックス
    //std::optional<int> _item_index;
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
    base::core::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="elem"></param>
    /// <returns></returns>
    void AddItem(const std::shared_ptr<ElemType>& elem);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActive(void) const;
    /// <summary>
    /// 無効化
    /// </summary>
    /// <param name=""></param>
    void Inactive(void);
    /// <summary>
    /// クリア
    /// </summary>
    /// <param name=""></param>
    void Clear(void);
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