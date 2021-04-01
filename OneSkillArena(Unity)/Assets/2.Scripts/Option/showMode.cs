using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class showMode : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        modeShow();
    }

    public void modeShow()
    {
        if (OptionManager.om.keyBoardMode)
        {
            GetComponent<UILabel>().text = "키보드";
        }
        else GetComponent<UILabel>().text = "조이패드";
    }
}
