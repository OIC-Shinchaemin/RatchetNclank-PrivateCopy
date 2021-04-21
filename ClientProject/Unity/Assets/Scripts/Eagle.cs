using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Eagle : Enemy
{
    
    [SerializeField] private bool canAtack = false;
    private float second;
    [SerializeField] private GameObject EagleBullet;
    private float shotspeed = 10f;
    public GameObject player;

    private void Start()
    {
        player = GameObject.Find("Player");
    }

    private void Update()
    {
        if(canAtack)
        {

            second += Time.deltaTime;


            if (second >= 1.0)    //1秒おきに攻撃
            {
                //プレイヤーの座標 - 自分の座標でベクトルを求めるわよん。
                Vector2 vec = player.transform.position - transform.position;
                //求めたベクトルを正規化するのです。
                vec.Normalize();
                //弾速を掛けることとする!!
                vec *= shotspeed;
                GameObject g = Instantiate(EagleBullet,transform.position,EagleBullet.transform.rotation);

                g.GetComponent<Rigidbody2D>().velocity = vec;


                g.SetActive(true);

                second = 0;
            }
        }

    }
}
