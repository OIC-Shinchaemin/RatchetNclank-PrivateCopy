using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ghetsis : MonoBehaviour
{
    private float rad;

    private int waypoint = 0;
    public GameObject wayPoint1;
    public GameObject wayPoint2;
    public GameObject wayPoint3;

    public GameObject bossChild;

    public BossEvent bossEvent;

    float second;

    float rotatespeed = 0;
    private Vector2 movespeed = new Vector2(.25f, .25f);

    private Vector2 nowpos;

    bool damegeOn = false;

    void Start()
    {

    }

    void FixedUpdate()
    {
        if (bossEvent.GetComponent<BossEvent>().bBoss == true) //ボス戦フラグがたったら
        {
            BossMove();

            if (damegeOn)
            {
                second += Time.deltaTime;
                if (second >= 0.3)    //〇秒おきに攻撃
                {
                    //memo:x=-2.55y=-3.5
                    Instantiate(bossChild, transform.position, transform.rotation);

                    second = 0;
                }
                transform.Rotate(0, 0, this.rotatespeed);
            }
        }
    }

    private void BossMove()
    {
        //そのうちfor文で書きたいゲーチスの移動コード
        switch (waypoint)
        {
            case 0:

                rad = Mathf.Atan2(
                wayPoint1.transform.position.y - transform.position.y,
                wayPoint1.transform.position.x - transform.position.x);

                nowpos = transform.position;

                nowpos.x += movespeed.x * Mathf.Cos(rad);
                nowpos.y += movespeed.y * Mathf.Sin(rad);

                float diffx1 = wayPoint1.transform.position.x - nowpos.x;
                float diffy1 = wayPoint1.transform.position.y - nowpos.y;

                transform.position = nowpos;

                if (Mathf.Abs(diffx1) < 1 && Mathf.Abs(diffy1) < 1)
                {
                    waypoint = 1;
                }
                break;

            case 1:
                rad = Mathf.Atan2(
                wayPoint2.transform.position.y - transform.position.y,
                wayPoint2.transform.position.x - transform.position.x);

                nowpos = transform.position;

                nowpos.x += movespeed.x * Mathf.Cos(rad);
                nowpos.y += movespeed.y * Mathf.Sin(rad);

                var diffx2 = wayPoint2.transform.position.x - nowpos.x;
                var diffy2 = wayPoint2.transform.position.y - nowpos.y;

                transform.position = nowpos;

                if (Mathf.Abs(diffx2) < 1 && Mathf.Abs(diffy2) < 1)
                {
                    waypoint = 2;
                }
                break;

            case 2:
                rad = Mathf.Atan2(
                wayPoint3.transform.position.y - transform.position.y,
                wayPoint3.transform.position.x - transform.position.x);

                nowpos = transform.position;

                nowpos.x += movespeed.x * Mathf.Cos(rad);
                nowpos.y += movespeed.y * Mathf.Sin(rad);

                var diffx3 = wayPoint3.transform.position.x - nowpos.x;
                var diffy3 = wayPoint3.transform.position.y - nowpos.y;

                transform.position = nowpos;

                if (Mathf.Abs(diffx3) < 1 && Mathf.Abs(diffy3) < 1)
                {
                    waypoint = 0;
                }
                break;
        }
    }


    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Throw")
        {
            rotatespeed += 7;
            damegeOn = true;
        }
    }

    public void OnDeathEvent()
    {
        bossEvent.bBoss = false;
        bossEvent.TriggerON();
    }
}