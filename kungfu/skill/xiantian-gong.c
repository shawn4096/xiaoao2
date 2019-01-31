// xiantian-gong.c ���칦
//updated by action@SJ 2008/9/15
//edit by sohu@xojh
#include <ansi.h>
#include <combat.h>
//#include "force.h"

inherit FORCE;
//#include <combat_msg.h>
//inherit SKILL;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
      int lvl, i;
        lvl = (int)me->query_skill("xiantian-gong", 1);
        i = (int)me->query("shen", 1);

	if ( me->query("gender") == "����" )
		return notify_fail("���칦�����������������������֮���������棡\n");
	
	if (me->query("family/family_name")!="ȫ���")
		return notify_fail("�㲢δ���ȫ���洫��������������������\n");
	
	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");
		
		    if ((lvl > 10 && lvl < 100 && i < lvl*lvl*lvl / 20 )
            || ( lvl >=100 && i < 10000))
                return notify_fail("�����������̫���ˣ��޷�ѧϰ���칦��\n");


	return 1;
}
int practice_skill(object me)
{
	
	if((int)me->query_skill("xiantian-gong", 1) >= 200 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("xiantian-gong", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ������������칦�ˡ�\n");
	}
	else return notify_fail("�����ڵ����칦��Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"xiantian-gong/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : me->name()+"��������ͨ�������ַ���ý���",
		"start_my_msg" : "����������ͨ����Ƭ��֮�䣬��������ȫ��˫�۾������䣬���ַ���ý����������٣���ƽʱ�������ˡ�\n",
		"end_my_msg" : "�㽫������ͨ��������ϣ���ȴ�������֣�˫�۾������䣬����վ��������\n",
		"end_other_msg" : ""+me->name()+"��������ͨ����ȥ��վ��������\n"
	]);
}



int ob_hit(object ob, object me, int damage)
{
	string msg;
	int ap, dp, j, neili, neili1;
	object weapon;
     
	if( damage < 100) return 0;

	neili = me->query("neili");
	neili1 = ob->query("neili");
//ֻ����ʹ������Ԫ����ʹ��
	if(!me->query_temp("xtg/wuqi")) {
		
		return 0;
	}

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}
//450��Ч������
	if (me->query_skill("parry",1) < 450
	 || me->query_skill_mapped("force") != "xiantian-gong"
	 || me->query("combat_exp") < ob->query("combat_exp")/3
	 || neili < 400 ) return 0;

	weapon = ob->query_temp("weapon");

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	
	if ( weapon ) ap *= 2;
	if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;
        
	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
	if ( me->is_busy() ) dp /= 2;   
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;  
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;
         
	if ( random(10) < 3 ) me->add_temp("fanzhen", 1);

	ap = ABS(ap);
	dp = ABS(dp);

	if ( me->query_temp("xtg/dywq"))
		dp += ap/2 + random(ap/2);
    if ( me->query_temp("xtg/wuqi"))
        dp += random(ap/2);
	if ( wizardp(me))
		tell_object(me, sprintf("ap: %d, dp: %d\n", ap, dp));
    

	if( random(dp) > ap && random(3)&&me->query("env/���칦")=="�������") {
		msg = HBCYN+HIW "$NĬ�����칦��������ת��Ϣ������������������$N�������γ�һ�����������\n" NOR;
		tell_object(ob, WHT "��ֻ�����ֵ���������������ޣ���һ��������ˮ��һ�����޴�������ͬʱ������һ�ɷ���֮��������\n" NOR);
		msg +=WHT "$nһ�д���$N�����ϣ�ֻ���ƺ�����ˮ��һ��������������\n"NOR;
		if(neili >= neili1*2 + random(damage)) {
			msg +=WHT "���$n�Ĺ�����$N����������������ˣ�\n"NOR,
			j = -damage;
		}
		else if( neili > neili1 + random(damage) ) {
			msg += WHT"���$n�Ĺ�����$N���������������һ�룡\n"NOR,
			j = -damage/3*2;
		}
		else {
			msg += WHT"���$N���������ֻ������$n��һС��������\n"NOR,
			j = -damage/2;
		}
		message_vision(msg, me, ob);
		return j;
	}
}