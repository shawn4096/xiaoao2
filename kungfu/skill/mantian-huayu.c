//mantian-huayu.c ���컨�꣬���¾������ڰ��ӡ������졢����
//cre by sohu@xojh
#include <ansi.h>
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>
string	*msg = ({
"$N������࣬һʽ������̤����������$w�������·�ͻȻ˦����ֱ����$n��$l",
"$w�ƿշɳ���һʽ�����羭�졹������һ�����ߣ��������ң�����$n��$l��",
"$N˫�����һʽ�����Ƽ��ա�������$w��$n����������$n��ȫ������",
"$N�����һ����ȴ��$nһ�С�������Ҷ����ʮ��ö$w�ɿ��л�������",
"$N���μ�����ǰ������һʽ��ѩ��׷�١�����ö$w��$n��в����ȥ",
"$Nһʽ�����ײ�ɣ��������һת������������ö$w������$n�ı���",
"$N���һ�ݣ�һ�С����Ƽ�����Ӹ����£�����$w���䣬ֱ��$n��$l",
"$Nһ�С����ǵ���������ָ������ö$w��һ��ڹ�����$n��ͷ��",
});

int valid_enable(string usage)
{
	return usage == "throwing" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
	  
	if (me->query_temp("mthy/xingluo"))
	{
		   	
	   return ([
		"action":YEL+replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$W"), "$W", "$w"YEL)+NOR,
		"damage": 100 + random(60),
		"damage_type":"����",
		"dodge": random(20)-10,
		"parry": random(10),
		"force": 100 + random(250),
		//"post_action": (: call_other, WEAPON_D, "throw_weapon" :)
	    ]);
	}
	
	
	return ([
		"action":msg[random(sizeof(msg))],
		"damage": 60 + random(60),
		"damage_type":"����",
		"dodge": random(20)-10,
		"parry": random(10),
		"force": 100 + random(250),
		//"post_action": (: call_other, WEAPON_D, "throw_weapon" :)
	]);
}

int practice_skill(object me)
{
	if ( me->query("jingli") < 30 || me->query("neili") < 10)
		return notify_fail("����������������컨�ꡣ\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

int valid_learn(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "throwing")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ( me->query("max_neili") < 1000)
		return notify_fail("�������������\n");

	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"mantian-huayu/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
     object weapon = me->query_temp("weapon");

    	if (!weapon) return;
		//���ӽ��ܺ�Ч��
     	if(((string)weapon->query("id")=="xiuhua zhen" ||(string)weapon->query("id")=="zhen" || (string)weapon->query("id")=="qijue zhen" || weapon->id("needle"))  
      	&& random(me->query_str()) > victim->query_str()/2){
			  victim->receive_wound("qi", me->query_str(1)*random(200),me);
		 message_vision(HIR "ֻ�����͡�һ����һ��Ѫ˿��"+victim->name()+"���̵���״������\n" NOR,me,victim);
		}
		//�����Ѫ����Ч��
		if (!victim->is_busy()&&weapon->query("id")=="heixue shenzhen"&&me->query("hmy/quest/heixue")&&random(10)>6)
		{
          message_vision(HIY"$N��$n��������Ȼ˦��������Ѫ���룬$nһ��С��Ϊ�������Ѩ������ʱ�������ơ�\n"NOR,me,victim);
		  victim->add_busy(2+random(3));
		  victim->apply_condition("heixue_poison",1+random(2));

		}
		//��ʬ���������ʬ����
        if (present("sanshi dan",me)&&me->query("hmy/quest/sanshi")&&random(10)>5)
        {
			message_vision(HIB"\n$N�ӿڴ�������һ����ʬ���񵤣���$n�ſڴ��֮�ʣ���Ȼ������һ����Ӱ����$n�Ŀ��У�\n"NOR,me,victim);
		    if (!victim->is_killing(me))
                me->kill_ob(victim);
			if( random(me->query("combat_exp")) > (int)victim->query("combat_exp")/2
                && me->query_str() > (int)victim->query_dex()/2){ 
               message_vision(HIG"\n$n���˹����������һʱ�������޴룬�����޼�������ʶ������������ҩ�衣\n"NOR, me, victim);
               me->add("max_neili", -random(1));
		       me->add("neili", -random(1000));
	        if (userp(victim))
		       me->add_condition("killer", 90);
           victim->set_temp("last_damage_from", "��ʬ��������");
		   victim->apply_condition("sanshi_poison", 5+random(3));
           victim->receive_wound("jing",random(1000),me);
		   message_vision(HIC"$nһ�����¶��������в����㷲�����������������С�������䶯�ĸо������в��ɴ󺧣�\n"NOR,me,victim);
		   victim->apply_condition("no_exert",1);
           return ;  
         }
         else if(random(me->query("combat_exp")) > (int)victim->query("combat_exp")/3
         || random(me->query("neili")) > victim->query("neili")/2){
          message_vision(HIB"\n$n���²��ã���æ����ֱ����ʬ���񵤴������ӹ���û�д��С�\n"NOR,me,victim);
          tell_object(victim,HIB"\n����Ȼ��ʱ�ܿ��˶�ʬ����һ���ȳ�����ǣ�����������ʬ�����ˡ�\n"NOR);
          me->add("neili", -400);
	      if (userp(victim))
		     me->add_condition("killer", 15);
          victim->apply_condition("sanshi_poison", 3+random(3));
          me->start_busy(1);
          victim->add_busy(1);
          return ;
         }

      }

	return;
				
}