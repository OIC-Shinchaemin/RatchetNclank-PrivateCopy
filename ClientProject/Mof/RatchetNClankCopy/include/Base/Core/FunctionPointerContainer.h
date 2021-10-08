#ifndef BASE_CORE_FUNCTION_POINTER_CONTAINER_H
#define BASE_CORE_FUNCTION_POINTER_CONTAINER_H


#include <tuple>
#include <string>
#include <unordered_map>

#include "Trait.h"


namespace base::core {
template<typename...FuncPtrs>
class FunctionPointerContainer {
private:
    //! �R���e�i
    std::tuple<std::unordered_map<std::string, FuncPtrs>...> _function_pointers;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <typeparam name="FuncPtrType"></typeparam>
    /// <param name=""></param>
    /// <returns>�A�h���X</returns>
    template<class FuncPtrType>
    std::unordered_map<std::string, FuncPtrType>& GetContainer(void) {
        constexpr int index = ty::tuple_index<std::tuple<FuncPtrs...>, FuncPtrType>::value;
        return std::get<index>(_function_pointers);
    }
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FunctionPointerContainer() :
        _function_pointers() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FunctionPointerContainer() {
    }
    /// <summary>
    /// �o�^
    /// </summary>
    /// <typeparam name="FuncPtrType">�^</typeparam>
    /// <param name="key">�L�[</param>
    /// <param name="value">�l</param>
    template<class FuncPtrType>
    void Register(const char* key, const FuncPtrType& value) {
        auto& container = this->GetContainer<FuncPtrType>();
        container.emplace(key, value);
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <typeparam name="FuncPtrType">�^</typeparam>
    /// <param name="key">�L�[</param>
    /// <returns></returns>
    template<class FuncPtrType>
    FuncPtrType Get(const char* key) {
        auto& container = this->GetContainer<FuncPtrType>();
        return container.at(key);
    }
};
}
#endif // !BASE_CORE_FUNCTION_POINTER_CONTAINER_H