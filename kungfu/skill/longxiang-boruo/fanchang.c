// fanchang.c 梵唱

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#include <combat_msg.h>
#include <pktime.h>

int exert(object me, object target)
{
	object obj, weapon;
	int ap,dp,curser;  
	string force;

	if( !target ) target = offensive_target(me);

	weapon = me->query_temp("weapon");  

	if( !weapon || !(weapon->query("skill_type") == "hammer" || weapon->query("skill_type") == "lun") )
		return notify_fail("你未执法器，不能凝神梵唱。\n");
	//if( weapon->query("skill_type") != "falun" && weapon->query("skill_type") != "hammer")
	//	return notify_fail("你未执法器，不能凝神梵唱。\n");
	//if( weapon->query_amount() < 2 && weapon->query("id") != "fenghuo lun" && weapon->query("hammer_count") < 2 )
	//if( weapon->query_amount() < 2 && weapon->query("hammer_count") < 2 && ((weapon->query("skill_type") != "lun")||(weapon->query("skill_type") != "hammer")) )
	//	return notify_fail("你需要二个轮子才能击打梵唱。\n");
	
	if(!objectp(obj = me->query_temp("armor/cloth")) ||
	(
		!obj->id("shisan longxiang") && !obj->id("longxiang jiasha")
	))
		return notify_fail("你未着龙象法袍，不能凝神梵唱。\n");

	if( !objectp(target) || target == me)
		return notify_fail("你想要唱给谁听？\n");

	if( !target->is_character() || target->is_corpse() )
		return notify_fail("看清楚一点，那并不是活物。\n");

	if( target->query("race") != "人类")
		return notify_fail(target->query("name") + "听不懂你的咒语！\n");

	if( (int)me->query("neili") < 5000 )
		return notify_fail("你的内力不够。\n");

	if( (int)me->query_skill("xiangfu-lun",1) < 250 )
		return notify_fail("你的降伏法功力不够！\n");

	if( (int)me->query_skill("mizong-fofa", 1) < 180 )
		return notify_fail("你的密宗心法功力不够！\n");

	if( (int)me->query_skill("longxiang-boruo", 1) < 250 )
		return notify_fail("你的龙象般若功功力不够！\n");

	if( environment(me)->query("no_fight") )
		return notify_fail("在这里不能唱。\n");

	if( target->query_temp("cursed", 1) )
		return notify_fail("此人已被降伏！\n");
	
    if ( me->query("no_pk") && userp(target) )
       return notify_fail("你已经金盆洗手，还是不要介入江湖恩怨吧。\n");

    if ( userp(me) && target->query("no_pk") )
      return notify_fail(target->name()+ "已经金盆洗手，得饶人处且饶人吧。\n");

    if ( pktime_limit(me, target) )
                return 0;
/*
    if(target->query("combat_exp")<10000000 )
                return notify_fail("死大米，一边凉快去。\n"); */         
	if( userp(me) && userp(target) ) {
                target->set_temp("other_kill/"+me->query("id"), 1);
                
                log_file("ANSUAN", 
                        sprintf("%-18s fanchan %-18s",
                                me->name(1)+"("+capitalize(getuid(me))+")",
                                target->name(1)+"("+capitalize(getuid(target))+")"
                        ),
                        this_object(),
                );
        }
                                     
	
	me->add("neili", - random(400));
	me->add("jingli",  - 250 );
	message_vision( BLU"$N摇头晃脑，击打着手中的"NOR+weapon->query("name")+BLU"，口中背诵密宗大乘佛经，夹杂以密宗六字咒。声音阴阳顿挫，有起有伏，暗含音律。\n" NOR, me);
	tell_object(target,  "你觉得那密咒比鬼哭还难听，脑袋里一团絮乱，眼前一堆鬼影在乱跳，越发感到恐惧。\n");

	ap=me->query_skill("force",1)+me->query_skill("mizong-fofa",1);
	dp=target->query_skill("force",1);
  	
	
	me->start_exert(4, "梵唱");	
	if (me->query_skill("mizong-fofa",1)<=target->query_skill("mizong-fofa",1))
			return notify_fail("你的密宗佛法不如对方深厚,无法施展梵唱！\n");
	
	//if( random(ap) > dp/2 && !target->query("no_sing") ) 
	if( random(ap) > dp  )
	//	|| random(me->query_int(1))>target->query_int(1)/2  
	{
		message_vision(HIR"$n只觉得$N的密咒夹杂着阵阵内力汹涌而至，$n顿时头晕眼花，胸气阻塞，浑身使不出劲来。\n"NOR, me, target);
		target->remove_all_killer();
		target->add_busy(3 + random(2));
		me->set_temp("curser", 1);
		me->start_busy(1 + random(3));
		curser = me->query_skill("mizong-fofa", 1) + me->query_skill("force",1)/5;
		target->add_temp("apply/attack", -curser );
		target->set_temp("cursed", curser );
		target->add_temp("apply/strength", -me->query_con()/2);
		target->set_temp("cursed_str", me->query_con()/2);

		target->set("jiali", 0);
		target->apply_condition("no_enforce", (me->query_skill("mizong-fofa")/20)
			+ 1 + target->query_condition("mizong-fofa"));

		if( (int)target->query("combat_exp") > me->query("combat_exp")/2 && userp(target) ) {
			me->improve_skill("force", me->query("int")*10);
		}
		call_out("del_sung", 15 + me->query_skill("mizong-fofa", 1)/10, me, target);
		return 1;
	} else {
		if( !stringp(force = to_chinese(target->query_skill_mapped("force"))) ) force = "内功";
		message_vision(HIY"$n潜运"+force+"，催动内力与$N念出的密咒抵抗，顿时四周的声调变的更为嘈杂，难以忍受。\n"NOR, me, target);
		me->start_busy(3+random(3));
		target->start_busy(1);
		if( !target->is_killing(me) ) target->kill_ob(me);
		return 1;
	}
}

void del_sung(object me, object target)
{
	if( !target ) return;

	if( target->query_temp("cursed") ) {
		target->add_temp("apply/attack", target->query_temp("cursed"));
		target->delete_temp("cursed");		
	}
	if( target->query_temp("cursed_str") ) {
		target->add_temp("apply/strength", target->query_temp("cursed_str"));
		target->delete_temp("cursed_str");
	}
	
	if( target->query_leader() ) target->set_leader(0);
	message_vision(YEL"嘈杂的音律渐渐消失，$n慢慢恢复了精神，不在受到$N的迷惑了。\n"NOR, me, target);
}

string exert_name(){ return HIB"梵唱"NOR; }

int help(object me)
{
        write(HIB"\n龙象般若功之「梵唱」："NOR"\n\n");
        write(@HELP
	那「龙象般若掌」共分十三层，第一层功夫十分浅易，纵是下愚之人，只要得到传授，
	一二年中即能练成。第二层比第一层加深一倍，需时三四年。第三层又比第二层加深
	一倍，需时七八年。如此成倍递增，越往后越难进展。待到第五层后，欲再练深一层，
	往往便须三十年以上苦功。金刚宗一门，高僧奇士历代辈出，但这一十三层「龙象般
	若功」，却从未有一人练到十层以上。这功夫循序渐进，本来绝无不能练成之理，若
	有人得享数千岁高龄，最终必臻第十三层境界，只人寿有限，金刚宗中的高僧修士欲
	在天年终了之前练到第七层、第八层，便非得躁进不可，这一来，往往陷入了欲速不
	达的大危境。北宋年间，吐番曾有一位高僧练到了第九层，继续勇猛精进，待练到第
	十层时，心魔骤起，无法自制，终于狂舞七日七夜，自绝经脉而死。
	梵唱是以高深龙象般若之力，发出密宗咒语，以期影响对方的行动，是重要的内功心
	法，施展后可以扰乱敌人的攻击,并且会适当降低对方的有效臂力和命中。本技能的命
	中和内功等级以及悟性有关，同门之间，密宗佛学习等级高低将直接决定彼此间斗法。	

	指令：exert fanchang

要求：
	当前内力的需求 5000 以上；
	龙象般若功等级 250 以上；
	金刚降伏轮等级 250 以上；
	密宗佛法的等级 180 以上；
	必须装备两个法轮类为兵器；
	穿着龙象袈裟。

HELP
        );
        return 1;
}
