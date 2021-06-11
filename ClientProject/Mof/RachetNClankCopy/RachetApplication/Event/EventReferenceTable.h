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
    /// �R���X�g���N�^
    /// </summary>
    EventReferenceTable();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EventReferenceTable();
public:
    /// <summary>
    /// �V���O���g��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static rachet::EventReferenceTable& Singleton(void);
    /// <summary>
    /// �擾
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    std::any At(const std::string& key);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="key"></param>
    /// <returns></returns>
    template<typename Type>
    Type Get(const std::string& key) {
        return std::any_cast<Type>(this->At(key));
    }
    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    void Register(const std::string& key, std::any value);
    /// <summary>
    /// �j��
    /// </summary>
    /// <param name="key"></param>
    void Dispose(const std::string& key);
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !RACHET_EVENT_REFERENCE_TABLE_H