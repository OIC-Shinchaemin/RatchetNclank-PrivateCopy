#include "GimmickBase.h"

class MoveCloud : public GimmickBase {
protected:

    float _speed;

public:

    MoveCloud(bool enable = true, bool collision = true,
        StageObjectType type = StageObjectType::None, std::string name = "",
        int mesh_no = -1,
        Vector3 pos = Vector3(),
        Vector3 scale = Vector3(1, 1, 1),
        Vector3 rotate = Vector3());
    virtual ~MoveCloud(void);

    virtual void Initialize(void) override;
    virtual void Update(float delta) override;
    virtual bool IsStart(void) const override;
};