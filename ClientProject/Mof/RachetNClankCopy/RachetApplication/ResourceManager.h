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
    //! �ǂݍ��܂ꂽ��
    bool _is_loaded;
    //! ����
    std::mutex _mutex;
    //! �R���e�i
    std::tuple<my::AbstructContainer<
        std::unordered_map,
        std::string,
        Types,
        std::hash<std::string>,
        std::equal_to<std::string>,
        std::allocator<std::pair<const std::string, Types>>>...> _resources;
    /// <summary>
    /// shared_ptr�̗v�f�ǉ�
    /// </summary>
    /// <typeparam name="T">�^</typeparam>
    /// <param name="">�p�X</param>
    /// <returns>����</returns>
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
    /// �Q�b�^�[
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns>�A�h���X</returns>
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
    /// �R���e�i�̉��
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns>�����t���O</returns>
    bool IsLoaded(void) {
        std::lock_guard<std::mutex> lock(_mutex);
        return this->_is_loaded;
    }
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path) {
        _is_loaded = false;

        std::ifstream stream(path);
        std::vector<std::string> paths;

        // �ǂݍ��ރt�@�C���̃p�X���i�[
        while (stream) {
            std::string buffer;
            std::getline(stream, buffer);
            paths.push_back(buffer);
        } // while

        // �ǂݍ���
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
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void) {
        this->Release(_resources);
        return true;
    }
    /// <summary>
    /// �Z�b�g
    /// </summary>
    /// <typeparam name="T">�^</typeparam>
    /// <param name="key">�L�[</param>
    /// <param name="value">�l</param>
    template<class T>
    void Set(const char* key, const T& value) {
        auto& container = this->GetContainer<T>();
        container.Add(key, value);
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <typeparam name="T">�^</typeparam>
    /// <param name="key">�L�[</param>
    /// <returns></returns>
    template<class T>
    T Get(const char* key) {
        auto& container = this->GetContainer<T>();
        return container.Find(key);
    }
};
}
#endif // !MY_RESOURCE_MANAGER_H