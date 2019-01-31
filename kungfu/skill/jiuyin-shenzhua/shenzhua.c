// Code of 搜狐
// Modified by sohu@xojh
//神爪 
//增加爪法威力

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill,damage;
        
		skill=me->query_skill("jiuyin-shenzhua",1);
		damage=skill+me->query_skill("daode-jing",1)+me->query_skill("jiuyin-zhengong",1);
		damage=damage*me->query_str(1)/7+random(damage);

        if (!target ) target = offensive_target(me);

        if (!target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("「九阴神爪」只能对战斗中的对手使用。\n");
		weapon=target->query_temp("weapon");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你手中拿着武器，如何使出「九阴神爪」？\n");

        if ((int)me->query_skill("jiuyin-shenzhua",1)< 450)
                return notify_fail("你的九阴神爪修为不够。\n");

        if (me->query_skill_mapped("claw")!="jiuyin-shenzhua"
			||me->query_skill_prepared("claw")!="jiuyin-shenzhua")
                return notify_fail("你尚未激发九阴神爪。\n");
        if (!me->query_skill("jiuyin-zhengong"))
                return notify_fail("你尚未学会九阴真功，无法施展这上卷的功夫。\n");
		if (!me->query_skill("daode-jing"))
                return notify_fail("你尚未学会道德经，无法施展这上卷的功夫。\n");

        if (me->query("jiali") < 50)
                return notify_fail("你的出手这么轻，又何必痛下杀手呢？\n");
        if (me->query("max_neili")<15000) return notify_fail("你的最大内力不够！\n");

        if (me->query("neili")<2000) return notify_fail("你的内力不够！\n");

        if (me->query("jingli")<=1500) return notify_fail("你的精力不够！\n");
		if (me->query_temp("jysz/shenzhua"))
			return notify_fail("你正在使用九阴神爪绝技！\n");
        
		message_vision(HBWHT+RED "\n$N猛喝一声，运气于双指，将九阴真经中"NOR+HIM"「九阴神爪」"HBWHT+RED"的功夫施展出来，手指的爪力大增，指力弥漫。\n\n" NOR, me,target);
		message_vision(HIM"这招数施展出来明显光明正大，臂力瞬间暴涨，威力强极！\n"NOR,me);
		me->add_temp("apply/claw",skill/4);
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/6);
		me->add_temp("apply/strength",skill/20);
		me->set_temp("jysz/shenzhua",skill);
		call_out("remove_shenzhua",1,me,(int)skill/30);
		
		if (random(me->query_skill("force",1))>target->query_skill("force",1)/2
		//	||random(me->query_str(1))>target->query_str(1)/2
			||random(me->query_dex(1))>target->query_dex(1)/2)
		{
			if (weapon)
			{
				message_vision(MAG"$N双爪晃动，前后左右罩住$n周身，趁$n不注意直接拿在"+weapon->query("name")+"上！\n"NOR,me,target);
				message_vision(YEL"$n一时不查，为$N抓住"+weapon->query("name")+YEL"，甩到地上！\n"NOR,me,target);
				weapon->move(environment(target));
				
			}
			else {
				message_vision(HIC"$n揉身而上，身形飘忽，点、拿、戳招式连出如花如雾！\n"NOR,me,target);
				message_vision(HIG"$n被瞬间捏住琵琶骨，顿时半身麻痹，动弹不得！\n"NOR,me,target);
				target->receive_damage("qi",damage,me);
				target->receive_wound("qi",damage,me);
				target->add_busy(3);
			}
		}
		me->add("neili",-800);
		me->add("jingli",-500);
        return 1;
}
int remove_shenzhua(object me,int count)
{
	int skill;
	if (!me) return 0;
	skill=me->query_temp("jysz/shenzhua");
	if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("claw")!="jiuyin-shenzhua"
		||me->query_skill_mapped("parry")!="jiuyin-shenzhua")
	{
		message_vision(HBWHT+MAG "\n$N长长吁了一口气，将九阴神爪功夫缓缓收功！\n\n" NOR, me);
		me->add_temp("apply/claw",-skill/4);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/6);
		me->add_temp("apply/strength",-skill/20);
		me->delete_temp("jysz/shenzhua");
		me->start_perform(3,"九阴神爪");
		return 1;
	}
	
	call_out("remove_shenzhua",1,me,count--);
}

string perform_name(){ return HBMAG+HIW"九阴神爪"NOR; }

int help(object me)
{
        write(RED"\n九阴神爪之「九阴神爪」："NOR"\n\n");
        write(@HELP
	九阴神爪乃是九阴真经上卷的功夫，为一代奇人黄裳
	所作，乃是集合天下爪法的大全和最高武技。九阴神
	爪施展后，爪法威力大增。因古墓中有重阳遗刻，所
	以古墓也有流传。
	九阴神爪在九阴真气驱使之下，力贯双指，功力大增！
	如对方有兵器有概率打掉该兵器，若没有可能将对方
	点穴并重创。

	注意：set 九阴神爪 九阴 有辅助攻击特效。
	
	指令：perform claw.shenzhua

要求：  
	当前内力的需求 2000 以上；
	最大内力的需求 15000 以上；
	当前精力的需求 1500 以上；
	九阴神爪的等级 450 以上；
	基本爪法的等级 450 以上；
	基本内功的等级 450 以上；
	激发爪法为九阴神爪；                
	备爪法为九阴神爪；
	且手无兵器；	

HELP
        );
        return 1;
}
