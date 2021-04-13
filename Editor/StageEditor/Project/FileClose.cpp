#include "FileClose.h"
#include "Define.h"
#include "ParameterMap.h"

bool FileClose::Action(std::any any) {

    MeshList*    mesh_list   = ParameterMap<MeshList>::GetInstance().Get("mesh_list");
    ObjectList*  object_list = ParameterMap<ObjectList>::GetInstance().Get("object_list");
    std::string* file_name   = ParameterMap<std::string>::GetInstance().Get("open_file_name");

    (*object_list).clear();
    for (const auto& it : *mesh_list) {
        it.second.lock()->Release();
    }
    (*mesh_list).clear();
    *file_name = "";

    MeshAsset::Release();
    return true;
}
