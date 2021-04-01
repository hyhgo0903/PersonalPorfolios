using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EffectDel : MonoBehaviour
{
    private float durTime = 2f;

    // Update is called once per frame
    void Update()
    {
        durTime -= Time.deltaTime;
        if (durTime <= 0)
        {
            Destroy(gameObject);
        }
    }
}
