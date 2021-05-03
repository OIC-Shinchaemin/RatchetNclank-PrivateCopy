using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Eagle : Enemy
{
    
    [SerializeField] private bool canAttack = false;
    [SerializeField] private bool canMove = false;

    private float second;
    [SerializeField] private GameObject EagleBullet;
    [SerializeField] private GameObject player;

    private Vector2 PlayerPos;
    private Vector2 EaglePos;


    [SerializeField] private float moveSpeed = 5;
    [SerializeField] private float topCap;
    [SerializeField] private float underCap;

    [SerializeField] bool Upmode = false;

    private float shotspeed = 10f;

    
    private void Update()
    {
        if (GetComponent<SpriteRenderer>().isVisible && !IsDead && GetComponent<HpEnemy>().Ebiflied == false)   
        {

            if (canAttack)
            {
                Attack();
            }

        }
        if (canMove && !IsDead && GetComponent<HpEnemy>().Ebiflied == false)
        {
            Move();
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

    private void Move()
    {
        if (Upmode)
        {
            rb.velocity = new Vector2(0, moveSpeed);
        }
        else
        {

            rb.velocity = new Vector2(0, -moveSpeed);

        }
        if (transform.position.y > topCap)
        {
            Upmode = false;
        }
        else if(transform.position.y < underCap)
        {
            Upmode = true;
        }

    }
}
