using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CustomizeResources : MonoBehaviour
{

    public GameObject[] weapons;
    public GameObject[] accessories;
    public GameObject[] chests;
    public GameObject[] elbows;
    public GameObject[] hairs;
    public GameObject[] heads;
    public GameObject[] hips;
    public GameObject[] knees;
    public GameObject[] roots;
    public GameObject[] shoulders;
    public GameObject[] spines;

    public static CustomizeResources cr = null;
    public static CustomizeResources Instance
    {
        get
        {
            if (null == cr) { return null; }
            return cr;
        }
    }


    private void Awake()
    {
        if (null == cr)
        {
            cr = this;
            DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            Destroy(this.gameObject);
        }
    }
}
