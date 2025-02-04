// wushuai.c 天人五衰
// Rewrite By lsxk@hsbbs 2007/5/16

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
#include "wushuai.h";
string perform_name(){ return HBRED"天人五衰"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i,j,lev,jiali;
   

    if( !target ) target = offensive_target(me);
     
    if( !userp(me) && userp(target) )
                return notify_fail("「天人五衰」只能由玩家使用。\n");

    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「天人五衰」只能对战斗中的对手使用。\n");

    if(me->query_skill_mapped("force") != "longxiang-boruo")
                return notify_fail("你的内功不是龙象波若功，无法使用「天人五衰」！\n");

    if( (int)me->query_skill("longxiang-boruo", 1) < 450 )
                return notify_fail("你的龙象波若功等级不够，无法使用「天人五衰」！\n");

    if( (int)me->query_skill("xiangfu-lun", 1) < 450 ) 
                return notify_fail("你的金刚降伏轮还未练成，无法使用「天人五衰」！\n");

    if((int)me->query_skill("hammer", 1) < 450 )
                return notify_fail("你的基本锤法不够娴熟，不能使用「天人五衰」！\n");

    if (!objectp(weapon = me->query_temp("weapon")) || (weapon->query("skill_type") != "hammer" && weapon->query("skill_type") != "lun")
        || me->query_skill_mapped("hammer") != "xiangfu-lun")
                return notify_fail("你必须使用锤法，才能使出「天人五衰」!\n");
                
    if((int)me->query_str() < 70)
           return notify_fail("你的膂力还不够强劲，使不出「天人五衰」绝技。\n");

    if(me->query_skill_mapped("parry") != "xiangfu-lun")
           return notify_fail("「天人五衰」需要使用降伏轮法招架一切敌方攻击。\n"); 

    if((int)me->query("max_neili") < 9000 )
           return notify_fail("你内力修为尚浅，使不出「天人五衰」。\n");  

    if( (int)me->query("neili") < 1000 )
           return notify_fail("你现在真气太弱，使不出「天人五衰」。\n");
	if( (int)me->query("jingli") < 1000 )
           return notify_fail("你现在精力太弱，使不出「天人五衰」。\n");

        message_vision(HBRED"\n只听“呜-呜-”之声大作，$N将手中法轮旋转连环，使出「天人五衰」绝技，奋力掷出！\n"NOR, me,target);

    lev = (int)me->query_skill("xiangfu-lun",1)/4;

    if( me->query_temp("xs/longxiang") ) 
	{
           message_vision(MAG"$N更把龙象内劲附于兵刃之上，"+weapon->query("name")+MAG"通体流淌着异样的紫色光芒！\n\n"NOR, me,target);
           lev *= 2;
    }

        me->start_perform(5,"「天人五衰」");
        me->add("neili", -300);
        me->set_temp("xfl/wushuai", 1);
        jiali = ((int)me->query("str",1)/2 + (int)me->query("con",1))/2 + random((int)me->query("jiali")/20 );
        me->add_temp("apply/damage",  lev);
        me->add_temp("apply/attack", lev*2);
        me->add_temp("apply/strength", jiali);
        for (i=0;i<5;i++)
		{
          j = i;
          if (i<1) j = 1;
          if (i>1) j = 3;
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"),j);
          me->add("neili", -200);
        }

        me->add_temp("apply/damage",  -lev);
        me->add_temp("apply/strength", -jiali);
        me->add_temp("apply/attack", -lev*2);

        me->delete_temp("xfl/wushuai");
        target->add_busy(1);
    return 1;
}

int help(object me)
{
        write(HIR"\n金刚降伏轮之「天人五衰」："NOR"\n");
        write(@HELP
	当年密宗金轮法王横扫西域，威镇草原，一手藏密金刚降伏轮
	使得出神入画！此「天人五衰」绝技乃法王得意之作，全由龙
	象之力以御气操作，法轮飞舞旋转，如飞龙降世，金刚开山！
	当世可挡之人寥寥无几！一招既出，招招连环。
	天人五衰乃是金轮法王当世不传之秘，将手中轮子飞出去连环
	进攻敌人，不死不休。

	指令;perform hammer.wushuai

要求：
	降伏轮法等级 450 级，
	基本锤法等级 450 级，
	龙象般若等级 450 级，
	最大内力需求 9000 以上，
	当前内力需求 1000 以上，
	当前精力需求 1000 以上，
	后天臂力要求 70 以上
	激发招架为降伏轮
	激发锤法为降伏轮
	激发内功为龙象般若
注意：
	金轮法王一生功力唯有龙象波若功和降伏轮，因此龙象功力越
	深，降伏轮威力越大，龙象般若和降伏轮的契合度极高，乃是
	金轮法王纵横西域、外蒙和中原的重要武技,	若巧妙设置
	【set 锁】会有意想不到的效果出现。
HELP
        );
        return 1;
}

