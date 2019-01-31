// feihua.c 雨打飞花
// cre by sohu@xojh 2014
// 根据金庸描述改编
// 剑招忽变，歪歪斜斜的使出一套“雨打飞花”剑法来。这一路剑走的全是斜势，飘逸无伦，但七八招斜势之中，偶尔又挟着一招正势，
#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return HIG"雨打飞花"NOR; }


int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time, lvl;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                 return notify_fail("「雨打飞花」只能对战斗中的对手使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if((int)me->query_skill("liangyi-jian",1) < 450 )
				return notify_fail("你的两仪剑法还不够火候，使不出「雨打飞花」。\n");
        if((int)me->query_skill("xuantian-wuji",1) < 450 )
                return notify_fail("你的玄天无级功还不够火候，使不出「雨打飞花」。\n");
        if( me->query_skill_mapped("sword") != "liangyi-jian"
			|| me->query_skill_mapped("parry") != "liangyi-jian" )
                return notify_fail("你现在没激发两仪剑，无法使用这个绝招！\n");
        if((string)me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("你不用玄天无级内功支持是无法使用这个绝招的！\n");
        
        if(me->query_temp("lyj/feihua") )
                return notify_fail("你现在已经在向对手使用了「雨打飞花」。\n");
      
        if( me->query("jingli", 1) < 1000 )
                return notify_fail("你的当前精力修为不够使用「雨打飞花」！\n");
        if( me->query_dex( ) < 60 )
				return notify_fail("你的后天身法修为不够使用「雨打飞花」！\n");
        if((int)me->query("neili")<1500)
                return notify_fail("你的真气不够！\n"); 
        attack_time = random((int)me->query_skill("liangyi-jian",1) / 25)+1;
       
		if(attack_time < 3)
               attack_time = 3;
        if(attack_time > 7)  attack_time = 7;
        
		msg = HIY "$N手中"+weapon->name()+HIY"剑招忽变，歪歪斜斜的使出一套「雨打飞花」剑法来。这一路剑走的全是斜势，\n"+
			"\n飘逸无伦，但七八招斜势之中，偶尔又挟着一招正势，摇摆如荷，摇曳如花！\n"NOR;
     
		
		message_vision(msg, me, target);
        lvl = ((me->query_skill("liangyi-jian", 1) + me->query_skill("xuantian-wuji", 1)))/ 6;
        lvl=lvl/3;

		me->set_temp("lyj/feihua", lvl);
        me->add_temp("apply/dexerity", lvl);
        me->add_temp("apply/damage", lvl);
        me->add_temp("apply/attack", lvl);
        me->add_temp("apply/sword", lvl/2);

		for(i = 0; i < 2; i++)
			if (me->is_fighting()&&objectp(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
		//第四招正招
		if (me->is_fighting()&&objectp(target))
		{
			    me->set_temp("lyj/feihua1",1);
				me->add_temp("apply/damage",lvl/4);
				if (userp(target))
					target->add_busy(1);
				else target->add_busy(4);
				message_vision(HBWHT+HIY"$N忽然使出一招两仪剑正招，极其突兀，$n一时不查，顿时有些手忙脚乱！\n"NOR,me,target);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->delete_temp("lyj/feihua1");
				me->add_temp("apply/damage",-lvl/4);
		}
		//第五招 歪斜招		
		if (me->is_fighting()&&objectp(target))				
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);	
		//第六招 歪斜招	
		if (me->is_fighting()&&objectp(target))				
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);						
		//第七招 正招
		if (me->is_fighting()&&objectp(target))
		{
			    me->set_temp("lyj/feihua1",1);
				me->add_temp("apply/damage",lvl/4);
				me->add_temp("apply/sword",lvl/4);
				message_vision(HIR"$N招式互变为两仪剑正招，$n一时不查，为$N刺中手腕！\n"NOR,me,target);
				target->receive_damage("qi",4000+random(3000),me);
				if (me->query("quest/kl/lyj/feihua/pass")
					&& me->query_skill_mapped("sword")=="liangyi-jian")
				{
					message_vision(HBRED+HIW"$N一剑刺实了后，剑势蓄积的后劲发动，剑尖连点三下，瞬间挑断了$n的寸关穴、曲池穴、劳宫穴！\n"NOR,me,target);
					message_vision(RED"$n手腕酸软，顿时受制，无法正常出招！\n"NOR,me,target);

					target->receive_damage("qi",random(5000),me);
					target->receive_wound("qi",random(2000),me);
					target->add_busy(2);
					target->apply_condition("no_enable",2);
				}
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->delete_temp("lyj/feihua1");
				me->add_temp("apply/damage",-lvl/4);
				me->add_temp("apply/sword",-lvl/4);
		}
		//第八招
	//	if (me->is_fighting()&& objectp(target))				
	//			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);						

		me->add_temp("apply/damage", -lvl);
        me->add_temp("apply/attack", -lvl);
        me->add_temp("apply/dexerity", -lvl);
		me->add_temp("apply/sword", -lvl/2);

		me->delete_temp("lyj/feihua");

        me->add("neili", -300);
        me->add("jingli", -80);
	
		message_vision(HIY"$N的攻势渐渐慢了下来，缓过劲来松了口气。\n"NOR,me);		
		me->start_perform(6,"「雨打飞花」");
		me->add_busy(1);
        return 1;
}

int help(object me)
{
    write(WHT"\n两仪剑法「"HIG"雨打飞花"WHT"」："NOR"\n");
    write(@HELP
	两仪剑法乃是昆仑派绝技，当初昆仑三圣何足道以此
	剑法横扫西域诸雄。后来在少林大战中一战成名，凭
	借的就是此剑法。两仪剑乃是正宗的正两仪剑法，剑
	法轻灵迅捷，不以力胜，但却将剑法灵动多变发挥到
	倘若身法轻功好，则两仪剑法的威力更上一层楼。
	雨打飞花乃是两仪剑中比较特殊的剑法，剑法全走斜
	势，但七八招斜势之中，偶尔又挟着一招正势，令敌
	人难以捉摸。解开长老谜题后，此招飞跃。

	指令：perform sword.feihua
	
要求：
	玄天无极等级 450 级以上；
	两仪剑法等级 450 级以上；
	有效身法等级 60    以上；
	基本剑法等级 300 级以上，
	最大内力要求 5000 以上，
	当前内力要求 1000 以上，
	当前精力要求 1000 以上，
	需手持剑类武器。    

HELP
	);
	return 1;
}
