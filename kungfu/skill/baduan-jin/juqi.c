// juqi.c 聚气  By sohu@xojh
// 作用为：增加后天身法和躲闪。  

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HIW"聚气"NOR;}

int exert(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
		skill=me->query_skill("baduan-jin",1)/10;
        if(!me->is_fighting() )
                return notify_fail("「聚气」只能在战斗中使用。\n");

        if((int)me->query_skill("baduan-jin", 1) < 100 )

			return notify_fail("你的八段锦等级不够，不能使用「聚气」。\n");
    
    
    
        if ((int)me->query("neili") < 500 )
                return notify_fail("你现在内力太弱，不能使用「聚气」。\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("你现在精力太少，不能使用「聚气」。\n");

        if(me->query_temp("bdj/juqi"))
                return notify_fail("你现正在使用八段锦「聚气」。\n");


        if (me->query_skill_mapped("force") != "baduan-jin")
                return notify_fail("你的内功有误，无法使用「聚气」。\n");

        message_vision(HIW"$N暗运一口真气，内力流转，感觉身体轻便了不少!\n"NOR, me);
        me->start_exert(3+random(2),"「聚气」");
        me->add("neili", -200);          
        me->add("jingli", -100);
    if (me->query("quest/baduanjin/pass2"))
	{
		message_vision(HIW"$N已深得八段锦之精髓，对于内力运用别有一番心得。!\n"NOR, me);
		skill=me->query_skill("baduan-jin",1)/5;		
	}	
	    me->add_temp("apply/parry",  skill);
		me->add_temp("apply/attack",  skill);
        me->set_temp("bdj/juqi", skill);

        call_out("check_fight", 0, me);
        return 1;
}

void check_fight(object me)
{  
        int i;

        if (!me) return;
        if( !me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || me->query_skill_mapped("force") != "baduan-jin")
		{
			i = me->query_temp("bdj/juqi");
			me->add_temp("apply/parry", -i);
			me->add_temp("apply/attack", -i);
			me->delete_temp("bdj/juqi");
			if(living(me) && !me->is_ghost())
              message_vision(HIY"$N渐感内力不支，长长地呼了口气，身法又恢复了先前模样。\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me);
}

int help(object me)
{
    write(YEL"\n八段锦「"HIW"聚气"YEL"」："NOR"\n");
   write(@HELP
	八段锦本是江湖流传的一门寻常基础内功，虽不及各大门派内功精
	妙但若练到深处，也绝非同小可！此「聚气」绝技乃运内劲于四肢，
	一定程度地提高自身实战招架和一定的命中。
	武林中一直有传言，八段锦中隐藏着一个极大的秘密......
	   
	指令：exert juqi

要求：
	八段锦 100 级，
	当前内力 500 以上，
	当前精力 500 以上，
	
HELP
   );
   return 1;
}
