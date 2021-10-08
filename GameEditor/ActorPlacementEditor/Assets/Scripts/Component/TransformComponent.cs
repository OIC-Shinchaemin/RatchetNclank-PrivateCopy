using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using Assets.Scripts.Json;

namespace Assets.Scripts.Component {
    public class TransformComponent : Component {
        [SerializeField]
        public Transform _transform;

        private void Start() {
            _transform = this.GetComponent<Transform>();
        }
        public override Assets.Scripts.Json.JsonComponent CreateJsonComponent() {
            var ret = new Assets.Scripts.Json.JsonComponent();
            ret.type = Json.ComponentType.kTransform;
            ret.paramater.priority = base.priority;
            return ret;
        }
    }
}