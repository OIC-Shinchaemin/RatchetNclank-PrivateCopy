using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

public class BossEvent : MonoBehaviour
{
    public GameObject player;
    public CinemachineVirtualCamera areaCam;
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

            // BossCamera ON
            areaCam.Priority = 100;
        }
    }

    public void TriggerON()
    {
        col.isTrigger = true;
        areaCam.Priority = 0;
    }
}
