#pragma once
#include <string>

// ********************************************************************************
/// <summary>
/// アクション管理用
/// </summary>
// ********************************************************************************
class ActionKeyName {
public:
    static constexpr char* MeshLoad         = "MeshLoad";
    static constexpr char* MeshLoadDialog   = "MeshLoadDialog";
    static constexpr char* SaveProject      = "SaveProject";
    static constexpr char* LoadProject      = "LoadProject";
    static constexpr char* ProjectDataParse = "ProjectDataParse";
    static constexpr char* AddObject        = "AddObject";
};

