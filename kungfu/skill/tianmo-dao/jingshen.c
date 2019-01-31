    // by xjqx 2008/12/30

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j = me->query_skill("tianmo-dao", 1)+me->query_skill("tianmo-zhang",1)/6;
        
		object weapon = me->query_temp("weapon");
        
		if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
               return notify_fail("惊神诀只能对战斗中的对手使用。\n");                

        if(!me->query_skill("xixing-dafa", 1) && !me->query_skill("tianmo-gong", 1))
                return notify_fail("你的内功不对，无法使用「惊神诀」。\n");  

        if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("以你现在的内功修为还使不出「惊神诀」。\n");  

        if( (int)me->query_skill("tianmo-dao", 1) < 250 )
                return notify_fail("你的刀法还未练成，不能使用惊神诀！\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "tianmo-dao")
                return notify_fail("你手里没有刀，无法使用惊神诀！\n");

        if((int)me->query_skill("tianmo-zhang", 1) < 250 )
                return notify_fail("你的天魔掌法还未练成，不能使用惊神诀！\n");  

        if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("你所使用的特殊内功不对。\n");   

        if(me->query_skill_mapped("strike") != "tianmo-zhang" 
         || me->query_skill_prepared("strike") != "tianmo-zhang")
                return notify_fail("你没有用天魔掌，无法使用惊神诀！\n");

     //   if(me->query_skill_mapped("parry") != "tianmo-zhang")
        if(me->query_skill_mapped("parry") != "tianmo-dao")
                return notify_fail("你的招架功夫不对，无法使用惊神诀！\n");

        if((int)me->query("max_neili") < 3000 )
                return notify_fail("你现在内力修为不够，不能使用惊神诀！\n");      

        if((int)me->query("neili") < 500 )
                return notify_fail("你现在内力不足，不能使用惊神诀！\n");      

        if((int)me->query_skill("blade", 1) < 250 )
                return notify_fail("你的基本刀法不够娴熟，不能在刀招中夹杂使用惊神诀。\n");

        if((int)me->query_skill("strike", 1) < 250 )
                return notify_fail("你的基本掌法不够娴熟，不能在刀招中夹杂使用惊神诀。\n");     

        message_vision(HIR"\n$N怒吼一声，使出日月神教绝技之「惊神诀」，只见漫天刀影掌影扑天盖地突袭$n而去！\n"NOR, me,target);
        me->set_temp("tmd/jingshen",1);
        me->add("neili", -400); 
        me->add("jingli", -250);
        if (!userp(me)) j=j/3;
        
        me->add_temp("apply/attack", j);
        me->add_temp("apply/damage", j/3);
        me->add_temp("apply/parry",j);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        if(objectp(target) && me->is_fighting(target))
        {
                //weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
                //weapon->wield(); 
        }
        if(objectp(target) && me->is_fighting(target) && me->query_skill("tianmo-dao",1)>120)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        if(objectp(target) && me->is_fighting(target) && me->query_skill("tianmo-dao",1)>200)
        {
                weapon->unequip(); 
				target->set_temp("must_be_hit",1); //惊神命中太低，加个一招必中，混混job吧  by renlai
				message_vision(RED"$N将手中兵器插入腰间，左掌向前一推，右掌向左一拉，招式显然有些怪异，但威力却不弱。\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
                weapon->wield();
				target->delete_temp("must_be_hit");

        }
        if(objectp(target) && me->is_fighting(target) && random((int)me->query_str()) > 30 && me->query_skill("tianmo-dao",1)>250) {
			    me->set_temp("tmd/pfm1",1);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				me->delete_temp("tmd/pfm1");

		}
        me->add_temp("apply/parry",-j);
        me->add_temp("apply/attack", -j);
        me->add_temp("apply/damage", -j/3);
        me->delete_temp("tmd/jingshen");
       // if (me->query_skill("tianmo-dao",1)<449)
     //   {
			me->start_busy(1+random(2));
         // }
		me->start_perform(3+random(2),"惊神诀");
        return 1;
}
string perform_name(){ return HIY"惊神诀"NOR; }

int help(object me)
{
        write(HIR"\n天魔刀法之「惊神诀」："NOR"\n\n");
        write(@HELP
	天魔刀乃是日月神教刀法绝技，惊神诀是将
	全身功力聚于一身，全力发动，刀刀狠辣，
	连续数招出手，打击对方，可谓惊天地泣鬼
	神，将刀法中厚重表现出来。
	
	指令：perform blade.jingshen

要求：  
	当前内力需求 500  以上；
	最大内力需求 3000 以上；
	天魔刀法等级 250 以上；
	天魔大法或吸星大法等级 250 以上；
	基本刀法等级 250 以上；
	基本内功等级 250 以上；
	基本掌法等级 250 以上；
	天魔掌法等级 250 以上；
	激发刀法为天魔刀；
	激发招架为天魔刀；
	激发掌法为天魔掌;
	激发内功为吸星大法或天魔功；
	且手持兵器,招式越是精炼，威力越是大，具体情况还待玩家自己捉摸。
	有道是熟能生巧，正是为此。
	注意：天魔刀120,200,250级后会陆续增加一招，越来越强。

HELP
        );
        return 1;
}
