using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGMSelector : MonoBehaviour
{
    public bool IsBossStage;
    public GameObject MusicChanger;
    public bool field;
    public bool sky;
    public bool under;
    public BossEvent bossEvent;
    public HpEnemy BossHp;
    // Start is called before the first frame update
    void Start()
    {
        BGM.bgm.isMiss = false;
        BGMChange();
    }
    private void Update()
    {
        if(IsBossStage)
        {
            bossBGMPlay();
        }
      
    }
    private void bossBGMPlay()
    {
        if (bossEvent.bBoss == true)
        {
            if(PermanentUI.perm.currentHP<=0)
            {
                MusicChanger.SetActive(false);
            }
            else
            {

                BGM.bgm.state = BGM.Musicstate.stop;
                MusicChanger.SetActive(true);
            }
        }
        else if(BossHp.health <= 0)
        {
            MusicChanger.SetActive(false);
            if (PermanentUI.perm.currentHP > 0)
            {
                BGMChange();
                Destroy(gameObject);

            }
        }
    }
    private void BGMChange()
    {

        if (field == true)
        {
            BGM.bgm.state = BGM.Musicstate.stage1;
 
 
        }
        if (sky == true)
        {
            BGM.bgm.state = BGM.Musicstate.stage2; 
           
        }
        if (under == true)
        {
            BGM.bgm.state = BGM.Musicstate.understage;

        }
    }

}
