//1999.2.26 by Snowman
// modify by athoi@sj 2004.06.11 for 因为精血表示内伤 所以改为恢复精血而非气血
// modify by server 增加set 效果，选择性恢复,recover jing 消耗内力是recover qi 的5 倍
// By Spiderii@ty 增加先天天赋技能效果
#include <ansi.h>

int exercising(object me);
int halt_exercise(object me);

int exert(object me)
{
	string force;
	mapping msg;
	
	if( me->is_fighting() )
		return notify_fail("战斗中运功疗伤？找死吗？\n");
	if (userp(me) && me->query_skill("medicine", 1) < 30)
		return notify_fail("你对本草术理的研究还不够，不能疗伤。\n");   
	if(!(force = me->query_skill_mapped("force")))
		return notify_fail("你还没有选择你要使用的内功。\n");
	if(me->query_skill("force",1) < 50)
		return notify_fail("你的内功等级还太低，不能运功疗伤。\n");
	if(me->query("env/heal") && me->query("env/heal") != "jing")
		return notify_fail("你还没有选择你要恢复的设定。\n");
	if (me->query("max_neili") < 200)
		return notify_fail("你的内力修为不够。\n");
	if (me->query("neili") < 50)
		return notify_fail("你的真气不够。\n");
	if (me->query_condition("liuxue")&&me->query_skill("medicine",1)>=80)
	{
		message_vision(HIC"$N盘膝而坐，利用自己深厚内功结合草木术知识点了自己几处穴道，将流血止住。\n"NOR,me);
		me->clear_condition("liuxue");
		me->add("neili",-50);
		me->add_busy(1);
	}
	if (me->query_condition("dgjj_poqi")&&me->query_skill("medicine",1)>=80)
	{
		message_vision(HIM"$N盘膝而坐，运起深厚内功，结合自己所学本草术理的知识将自己丹田部位封住，治好丹田伤势。\n"NOR,me);
		me->clear_condition("dgjj_poqi");
		me->add("neili",-250);
		me->add_busy(3+random(3));
	}
	if (!me->query("env/heal") && me->query("eff_qi") >= me->query("max_qi"))
		return notify_fail("你并没有受伤！\n");
	if (me->query("env/heal") == "jing" && me->query("eff_jing") >= me->query("max_jing"))
		return notify_fail("你并没有受伤！\n");
	if (!me->query("env/heal") && me->query("eff_qi") < me->query("max_qi") / 4 || me->query("env/heal") == "jing"&& me->query("eff_jing") < me->query("max_jing") / 4)
		return notify_fail("你已经受伤过重，经受不起真气震荡！\n");
	
      	msg = SKILL_D(force)->exercise_msg(me);
      	if (!msg || undefinedp(msg["heal_msg"]))
	   	message_vision(HIW"$N盘膝坐下，开始运功疗伤。\n"NOR,me);
      	else 
      		message_vision(msg["heal_msg"],me);
     
      	me->set_temp("pending/heal", 1);
      	me->set_temp("period", 1);
      	me->start_busy((: exercising :), (:halt_exercise:));
      	return 1;
}

int exercising(object me)
{
	int period = me->query_temp("period");
	int skill = (me->query_skill("jingmai-xue", 1) + me->query_skill("medicine", 1)) / 2;
	string force;
	mapping msg;
	
	if (!userp(me) && !skill) 
		skill = 100;
	if (!living(me) || !(force = me->query_skill_mapped("force")) || !skill) 
	{
		me->delete_temp("pending/heal");
		me->delete_temp("period");
		return 0;
	}

	msg = SKILL_D(force)->exercise_msg(me);
	skill = (skill+random(skill))/4;
	skill += me->query_skill(force)/10;
	skill += random(me->query_con()/4);
	
	if( !me->query("env/heal") && me->query("eff_qi") >= me->query("max_qi"))
	{
		if (me->query("max_qi")>=50000) tell_object(me,HIC"你因为内功深厚，气息悠长，因此恢复起来迅捷非常！\n"NOR);
		tell_object(me, "良久，你感觉通过自己的内息运行，身上的伤势已经全好了。\n");
		if (!msg || undefinedp(msg["heal_finish_msg"]))
			message_vision(HIW"$N运功完毕，站起身来，看上去气色饱满，精神抖擞。\n"NOR,me);
		else 
			message_vision(msg["heal_finish_msg"],me);
		me->delete_temp("pending/heal");
		me->delete_temp("period");
		return 0;
	}
		if( me->query("env/heal") == "jing"&& me->query("eff_jing") >= me->query("max_jing"))
	{
		tell_object(me, "良久，你感觉通过自己的内息运行，身上的伤势已经全好了。\n");
		if (!msg || undefinedp(msg["heal_finish_msg"]))
			message_vision(HIW"$N运功完毕，站起身来，看上去气色饱满，精神抖擞。\n"NOR,me);
		else 
			message_vision(msg["heal_finish_msg"],me);
		me->delete_temp("pending/heal");
		me->delete_temp("period");
		return 0;
	}
	if( me->query("neili") < 50 )
	{
		tell_object(me, "你正在运功疗伤，却发现自己所剩的内力不够了。\n");
		if(me->query("eff_qi") < me->query("max_qi") || me->query("eff_jing") < me->query("max_jing"))
			tell_object(me, HIY"你呼出一口气站了起来，可惜伤势还没有完全恢复。\n"NOR);
		if (!msg || undefinedp(msg["heal_unfinish_msg"]))
			message_vision(HIY"$N运功完毕，缓缓站了起来，脸色看起来好了许多。\n"NOR,me);
		else 
			message_vision(msg["heal_unfinish_msg"],me);
		me->delete_temp("pending/heal");
		me->delete_temp("period");
		return 0;
	}
                  
       //天赋“绝世筋骨”影响效果：  by spiderii@ty
                   if((int)me->query("relife/recover/jsjg",1) > 0){
                       skill += (int)me->query("relife/recover/jsjg",1) * skill * 8 / 100;
                       tell_object(me,HIC"你因为转世重修，周身经脉比以往拓宽了数倍，因此恢复起来迅捷非常！\n"NOR);
                       me->receive_curing("qi",skill);
                       me->receive_curing("jing",skill);
                   }
        if (me->query("env/heal") == "jing" && me->receive_curing("jing", skill))
        me->receive_damage("neili", 50 * 5);//恢复精注重内力修为,提高内力消耗
        
		//这里提高高exp的速度 by renlai
		if (me->query("max_qi")<50000)
		{
	    	if (!me->query("env/heal") && me->receive_curing("qi", skill))
            me->receive_damage("neili", 50);
		}
		else
		{
			//加速，但是也更消耗内力			
			if (!me->query("env/heal") && me->receive_curing("qi", skill*3))
            me->receive_damage("neili", 200);
		}

	switch(period) 
	{
		case 5:
		case 100:
		case 150:
			tell_object(me, "你双手互握，气凝丹田，不停地催动内息疗伤。\n");
			break;
		case 10:
		case 40:
		case 80:
		case 110:
		case 160:
			message_vision("$N开口吐出一口瘀血，脸色看起来好了一点。\n",me);
			break;
		case 20:
		case 120:
		case 170:
			tell_object(me, "你将双掌掌心相对，内息顺势缓缓运转，通行于全身伤脉。\n");
			me->improve_skill("jingmai-xue", 1);
			break;
		case 30:
		case 130:
		case 180:
			tell_object(me, "你真气在体内转三转，呕出两口瘀血，稍去了点胸口闭塞之气。\n");
			me->improve_skill("force", 1);
			break;
		case 60:
		case 90:
		case 140:
		case 190:
			message_vision("$N打坐运气，调息了大半个时辰，精神为之一振。\n", me);
			break;
		case 50:
		case 70:
		case 200:
			tell_object(me, "你体内真气逐步贯通，四肢渐渐开始复有力气了。\n\n");
			me->improve_skill("medicine", 1);
			break;
	}
	me->add_temp("period", random(skill)+1);
	return 1; 
}

int halt_exercise(object me)
{
	string force;
	mapping msg;
	
	force = me->query_skill_mapped("force");
	if (force) 
		msg = SKILL_D(force)->exercise_msg(me);
	me->delete_temp("pending/heal");
	me->delete_temp("period");
	me->receive_damage("jing", 50);
	me->receive_damage("jingli", 50);
	tell_object(me, "你心头一动，急忙吐气纳息，硬生生将内息压了下去。\n");
	if (!msg || undefinedp(msg["heal_halt_msg"]))
		message_vision("$N一震，吐出一口瘀血，缓缓站了起来。\n", me);
	else    
		message_vision(msg["heal_halt_msg"], me);    
	me->start_busy(1+random(5));
	return 1;
}
