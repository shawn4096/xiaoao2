// Modified by Darken@SJ
// Modify by server@sjty 2007.7.27 增加失败描述。


#include <ansi.h>
inherit F_SSERVER;

void remove_effect(object me, object target, int count, int skill);

string exert_name() { return HIM"奇门迷魂阵"NOR; }

int exert(object me, object target)
{
        int skill;
        skill = me->query_skill("qimen-bagua", 1);
        if( !target ) target = offensive_target(me);
        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("布迷阵只能对战斗中的对手使用。\n");
        if (me->query_temp("thd/mazed")) 
                return notify_fail("你正在陷入别人布的迷阵中。\n");

        if (me->is_busy())
             return notify_fail("你目前正自顾不暇，无暇布置迷阵。\n");
		//禁止NPC用，以免bug
		if (!userp(me)) return 0;
		
        if( (int)me->query("neili") < 300  ) 
                return notify_fail("你的内力不够。\n");
        if( (int)me->query("jingli") < 200  ) 
                return notify_fail("你的精力不够。\n");
        if( (int)me->query_temp("thd/maze") ) 
                return notify_fail("你已经布了一个迷阵了。\n");

        me->add("neili", -200+random(300));
        me->add("jingli",-100);
        me->start_exert(5,"奇门迷魂阵");
		if (me->query("thdjj/ronghe")=="pass") 
		{
		  message_vision(HBRED+HIY"$N飘然跃起，左拍一掌，右挑一腿，行动间轻松将周围的石块、树枝悄然移动了位置！\n"NOR, me, target);
		  skill=skill+me->query("bihai-chaosheng",1)/6;
	   }
		else
			message_vision(HIY"$N突然跃起，左拍一掌，右挑一腿，将周围的石块、树枝移动了位置！\n"NOR, me, target);

               me->set_temp("thd/maze", skill);    
			   
               me->add_temp("apply/dexerity", skill/10);
               me->add_temp("apply/dodge",  skill /2);
               me->add_temp("apply/parry",  skill /2);
			   if (me->query("thdjj/ronghe")=="pass") {
				   me->add_temp("apply/defense", skill/2);
                   me->add_temp("apply/attack", skill/5);
			   }


       if(random(me->query_dex()) > target->query_dex()/3 
		   || random(skill) > target->query_skill("qimen-bagua",1)/3 )
       {
                message_vision(HBYEL"$n陷入迷阵中，登时手足无措。\n" NOR, me, target);
                target->add_temp("apply/dexerity", -skill/10);
                target->add_temp("apply/damage", -skill/2);
                target->add_temp("apply/dodge",   -skill/2);
                target->add_temp("apply/parry",     -skill/2);
                target->set_temp("thd/mazed", skill);
				
                if (me->query("thdjj/ronghe")=="pass") target->start_busy(4+random(2));
				else target->start_busy(2+random(1));
				//call_out("remove_effect", 1, me, target, skill / 2, skill);
       }
       else {
                message_vision(HBGRN"$n迅速趋前退，身形连闪，已在迷阵之外。\n" NOR, me, target);
                me->start_exert(3,"奇门迷魂阵");
				me->add_busy(1+random(2));
        }
	    call_out("remove_effect", 1, me, target, skill / 2, skill);
       return 1;
}
void remove_effect(object me, object target, int count, int skill)
{
        if (objectp(me) && me->query_temp("thd/maze")){
                if (count-- > 0 && me->is_fighting(target)) {
                        call_out("remove_effect", 1, me, target, count, skill);
                        return;
                }
			//如果出maze的是npc，当npc死了，并且没有出现
                if (me->query("thdjj/ronghe")=="pass") {
			        me->add_temp("apply/defense", -skill /2);
                    me->add_temp("apply/attack", -skill /5);
	            }
                me->add_temp("apply/dexerity", -skill/10);
                me->add_temp("apply/dodge",   -skill /2);
                me->add_temp("apply/parry",   -skill /2);
                me->delete_temp("thd/maze");

                if (!target) return;

                me->delete_temp("thd/maze");

                if (objectp(target) && me->is_fighting(target)) {
                        
						tell_object(me, "你布的迷阵已经被" + target->name() + "破坏了。\n");
                        if (userp(target) && living(target))
                                tell_object(target, me->name() + "对你布的迷阵已经被你识破了。\n");
                }
                else {
                        tell_object(me, "你布的迷阵已经失效了。\n");
                  }
        }
        if (objectp(target) && target->query_temp("thd/mazed")){

                target->delete_temp("thd/mazed");
                target->add_temp("apply/dexerity", skill/10);
                target->add_temp("apply/damage", skill/2);
                target->add_temp("apply/dodge",  skill/2);
                target->add_temp("apply/parry",  skill/2);

        }
		return;


}

int help(object me)
{
        write(HIG"\n「奇门迷魂阵」："NOR"\n");
        write(@HELP

	使用奇门八卦之易理，在身旁以碧海潮生之内劲
	迅速排列树枝，土石等物来布下一个特别为短兵
	相接所准备的迷阵。陷入迷阵的对手不仅动作忙
	乱，同时战斗能力也会降低；自身的防御和招架
	相对的提高。
	效果跟双方奇门八卦等级差及身法对比密切相关。
	
	指令：exert maze

要求：
	碧海潮生等级 50 以上；
	奇门八卦等级 50 以上；
	最大内力 300 以上；
	若是自身陷入对手的迷阵则无法使用。
HELP
        );
        return 1;
}

