using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PartsSetting : MonoBehaviour
{
    PartsSetting ps;

    private Customize plCustom;

    private void Awake()
    {
        if (null == ps)
        {//인스턴스가 탄생했을 때 전역변수 instance에 게임매니저 인스턴스가 담겨있지 않다면, 자신을 넣어준다.
            ps = this;
        }
        plCustom = GameObject.Find("PlayerAni").GetComponent<Customize>();            
    }
    
    void Update()
    {

    }
}
