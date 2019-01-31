// fanshen.c 鹞子翻身刀
//Created by sohu
//苗人凤凝立不动，听得正面刀来，左侧鞭至，仍是不闪不架，待得刀鞭离身不过半尺，猛地转身，刷的一刀，
//正中持鞭者右臂，手臂立断，钢鞭落地。那人长声惨呼。持刀者吓了一跳，伏身向旁滚开。
#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HBRED"鹞子翻身刀"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i,damage;
	string msg;
    i = me->query_skill("hujia-daofa", 1);
    if( !target ) target = offensive_target(me);
   
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「鹞子翻身刀」只能对战斗中的对手使用。\n");

    if((int)me->query_skill("force", 1) < 250 )
                return notify_fail("你的基本内功不够娴熟，无法支持「鹞子翻身刀」。\n");

    if( (int)me->query_skill("hujia-daofa", 1) < 250 ) 
                return notify_fail("你的胡家刀法还未练成，不能使用「鹞子翻身刀」！\n");

    if((int)me->query_skill("blade", 1) < 250 )
                return notify_fail("你的基本刀法不够娴熟，不能使用「鹞子翻身刀」。\n");

    if((int)me->query_skill("dodge", 1) < 250 )
                return notify_fail("你的基本轻功不够娴熟，不能使用「鹞子翻身刀」。\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "blade"
        || me->query_skill_mapped("blade") != "hujia-daofa")
        //|| me->query_skill_mapped("parry") != "hujia-daofa"
                return notify_fail("你手里无刀，如何使用「鹞子翻身刀」？\n");
                 
    if((int)me->query("max_neili") < 5000 )
                return notify_fail("你的内力修为不够，不能使用「鹞子翻身刀」！\n");

    if((int)me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用「鹞子翻身刀」！\n");

    if((int)me->query("jingli") < 1000 )
                return notify_fail("你现在太累了，不能使用「鹞子翻身刀」！\n");
    if((int)me->query("hjdf/fanshen")  )
                return notify_fail("你正在使用「鹞子翻身刀」！\n");
      
    message_vision(RED"\n$N凝立不动，仍是不闪不架，待得$n离身不过半尺，猛地转身，刷的一刀！\n忽然施展出胡家刀法之"HIG"「鹞子翻身刀」"RED"绝技!\n"NOR, me,target);
        
    me->add("neili", -800);
    me->add("jingli",-500);
    me->set_temp("hjdf/fanshen",1);

  
    if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_dex(1))>target->query_dex(1)/2)
    {  
	
	    message_vision(HIR"\n\n$n却见$N陡然反身，将手中的"+weapon->query("name")+HIR"正中$n右臂，$n惨叫一声，手臂立断！\n"NOR,me,target);
		//target->set_temp("must_be_hit",1);
		damage=i+me->query_skill("force",1)+me->query_skill("blade",1);
		damage=damage*me->query_dex(1)/10;
		
		if (userp(target) && damage >6000) damage=6000+random(1000);
		
		
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/4,me);
        if (wizardp(me)) write("damage="+damage);
       
		target->apply_conditon("broken_arm",1);

		msg = damage_msg(damage, "震伤");
		msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));        
    	
    } else
	{
		message_vision(HIC"$n当即一个铁板桥躲过此招，但却吓了一声冷汗。\n"NOR,me,target);
		target->apply_condition("no_exert",1);
		target->add_busy(1);
		me->add_busy(2);
		
	}
   
    me->delete_temp("hjdf/fanshen");
   // me->start_busy(1);
	me->start_perform(2+random(2),"「鹞子翻身刀」");
    //target->start_busy(1);
    return 1;
}

int help(object me)
{
   write(YEL"\n胡家刀法之「"HIG"鹞子翻身刀"YEL"」："NOR"\n");
   write(@HELP
	胡家刀法乃是传自辽东大侠胡一刀的家传绝技，后来
	胡一刀和苗人凤彼此间结下了恩怨之仇，使得胡斐流
	落江湖，凭借此刀法纵横江湖。乃刀中绝技。
	鹞子翻身刀，乃是利用高超的身法优势，快速反应，
	往来纵横驰骋，令敌人防不胜防间，反手一刀劈出，
	劈向对方手臂，使得制敌人呈断手状态。异常凶狠辣
	注意：鹞子翻身刀需要高身法方显威力。

	指令：perform blade.fanshen

要求：
	胡家刀法 250 级，
	基本刀法 250 级，
	基本轻功 250 级，
	基本内功 250 级，
	最大内力 5000 以上，
	当前内力 1000 以上，
	当前精力 1000 以上，
	激发刀法为胡家刀法。
	手持刀类武器；
HELP
   );
   return 1;
}