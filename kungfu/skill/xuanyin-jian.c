// ��������
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : HIB"$Nһ�����е�$w"+HIB+"����ǰֱ��������һ�С�������·��ֱָ$n"+HIB+"��$l"NOR,
	"skill_name" : "������·",
	"lvl" : 0,
	"damage_type" : "����"
]),
([
	"action" : HIM"$Nʹ���������ֻء���$w"+HIM+"����ҡ�ڲ�����ҡҡ�λεô���$n"+HIM+"��$l"NOR,
	"skill_name" : "�����ֻ�",
	"lvl" : 30,
	"damage_type" : "����"
]),
([
	"action" : HIW"$Nһ�С�����Ϯ�塹��$n"+HIW+"һ����$l�Ѿ���$N����"NOR,
	"skill_name" : "����Ϯ��",
	"lvl" : 50,
	"damage_type" : "����"
]),
([
	"action" : HIC"$NԾ�����࣬����$w"+HIC+"���˸����ߣ�бб���£����������졹������$n"HIC"��$l"NOR,
	"skill_name" : "��������",
	"lvl" : 70,
	"damage_type" : "����"
]),
([
	"action" : HIG"$N�������֣�ͻȻ��$w"+HIG+"���ö��ϣ�һʽ������������Ѹ���ޱȵĹ���$n"+HIG+"��$l"NOR,
	"skill_name" : "������",
	"lvl" : 90,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;
	if (!(weapon = me->query_temp("weapon")))
		return notify_fail("����ʱ�޷�������������\n");
	if ((string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԣ��޷�������������\n");
	if ((int)me->query("max_neili") < 60)
		return notify_fail("�������������\n");
	if ( me->query_skill("xuanyin-jian", 1) < 150 )
		return notify_fail("������������ȼ���������ϰ��\n");
	if ((int)me->query_skill("jiuyin-zhengong", 1) < 50)
		return notify_fail("��ľ����湦���̫ǳ��\n");
	if (me->query_skill_mapped("force") != "jiuyin-zhengong")
		return notify_fail("��ϰ�������������о���������ϡ�\n");
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
	int i, j, level;

	level   = (int) me->query_skill("xuanyin-jian",1);
	for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			
			
			
			return ([
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"damage":	200 + random(180),
				"force":	300 + random(350),
				"dodge":	random(30),
				"parry":	random(30),
			]);
		}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 60 || me->query("neili") < 30)
		return notify_fail("�����������������������\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xuanyin-jian/" + action;
}

int ob_hit(object ob, object me, int damage)
{
	object wp,wp1;
	string msg;
	int p,j,skill, neili, neili1, exp, exp1;
	wp = me->query_temp("weapon");
	wp1 = ob->query_temp("weapon");
	skill = me->query_skill("xuanyin-jian", 1);
	neili = me->query("neili");
	neili1 = ob->query("neili");
	exp = me->query("combat_exp");
	exp1 = ob->query("combat_exp");

	if( me->query("jiali") 
	&& skill+50 > random(ob->query_skill("parry", 1)/3)
	&& wp 
	&& skill > 100
	&& me->query_skill_mapped("parry") == "xuanyin-jian"
	&& living(ob)
	&& !me->is_busy()){
		if(wp1){
			msg = HIW"$N����һ�⣬��������湦һ��\n"NOR;
			msg = replace_string(msg, "$w", wp1->name());
			if(neili >= random(neili1+damage)){
				if(random(me->query_str(1)) > ob->query_str(1)/3 && skill > 120){
					msg += HIW"$n����"+wp1->name()+HIW"��$Nһ����Щ���֣�\n"NOR;
					ob->add_busy(2+random(2));
					j = -(damage);
				}
				else{
					ob->receive_damage("qi", damage/10, me);
					ob->receive_wound("qi", damage/10, me);
					p = ob->query("qi")*100/ob->query("max_qi");
					msg += COMBAT_D->damage_msg(damage/20, "�˺�");
					msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
					j = -(damage/2+skill/2);
				}
			}
			else if(neili >= random(neili1)+damage){
				msg += "�����$n�Ĺ�������һ�衣\n";              
				j = -(damage/2+skill/2);
			}
			else{
				j = damage/2+random(damage/2);
				if(j<damage/2) msg += "�������������$n��������������ȥ��\n";
				else msg += "����Ծ���������$n��������������ȥ��\n";
				j = -j;
			}
			message_vision(msg, me, ob);
			return j;
		}
		else{
			msg = HIY"$N����һת����$n�й�ֱ����\n"NOR;
			if(neili >= neili1+random(neili1)+damage){
				ob->receive_damage("qi", damage/10, me);
				ob->receive_wound("qi", damage/10, me);
				p = ob->query("qi")*100/ob->query("max_qi");
				msg += COMBAT_D->damage_msg(damage, "����");
				msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
				j = -(damage*2+skill);
			}
			else if(neili >= random(neili1)+damage){
				msg += "�����$n�Ĺ�������һ�衣\n";              
				j = -(damage+skill);
			}
			else{
				j = damage/2+random(damage/2); 
				if(j<damage/2) msg += "�������������$nһЩ����ת�ƿ�ȥ��\n";
				else msg += "�������������$nһЩ����ת�ƿ�ȥ��\n";
				j = -j;
			}
			message_vision(msg, me, ob);
			return j;
		}
	}
}


mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	object weap,weap1;
	int ap, dp,skill,skill1;
	weap = victim->query_temp("weapon");
	weap1 = me->query_temp("weapon");
	skill=me->query_skill("jiuyin-zhengong",1);
    skill1=me->query_skill("xuanyin-jian",1);
//�����
	if( me->query_temp("jiuyin/powerup")
	 && me->query_skill("xuanyin-jian", 1) > 450
	 && me->query("neili") > 2000
	 && victim->query_temp("weapon")
	 && random(me->query_skill("xuanyin-jian",1)) > victim->query_skill("dodge", 1)/2 
	 && random(10) > 3) {
		message_vision(HBBLU+WHT"ֻ��$N"+ weap1->name() + HBBLU+WHT"�ھ������������£��γ�����������������" + weap->name() +HBBLU+WHT"�پ��аѳֲ�ס�����ƣ�\n" NOR, me );
		
		ap = me->query("combat_exp", 1) /1000 * me->query_int(1);
		dp = victim->query("combat_exp", 1) /1000 * victim->query_int(1);
		if (random(ap + dp ) > dp ) {
			message_vision(HIC"$n��������ôһ������ʱ����������ת�˼����߰˸�Ȧ�ӣ�"+ weap->name()+ HIY"���ֶ�ȥ��\n" NOR, victim );
			weap->move(environment(me));
			victim->add_busy(2);
			//victim->reset_action();
		}
		else {
			message_vision(HIY"$n�����ɾ���"+ weap->name()+ HIY"˳�ŷ��������ת���£��⿪��"+weap1->name()+HIY"�Ĳ��ơ�\n" NOR, victim );
			victim->add("neili", -50);
		}
		me->add("neili", -(20+random(30)));
	}
	//���ֶϽ�
    //�ƻ�Ч��
	if (me->is_fighting()&&objectp(victim)&&me->query_temp("jiuyin/powerup")&&!random(3))
	{
	
	  switch (random(4)) {
	    case 0:
			message_vision(HIR"$N����һ������������������"+weap1->query("name")+HIR"�ϣ�����������\n"NOR,me,victim);
          if (random(me->query_str(1))>victim->query_str(1)/4)
          {
		    message_vision(HIR"$N�����泩�������ݺᣬ����������\n"NOR,me,victim);
			me->add_temp("apply/damage",skill/6);
			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
			//COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
			me->add_temp("apply/damage",-skill/6);
          }else {
			message_vision(HIY"$n�书����ޱȣ������������󻺽�ѹ����\n"NOR,me,victim);
            
		   }
	    break;
	    case 1:
		 message_vision(HIG"$N��������ת���⣬�������磬������������$næµ֮�ʣ�����һ������$n��\n"NOR,me,victim);
	     if (random(me->query_dex(1))>victim->query_dex(1)/4)
          {
		    message_vision(HIR"$n�����ϵ��⽣����Ȼ��˹��죬��æ�������������һ�������ؿڡ�\n"NOR,me,victim);
			victim->receive_damage("qi",skill1*4,me);
          }else {
			message_vision(CYN"$n�Ṧ�˵ã���æ�����Ź���㿪����ȴ����һ���亹��\n"NOR,me,victim);
            me->add_busy(2);
			victim->add_busy(1);
		   }

	    break;
	    case 2:
         message_vision(HIM"$N��Ȼ��ʩչ������ʮ��������ʽ�������籩�ꡣ\n"NOR,me,victim);
	     if (random(me->query_int(1))>victim->query_int(1)/3)
          {
		    message_vision(RED"$n�پ������������پ��������ƣ���㱼�Ϊ$Nһ����������\n"NOR,me,victim);
            victim->set_temp("must_be_hit", 1);
		    COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
		    victim->delete_temp("must_be_hit");
            victim->apply_condition("broken_arm",1); 
			victim->apply_condition("no_perform",2);
          }else {
			message_vision(MAG"$n����ʶ�㣬������$N����ͼ������㿪��\n"NOR,me,victim);
            me->add_busy(1);
			victim->add_busy(1);
		   }
	    break;
        case 3:
         message_vision(HIM"$N����������ӿ���ȣ������鶯����ת����,ȫ��$n�������ϵ��ķ�λ��\n"NOR,me,victim);
	     if (random(me->query("combat_exp"))>victim->query("combat_exp")/3)
          {
		    message_vision(BLU"$N��"+weap1->query("name")+BLU"��Ȼ�������������$nֻ���ķ����ң����������ڼӿ졣\n"NOR,me,victim);
            victim->receive_damage("jingli",random(skill1),me);
			victim->receive_damage("jing",random(skill1)/2,me);
          }else {
			message_vision(HIC"$n����������������$N��������Ӱ�졣\n"NOR,me,victim);         
		   }
	    break;
	   }
     }
	return 1;
}