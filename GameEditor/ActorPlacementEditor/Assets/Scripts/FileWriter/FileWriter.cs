using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Assets.Scripts.FileWriter {
    public class FileWriter : MonoBehaviour {
        string prefab_path = "Prefabs/";
        //public string[] prefab_names;
        public List<string> prefab_names;


        public FileWriter() {
            prefab_names = new List<string>();
            prefab_names.Add(Json.ActorType.kBarrack);
            prefab_names.Add(Json.ActorType.kBombGloveBullet);
            prefab_names.Add(Json.ActorType.kBlasterBullet);
            prefab_names.Add(Json.ActorType.kBombGloveEffect);
            prefab_names.Add(Json.ActorType.kBlaster);
            prefab_names.Add(Json.ActorType.kBombGlove);
            prefab_names.Add(Json.ActorType.kBolt);
            prefab_names.Add(Json.ActorType.kBulletItem);
            prefab_names.Add(Json.ActorType.kEnemy);
            prefab_names.Add(Json.ActorType.kEnemyBullet);
            prefab_names.Add(Json.ActorType.kFence);
            prefab_names.Add(Json.ActorType.kKing);
            prefab_names.Add(Json.ActorType.kNanotechItem);
            prefab_names.Add(Json.ActorType.kOmniWrench);
            prefab_names.Add(Json.ActorType.kPlayer);
            prefab_names.Add(Json.ActorType.kPyrocitor);
            prefab_names.Add(Json.ActorType.kPyrocitorBullet);
            prefab_names.Add(Json.ActorType.kShip);
            prefab_names.Add(Json.ActorType.kShop);
            prefab_names.Add(Json.ActorType.kScarecrow);
            prefab_names.Add(Json.ActorType.kTerrain);
            prefab_names.Add(Json.ActorType.kWall);
        }

        // Start is called before the first frame update
        void Start() {
            var writer = new Assets.Scripts.Json.JsonFileWriter();
            OutputByScene(writer);
            OutputByPrefab(writer);
        }
        void OutputByScene(in Assets.Scripts.Json.JsonFileWriter writer) {
            var placements = new Assets.Scripts.Json.JsonEditStagePlacement();
            {
                int count = 0;
                // •À‚×‘Ö‚¦‚Í‚µ‚È‚¢
                foreach(GameObject obj in UnityEngine.Object.FindObjectsOfType(typeof(GameObject))) {
                    if(obj.activeInHierarchy) {
                        var elem = obj.GetComponent<Assets.Scripts.Json.JsonEditElement>();
                        if(elem) {
                            count++;
                        } // if
                    } // if
                } // for
                placements.element_list = new Assets.Scripts.Json.JsonEditStageData[count];
            }

            int index = 0;
            foreach(GameObject obj in UnityEngine.Object.FindObjectsOfType(typeof(GameObject))) {
                if(obj.activeInHierarchy) {
                    var elem = obj.GetComponent<Assets.Scripts.Json.JsonEditElement>();
                    if(elem) {
                        placements.element_list[index] = elem.data;
                        index++;
                    } // if
                } // if
            } // for
            writer.Write(placements, "placement_data");
        }
        void OutputByPrefab(in Assets.Scripts.Json.JsonFileWriter writer) {

            foreach(var name in prefab_names) {
                Debug.Log(name);
                var prefab = (GameObject)Resources.Load(prefab_path + name);
                if(prefab) {
                    var actor = prefab.GetComponent<Assets.Scripts.Actor.Actor>();
                    actor.GenerateMetaData();
                    writer.Write(actor.meta, prefab.name);
                } // if
            } // for
        }

    }
}