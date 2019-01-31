// This program is a part of NITAN MudLIB
// sheshen.c 「舍身喂鹰」

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me,int count);

int perform(object me)
{
        object weapon;
        int skill;
        string msg;

        if (userp(me) && ! me->query("quest/sl/cbd/pass"))
                return notify_fail("你还没有受过高人指点，无法施展「舍身喂鹰」。\n");
        
		if ((int)me->query_skill("cibei-dao", 1) < 250)
                return notify_fail("你的慈悲刀法不够娴熟，不会使用「舍身喂鹰」。\n");
        if ((int)me->query_skill("blade", 1) < 250)
                return notify_fail("你的基本刀法不够娴熟，不会使用「舍身喂鹰」。\n");

        if ((int)me->query("neili") < 500 )
                return notify_fail("你的真气不够，无法使用「舍身喂鹰」。\n");
		if (me->query_skill_mapped("blade")!="cibei-dao")
		        return notify_fail("你没有激发刀法或招架为慈悲刀，无法使用「舍身喂鹰」。\n");

        if ((int)me->query_temp("cbd/sheshen"))
                return notify_fail("你已经在运功中了。\n");
        if (me->query_skill_mapped("parry")!="cibei-dao")
                return notify_fail("你没有招架慈悲刀。\n");

        if (!objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        skill = me->query_skill("cibei-dao", 1);
		if (me->query_skill_mapped("force")=="yijin-jing")
		{
			skill=skill+me->query_skill("yijing-jing",1)/3;
			message_vision(RED"$N身负少林绝学易筋经，慈悲刀法威力大增！\n"NOR,me);
		}
        msg = YEL "$N" YEL "使出慈悲刀法「舍身喂鹰」，将浑身的功力都运到" +
              weapon->query("name") + YEL "上，幻起一片刀光,将周身防御水泄不通！\n" NOR;
        
		message_vision(msg, me);
	
        me->add_temp("apply/attack", skill / 3);
        me->add_temp("apply/defense", skill / 4);
		me->add_temp("apply/parry", skill / 4);
		me->add_temp("apply/armor", skill / 4);
		me->add_temp("apply/armor", skill / 4);

        me->set_temp("cbd/sheshen", skill);

        call_out("remove_effect",1,me,skill/50);

        me->add("neili", -100);
        //if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me,int count)
{
	int skill;
	if (!me) return;
	if (me->query_temp("cbd/sheshen")==0) return;
	
	skill=me->query_temp("cbd/sheshen");

	if (count<0
		||me->query_skill_mapped("parry")!="cibei-dao"
		||!me->is_fighting())
	{
        me->add_temp("apply/attack", -skill / 3);
        me->add_temp("apply/defense", -skill / 4);
		me->add_temp("apply/parry", -skill / 4);
		me->add_temp("apply/armor", -skill / 4);
		me->add_temp("apply/armor", -skill / 4);
        me->delete_temp("cbd/sheshen");
        tell_object(me, "你的「舍身喂鹰」运行完毕，将内力收回丹田。\n");
		return;
    }
	call_out("remove_effect",1,me,count--);

}
string perform_name(){ return YEL"舍身喂鹰"NOR; }
int help(object me)
{
         write(HIB"\n慈悲刀法之「舍身喂鹰」："NOR"\n");
        write(@HELP
	舍身喂鹰是选自佛教经典故事，里面蕴含舍己为人的处世哲学
	慈悲刀法攻击不强，重要的是防御，运使此招后，刀法中的慈
	悲之意顿显，防御力大增。若修习易筋经则将威力倍增。
	注意：此招需向宁波天童寺心观和尚之武学,不伤人命。 
	
	指令：perform blade.sheshen

要求：
	慈悲刀法：450
	基本刀法：450
	当前内力：500
	需激发招架慈悲刀。       
HELP
        );
        return 1;
}
