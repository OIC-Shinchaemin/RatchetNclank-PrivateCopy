using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndingFox1 : MonoBehaviour
{
    private Rigidbody2D rb;
    private Animator anim;
    private enum State { idle, running, jumping, falling }
    private State state = State.idle;

    private float second;
    private bool moved = false;
    [SerializeField] private AudioSource footstep;
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        rb = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        second += Time.deltaTime;
        if (!moved)
        {
            if (second < 4.0f)
            {
                state = State.running;
                rb.velocity = new Vector2(3f, rb.velocity.y);

            }
            else if(second < 4.5f)
            {
                state = State.idle;
            }
            else if (second > 4.5)
            {
                state = State.idle;
                second = 0f;
                moved = true;

            }
        }
        else
        {
            if (second > 1.0f && state != State.jumping && state != State.falling)
            {
                state = State.jumping;

                rb.velocity = new Vector2(rb.velocity.x, 10f);
            }
            else if (state == State.jumping && rb.velocity.y < .1f)
            {
                state = State.falling;
            }
            else if (state == State.falling && rb.velocity.y == 0)
            {
                state = State.idle;
            }
        }
        anim.SetInteger("state", (int)state);

    }
    private void FootStep()
    {
        footstep.Play();
    }
}
