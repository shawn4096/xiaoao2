// taiji.c 太极拳「太极」
// by lsxk@hsbbs 2/06/2007
/*
	掤－－自己被击中时,消耗大量内力来反噬对方攻击
	捋－－自己被击中时,降低对方攻击力道
	挤－－击中对方时,让对方短暂忙乱
	按－－击中对方时,在短时间内对方无法使用特殊内功
	采－－击中对方时,若对方忙乱,则重击对手
   挒－－自己被击中时,在短时间内对方无法使用特殊外功
   肘－－击中对方时,重击对方
   靠－－自己被击中时,使对方短时间内无法出招
*/
//适当下调各项数值，玩家反映太变态了。。By Spiderii
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI                "/kungfu/skill/yinyun-ziqi/taiji"

void taiji_check(object, object, string, int);

string perform_name(){ return HIW"太极"NOR; }
string *taiji_sn = ({"掤","捋","挤","按","采","挒","肘","靠",});

int perform(object me, object target)
{
        if( !target ) target = offensive_target(me);

         if( !objectp(target)|| !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「太极」只能对战斗中的对手使用。\n");

       if(userp(me) && me->query("quest/tjq/taiji")!="pass")
            return notify_fail("你尚未精通太极奥意,还不会使用「太极」如此精妙得招数!\n");

	   if( userp(me)
        &&( me->query_skill_mapped("parry") != "taiji-quan" ))
                return notify_fail("「太极」必须在用太极拳激发招架的情况下才能使用。\n");
        if( userp(me) && ( me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("你的内功或拳法不对，根本不能发挥出「太极」的优势。\n");  
        if( me->query_skill("taiji-quan", 1) < 500 )
                return notify_fail("你对太极拳理的理解还不够，还使不出这精妙的「太极」？\n");
        if( me->query_skill("yinyun-ziqi", 1) < 500 )
                return notify_fail("你的氤氲紫气的还不够熟练，无法使出「太极」!\n");
        if( me->query_skill("taoism", 1) < 200 )
                return notify_fail("你对道学心法的理解还不够，使出这精妙的太极「太极」惟恐会走火入魔！\n");
        if( (int)me->query("neili", 1) < 2000 )
                return notify_fail("「太极」乃靠一口精湛浑厚的内力所支，以你目前的内力实在难以使出该绝招！\n"); 

        if( (int)me->query("max_neili", 1) < 15000 )
                return notify_fail("「太极」乃靠一口精湛浑厚的内力所支，以你目前的内力修为实在有所不妥！\n"); 
//         if( (int)me->query("max_jingli", 1) < 4000 )  
// 不能用max_jingli 看看eff_jingli
        if( (int)me->query("max_jingli", 1) < 5000 )  
                return notify_fail("「太极」乃需消耗极大的精力来克敌制胜的绝招,你目前的精力修为实在太低了！\n"); 
        if( (int)me->query("jingli", 1) < 1500 )
                return notify_fail("你目前的精力太低了,使不出「太极」绝招！\n");

	    if( me->query_temp("tjq/taiji"))
                return notify_fail("你正在使用「太极」!\n");

        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n"); 

        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
        int i,num,j;
        string msg, taiji_set;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target)
        || me->query("neili") < 2000 || me->query("jingli") < 1500 || me->query_temp("weapon"))
                return 0;

       i = (int)me->query_skill("taiji-quan",1) / 20;
	   j = 3 + ((int)me->query_skill("taiji-quan",1)-400)/30;
	   if (j>8) j = 8;

	   taiji_set = me->query("env/taiji");

         msg = HBMAG+HIW "\n$N当下凝神聚精，招式已不见凌厉之气，但见每一招，每一式，均弧形击出，弧形收回，竟无半点棱角！"+

			 "\n$N更将太极口诀精要之处发挥得淋漓尽致，招式浑然一体，已然深得「太极」精要！\n"NOR;
       message_vision(msg, me, target);
       me->add_temp("apply/defense",me->query_skill("taiji-quan")/2 );

       me->start_perform(3,"「太极」");

//若没有set taiji 则	
       if (!me->query("env/taiji")){
		for (num=0;num<j;num++){
		   if (!me->query("env/taiji"))
			me->set("env/taiji",taiji_sn[random(sizeof(taiji_sn))]+"|");
		   else
            me->set("env/taiji",me->query("env/taiji")+taiji_sn[random(sizeof(taiji_sn))]+"|");
		   //若自己设置了，就会在设置基础上随机添加
		}
		taiji_set = "none";
	   }
		me->set_temp("tjq/taiji",j); 
		me->add_temp("apply/attack", i);
		me->add_temp("apply/armor", i);
		me->add_temp("apply/dodge", i);

	   taiji_check(me,target,taiji_set,i);
		target->set_temp("must_be_hit",1);
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);

		target->delete_temp("must_be_hit");
   
        return 1;

}

void taiji_check(object me, object target, string taiji_set, int i)
{
	if (!me) return;
	if (!me->is_fighting()
	 || me->query_skill_mapped("cuff")!="taiji-quan"
	 || me->query_skill_mapped("force")!="yinyun-ziqi"
	 || me->query_skill_mapped("parry")!="taiji-quan"
	 || !me->query_temp("tjq/taiji")
	 || (int)me->query("neili",1) < 2000
	 || (int)me->query("jingli",1) < 1500
	 || me->is_ghost()
	 || (me->query_temp("tjq/taiji") && !me->query("env/taiji") ))
	{
 		   me->delete_temp("tjq/taiji");
           me->add_temp("apply/attack", -i);
           me->add_temp("apply/armor", -i);
           me->add_temp("apply/dodge", -i);
           message_vision(WHT"\n$N「太极」神功使完，气归丹田，缓缓收功而退！\n"NOR, me);
		   
me->add_temp("apply/defense", - me->query_skill("taiji-quan")/2 );

		if (taiji_set !="none") me->set("env/taiji",taiji_set);
		else me->delete("env/taiji");
	}
   else{
//       remove_call_out("taiji_check");
       call_out("taiji_check",1,me,target,taiji_set,i);
   }
   return;
}

int help(object me)
{
	write(WHT"\n太极拳之绝技「"HIW"太极"WHT"」："NOR"\n");
	write(@HELP
	太极者，四两拨千斤之句，显非力胜；观耄耋御众之形，快何能为。立如秤
	准，活如车轮，偏沉则随，双重则滞。由招熟而渐悟懂劲，由懂劲而阶及神
	明。然非用力日久，不能豁然贯通焉。
	此「太极」神功乃太极拳练到极高明的境界后而领悟出的集攻防于一体的神
	技!若运用得法,恐当世无人能敌!
	使用前请按照格式set taiji 参数1|参数2|参数3|....设定顺序；
	可选参数如下：
	掤，捋，挤，按，采，挒，肘，靠。

	指令:  perform cuff.taiji

要求：
	最大内力需求 15000 以上；
	最大精力需求 5000 以上；
	当前内力需求 2000 以上；
	当前精力需求 1500 以上；
	太极拳法等级 500 以上；
	氤氲紫气等级 500 以上；
	道学心法等级 200 以上；
	激发拳法为太极拳法
	激发招架为太极拳法
	激发内功为氤氲紫气；
	手无兵器；

          
HELP
	);
	return 1;
}
