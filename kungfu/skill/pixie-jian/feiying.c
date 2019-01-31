// feiying.c 葵花飞影术

#include <ansi.h>
string perform_name(){ return MAG"葵花飞影术"NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill,count;

        if( !target ) target = me;
		count=(int)skill/20;        
        if( (int)me->query("neili") < 500  ) 
                return notify_fail("你的内力不够。\n");
        if( (int)me->query("jingli") < 200  ) 
                return notify_fail("你的精力不够。\n");
        if( (int)me->query_temp("feiying") ) 
                return notify_fail("你已经在运用葵花飞影术了。\n");
        if( (int)me->query_skill("pixie-jian", 1) < 150 )
                return notify_fail("你的辟邪剑法还没练成，无法使用葵花飞影术。\n");
        if( (int)me->query_dex() < 30  )
                return notify_fail("你的身法太低，不能使用葵花飞影术。\n");
       if(me->query_temp("pxj/feiying"))
                return notify_fail("你已经在使用葵花飞影术。\n");

        //skill = me->query_skill("dodge",1);
        skill =me->query_skill("kuihua-shengong",1) + me->query_skill("pixie-jian",1);
        skill = skill / 10;
        me->add("neili", -300);
        me->add("jingli", -250);
		if (me->query_skill("pixie-jian",1)>200)
		{
			if(!QUEST_D->queryquest(me,"kuihua/book"))
                return notify_fail("你对辟邪剑的真意尚未理解，不能使用「飞影术」！\n");
			if(me->query("gender")!="无性" )
                return notify_fail("你没自宫，对辟邪剑的真意尚未理解，不能使用「飞影术」！\n");

		}
        message_vision(
        MAG "只见$N眼中青光一闪，凭空飞升离地尺余，身形飘浮不定，就如影子一般。\n" NOR, me);
        tell_object(me, MAG "你默运葵花飞影术，内劲外泄，将身体凭空抬了起来。\n" NOR);

        me->add_temp("apply/dodge", skill*3);
        me->add_temp("apply/parry", skill);

		if (QUEST_D->queryquest(me,"kuihua/book"))
		   me->add_temp("apply/dexerity",skill);
		
        
		me->set_temp("pxj/feiying", skill);

		call_out("remove_effect",1,me,count);
        if( me->is_fighting() &&me->query_skill("pixie-jian",1)<550) me->start_busy(1);

        return 1;
}

void remove_effect(object me, int count)
{
	int amount;
	if(!me) return;
	amount=me->query_temp("pxj/feiying");
	
	
	if (!me->is_fighting()
		||me->query_skill_mapped("sword")!="pixie-jian"
		||me->query_skill_mapped("dodge")!="pixie-jian")
	{
	
        me->add_temp("apply/dodge", - amount*3);
		me->add_temp("apply/parry", - amount);

		if (QUEST_D->queryquest(me,"kuihua/book"))
			me->add_temp("apply/dexerity",-amount);
        
		me->delete_temp("pxj/feiying");

		tell_object(me, MAG "你一遍葵花飞影术已经使完，身法又恢复正常。\n" NOR);
		return;
	}
	call_out("remove_effect",2,me,count -1);
	return;
}
int help(object me)
{
   write(WHT"\n辟邪剑法「"MAG"葵花飞影术"WHT"」："NOR"\n");
   write(@HELP
	日月神教乃江湖中重要的一大邪派组织，做事全凭个人好恶
	教中长老武技各有所长，这辟邪剑法乃是现任教主东方不败
	的绝技，后来江湖流传各种版本，但正宗辟邪剑法以轻巧、
	灵活、多变而著称。
	「葵花飞影术」是将强大功力和剑法融合，大幅提升自己的
	躲避，必须解开葵花神功，方能使用。550级后飞跃，躲避
	效果更强！。此招超过200级后只有自宫方可体味其中葵花真意。
    
	指令：perform sword.feiying

要求：
	当前内力 500 以上；
	当前精力 200 以上；
	辟邪剑法 150 以上；
	基本轻功 150 以上；
	后天身法 30  以上；
	激发轻功辟邪剑法

HELP
   );
   return 1;
}
