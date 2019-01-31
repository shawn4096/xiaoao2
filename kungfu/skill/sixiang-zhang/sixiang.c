// piaoxue.c by sohu@xojh
//峨嵋武学，暗合河洛四象。源出河洛之图，变化方位暗合四象玄机。
//[1]  该掌法依据四象中天地阴阳的种种变化，从而创出的掌法。此招一经施展，对手在受伤后还是深陷其中，无法脱身。是非常实用的招数。 [2] 
//sixiangyi.c 四象掌意

#include <ansi.h>

inherit F_SSERVER;


int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total; 
       
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「四象意」只能在战斗时使用！\n");
         
        if( objectp(weapon=me->query_temp("weapon")) )                              
                return notify_fail("你手里拿着武器，无法施展「四象意」！\n");               
        
        if( (int)me->query_skill("sixiang-zhang", 1) < 200 )
                return notify_fail("你的四象掌还不够熟练，不能使用「四象意」！\n");

        if (me->query_skill_mapped("strike") != "sixiang-zhang"
			||me->query_skill_prepared("strike") != "sixiang-zhang")
                return notify_fail("只有使用四象掌时才能使用「四象意」！\n");
	    if (me->query_skill_mapped("dodge") != "anying-fuxiang")
                return notify_fail("四象掌只有使用暗影浮香轻功时才能使用「四象意」！\n");

        if( (int)me->query_skill("linji-zhuang", 1) < 200 )
                return notify_fail("你的临济庄还不够熟练，不能使用「四象意」！\n");       

        if((int)me->query("max_jingli", 1) < 1000 )
                return notify_fail("你的最大精力不足，不能使用「四象意」！\n");       

        if((int)me->query("max_neili", 1) < 1800) 
                return notify_fail("你的最大内力不足，不能使用「四象意」！\n");      		
        if((int)me->query("neili", 1) < 500) 
                return notify_fail("你的当前内力不足，不能使用「四象意」！\n");      		
        if( me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("你现在所使用的内功同临济庄相抵触，不能使用「四象意」。\n");
        
		if (target->is_busy())
		{
                return notify_fail("对方已经手忙脚乱中，赶紧进攻吧！\n");   		

		}
		me->add("jingli",-100);
        me->add("neili",-400);
        
        message_vision(HIC"$N轻身前纵，左手向左划了半圆，右手成掌，向前急速推出，施展出峨嵋派四象掌法之「四象意」绝技。\n"NOR,me,target);
		message_vision(HIW"\n\n$N行走之间，举手投足间暗合河洛四象，变化方位暗合四象玄机的阴阳变化，一经施展，$N宛如花中蝴蝶，飘忽不定。\n "NOR,me,target);
        if(random((int)me->query_skill("sixiang-zhang",1))> (int)target->query_skill("parry",1)/2
          ||random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/2
          ||target->is_busy() )
		{
			message_vision(HIY"\n$N将天地阴阳的种种变化都融合在招式和步伐中，$n顿觉自己深陷其中，无法脱身，四面八方都是$N的影子。\n "NOR,me,target);
			if (!userp(target))
			{
				target->add_busy(3+random(3));
			}
			else target->add_busy(1);
			
			if (objectp(target)&&me->is_fighting(target))
				call_out("attack_damage",1,me,target);     
			  
		}else {
			message_vision(HIY"$n对于阴阳八卦和四象之学早已了然于胸，向左侧斜行半步，顿时走出$N的漫天掌影。\n"NOR,me,target);
			me->start_busy(1);
		}
		
		   

		if (me->query_skill("sixiang-zhang",1)<250)
			me->start_perform(2,"四象意");
        return 1;
}

int attack_damage(object me,object target)
{
		int i,total;
		string result,msg;
		if (!me||!target) return 0;
		
		message_vision(CYN "\n$N间$n疏忽，顺手使出一招「"HIW"漫天飞雪"CYN"」，双掌飞舞，出掌飘逸，两畔生风，夹杂着令人窒息的劲气击向$n。\n"NOR,me,target);

        total=(int)me->query_skill("sixiang-zhang",1)+(int)me->query_skill("linji-zhuang",1)+(int)me->query_skill("strike",1)+(int)me->query_skill("anying-fuxiang",1);
		if (me->query("class")=="bonze") i=i+me->query_skill("dacheng-fofa",1);
        total += i;
		total=total*2;
        if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
		target->receive_damage("qi", total, me );
		target->receive_wound("qi", total/3 , me);
		result = COMBAT_D->damage_msg(i,"瘀伤");
		result = replace_string( result, "$l", "腹部" );
		msg = result;
		message_vision(msg,me,target);
        COMBAT_D->report_status(target, 0); 
		return 1;
}
string perform_name(){ return HIC"四象意"NOR; }

int help(object me)
{
   write(HIC"\n四象掌之「 四象意 」："NOR"\n");
   write(@HELP
	四象掌绝学是峨嵋重要的空手武技，和雁行刀法配合有不弱
	的表现，当和峨嵋的另外一项空手武技截手九式互备后，会
	产生一定程度的飞跃。四象意是利用峨嵋身法的急速走动和
	掌法精意，将对方困在掌法之中的招式。250后飞跃
	
	指令: perform strike.sixiang
	
要求：
	最大内力的需求 1800 以上；
	最大精力的需求 1000 以上；
	当前内力的需求 500 以上；
	四象掌法的等级 200 以上；
	基本掌法的等级 200 以上；
	临济十二桩等级 200 以上；
	出家人因大乘佛法原因，有略微优势。
		
HELP
   );
   return 1;
}
