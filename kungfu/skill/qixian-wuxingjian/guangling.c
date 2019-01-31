// guangling.c
//updated by Zmud@Sjmud 10/3/2009

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int i, a;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「广陵散意」只能对战斗中的对手使用。\n");

		if( me->query_temp("qxwxj/guangling") )
			 return notify_fail("你正在使用「广陵散意」。\n");
 
        if( (int)me->query_skill("qixian-wuxingjian", 1) < 400 )
		   return notify_fail("你的七弦无形剑等级不足，无法使出「广陵散意」。\n");
 
        if( (int)me->query_skill("sword", 1) < 400 )
		   return notify_fail("你的基本剑法等级不足，无法使出「广陵散意」。\n");

		
        if( (int)me->query_skill("force", 1) < 400 )
		    return notify_fail("你的基本内功等级不足，无法使出「广陵散意」。\n");

        if( (int)me->query("max_neili") < 9000 )
		   return notify_fail("你的内力修为太浅，无法使出「广陵散意」。\n");

	    if( (int)me->query("neili") < 2000 )
		   return notify_fail("你的真气不足，无法使出「广陵散意」。\n");
		
		if( (int)me->query("jingli") < 1000 )
		   return notify_fail("你的精力不足，无法使出「广陵散意」。\n");

	    //if( me->query_skill_mapped("force") != "xixing-dafa" )
		  // return notify_fail("你没有使用吸星大法，无法使出「广陵散意」?\n");

	    if( !objectp(weapon = me->query_temp("weapon"))
	     || weapon->query("skill_type") != "sword"
	     || me->query_skill_mapped("sword") != "qixian-wuxingjian" )
	    	return notify_fail("你使得了「广陵散意」么?\n");

        i = (int)me->query_skill("qixian-wuxingjian",1) /3 +(int)me->query_skill("xixing-dafa",1) /3;
        
        
		message_vision(MAG"$N左手捏了剑诀，右手将手中的"+weapon->query("name")+MAG"轻轻一弹，一阵密集清脆的乐音响起，其旋律正是名闻江湖的「广陵散意」。\n"NOR,me);
		message_vision(HIG"$N轻轻一叹，轻声哼着旋律，轻吟道，”人言嵇康之后再无广陵散，纯属无稽之谈“！\n"NOR,me);
		message_vision(MAG"随后，$N漫不经心的看了$n一眼，喝道，既然如此，我就让你见识见识这广陵散的真意！\n"NOR,me,target);
		message_vision(HIM"$N施展出七弦无形剑绝技「广陵散意」，看似轻盈飘渺，但散发的剑气却愈见凌厉，嗤嗤作响！\n"NOR,me);

		me->add("neili",-(150+random(50))); 
        me->add("jingli",-150); 
		me->set_temp("qxwxj/guangling",i);
		
		me->add_temp("apply/attack",i/3);
		me->add_temp("apply/sword",i/6);
		//me->add_temp();
		
		call_out("remove_effect",1,me,i/10);
		
        return 1;
}


void remove_effect(object me, int count)
{
        int i;
		if (!objectp(me)) return;
	    i=me->query_temp("qxwxj/guangling");
		
		if (objectp(me) && me->query_temp("qxwxj/guangling")){
                if (count-- > 0 && me->is_fighting()) {
                        call_out("remove_effect", 1, me, count);
                
                        return;
                }
		}
		me->add_temp("apply/attack",-i/3);
		me->add_temp("apply/sword",-i/6);

        message_vision(MAG"$N从广陵散意境中退了出来，急速喘息几口真气，缓缓收功。\n"NOR,me);
        me->delete_temp("qxwxj/guangling");
        
		return;
   
}

string perform_name(){ return HIM"广陵散意"NOR; }
int help(object me)
{
        write(HIB"\n七弦无形剑"+HIY"「广陵散意」"NOR"\n");
        write(@HELP
	“七弦无形剑”乃是梅庄四友中老大，黄钟公的成名绝技。“七弦无形剑”
	是黄钟公自创的绝技。对敌的时候，通过在琴音之中灌注上乘内力，用
	以扰乱敌人心神，对方内力和琴音一生共鸣，便不知不觉地为琴音所制。
	琴音舒缓，对方出招也跟着舒缓；琴音急骤，对方出招也跟着急骤。但
	黄钟公琴上的招数却和琴音恰正相反。他出招快速而琴音加倍悠闲，对
	方势必无法挡架。
	「广陵散意」“七弦无形剑”只是琴音，声音本身自不能伤敌，效用全在
	激发敌人内力，扰乱敌招，对手内力越强，对琴音所起感应也越加厉害。
	其中最厉害的招数是“六丁开山”神技，施展时通过六次拨弦，不断催加
	内力，最后七弦同响，内力催到顶峰，是黄钟公武功中的登峰造极之作。
	450后大飞。

	指令：perform sword.guangling

要求：
	最大内力要求 9000 以上
	当前内力要求 2000 以上
	当前精力要求 1500 以上
	基本内功等级 400 以上；
	基本剑法等级 400 以上；
	七弦无形剑法 400 以上；
	持有剑类武器；
	无需特定门派内功支持,
	吸星大法有额外加成。

HELP
        );
        return 1;
}

