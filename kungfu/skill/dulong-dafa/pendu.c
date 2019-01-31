//pendu.c 
//cre by sohu@xojh


#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_SSERVER;

string exert_name() {return HBBLU+HIW"喷毒"NOR;}

int exert(object me, object target)
{
        int skill,i;
		object yaocao;
		string poi;
		if( !target ) target = offensive_target(me);

	 
		if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
        	return notify_fail("「喷毒绝技」只能对战斗中的对手使用。\n");
        if((int)me->query_skill("dulong-dafa",1) < 200  )
                return notify_fail("你的毒龙大法功力不够，无法使用「喷毒绝技」。\n");
		 if((int)me->query_skill("force",1) < 200  )
                return notify_fail("你的基本内功功力不够，无法使用「喷毒绝技」。\n");
		if((int)me->query_skill("medicine",1) < 100  )
                return notify_fail("你的本草术理不够，无法使用「喷毒绝技」。\n");
		if((int)me->query_skill("poison",1) < 150  )
                return notify_fail("你的毒计不够，无法使用「喷毒绝技」。\n");
        if((int)me->query_skill("shenlong-yaoli",1) < 180  )
                return notify_fail("你对神龙药理学的领悟尚缺，无法使用「喷毒绝技」。\n");
		//if( target = me)
				//return notify_fail("你不能对自己使用「喷毒绝技」。\n");
        if((int)me->query("neili") < 500
         || (int)me->query("max_neili")< 2500  )
                return notify_fail("你的内力不够。\n");

		if (!userp(target))
		{
			i=3;
		}
		else i=2;

		if (!me->query("quest/sld/dldf/pendu/pass"))
		{
			if (!objectp(yaocao=present("yao cao",me)) || yaocao->query("local")!="sld")
				return notify_fail("你身上没有神龙岛特有药草，无法使用喷毒。\n");
       // skill= (me->query_skill("dulong-dafa",1)/2 + me->query_skill("shenlong-yaoli",1))*14+ me->query_skill("medicine",1))*14;     
       
			message_vision(HIB"\n$N从背囊中摸出一把不知名的草药，快速咀嚼几口，然后运起毒龙大法，将口中的草药猛然间喷向$n。\n\n"NOR,me,target);
			yaocao->add("amount",-1);
			if ((int)yaocao->query("amount")<1)
			{
				message_vision(HIY"这一株药草快要用完了,你三下五除二将它塞入口中。\n"NOR,me);
				destruct(yaocao);
			}

		}else {
			message_vision(HBGRN+HIW"\n$N施展毒龙大法逆转之法，将身上蓄积的毒性化作一口毒气，猛然间喷向$n面庞。\n\n"NOR,me,target);
			i=3;
		}
	   // message_vision(HIb"\n$n满头大汗，用劲将身体内的毒素逼出体外。\n\n"NOR, me);
	
		if (random(me->query("neili"))>target->query("neili")/i
			||random(me->query("combat_exp"))>target->query("combat_exp")/i)
		{
			message_vision(HIB"\n$n只觉得一股腥臭无比的烟气向自己罩来，一阵窒息，心中却意识到自己已经中毒了。\n\n"NOR,me,target);
			poi==(string)me->query("env/喷毒");
			if (poi)
			{
					switch (poi)
					{
						case "蛇毒":
							target->add_condition("snake_poison",i);break;
						case "千里香":
							target->add_condition("qianli_poison",i);break;
						case "七虫七花膏":
							target->add_condition("7bug_poison",i);break;
						case "腐骨毒":
							target->add_condition("fugu_poison",i);break;
					}
			}else {
					switch (random(6))
					{
						case 0:
							target->add_condition("snake_poison",i);break;
						case 1:
							target->add_condition("qianli_poison",i);break;
						case 2:
							target->add_condition("7bug_poison",i);break;
						case 3:
							target->add_condition("fugu_poison",i);break;
						case 4:
							target->add_condition("snake_poison",i);break;
						case 5:
							target->add_condition("snake_poison",i);break;
				
					}	
			}			

		}else {
			message_vision(HIC"\n$n急忙运功将这股烟气阻隔在三尺之外。\n\n"NOR,me,target);
			target->add("neili",-random(1000));
			me->add_busy(1);
		}
			
        me->add("neili",-300);
		me->add("neili",-400);
		me->start_exert(3,"「喷毒」");
        return 1;
}

int help(object me)
{
        write(WHT"\n毒龙大法之"+HBBLU+HIW"「喷毒」"WHT"：\n\n"NOR);
        write(@HELP
	毒龙大法乃是神龙岛内功绝技，乃是开山祖师
	洪教主根据门派独特心法所创立。既有其蛇毒
	的特性，又有其强悍的一面。
	「喷毒」绝技乃是利用深厚的内功心法和独特
	的神龙药理知识相结合，对中了神龙岛一脉的
	各种毒素通过强大内力喷出体外，影响对方。
	若药植术较高且解开喷毒谜题，则威力大增。
	注意；set 喷毒 xx
		xx包括蛇毒、千里香、七虫七花膏、腐骨毒
	若不设定则随机喷毒。
	
	使用指令：yun pendu
		
要求：
	当前内力要求 500 以上；
	最大内力要求 2500 以上；
	基本内功等级 200  以上；
	毒龙大法等级 200 以上；
	本草术理等级 100 以上；
	神龙药理等级 180 以上；
	毒计技能需求 150 以上；
	激发内功为毒龙大法；
	
HELP
        );
        return 1;
}


