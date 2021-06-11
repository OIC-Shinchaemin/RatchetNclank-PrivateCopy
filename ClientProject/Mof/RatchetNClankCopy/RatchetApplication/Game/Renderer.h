#ifndef RATCHET_GAME_RENDERER_H
#define RATCHET_GAME_RENDERER_H


#include <memory>
#include <vector>

#include "../GameDefine.h"
#include "../Actor/Actor.h"
#include "../ResourceManager.h"


namespace ratchet {
namespace game {
class Renderer {
    //! キャラクタ
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _actors;
    //! 表示
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _enable_actors;
    //! 非表示
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _disable_actors;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Renderer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Renderer();
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// リセット
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
}
#endif // !RATCHET_GAME_RENDERER_H