using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Scripts.Component.Collision {
    public class BarrackCollisionComponent : Assets.Scripts.Component.Collision.CollisionComponent {
        public override Assets.Scripts.Json.JsonComponent CreateJsonComponent() {
            var ret = new Assets.Scripts.Json.JsonComponent();
            ret.type = Json.ComponentType.Collision.kBarrackCollisionComponent;
            return ret;
        }
    }
}
