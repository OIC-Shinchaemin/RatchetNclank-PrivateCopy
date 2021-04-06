#ifndef MY_MOTION_NAMES_H
#define MY_MOTION_NAMES_H


#include <string>
#include <unordered_map>

#include "My/Core/Utility.h"


namespace my {
struct MotionNames : public std::unordered_map<int, std::string> {
    using super = std::unordered_map<int, std::string>;
    MotionNames() {
    }
    bool Load(const char* path) {
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return false;
        } // if

        auto& names = document["names"];
        for (int i = 0, n = names.Size(); i < n; i++) {
            this->emplace(i, names[i].GetString());
        } // for
        return true;
    }
    bool Release(void) {
        return true;
    }

    template<typename Enum>
    const char* GetName(Enum type) {
        return this->At(type);
    }
    template<typename Enum>
    const char* At(Enum type) {
        return this->at(static_cast<int>(type)).c_str();
    }

};
}
#endif // !MY_MOTION_NAMES_H