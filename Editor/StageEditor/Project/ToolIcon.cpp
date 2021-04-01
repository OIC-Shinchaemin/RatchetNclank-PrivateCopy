#include "ToolIcon.h"
#include "Define.h"

bool ToolIcon::Load(void) {
    const std::string key[] = {
        Hand,
        ArrowMove,
        ArrowRotate,
        ArrowScale,
    };
    LPCMofChar file[] = {
        "toolicon/hand.png",
        "toolicon/arrow_move.png",
        "toolicon/arrow_rotate.png",
        "toolicon/arrow_scale.png",
    };
    int i = 0;
    for (const auto& it : key) {
        if (!TextureAsset::Load(it, file[i++])) {
            return false;
        }
    }
    return true;
}

void* ToolIcon::GetTexture(const std::string& key) {
    return static_cast<void*>(TextureAsset::GetAsset(key)->GetTexture());
}
