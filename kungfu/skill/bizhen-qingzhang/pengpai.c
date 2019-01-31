// bizhen-qingzhang  碧针清掌 澎湃掌
//KinGSo
 
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

string perform_name() {return HBBLU HIC"澎湃掌"NOR;}

int perform(object me, object target)
{
        int lev;
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("「澎湃掌」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「澎湃掌」！\n");   

        if( (int)me->query_skill("bizhen-qingzhang", 1) < 100 )
                return notify_fail("你的掌法还不够娴熟，使不出「澎湃掌」绝技。\n");

        if((int)me->query_skill("force",1) < 160 ) 
                return notify_fail("你的内功修为还不够，使不出「澎湃掌」绝技。\n");
               

        if (me->query_skill_prepared("strike") != "bizhen-qingzhang" 
         || me->query_skill_mapped("strike") != "bizhen-qingzhang" )
                return notify_fail("你现在无法使用「澎湃掌」！\n"); 
    

        if( (int)me->query("neili") < 1000)
                return notify_fail("你现在真气太弱，使不出「澎湃掌」。\n");

        if( (int)me->query("jingli") < 1000 )
                return notify_fail("你现在精力太少，使不出「澎湃掌」。\n");
       
		

        lev = (int)me->query_skill("bizhen-qingzhang", 1); 
        
        message_vision(HBBLU HIC"\n$N鼓荡掌风，双掌挥舞出一个大圈，「澎湃掌」横推而出，顿时一股汹涌澎湃掌的劲气如波浪一般向$n涌来！\n"NOR,me,target);
        me->add_temp("apply/damage", lev/6);
        me->add_temp("apply/attack", lev/6);       

		me->set_temp("bzqz/pengpai",1);
        COMBAT_D->do_attack(me, target, 0, 3);
	    if( me->is_fighting(target))
		 COMBAT_D->do_attack(me, target, 0, 3);
       
        if( me->is_fighting(target)
			&& (int)me->query_skill("bizhen-qingzhang",1) > 120 ) 
		{
            if((int)me->query_skill("bizhen-qingzhang",1)>=250 )
                    COMBAT_D->do_attack(me, target, 0, 3);
            else
                    COMBAT_D->do_attack(me, target, 0, 1);
            
        }
        if( me->is_fighting(target) 
			&& (int)me->query_skill("bizhen-qingzhang",1) > 159 )
		{
            if((int)me->query_skill("bizhen-qingzhang",1)>=250 )
         		COMBAT_D->do_attack(me, target, 0, 3);
	        else	COMBAT_D->do_attack(me, target, 0, 1);
            
        }
        
        me->add_temp("apply/damage", -lev/6);
        me->add_temp("apply/attack", -lev/6);
        me->add("neili", -500);
        me->add("jingli", -200);
		me->delete_temp("bzqz/pengpai");
        me->start_perform(5,"「澎湃掌」");
        return 1;
}

int help(object me)
{
   write(HIC"\n碧针清掌「"HBBLU HIC"澎湃掌"HIC"」："NOR"\n\n");
   write(@HELP
	碧针清掌是摩天居士谢烟客独门绝技，一旦施展
	周围方圆一丈内皆为劲气笼罩，可谓澎湃劲气汹
	涌如潮，极其厉害。
	
	指令：perform strike.pengpai

要求: 
	当前内力 1000 以上；
	当前精力 1000 以上；
	碧针清掌等级 400 以上；
    基本内功等级 400 以上；
	激发掌法为碧针清掌；
	内功不限；
	空手，备碧针清掌。

HELP
   );
   return 1;
}

