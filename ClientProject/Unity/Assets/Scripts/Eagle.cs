using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Eagle : Enemy
{
    
    [SerializeField] private bool canAttack = false;
    private float second;
    [SerializeField] private GameObject EagleBullet;
    [SerializeField] private GameObject player;

    public Vector2 PlayerPos;
    public Vector2 EaglePos;


    private float shotspeed = 10f;

    
    private void Update()
    {
        if(canAttack)
        {
            Attack();
        }

    }

    private void Attack()
    {
        second += Time.deltaTime;


        if (second >= 1.0)    //1秒おきに攻撃
        {
            PlayerPos = player.GetComponent<Transform>().position;
            EaglePos = GetComponent<Transform>().position;

            if (PlayerPos.x>EaglePos.x)
            {
                transform.localScale = new Vector2(-1, 1);
            }
            else
            {
                transform.localScale = new Vector2(1, 1);
            }
            //プレイヤーの座標 - 自分の座標でベクトルを求めるわよん。
            Vector2 vec = PlayerPos - EaglePos;
            //求めたベクトルを正規化するのです。
            vec.Normalize();
            //弾速を掛けることとする!!
            vec *= shotspeed;
            GameObject g = Instantiate(EagleBullet, transform.position, EagleBullet.transform.rotation);
            g.SetActive(true);
            g.GetComponent<Rigidbody2D>().velocity = vec;

            second = 0;
        }
    }
}
