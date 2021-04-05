#ifndef MY_GAME_DEFINE_H
#define MY_GAME_DEFINE_H

#include <stdexcept>
#include <string>
#include <Mof.h>

#include "My/Core/Math.h"
#include "MotionNames.h"
#include "ResourceManager.h"
#include "FunctionPointerContainer.h"


namespace my {
struct Transform {
    Mof::CVector3 position = math::vec3::kZero;
    Mof::CVector3 rotate = math::vec3::kZero;
    Mof::CVector3 scale = math::vec3::kOne;
};
using ResourceMgr = my::ResourceManager<
    std::shared_ptr<Mof::CTexture>,
    std::shared_ptr<Mof::CMeshContainer>,
    std::shared_ptr<my::MotionNames>
>;

class Enemy;
using FuncPtrEnemyBool = bool(Enemy::*)(void);
using FuncPtrEnemyFloat = float(Enemy::*)(void);
//using FuncPtrEnemyBoolConst = bool(Enemy::*)(void) const;
using FuncPtrContainer = my::FunctionPointerContainer<
    FuncPtrEnemyBool,
    FuncPtrEnemyFloat
>;
}
#endif // !MY_GAME_DEFINE_H