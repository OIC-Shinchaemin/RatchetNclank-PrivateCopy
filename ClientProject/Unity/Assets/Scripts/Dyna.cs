using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Dyna : MonoBehaviour
{
    private float attackSecond;

    [SerializeField] private GameObject eagleBullet;
    [SerializeField] private GameObject player;

    private float moveSpeed = .04f;

    private Vector3 playerPos;
    private Vector3 dynaPos;

    private float shotspeed = 10f;

    public BossEvent bossEvent;

    Vector2 defaultScale = Vector2.zero;
    Vector2 defaultPosition = Vector2.zero;

    //private bool damegeOn = false;

    int attackCount = 0;

    [SerializeField] private GameObject point1, point2, point3, point4, point5;
    bool move1, move2, move3, move4, move5, move6;
    private float stayTime;
    private bool moving;

    void Start()
    {

        move1 = move2 = move3 = move4 = move5 = move6 = false;

        defaultScale = transform.localScale;
        defaultPosition = transform.localPosition;
    }

    void Update()
    {
        if (bossEvent.GetComponent<BossEvent>().bBoss == true)
        {

            playerPos = player.GetComponent<Transform>().position;
            dynaPos = GetComponent<Transform>().position;

            FaceDirection();

            if (moving == false)
            {
                stayTime += Time.deltaTime;
            }

            if (stayTime >= 5)
            {
                moving = true;
                Move();
            }

                Attack();
        }
    }

    private void Move()
    {
        //いずれswithにします
        //というかちゃんとイージングとか使いたいです。
        //今はゴリ押しフラグ、いっきまーす！

        //y座標が設定されたポイントに移動するまで移動
        if (dynaPos.y <= point1.transform.position.y && !move1)
        {
            dynaPos.y += moveSpeed;
        }
        if (dynaPos.y >= point1.transform.position.y)
        {
            dynaPos = point2.transform.position;
            move1 = true;
        }

        //y座標が設定されたpoint3に移動するまで移動
        if (move1 && dynaPos.y >= point3.transform.position.y && !move2)
        {
            dynaPos.y -= moveSpeed;
        }
        if (dynaPos.y <= point3.transform.position.y)
        {
            move2 = true;
        }

        //y座標が設定されたpoint2に移動するまで移動
        if (dynaPos.y <= point2.transform.position.y && move2 && !move3)
        {
            dynaPos.y += moveSpeed;
        }
        if (dynaPos.y >= point2.transform.position.y)
        {
            dynaPos = point4.transform.position;
            move3 = true;
        }


        if (move3 && dynaPos.y >= point5.transform.position.y && !move4)
        {
            dynaPos.y -= moveSpeed;
        }
        if (dynaPos.y <= point5.transform.position.y)
        {
            move4 = true;
        }

        //y座標が設定されたpoint2に移動するまで移動
        if (dynaPos.y <= point4.transform.position.y && move4 && !move5)
        {
            dynaPos.y += moveSpeed;
        }
        if (dynaPos.y >= point4.transform.position.y)
        {
            dynaPos = point1.transform.position;
            move5 = true;
        }

        if (move5 && dynaPos.y >= defaultPosition.y && !move6)
        {
            dynaPos.y -= moveSpeed;
        }
        if (dynaPos.y <= defaultPosition.y && move5)
        {
            move6 = true;
        }

        if (move6)
        {
            moving = false;
            move1 = move2 = move3 = move4 = move5 = move6 = false;
            stayTime = 0;
        }

        transform.position = dynaPos;

        //attackCount = 0;
    }

    private void Attack()
    {
        attackSecond += Time.deltaTime;


        if (attackSecond >= .5)    //n秒おきに攻撃
        {
            //プレイヤーの座標 - 自分の座標でベクトルを求めるわよん。
            Vector2 vec = playerPos - dynaPos;
            //求めたベクトルを正規化するのです。
            vec.Normalize();
            //弾速を掛けることとする!!
            vec *= shotspeed;
            GameObject g = Instantiate(eagleBullet, transform.position, eagleBullet.transform.rotation);
            g.SetActive(true);
            g.GetComponent<Rigidbody2D>().velocity = vec;

            attackSecond = 0;

            attackCount++;
        }
    }

    private void FaceDirection()
    {
        Vector2 localScale = transform.localScale;

        if (playerPos.x > dynaPos.x && localScale.x > 0)
        {
            localScale.x *= -1;

        }
        else if (playerPos.x < dynaPos.x && localScale.x < 0)
        {
            localScale = defaultScale;
        }

        transform.localScale = localScale;
    }

    //private void OnTriggerEnter2D(Collider2D collision)
    //{
    //    if (collision.gameObject.tag == "Throw")
    //    {
    //        damegeOn = true;
    //    }
    //}

    public void OnDeathEvent()
    {
        bossEvent.bBoss = false;
        bossEvent.TriggerON();
    }

    float EaseInBack(float t, float overshoot = 1f)
    {
        float s = 1.70158f * overshoot;
        return t * t * ((s + 1f) * t - s);
    }

}
