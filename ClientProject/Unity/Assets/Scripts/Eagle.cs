using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Eagle : Enemy
{
    [SerializeField] private bool canAtack = false;
    private float second;
    [SerializeField] private GameObject EagleBullet;
    private void Update()
    {
        if(canAtack)
        {

            second += Time.deltaTime;


            if (second >= 1.0)    //1秒おきに攻撃
            {
                //memo:x=-2.55y=-3.5
                GameObject g = Instantiate(EagleBullet);
                g.transform.position = EagleBullet.transform.position;
                g.transform.rotation = EagleBullet.transform.rotation;
                g.SetActive(true);

                second = 0;
            }
        }

    }
}
