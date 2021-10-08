using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using Assets.Scripts.Json;

namespace Assets.Scripts.Component {
    class VelocityComponent : Component {
        [SerializeField]
        public Rigidbody _rigidbody;

        private void Start() {
            _rigidbody = this.GetComponent<Rigidbody>();
        }
        public override Assets.Scripts.Json.JsonComponent CreateJsonComponent() {
            var ret = new Assets.Scripts.Json.JsonComponent();
            ret.type = Json.ComponentType.kVelocityComponent;
            ret.paramater.priority = base.priority;
            return ret;
        }
    }
}
