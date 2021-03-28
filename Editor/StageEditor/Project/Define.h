#pragma once
#include "AssetBase.h"

// マウス
#define MOFMOUSE_CENTERBUTTON 2

// Window関係
static constexpr int window_width  = 1280;
static constexpr int window_height =  720;

// カメラ関係
static float camera_move_rotation_ratio  = 0.01f;
static float camera_move_zoom_ratio      = 0.0001f;
static float camera_move_zoom_hold_ratio = 0.01f;
static float camera_move_track_ratio     = 0.01f;

// アセット関係
using MeshAsset = AssetBase<std::string, CMeshContainer>;

// ********************************************************************************
/// <summary>
/// オブジェクトデータ
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
    /// <created>いのうえ,2021/03/20</created>
    /// <changed>いのうえ,2021/03/20</changed>
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

using MeshData      = std::pair<std::string, std::shared_ptr<CMeshContainer>>;
using MeshList      = std::vector<MeshData>;
using ObjectList    = std::vector<ObjectData>;
using AddObjectData = std::pair<ObjectData*, ObjectList*>;
using SaveData      = std::tuple<std::string, MeshList*, ObjectList*>;
using LoadData      = std::pair<std::string, std::string*>;