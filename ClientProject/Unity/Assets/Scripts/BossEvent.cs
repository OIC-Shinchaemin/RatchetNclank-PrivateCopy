using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossEvent : MonoBehaviour
{
    public GameObject player;
    public bool bBoss = false;

    private Collider2D col;

    void Awake()
    {
        col = GetComponent<Collider2D>();
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject == player)
        {            
            bBoss = true;            
        }
    }

    private void OnTriggerExit2D(Collider2D other)
    {
        if (other.gameObject == player)
        {
            // Trigger OFF
            col.isTrigger = false;
        }
    }

    public void TriggerON()
    {
        col.isTrigger = true;
    }
}
