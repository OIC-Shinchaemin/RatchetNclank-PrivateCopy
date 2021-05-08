using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGM : MonoBehaviour
{


    [SerializeField] private AudioSource title;
    [SerializeField] private AudioSource field;
    [SerializeField] private AudioSource under;
    [SerializeField] private AudioSource sky;
    [SerializeField] private AudioSource miss;
    [SerializeField] private AudioSource gameover;
    [SerializeField] private AudioSource ending;


    public enum Musicstate { title,stage1, stage2, understage, death, gameover, gameend,stop };
    public Musicstate state = Musicstate.title;
    public static BGM bgm;


    public bool isTitle,isField,isUnder,isSky,isMiss,isGameover,isEnd;






    // Start is called before the first frame update
    void Start()
    {
        DontDestroyOnLoad(this);

        if(!bgm)
        {
            bgm = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (state == Musicstate.title && !isTitle)
        {
            title.Play();
            isTitle = true;
        }
        else if (state == Musicstate.stage1 && !isField)
        {
            field.Play();
            isField = true;
        }
        else if (state == Musicstate.stage2 && !isSky)
        {
            sky.Play();
            isSky = true;
        }
        else if (state == Musicstate.understage && !isUnder)
        {
            under.Play();
            isUnder = true;
        }
        else if (state == Musicstate.death && !isMiss)
        {

            Allstop();
            
            isMiss = true;
            miss.Play();
        }
        else if (state == Musicstate.gameover && !isGameover)
        {
            gameover.Play();
            isGameover = true;
        }
        else if (state == Musicstate.gameend && !isEnd)
        {
            ending.Play();
            isEnd = true;
        }
        else if (state == Musicstate.stop) 
        {
            Allstop();
        }

    }


    private void Allstop()
    {
        isTitle = isField = isUnder = isSky = isMiss = isGameover = isEnd = false;
        title.Stop();
        field.Stop();
        under.Stop();
        sky.Stop();
        miss.Stop();
    }
    public void GameEnd()
    {
        Destroy(gameObject);
    }
}
