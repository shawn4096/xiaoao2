//昆仑叠掌之红砂掌
//冯锡范绝技
// By sohu

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HBRED+HIY"红砂掌"NOR; }

void checking(object me,int count);

int perform(object me, object target)
{
        int skill;

        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("【红砂掌】只能在战斗中使用。\n");       
        if( (int)me->query_skill("strike", 1) < 350 )
                return notify_fail("你的基本掌法不够娴熟，无法使用昆仑叠掌之红砂掌。\n");  
 		if((int)me->query_skill("kunlun-zhang", 1) < 350 )
                return notify_fail("你的昆仑叠掌还不够娴熟，不能使出昆仑叠掌之红砂掌。\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 350 )
                return notify_fail("你的玄天无极功修为不足以将内力外放。\n");

		//意味着550后可以武器蓄力？？
		
		if( objectp(me->query_temp("weapon")) )
                return notify_fail("红砂掌需要空手使用。\n");  
        
        if (me->query_skill_prepared("strike") != "kunlun-zhang"
           || me->query_skill_mapped("strike") != "kunlun-zhang")
                return notify_fail("你不使用昆仑叠掌，又岂能使得红砂掌？\n");   
        
		if( (int)me->query("max_neili", 1) < 6000 )
                return notify_fail("你内力修为太浅，无法红砂掌！\n");                
        if( (int)me->query("neili", 1) < 2000 )
                return notify_fail("你现在真气不够，无法红砂掌。\n");

        if( me->query_skill("poison",1)<150 )
                return notify_fail("你的毒性不够150，无法发挥不出红砂掌之威。\n");   
        if( me->query_str(1) < 70 )
                return notify_fail("你的后天臂力不足70，无法使用昆仑叠掌之红砂掌。\n");  

		if( !me->query("quest/kl/klz/hongsha/pass") )
                return notify_fail("你未得到冯锡范的传授，无法发挥不出红砂掌之威。\n");   
        
		if( me->query_temp("klz/hongsha") )
                return notify_fail("你正在施展红砂掌力！？\n");
                                                                               
        skill=me->query_skill("kunlun-zhang",1);

        message_vision(HBRED+HIY"\n$N运起内功，面色泛起一片红潮，真气缓缓溶入双手，双手呈一片赤红状，极为骇人，正是昆仑绝学「红砂掌力」！\n" NOR, me);
  //      message_vision(HBRED+HIY"\n！\n" NOR, me);
		if (me->query("gender")!="男性")
		{
			skill=skill/3;
		}
		me->set_temp("klz/hongsha",skill);
		me->add_temp("apply/attack",skill/5);
		me->add_temp("apply/strike",skill/5);
		me->add_temp("apply/damage",skill/8);

        me->add("neili", -500);
		me->add("jingli",-200);
        call_out("checking",0,me,(int)skill/30);
        return 1;
}

void checking(object me,int count)
{
		int skill;
		if( !me )  return;	
		
		skill=me->query_temp("klz/hongsha");
		
		if (count<0
		||me->query_skill_mapped("strike")!="kunlun-zhang"
		||me->query_skill_prepared("strike")!="kunlun-zhang"
		||!me->is_fighting())
		{
			me->add_temp("apply/attack",-skill/5);
			me->add_temp("apply/strike",-skill/5);
			me->add_temp("apply/damage",-skill/8);

			me->delete_temp("klz/hongsha");

			message_vision(RED"$N呼出一口暗红色浊气，缓缓将红砂掌力收功！\n"NOR,me);
			return;
		}
		
		call_out("checking",1,me,count-3);

}  


int help(object me)
{
	write(WHT"\n昆仑叠掌之「"HBRED+HIY"红砂掌"WHT"」："NOR"\n");
	write(@HELP
	昆仑红砂掌是昆仑名宿冯锡范的著名招式，以内劲
	运使双掌，呈赤红之色，打中对方后，对方身上会
	有明显的血红掌印，中者若不及时救治怕有生命之
	忧。实乃昆仑掌法独到之招式。男性威力强于女性

	此招是因毒气聚集丹田，由掌而发，所以毒计水准
	足够高且和蓄力配合得当，昆仑掌威力将大增。解
	开谜题后，会让对手随机中毒。


	注意:此招需向冯锡范请教，乃是昆仑绝学之一
	
	指令：perform strike.hongsha

要求：     
	当前内力 2000 以上，
	最大内力 6000 以上。
	基本掌法 350  以上；
	昆仑叠掌 350  以上；
	毒计水平 150  以上；
	后天臂力 70   以上；
	激发内功不限；
	激发掌法为昆仑掌；
	激发招架为昆仑掌；
	空手且备掌法为昆仑掌；
	解密冯锡范方可使用。
HELP
	);
	return 1;
}
