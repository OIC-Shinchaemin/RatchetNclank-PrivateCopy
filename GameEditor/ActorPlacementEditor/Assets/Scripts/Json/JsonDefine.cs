using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;


namespace Assets.Scripts.Json {
    [Serializable]
    public class JsonTransform {
        public float[] position = new float[3];
        public float[] rotation = new float[3];
        public float[] scale = new float[3];
    }
    [Serializable]
    public class JsonActorParamater {
        public string type = TextCode.kUndefined;
        public string name = TextCode.kNameless;
        public string tag = TextCode.kNone;
        public string[] tags;
    }
    [Serializable]
    public class JsonComponentParamater {
        public int priority = 0;
        public string path = null;
        public float[] color = new float[4];
        public int hp_max = 0;
        public float height = 0.0f;
        public float volume = 0.0f;
        public float range = 0.0f;
        public JsonComponent[] children;
        public string[] behaviour;
    }
    [Serializable]
    public class JsonComponent {
        public string type = TextCode.kUndefined;
        public JsonComponentParamater paramater = new JsonComponentParamater();
    }
    [Serializable]
    public class JsonActorBuilder {
        public JsonActorParamater actor = new JsonActorParamater();
        public JsonComponent [] compoennts = null;
        public string parent;
        public string[] children;
        public JsonActorBuilder() {
        }
    }

    [Serializable]
    public class JsonEditStageData {
        public string type = TextCode.kNone;
        public string builder_path = TextCode.kNone;
        public JsonActorParamater paramater = new JsonActorParamater();
        public JsonTransform transform = new JsonTransform();
    }
    [Serializable]
    public class JsonEditStagePlacement {
        public JsonEditStageData[] element_list;
        public JsonEditStagePlacement() {
        }
    }
    class TextCode {
        public static string kUndefined = "undefined";
        public static string kNameless = "nameless";
        public static string kNone = "none";
    }
    class ObjectType {
        public static string kSample = "Sample";
        public static string kActor = "Actor";
    }
    class ActorType {
        public static string kBarrack = "Barrack";
        public static string kBombGloveBullet = "BombGloveBullet";
        public static string kBlasterBullet = "BlasterBullet";
        public static string kBombGloveEffect = "BombGloveEffect";
        public static string kBlaster = "Blaster";
        public static string kBombGlove = "BombGlove";
        public static string kBolt = "Bolt";
        public static string kBulletItem = "BulletItem";

        public static string kEnemy = "Enemy";
        public static string kEnemyBullet = "EnemyBullet";
        public static string kFence = "Fence";
        public static string kKing = "King";

        public static string kNanotechItem = "NanotechItem";
        public static string kOmniWrench = "OmniWrench";

        public static string kPlayer = "Player";
        public static string kPyrocitor = "Pyrocitor";
        public static string kPyrocitorBullet = "PyrocitorBullet";

        public static string kShip = "Ship";
        public static string kShop = "Shop";
        public static string kScarecrow = "Scarecrow";

        public static string kTerrain = "Terrain";
        public static string kWall = "Wall";
    }

    class ComponentType {
        public static string kAction = "ActionComponent";
        public static string kActionState = "ActionState";
        public static string kAIState = "AIStateComponent";
        public static string kAnimationMesh = "AnimationMeshComponent";
        public static string kBillboard = "BillboardComponent";
        public static string kCamera = "CameraComponent";
        public static string kHpComponent = "HpComponent";
        public static string kInvincible = "InvincibleComponent";
        public static string kMesh = "MeshComponent";
        public static string kMotion = "MotionComponent";
        public static string kMotionState = "MotionStateComponent";
        public static string kSightRecognition = "SightRecognitionComponent";
        public static string kTransform = "TransformComponent";
        public static string kVelocityComponent = "VelocityComponent";

        public class Bullet {
            public static string k = "";
        };
        public class Collision {
            public static string k = "";
            public static string kBarrackCollisionComponent = "BarrackCollisionComponent";
        };
        public class Enemy {
            public static string k = "";
        };
        public class Item {
            public static string k = "";
        };
        public class Player {
            public static string k = "";
        };
        public class Scarecrow {
            public static string k = "";
        };
        public class Ship {
            public static string k = "";
        };
        public class Weapon {
            public class OmniWrench {
                public static string k = "";
            };
        };
    }
}