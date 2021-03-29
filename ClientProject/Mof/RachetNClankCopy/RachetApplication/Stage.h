#pragma once
#include "Mof.h"
#include <unordered_map>

// ********************************************************************************
/// <summary>
/// 
/// </summary>
// ********************************************************************************
class Stage {
public:
    
    // ********************************************************************************
    /// <summary>
    /// �I�u�W�F�N�g�f�[�^
    /// </summary>
    // ********************************************************************************
    struct ObjectData {
        Vector3                         position     { 0.0f, 0.0f, 0.0f };
        Vector3                         scale        { 1.0f, 1.0f, 1.0f };
        Vector3                         rotation     { 0.0f, 0.0f, 0.0f };
        std::shared_ptr<CMeshContainer> mesh_pointer { nullptr };
        std::string                     name         { "" };

        // ********************************************************************************
        /// <summary>
        /// 
        /// </summary>
        /// <param name="v1"></param>
        /// <param name="v2"></param>
        /// <returns></returns>
        /// <created>���̂���,2021/03/20</created>
        /// <changed>���̂���,2021/03/20</changed>
        // ********************************************************************************
        static bool Compare(const ObjectData& v1, const ObjectData& v2) {
            bool pos_flag    = (v1.position     == v2.position    );
            bool scale_flag  = (v1.scale        == v2.scale       );
            bool rotate_flag = (v1.rotation     == v2.rotation    );
            bool mesh_flag   = (v1.mesh_pointer == v2.mesh_pointer);
            bool name_flag   = (v1.name         == v2.name        );
            return (pos_flag && scale_flag && rotate_flag && mesh_flag && name_flag);
        }
    };

    //! ���O�̒u������
    using MeshPtr       = std::shared_ptr<CMeshContainer>;

    //! vector<ObjectData>
    using ObjectList    = std::vector<ObjectData>;

    //! pair<file_name, mesh_pointer>
    using MeshData      = std::pair<std::string, MeshPtr>;

    //! vector<MeshData>
    using MeshList      = std::vector<MeshData>;

    //! pair<ObjectData*, ObjectList*>
    using AddObjectData = std::pair<ObjectData*, ObjectList*>;

    //! tuple<file_name, MeshList*, ObjectList*>
    using SaveData      = std::tuple<std::string, MeshList*, ObjectList*>;

    //! pair<file_name, file_buffer>
    using LoadData      = std::pair<std::string, std::string*>;

private:

    //! ���b�V���|�C���^�z��
    MeshList   _mesh_array;

    //! �I�u�W�F�N�g�f�[�^�z��
    ObjectList _object_array;

    bool Purse(const std::string* buffer, MeshList* mesh_list, ObjectList* object_list);

    bool LoadMap(std::string* buffer_pointer, const std::string& map_file);

    bool LoadMesh(const std::string& key, const std::string& mesh_file);

    Stage::MeshPtr GetMeshPtr(const std::string& key);

    std::string GetFileName(const std::string& file);

    std::string GetExt(const std::string& file);

    std::string ChangeFullPath(const std::string& file);

    void AddObject(AddObjectData* data);

public:

    void Initialize(void);

    void Update(void);

    void Render(void);

    void Release(void);
};

