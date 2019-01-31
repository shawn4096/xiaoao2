#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg,dodge_skill;
	int p, ap, dp,lvl,damage,skill;
    weapon=me->query_temp("weapon");  
	if( !target ) target = offensive_target(me);

	if(!objectp(weapon = me->query_temp("weapon"))
	 ||(string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("「飞雁随风刃」只能在战斗中对对手使用。\n");

	if((int)me->query_skill("force", 1) < 350 )
		return notify_fail("你的基本内功等级不够，不能使用飞雁随风刃。\n");       

	if(me->query_skill_prepared("strike") != "sixiang-zhang"
	 || me->query_skill_mapped("strike") != "sixiang-zhang")
		return notify_fail("你不会四象掌，现在无法使用飞雁随风刃。\n");

	

	if ((int)me->query_skill("yanxing-daofa", 1) < 350 )
		return notify_fail("你的雁行刀法等级不够，不能使用飞雁随风刃！\n");    

	if( me->query_skill_mapped("blade") != "yanxing-daofa"
	 || me->query_skill_mapped("parry") != "yanxing-daofa")
		return notify_fail("你现在不能使用飞雁随风刃！\n"); 

	if ((int)me->query_skill("blade", 1) < 350 )
		return notify_fail("你的基本刀法不够娴熟，不能使用飞雁随风刃！\n");    

	if ((int)me->query_skill("sixiang-zhang", 1) < 350 )
		return notify_fail("你的四象掌不够娴熟，不能使用飞雁随风刃！\n");    

	if ((int)me->query_skill("strike", 1) < 350 )
		return notify_fail("你的基本掌法不够娴熟，不能使用飞雁随风刃！\n");    

	if ((int)me->query("neili") < 2500 )
		return notify_fail("你现在真气太弱，不能使用飞雁随风刃！\n");

	if ((int)me->query("jingli") < 1500 )
		return notify_fail("你现在精力不够，不能使用飞雁随风刃！\n");

	if ((int)me->query("max_neili") < 5000 )
		return notify_fail("你现在内力太弱，不能使用飞雁随风刃！\n");

	message_vision(HIY"$N突然把手中"+weapon->query("name")+HIY"往上一扔！\n"NOR, me, target);
	//瞬间提高身法
	me->add_temp("apply/dexerity", me->query_skill("dodge",1)/20);
	
	ap = me->query("combat_exp")/1000 * me->query_skill("strike",1);
	dp = target->query("combat_exp")/1000* target->query_skill("parry",1);
   
	if (me->query_skill("yanxing-daofa",1)<350)
       lvl=me->query_skill("yanxing-daofa",1)+me->query_skill("linji-zhuang",1)/4;
	else lvl=me->query_skill("yanxing-daofa",1)+me->query_skill("linji-zhuang",1)/2;
	damage=lvl;
	//俗家有优势
	
	if (me->query_skill("jiuyin-zhengong",1)>150)
	{
		message_vision(HIB"$N默念九阴真经要诀，飞雁随风刃的威力随之增强！\n"NOR,me);
		lvl=lvl+me->query_skill("jiuyin-zhengong",1)/2;
		
	}
	if (me->query("class")!="bonze")
	{
		damage+=lvl;
	}
	me->add_temp("apply/attack",lvl/2);
	me->add_temp("apply/strike",lvl/5);
	me->add_temp("apply/damage",lvl/10);
	me->add_temp("apply/blade",lvl/5);
	
	if (me->query_skill("jiuyin-zhengong",1))
	{
		skill=me->query_skill("yanxing-daofa",1)+me->query_skill("blade",1)/4+me->query_skill("jiuyin-zhengong",1);
		damage+=skill;
		
	}
	message_vision(HIR"$N看$n一怔，立刻运使出一招四象掌的绝学“飘雪穿云掌”！\n"NOR, me, target);

	if (random( ap + dp) > dp )
	{
		
	 	message_vision(HIY"$n一时疏忽，被$N重重的击中胸口！\n"NOR, me, target); 
		target->receive_damage("qi", damage*3,me);
		target->receive_wound("qi", damage,me);
		target->add_busy(1);
        if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ me->query_skill("sixiang-zhang", 1) * 3+ WHT"点攻击伤害。\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+me->query_skill("sixiang-zhang", 1) * 3+ WHT"点伤害。\n"NOR);
		p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");
		msg = "( $n"+COMBAT_D->eff_status_msg(p)+" )\n"; 
		message( msg, me, target);
		COMBAT_D->report_status(target, userp(me)?3:1);
        //me->add_temp("apply/attack",damage);	
        
    if (me->is_fighting(target))
		{
		 weapon->unequip(); 
         me->add_temp("apply/strike", lvl/3);
		 me->add_temp("apply/attack", lvl/6);
		 me->add_temp("apply/damage", lvl/6);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
         me->add_temp("apply/strike", -lvl/3);
		 me->add_temp("apply/attack", -lvl/6);
		 me->add_temp("apply/damage", -lvl/6);
		 weapon->wield();
		}
		
	}
	else{
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		message( msg, me, target);
	}
	message_vision(HIR"\n$N以暗影浮香之技纵起，接了空中落下来的刀，唰唰连劈三刀！\n"NOR, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	
	me->add_temp("apply/dexerity",-me->query_skill("dodge",1)/20);
	
	me->add_temp("apply/attack",-lvl/2);
	me->add_temp("apply/strike",-lvl/5);
	me->add_temp("apply/damage",-lvl/10);
	me->add_temp("apply/blade",-lvl/5);
	me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jinli", -100);
	me->start_perform(3+random(2), "「飞雁随风刃」");       
	return 1;

}
string perform_name(){ return HIG"飞雁随风刃"NOR; }

int help(object me)
{
        write(HIG"\n雁行刀法之「飞雁随风刃」："NOR"\n\n");
        write(@HELP
	雁行刀法乃是峨眉俗家弟子武技，可以向孤鸿子
	学习习得。因雁行刀乃俗家弟子使用，刀法无需
	和临济庄配合使用，也是一门不俗的武技。
	「飞雁随风刃」的奥秘就在于忽然将武器抛向空
	中，吸引对手的注意力，对手若经验不丰富，则
	会上当受骗，峨眉弟子只需施展峨眉另一门绝技
	【四象掌】就会打向对方的胸口，造成伤害。开
	了峨眉九阴后，威力增加。
	
	指令：perform blade.feiyan
        
要求：  
	当前内力需求 2500 以上；
	最大内力需求 5000 以上；
	当前精力需求 1500 以上；
	雁行刀法等级 350 以上；
	四象掌法等级 350 以上；
	基本内功等级 350 以上；
	基本刀法等级 350 以上；
	基本掌法等级 350 以上；
	激发刀法为雁行刀法；
	激发招架为雁行刀法；
	激发掌法为四象掌；
	备掌法为四象掌；
	激发内功不限；
	且手持刀类兵器。

HELP
        );
        return 1;
}
