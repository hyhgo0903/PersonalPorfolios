﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    public static UIManager uIManager;

    private void Awake()
    {
        if (uIManager == null) uIManager = this;
    }

    void Update()
    {
        
    }
}
