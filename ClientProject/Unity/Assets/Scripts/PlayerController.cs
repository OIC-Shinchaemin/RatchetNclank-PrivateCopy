using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;
using System;

public class PlayerController : MonoBehaviour
{
    //Start() variables
    private Rigidbody2D rb;
    private Animator anim;
    private Collider2D coll;

    //FSM
    private enum State { idle, running, jumping, falling, hurt, climb, atack, Die }
    private State state = State.idle;

    //Ladder variables
    [HideInInspector] public bool canClimb = false;
    [HideInInspector] public bool bottomLadder = false;
    [HideInInspector] public bool topLadder = false;
    [HideInInspector] public Ladder ladder;
    private float naturalGravity;
    [SerializeField] float climbSpeed = 3f;

    //Inspector variables
    [SerializeField] private LayerMask ground;
    [SerializeField] private float speed = 10f;
    [SerializeField] private float JumpForce = 10f;
    [SerializeField] private float hurtForce = 10f;
    [SerializeField] private AudioSource cherry;
    [SerializeField] private AudioSource footstep;

    //ぇぬのコード用
    public bool CanAtack = false;
    [SerializeField] private GameObject atackball;
    [SerializeField] private AudioSource Throwse;
    public bool Left = false;
    private int DCount;

    //本当は使いたくなかった変数たち
    //int JumpCount;

    float hDirection = 0;
    float LimitSpeed = 30f;

    private void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        coll = GetComponent<Collider2D>();
        PermanentUI.perm.healthAmount.text = PermanentUI.perm.currentHP.ToString();
        naturalGravity = rb.gravityScale;
    }

    private void Update()
    {


        if (state == State.climb)
        {
            Climb();
        }
        else if (state != State.hurt)
        {
            Movement();
        }

        MoveLimit();

        if (Input.GetButtonDown("Jump"))
        {
            if (state != State.hurt && state != State.Die)
            {
                RaycastHit2D lhit = Physics2D.Raycast(rb.position+new Vector2(0.4f,0), Vector2.down, 1.3f, ground);
                RaycastHit2D rhit = Physics2D.Raycast(rb.position + new Vector2(-0.4f, 0), Vector2.down, 1.3f, ground);
                if (lhit.collider != null || rhit.collider != null)
                {
                    Jump();
                }
            }
        }

        //攻撃   by ぇぬ
        if (CanAtack)
        {
            Atack();
        }

        AnimationState();
        anim.SetInteger("state", (int)state); //アニメーションステータスをセットするとこ

        Debug();
    }

    private void MoveLimit()
    {
        if (rb.velocity.magnitude > LimitSpeed)
        {
            rb.velocity = rb.velocity.normalized * LimitSpeed;
        }
    }

    private void Debug()
    {
        //UnityEngine.Debug.Log("Now scene is <color=red>" + SceneManager.GetActiveScene().name + "</color>");
        //UnityEngine.Debug.Log(rb.velocity.y);
        //UnityEngine.Debug.Log(coll.IsTouchingLayers(ground));
        //UnityEngine.Debug.Log(hDirection);

    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag=="Collectable")
        {
            cherry.Play();
            Destroy(collision.gameObject);
            PermanentUI.perm.cherries += 1;
            PermanentUI.perm.cherryTaxt.text = PermanentUI.perm.cherries.ToString();
            PermanentUI.perm.CherryScore();
            
        }
        //if(collision.tag=="Powerup")        //チュートリアルで使用したパワーアップコード。現在使用してません。
        //{
        //    Destroy(collision.gameObject);
        //    JumpForce = 25;
        //    GetComponent<SpriteRenderer>().color = Color.yellow;
        //    StartCoroutine(ResetPower());
        //}
        if (collision.tag == "AtackMode")
        {
            Destroy(collision.gameObject);
            GetComponent<SpriteRenderer>().color = Color.red;
            CanAtack = true;
        }
        if (collision.gameObject.tag == "Destroy")
        {
            PermanentUI.perm.currentHP = 0;
            PermanentUI.perm.healthAmount.text = PermanentUI.perm.currentHP.ToString();
            if (PermanentUI.perm.currentHP <= 0)
            {
                PermanentUI.perm.PlayerCount -= 1;
                state = State.Die;
            }
        }
        if (collision.gameObject.tag == "Enemy")
        {
            Enemy enemy = collision.gameObject.GetComponent<Enemy>();
            CollisionEnemy(enemy);
        }
    }

    void CollisionBullet(Bullet bullet)
    {
        state = State.hurt;

        HandleHealth();//ダメージ判定するとこ！HP0になったらリセット！！

        if (bullet.gameObject.transform.position.x > transform.position.x)
        {

            rb.velocity = new Vector2(-hurtForce, rb.velocity.y);

        }
        else
        {
            rb.velocity = new Vector2(hurtForce, rb.velocity.y);
        }
    }
    void CollisionEnemy(Enemy enemy)
    {

        if (state == State.falling)
        {
            enemy.JumpedOn();
            PermanentUI.perm.EnemyScore();
            Jump();
        }
        else
        {
            state = State.hurt;

            HandleHealth();//ダメージ判定するとこ！HP0になったらリセット！！

            if (enemy.gameObject.transform.position.x > transform.position.x)
            {

                rb.velocity = new Vector2(-hurtForce, rb.velocity.y);

            }
            else
            {
                rb.velocity = new Vector2(hurtForce, rb.velocity.y);
            }
        }
    }

    private void OnCollisionEnter2D(Collision2D other)
    {

        if(other.gameObject.tag=="Lift")
        {
            transform.SetParent(other.transform);
        }


        if (other.gameObject.tag == "Enemy")
        {
            Enemy enemy = other.gameObject.GetComponent<Enemy>();
            CollisionEnemy(enemy);
        }

        if (other.gameObject.tag == "HpEnemy")
        {
            HpEnemy HpEnemy = other.gameObject.GetComponent<HpEnemy>();
            CollisionHpEnemy(HpEnemy);
        }

        if (other.gameObject.tag == "Destroy")
        {
            PermanentUI.perm.currentHP = 0;
            PermanentUI.perm.healthAmount.text = PermanentUI.perm.currentHP.ToString();
            if (PermanentUI.perm.currentHP <= 0)
            {
                PermanentUI.perm.PlayerCount -= 1;
                state = State.Die;

            }
        }
        if (other.gameObject.tag == "Bullet")
        {
            Bullet bullet = other.gameObject.GetComponent<Bullet>();
            CollisionBullet(bullet);
        }
    }

    private void OnCollisionExit2D(Collision2D other)
    {
        if (other.gameObject.tag == "Lift")
        {
            transform.SetParent(null);
        }
    }

    private void CollisionHpEnemy(HpEnemy HpEnemy)
    {
        state = State.hurt;

        HandleHealth();//ダメージ判定するとこ！HP0になったらリセット！！

        if (HpEnemy.gameObject.transform.position.x > transform.position.x)
        {

            rb.velocity = new Vector2(-hurtForce, rb.velocity.y);

        }
        else
        {
            rb.velocity = new Vector2(hurtForce, rb.velocity.y);
        }
    }

    private void HandleHealth()
    {
        PermanentUI.perm.currentHP -= 1;
        PermanentUI.perm.healthAmount.text = PermanentUI.perm.currentHP.ToString();
        if (PermanentUI.perm.currentHP <= 0)
        {
            PermanentUI.perm.PlayerCount -= 1;
            state = State.Die;

            //PermanentUI.perm.Reset();
            //SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    private void Movement()
    {
        if (state != State.atack && state != State.Die)
        {
            hDirection = Input.GetAxis("Horizontal");

            float moveSpeed = 0.0f;

            //climb start
            if (canClimb && Mathf.Abs(Input.GetAxis("Vertical")) > .1f)
            {
                state = State.climb;
                rb.constraints = RigidbodyConstraints2D.FreezePositionX | RigidbodyConstraints2D.FreezeRotation;
                transform.position = new Vector3(ladder.transform.position.x, rb.position.y);
                rb.gravityScale = 0f;
            }

            //Moving Left
            if (hDirection < 0)
            {
                moveSpeed = -speed;
                transform.localScale = new Vector2(-1, 1);
                Left = true;
            }
            //Moving Right
            else if (hDirection > 0)
            {
                moveSpeed = speed;
                transform.localScale = Vector2.one;
                Left = false;
            }

            else
            {
                moveSpeed = 0;
            }

            rb.velocity = new Vector2(moveSpeed, rb.velocity.y);

            //Jumping
            
        }
    }

    private void Jump()
    {
        rb.velocity = new Vector2(rb.velocity.x, JumpForce);
        if (state != State.Die)
        {
            state = State.jumping;
        }
    }

    private void Atack()
    {
        if (state != State.hurt)
        {
            if (state != State.atack && state != State.Die && state != State.climb)
            {
                if (Input.GetButtonDown("Attack"))
                {
                    Throwse.Play();
                    state = State.atack;
                    GameObject g = Instantiate(atackball);
                    g.transform.position = atackball.transform.position;
                    g.transform.rotation = atackball.transform.rotation;

                    g.SetActive(true);

                }
            }
        }
    }

    private void AnimationState()
    {
        if(state==State.climb)
        {

        }

        else if (state == State.jumping)
        {
            if (rb.velocity.y < .1f)
            {
                state = State.falling;
            }
        }
        else if (state == State.falling)
        {
            if (coll.IsTouchingLayers(ground))
            {
                //UnityEngine.Debug.Log("ぐらうんど");
                PermanentUI.perm.CountReset();
                state = State.idle;
            }
        }
        else if (state == State.hurt)
        {
            if (Mathf.Abs(rb.velocity.x) < .1f && state != State.Die)
            {
               PermanentUI.perm.CountReset();
                state = State.idle;
            }
        }
        else if (rb.velocity.y < -.1f && state != State.Die)
        {
            state = State.falling;
        }
        else if (Mathf.Abs(rb.velocity.x) > 1f)
        {
            //moving
            if (state != State.atack && state != State.Die)
            {
                state = State.running;
            }

        }
        else
        {
            if (state != State.atack && state != State.Die)
            {
                state = State.idle;
            }
        }
    }

    private void FootStep()
    {
        footstep.Play();
    }

    private void AtackRelease()
    {
        if (coll.IsTouchingLayers(ground))
        {
            state = State.idle;
        }
        else if (rb.velocity.y < .1f)
        {
            state = State.falling;
        }
    }

    private IEnumerator ResetPower()
    {
        yield return new WaitForSeconds(10);
        JumpForce = 10;
        GetComponent<SpriteRenderer>().color = Color.white;
    }

    private void Climb()
    {
        if (Input.GetButtonDown("Jump"))
        {
            rb.constraints = RigidbodyConstraints2D.FreezeRotation;
            canClimb = false;
            rb.gravityScale = naturalGravity;
            anim.speed = 1f;
            Jump();
            return;
        }

        float vDirection = Input.GetAxis("Vertical");

        if (vDirection > .1f && !topLadder)
        {
            rb.velocity = new Vector2(0f, vDirection * climbSpeed);
            anim.speed = 1f;
        }
        else if (vDirection < -.1f && !bottomLadder)
        {
            rb.velocity = new Vector2(0f, vDirection * climbSpeed);
            anim.speed = 1f;
        }
        else
        {
            anim.speed = 0f;
            rb.velocity = Vector2.zero;
        }
    }

    private void DeathFreeze()
    {
        rb.velocity = Vector2.zero;
        rb.bodyType = RigidbodyType2D.Kinematic;
        //coll.isTrigger = true;
        GetComponent<Collider2D>().enabled = false;
    }

    private void DeathFall()
    {
        anim.SetTrigger("DFall");
        rb.bodyType = RigidbodyType2D.Dynamic;
        Jump();
    }

    private void DeathCount()
    {
        DCount++;
        if (DCount >= 10)
        {
            PermanentUI.perm.Reset();
            SceneManager.LoadScene("HalfScene");
        }
    }
}
