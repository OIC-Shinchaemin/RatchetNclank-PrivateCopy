#include "LoadProject.h"
#include "Define.h"
#include "My/Core/Utility.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>‚¢‚Ì‚¤‚¦,2021/03/26</created>
/// <changed>‚¢‚Ì‚¤‚¦,2021/03/26</changed>
// ********************************************************************************
bool LoadProject::Action(std::any any) {

    LoadData* save_data = std::any_cast<LoadData*>(any);
    if (save_data == nullptr) {
        return false;
    }

    const std::string&   file_name = std::get<0>(*save_data);
    rapidjson::Document* buffer    = std::get<1>(*save_data);

    if (!ut::ParseJsonDocument(file_name.c_str(), *buffer)) {
        return false;
    }

    return true;
}
