// powerup.c 蛤蟆功

#include <ansi.h>

inherit F_CLEAN_UP;


int exert(object me)
{
	int skill;

	//if (target != me)
	//	return notify_fail("你只能自己使用蛤蟆功来提升自己的战斗力。\n");
	if (me->query_skill_mapped("force")!="hamagong")
		return notify_fail("你只能用蛤蟆功来提升自己的战斗力。\n");
	if (me->query_skill("hamagong")<100)
		return notify_fail("你的蛤蟆功威力不足100级，无法发出蛤蟆功。\n");
	if (me->query_skill("force")<100)
		return notify_fail("你的基本内功不足100级，无法发出蛤蟆功。\n");
	if ((int)me->query("neili") < 1000 )
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_temp("hmg/powerup"))
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("hamagong",1);
	me->add("neili", -200);
	message_vision(HBGRN+HIW "$N" HBGRN+HIW "蹲在地上，双手伏地，双手弯与肩齐，状如蛤蟆，“呱”“呱”“呱”的大叫三声！\n"+
		"随着$N的连续鸣叫，三股极大的力道一圈圈的向四周不断散开！\n" NOR,me);

	me->add_temp("apply/attack", skill / 10);
	//me->add_temp("apply/strike", skill / 10); //统一在逆转里加，不能两次叠加 by renlai
	//me->add_temp("apply/cuff", skill / 10);
	me->add_temp("apply/staff", skill / 10);
	//me->add_temp("apply/defense", skill / 3);
	//me->add_temp("apply/armor", skill / 5);
	me->set_temp("hmg/powerup",skill);

	call_out("remove_effect",1,me,skill/20);

	return 1;
}

void remove_effect(object me,int count)
{
        int skill;
		
		if (!me) return;

        skill=me->query_temp("hmg/powerup");
		if (!me->query_temp("hmg/powerup")) return;
		
		if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("force")!="hamagong")
        {
			me->add_temp("apply/attack", -skill / 10);
			//me->add_temp("apply/strike", -skill / 10);
			//me->add_temp("apply/cuff", -skill / 10);
			me->add_temp("apply/staff", -skill / 10);
			//me->add_temp("apply/defense", -skill / 3);
			//me->add_temp("apply/armor", -skill / 5);
	        me->delete_temp("hmg/powerup");
	        tell_object(me, HIG"你的"HIR"「蛤蟆功」"HIG"运行完毕，将内力收回丹田。\n"NOR);
			return;
        }
		call_out("remove_effect",2,me,count--);
}
string exert_name(){ return HIG"蛤蟆气"NOR; }

int help(object me)
{
write(WHT"\n蛤蟆功「蛤蟆气」："NOR"\n");
write(@HELP
	欧阳锋的独门绝技蛤蟆功乃是天下武学中的绝顶功夫。
	自从他逆练九阴成疯而又夺得天下第一的称号后，这
	蛤蟆功更大逆寻常武功，更加怪异无伦。这逆转九阴
	之法，便是当年他传与杨过的绝技！
	蛤蟆劲气乃是蛤蟆功的精髓，是西毒欧阳锋在华山论
	剑中的独门内功心法，非嫡系子侄不传。
	注意：set 蛤蟆功散毒 会将蛤蟆毒和蛇毒随机散发

	指令：exert powerup

要求：
	当前内力 1000 以上；
	基本内功 100 级以上；
	蛤蟆功法 100 级以上；
HELP
);
return 1;

}
