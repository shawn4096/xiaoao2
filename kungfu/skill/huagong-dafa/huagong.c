// huagong.c 化功
// by snowman@SJ
// modify by snowman@SJ 25/02/2000
// Modified by darken@SJ
// Modified by olives@SJ 5/17/2001
// for action.c changed,some bugs.
// Modified by olives@SJ 7/21/2001
// 加上失败的描述

#include <ansi.h>

inherit F_SSERVER;

string exert_name(){ return HBRED"化功"NOR; }
int check_fight(object me);
int halt_fight(object me);

int exert(object me, object target)
{
	object room, ob;

	if( !target) target = offensive_target(me);
	if( !target || !objectp(target) || !me->is_fighting(target) || !living(target))
		return notify_fail("化功只能在战斗中对对手使用。\n");

	if( !objectp(target) || target->query("id") == "mu ren" )
		return notify_fail("用火把来烧比较快。\n");

	//if( !userp(target) && !wizardp(me))
		//return notify_fail("你不能对他使用化功！\n");

	if(!( room = find_object("/d/taishan/fengchan")) )
		room = load_object("/d/taishan/fengchan");
	if( objectp(ob = present("zhong shentong", room)) ) {
		if(target->query("id") == ob->query("winner"))
			return notify_fail("大胆！竟敢对中神通运用化功大法！\n");
	}

	if( !living(target) || ! target->query("can_speak"))
		return notify_fail("它不是活物，你没法吸取内力？\n");

	if( me->query_temp("weapon"))
		return notify_fail("你必须空手使用化功大法，方能抓住对手。\n");

	if( me->query_skill_prepared("strike") != "chousui-zhang")
		return notify_fail("你必须使用抽髓掌，方能抓住对手。\n");

	if( (int)me->query_skill("huagong-dafa",1) < 350 )
		return notify_fail("你的功力不够，不能施展化功大法！\n");
    if( (int)me->query("max_neili") < 5000 )
		return notify_fail("你的最大内力不够，不能施展化功大法！\n");
	 if( (int)me->query("neili") < 1500 )
		return notify_fail("你的内力不够，不能施展化功大法！\n");
	if( (int)me->query_skill("poison",1) < 200 )
		return notify_fail("你体内的毒素不够，不能施展化功大法！\n");

	if(environment(me)->query("no_death"))
		return notify_fail("此地不能施展化功大法！\n");

	if((int)target->query("max_neili") <= 0
	|| target->query("combat_exp") < me->query("combat_exp")/2)
		return notify_fail( target->name() +"没有多少内力可化了。\n");

	message_vision(HBBLU"突然$N仰天阴阴一声长笑，运起化功大法，接着左手手掌虚扬，右手猛地向$n拍去！\n" NOR, me, target );

	if( random(me->query_int()) > target->query_int()/2) {
	    message_vision(HBMAG"$n忘记了对方乃是臭名昭著的星宿弟子，双掌一接触后，一股阴冷的气劲顺着$n的双臂直入丹田！\n" NOR, me, target );
	    me->start_busy((:check_fight:),(:halt_fight:));
	    me->set_temp("huagong/target",target);
	    target->start_busy(2);
	}
	else
		message_vision(YEL"\n可是$n看破了$N的企图，机灵地溜了开去。\n"NOR,me,target);

	if( !target->is_killing(me->query("id")) ){
		me->kill_ob(target);
		target->kill_ob(me);
	}

	me->start_exert(2+random(2),"「化功大法」");
	return 1;
}

int check_fight(object me)
{
	object target,victim, *people;
	int i,dp,ap;
	if(!objectp(target = me->query_temp("huagong/target")) || !userp(target))
	{
		me->delete_temp("huagong");
		me->start_exert(2+random(2),"「化功大法」");
		message_vision(HIC"\n$N大袖一拢，将双掌隐于袖中。\n"NOR,me);
		return 0;
	}
	target->start_busy(2);
	if (target->query_skill_mapped("douzhan-xingyi"))
		dp = target->query_skill("douzhan-xingyi",1);
	else if (target->query_skill_mapped("qiankun-daouoyi"))
	   dp = target->query_skill("qiankun-danuoyi",1);
	/*
	if(target->query_skill("qiankun-danuoyi",1)>dp)
	  dp = target->query_skill("qiankun-danuoyi",1);*/
	ap = me->query_skill("chousui-zhang",1);
	
	//化掉功力后效果
	if(target->query("max_neili") < 1
	   || target->query_temp("huagong/count") > 10) {
	    message_vision(RED"$n被$N化尽了丹元，软软的摊在地上。\n"NOR, me, target);
	    message_vision(RED"$N哈哈一笑，松开了手。\n"NOR, me, target);
	    target->add("max_neili",-50-random(30));
	    if(target->query("max_neili")<0)
		target->set("max_neili",0);
	    target->set("neili",0);
	    target->delete_temp("huagong/count");
//          me->remove_all_enemy();
//          target->remove_all_enemy();
	    me->start_exert(2+random(2),"「化功大法」");
	    return 0;
	}

	if(dp>350&&random(ap+dp)<dp)
	{
	     people = all_inventory(environment(me));
	     i = random(sizeof(people));
	     victim = people[i];
	     if(victim != me
	     && victim != target
	     && !victim->is_character()
	     && living(victim)
	     && !wizardp(victim)) {
		    message_vision(HBRED"$N灵机一动，一牵一引，把$n转到身前，让其接过了对手的致命魔掌！\n"NOR, target, victim);
		    target->remove_all_enemy();
		    me->remove_all_enemy();
		    me->set_temp("huagong/target",victim);
		    victim->start_busy(random(1));
		    return 1;
	     }
		 else{
            if (target->query_skill("qiankun-danuoyi"))
               message_vision(YEL"$N灵机一动，运起乾坤大挪移第七层神功，一牵一引，将其反击了回去！\n"NOR, target, victim);
		    else if (target->query_skill("douzhuan-xingyi"))
		       message_vision(YEL"$N灵机一动，运起斗转星移以彼之道还施彼身神功，一牵一引，将其反击了回去！\n"NOR, target, victim);
			me->remove_all_enemy();
		    me->receive_damage("qi",2000+random(2000),me);
			me->receive_wound("qi",1000+random(1000),me);
			me->apply_condition("xx_poison",5+random(5));
			me->start_busy(2);
		    //me->set_temp("huagong/target",victim);
		    //victim->start_busy(random(1));
		    return 1;
		 }
	}
	if (random(target->query("neili")) > me->query("neili")/2) {
	    message_vision(RED"$n拼著大耗真元，将全身内力用力向$N一送，挣开了$N的掌握。\n"NOR, me, target);
	    target->add("max_neili",-5-random(5));
	    me->start_exert(2+random(2),"「化功大法」");
	    return 0;
	}
	message_vision(RED"$n使劲挣扎，就是无法脱出$N掌握，只觉得内力不断流失。\n"NOR, me, target);
	//me->add("combat_exp", random(me->query_skill("poison"))/10);
	target->add("max_neili", -10-random(10));
	target->add("neili", -ap*2-random(ap));
	target->add_temp("huagong/count", 1);
	return 1;
}

int halt_fight(object me)
{
	notify_fail("你双手一扯，藏入飘飘的双袖中，恍若未动一般。\n");
	me->start_busy(1+random(2));
	me->start_perform(2+random(2),"「化功大法」");
	me->start_exert(2+random(2),"「化功大法」");
	return 1;
}


int help(object me)
{
        write(HBBLU"\n化功大法之「化功」绝技：\n"NOR);
        write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	化功大法吸人内力，阴毒异常，江湖上人提起，无不谈虎色变。
	这化功大法之化功绝技乃是以毒化去对方内力的效果，通过毒气
	运用，附加以高深的内功在于对方接触过程中不断侵蚀对方经脉，
	伤害其功力和最大功力，端的是阴险无比。解密化功大法的奥秘
	后，会出现飞跃。斗转星移和乾坤大挪移对此招有一定克制功效，		 
	最终判断双方功力。玩家当慎用。
	
	指令：yun huagong

要求:
	化功大法 350 级；
	毒技等级 200 级；
	当前内力 1500 点；
	最大内力 5000 点。
	需激发掌法为抽髓掌,
	命中悟性有关。
HELP
);
return 1;
}
