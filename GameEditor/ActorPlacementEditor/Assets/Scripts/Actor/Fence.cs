using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Scripts.Actor {
    public class Fence : Assets.Scripts.Actor.Actor {

        public override void GenerateMetaData() {
            meta = new Assets.Scripts.Json.JsonActorBuilder();
            meta.actor.name = "fence";
            meta.actor.type = Json.ActorType.kFence;
            var builder = new Json.JsonMetaActorsComponentBuilder();
            builder.Build(this, ref meta.compoennts);
        }
        void Start() {
            base.GenerateDefaultData();
            _edit_element.data.type = Json.ActorType.kFence;
            _edit_element.data.paramater.type = Json.ActorType.kFence;
            builder = "fence.json";

            _edit_element.data.builder_path = builder;
        }
    }
}
