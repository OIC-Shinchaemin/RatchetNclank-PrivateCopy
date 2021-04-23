#pragma once
#include <any>
#include <unordered_map>
#include <string>
#include <optional>
#include "ParameterKey.h"

using ParameterMap = std::unordered_map<std::string, std::any>;

class EditorParameter {
private:

	ParameterMap _map;

	EditorParameter(void) = default;

public:
	
	~EditorParameter(void) = default;

	static EditorParameter& GetInstance(void) {
		static EditorParameter instance;
		return instance;
	}

	ParameterMap& GetMap(void) {
		return _map;
	}

	EditorParameter& Add(std::string key, std::any data) {
		_map[key] = data;
		return *this;
	}

	template<typename T>
	std::optional<T*> GetData(const std::string& key) {
		if (_map.find(key) != _map.end()) {
			if (T* data = std::any_cast<T*>(_map[key])) {
				return data;
			}
		}
		return std::nullopt;
	}
};

#define theParam EditorParameter::GetInstance()