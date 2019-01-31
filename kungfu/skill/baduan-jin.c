// baduan-jin.c 八段锦
//updated by sohu@xojh

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { 
	 
	return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("baduan-jin", 1);
	int t = 1, j;
	
	if (!me->query("quest/baduanjin/pass"))		
		return notify_fail("八段锦只能通过解密后方可学习。\n");

	for( j = 1; j < lvl / 10; j++) t *= 2;
	if( t > 5000 ) t = 5000;
	//if( me->query("gender") == "无性" && lvl > 49 )
		//return notify_fail("你无根无性，阴阳不调，难以领会高深的八段锦。\n");

    if( (int)me->query_skill("force", 1) < 10 )
		return notify_fail("你的基本内功火候还不够。\n");

	if( (int)me->query_skill("baduan-jin", 1) > me->query_skill("force", 1) + 10
	&& me->query_skill("baduan-jin", 1) >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	return valid_public(me);
}

int practice_skill(object me)
{
    if (!me->query("quest/baduanjin/pass"))		
		return notify_fail("八段锦只能通过解密后方可练习。\n");

   if( (int)me->query_skill("baduan-jin", 1) >= 210 ) {

	if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("baduan-jin", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高八段锦了。\n");
	}
	else return notify_fail("你现在的八段锦修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"baduan-jin/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"头顶笼罩着浓郁的白气，神色极为肃穆" NOR,
		"start_my_msg" : "你深深吸一口气导入丹田，然后由丹田下行，经督脉而至任脉，形成一个小循环。\n",
		"start_other_msg" : me->name()+"盘膝坐了下来，双手虚握成拳，真气流转不绝。\n",
		"halt_msg" : "$N长出一口浊气，站了起来。\n",
		"end_my_msg" : "你将八段锦呼吸之法在体内运行十二周天，返回丹田，只觉得全身通泰的。\n",
		"end_other_msg" : me->name()+"长出一口气，散去全身八段锦真气，一抖衣襟，站了起来。\n"
	]);
}
