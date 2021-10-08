using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;


namespace Assets.Scripts.Json {
    class JsonFileWriter {
        public bool Write(in Assets.Scripts.Json.JsonActorBuilder meta, string filename) {
            string json = JsonUtility.ToJson(meta);
            string path = "Assets/Resources/json/" + filename + ".json";

            bool isAppend = false; // 追記無効
            using(var fs = new StreamWriter(path, isAppend, System.Text.Encoding.GetEncoding("UTF-8"))) {
                fs.Write(json);
            }
            return true;
        }
        public bool Write(in Assets.Scripts.Json.JsonEditStageData meta, string filename) {
            string json = JsonUtility.ToJson(meta);
            string path = "Assets/Resources/json/" + filename + ".json";

            bool isAppend = false; // 追記無効
            using(var fs = new StreamWriter(path, isAppend, System.Text.Encoding.GetEncoding("UTF-8"))) {
                fs.Write(json);
            }
            return true;
        }

        public bool Write(in Assets.Scripts.Json.JsonEditStagePlacement meta, string filename) {
            string json = JsonUtility.ToJson(meta);
            string path = "Assets/Resources/json/" + filename + ".json";

            bool isAppend = false; // 追記無効
            using(var fs = new StreamWriter(path, isAppend, System.Text.Encoding.GetEncoding("UTF-8"))) {
                fs.Write(json);
            }
            return true;
        }
    }
}