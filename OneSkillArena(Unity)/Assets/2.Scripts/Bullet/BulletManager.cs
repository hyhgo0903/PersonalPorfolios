using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletManager : MonoBehaviour
{
    public static BulletManager bm = null;
    public static BulletManager Instance
    {
        get
        {
            if (null == bm) { return null; }
            return bm;
        }
    }

    int poolSize = 100;
    public Queue<GameObject> bulletObjectPool;

    private void Awake()
    {
        if (null == bm)        {
            bm = this;
            DontDestroyOnLoad(this.gameObject);
        }
        else        {
            Destroy(this.gameObject);
        }
    }


    public GameObject bulletPrefab;// 총알
    public GameObject bulletEffect;// 걍터지는 이펙
    public GameObject bombEffect;  // 펑터지는 이펙


    private void Start()
    {
        bulletObjectPool = new Queue<GameObject>();
        for (int i = 0; i < poolSize; ++i)
        {
            GameObject bullet = Instantiate(bulletPrefab);
            bullet.SetActive(false);
            bulletObjectPool.Enqueue(bullet);
        }
    }

    public void smallEffect(Transform transform)
    {
        Instantiate(bulletEffect, transform.position, transform.rotation);
    }

    public void bigEffect(Transform transform)
    {
        Instantiate(bombEffect, transform.position, transform.rotation);
    }

    public void PlayerFire()
    {
        switch (SkillManager.skm.currentTrack)
        {
            case SkillManager.SkillTrack.Bolt:
                PFireInstantiate(0f);
                break;
            case SkillManager.SkillTrack.Explosion: // 맞으면 펑
                PFireInstantiate(0f);
                break;
            case SkillManager.SkillTrack.Nova: // 원형으로 나가는데 짧음
                for (int i = 0; i < 12; ++i)
                {
                    PFireInstantiate(30f*i);
                }
                break;
            case SkillManager.SkillTrack.Multiple: // 5발 부채꼴
                for (int i = 0; i < 5; ++i)
                {
                    PFireInstantiate(-40f + 20f * i);
                }
                break;
            case SkillManager.SkillTrack.Total: // 원형 + 멀리 + 폭발까지
                for (int i = 0; i < 12; ++i)
                {
                    PFireInstantiate(30f * i);
                }
                break;
        }
        
    }

    public void PFireInstantiate(float angle)
    {
        if (bulletObjectPool.Count <= 0)
        { // 없으면 만들어서 추가해놓는다
            GameObject bullet = Instantiate(bulletPrefab);
            bullet.SetActive(false);
            bulletObjectPool.Enqueue(bullet);
        }
        GameObject dequeuedBullet = bulletObjectPool.Dequeue();
        dequeuedBullet.SetActive(true);
        int temp = (int)SkillManager.skm.currentElement;
        dequeuedBullet.GetComponent<BulletMove>().init(temp,
                GameObject.FindWithTag("PlayerFirePos").transform,
                GameObject.FindWithTag("Player").transform);
        dequeuedBullet.transform.Rotate(0f,angle,0f);
    }

}
