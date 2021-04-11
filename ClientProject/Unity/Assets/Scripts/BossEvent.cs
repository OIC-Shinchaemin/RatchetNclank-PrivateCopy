using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossEvent : MonoBehaviour
{
    public GameObject player;
    public bool bBoss = false;

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject == player)
        {
            bBoss = true;
        }
    }
}
