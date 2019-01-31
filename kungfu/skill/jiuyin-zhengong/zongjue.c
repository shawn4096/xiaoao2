#include <ansi.h>

int exert(object me)
{
	int i;

	if (me->query_skill_mapped("force")!="jiuyin-zhengong")
	    return notify_fail("你激发的内功不对，无法施展九阴总决。\n");
	if(me->query_temp("jiuyin/powerup"))
		return notify_fail("你正在运使九阴总诀。\n");
    if ((int)me->query_skill("force", 1) < 500)
		return notify_fail("你的基本内功修为还不够。\n");
	if ((int)me->query_skill("jiuyin-zhengong", 1) < 500)
		return notify_fail("你的九阴真功修为还不够。\n");

	if ((int)me->query_skill("daode-jing", 1) < 500)
		return notify_fail("你的道德经修为还不够。\n");

	if( (int)me->query("neili") < 5000 )
		return notify_fail("你的真气不够。\n");
//为什么是force而不是jiuyin-zhengong的判断么？
	//i = me->query_skill("force")/5;
	i = me->query_skill("jiuyin-zhengong")/2;
	//i = i*3;
	me->add("neili", -500);
	//me->start_exert(3, "九阴总诀");
	me->add_temp("apply/dodge", i);
    me->add_temp("apply/parry", i);
	me->add_temp("apply/defense", i*3/2);
	me->add_temp("apply/armor", i*3/2);
	me->add_temp("apply/attack", i);
	me->add_temp("apply/damage", i/3);
	//me->add_temp("apply/whip", i);
	me->add_temp("apply/strike", i);
	me->add_temp("apply/cuff", i);
	me->add_temp("apply/claw", i);
	me->set_temp("jiuyin/powerup", 1);
	message_vision(HBBLU+HIW"$N运起九阴总诀，真气流转不绝，周身隐隐形成一层真气，功夫威力陡然大增！\n"NOR, me);

	//if ( me->is_fighting())
		//me->start_busy(random(2));
	call_out("remove_effect", (int)me->query_skill("force")/4, me, i);
	return 1;
}

void remove_effect(object me, int i)
{
	if (!me) return;
	me->delete_temp("jiuyin/powerup");
	me->add_temp("apply/dodge", - i);
	me->add_temp("apply/attack", - i);
    me->add_temp("apply/parry", - i);
	me->add_temp("apply/defense", -i*3/2);
	me->add_temp("apply/armor", -i*3/2);
	me->add_temp("apply/damage", - i/3);
	//me->add_temp("apply/whip", - i);
	me->add_temp("apply/strike", - i);
	me->add_temp("apply/cuff", - i);
	me->add_temp("apply/claw", - i);
	message_vision(HIC"$N的九阴总诀运使完毕，轻轻吐出一口浊气。\n"NOR, me);
}

string exert_name(){ return HBBLU+HIW"九阴总诀"NOR; }

int help(object me)
{
        write(HBBLU+HIW"\n九阴真功之「九阴总诀」："NOR"\n\n");
        write(@HELP
	九阴真经乃是北宋延平人黄裳所著作，状元及第，原为文官，
	因校对《道藏》而悟通武学义理。及后黄裳被派遣消灭明教，
	官兵无能败阵，黄裳不服，单人匹马杀伤了明教多人，引来
	众人上门寻仇。黄裳不敌逃去，家人尽数被杀。为雪深仇，
	黄裳隐居40多年，苦思破解敌人武功之道。40年后武功大成
	但敌人均已纷纷谢世，黄裳感慨万千而将自己所有武功形成
	《九阴真经》上下两册，遗留世间。
	后九阴真经为五绝之首的王重阳所得，交予周伯通藏匿，以
	荼毒江湖，后来周伯通为东邪所骗，将下册盗走，周伯通下
	落不明。
	要求：  
		当前内力值为 5000 以上；
		道德经的等级 500 以上；
		基本内功等级 500 以上；
		九阴真功等级 500 以上。
    注意：
		set 九阴真功 护体 以阴柔内力化解对方有效伤害以及反震
		
HELP
        );
        return 1;
}
