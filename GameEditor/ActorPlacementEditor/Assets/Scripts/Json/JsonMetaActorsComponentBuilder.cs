using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Scripts.Json {
    public class JsonMetaActorsComponentBuilder {
        public void Build(Assets.Scripts.Actor.Actor actor, ref JsonComponent[] components) {
            int index = 0;
            var compatible_component = actor.GetComponents<Assets.Scripts.Component.Component>();
            components = new Assets.Scripts.Json.JsonComponent[compatible_component.Count()];

            foreach(var behaviours in compatible_component) {
                components[index] = behaviours.CreateJsonComponent();
                index++;
            } // for
        }
    }
}
