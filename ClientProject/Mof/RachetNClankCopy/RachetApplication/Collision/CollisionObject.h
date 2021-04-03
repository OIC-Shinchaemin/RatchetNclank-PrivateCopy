#ifndef MY_COLLISION_OBJECT_H
#define MY_COLLISION_OBJECT_H


#include <optional>
#include <any>
#include <memory>

#include <Mof.h>


namespace my {
struct CollisionInfo {
    //! 埋まり値
    float d = 0.0f;
    CollisionInfo() : d(0.0f) {}
    CollisionInfo(const Mof::COLLISIONOUTGEOMETRY& c) : d(c.d) {}
    virtual ~CollisionInfo() {}
};
class CollisionObject {
public:    
    class CollisionFunc {
        using Func = std::function<bool(std::shared_ptr<my::CollisionInfo>)>;
    private:
        //! 実行関数
        Func _func;
    public:
        CollisionFunc() :_func() {}
        CollisionFunc(Func func) :_func(func) {}
        void AddFunction(Func lambda) {
            this->_func = lambda;
        }
        bool Excute(std::shared_ptr<my::CollisionInfo> info) {
            return _func(info);
        }
    };
private:
    std::unordered_map<std::string, CollisionFunc> _func_map;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CollisionObject();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CollisionObject();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="owner"></param>
    virtual void SetOwner(std::any owner) = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetType(void) const = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CSphere> GetSphere(void) = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CBoxAABB> GetBox(void) = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetRay(void) = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) = 0;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="type"></param>
    /// <param name="lambda"></param>
    void AddCollisionFunc(const std::string& type, CollisionFunc lambda);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    void ExcuteFunction(const std::string& key, const my::CollisionInfo& info);
};
}
#endif // !MY_COLLISION_OBJECT_H