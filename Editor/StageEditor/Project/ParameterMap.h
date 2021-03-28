#pragma once
#include "Singleton.h"
#include "MofImGui/MofImGui.h"
#include <unordered_map>

// ********************************************************************************
/// <summary>
/// Gui��ł�����l���Ǘ�����N���X
/// </summary>
// ********************************************************************************
template<class T >
class ParameterMap : public Singleton<ParameterMap<T>> {
private:
    
    //! �p�����[�^�}�b�v
    std::unordered_map<std::string, T*> _parameter_map;

public:

    // ********************************************************************************
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    ParameterMap(void) = default;

    // ********************************************************************************
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    ~ParameterMap(void) = default;

    // ********************************************************************************
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="key">�o�^����L�[</param>
    /// <param name="data">�o�^����f�[�^�|�C���^</param>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    void Set(const std::string& key, T* data) {
        _parameter_map[key] = data;
    }

    // ********************************************************************************
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="key">�擾����l�̃L�[</param>
    /// <returns>�f�[�^�|�C���^, nullptr : ���s</returns>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
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