using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AvataRotate : MonoBehaviour
{
    Animator anim;
    public GameObject buttonManager;

    private void Awake()
    {
        anim = gameObject.GetComponent<Animator>();
    }

    void Update()
    {
        if (buttonManager.GetComponent<CustomizeButton>().isRotate)
            gameObject.transform.Rotate(Time.deltaTime * 120f * Vector3.up);
    }
}
