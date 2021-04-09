#pragma once
#include "Mof.h"
#include <unordered_map>

// ********************************************************************************
/// <summary>
/// アセットのベースクラス
/// </summary>
// ********************************************************************************
template <typename Key, typename T > class AssetBase {
private:
    // operator= の削除
    void operator= (const AssetBase<Key,T>&) = delete;

    //! マップ
    std::unordered_map<Key, std::shared_ptr<T>> _asset_map; 

    // ********************************************************************************
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <created>いのうえ,2020/04/26</created>
    /// <changed>いのうえ,2020/04/26</changed>
    // ********************************************************************************
    AssetBase(void)
        : _asset_map() {
    }

    // ********************************************************************************
    /// <summary>
    /// マップの取得
    /// </summary>
    /// <returns>マップ</returns>
    /// <created>いのうえ,2020/04/26</created>
    /// <changed>いのうえ,2020/04/26</changed>
    // ********************************************************************************
    static AssetBase<Key,T>& GetAssetMap(void) {
        static AssetBase<Key,T> asset_map;
        return asset_map;
    }

public:

    // ********************************************************************************
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <created>いのうえ,2020/04/26</created>
    /// <changed>いのうえ,2020/04/26</changed>
    // ********************************************************************************
    ~AssetBase(void) {
        Release();
    }

    // ********************************************************************************
    /// <summary>
    /// アセットの登録。
    /// </summary>
    /// <param name="key">検索用キー</param>
    /// <param name="fileName">ファイル名</param>
    /// <returns>登録が成功すれば true それ以外 false</returns>
    /// <created>いのうえ,2020/04/26</created>
    /// <changed>いのうえ,2020/11/11</changed>
    // ********************************************************************************
    static bool Load(const Key& key, LPCMofChar fileName) {
        // 存在するかの検索。
        if (GetAssetMap()._asset_map.find(key) == GetAssetMap()._asset_map.end() ||
            GetAssetMap()._asset_map[key] == nullptr)
        {
            // 存在しない場合はポインタを作成する。
            GetAssetMap()._asset_map[key] = std::make_shared<T>();
        }
        // アセットの読み込みを行う。
        return GetAssetMap()._asset_map[key]->Load(fileName);
    }

    // ********************************************************************************
    /// <summary>
    /// 登録したキーからアセットの取得。
    /// </summary>
    /// <param name="key">キー</param>
    /// <returns>データを返す。データがない場合 empty を返す。</returns>
    /// <created>いのうえ,2020/04/26</created>
    /// <changed>いのうえ,2020/04/26</changed>
    // ********************************************************************************
    static std::shared_ptr<T> GetAsset(const Key& key) {
        return GetAssetMap()._asset_map[key];
    }

    // ********************************************************************************
    /// <summary>
    /// アセットの取得。
    /// </summary>
    /// <returns>全データ</returns>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    static std::unordered_map<Key, std::shared_ptr<T>>& GetAsset(void) {
        return GetAssetMap()._asset_map;
    }

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    /// <created>いのうえ,2021/03/31</created>
    /// <changed>いのうえ,2021/03/31</changed>
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
    /// <created>いのうえ,2021/03/30</created>
    /// <changed>いのうえ,2021/03/30</changed>
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
    /// マップからキーのデータを削除する。
    /// </summary>
    /// <param name="key">検索用キー</param>
    /// <created>いのうえ,2020/09/10</created>
    /// <changed>いのうえ,2020/09/10</changed>
    // ********************************************************************************
    static void Erase(const Key& key) {
        Release(key);
        GetAssetMap()._asset_map.erase(key);
    }

    // ********************************************************************************
    /// <summary>
    /// 指定データの解放。
    /// </summary>
    /// <param name="key">開放するデータのキー</param>
    /// <created>いのうえ,2020/04/26</created>
    /// <changed>いのうえ,2020/11/11</changed>
    // ********************************************************************************
    static void Release(const Key& key) {
        if (GetAssetMap()._asset_map[key]) {
            GetAssetMap()._asset_map[key]->Release();
        }
    }

    // ********************************************************************************
    /// <summary>
    /// 全データの解放。
    /// </summary>
    /// <created>いのうえ,2020/04/26</created>
    /// <changed>いのうえ,2020/09/10</changed>
    // ********************************************************************************
    static void Release(void) {
        for (auto& itr : GetAssetMap()._asset_map) {
            if (itr.second) {
                itr.second->Release();
            }
        }
    }
};