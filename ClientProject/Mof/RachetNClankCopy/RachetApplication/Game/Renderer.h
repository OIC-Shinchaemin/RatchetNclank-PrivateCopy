#ifndef MY_RENDERER_H
#define MY_RENDERER_H


#include <memory>
#include <vector>

#include "../Actor.h"
#include "../Character/Character.h"


namespace my {
class Renderer {
    //! キャラクタ
    std::vector<std::shared_ptr<my::Character>> _characters;
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
    void AddElement(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
};
}
#endif // !MY_RENDERER_H