// ailao.c 哀牢山三十六剑

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i, a,skill;

        if (!target) target=offensive_target(me);

        if (!target
                || !target->is_character()
                || !me->is_fighting(target))
                return notify_fail("你不在战斗中！\n");

//      if (target->is_busy())
//              return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");
        
        weapon=me->query_temp("weapon");
        if (!objectp(weapon) || weapon->query("skill_type") != "sword")
                return notify_fail("你手中无剑，如何使得出哀牢山三十六剑？\n");

        if (me->query_skill("force", 1)<400)
                return notify_fail("你的内功火候未到，无法驾驭哀牢山三十六剑！\n");
        
        if (me->query_skill("sword", 1) < 400)
                return notify_fail("你剑法修为不够，无法施展哀牢山三十六剑！\n");
        
        if (me->query_skill("duanjia-jianfa",1)<400)
                return notify_fail("你段家剑修为不够，无法施展哀牢山三十六剑！\n");
        
        if( me->query_skill_mapped("force") != "qiantian-yiyang")
			if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("你所用的内功与哀牢山三十六剑气路相悖！\n");
        if (me->query_skill_mapped("sword") != "duanjia-jianfa"
          || me->query_skill_mapped("parry") != "duanjia-jianfa")
                return notify_fail("你激发的剑法不对，无法使用「哀牢山三十六剑」进行攻击。\n");

        if (me->query("neili") <= 1500)
                return notify_fail("你的内力不够使用哀牢山三十六剑！\n");
       if (me->query("jingli") <= 1000)
                return notify_fail("你的精力不够使用哀牢山三十六剑！\n");
        
		message_vision(HIW "\n突然间$N剑法突变，剑气纵横，上六剑，下六剑，前六剑，后六剑，左六剑，右六剑，\n"NOR, me, target);
        message_vision(HIR "\n施展「哀牢山三十六剑」，对$n虚虚实实连刺了三十六剑！\n\n" NOR, me, target);
		skill=me->query_skill("duanjia-jianfa",1);

	
		if (me->query("quest/tls/djjf/ailao/pass"))
		{
			a=7+random(4);
			if (me->query("class")!="bonze"&&me->query_temp("qtyy/yiyang")) 
				skill=skill+me->query_skill("qiantian-yiyang",1)/6;
			message_vision(HIY "\n$N乾天一阳功力布满全身，真力澎湃，和剑法融为一体，哀牢山剑意大增！\n\n" NOR, me, target);
		}else a=6;
		
		me->add_temp("apply/sword",skill/5);
		me->add_temp("apply/attack",skill/5);
		me->add_temp("apply/damage",skill/5);	
		me->set_temp("djjf/ailao",1);
        
		for (i=1; i<=a; i++)
		{		
				if (me->is_fighting()&&objectp(target))
			         COMBAT_D->do_attack(me, target, weapon,random(2)?3:1);
		}
		me->add_temp("apply/sword",-skill/5);
		me->add_temp("apply/attack",-skill/5);
		me->add_temp("apply/damage",-skill/5);
		me->delete_temp("djjf/ailao");
        me->add("neili", -200);
        me->add("jing", -20);
		me->start_perform( 5, "「哀牢山三十六剑」");
		me->start_busy(1);
        return 1;
}
string perform_name() {return HIR"哀牢山三十六剑"NOR;}

int help(object me)
{
        write(HIR"\n段家剑法之「哀牢山三十六剑」："NOR"\n\n");
        write(@HELP
	段家剑法乃是大理国皇家家传的武技，大理乃皇族，同
	时也是武林人士，除了大理一阳指绝世武功外，还有其
	他武技享誉江湖。哀牢山三十六剑乃是剑法精粹，自大
	雄关一战，段家剑法享誉江湖。解开哀牢山剑意后，招
	式会随机增加。
	
	perform sword.ailao

要求：
	当前内力需求 1500 以上；
	当前精力需求 1000 以上；
	段家剑法需求 400  级；
	基本剑法需求 400  级；
	乾天一阳需求 400  级(枯荣禅功)；
	基本内功需求 400  级；
	激发剑法为段家剑法；
	激发招架为段家剑法；
	激发内功为乾天一阳或枯荣禅功；
	且手持兵器。

HELP
        );
        return 1;
}
