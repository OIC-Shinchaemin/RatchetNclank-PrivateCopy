#ifndef MY_SERVICE_LOCATOR_H
#define MY_SERVICE_LOCATOR_H


#include <memory>


namespace my {
template<class Service>
class ServiceLocator {
private:
    //! �T�[�r�X
    static std::weak_ptr<Service> _service;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<Service> GetService(void) const;
public:
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    static void SetService(const std::shared_ptr<Service>& ptr);
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <typeparam name="Service"></typeparam>
    ServiceLocator();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ServiceLocator();
};
template<class Service>
inline std::shared_ptr<Service> ServiceLocator<Service>::GetService(void) const {
    return _service.lock();
}
template<class Service>
inline void ServiceLocator<Service>::SetService(const std::shared_ptr<Service>& ptr) {
    _service = ptr;
}
template<class Service>
inline ServiceLocator<Service>::ServiceLocator() {
}
template<class Service>
inline ServiceLocator<Service>::~ServiceLocator() {
}
}
#endif // !MY_SERVICE_LOCATOR_H