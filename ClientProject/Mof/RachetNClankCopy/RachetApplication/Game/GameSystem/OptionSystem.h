#ifndef MY_OPTION_SYSTEM_H
#define MY_OPTION_SYSTEM_H


#include "GameSystem.h"

namespace my {
class OptionSystemItem : public std::enable_shared_from_this<my::OptionSystemItem> {
    using this_type = my::OptionSystemItem;
private:
    //! テキスト
    std::string _text;
    //! 実行関数
    std::function<bool(void)> _on_enter;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    OptionSystemItem();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    OptionSystemItem(std::function<bool(void)> func);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~OptionSystemItem();
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
    [[nodiscard]]virtual bool Execute(void);
};


class OptionSystem : public my::GameSystem {
    using super = my::GameSystem;
    using this_type = my::OptionSystem;
    using ElemType = my::OptionSystemItem;
public:
    struct Info {
        bool enter = false;
        bool exit = false;
        std::vector<std::shared_ptr<ElemType>>* items;
    };
private:
    //! 情報
    this_type::Info _infomation;
    //! 通知用
    my::Observable<const this_type::Info&> _info_subject;
    //! 子供
    std::vector<std::shared_ptr<ElemType>> _item;
    //! 子供
    std::vector<std::shared_ptr<ElemType>> _execute_list;
    //! インデックス
    int _item_index;
    //! 次
    //std::shared_ptr<this_type> _next;
    //! 次
    //std::shared_ptr<this_type> _next;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    OptionSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~OptionSystem();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="elem"></param>
    /// <returns></returns>
    void AddItem(const std::shared_ptr<ElemType>& elem);
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
#endif // !MY_OPTION_SYSTEM_H