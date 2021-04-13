#pragma once
#include "Singleton.h"
#include "MofImGui/MofImGui.h"
#include <unordered_map>

// ********************************************************************************
/// <summary>
/// Gui上でいじる値を管理するクラス
/// </summary>
// ********************************************************************************
template<class T >
class ParameterMap : public Singleton<ParameterMap<T>> {
private:
    
    //! パラメータマップ
    std::unordered_map<std::string, T*> _parameter_map;

public:

    // ********************************************************************************
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    ParameterMap(void) = default;

    // ********************************************************************************
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    ~ParameterMap(void) = default;

    // ********************************************************************************
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="key">登録するキー</param>
    /// <param name="data">登録するデータポインタ</param>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    void Set(const std::string& key, T* data) {
        _parameter_map[key] = data;
    }

    // ********************************************************************************
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="key">取得する値のキー</param>
    /// <returns>データポインタ, nullptr : 失敗</returns>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    T* Get(const std::string& key) {
        if (_parameter_map.find(key) == _parameter_map.end()) {
            return nullptr;
        }
        return _parameter_map[key];
    }
};

//#define theParameterMapInt   ParameterMap<int>::GetInstance()
//#define theParameterMapFloat ParameterMap<float>::GetInstance()