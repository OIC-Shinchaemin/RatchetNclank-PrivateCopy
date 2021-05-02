#ifndef MY_RESOURCE_MANAGER_H
#define MY_RESOURCE_MANAGER_H


#include <tuple>
#include <string>
#include <unordered_map>
#include <mutex>

#include <Mof.h>

#include "my/Core/AbstructContainer.h"
#include "MotionNames.h"


namespace my {
template<typename...Types>
class ResourceManager {
private:
    //! 読み込まれたか
    bool _is_loaded;
    //! 同期
    std::mutex _mutex;
    //! コンテナ
    std::tuple<my::AbstructContainer<
        std::unordered_map,
        std::string,
        Types,
        std::hash<std::string>,
        std::equal_to<std::string>,
        std::allocator<std::pair<const std::string, Types>>>...> _resources;
    /// <summary>
    /// shared_ptrの要素追加
    /// </summary>
    /// <typeparam name="T">型</typeparam>
    /// <param name="">パス</param>
    /// <returns>成功</returns>
    template<class T>
    bool AddSharedElement(const char* path) {
        auto ptr = std::make_shared<T>();
        if (!ptr->Load(path)) {
            ptr.reset();
            return false;
        } // if
        this->Set<std::shared_ptr<T>>(path, ptr);
        return true;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns>アドレス</returns>
    template<class T>
    my::AbstructContainer<std::unordered_map,
        std::string,
        T,
        std::hash<std::string>,
        std::equal_to<std::string>,
        std::allocator<std::pair<const std::string, T> >>&GetContainer(void) {
        constexpr int index = ty::tuple_index<std::tuple<Types...>, T>::value;
        return std::get<index>(_resources);
    }
    /// <summary>
    /// コンテナの解放
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="t"></param>
    template <size_t N = 0, typename T>
    void Release(T& t) {
        if constexpr (N < std::tuple_size<T>::value) {
            auto& x = std::get<N>(t);
            x.Release();
            this->Release<N + 1>(t);
        } // if
    }

public:
    ResourceManager() :
        _is_loaded(false),
        _mutex(),
        _resources() {
    }
    ~ResourceManager() {
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns>完了フラグ</returns>
    bool IsLoaded(void) {
        std::lock_guard<std::mutex> lock(_mutex);
        return this->_is_loaded;
    }
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path) {
        _is_loaded = false;

        std::ifstream stream(path);
        std::vector<std::string> paths;

        // 読み込むファイルのパスを格納
        while (stream) {
            std::string buffer;
            std::getline(stream, buffer);
            paths.push_back(buffer);
        } // while

        // 読み込む
        for (auto& temp : paths) {
            auto& data_path = temp;
            if (auto format = std::strstr(data_path.c_str(), ".png"); format) {
                bool success = this->AddSharedElement<Mof::CTexture>(data_path.c_str());
                //std::cout << "Mof::CTexture success = " << success << "\n";
            } // else if
            else if (auto format = std::strstr(data_path.c_str(), ".jpg"); format) {
                bool success = this->AddSharedElement<Mof::CTexture>(data_path.c_str());
                //std::cout << "Mof::CTexture success = " << success << "\n";
            } // else if
            else if (auto format = std::strstr(data_path.c_str(), ".mom"); format) {
                bool success = this->AddSharedElement<Mof::CMeshContainer>(data_path.c_str());
                //std::cout << "Mof::CMeshContainer success = " << success << "\n";
            } // else if
            else if (auto format = std::strstr(data_path.c_str(), ".motion_names"); format) {
                bool success = this->AddSharedElement<my::MotionNames>(data_path.c_str());
                //std::cout << "Mof::MotionNames success = " << success << "\n";
            } // else if
        } // for
        _is_loaded = true;
        return true;
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void) {
        this->Release(_resources);
        return true;
    }
    /// <summary>
    /// セット
    /// </summary>
    /// <typeparam name="T">型</typeparam>
    /// <param name="key">キー</param>
    /// <param name="value">値</param>
    template<class T>
    void Set(const char* key, const T& value) {
        auto& container = this->GetContainer<T>();
        container.Add(key, value);
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="T">型</typeparam>
    /// <param name="key">キー</param>
    /// <returns></returns>
    template<class T>
    T Get(const char* key) {
        auto& container = this->GetContainer<T>();
        return container.Find(key);
    }
};
}
#endif // !MY_RESOURCE_MANAGER_H