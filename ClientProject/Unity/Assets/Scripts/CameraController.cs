using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public Transform player;

    private void Update()
    {
        if (PermanentUI.perm.currentHP > 0)
        {

            //UnityEngine.Debug.Log("あばば");
            transform.position = new Vector3(player.position.x, player.position.y, transform.position.z);
        }
        else
        {
            //UnityEngine.Debug.Log("(｀・ω・´)ｼｬｷｰﾝ");

            transform.position = new Vector3(transform.position.x, transform.position.y, transform.position.z);
            GetComponent<Cinemachine.CinemachineBrain>().enabled = false; 
        }
    }
}
