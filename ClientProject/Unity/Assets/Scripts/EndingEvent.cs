using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class EndingEvent : MonoBehaviour
{

    [SerializeField] TextMeshProUGUI ClearText;
    [SerializeField] GameObject NormalFox;
    [SerializeField] GameObject PinkFox;
    [SerializeField] GameObject ResultController;
    private Rigidbody2D nrb;
    private Rigidbody2D prb;
    private Animator nanim;
    private Animator panim;
    private enum State { idle, running, jumping, falling}

    private State nstate = State.idle;
    private State pstate = State.idle;






    private float second;
    private bool moved = false;
    private bool pLeft = false;



    private void Start()
    {
        PermanentUI.perm.stage.text = "";
        PermanentUI.perm.SceneName.text = "";
        nrb = NormalFox.GetComponent<Rigidbody2D>();
        prb = PinkFox.GetComponent<Rigidbody2D>();
        nanim = NormalFox.GetComponent<Animator>();
        panim = PinkFox.GetComponent<Animator>();
    }

    void Update()
    {
        NormalFox.transform.localScale = Vector2.one;
        if(pLeft)
        {
            PinkFox.transform.localScale = new Vector2(-0.7f, 0.7f);
        }
        else
        {
            PinkFox.transform.localScale = new Vector2(0.7f, 0.7f);
        }
        second += Time.deltaTime;


        if(!moved)
        {

            if (second < 4.0f)
            {
                nstate = State.running;
                nrb.velocity = new Vector2(3f, nrb.velocity.y);

            }
            else
            {
                nstate = State.idle;
            }
            if(second > 1.0f)
            {
                pLeft = true;
            }
            if (second > 3.0f && second < 4.5f)
            {
                pstate = State.running;
                prb.velocity = new Vector2(-3f, prb.velocity.y);
            }
            else if(second >4.5)
            {
                pstate = State.idle;
                second = 0f;
                moved = true;

            }
        }
        else
        {
            
            if (second > 1.0f && nstate != State.jumping && nstate != State.falling)
            {
                ClearText.text = "Game Clear!!";
                nstate = State.jumping;

                nrb.velocity = new Vector2(nrb.velocity.x, 10f);
            }
            else if (nstate == State.jumping && nrb.velocity.y < .1f)
            {
                nstate = State.falling;
            }
            else if (nstate == State.falling && nrb.velocity.y == 0) 
            {
                nstate = State.idle;
            }
            if (second > 1.0f && pstate != State.jumping && pstate != State.falling)
            {
                pstate = State.jumping;

                prb.velocity = new Vector2(prb.velocity.x, 10f);
            }
            else if (pstate == State.jumping && prb.velocity.y < .1f)
            {
                pstate = State.falling;
            }
            else if (pstate == State.falling && prb.velocity.y == 0)
            {
                pstate = State.idle;
            }

            if(second >5f)
            {
                ResultController.SetActive(true);
                ClearText.text = "";
            }

        }

        


        nanim.SetInteger("state", (int)nstate);
        panim.SetInteger("state", (int)pstate);
    }

}
