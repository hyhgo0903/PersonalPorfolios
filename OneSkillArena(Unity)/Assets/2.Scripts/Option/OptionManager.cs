using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class OptionManager : MonoBehaviour
{

    public static OptionManager om = null;
    public static OptionManager Instance
    {
        get {
            if (null == om) {return null;}
            return om;
        }
    }

    public bool keyBoardMode = false;
    public float dpi = 5f;

    public float getDpi() { return dpi; }
    public bool getKeyBoardMode() { return keyBoardMode; }
    public void setKeyBoardMode(bool mode) { keyBoardMode = mode; }
        

    private void Awake()
    {
        if (null == om)
        {//인스턴스가 탄생했을 때 전역변수 instance에 게임매니저 인스턴스가 담겨있지 않다면, 자신을 넣어준다.
            om = this;            
            DontDestroyOnLoad(this.gameObject); //씬 전환이 되더라도 파괴되지 않게 한다.
        }
        else {
            //만약 씬 이동이 되었는데 그 씬에도 Hierarchy에 GameMgr이 존재할 수도 있다.
            //그래서 이미 전역변수인 instance에 인스턴스가 존재한다면 새로운 씬의 인스턴스 삭제
            Destroy(this.gameObject);
        }

    }


}
