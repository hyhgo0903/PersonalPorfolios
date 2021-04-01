using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 싱글톤으로 관리되며, 스킬 종류를 지정합니다.

public class SkillManager : MonoBehaviour
{
    public static SkillManager skm;
    public static SkillManager Instance
    {
        get {
            if (skm == null) skm = new SkillManager();
            return skm;
        }
    }
    public GameObject text1;
    public GameObject text2;
    public GameObject text3;

    // ####### 각 속성을 이넘으로 정의 #######
    // 첫줄은 기본보유, 둘째줄은 습득, 셋째줄은 조합
    public enum Elements {            // 원소
        Magic,
        Fire, Cold, Lightening,
        Ultimate
    }
    public enum SkillTrack {               // 궤적
        Bolt,
        Explosion, Nova, Multiple,
        Total
    }
    public enum SkillUtil {      // 스킬 특수능력
        NoUtil,        
        Bloody, Stun
    }


    public Elements currentElement;
    public SkillTrack currentTrack;
    public SkillUtil currentUtil;


    private void Awake()
    {
        if (null == skm) {
            skm = this;
            DontDestroyOnLoad(this.gameObject);
        }
        else  Destroy(this.gameObject);

    }

    private void Start()
    {
        currentElement = (Elements)GameDataManager.gdm.currentElement;
        currentTrack = (SkillTrack)GameDataManager.gdm.currentTrack;
        currentUtil = (SkillUtil)GameDataManager.gdm.currentUtil;
        SetText();
    }

    void SetText()
    {
        switch (currentElement)
        {
            case Elements.Magic:
                text2.GetComponent<UILabel>().text = "매직";
                break;
            case Elements.Fire:
                text2.GetComponent<UILabel>().text = "파이어";
                break;
            case Elements.Cold:
                text2.GetComponent<UILabel>().text = "콜드";
                break;
            case Elements.Lightening:
                text2.GetComponent<UILabel>().text = "라이트닝";
                break;
            case Elements.Ultimate:
                text2.GetComponent<UILabel>().text = "얼티밋";
                break;
        }
        switch (currentTrack)
        {
            case SkillTrack.Bolt:
                text3.GetComponent<UILabel>().text = "볼트";
                break;
            case SkillTrack.Explosion:
                text3.GetComponent<UILabel>().text = "붐";
                break;
            case SkillTrack.Nova:
                text3.GetComponent<UILabel>().text = "노바";
                break;
            case SkillTrack.Multiple:
                text3.GetComponent<UILabel>().text = "멀티샷";
                break;
            case SkillTrack.Total:
                text3.GetComponent<UILabel>().text = "스톰";
                break;
            default:
                break;
        }
        switch (currentUtil)
        {
            case SkillUtil.NoUtil:
                text1.GetComponent<UILabel>().text = "";
                break;
            case SkillUtil.Bloody:
                text1.GetComponent<UILabel>().text = "흡혈의";
                break;
            case SkillUtil.Stun:
                text1.GetComponent<UILabel>().text = "기절의";
                break;
        }
        
    }

    // Update is called once per frame
    void Update()
    {

        SetText();
        if (Input.GetKeyDown(KeyCode.E))
        {
            switch (currentElement)
            {
                case Elements.Magic:
                    currentElement = Elements.Fire;
                    break;
                case Elements.Fire:
                    currentElement = Elements.Cold;
                    break;
                case Elements.Cold:
                    currentElement = Elements.Lightening;
                    break;
                case Elements.Lightening:
                    currentElement = Elements.Ultimate;
                    break;
                case Elements.Ultimate:
                    currentElement = Elements.Magic;
                    break;
            }
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            switch (currentTrack)
            {
                case SkillTrack.Bolt:
                    currentTrack = SkillTrack.Explosion;
                    break;
                case SkillTrack.Explosion:
                    currentTrack = SkillTrack.Nova;
                    break;
                case SkillTrack.Nova:
                    currentTrack = SkillTrack.Multiple;
                    break;
                case SkillTrack.Multiple:
                    currentTrack = SkillTrack.Total;
                    break;
                case SkillTrack.Total:
                    currentTrack = SkillTrack.Bolt;
                    break;
            }
        }
        if (Input.GetKeyDown(KeyCode.T))
        {
            switch (currentUtil)
            {
                case SkillUtil.NoUtil:
                    currentUtil = SkillUtil.Bloody;
                    break;
                case SkillUtil.Bloody:
                    currentUtil = SkillUtil.Stun;
                    break;
                case SkillUtil.Stun:
                    currentUtil = SkillUtil.NoUtil;
                    break;
            }
        }
    }
}
