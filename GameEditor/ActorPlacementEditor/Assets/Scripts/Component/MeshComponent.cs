using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using Assets.Scripts.Json;


namespace Assets.Scripts.Component {
    public class MeshComponent : Component {
        [SerializeField]
        public MeshFilter mesh_filter;
        [SerializeField]
        public string path;

        private void Start() {
            mesh_filter = this.GetComponent<MeshFilter>();
        }
        public override Assets.Scripts.Json.JsonComponent CreateJsonComponent() {
            var ret = new Assets.Scripts.Json.JsonComponent();
            ret.type = Json.ComponentType.kMesh;
            ret.paramater.priority = base.priority;
            ret.paramater.path = path;
            return ret;
        }
    }
}
