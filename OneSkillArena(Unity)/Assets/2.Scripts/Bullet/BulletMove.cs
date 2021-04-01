using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletMove : MonoBehaviour
{
    public int type; // 0매직 1파이어 2콜드 3라이트닝 4궁극
    private float speed = 4f;
    private float durTime;

    public void init(int type, Transform position, Transform rotation)
    {   // 해당하는 이펙트로 켜줍니다

        if (SkillManager.skm.currentTrack == SkillManager.SkillTrack.Nova) durTime = 0.5f;
        else durTime = 2f;
        for (int i = 0; i < 5; ++i)
        {
            transform.GetChild(i).gameObject.SetActive(false);
        }
        transform.GetChild(type).gameObject.SetActive(true);

        if (SkillManager.skm.currentTrack == SkillManager.SkillTrack.Nova
            || SkillManager.skm.currentTrack == SkillManager.SkillTrack.Total)
        { // 노바형은 플레이어에서 나가고 이외는 손위치에서 나가도록 했습니다.
            transform.position = rotation.position + Vector3.up * 0.7f; // 몸에서
        }
        else transform.position = position.position; // 손에서

        transform.rotation = rotation.rotation; // 방향은 플레이어 방향따라

        if (SkillManager.skm.currentTrack == SkillManager.SkillTrack.Explosion
            || SkillManager.skm.currentTrack == SkillManager.SkillTrack.Total)
        { // 펑터지는건 크게했습니다
            transform.localScale = new Vector3(1.2f, 1.2f, 1.2f);
        }
        else transform.localScale = new Vector3(0.7f, 0.7f, 0.7f);
    }

    void Update()
    {
        if (GameSceneButtonManager.gm.gamePause || GameSceneButtonManager.gm.gameClear) bulletOff();
        transform.position += transform.forward * speed * Time.deltaTime; // 이동합니다
        //지속시간. 보통은 화면이나 맞고 꺼질테지만 노바는 짧아서 여기에 잘 걸릴듯
        durTime -= Time.deltaTime;
        if (durTime <= 0)
        {
            bulletOff();
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        //GameObject effect = Instantiate(effectFactory);
        //effect.transform.position = transform.position;

        if (other.gameObject.tag.Contains("Enemy")
            && other.GetComponent<EnemyMove>().enemyState == EnemyMove.EnemyState.Die) return;

        if (other.gameObject.tag.Contains("Enemy") &&
            SkillManager.skm.currentTrack != SkillManager.SkillTrack.Explosion
        && SkillManager.skm.currentTrack != SkillManager.SkillTrack.Total)
        {
            other.gameObject.GetComponent<EnemyMove>().dealDamage(10);
        }

        if (SkillManager.skm.currentTrack == SkillManager.SkillTrack.Explosion
        || SkillManager.skm.currentTrack == SkillManager.SkillTrack.Total)
        {
            Collider[] cols = Physics.OverlapSphere(transform.position, 2.5f, 1 << 12);
            //쉬프트연산자(빠름) 에너미레이어가 12번이기 때문에
            for (int i = 0; i < cols.Length; ++i)
            {
                cols[i].GetComponent<EnemyMove>().dealDamage(10);
            }
        }


        if (other.gameObject.tag.Contains("Player")) return;
        if (SkillManager.skm.currentTrack == SkillManager.SkillTrack.Explosion
            || SkillManager.skm.currentTrack == SkillManager.SkillTrack.Total)
        {
            BulletManager.bm.bigEffect(gameObject.transform);
        }
        else BulletManager.bm.smallEffect(gameObject.transform);
        bulletOff();
    }

    private void bulletOff()
    {
        BulletManager.bm.bulletObjectPool.Enqueue(gameObject);
        for (int i = 0; i < 5; ++i)
        {
            transform.GetChild(type).gameObject.SetActive(false);
        }
        gameObject.SetActive(false);
    }
}
