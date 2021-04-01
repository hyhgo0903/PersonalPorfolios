using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class GameDataManager
{ // monobehaviour 상속을 받지 않는 싱글톤
    private GameDataManager() { }
    public static GameDataManager gdm = null;
    public static GameDataManager GetInstance()
    {
        if (gdm == null) { gdm = new GameDataManager(); }
        return gdm;
    }

    // ############### json관련 불러올 파일명 #########
    public string ID;

    // ############### 스테이지 관련 #################
    public int stageNum; // 몇번쨰 스테이지인지

    // ############### 플레이어 관련 #################
    public int playerHp;
    public float playerDelay;
    public float playerMoveSpeed;
    public int playerWweaponIndex;
    public int playerLweaponIndex;
    public int playerAccessoriesIndex;
    public int playerChestsIndex;
    public int playerElbowsIndex;
    public int playerHairsIndex;
    public int playerHeadsIndex;
    public int playerHipsIndex;
    public int playerKneesIndex;
    public int playerRootsIndex;
    public int playerShouldersIndex;
    public int playerSpinesIndex;

    // ############### 스킬보유 관련 #################
    public bool[] itemBox = new bool[8];
    // 파이어 아이스 라이트닝 붐 멀티샷 노바 흡혈 

    public int currentElement;
    public int currentTrack;
    public int currentUtil;

    // ############### 에너미 관련 #################
    public int enemyNum; // 각 구역당 에너미 몇명
    public int enemyWeakness; // 불1 콜드2 라이트닝3 맞으면 데미지 2배, 전능은 그냥 3배
    public int enemyAttribute;
    public int enemyDmg;
    public int enemyHp;
    public int enemyDelay;
    public int enemyWweaponIndex;
    public int enemyLweaponIndex;
    public int enemyAccessoriesIndex;
    public int enemyChestsIndex;
    public int enemyElbowsIndex;
    public int enemyHairsIndex;
    public int enemyHeadsIndex;
    public int enemyHipsIndex;
    public int enemyKneesIndex;
    public int enemyRootsIndex;
    public int enemyShouldersIndex;
    public int enemySpinesIndex;





    void Awake()
    {
        if (null == gdm)
        {
            gdm = this;
        }
        playerDelay = 0f;
        playerHp = playerWweaponIndex =
        stageNum = enemyNum = playerAccessoriesIndex = playerChestsIndex = playerElbowsIndex =
        playerHairsIndex = playerHeadsIndex = playerHipsIndex = playerKneesIndex =
        playerRootsIndex = playerShouldersIndex = playerSpinesIndex = 0;
        for (int i = 0; i < 8; ++i)
        {
            itemBox[i] = false;
        }
    }
}
