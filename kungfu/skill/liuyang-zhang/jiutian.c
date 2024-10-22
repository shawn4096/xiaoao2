// 九天乾阳  action@SJ 2008/12/28
//modified by zhuifeng@SJFY 2010/0717

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return HIC"九天"HIR"乾阳"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lv, i, hit;
         string weapon;

        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("「九天乾阳」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「九天乾阳」！\n");   
                
        if( (int)me->query_skill("liuyang-zhang", 1) < 100 )
                return notify_fail("你的天山六阳掌还不够娴熟，使不出「九天乾阳」绝技。\n");
                
        if (me->query_skill_prepared("strike") != "liuyang-zhang"
            || me->query_skill_mapped("strike") != "liuyang-zhang")
                return notify_fail("你现在无法使用「九天乾阳」进行攻击。\n");  
/*
        if( (int)me->query_skill("bahuang-gong", 1) < 100 )
 
			if( (int)me->query_skill("beiming-shengong", 1) < 100 )
 
			return notify_fail("你的内功等级还不够，使不出「九天乾阳」绝技。\n");
            
        if (me->query_skill_mapped("force") != "bahuang-gong")
			
        if (me->query_skill_mapped("force") != "beiming-shengong")
 
			return notify_fail("你的内功有误，无法使用「九天乾阳」。\n");   */                
		            
        if( me->query("max_neili") < 1000 )
                return notify_fail("你现在内力太弱，使不出「九天乾阳」。\n"); 
                     
        if( (int)me->query("neili") < 800 )
                return notify_fail("你现在真气太弱，使不出「九天乾阳」。\n");
      
        
        lv = me->query_skill("liuyang-zhang",1);
        lv = lv /3;
        hit = (lv/50);
        if(hit > 6) hit = 6;
        if(hit <2) hit = 2;
        
        me->add_temp("apply/attack", lv*4/5);
        me->add_temp("apply/damage", lv*3/5);
        me->add_temp("apply/parry", lv);
        
		message_vision(HIB"\n$N突然大喝一声，使出逍遥派绝学「九天乾阳」,铺天盖地向$n狂袭而去！\n"NOR, me,target);

        me->set_temp("lyz_times",hit);
        me->set_temp("lyz_effect",1);
        me->add_temp("lyz/jiutian", 3);
        me->set_temp("action_flag", member_array("strike", keys(me->query_skill_prepare())));

        for( i=0; i < hit; i++ )
        {
                me->add_temp("lyz/jiutian", 1);
                COMBAT_D->do_attack(me, target, weapon, 1);
        }
      
        me->add("neili", -hit*20+20);
        me->add("jing", -hit*5);
        me->start_perform(3,"「九天乾阳」");
        me->delete_temp("lyz/jiutian");
        me->delete_temp("lyz_times");
        me->add_temp("apply/attack", -lv*4/5);
        me->add_temp("apply/damage", -lv*3/5);
        me->add_temp("apply/parry", -lv);
        return 1;
}

int help(object me)
{
        write(HIR"\n天山六阳掌之「九天乾阳」："NOR"\n");
        write(@HELP
	天山六阳掌在逍遥派武技中属于高深武学，威力巨大。
	一旦施展后，若内功为逍遥北冥神功、八荒功或小无相
	则同时可以附带生死符攻击，端的是厉害无比。逍遥派
	武功讲究轻灵飘逸，闲雅清隽，一旦施展在白衣飘飘中
	暗藏杀机。其中，天山六阳掌之「九天乾阳」绝招为逍
	遥派绝学，连续攻击数招厉害无比。
	
	指令: perform strike.jiutian

要求：  
	最大内力 1000 以上；      
	当前内力 800  以上；  
	天山六阳掌等级 100 以上；
	激发掌法为天山六阳掌；
	备掌法为天山六阳掌；
	且手无兵器；                               
HELP
        );
        return 1;
}
