#include "AddObject.h"
#include "Define.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>いのうえ,2021/03/26</created>
/// <changed>いのうえ,2021/03/26</changed>
// ********************************************************************************
bool AddObject::Action(std::any any) {
    const AddObjectData* data = std::any_cast<AddObjectData*>(any);
    if (data == nullptr) {
        return false;
    }
    const ObjectData* object_data = data->first;
    ObjectList*       object_list = data->second;
    using list_iterator = std::vector<ObjectData>::iterator;
    // 登録する名前
    std::string name = object_data->name;
    // すでに名前があるかの検索関数
    std::function<list_iterator(std::string)> name_find =
        [&](std::string n) {
        return std::find_if(object_list->begin(), object_list->end(), [&](const ObjectData& v) { return v.name == n; });
    };
    // 名前がかぶった場合の番号
    int count = 1;
    for (list_iterator it = name_find(name); it != object_list->end(); count++) {
        name = object_data->name + std::to_string(count);
        it   = name_find(name);
    }
    // データの登録
    ObjectData push_data = *object_data;
    push_data.name       = name;
    object_list->push_back(push_data);
    return true;
}
