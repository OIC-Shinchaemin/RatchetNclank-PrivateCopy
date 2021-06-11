#ifndef RACHET_EVENT_REFERENCE_TABLE_H
#define RACHET_EVENT_REFERENCE_TABLE_H


#include <any>
#include <memory>
#include <string>
#include <unordered_map>


namespace rachet {
class EventReferenceTable : public std::enable_shared_from_this<rachet::EventReferenceTable> {
private:
    std::unordered_map<std::string, std::any> _data_table;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EventReferenceTable();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EventReferenceTable();
public:
    /// <summary>
    /// シングルトン
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static rachet::EventReferenceTable& Singleton(void);
    /// <summary>
    /// 取得
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    std::any At(const std::string& key);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="key"></param>
    /// <returns></returns>
    template<typename Type>
    Type Get(const std::string& key) {
        return std::any_cast<Type>(this->At(key));
    }
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    void Register(const std::string& key, std::any value);
    /// <summary>
    /// 破棄
    /// </summary>
    /// <param name="key"></param>
    void Dispose(const std::string& key);
    /// <summary>
    /// リセット
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !RACHET_EVENT_REFERENCE_TABLE_H