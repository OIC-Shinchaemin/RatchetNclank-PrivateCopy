#ifndef RACHET_RENDERER_H
#define RACHET_RENDERER_H


#include <memory>
#include <vector>

#include "../GameDefine.h"
#include "../Actor.h"
#include "../ResourceManager.h"


namespace rachet {
class Renderer {
    //! キャラクタ
    std::vector<std::shared_ptr<rachet::Actor>> _actors;
    //! 表示
    std::vector<std::shared_ptr<rachet::Actor>> _enable_actors;
    //! 非表示
    std::vector<std::shared_ptr<rachet::Actor>> _disable_actors;
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
    void AddElement(const std::shared_ptr<rachet::Actor>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<rachet::Actor>& ptr);
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
#endif // !RACHET_RENDERER_H