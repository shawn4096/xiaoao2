//yingyang.c 鹰扬三击
//cre by sohu@xojh 

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return HIR"鹰扬三击"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lv,lvf;
		object weapon=me->query_temp("weapon");

        if( !target ) target = offensive_target(me);
        
		if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("鹰爪手「鹰扬三击」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「鹰扬三击」！\n");   
        if( (int)me->query_skill("yingzhua-shou", 1) < 250 )
                return notify_fail("你的鹰爪手还不够娴熟，使不出「鹰扬三击」绝技。\n");
        if (me->query_skill_prepared("hand") != "yingzhua-shou"
        || me->query_skill_mapped("hand") != "yingzhua-shou")
                return notify_fail("你现在无法使用「鹰扬三击」进行攻击。\n");  

	    if( me->query_skill_mapped("force") != "shenghuo-shengong" )
		        return notify_fail("你现在使用的内功，不能使用「鹰扬三击」。\n");
        if( (int)me->query_skill("shenghuo-shengong", 1) < 250 )
                return notify_fail("你的圣火神功等级还不够，使不出「鹰扬三击」绝技。\n");
       
        if( me->query("max_neili") < 3500 )
                return notify_fail("你现在内力太弱，使不出「鹰扬三击」。\n");      
        if( (int)me->query("neili") <1500 )
                return notify_fail("你现在真气太弱，使不出「鹰扬三击」。\n");
      
        
        lv = me->query_skill("yingzhua-shou",1);
		lvf=me->query_skill("shenghuo-shengong",1)/8;
     
        if (me->query("mj/quest/yzs"))
        {
			//message_vision(HIC"$N想起鹰王的指点，灵光一动，将圣火神功劲气运于爪中，招式更见犀利！\n"NOR,me,target);
			lv += lvf;
        }
		//lv += lvf;
		
		if (target->is_busy() && me->query_skill_mapped("force")=="shenghuo-shengong")
		{
			message_vision(HIC"$N见$n正处于忙乱之中，自顾不暇，圣火神功运于爪中，鹰爪手威力顿时增加不少。\n"NOR,me,target);
			lv+=lv/8;
		}
        me->add_temp("apply/attack", lv/3);
		me->add_temp("apply/hand", lv/3);
        me->add_temp("apply/damage", lv/5);
       // me->add_temp("apply/parry", -lv/5);
        message_vision(HIR"\n$N突然间大喝一声，纵身而上，身形在空中翱翔飞纵，双手挥舞左右盘旋，施展出「鹰扬三击」绝技瞬间向$n攻出三招厉害杀招。 \n"NOR,me,target);
     
   
        me->set_temp("yzs/yingyang", 3);
		
      
        COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
        COMBAT_D->do_attack(me, target, 0, 3);
		COMBAT_D->do_attack(me, target, 0, 3);
		if (me->query("mj/quest/yzs") && me->query_temp("mj/shenghuo"))
		{
			target->add_busy(1);
			message_vision(HIC"$N想起鹰王的指点，灵光一动，将圣火神功劲气运于爪中，招式更见犀利！\n"NOR,me,target);
			COMBAT_D->do_attack(me, target,0, 3);

		}      
       
        me->add_temp("apply/attack", -lv/3);
		me->add_temp("apply/hand", -lv/3);
        me->add_temp("apply/damage", -lv/5);
		
		me->start_perform(4,"「鹰扬三击」");
        me->start_busy(1+random(2));
        me->delete_temp("yzs/yingyang");
      
        return 1;
}


int help(object me)
{
        write(HIY"\n鹰爪手之「鹰扬三击」："NOR"\n");
        write(@HELP
	鹰爪手绝技，是明教护教法白眉鹰王殷天正的成名绝技，
	是将擒拿格斗与近身搏击术融合在一起的绝技。在双方
	对战过程中，既可以通过贴身擒拿术，点中对方的穴道，
	又可以通过绝杀技一招致敌。
	
	指令:perform hand.yingyang

要求：
	最大内力 3500 以上；      
	当前内力 1500  以上；  
	鹰爪手等级 250 以上；
	圣火神功等级 250 以上；
	激发爪法为鹰爪手；
	激发招架为鹰爪手；
	且手无兵器；
                
HELP
        );
        return 1;
}


