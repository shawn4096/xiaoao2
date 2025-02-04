#include <ansi.h>

int exercising(object me);
int halt_exercise(object me);

int exert(object me, mixed arg)
{
	if(!arg)
		return notify_fail("格式：exert shenyou <id> \n"); 

	if(objectp(arg))
		return notify_fail("你要找的人就在一旁，还「神游」干什么？\n"); 

	if(!stringp(arg))
		return notify_fail("你要「神游」什么？\n"); 
	//限制洗手id神游玩家
	if (me->query("no_pk"))
		return notify_fail("你已经金盆洗手，还是不要介入江湖争斗吧！\n");

	if( arg == me->query("id"))
		return notify_fail("「神游」自己？你不是走火如魔了吧？\n"); 

	if( (int)me->query_skill("longxiang-boruo",1) < 180 )
		return notify_fail("你的龙象般若功根基不稳，无法运用「神游」！\n"); 

	if ( environment(me)->query("no_death") || environment(me)->query("no_fight"))
		return notify_fail("这里不适合你神游。\n");

	if( (int)me->query_skill("mizong-fofa",1) < 180 )
		return notify_fail("你的密宗佛法不够，无法运用「神游」！\n");    

	if( me->is_fighting() )
		return notify_fail("「神游」只能在安静的环境中使用。\n");

	if( (int)me->query("neili") < 2000 || (int)me->query("max_neili")<3000  ) 
		return notify_fail("你的内力不够。\n");

	if( (int)me->query_temp("mz_shenyou") ) 
		return notify_fail("你已经在运功神游中了。\n");

	if( me->query("jing") < me->query("eff_jing"))	
		return notify_fail("你精神不凝，如何能「神游」？\n");  

	if( me->query("jingli") < 1000)
		return notify_fail("你目前精力衰竭，恐怕无法「神游」。\n");

	if( me->query_int(1) < 40)
		return notify_fail("只有大智大慧之人才能通晓「神游」，看样子你是不行的了。\n");
	  
	me->add("neili", -2000);

	message_vision(HIY"\n$N盘膝闭目，按照莲花生传播的佛教咒术和密法修练「神游」大法，\n"+
		"其能点石成金，起死回生，或骑上光线，上升飞天。。。\n\n" NOR, me);

	me->set_temp("mz_shenyou", 1);
	me->set_temp("period", 1);
	me->set_temp("person", arg);
	me->start_busy((: exercising :), (:halt_exercise:));
	return 1;
}

int exercising(object me)
{
	object npc, target;
	string arg;
	int period = (int)me->query_temp("period");
	 
	me->receive_damage("jing", 5+random(5));
	me->receive_damage("jingli", 5+random(5));

	if(!living(me)) return 0;
	if(me->query("jing") < 1 || me->query("jingli") < 1){
		me->delete_temp("mz_shenyou");
		me->delete_temp("period");
		me->delete_temp("person");
		me->delete_temp("shenyou_npc");
		me->unconcious();
		return 0;
	}
	if(!me->query_temp("person")){
		halt_exercise(me);
		return 0;
	}
	if(period < 0 && period > -6){
		me->set_temp("period", period-1);
		return 1;
	}
	if(period <= -6){
		write("\n你缓缓站起身来，只觉得全身虚脱，十分疲惫。\n\n");
		tell_room(environment(me), me->name()+"长长呼出一口秽气，缓缓站了起来。\n\n", ({ me }));
		me->set("jing", 1);
		me->set("jingli", 1);
		me->delete_temp("period");
		me->delete_temp("person");
		me->delete_temp("mz_shenyou");
		me->start_busy(2);
		return 0;
	}
	if(me->query("jing") <= 80 || me->query("jingli") <= 80){
		write(HIY"\n渐渐地，你的思感又回转回来，一丝轻微的声音传来，身体也开始有了感觉。\n\n"NOR);
		npc = me->query_temp("shenyou_npc");
		if(objectp(npc))
			npc->do_remove();
		me->delete_temp("shenyou_npc");
		me->add("potential", 1+random(5));
		me->set_temp("period", -1);
		return 1;
	}
	switch(period) {
		case 2:
			write("\n你全身放松，缓缓将呼吸内缄，清除脑中杂念。\n\n");
			break;
		case 6:
			write("\n不一会儿，你觉得自己的神志越来越清醒，而身体也越来越轻了。\n\n");
			break;
		case 9:
			write(HIY"\n渐渐地，你发现你看见了自己盘膝坐在那里，好似形神已经分开了似的。\n\n"NOR);
			break;
		case 12:
			write(HIC"\n你发现自己的神志越伸越远，于瞬时间已经跨过了高山大海，游荡于真空之中！\n\n"NOR);
			me->improve_skill("force", 1);
			break;
		case 16:
			arg = me->query_temp("person");
			if ((target = LOGIN_D->find_body(arg)) && me->visible(target)){
				write(HIW"\n你的思感伸张开去，只一刹那，便来到"+target->name()+HIW"的身边！\n\n"NOR);
				if (wizardp(target)) {
					tell_object(me, MAG"\n你猛然发现，那人竟是忽隐忽现，好似一名漂浮在半空的神！\n"+
							"而且还回过头来，瞪了你一眼！你感到大事不妙，连忙退了回来。\n\n"NOR);
					halt_exercise(me);
				}
				else {
					npc = new(__DIR__"shenyou_npc");
					npc->do_setup(me, target);
					me->set_temp("shenyou_npc", npc);
				}
			}
			else {
				write(HIW"\n你的思感伸张开去，但灵光一闪，竟发现找不到那人！\n\n"NOR);
				halt_exercise(me);
			}
			break;
	}
	period++;
	me->set_temp("period", period);
	return 1; 
}

int halt_exercise(object me)
{
	object npc;
	if ( !me->query_temp("period"))
		return 1;
	me->delete_temp("mz_shenyou");
	me->delete_temp("period");
	me->delete_temp("person");
	me->receive_damage("jing", 200);
	me->receive_damage("jingli", 200);
	me->add("max_neili",-20-random(20));
	npc = me->query_temp("shenyou_npc");
	if(objectp(npc))
		npc->do_remove();
	write("你心头一震，冷汗直下，再不能继续「神游」大法，只好睁眼站起。\n");
	tell_room(environment(me), me->name()+"全身一阵抖动，头上汗如雨下，呼的一声站了起来。\n", ({ me }));
	me->start_busy(1+random(5));
	return 1;
}

string exert_name(){ return HIY"神游"NOR; }

int help(object me)
{
	write(HIY"\n龙象般若功之「神游」："NOR"\n\n");
	write(@HELP
	要求：	当前内力 2000 以上；
		最大内力 3000 以上；
		当前精力 1000 以上；
		欢喜禅等级 180 以上；
		龙象般若功等级 180 以上；
		后天悟性 40 以上。

HELP
        );
        return 1;
}
