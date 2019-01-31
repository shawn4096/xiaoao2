//shenwei.c
//Created by Redhat@Sjmud 2009/4/7
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

string perform_name(){ return HIR"神威枪"NOR; }
int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「神威枪」只能对战斗中的对手使用。\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "spear" )
                return notify_fail("你手中无枪，怎能运用「神威枪」？！\n");

        if( me->query_temp("yjq/shenwei"))
                return notify_fail("你正在使用「神威枪」绝技！\n");
                
        if( me->query_temp("yjq/qinghe"))
                return notify_fail("你正在使用「骤雨清荷」绝技！\n");
                
        if( me->query_temp("yjq/jifeng"))
                return notify_fail("你正在使用「疾风枪」绝技！\n");

        if((int)me->query_skill("yangjia-qiang", 1) < 350
         ||(int)me->query_skill("spear", 1) < 350)
                return notify_fail("你修为还不够，还未能领悟「神威枪」！\n");

        if (me->query_skill_mapped("spear") != "yangjia-qiang")
        // || me->query_skill_mapped("parry") != "yangjia-qiang"
                return notify_fail("你现在无法使用「神威枪」进行攻击。\n");

        if( me->query("max_neili") <= 6000 )
                return notify_fail("你的内力修为不足，不足以施展「神威枪」！\n");

        if( me->query("neili") <= 2000 )
                return notify_fail("你的内力不够，不足以施展「神威枪」！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力有限，不足以施展「神威枪」！\n");
                
        if( (int)me->query_str() < 65 )
		            return notify_fail("你的先天臂力不足，估计无法使出「神威枪」绝技。\n");

        message_vision(HIM"\n$N大喝一声，突然间怒发冲冠，枪花乱抖，使出杨家枪绝技之「神威枪」，只见"+weapon->name()+HIM"上隐约环绕着红色光芒，宛如"HIR"火焰枪"HIM"一般！\n" NOR, me);

        if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
        }
        skill = me->query_skill("spear",1);
      	improve = skill;
      	//if ( improve > 100 ) improve = improve+me->query("PKS");

        me->set_temp("yjq/shenwei", improve);
        me->add_temp("apply/damage", improve);
        me->add_temp("apply/spear", improve);
        me->add_temp("apply/strength", improve/10 );
        call_out("remove_effect", 2,  me, weapon, skill);
       // if (me->query_skill("yangjia-qiang",1)<500)
       //      me->start_perform(2,"「神威枪」");
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(! me->is_fighting()
         || !weapon
         || me->query_skill_mapped("spear") != "yangjia-qiang"
         || me->query_skill_mapped("parry") != "yangjia-qiang"
         || count < 1 ){
          i = me->query_temp("yjq/shenwei");
          me->add_temp("apply/spear", -i);
          me->add_temp("apply/damage", -i);
          me->add_temp("apply/strength", -i/10 );
          me->delete_temp("yjq/shenwei");
	      if (weapon)
		     message_vision(HIW"\n$N一套「神威枪」使完，手中"NOR+weapon->name()+HIY"上的红色光芒逐渐消失了。\n"NOR, me);
          return;
        }
        else {
          //if (me->query_skill("yangjia-qiang",1)<500)
            // me->start_perform(1,"「神威枪」");
          call_out("remove_effect", 1, me, weapon, count -1);
        }
}
int help(object me)
{
	write(HIY"\n杨家枪之「神威枪」："NOR"\n");
	write(@HELP
	杨家枪乃是传自北宋年间杨家将的枪法，无论马上还是
	马下都极为实战，其中神威枪是将一身精气神和杀气融
	入到枪法之中，杀人数越多，此招威力越强。能在短时
	内将枪法的威力大幅提升。

	指令：perform spear.shenwei

要求：	
	当前内力需求 2000 以上；
	当前精力需求 1000 以上；
	最大内力需求 6000 以上；
	杨家枪法等级 350  以上；
	有效臂力等级 65   以上；
	激发枪法为杨家枪；	
HELP
	);
	return 1;
}



