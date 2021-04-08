using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AtackBall : MonoBehaviour
{
    [SerializeField] private PlayerController Player;
    [SerializeField] private LayerMask ground;
    private Rigidbody2D rb;
    private Collider2D coll;
    [SerializeField] private AudioSource sound;
    private bool IsBreaking;
    private Animator anim;
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        rb = GetComponent<Rigidbody2D>();
        coll = GetComponent<Collider2D>();
        if(Player.Left)                             //プレイヤーが左向きなら左方向に射出
        {
            transform.localScale = new Vector2(-1, -1);
            rb.velocity = new Vector2(-15, 5);

        }
        else
        {
            transform.localScale = new Vector2(1, -1);
            rb.velocity = new Vector2(15, 5);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (coll.IsTouchingLayers(ground) && !IsBreaking)          //何らかの地形に接触したら消滅する
        {
            sound.Play();
            anim.SetTrigger("Lost");
            rb.bodyType = RigidbodyType2D.Kinematic;
            rb.velocity = Vector2.zero;
            IsBreaking = true;

        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Enemy"&&!IsBreaking)               
        {
            sound.Play();
            anim.SetTrigger("Lost");
            rb.bodyType = RigidbodyType2D.Kinematic;
            rb.velocity = Vector2.zero;
            coll.enabled = false;
            IsBreaking = true;
        }
        else if (collision.tag == "Destroy")
        {
            Lost();
        }
    }

    private void Lost()
    {
        Destroy(gameObject);
    }
}
