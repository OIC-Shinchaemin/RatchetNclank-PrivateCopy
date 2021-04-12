#pragma once
#include "Mof.h"
#include <unordered_map>

// ********************************************************************************
/// <summary>
/// �A�Z�b�g�̃x�[�X�N���X
/// </summary>
// ********************************************************************************
template <typename Key, typename T > class AssetBase {
private:
    // operator= �̍폜
    void operator= (const AssetBase<Key,T>&) = delete;

    //! �}�b�v
    std::unordered_map<Key, std::shared_ptr<T>> _asset_map; 

    // ********************************************************************************
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <created>���̂���,2020/04/26</created>
    /// <changed>���̂���,2020/04/26</changed>
    // ********************************************************************************
    AssetBase(void)
        : _asset_map() {
    }

    // ********************************************************************************
    /// <summary>
    /// �}�b�v�̎擾
    /// </summary>
    /// <returns>�}�b�v</returns>
    /// <created>���̂���,2020/04/26</created>
    /// <changed>���̂���,2020/04/26</changed>
    // ********************************************************************************
    static AssetBase<Key,T>& GetAssetMap(void) {
        static AssetBase<Key,T> asset_map;
        return asset_map;
    }

public:

    // ********************************************************************************
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <created>���̂���,2020/04/26</created>
    /// <changed>���̂���,2020/04/26</changed>
    // ********************************************************************************
    ~AssetBase(void) {
        Release();
    }

    // ********************************************************************************
    /// <summary>
    /// �A�Z�b�g�̓o�^�B
    /// </summary>
    /// <param name="key">�����p�L�[</param>
    /// <param name="fileName">�t�@�C����</param>
    /// <returns>�o�^����������� true ����ȊO false</returns>
    /// <created>���̂���,2020/04/26</created>
    /// <changed>���̂���,2020/11/11</changed>
    // ********************************************************************************
    static bool Load(const Key& key, LPCMofChar fileName) {
        // ���݂��邩�̌����B
        if (GetAssetMap()._asset_map.find(key) == GetAssetMap()._asset_map.end() ||
            GetAssetMap()._asset_map[key] == nullptr)
        {
            // ���݂��Ȃ��ꍇ�̓|�C���^���쐬����B
            GetAssetMap()._asset_map[key] = std::make_shared<T>();
        }
        // �A�Z�b�g�̓ǂݍ��݂��s���B
        return GetAssetMap()._asset_map[key]->Load(fileName);
    }

    // ********************************************************************************
    /// <summary>
    /// �o�^�����L�[����A�Z�b�g�̎擾�B
    /// </summary>
    /// <param name="key">�L�[</param>
    /// <returns>�f�[�^��Ԃ��B�f�[�^���Ȃ��ꍇ empty ��Ԃ��B</returns>
    /// <created>���̂���,2020/04/26</created>
    /// <changed>���̂���,2020/04/26</changed>
    // ********************************************************************************
    static std::shared_ptr<T> GetAsset(const Key& key) {
        return GetAssetMap()._asset_map[key];
    }

    // ********************************************************************************
    /// <summary>
    /// �A�Z�b�g�̎擾�B
    /// </summary>
    /// <returns>�S�f�[�^</returns>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    static std::unordered_map<Key, std::shared_ptr<T>>& GetAsset(void) {
        return GetAssetMap()._asset_map;
    }

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    /// <created>���̂���,2021/03/31</created>
    /// <changed>���̂���,2021/03/31</changed>
    // ********************************************************************************
    static int GetUseCount(const Key& key) {
        return GetAssetMap()._asset_map[key].use_count();
    }

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <param name="std::shared_ptr<T>"></param>
    /// <returns></returns>
    /// <created>���̂���,2021/03/30</created>
    /// <changed>���̂���,2021/03/30</changed>
    // ********************************************************************************
    static Key GetKey(const std::shared_ptr<T>& ptr) {
        auto data = std::find_if(
            GetAssetMap()._asset_map.begin(), GetAssetMap()._asset_map.end(),
            [&](const std::pair<Key, std::shared_ptr<T>>& obj) { return obj.second == ptr; }
        );
        return data->first;
    }

    // ********************************************************************************
    /// <summary>
    /// �}�b�v����L�[�̃f�[�^���폜����B
    /// </summary>
    /// <param name="key">�����p�L�[</param>
    /// <created>���̂���,2020/09/10</created>
    /// <changed>���̂���,2020/09/10</changed>
    // ********************************************************************************
    static void Erase(const Key& key) {
        Release(key);
        GetAssetMap()._asset_map.erase(key);
    }

    // ********************************************************************************
    /// <summary>
    /// �w��f�[�^�̉���B
    /// </summary>
    /// <param name="key">�J������f�[�^�̃L�[</param>
    /// <created>���̂���,2020/04/26</created>
    /// <changed>���̂���,2020/11/11</changed>
    // ********************************************************************************
    static void Release(const Key& key) {
        if (GetAssetMap()._asset_map[key]) {
            GetAssetMap()._asset_map[key]->Release();
        }
    }

    // ********************************************************************************
    /// <summary>
    /// �S�f�[�^�̉���B
    /// </summary>
    /// <created>���̂���,2020/04/26</created>
    /// <changed>���̂���,2020/09/10</changed>
    // ********************************************************************************
    static void Release(void) {
        for (auto& itr : GetAssetMap()._asset_map) {
            if (itr.second) {
                itr.second->Release();
            }
        }
    }
};