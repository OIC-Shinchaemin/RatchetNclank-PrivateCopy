#ifndef RATCHET_RESOURCE_MANAGER_H
#define RATCHET_RESOURCE_MANAGER_H


#include <tuple>
#include <string>
#include <unordered_map>
#include <mutex>

#include <Mof.h>

#include "Base/Core/AbstructContainer.h"
#include "Base/Resource/ResourceFont.h"
#include "MotionNames.h"


namespace ratchet {
	template<typename...Types>
	class ResourceManager {
	private:
		//! コンテナ
		std::tuple<base::core::AbstructContainer<
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
		base::core::AbstructContainer<std::unordered_map,
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
			_resources() {
		}
		~ResourceManager() {
		}
		/// <summary>
		/// 読み込み
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		bool Load(const char* path) {
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
					this->AddSharedElement<Mof::CTexture>(data_path.c_str());
				} // else if
				else if (auto format = std::strstr(data_path.c_str(), ".jpg"); format) {
					this->AddSharedElement<Mof::CTexture>(data_path.c_str());
				} // else if
				else if (auto format = std::strstr(data_path.c_str(), ".mom"); format) {
					this->AddSharedElement<Mof::CMeshContainer>(data_path.c_str());
				} // else if
				else if (auto format = std::strstr(data_path.c_str(), ".motion_names"); format) {
					this->AddSharedElement<ratchet::MotionNames>(data_path.c_str());
				} // else if
				else if (auto format = std::strstr(data_path.c_str(), ".ttf"); format) {
					this->AddSharedElement<sip::CResourceFont>(data_path.c_str());
				} // else if
				else if (auto format = std::strstr(data_path.c_str(), ".mp3"); format) {
					if (temp.find("bgm/") != std::string::npos) {
						this->AddSharedElement<Mof::CStreamingSoundBuffer>(data_path.c_str());
					} // if
					else if (temp.find("se/") != std::string::npos) {
						this->AddSharedElement<Mof::CSoundBuffer>(data_path.c_str());
					} // else if
				} // else if
			} // for
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
#endif // !RATCHET_RESOURCE_MANAGER_H