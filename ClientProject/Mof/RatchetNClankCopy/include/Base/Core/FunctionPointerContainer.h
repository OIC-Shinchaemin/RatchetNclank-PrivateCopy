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
    //! コンテナ
    std::tuple<std::unordered_map<std::string, FuncPtrs>...> _function_pointers;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="FuncPtrType"></typeparam>
    /// <param name=""></param>
    /// <returns>アドレス</returns>
    template<class FuncPtrType>
    std::unordered_map<std::string, FuncPtrType>& GetContainer(void) {
        constexpr int index = ty::tuple_index<std::tuple<FuncPtrs...>, FuncPtrType>::value;
        return std::get<index>(_function_pointers);
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FunctionPointerContainer() :
        _function_pointers() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FunctionPointerContainer() {
    }
    /// <summary>
    /// 登録
    /// </summary>
    /// <typeparam name="FuncPtrType">型</typeparam>
    /// <param name="key">キー</param>
    /// <param name="value">値</param>
    template<class FuncPtrType>
    void Register(const char* key, const FuncPtrType& value) {
        auto& container = this->GetContainer<FuncPtrType>();
        container.emplace(key, value);
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="FuncPtrType">型</typeparam>
    /// <param name="key">キー</param>
    /// <returns></returns>
    template<class FuncPtrType>
    FuncPtrType Get(const char* key) {
        auto& container = this->GetContainer<FuncPtrType>();
        return container.at(key);
    }
};
}
#endif // !BASE_CORE_FUNCTION_POINTER_CONTAINER_H