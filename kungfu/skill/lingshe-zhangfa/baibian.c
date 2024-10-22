// baibian.c 灵蛇百变
// by fengyue
#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIC"灵蛇百变"NOR;}

int perform(object me, object target)
{
        int lvl;
        object weapon = me->query_temp("weapon");
        lvl =  (int)me->query_skill("lingshe-zhangfa", 1) + (int)me->query_skill("lingshe-quanfa", 1) + (int)me->query_skill("hamagong", 1) ;
        lvl=lvl/3;
        if( !target ) target = offensive_target(me);
     
        if( !target || !me->is_fighting(target) )
                return notify_fail("「灵蛇百变」只能在战斗中对对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "lingshe-zhangfa")
                return notify_fail("你没有使用灵蛇杖法，无法发挥出「灵蛇百变」的威力！\n");             

        if( (int)me->query_skill("lingshe-zhangfa",1) < 300 )
                return notify_fail("你的灵蛇杖法不够娴熟，不能使用「灵蛇百变」！\n");
      
        if( (int)me->query_skill("staff",1) < 300 )
                return notify_fail("你的基本拳法等级不够，不能使用「灵蛇百变」！\n");  

        if( (int)me->query_skill("lingshe-quanfa", 1) < 300 )
                return notify_fail("你的灵蛇拳法等级不够，不能使用「灵蛇百变」！\n");
      
        if( (int)me->query_skill("hamagong", 1) < 300 )
                return notify_fail("你的蛤蟆功等级不够，不能使用「灵蛇百变」！\n");

        if( (int)me->query("max_neili") < 5000 )
                return notify_fail("你的内力太弱，不能使用「灵蛇百变」！\n");
      
        if( (int)me->query("neili") < 2000 )
                return notify_fail("你的内力太少了，无法使用出「灵蛇百变」！\n");   
                                                                                 
        if (me->query_skill_prepared("cuff") != "lingshe-quanfa"
          || me->query_skill_mapped("cuff") != "lingshe-quanfa"
          || me->query_skill_mapped("force") != "hamagong")
                return notify_fail("你现在无法使用「灵蛇百变」进行攻击。\n");


         message_vision(HIC"\n$N右手蛇杖忽缩,，左手手臂随势而弯,出拳的方位匪夷所思，宛然灵动如蛇，正是一招“灵蛇百变”！\n"NOR, me);


         if(  target->query("family/family_name") == "丐帮"  && me->query("oyf/hamagong") == 2
          && random( me->query("combat_exp")/ 100 * me->query_int(1)) < target->query("combat_exp")/100 * target->query_int(1) / 2)
         {
          message_vision(HIC"\n谁知道$n平生抓蛇无数，勾腕伸爪，疾以擒拿手拿$N拳头，这一下恰到好处，又快又准，正是克制“灵蛇拳法”的巧妙法！\n"NOR, me,target);
          me->start_busy(1+random(2));
          return 1;
          }
          else{

        me->add("neili", -(300+random(100))); 
        me->add("jingli", -100);      
        me->add_temp("apply/cuff", lvl/4);
        me->add_temp("apply/attack", lvl/3);
        me->add_temp("apply/damage", lvl /4);
        me->set_temp("lszf/bb",1);
        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        weapon->wield();
        
        if(me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        if(me->is_fighting(target)){ 
              weapon->unequip();
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
              weapon->wield();
                          }
        if(me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        if(me->is_fighting(target)){ 
              weapon->unequip();
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
              weapon->wield();
                           }

       message_vision(HIC"\n$N余势未了，突然长身往前疾扑，左臂伸了两伸，已将$n左足踝上三寸的“悬钟穴”、右足内踝上七寸的“中都穴”先后点中！\n"NOR, me,target);
       target->add_busy( random(3) + 2);
 
       if( me->query("oyf/hamagong")>2 && me->is_fighting(target) ) {
                       if(random(2)) target->apply_condition("no_exert",2);
                       if(random(2)) target->apply_condition("no_fight",2);
                       target->apply_condition("no_perform",4);
					   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                       if(me->is_fighting(target))
                          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                                                    }
        me->start_busy(1);
        me->add_temp("apply/cuff", -lvl/4);
        me->add_temp("apply/attack", -lvl/3);
        me->add_temp("apply/damage", - lvl /4 );
        me->delete_temp("lszf/bb");
    	me->start_perform(5 , "「灵蛇百变」");
        return 1;
    }

}
int help(object me)
{
        write(HIC"\n灵蛇杖法之"+HIC"「灵蛇百变」"NOR"\n\n");
        write(@HELP
	灵蛇杖法乃是白驼山武学精髓所在，欧阳锋一生以驱蛇和蛤蟆功名扬江湖，凭借此两
	大神技得意获得五绝称呼，并创立白驼山一脉武学。白驼山武学以狠辣、阴险、剧毒
	诡异为特色。灵蛇百变是欧阳锋在长期训练蛇、养蛇过程中观看蛇之变化所创立的招
	式，讲究的变化万千，灵动异常。
	
	要求：当前内力 2000  以上；
		当前精力 1000  以上；
		最大内力 5000 以上；
		基本杖法等级 300 以上；\
		蛤蟆功的等级 300 以上；
		灵蛇杖法等级 300 以上；
		激发拳法为灵蛇拳法；
		激发招架为灵蛇杖法。

HELP
        );
        return 1;
}
