// quanzhen-jianfa ȫ�潣��
// Modify By River 99.5.26
inherit SKILL;
#include <ansi.h>
mapping *action = ({
([
	"action" : "$N��Ӱ�ζ���̤���ţ���ƫ�棬һʽ���ֻ���������$w��ֱ����$n��$l",
	"lvl" : 0,
	"skill_name" : "�ֻ�����",
	"damage_type" : "����"
]),
([
	"action" : "$N��ǰԾ��һ�������ֽ���������$wʹ��һʽ������Į����ֱ��$n��$l",
	"lvl" : 10,
	"skill_name" : "����Į��",
	"damage_type" : "����"
]),
([
	"action" : "$N�β�ͦ����һʽ����ɽ������������$w�����ޱȣ���������$n��$l",
	"lvl" : 25,
	"skill_name" : "��ɽ����",
	"damage_type" : "����"
]),
([
	"action" : "$N����΢�࣬$w������һ���һ���󻡣�һʽ��˳ˮ���ۡ���ƽƽ����$n��$l��ȥ",
	"lvl" : 30,
	"skill_name" : "˳ˮ����",
	"damage_type" : "����"
]),
([
	"action" : "$N����š���������鱧��Բ��һʽ�������仨��������$w�й�ֱ��������$n��$l",
	"lvl" : 50,
	"skill_name" : "�����仨",
	"damage_type" : "����"
]),
([
	"action" : "$Nһʽ������ٵء���$w������������������ֱ����Ю����֮����Ȼն��$n��$l",
	"lvl" : 70,
	"skill_name" : "����ٵ�",
	"damage_type" : "����"
]),
([
	"action" : "$N����ʩ�����׵罻�ӡ���$w�Ƴ�һ��������â��������ƿ�����$n��$l",
	"lvl" : 90,
	"skill_name" : "�׵罻��",
	"damage_type" : "����"
]),
([
	"action" : "$N˫�Ȱ�����ף�һʽ�����񹲷ߡ���$w��������ԲȦ����������������",
	"lvl" : 110,
	"skill_name" : "���񹲷�",
	"damage_type" : "����"
]),
});
//���ࡢ��诡����ᡢ��Ȩ����⡢������ҡ��
mapping *actionqs = ({
([
	"action" : HIG"$N������������������ռ�����ࡹλ�ã����ֽ�Ӱ�ζ�������������һ����������Σ������Ƶ���������\n�Լ������ĽǶȾ�ֱ����$n��$l��"NOR,
	"lvl" : 0,
	"skill_name" : "����",
	"damage_type" : "����"
]),
([
	"action" : HIR"$N��ǰԾ��һ����ת����诡������ֽ���������������ص�ת�����ף�����Ķ�����项\nʹ��һʽ������Į����ֱ��$n��$l"NOR,
	"lvl" : 10,
	"skill_name" : "���",
	"damage_type" : "����"
]),
([
	"action" : HIY"$N�β�ͦ�������롸���᡹λ��һʽ����ɽ������������������̫�����������ޣ����¿����ʸ��ᡣ��\n�������������ޱȣ���������$n��$l"NOR,
	"lvl" : 25,
	"skill_name" : "����",
	"damage_type" : "����"
]),
([
	"action" : HIB"$N����΢�࣬����ǰ����ת����ռ����Ȩ��λ�ã�$w������һ���һ���󻡣�һʽ��˳ˮ���ۡ�\n�������������շ��ξ��ߣ��������������ƽƽ����$n��$l��ȥ!"NOR,
	"lvl" : 30,
	"skill_name" : "��Ȩ",
	"damage_type" : "����"
]),
([
	"action" : HIM "$N������𣬻��䡸��⡹λ�á������������˶��������ã�����ȫ�ڶ����󡣡�\n�����鱧��Բ��һʽ�������仨��������$w�й�ֱ��������$n��$l��"NOR,
	"lvl" : 50,
	"skill_name" : "���",
	"damage_type" : "����"
]),
([
	"action" : HIC"$N�������������������䵽��������λ�á���������������ʵ�����ǣ�������������������\nһʽ������ٵء�������������������ֱ����Ю����֮����Ȼն��$n��$l��"NOR,
	"lvl" : 70,
	"skill_name" : "����",
	"damage_type" : "����"
]),
([
	"action" : HIW"$N������������ԭ��ת��ͻȻ̤�롸ҡ�⡹λ�á���������������ת����ҡ�⶷ת�ǹ��ơ���\n����ʩ�����׵罻�ӡ������������Ƴ�һ��������â��������ƿ�����$n��$l��"NOR,
	"lvl" : 90,
	"skill_name" : "ҡ��",
	"damage_type" : "����"
]),

});


int valid_enable(string usage)
{
	return (usage == "sword") || (usage == "parry"); 
}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if (me->query("family/family_name")=="ȫ���")
	{
		if (me->query("family/generation")>3)
		{
			return notify_fail("ȫ��̵�����Ҫ��ʵ���������������Ӳ���ѧ\n");
		}
		if (me->query_skill("xiantian-gong",1)<350)
		{
			return notify_fail("ȫ�潣����ȫ��̸����似��������칦̫������350���޷���ϰȫ�潣��!\n");
		}
	}
	if(!me->query_skill("xiantian-gong"))
	  if ((int)me->query_skill("yunu-xinjing", 1) < 20)
		return notify_fail("�����Ů�ľ����̫ǳ��\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{ 
	int i, j, level,xtg;
	level = me->query_skill("quanzhen-jianfa",1);
	xtg = me->query_skill("xiantian-gong", 1);
     //����
	if (me->query_temp("htz/lianhuan")) {
	  for(i = sizeof(actionqs); i > 0; i--){
		if(level > actionqs[i-1]["lvl"]){
			j = NewRandom(i, 20, level/5);
				return ([  
					"action":actionqs[j]["action"],
					"lvl" : actionqs[j]["lvl"],
					"force" : 100 + random(100),
					"dodge": random(20)+xtg/15,
					"damage": 100 + random(50) + xtg/10,
					"parry": random(15)+xtg/15,//ԭ����15
					//"weapon" : random(2)?"����":"����",
					"damage_type" : actionqs[j]["damage_type"],
				]);           
            }
	    }
	 }
	  
	
			//���
		
	  else if ( me->query_temp("hebi") && random(2) || me->query_temp("hubo")) { 
		    for(i = sizeof(action); i > 0; i--){
		      if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/5);
							
				return ([  
                    "action" :random(2)? HIB + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIB)+NOR
							   : MAG + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"MAG)+NOR,
					"force" : 200 + random(350),
					"dodge": random(30),
					"damage": 80 + random(140),
					"parry": random(30),
					"weapon" : random(2)?"����":"����",
					"damage_type" : random(2)?"����":"����",
				]);
				}
			 }
		}
		else if ( me->query_temp("sanqing1")) 
		{ 
		    for(i = sizeof(action); i > 0; i--){
		      if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/5);
							
				return ([  
                    "action" :random(2)? HIB + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIB)+NOR
							   : MAG + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"MAG)+NOR,
					"force" : 200 + random(350),
					"dodge": random(30),
					"damage": 100 + random(140),
					"parry": random(30),
					"weapon" : random(2)?"����":"����",
					"damage_type" : random(2)?"����":"����",
				]);
				}
			 }
		}
			//����
		else if( me->query_temp("sanqing")){
			for(i = sizeof(action); i > 0; i--){
		      if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/5);
				
				return ([  
					"action":HIC+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC), NOR, HIC)+NOR,
					"lvl" : action[j]["lvl"],
					"force" : 120 + random(250) + xtg/10,
					"dodge": random(20)- 5 +xtg/15,
					"damage": 60 + random(80) + random((level+xtg)/4),
					"parry": random(15)+xtg/10,//ԭ����15
					//"weapon" : random(2)?"����":"����",
					//"damage_type" : random(2)?"����":"����",
					"damage_type" : action[j]["damage_type"],
				]);
				}
			}
		}

			//��
		else if( me->query_temp("qzjf/lian")){
			for(i = sizeof(action); i > 0; i--){
		      if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/5);	
				return ([  
					"action":HIR+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIR), NOR, HIR)+NOR,
					"lvl" : action[j]["lvl"],
					"force" : 120 + random(250) + xtg/10,
					"dodge": random(20)- 5 +xtg/15,
                    "damage": 100 + random(50) + xtg/10,

					"parry": random(15)+xtg/10,//ԭ����15
					//"weapon" : random(2)?"����":"����",
					"damage_type" : action[j]["damage_type"],
				]);
				}
			  }
			}						
		else {
		for(i = sizeof(action); i > 0; i--){
		  if(level > action[i-1]["lvl"]){
			j = NewRandom(i, 20, level/5);	
			return ([
				"action": action[j]["action"],
				"force" : 100 +random(250),
				"dodge": random(20)-10,
				"parry": random(10),
				"damage": 80 +random(80),
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
			]);
		  }
		}
	}	  
	
	
}

int practice_skill(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("neili") < 10)
		return notify_fail("�������������ȫ�潣����\n");
	if ((int)me->query("jingli") < 30)
		return notify_fail("�������������ȫ�潣����\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"quanzhen-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
//      ����ȫ�潣�����������������ʺܵ�
        object weapon; 
        int i,damage;
        weapon = me->query_temp("weapon");
        i = me->query_skill("quanzhen-jianfa", 1);
		damage=i+me->query_skill("xiantian-gong", 1)+me->query_skill("tiangang-beidouzhen", 1);
		damage=damage*me->query_str()/20+random(damage);

        if( !userp(me) && random(2) ) return 0;

        if( !weapon || weapon->query("skill_type") != "sword" ) return 0;
        //ȫ��ͬ�鲻���ý���
		//�޽���������auto
		if( i < 450
			||me->query_skill("xiantian-gong",1)<450
			||!me->query("qzjf/tonggui")
			|| !living(victim)
			|| me->query_skill_mapped("parry") != "quanzhen-jianfa"
            || me->query_skill_mapped("force") != "xiantian-gong"
            || me->query_skill_mapped("sword") != "quanzhen-jianfa"
			|| !me->query("quest/qz/qzjf/jianjue/pass")
		) return 0;        
         
       
       if( random(me->query_str()) > victim->query_con()/2
		  && !random(3)
          && random(me->query_skill("sword",1)) > victim->query_skill("parry",1)/2 )
           {
               
                switch(random(4)){
                    case 0:
                        message_vision(HBMAG"$N�������������������ġ�������ָ�����½Դ���������ָ�����½��ġ������͵��˽���ת��������һ�ƽ����澢����\n"NOR, me);
                        me->add_temp("apply/sword",  me->query_skill("quanzhen-jianfa", 1)/4);
						message_vision(HIG"$nһ��С��Ϊ���ǽ��������Ľ������ˣ��Ŀڴ�һ�����飬�ֽŶ�ʱΪ֮һ����\n"NOR,me,victim);
						victim->add_busy(2+random(2));
                        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), userp(me)?3:1);
                        me->add_temp("apply/sword", -me->query_skill("quanzhen-jianfa", 1)/4);
                        break;
					case 1:
                        message_vision(HBRED"$NĬ��ȫ�潣������������ָ�����½��������ָ�����½Զ�����������"+weapon->name()+HBRED"�͵Ļ�ת�ٴδ̳���\n"NOR, me);
                        me->set_temp("jianjue", 1);
                        me->add_temp("apply/attack",  me->query_skill("quanzhen-jianfa", 1)/4);
						message_vision(HIG"$nΪ���ǽ��������Ľ������ˣ���Ѫֱð��\n"NOR,me,victim);

						victim->receive_damage("qi",damage,me);
						victim->receive_wound("qi",damage/3,me);
                        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2)?1:3);
                        me->add_temp("apply/attack", -me->query_skill("quanzhen-jianfa", 1)/4);
                        me->delete_temp("jianjue");
					    break;
					case 2:
                        message_vision(HBGRN"$NĬ�����ǽ�����������������ʱ����ת���ٱ������߽�����ǰ����������"+weapon->name()+HBGRN"�󿪴�ϣ���ʽѸ�ͣ�ȫȻ��Ҫ���Ĵ򷨣�\n"NOR, me);
                        me->set_temp("jianjue", 1);
                        me->add_temp("apply/damage",  me->query_skill("quanzhen-jianfa", 1)/4);
						//victim->receive_damage("qi",2*i+random(i));
						//victim->receive_wound("qi",i);
                        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
                        me->add_temp("apply/damage", -me->query_skill("quanzhen-jianfa", 1)/4);
                        me->delete_temp("jianjue");
					    break;

					case 3:
                        message_vision(MAG"$N�������˽�ָ�����ֽ�����Ȼ�������������ȴӱ��������ɱ�������չ������ʱ�����ݺᣬ��$n����ѹ�ƣ�\n"NOR, me, victim);
                        victim->add_temp("lost_attack", 1);
						victim->set_temp("no_fight",1);
						
						victim->add_busy(2+random(1));
						if (!victim->query_temp("qzjf/jianjue"))
						{
							victim->add_temp("apply/attack",i/4);
							victim->add_temp("apply/dodge",i/4);
							victim->add_temp("apply/parry",i/4);
							victim->set_temp("qzjf/jianjue",i);
						}
						call_out("check_fight",5,victim);
				       break;
				}
		   }
        return 1;
}
//������lost_attack ���
void check_fight(object victim)
{
	int i;
	if(!victim) return;
	victim->delete_temp("no_fight");
	victim->delete_temp("lost_attack");
	i=victim->query_temp("qzjf/jianjue");
	if (!victim->query_temp("qzjf/jianjue"))
	{
		victim->add_temp("apply/attack",i/4);
		victim->add_temp("apply/dodge",i/4);
		victim->add_temp("apply/parry",i/4);
		victim->delete_temp("qzjf/jianjue");
		message_vision(HIW"$N����һ��ȫ�潣����ѹ����ʧ��\n"NOR,victim);
	}
	return;
    
}
