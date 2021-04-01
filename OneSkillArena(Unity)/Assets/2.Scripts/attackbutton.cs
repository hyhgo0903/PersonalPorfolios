using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class attackbutton : MonoBehaviour
{
    public PlayerMove player;
    public Image image;

    private void Start()
    {
        image.type = Image.Type.Filled;
    }

    void Update()
    {
        image.fillAmount = 1f - player.GetDelRatio();
    }
}
