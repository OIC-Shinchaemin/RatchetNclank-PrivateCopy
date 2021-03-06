#include "SaveSystem.h"

#include "Base/Core/Header.h"
#include "Base/Core/Utility.h"


ratchet::game::gamesystem::save::SaveSystem::SaveSystem() :
    _path("../Resource/save/savedata.json") {
}

ratchet::game::gamesystem::save::SaveSystem::~SaveSystem() {
}

bool ratchet::game::gamesystem::save::SaveSystem::Fetch(ratchet::game::gamesystem::save::SaveData& out) {
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(_path.c_str(), document)) {
        return false;
    } // if

    auto savedata_param = ratchet::game::gamesystem::save::SaveDataParam();
    if (document.HasMember("param")) {
        const auto& param = document["param"];
        if (param.HasMember("money")) {
            _ASSERT_EXPR(param["money"].IsInt(), L"指定された型でありません");
            savedata_param.money = param["money"].GetInt();
        } // if
    } // if

    if (document.HasMember("weapons")) {
        const auto& weapons = document["weapons"];
        for (int i = 0, n = weapons.Size(); i < n; i++) {
            /*
            auto it = std::find_if(savedata_param.available_weapons.begin(), savedata_param.available_weapons.end(), [&](const std::string& name) {
                return name == weapons[i].GetString();
            });
            if (it == savedata_param.available_weapons.end()) {
            } // if
            */
            savedata_param.available_weapons.push_back(weapons[i].GetString());
        } // for
    } // if


    out.MoveParam(savedata_param);
    return true;
}

bool ratchet::game::gamesystem::save::SaveSystem::Save(const ratchet::game::gamesystem::save::SaveDataParam& param) {
    rapidjson::Document document(rapidjson::Type::kObjectType);

    rapidjson::Value work(rapidjson::Type::kObjectType);
    work.AddMember("money", param.money, document.GetAllocator());
    document.AddMember("param", work, document.GetAllocator());

    rapidjson::Value weapons(rapidjson::Type::kArrayType);
    for (auto& name : param.available_weapons) {
        auto temp = rapidjson::StringRef(name.c_str(), name.size());
        weapons.PushBack(rapidjson::Value(temp), document.GetAllocator());
    } // for
    document.AddMember("weapons", weapons, document.GetAllocator());

    std::ofstream temp(_path.c_str());
    rapidjson::OStreamWrapper stream(temp);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(stream);
    document.Accept(writer);
    return true;
}