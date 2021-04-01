using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.UI;

public class EnemyMove : MonoBehaviour
{
    public enum EnemyState
    {
        Idle, Move, Attack, Damaged, Die
    }
    public EnemyState enemyState;

    

    Animator anim;
    public int hp;
    public int maxHp;
    private int attackDamage;
    private int weakness;
    Transform target;
    NavMeshAgent nav;
    GameDataManager gdm;

    private float findDistance;
    private float attackDistance;
    private float maxAttackDistance;
    private float moveAround = 0f;

    float currentTime = 0;
    float attackDelay = 2.0f;

    CharacterController cc;
    public Slider hpSlider;
    public GameObject damagePrefab;

    private void Awake()
    {
        enemyState = EnemyState.Idle;
        nav = GetComponent<NavMeshAgent>();
        nav.enabled = false;
        anim = GetComponentInChildren<Animator>();
        target = GameObject.FindWithTag("Player").transform;
        gdm = GameDataManager.GetInstance();

    }

    void Start()
    {
        maxHp = gdm.enemyHp;
        hp = maxHp;
        if (transform.position.x < 1f && transform.position.x > -1f)
        {
            MultiplyHP(gdm.enemyNum);
        }
        weakness = gdm.enemyWeakness;
        attackDamage = gdm.enemyDmg;
        GetComponentInChildren<Customize>().enemyInit();
        cc = GetComponent<CharacterController>();

        findDistance = 9.0f;
        attackDistance = 1f;
        maxAttackDistance = 2f;
        switch (gdm.enemyAttribute)
        {
            case 0:
                break;
            case 1:
                GetComponent<NavMeshAgent>().speed = 8f;
                break;
            case 2:
                break;
            case 3:
                findDistance = 18f;
                break;
        }
    }


    // Update is called once per frame
    void Update()
    {
        if (GameSceneButtonManager.gm.gamePause || GameSceneButtonManager.gm.gameClear) return;
        
        if (Input.GetKeyDown(KeyCode.Q))
        {
            if (transform.position.y < 3) dealDamage(maxHp);
        }

        switch (enemyState)
        {
            case EnemyState.Idle:
                Idle();
                break;
            case EnemyState.Move:
                nav.enabled = true;
                nav.destination = target.position;
                Move();
                break;
            case EnemyState.Attack:
                Attack();
                break;
            case EnemyState.Damaged:
                Damaged();
                break;
            case EnemyState.Die:
                break;
        }

        anim.SetBool("isMove", enemyState == EnemyState.Move);
        if(hpSlider != null) hpSlider.value = (float)hp / (float)maxHp;
    }

    public void MultiplyHP(int multiply)
    {
        maxHp = multiply * maxHp;
        hp = maxHp;
    }

    private void ChangeState(EnemyState state)
    {
        enemyState = state;
        switch (state)
        {
            case EnemyState.Idle:
                if (nav.enabled) nav.enabled = false;
                Idle();
                break;
            case EnemyState.Move:
                if (!nav.enabled) nav.enabled = true;
                Move();
                break;
            case EnemyState.Attack:
                if (nav.enabled) nav.enabled = false;
                Attack();
                break;
            case EnemyState.Damaged:
                if (nav.enabled) nav.enabled = false;
                Damaged();
                break;
            case EnemyState.Die:
                if (nav.enabled) nav.enabled = false;
                break;
        }
    }


    void Idle()
    {
        if(transform.position.y < 3) moveAround -= Time.deltaTime;
        if (moveAround > 0f)
        {
            anim.SetTrigger("MoveAroundStart");
            cc.Move(1f*Time.deltaTime*transform.forward);
        }
        else if (moveAround <= 0f)
        {
            anim.SetTrigger("MoveAroundEnd");
            if (moveAround < -4f)
            {
                transform.Rotate(new Vector3(0, Random.Range(0,360), 0));
                moveAround = Random.Range(1f, 2f);
            }
        }

        if (Vector3.Distance(transform.position, target.position)
            < findDistance && (transform.position.y - target.position.y <= 1f))
        {
            enemyState = EnemyState.Move;
            anim.SetTrigger("IdleToMove");
        }
    }

    void Move()
    {
        if (Vector3.Distance(transform.position,
            target.position) <= attackDistance)
        {
            ChangeState(EnemyState.Attack);
            if (currentTime < attackDelay) currentTime += Time.deltaTime;
            anim.SetTrigger("MoveToAttackDelay");
        }
    }

    void Attack()
    {
        // 공격범위 안에 들어오면
        if (Vector3.Distance(transform.position,
            target.position) < maxAttackDistance)
        { // 공격
            currentTime += Time.deltaTime;
            if (currentTime > attackDelay)
            {                
                target.parent.gameObject.GetComponent<PlayerMove>().GetDmg(attackDamage);
                currentTime = 0;
                anim.SetTrigger("NormAtk");
            }
        }
        else
        { // 아니면 재 탐색 혹은 추격
            ChangeState(EnemyState.Move);
            if (currentTime < attackDelay) currentTime += Time.deltaTime;
            anim.SetTrigger("AttackToMove");
        }
    }

    void Damaged()
    {
        //예를 들면 피격 상태를 처리하기 위한 코루틴을 선언

        StartCoroutine(DamagedProcess());
    }

    IEnumerator DamagedProcess()
    {//0.19초
        if (SkillManager.skm.currentUtil == SkillManager.SkillUtil.Stun)
        {
            anim.speed = 0.2f;
            yield return new WaitForSeconds(1f);
        }
        else
        {
            anim.speed = 2f;
            yield return new WaitForSeconds(0.1f);
        }

        anim.speed = 1f;
        ChangeState(EnemyState.Move);
    }

    void Die()
    {//죽었으니까 첫번째론 피격중인 코루틴이 있으면 중지해주자
        StopAllCoroutines();
        hpSlider.gameObject.SetActive(false);
        // 코루틴은 싱글쓰레드같은거
        GameSceneButtonManager.gm.enemyDeleted();
        //죽기위한 상태처리를 하자
        Destroy(gameObject, 3f);
    }

    public void dealDamage(int damage)
    {
        if (enemyState == EnemyState.Die ||
            enemyState == EnemyState.Damaged) return;
        //천보일땐 데미지 무시하고 그냥 이동        
        if (gdm.enemyAttribute == 2 && enemyState == EnemyState.Idle)
        {
            ChangeState(EnemyState.Move);
            return;
        }

        int temp = (int)SkillManager.skm.currentElement;
        if (temp == 4){             // 전능이면 3배
            GameSceneButtonManager.gm.calculatedDamage = 3 * damage;
            Instantiate(damagePrefab, transform.position, Camera.main.transform.rotation);
            hp -= 3*damage;
            if (SkillManager.skm.currentUtil == SkillManager.SkillUtil.Bloody)
            { // 흡혈이면 피해량 반만큼 회복
                target.parent.gameObject.GetComponent<PlayerMove>().GetHp(3 * damage / 2);
            }
        }
        else if (temp == weakness)
        { // 약점과 맞으면 2배
            GameSceneButtonManager.gm.calculatedDamage = 2 * damage;
            Instantiate(damagePrefab, transform.position, Camera.main.transform.rotation);
            hp -= 2 * damage;
            if (SkillManager.skm.currentUtil == SkillManager.SkillUtil.Bloody)
            {
                target.parent.gameObject.GetComponent<PlayerMove>().GetHp(damage);
            }
        }
        else
        {
            GameSceneButtonManager.gm.calculatedDamage = damage;
            Instantiate(damagePrefab, transform.position, Camera.main.transform.rotation);
            hp -= damage;
            if (SkillManager.skm.currentUtil == SkillManager.SkillUtil.Bloody)
            {
                target.parent.gameObject.GetComponent<PlayerMove>().GetHp(damage/2);
            }
        }
        

        if (hp > 0)
        {
            ChangeState(EnemyState.Damaged);
            anim.SetTrigger("GetDmg");
        }
        else
        {
            ChangeState(EnemyState.Die);
            anim.SetTrigger("GetDead");
            Die();
        }
    }

}
