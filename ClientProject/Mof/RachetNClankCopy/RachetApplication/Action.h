#ifndef MY_ACTION_H
#define MY_ACTION_H


#include <memory>


namespace my {
class Action : public std::enable_shared_from_this<my::Action> {
protected:
    //! 所有者
    std::weak_ptr<class Enemy> _owner;
    //! 有効
    bool _active;
    //! 更新順
    int _priority;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool InactiveCondition(void) const = 0;
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Execute(float delta_time) = 0;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Action();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Action();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="owner"></param>
    void SetOwner(const std::shared_ptr<class Enemy>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<class Enemy> GetOwner(void) const;
    /// <summary>
    /// 有効判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActive(void) const;
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void);
};
}
#endif // !MY_ACTION_H