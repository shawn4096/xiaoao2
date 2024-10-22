// huanying.c
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int skill;
	if( !target ) target = offensive_target(me);

	if(!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("「幻影」只能在战斗中对对手使用。\n");

	if((int)me->query_skill("force", 1) < 100 )
		return notify_fail("你的基本内功等级不够，不能呼唤幻影。\n");       

	

	if((int)me->query_skill("yanxing-daofa", 1) < 150 )
		return notify_fail("你的雁行刀法等级不够，不能呼唤鬼魂！\n");    

	if((int)me->query_skill("blade", 1) < 150 )
		return notify_fail("你的基本刀法极不够娴熟，不能呼唤出你的幻影！\n");    

	if( me->query_skill_mapped("blade") != "yanxing-daofa"
	 || me->query_skill_mapped("parry") != "yanxing-daofa")
		return notify_fail("你现在无法呼唤出幻影进行攻击！\n"); 

	if((int)me->query("neili") < 700 )
		return notify_fail("你现在真气太弱，不能呼唤幻影！\n");

	if((int)me->query("max_neili") < 2000 )
		return notify_fail("你现在内力太弱，不能呼唤幻影！\n");

	if ((int)me->query_temp("幻影", 1) ) 
		return notify_fail("你已经呼唤出了自己的幻影！\n");
    
	message_vision(HIY"\n$N前后游走，身形闪动，手中钢刀越使越快，幻起无数刀光化出数个身形。\n"+
			"$n被此雁行刀法之「无形幻影」所迷惑，手足无措，不知哪个$N是真，哪个是假。\n\n"NOR, me, target);

	if (me->query_skill("yanxing-daofa")<350)
	{	
		me->start_busy(1+random(1));
		}
	me->add("neili", -200);    
	skill = me->query_skill("yanxing-daofa", 1)/3;
	me->set_temp("幻影", 1);
	me->set_temp("huanying",skill);
	//俗世男人有威力
	if (me->query("gender")!="男性" || me->query("class")!="bonze"||!me->query("quest/em/yxdf/jueji/pass"))
		me->start_perform(1+random(3), "「无形幻影」");
	me->add_temp("apply/attack",skill);
	me->add_temp("apply/damage",skill/2);
	call_out("remove_effect", 1, me, skill);
	return 1;
}

void remove_effect(object me,int count)
{
	int skill;
	object weapon;
	if (!me) return;
	weapon=me->query_temp("weapon");

	skill=me->query_temp("huanying");
	if(!me->is_fighting()
	 || me->query_skill_mapped("blade") != "yanxing-daofa"
	 || !weapon
	 || weapon->query("skill_type")!="blade"
	 || count < 1){
		message_vision("那个"HIY"幻影"NOR"于半空徘徊了一阵，就消失在地底了！\n", me);
		me->delete_temp("幻影");
		me->add_temp("apply/attack",-skill);
	    me->add_temp("apply/damage",-skill/2);
		me->delete_temp("huanying");
		return;
	}
	else {
		call_out("remove_effect", 1, me, count -1);
	}
}

string perform_name(){ return HIC"无形幻影"NOR; }

int help(object me)
{
        write(HIC"\n雁行刀法之「无形幻影」："NOR"\n\n");
        write(@HELP
	雁行刀法乃是峨眉俗家弟子武技，可以向孤鸿子
	学习习得。刀法需要和临济庄配合使用，「飞雁
	随风刃」的奥秘就在于忽然将武器抛向空中，吸
	引对手的注意力，对手若经验不丰富，则会上当
	受骗，峨眉弟子只需施展峨眉另一门绝技，【四
	象掌】就会打向对方的胸口，造成伤害。
	注意：俗家男子解开孤鸿子谜题后，此招飞跃
	
	指令：perform blade.huanying

要求：  
	当前内力需求 700 以上；
	最大内力需求 2000 以上；
	雁行刀法等级 150 以上；
	基本内功等级 150 以上；
	基本刀法等级 150 以上；
	激发刀法为雁行刀法；
	激发招架为雁行刀法；
	激发内功不限；
	且手持兵器,350后小飞。

HELP
        );
        return 1;
}
