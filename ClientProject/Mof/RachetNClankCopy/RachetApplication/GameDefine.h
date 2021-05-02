#ifndef MY_GAME_DEFINE_H
#define MY_GAME_DEFINE_H

#include <stdexcept>
#include <string>
#include <Mof.h>

#include "My/Core/Math.h"
#include "MotionNames.h"
#include "ResourceManager.h"
#include "my/Core/FunctionPointerContainer.h"


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
using FuncPtrContainer = my::FunctionPointerContainer<
    FuncPtrEnemyBool,
    FuncPtrEnemyFloat
>;


class Mesh : public Mof::CMeshContainer {
    using super = Mof::CMeshContainer;
private:
    //! Õ“Ë” 
    Mof::CBoxAABB _collision_box;
    Mesh() :_collision_box() {
    }

    virtual MofBool Load(LPCMofChar pName) override {
        bool re = super::Load(pName);
    //Mof::CVector3 scale; mat.GetScaling(scale);
    //Mof::CVector3 trans; mat.GetTranslation(trans);

    //Mof::CBoxAABB box; geometry->CalculateAABB(box);
    //box.Size.x *= scale.x; box.Size.y *= scale.y; box.Size.z *= scale.z;
    //box.Position.x += trans.x; box.Position.y += trans.y; box.Position.z += trans.z;
    //std::swap(box.Size.y, box.Size.z);

    //auto pos = super::GetOwner()->GetPosition();
    //pos.y -= _enemy_com.lock()->GetHeight();
    //box.Position.y += _enemy_com.lock()->GetHeight();
    //if (!super::CollisionShpereAABB(this->GetSphere().value(), box)) {
    //    geometry->SetMatrix(default_matrix);
    //    continue;
    //} // if

        return re;
    }
};
}
#endif // !MY_GAME_DEFINE_H