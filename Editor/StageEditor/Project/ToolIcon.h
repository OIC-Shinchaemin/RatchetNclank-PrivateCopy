#pragma once
#include "Singleton.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
// ********************************************************************************
class ToolIcon : public Singleton<ToolIcon> {
private:

public:

    static constexpr char* Hand        = "Hand";
    static constexpr char* ArrowMove   = "ArrowMove";
    static constexpr char* ArrowRotate = "ArrowRotate";
    static constexpr char* ArrowScale  = "ArrowScale";

    ToolIcon(void) = default;

    ~ToolIcon(void) = default;

    bool Load(void);

    void* GetTexture(const std::string& key);
};

