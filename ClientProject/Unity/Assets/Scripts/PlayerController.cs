using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;

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
    public Ladder ladder;
    private float naturalGravity;
    [SerializeField] float climbSpeed = 3f;

    //Inspector variables
    [SerializeField] private LayerMask ground;
    [SerializeField] private float speed = 5f;
    [SerializeField] private float JumpForce = 10f;
    [SerializeField] private float hurtForce = 10f;
    [SerializeField] private AudioSource cherry;
    [SerializeField] private AudioSource footstep;

    //ぇぬのコード用
    [SerializeField] private bool CanAtack = false;
    [SerializeField] private GameObject atackball;
    [SerializeField] private AudioSource Throwse;
    public bool Left = false;
    private int DCount;

    //本当は使いたくなかった変数たち
    int JumpCount;
    
    private void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        coll = GetComponent<Collider2D>();
        PermanentUI.perm.healthAmount.text = PermanentUI.perm.health.ToString();
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
        //攻撃   by ぇぬ
        if (CanAtack)
        {
            Atack();
        }

        AnimationState();
        anim.SetInteger("state", (int)state); //アニメーションステータスをセットするとこ

        Debug();
    }

    private void Debug()
    {
        //UnityEngine.Debug.Log("Now scene is <color=red>" + SceneManager.GetActiveScene().name + "</color>");
        //UnityEngine.Debug.Log(rb.velocity.y);
        //UnityEngine.Debug.Log(coll.IsTouchingLayers(ground));

    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag=="Collectable")
        {
            cherry.Play();
            Destroy(collision.gameObject);
            PermanentUI.perm.cherries += 1;
            PermanentUI.perm.cherryTaxt.text = PermanentUI.perm.cherries.ToString();
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
            PermanentUI.perm.health = 0;
            PermanentUI.perm.healthAmount.text = PermanentUI.perm.health.ToString();
            if (PermanentUI.perm.health <= 0)
            {
                state = State.Die;

            }
        }
        if (collision.gameObject.tag == "Enemy")
        {
            Enemy enemy = collision.gameObject.GetComponent<Enemy>();
            CollisionEnemy(enemy);
        }
    }

    void CollisionEnemy(Enemy enemy)
    {

        if (state == State.falling)
        {
            enemy.JumpedOn();
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
        if (other.gameObject.tag == "Enemy")
        {
            Enemy enemy = other.gameObject.GetComponent<Enemy>();
            CollisionEnemy(enemy);
        }

        if (other.gameObject.tag == "Destroy")
        {
            PermanentUI.perm.health = 0;
            PermanentUI.perm.healthAmount.text = PermanentUI.perm.health.ToString();
            if (PermanentUI.perm.health <= 0)
            {
                state = State.Die;

            }
        }
    }

    private void HandleHealth()
    {
        PermanentUI.perm.health -= 1;
        PermanentUI.perm.healthAmount.text = PermanentUI.perm.health.ToString();
        if (PermanentUI.perm.health <= 0)
        {
            state = State.Die;
            //PermanentUI.perm.Reset();
            //SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    private void Movement()
    {
        if (state != State.atack && state != State.Die)
        {
            float hDirection = Input.GetAxis("Horizontal");
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
                transform.localScale = new Vector2(1, 1);
                Left = false;
            }

            else
            {
                moveSpeed = 0;
            }

            UnityEngine.Debug.Log(moveSpeed);

            rb.velocity = new Vector2(moveSpeed, rb.velocity.y);

            //Jumping
            if (Input.GetButtonDown("Jump"))
            {
                if (coll.IsTouchingLayers(ground))
                {
                    Jump();
                }
            }
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
        if (state != State.atack && state != State.Die)
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
                state = State.idle;
            }
        }
        else if (state == State.hurt)
        {
            if (Mathf.Abs(rb.velocity.x) < .1f && state != State.Die)
            {
                CountReset();
                state = State.idle;
            }
        }
        else if (rb.velocity.y < -.1f && state != State.Die)
        {
            state = State.falling;
        }
        else if (Mathf.Abs(rb.velocity.x) > 2f)
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
        coll.isTrigger = true;
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
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
    public void ScoreUpdate()               //ややこしいバグを後回しにするための奴
    {
        PermanentUI.perm.ScoreText.text = PermanentUI.perm.scoreValue.ToString("D7");
    }



    private void CherryScore()               //以下同文
    {
        PermanentUI.perm.scoreValue += PermanentUI.perm.cherries * 100;
        ScoreUpdate();
    }
    private void EnemyScore()
    {
        JumpCount++;
        if (JumpCount > 8)
        {
            JumpCount = 8;
        }
        PermanentUI.perm.scoreValue += JumpCount * 100;
        ScoreUpdate();
    }
    private void CountReset()
    {
        JumpCount = 0;
    }

}
