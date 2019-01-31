// xiantian-gong.c 先天功
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

	if ( me->query("gender") == "无性" )
		return notify_fail("先天功练的是天罡正气，公公阴人之身修练无益！\n");
	
	if (me->query("family/family_name")!="全真教")
		return notify_fail("你并未获得全真真传，难以再练先天真气。\n");
	
	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("你的基本内功火候还不够。\n");
		
		    if ((lvl > 10 && lvl < 100 && i < lvl*lvl*lvl / 20 )
            || ( lvl >=100 && i < 10000))
                return notify_fail("你的侠义正气太低了，无法学习先天功。\n");


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
		else return notify_fail("你现在的修为不足以提高先天功了。\n");
	}
	else return notify_fail("你现在的先天功修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"xiantian-gong/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : me->name()+"运起纯阳神通功，身手分外矫健。",
		"start_my_msg" : "你运起纯阳神通功，片刻之间，白气笼罩全身，双眼精光四射，身手分外矫健，进退神速，与平时判若两人。\n",
		"end_my_msg" : "你将纯阳神通功运行完毕，除却白气笼罩，双眼精光四射，缓缓站了起来。\n",
		"end_other_msg" : ""+me->name()+"将纯阳神通功退去，站了起来。\n"
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
//只有运使五气朝元方可使用
	if(!me->query_temp("xtg/wuqi")) {
		
		return 0;
	}

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}
//450后效果彰显
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
    

	if( random(dp) > ap && random(3)&&me->query("env/先天功")=="先天罡气") {
		msg = HBCYN+HIW "$N默运先天功，真气流转不息，气机不绝，隐隐在$N的身上形成一种先天罡气。\n" NOR;
		tell_object(ob, WHT "你只觉对手的先天罡气柔软如棉，这一招宛如打进水中一样，无从着力，同时隐隐有一股反震之力传来！\n" NOR);
		msg +=WHT "$n一招打在$N的身上，只觉似乎打在水中一样，不可着力。\n"NOR;
		if(neili >= neili1*2 + random(damage)) {
			msg +=WHT "结果$n的攻击被$N的先天罡气给化掉了！\n"NOR,
			j = -damage;
		}
		else if( neili > neili1 + random(damage) ) {
			msg += WHT"结果$n的攻击被$N的先天罡气化掉了一半！\n"NOR,
			j = -damage/3*2;
		}
		else {
			msg += WHT"结果$N的先天罡气只化掉了$n的一小半力道！\n"NOR,
			j = -damage/2;
		}
		message_vision(msg, me, ob);
		return j;
	}
}