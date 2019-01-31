//modify By Ziqing  Y2k
// Modified by snowman@SJ 05/12/2000

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HBGRN+HIW"摄心"NOR;}

int exert(object me, object target)
{

        int hits;

        if( !target ) target = offensive_target(me);

		if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
        	return notify_fail("「摄心大法」只能对战斗中的对手使用。\n");
           
        if( (int)me->query_skill("dulong-dafa", 1) < 350 
        || (int)me->query_skill("shenlong-yaoli", 1) < 190 
        || (int)me->query_int() <=50 )
                return notify_fail("你修为还不够，还未能运用「摄心」！\n");
         if(!userp(me) )
                return notify_fail("你没有人性，乃是一个npc，算了吧！\n");
        if( me->query_skill("force", 1) < 350 )
                return notify_fail("你的内功修为火候未到，施展只会伤及自身！\n");
     
        if( me->query("max_neili") < 5000 )
                return notify_fail("你的内力修为不足以运用「摄心」！\n");
        if( me->query("max_jingli") < 2500 )
                return notify_fail("你的最大精力修为不足以运用「摄心」！\n");
        if( me->query("neili") < 1000 )
                return notify_fail("你的内力不够，劲力不足以运用「摄心」！\n");

        if( me->query("jingli") < 500 )
                return notify_fail("你的精力有限，不足以运用「摄心」！\n");
        if( target->query_temp("shexin"))
                return notify_fail("对方已经身中摄心大法了");
        message_vision(HBBLU+HIW"$P忽然间嘴里发出“嘶~~~嘶~~”的怪异声音，同时不断嘀咕，语速甚快，有勾魂夺魄之效！\n" NOR, me , target);
        message_vision(HBBLU+HIW"$n听到$P每念一句，心中就是一凛，但觉的这人的行为希奇古怪，前所未有！\n\n" NOR, me , target);
       
        if( target->query_temp("hmg/nizhuan")){ 
           	message_vision("结果$P只觉$n招式怪异摄心大法无法成功！\n", me, target);
           	return 1;
        }
		//蛤蟆功失效
        if( target->query_temp("jiuyin/fast")){
           	message_vision("结果$P只觉$n身形飘忽不定难以捉摸摄心大法无法成功！\n", me, target);
        	return 1;
        }
		//对九阴身法失效
     	if( target->query_skill("buddhism", 1) > 200 && !target->is_killing(me->query("id")) ){
     		message_vision("结果$n佛法高深，摄心大法根本对$p没用！\n", me, target);
        	return 1;
        }
		//对高僧失效
        if( random(me->query_int()) > target->query_int()/2 ){
        	message_vision("结果$n受到$P的摄心大法的影响，原先的斗志顿然消失！\n", me , target);
       		target->remove_all_killer();
       		target->receive_damage("jing", me->query_int()*10, me);
       		target->receive_wound("jing", me->query_int()*3, me);
        	if( !userp(target) )
        		target->add_busy(4); 
			else target->add_busy(2);
        	hits = random(60)+(me->query_dex()-target->query_dex())*5+(me->query("jingli")-target->query("jingli"))/20;
       		if (hits > 30) {
        		message_vision(HIR"$n受到$P摄心大法感应，越斗越是害怕，力气顿时无法凝聚! \n", me , target);
         		target->apply_condition("sld_shexin", 3+random(3) );
         		target->apply_condition("no_perform", 3);
         		target->apply_condition("no_exert", 3);
				target->set_temp("shexin",1);
         		target->set("jiali", 0);
         		me->start_busy(1);
        	}
        }
		else
		{
			me->start_busy(2);
			message_vision("结果$P只觉$n行为举止诡异莫名！\n", me, target);
		}
		me->add("neili",-300);
        me->add("jingli",-100);
        me->start_exert(5, "「摄心」");
        return 1;
}  
int help(object me)
{
        write(HIG"\n毒龙大法之"+HBBLU+HIW"「摄心」："NOR"\n\n");
        write(@HELP
	毒龙大法乃是神龙岛内功绝技，乃是开山祖师
	洪教主根据门派独特心法所创立。既有其蛇毒
	的特性，又有其强悍的一面。
	「摄心」绝技乃是根据蛇在进攻过程中不断发
	出嘶嘶之声以恐吓对方所所悟的武功。对方若
	为这招所惑，则会陷入封招闭气状态。
	注意：此招对身负蛤蟆功，九阴身法，佛法高
	深的对象失效，需解谜方可使用；

	使用指令：yun shexin
		
要求：
	当前内力要求 5000 以上；
	最大内力要求 1000 以上；
	最大精力要求 2500 以上；
	当前精力要求 1000 以上；
	基本内功等级 350  以上；
	毒龙大法等级 350 以上；
	神龙药理等级 190 以上；
	当前悟性需求 50 以上；
	激发内功为毒龙大法；
	
HELP
        );
        return 1;
}

