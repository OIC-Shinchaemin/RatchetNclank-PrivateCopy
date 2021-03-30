#ifndef MY_RENDERER_H
#define MY_RENDERER_H


#include <memory>
#include <vector>

#include "../Actor.h"

namespace my {
class Renderer {
    //! キャラクタ
    std::vector<std::shared_ptr<my::Actor>> _actors;
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
    void AddElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
};
}
#endif // !MY_RENDERER_H