using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AlphaMinus : MonoBehaviour
{
    Image img;

    private void Start()
    {
        img = GetComponent<Image>();
    }

    void Update()
    {
        Color color = img.color;
        color.a -= 0.5f * Time.deltaTime;
        if (color.a < 0f) Destroy(gameObject);
        img.color = color;
    }
}
