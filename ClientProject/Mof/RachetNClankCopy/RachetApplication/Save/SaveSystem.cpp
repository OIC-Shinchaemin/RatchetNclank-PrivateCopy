#include "SaveSystem.h"

#include "My/Core/Header.h"
#include "My/Core/Utility.h"


my::SaveSystem::SaveSystem() :
    _path("../Resource/save/savedata.json"){
}

my::SaveSystem::~SaveSystem() {
}

bool my::SaveSystem::Fetch(my::SaveData& out) {
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(_path.c_str(), document)) {
        return false;
    } // if

    auto savedata_param = my::SaveDataParam();
    if (document.HasMember("param")) {
        const auto& param = document["param"];
        if (param.HasMember("money")) {
            _ASSERT_EXPR(param["money"].IsInt(), L"Žw’è‚³‚ê‚½Œ^‚Å‚ ‚è‚Ü‚¹‚ñ");
            savedata_param.money = param["money"].GetInt();
        } // if
    } // if
    out.MoveParam(savedata_param);
    return true;
}

bool my::SaveSystem::Save(const my::SaveDataParam& param) {
    rapidjson::Document document(rapidjson::Type::kObjectType);
    rapidjson::Value work(rapidjson::Type::kObjectType);
    work.AddMember("money", param.money, document.GetAllocator());

    document.AddMember("param", work, document.GetAllocator());

    std::ofstream temp(_path.c_str());
    rapidjson::OStreamWrapper stream(temp);

    rapidjson::Writer<rapidjson::OStreamWrapper> writer(stream);
    document.Accept(writer);

    return true;
}