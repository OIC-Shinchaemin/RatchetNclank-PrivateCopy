using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using Assets.Scripts.Json;


namespace Assets.Scripts.Component.Collision {
    public class CollisionComponent : Component {
        private void Start() {
        }
        public override Assets.Scripts.Json.JsonComponent CreateJsonComponent() {
            var ret = new Assets.Scripts.Json.JsonComponent();
            return ret;
        }
    }
}
