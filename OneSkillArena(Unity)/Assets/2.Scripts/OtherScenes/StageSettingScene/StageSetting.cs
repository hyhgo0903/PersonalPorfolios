using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class StageSetting : MonoBehaviour
{
    public GameObject TotalMap;
    public GameObject enemyNumLabel;
    public GameObject enemyWeakLabel;
    public GameObject enemyHpLabel;
    public GameObject enemyDmgLabel;
    public GameObject rerollbutton;
    public GameObject rerollLabel;
    public GameObject stageNum;
    public GameObject attributeLabel;
    public GameObject SkillElementLabel;
    public GameObject SkillTrackLabel;
    public GameObject SkillUtilLabel;
    public Customize enemyModel;
    GameDataManager gdm;
    private bool rerolled;
    private bool gameStart = false;
    public Image img;

    private void Awake()
    {
        gdm = GameDataManager.GetInstance();
        ++gdm.stageNum;
        if (gdm.enemyNum != 0) // 중간에 세이브로 저장한것
        { // 클리어시 이거 초기화함
            --gdm.stageNum;
            rerolled = true;
            rerollbutton.GetComponent<UIButton>().isEnabled = false;
            rerollLabel.GetComponent<UILabel>().text = "(0회)";
        }
        else EnemyRandomCustomize();
        stageNum.GetComponent<UILabel>().text = "스테이지 " + gdm.stageNum;
        rerolled = false;
        SkillChanged();
    }

    private void SkillChanged()
    {
        switch (gdm.currentElement)
        {
            case 0:
                SkillElementLabel.GetComponent<UILabel>().text = "매직";
                break;
            case 1:
                SkillElementLabel.GetComponent<UILabel>().text = "파이어";
                break;
            case 2:
                SkillElementLabel.GetComponent<UILabel>().text = "콜드";
                break;
            case 3:
                SkillElementLabel.GetComponent<UILabel>().text = "라이트닝";
                break;
            case 4:
                SkillElementLabel.GetComponent<UILabel>().text = "얼티밋";
                break;
        }

        switch (gdm.currentTrack)
        {
            case 0:
                SkillTrackLabel.GetComponent<UILabel>().text = "볼트";
                break;
            case 1:
                SkillTrackLabel.GetComponent<UILabel>().text = "붐";
                break;
            case 2:
                SkillTrackLabel.GetComponent<UILabel>().text = "노바";
                break;
            case 3:
                SkillTrackLabel.GetComponent<UILabel>().text = "멀티샷";
                break;
            case 4:
                SkillTrackLabel.GetComponent<UILabel>().text = "스톰";
                break;
        }

        switch (gdm.currentUtil)
        {
            case 0:
                SkillUtilLabel.GetComponent<UILabel>().text = "(유틸X)";
                break;
            case 1:
                SkillUtilLabel.GetComponent<UILabel>().text = "흡혈";
                break;
            case 2:
                SkillUtilLabel.GetComponent<UILabel>().text = "기절";
                break;
        }
    }

    public void plusElement()
    {
        ++gdm.currentElement;
        if (gdm.currentElement > 4) gdm.currentElement = 0;

        // 없으면 다음으로 넘긴다
        if ((gdm.currentElement == 1 && !gdm.itemBox[0])
            || (gdm.currentElement == 2 && !gdm.itemBox[1])
            || (gdm.currentElement == 3 && !gdm.itemBox[2])
            || (gdm.currentElement == 4 && (!gdm.itemBox[0] || !gdm.itemBox[1] || !gdm.itemBox[2])))
            plusElement();
        else SkillChanged();
    }

    public void minusElement()
    {
        --gdm.currentElement;
        if (gdm.currentElement < 0) gdm.currentElement = 4;

        // 없으면 다음으로 넘긴다
        if ((gdm.currentElement == 1 && !gdm.itemBox[0])
            || (gdm.currentElement == 2 && !gdm.itemBox[1])
            || (gdm.currentElement == 3 && !gdm.itemBox[2])
            || (gdm.currentElement == 4 && (!gdm.itemBox[0] || !gdm.itemBox[1] || !gdm.itemBox[2])))
            minusElement();
        else SkillChanged();
    }

    public void plusTrack()
    {
        ++gdm.currentTrack;
        if (gdm.currentTrack > 4) gdm.currentTrack = 0;

        // 없으면 다음으로 넘긴다
        if ((gdm.currentTrack == 1 && !gdm.itemBox[3])
            || (gdm.currentTrack == 2 && !gdm.itemBox[4])
            || (gdm.currentTrack == 3 && !gdm.itemBox[5])
            || (gdm.currentTrack == 4 && (!gdm.itemBox[3] || !gdm.itemBox[4] || !gdm.itemBox[5])))
            plusTrack();
        else SkillChanged();
    }

    public void minusTrack()
    {
        --gdm.currentTrack;
        if (gdm.currentTrack < 0) gdm.currentTrack = 4;

        // 없으면 다음으로 넘긴다
        if ((gdm.currentTrack == 1 && !gdm.itemBox[3])
            || (gdm.currentTrack == 2 && !gdm.itemBox[4])
            || (gdm.currentTrack == 3 && !gdm.itemBox[5])
            || (gdm.currentTrack == 4 && (!gdm.itemBox[3] || !gdm.itemBox[4] || !gdm.itemBox[5])))
            minusTrack();
        else SkillChanged();
    }

    public void plusUtil()
    {
        ++gdm.currentUtil;
        if (gdm.currentUtil > 2) gdm.currentUtil = 0;

        // 없으면 다음으로 넘긴다
        if ((gdm.currentUtil == 1 && !gdm.itemBox[6])
            || (gdm.currentUtil == 2 && !gdm.itemBox[7]))
            plusUtil();
        else SkillChanged();
    }
    
    public void minusUtil()
    {
        --gdm.currentUtil;
        if (gdm.currentUtil < 0) gdm.currentUtil = 2;

        // 없으면 다음으로 넘긴다
        if ((gdm.currentUtil == 1 && !gdm.itemBox[6])
            || (gdm.currentUtil == 2 && !gdm.itemBox[7]))
            minusUtil();
        else SkillChanged();
    }

    public void rerollClicked()
    {
        rerolled = true;
        rerollbutton.GetComponent<UIButton>().isEnabled = false;
        rerollLabel.GetComponent<UILabel>().text = "(0회)";
        enemyModel.enemyInit();
    }

    public void EnemyRandomCustomize()
    {
        if (rerolled) return;
        gdm.enemyNum = Random.Range(2, 6);
        enemyNumLabel.GetComponent<UILabel>().text = "지점당 적의 수 : " + gdm.enemyNum + "명";
        
        gdm.enemyHp = ((50 * gdm.stageNum) + Random.Range(50, 80)) / gdm.enemyNum;
        enemyHpLabel.GetComponent<UILabel>().text = "적 최대체력 : " + gdm.enemyHp;

        gdm.enemyDmg = ((2 * gdm.stageNum) + Random.Range(2, 5));
        enemyDmgLabel.GetComponent<UILabel>().text = "적 공격력 : " + gdm.enemyDmg;


        gdm.enemyAttribute = Random.Range(0, 4);
        // 첫판은 무속성 고정
        if (gdm.stageNum == 1) gdm.enemyAttribute = 0;
        switch (gdm.enemyAttribute)
        {
            case 0:
                attributeLabel.GetComponent<UILabel>().text = "특징 : 없음";
                break;
            case 1:
                attributeLabel.GetComponent<UILabel>().text = "특징 : 빠른 속도";
                break;
            case 2:
                attributeLabel.GetComponent<UILabel>().text = "특징 : 보호막(첫 공격 무효)";
                break;
            case 3:
                attributeLabel.GetComponent<UILabel>().text = "특징 : 멀리서 달려듦";
                break;
        }


        gdm.enemyWeakness = Random.Range(1, 4);
        switch (gdm.enemyWeakness)
        {
            case 1:
                enemyWeakLabel.GetComponent<UILabel>().text = "약점 : 화염";
                break;
            case 2:
                enemyWeakLabel.GetComponent<UILabel>().text = "약점 : 콜드";
                break;
            case 3:
                enemyWeakLabel.GetComponent<UILabel>().text = "약점 : 라이트닝";
                break;
        }

        //enemyDelay;
        gdm.enemyWweaponIndex = Random.Range(0, 10);
        gdm.enemyLweaponIndex = Random.Range(0, 10);
        gdm.enemyChestsIndex = Random.Range(0, 10);
        gdm.enemyHipsIndex = Random.Range(0, 10);
        gdm.enemyKneesIndex = Random.Range(0, 10);
        gdm.enemyRootsIndex = Random.Range(0, 10);
        gdm.enemySpinesIndex = Random.Range(0, 10);
        gdm.enemyAccessoriesIndex = Random.Range(0, 10);
        gdm.enemyHairsIndex = Random.Range(0, 10);
        gdm.enemyHeadsIndex = Random.Range(0, 10);
        gdm.enemyElbowsIndex = Random.Range(0, 9);
        gdm.enemyShouldersIndex = Random.Range(0, 9);
    }

    void Update()
    {
        if (TotalMap.transform.position.y > 0)
        {
            TotalMap.transform.position += Vector3.down;
        }
        else
        {
            TotalMap.transform.Rotate(0.3f * Vector3.up);
        }

        if(gameStart)
        {
            Color color = img.color;
            color.a += 0.5f * Time.deltaTime;
            if (color.a > 1f)
                SceneManager.LoadScene(2);
            img.color = color;
        }

        if (Input.GetKeyDown(KeyCode.Q))
        {
            for(int i = 0; i < 8; ++i)
            {
                gdm.itemBox[i] = true;
            }
        }
    }

    public void StartButton()
    {
        gameStart = true;
    }
}
