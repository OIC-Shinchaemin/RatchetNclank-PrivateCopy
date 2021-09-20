using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;


namespace Assets.Scripts.Actor {
    public class Actor : MonoBehaviour {
        [SerializeField]
        public Json.JsonEditElement _edit_element;
        [SerializeField]
        public Assets.Scripts.Json.JsonActorBuilder meta;
        [SerializeField]
        public string builder = "";

        public virtual void GenerateMetaData() {
        }
        protected void GenerateDefaultData() {
            _edit_element = this.GetComponent<Json.JsonEditElement>();
            _edit_element.data.paramater.name = this.name;
            _edit_element.data.paramater.tag = this.tag;
            _edit_element.data.transform.position[0] = this.transform.position.x;
            _edit_element.data.transform.position[1] = this.transform.position.y;
            _edit_element.data.transform.position[2] = this.transform.position.z;
            _edit_element.data.transform.rotation[0] = this.transform.rotation.x;
            _edit_element.data.transform.rotation[1] = this.transform.rotation.y;
            _edit_element.data.transform.rotation[2] = this.transform.rotation.z;
            _edit_element.data.transform.scale[0] = 1.0f;
            _edit_element.data.transform.scale[1] = 1.0f;
            _edit_element.data.transform.scale[2] = 1.0f;
        }
    }
}
