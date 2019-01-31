// chuanliu.c
//xjqx@sj 2008/12/30
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object me,int count);
int perform(object me, object target)
{
	object weapon;
	int skill;
	weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("你只能在战斗中使用化身万千。\n");
	if (!me->query("quest/hmy/tmd/pass"))
		return notify_fail("你只是听说过化身万千刀法，但没有受人指点，不能在战斗中使用化身万千。\n");
	if (!objectp(weapon) || (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

    if (me->query_skill_mapped("force") != "tianmo-gong" )
       if(me->query_skill_mapped("force") != "xixing-dafa")
          return notify_fail("你所使用的特殊内功不对。\n"); 

    if(!me->query_skill("xixing-dafa", 1))
       if(me->query_skill("tianmo-gong", 1) < 250)
          return notify_fail("以你现在的内功修为还使不出「化身万千」。\n");  

	if ((int)me->query_skill("blade", 1) < 250 )
		return notify_fail("你的基本刀法极不够娴熟，不能使用化身万千！\n");

	if ( me->query_skill_mapped("blade") != "tianmo-dao"
	 || me->query_skill_mapped("parry") != "tianmo-dao" )
		return notify_fail("你现在无法使用化身万千！\n");

	if ((int)me->query("neili") < 1000 )
		return notify_fail("你现在真气太弱，不能使用化身万千！\n");

	if ((int)me->query("max_neili") < 3000 )
		return notify_fail("你现在内力太弱，不能使用化身万千！\n");

	if (me->query_temp("tmd/huashen") ) 
		return notify_fail("你已经在使用化身万千了！\n");
    if (me->query_skill_mapped("force")=="tianmo-gong")
       message_vision(HIY"\n$N暗运起天魔功，将手中" + weapon->query("name")+HIY"划出多层光影，即刻威力大增，势不可挡。\n"NOR, me);
    else if (me->query_skill_mapped("force")=="xixing-dafa")
       message_vision(HIG"\n$N暗运起吸星大法，将手中" + weapon->query("name") +HIG"划出多层光影，即刻威力大增，势不可挡。\n"NOR, me);
    	
	skill = me->query_skill("tianmo-dao",1);
	
	if (me->query_skill_mapped("force")=="tianmo-gong") skill += me->query_skill("tianmo-gong",1)/8;
	if (me->query_skill_mapped("force")=="xixing-dafa") skill += me->query_skill("xixing-dafa",1)/4;
	
	
	me->add_temp("apply/attack", skill/4);
	me->add_temp("apply/damage", skill/5);
	me->add_temp("apply/parry", skill/4);
	me->add_temp("apply/dodge", skill/4);
	me->add_temp("apply/blade", skill/4);
	
	me->set_temp("tmd/huashen", skill);
    message_vision(HIR"\n$N身法急速变化，满场游走，刀影闪烁，霍霍成风，不时抽空向外劈出一刀。\n"NOR, me);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	//if ( me->query_skill("tianmo-dao", 1) > 349)
		//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    if (me->query_skill("tianmo-dao",1)<350)
    {
		me->start_perform(1, "化身万千");
	   
    }
	me->add("neili", -300);
	//if (objectp(target)&&me->is_fighting())
		call_out("remove_effect", 1, me, (int)skill/30);
	remove_effect(me,(int)skill/30);
	return 1;
}

void remove_effect(object me,int count)
{
	int skill;
	object target,weapon;
	if( !me||!me->query_temp("tmd/huashen")) return;
	skill=me->query_temp("tmd/huashen");
	weapon=me->query_temp("weapon");
	if(!me->is_fighting()
		|| count<0
		|| !me->query_temp("weapon") 
		|| me->query_skill_mapped("blade") != "tianmo-dao"
		|| me->query_skill_mapped("parry") != "tianmo-dao")
	{
		if(me->query_temp("weapon"))
			message_vision(HIY"$N身形一滞，渐渐收回弥漫的刀影，天魔刀的威力顿时散尽！\n"NOR, me);
		else message_vision(HIY"$N身形一滞，渐渐收回内功，天魔刀的威力顿时散尽！\n"NOR, me);
		me->add_temp("apply/attack", -skill/4);
		me->add_temp("apply/damage", -skill/5);
		me->add_temp("apply/parry", -skill/4);
	    me->add_temp("apply/dodge", -skill/4);
	    me->add_temp("apply/blade", -skill/4);
		me->delete_temp("tmd/huashen");
		return;
	}   
	//若有战斗对象，则触发协助攻击
	target = offensive_target(me);
    
	if (objectp(target)
		&&random(me->query("combat_exp"))>target->query("combat_exp")/2
		&&me->query_skill_prepared("strike")=="tianmo-zhang"
		&&me->query_skill_mapped("strike")=="tianmo-zhang")
    {
		message_vision(HIY"$N趁$n忽视之际，快速将刀交与左手，右手忽然施展出天魔掌绝学，迅捷无比地拍向$n的后背。\n"NOR, me, target);
		
		if (random(me->query_skill("strike",1))>target->query_skill("parry",1)/3)
		{
			message_vision(HIR"$n一不小心，被$N一掌打中后背。\n"NOR, me, target);
			target->add_busy(1+random(1));
			target->receive_damage("qi",3*skill,me);
            target->receive_wound("qi",skill,me);
			weapon->unequip(); 
			me->add_temp("apply/strike",skill/2);
			COMBAT_D->do_attack(me, target,0, 3);
            me->add_temp("apply/strike",-skill/2);
			weapon->wield();
		}
		else message_vision(HIC"$n看破了$N的企图，冷笑一声，躲了开去。\n"NOR, me, target);
    }
	//若目标存在则继续循环调用
	if (objectp(me))
		call_out("remove_effect", 1, me,count--);
	
	return;
}

string perform_name(){ return HIB"化身万千"NOR; }

int help(object me)
{
        write(HIB"\n天魔刀之「化身万千」："NOR"\n\n");
        write(@HELP
	以高超的身法优势，快速转动，演化多个化身，同时
	向对方攻击，这是天魔刀法中非常重要的辅助进攻技
	能，实施化身万千后攻防会大幅提升。
	
	指令:perform blade.huashen

要求：
	当前内力需求 1000 以上；
	最大内力需求 3000 以上；
	天魔刀的等级 250 以上；
	天魔功或吸星大法等级 250 以上；
	基本刀法等级 250 以上；
	激发刀法为天魔刀；
	激发招架为天魔刀；
	激发内功为吸星大法或天魔功；
	且手持刀类兵器，350级后小飞。

HELP
        );
        return 1;
}
