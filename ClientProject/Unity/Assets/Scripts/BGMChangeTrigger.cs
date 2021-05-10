using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGMChangeTrigger : MonoBehaviour
{
    Collider2D col;
    public bool isGround;
    public GameObject player;
    private void Start()
    {
        col = GetComponent<Collider2D>();
    }
    private void OnTriggerEnter2D(Collider2D other)
    {

        if (other.gameObject == player)
        {
            BGM.bgm.state = BGM.Musicstate.stop;
            Debug.Log("当たってるはずなんだけど");
            BGMChange();
        }
    }
    private void BGMChange()
    {

        if (isGround)
        {
            BGM.bgm.state = BGM.Musicstate.stage1;
        }
        else
        {
            BGM.bgm.state = BGM.Musicstate.understage;
        }

    }
}
