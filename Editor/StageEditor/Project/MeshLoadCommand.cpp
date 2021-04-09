#include "MeshLoadCommand.h"
#include "MeshWindow.h"
#include "FileDialog.h"
#include "ParameterMap.h"

MeshLoadCommand::MeshLoadCommand(const std::string& key, const std::string& file) 
    : _file_name(file)
    , _key_name(key) {
}

void MeshLoadCommand::Register(void) {
}

void MeshLoadCommand::Exec(void) {
    if (MeshAsset::GetAsset(_key_name)) {
        MeshAsset::Erase(_key_name);
    }
    std::string* resource_path = ParameterMap<std::string>::GetInstance().Get("resource_path");
    std::string  path          = *resource_path + "/" + _file_name;
    MeshAsset::Load(_key_name, path.c_str());
    std::string                   key  = FileDialog::GetFileName(_file_name.c_str());
    std::weak_ptr<CMeshContainer> mesh = MeshAsset::GetAsset(_key_name);
    MeshData                      data(key, mesh);
    MeshWindow::GetInstance().AddMeshList(&data);
}

void MeshLoadCommand::Undo(void) {
    MeshWindow::GetInstance().MeshRelease();
}

const std::string MeshLoadCommand::GetName(void) const {
    return "MeshLoadCommand";
}
