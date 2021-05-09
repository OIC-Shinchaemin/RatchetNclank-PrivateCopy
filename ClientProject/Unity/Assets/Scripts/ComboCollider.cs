using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ComboCollider : MonoBehaviour
{
    public BossEvent bossEvent;

    private Collider2D col;

    void Awake()
    {
        col = GetComponent<Collider2D>();
    }
    void Update()
    {
        if (bossEvent.bBoss == true)
        {
            col.isTrigger = false;
        }
        else
        {
            col.isTrigger = true;
        }
    }
}
