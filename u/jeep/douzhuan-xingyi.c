// douzhuan-xingyi ��ת����
// 1997-2-14

inherit SKILL;

#include <weapon.h>
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

string *parry_msg = ({
YEL"�����һ��������������$Nһ��һ����$N��������Խ����������һ�ԡ�\n",
HIB"$N����һ����������$l��$n����$N��$l������Ī��������ﻬ��һ�ԡ�\n",
HIW"$N˫��ǰ̽����۴���$n�ұۣ��ұ�ʹ��$n��������$n���л�ȥ��\n",
HIY"$N���ƶ�ת��$n����Ī�����������;ת�˷���ֱ���Լ�Ϯ����\n",
YEL"$N�����Ϲۣ�˫����Է��ཻ���ƣ�̸Ц�侹ʹ��$n�������գ�ʹ��$n��֪����Ǻá�\n",
HIB"$N����������$n�͹����ʹ������������$n�ĳ�����������$n�������������С�\n",
HIW"ֻ��$N����Ʈ�磬ǡ���������ƣ������һʽ��˫�ƶ����޶�����׽��������$n��$l��\n",
HIY"$N����Ʈ�������������ƶ�ת֮�䷴��$n����������$n��ȴ����$n��˼������⡣\n",
});

string *colors = ({YEL,HIB,HIW,HIY,YEL,HIB,HIW,HIY});

int valid_enable(string usage)
{
	return usage == "parry";
}

int valid_learn(object me)
{
	return notify_fail("��ת����ֻ��ͨ����������ߡ�\n");
}

int practice_skill(object me)
{
	return notify_fail("��ת����ֻ��ͨ����������ߣ��޷�ͨ����ϰ����ߡ�\n");
}

int ob_hit(object ob, object me, int damage)
{
	object weapon, vweapon;
	string msg, *limbs, limb, attack_skill, skill_type, vskill_type;
	int ap, dp, skill, size, i, p;

	if( ob->query("env/invisibility") ) return 0;

	if( me->query_temp("fanzhen")){
		me->delete_temp("fanzhen");
		return 0;
	}

	weapon = me->query_temp("weapon");

	if (me->query_skill("douzhuan-xingyi", 1) < 150
	|| me->query_skill_mapped("parry") != "douzhuan-xingyi"
	|| me->query_skill("shenyuan-gong", 1) < 150
	|| me->query("combat_exp") < ob->query("combat_exp")/2 ) 
		return 0;

	skill = me->query_skill("douzhuan-xingyi", 1);
	vweapon = ob->query_temp("weapon");

	if ( weapon) skill_type = weapon->query("skill_type");
	if ( vweapon) vskill_type = vweapon->query("skill_type");

	if (!me->query("quest/bishen/pass"))
		if ( vskill_type != skill_type ) return 0;
	
	if(objectp(vweapon))
		msg = vweapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}
    
	if ( me->query("neili") < ob->query("neili")/5 ) return 0;

	if ( vweapon ){
		attack_skill = ob->query_skill_mapped(vskill_type);
	}
	else
		attack_skill = ob->query_skill_prepared(msg);

	if (!attack_skill ) return 0;

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	if ( vweapon ) ap *= 2;
	if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;
	if ( me->is_busy()) ap /= 2;

	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;

	ap = ABS(ap);
	dp = ABS(dp);
	
    if (me->query("shenyuan/powerup") && random(10) > 5)
    {
		switch(random(3)){
		      case 0:
                  message_vision(HBMAG"$N����ת���Ƶ���ʽ���뵽��ʽ�У����Է��Ĺ���������ȥ��\n"NOR,me,ob);
			      me->set_temp("fanzhen", 1);
		          ob->receive_damage("qi", damage + me->query("jiali")*2, me);				  
		          ob->receive_wound("qi", damage/4, me);
				  message_vision(HIR"$nһ��������Ľ�ݾ������Ա�֮����ʩ�������ľ�֮�࣬������æ����������\n"NOR,me,ob);
				  ob->add_busy(1+random(3));
				  ob->set_temp("must_be_hit",1);
                  COMBAT_D->do_attack(ob, ob, ob->query_temp("weapon"), userp(me)?3:1);
		          ob->delete_temp("must_be_hit");
				  return -damage;
                  break;
			  case 1:
                  message_vision(HBBLU"$N���в��У�Ĭ������͵ѧ������ʽ�Ѿ���Ȼ���أ��������룬����ʶ�оͿ�ʼʩչ������\n"NOR,me,ob);
		          ob->receive_damage("jing", me->query_skill("douzhuan-xingyi",1), me);
		          ob->receive_wound("jing", me->query_skill("douzhuan-xingyi",1)/4, me);
				  return -damage/2;
                  break;
			  case 2:
		          message_vision(HIG"$N����ҹ���Ƕ�ʱ������书��ʩչ��������������ˮ���ܿ���һЩ�˺���\n"NOR,me,ob);
		          return -damage/3;
                  break;
	       	}
    }

	if ( random(dp + ap) > ap && random(2)) {
		limbs = ob->query("limbs");
		limb = limbs[random(sizeof(limbs))];
		size = sizeof(parry_msg);
		i = random(size);
		msg = parry_msg[i];
		msg += SKILL_D(attack_skill)->query_action(ob, vweapon)["action"];
		msg = replace_string( msg, "$l", limb) + "��\n"NOR;
		
		if (userp(ob) && !userp(me) && damage > 1800)
			damage = 1800 + random (50);

		ob->receive_damage("qi", damage + me->query("jiali")*2, me);
		ob->receive_wound("qi", damage/2, me);
		
		if (!weapon)
			msg += COMBAT_D->damage_msg(damage, "����");
		else 
			msg += COMBAT_D->damage_msg(damage, "����");
		msg = replace_string(msg, "$l", limb);
		
		if (weapon)
		{
			msg = replace_string( msg, "$w", weapon->name());
		}

		p = (int)ob->query("qi")*100/(int)ob->query("max_qi");
		msg += "( $n"+eff_status_msg(p)+" )\n";
		message_vision(msg, me, ob);

		me->set_temp("fanzhen", 1);
		return -damage;
	}
	return 0; 
}

string perform_action_file(string action)
{
	return __DIR__"douzhuan-xingyi/" + action;
}
