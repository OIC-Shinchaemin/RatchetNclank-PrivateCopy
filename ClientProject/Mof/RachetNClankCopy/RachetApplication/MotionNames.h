#ifndef MY_MOTION_NAMES_H
#define MY_MOTION_NAMES_H


#include <string>
#include <unordered_map>

#include "My/Core/Utility.h"


namespace my {
struct MotionInfo {
    std::string state;
    std::string name;
    float speed = 1.0f;
    bool loop = false;
    bool same = false;
};
struct MotionNames : public std::unordered_map<int, my::MotionInfo> {
    using super = std::unordered_map<int, my::MotionInfo>;
    MotionNames() {
    }
    bool Load(const char* path) {
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return false;
        } // if

        auto& infos = document["info"];
        for (int i = 0, n = infos.Size(); i < n; i++) {
            auto info = my::MotionInfo();
            info.name = infos[i]["name"].GetString();
            info.speed = infos[i]["speed"].GetFloat();
            info.loop = infos[i]["loop"].GetBool();
            info.same = infos[i]["same"].GetBool();
            info.state = infos[i]["state"].GetString();
            this->emplace(i, std::move(info));
        } // for
        return true;
    }
    bool Release(void) {
        super::clear();
        return true;
    }
    template<typename Enum>
    const char* GetName(Enum type) {
        return this->At(type).name.c_str();
    }
    template<typename Enum>
    const char* At(Enum type) {
        return this->at(static_cast<int>(type)).name.c_str();
    } 
};
}
#endif // !MY_MOTION_NAMES_H