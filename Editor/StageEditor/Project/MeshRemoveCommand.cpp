#include "MeshRemoveCommand.h"
#include "MeshWindow.h"
#include "ParameterMap.h"
#include "FileDialog.h"

MeshRemoveCommand::MeshRemoveCommand(void) 
    : _key("")
    , _file_name("") 
    , _insert_point(0) {
    std::string*                     resource_path = ParameterMap<std::string>::GetInstance().Get("resource_path");
    std::shared_ptr<CMeshContainer>& mesh          = MeshWindow::GetInstance().GetSelectMeshData()->second.lock();
    _key          = MeshAsset::GetKey(mesh);
    _file_name    = (*resource_path) + "\\" + _key;
    _insert_point = MeshWindow::GetInstance().GetSelectNo();
}

void MeshRemoveCommand::Register(void) {
}

void MeshRemoveCommand::Exec(void) {
    MeshWindow::GetInstance().MeshRelease();
}

void MeshRemoveCommand::Undo(void) {
    MeshList::iterator it = MeshWindow::GetInstance().GetMeshList().begin();
    if (MeshAsset::GetAsset(_key)) {
        MeshAsset::Erase(_key);
    }
    MeshAsset::Load(_key, _file_name.c_str());
    std::string                   key  = FileDialog::GetFileName(_file_name.c_str());
    std::weak_ptr<CMeshContainer> mesh = MeshAsset::GetAsset(_key);
    MeshData                      data(key, mesh);
    MeshWindow::GetInstance().GetMeshList().insert(it + _insert_point, data);
    MeshWindow::GetInstance().SetSelectNo(_insert_point);
}

const std::string MeshRemoveCommand::GetName(void) const {
    return "MeshRemoveCommand";
}
