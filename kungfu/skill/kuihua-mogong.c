// By KinGSo@���� 2006��4��25�� 
// kuihua-shengong ����ħ��


inherit FORCE;
#include <ansi.h>

string *dodge_msg = ({
        "$n΢΢һ������ȻԶȥ��ʹ$N�Ľ���ȫȻ���á�\n",
        "$n��ʱ��ƽ����������������ȣ�ʹ$NȫȻ�޷����ա�\n",
        "$n����һ�ˣ���ȥ�����κ�׷����\n",
        "$n�㲻��أ���֫�Ͱڣ���Ȼ��$N�Ľ���ȫ�������\n",
});

string *finger_name = ({ "������ָ", "��������ָ", "����ʳָ",
                         "������ָ", "��������ָ", "����ʳָ", }); 

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("kuihua-mogong", 1);
        return lvl * lvl * 18 * 15 / 100 / 200;
}

mapping *actionf = ({
([      "action":"$Nٿ�Ľ�ǰ�����ο켫����ָ����$n��$l",
        "force" : 310,
       
        "dodge" : 60,
        "parry" : 20,
        "damage": 190,
        "damage_type":  "����"
]),
([      "action":"$N����ǰ����������ͬ���ȣ���������׽������ָ���Ĵ���$n��$l",
        "force" : 310,
        
        "dodge" : 65,
        "parry" : 20,
        "damage": 200,
        "damage_type":  "����"
]),
([      "action":"$N����һת����ָ�̳���ֱָ$n��$l",
        "force" : 330,
        
        "dodge" : 70,
        "parry" : 20,
        "damage": 210,
        "damage_type":  "����"
]),
([      "action":"$NƮȻԶȥ�����ֽ�ǰ���ٶȿ�Ĳ���˼�飬һָ����������$n��$l",
        "force" : 345,
        
        "dodge" : 75,
        "parry" : 35,
        "damage": 190,
        "damage_type":  "����"
]),
([      "action":"$N����һ�Σ�ͻȻ����һ�ţ�����$n��$l",
        "force" : 350,
        
        "dodge" : 70,
        "parry" : 25,
        "damage": 200,
        "damage_type":  "����"
]),
([      "action":"$N���¼��ߣ����α��Ī�⣬ͻȻһָ����$n��$l",
        "force" : 450,
       
        "dodge" : 85,
        "parry" : 25,
        "damage": 220,
        "damage_type":  "����"
]),
});

mapping *actionw = ({
([      "action":"$Nٿ�Ľ�ǰ�����ο켫�����е�$w����$n��$l",
        "force" : 360,
       
        "dodge" : 70,
        "parry" : 20,
        "damage": 420,
        "damage_type":  "����"
]),
([      "action":"$N����ǰ����������ͬ���ȣ���������׽�������е�$w���Ĵ���$n��$l",
        "force" : 390,
        
        "dodge" : 60,
        "parry" : 25,
        "damage": 430,
        "damage_type":  "����"
]),
([      "action":"$N����һת��$w�̳���ֱָ$n��$l",
        "force" : 365,
        
        "dodge" : 80,
        "parry" : 15,
        "damage": 450,
        "damage_type":  "����"
]),
([      "action":"$NƮȻԶȥ�����ֽ�ǰ���ٶȿ�Ĳ���˼�飬$w����������$n��$l",
        "force" : 380,
        
        "dodge" : 75,
        "parry" : 15,
        "damage": 560,
        "damage_type":  "����"
]),
([      "action":"$N����һ�Σ�ͻȻ����һ������$n��������������ջأ�����$w����$n��$l",
        "force" : 400,
       
        "dodge" : 80,
        "parry" : 17,
        "damage": 580,
        "damage_type":  "����"
]),
([      "action":"$N���¼��ߣ����α��Ī�⣬ͻȻһ���֣�$w��Ҳ�ƵĲ���$n��$l",
        "force" : 420,
        
        "dodge" : 95,
        "parry" : 20,
        "damage": 650,
        "damage_type":  "����"
]),
});

mapping *action_qm = ({
([      "action":HBMAG"$N����$w"+HBCYN"ͻȻ���з�һ�䣬һ�С�����Ū�ѡ���$w�����������ʽ������ס�$n����֮�з������"NOR,
        "force" : 160,
        "dodge" : 5,
        "parry" : 5,
        "damage": 215,
        "lvl" : 0,
        "skill_name" : "����Ū��",
        "damage_type":  "����"
]),
([      "action":HBMAG HIY"$N����ˣ�$n��׷������ͻȻ��$N����$n��ǰ��һ�С��������𡹣�����$wֱָ$n��$l"NOR,
        "force" : 200,
        "dodge" : 5,
        "parry" : 5,
        "damage": 225,
        "lvl" : 10,
        "skill_name" : "��������",
        "damage_type":  "����"
]),
([      "action":HBMAG HIW"$N����$w"+HBCYN"�ζ�,����Ʈ����������ȣ�ת�˼�ת��һ�С��������������Ʋ���$n�����"NOR,
        "force" : 260,
        "dodge" : 8,
        "parry" : 8,
        "damage": 30,
        "lvl" : 220,
        "skill_name" : "��������",
        "damage_type":  "����"
]),
([      "action":BBLU HIC"$N"+HBCYN"һ����Ц��һ�С����Ǹ��¡�������Ｒ����ǰ��һ˲֮�䣬��$n����Ѳ���һ�ߣ�$w�漴�ݳ�"NOR,
        "force" : 330,
        "dodge" : 10,
        "parry" : 15,
        "damage": 240,
        "lvl" : 30,
        "skill_name" : "���Ǹ���",
        "damage_type":  "����"
]),
([      "action":HBMAG HIC"$N�ȵ������ã������㼴�γ�$w��һ�С����ഩ���������ִ̳�������ת����ȥ"NOR,
        "force" : 205,
        "dodge" : 35,
        "damage": 220,
        "lvl" : 80,
        "skill_name" : "���ִ̳�",
        "damage_type":  "����"
]),
([      "action":HBBLU "$N��س嵽$n��ǰ��һ�С���ظ��Ŀ��������$wֱ��$n���ۣ�$n��æ�мܣ�����$N��$wͻȻת��"NOR,
        "force" : 240,
        "dodge" : 50,
        "damage": 245,
        "lvl" : 90,
        "skill_name" : "ֱ������",
        "damage_type":  "����"
]),
([      "action":HBBLU HIG"$N����Ծ��$ņ��һ����������$Nһ�С����Ƿɶ项������ֱ����£�����$w����$n��$l"NOR,
        "force" : 270,
        "dodge" : 60,
        "damage": 270,
        "lvl" : 100,
        "skill_name" : "����Ծ��",
        "damage_type":  "����"
]),
([      "action":HBMAG HIM"$Nһ�С�Ⱥа���ס�����֦�Ͱڣ�$n��ǰ�·�ͻȻ�������߰˸�$N���߰�ֻ$wһ�����$n"NOR,
        "force" : 300,
        "dodge" : 75,
        "damage": 300,
        "lvl" : 110,
        "skill_name" : "Ⱥа����",
        "damage_type":  "����"
]),
});
string *usage_skills = ({ "finger", "sword", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        
        return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
        return combo == "kuihua-mogong";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{       int i, level;

	level=me->query_skill("kuihua-mogong",1);

        
        if( me->query_temp("kh_qm")) {
        for(i = sizeof(action_qm); i > 0; i--) 
                if(level >= action_qm[i-1]["lvl"])
                        return action_qm[NewRandom(i, 20, level/5)];
        }
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;
        
        if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("�㲻ɢȥ���վ�����ô��������ħ����\n");
    
        if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��󡹦����ô��������ħ����\n");

        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��Ȫ�񹦣���ô��������ħ����\n");

       if((int)me->query_skill("jiuyin-zhengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����湦����ô��������ħ����\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô��������ħ����\n");  
     
       if((int)me->query_skill("luohan-fumogong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�޺���ħ������ô��������ħ����\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ̫��������ô��������ħ����\n");  

        if ((int)me->query("combat_exp") < 3000000)
                return notify_fail("����ÿ���ħ�����֮����"
                                   "ƾ�Լ���ս������һʱ��������ᡣ\n");

       
            if (me->query("gender") != "����")
                return notify_fail(BLINK HIY"�������񹦻ӵ��Թ�����\n" NOR);
                
        
        

        if ((int)me->query_dex()< 35)
                return notify_fail("������Լ����������鶯��������������ôƮ�"
                                   "����Ŀ���ħ����\n");
 
       if ((int)me->query_int()< 32)
                return notify_fail("������Լ����������Բ�����������������ô����"
                                   "����Ŀ���ħ����\n");
       if ((int)me->query_str()< 25)
                return notify_fail("������Լ����������������������������ô����"
                                   "����Ŀ���ħ����\n");

      
 
       

        return 1;
}

int practice_skill(object me)
{
       if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("�㲻ɢȥ���վ�����ô��������ħ����\n");
    
        if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��󡹦����ô��������ħ����\n");

        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��Ȫ�񹦣���ô��������ħ����\n");

       if((int)me->query_skill("kuihua-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô��������ħ����\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô��������ħ����\n");  
     
       if((int)me->query_skill("luohan-fumogong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�޺���ħ������ô��������ħ����\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ̫��������ô��������ħ����\n");  



       if((int)me->query_skill("kuihua-mogong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("kuihua-mogong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -random(30));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ�����������ħ���ˡ�\n");       }
        else return notify_fail("�����ڵĿ���ħ����Ϊֻ����ѧ(learn)�������������ȡ�\n");

}
int difficult_level()
{
        return 1600;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("kuihua-mogong", 1);
        if (lvl <= 200) return 70;
        if (lvl < 250) return 90;
        if (lvl < 300) return 100;
        if (lvl < 350) return 115;
        return 130;
}

mixed ob_hit(object ob, object me, int damage)
{
	 //By kingso 2007 01 26���±༭��Ҳ��лCounterС��������ҵײ㲻֧��+= ([   
        int ap, dp;
        int  lvl;
        lvl = me->query_skill("kuihua-mogong", 1);
        if ( lvl < 150
          || me->query("neili") < 300
          || me->query_skill_mapped("force") != "kuihua-mogong")
         	return 0;
         	
        ap = ob->query_skill("parry");
        dp = me->query_skill("force");
        if (random(dp)> ap/2)
        {
	        me->add("neili", -50);
          me->receive_curing("qi", damage);
          me->receive_heal("qi", damage);

                return random(2) ?  HBMAG HIY "$N"HBMAG HIY"�۾�һ����$n"HBMAG HIY"��û����Ӱ��ͻȻ$n" 
                                    HBMAG HIY"���������һ��$N"HBMAG HIY"��ͷ������Ծ����\n" NOR:
                                                        
                                    HBMAG HIC"��Ȼ�䣬ֻ��$n"HBMAG HIC"��֦һ�ڣ���ʱ����������"
                                    HBMAG HIC"$n"HBMAG HIC"��Ӱ�ӣ�$N"HBMAG HIC"ȴ�޷�����$n"HBMAG HIC"�ķ�λ��\n" NOR;
                     }
}


mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("kuihua-mogong", 1);
   
    if (random(me->query_dex()) >= (target->query_dex()/4) && j > 120 &&
        me->query_skill("dodge",1) > 120 &&
        me->query("jingli")>300 && 
        !target->is_busy() &&
        me->query("combat_exp")/2 > random(target->query("combat_exp")) && 
        me->query("neili")>500)
   {
          switch(random(2))
          {
            case 0 :
               msg = HIC "$NĬ�˿���ħ��������Ʈ�����������м���.һ��ָ��$n�����Ѩ��\n";
               msg = msg + "$nֻ��ȫ��һ�飬�ѱ����е���"HIY"������Ѩ�����縮Ѩ������׵Ѩ����\n"NOR; 
               target->recevied_damage("qi", j +random(300));
               target->start_busy(2+random(2));
               break;
            case 1 :
               msg = HIW "$N���й��죬ָ������.��ʱ��������,��$n�������ڣ�\n";
               msg += "$nֻ������ҪѨһ�飬�ѱ����е���"HIY"�����Ѩ�����͹�Ѩ�����ٻ�Ѩ����\n"NOR;
               target->recevied_damage("qi", j + random(300));
               target->start_busy(3+random(2));
               me->add("neili",-50);
               message_vision(msg, me, target);
               return j/(4-random(2));
               break;
            
          }         
          message_vision(msg, me, target);
   }
}
string perform_action_file(string action)
{
        return __DIR__"kuihua-mogong/perform/" + action;
}

string exert_function_file(string action)
{
       return __DIR__"kuihua-mogong/exert/" + action;
}
