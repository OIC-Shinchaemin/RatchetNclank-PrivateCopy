#ifndef BASE_CORE_SERVICE_LOCATOR_H
#define BASE_CORE_SERVICE_LOCATOR_H


#include <memory>


namespace base {
namespace core {
template<class Service>
class ServiceLocator {
private:
    //! サービス
    std::shared_ptr<Service> _service;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <typeparam name="Service"></typeparam>
    ServiceLocator();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ServiceLocator();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetService(const std::shared_ptr<Service>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<Service> GetService(void) const;
};
template<class Service>
inline ServiceLocator<Service>::ServiceLocator() {
}
template<class Service>
inline ServiceLocator<Service>::~ServiceLocator() {
}
template<class Service>
inline void ServiceLocator<Service>::SetService(const std::shared_ptr<Service>& ptr) {
    this->_service = ptr;
}
template<class Service>
inline std::shared_ptr<Service> ServiceLocator<Service>::GetService(void) const {
    return this->_service;
}
}
}
#endif // !BASE_CORE_SERVICE_LOCATOR_H