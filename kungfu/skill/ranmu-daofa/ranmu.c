// ranmu.c 燃木诀
// by sohu@xojh

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object me, int count);

int perform(object me, string arg)
{
      object weapon, target;
      int i, j, z;       
      j = me->query_skill("ranmu-daofa", 1);
      weapon = me->query_temp("weapon");  
      

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
           return notify_fail("「燃木诀」只能在战斗中对对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "blade"
       || me->query_skill_mapped("blade") != "ranmu-daofa")
           return notify_fail("你现在无法使出「燃木诀」绝技！\n");

        if (weapon->query("id") != "mu dao")
           return notify_fail("你没有木刀，无法使出「燃木诀」绝技！\n");
		if (!me->query("quest/sl/rmdf/ranmu/pass"))
	       return notify_fail("你只是听说过燃木刀法，尚未融会贯通，无法使出「燃木诀」绝技！\n");

        if(me->query_skill("ranmu-daofa", 1) < 160 )
                return notify_fail("你的燃木刀法火候不够，使不出「燃木诀」绝技。\n");

        if(me->query_skill("blade", 1) < 140 )
                return notify_fail("你的基本功还不够娴熟，使不出「燃木诀」绝技。\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("你的内功等级不够，使不出「燃木诀」绝技。\n");

        if( (int)me->query_str() < 32)
                return notify_fail("你的膂力还不够强劲，使不出「燃木诀」绝技。\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("你的身法还不够迅猛，使不出「燃木诀」绝技。\n");
 
       if(me->query_skill("yijin-jing", 1) < 170 )   
                return notify_fail("你的易筋经修为不够，无法使用「燃木诀」绝技。\n");  
	   if (me->query_skill_mapped("parry")!="ranmu-daofa"&&me->query_skill_mapped("parry")!="cibei-dao")
                return notify_fail("你的招架不对，无法使用「燃木诀」绝技。\n");  
       if (me->query_temp("fumo"))
			return notify_fail("你现在正在使用「金刚伏魔」神功。\n"); 
		
       if(me->query_temp("rmdf/ranmu")) 
			return notify_fail("你现在正在使用「燃木诀」绝技。\n"); 


       if (me->query("neili") < 1000)
			return notify_fail("你的内力不够。\n");
       if (me->query("jingli") < 800)
			return notify_fail("你的精力不够。\n");
        me->add("neili", -300);
        me->add("jingli", -500);
        message_vision(HIR"$N右手执刀，左手单掌合揖，突然爆吼一声，运起佛门至上金刚伏魔功，向外连续劈出九九八十一刀！\n"
						+"在$N强大内劲支持下，手中的木刀和空气剧烈摩擦，顿时化作一团火焰，激荡的炙流将$n团团围住！\n"NOR,me,target);
        
		me->add_temp("apply/strength", j/10);
        me->add_temp("apply/attack", j/2); 
        me->add_temp("apply/damage", j/3);
        me->add_temp("apply/blade", j/4);

        me->set_temp("rmdf/ranmu", j);
        
		call_out("remove_effect", 1, me,(int)j/50);

        return 1;
}

void remove_effect(object me, int count)
{
       
    int j;
	object weapon;
	
	if (!me) return;
//	if (!me->query_temp("rmdf/ranmu")) return;
	
	j=me->query_temp("rmdf/ranmu");
	weapon=me->query_temp("weapon");

	if (count<0
		||!me->is_fighting()
		||!weapon
		|| weapon->query("id")!="mu dao"
		||me->query_skill_mapped("blade")!="ranmu-daofa")
	{
		
		me->add_temp("apply/strength", -j/10);
        me->add_temp("apply/attack", -j/2); 
        me->add_temp("apply/damage", -j/3);
        me->add_temp("apply/blade", -j/4);
		me->delete_temp("rmdf/ranmu");
		message_vision(HIR"$N缓缓将燃木刀法的「燃木」绝技收功！\n"NOR,me);
		return;
	}
	call_out("remove_effect",1,me,count--);
}

string perform_name(){ return HIR"燃木诀"NOR; }

int help(object me)
{
        write(HIY"\n燃木刀法之「燃木诀」："NOR"\n\n");
        write(@HELP
	燃木刀法乃是少林三大终极兵器之一，是刀法的集大成武技
	此招乃是少林七十二绝技中不传之秘，武功练到高深处后，
	凭借深厚内力，可以做到以掌化刀，厉害无比。此门武功由
	少林玄苦大师修习，自玄苦大师圆寂后，此武技无人修成，
	当一代高僧鸠摩智凭借小无相神功演化燃木刀法大战少林寺
	时，使得此门武技名扬天下。
	
	注意：修习手刀绝技需要身兼少林基础刀法修罗刀的杀意和
		慈悲刀的慈悲之意，在杀伐和慈悲的融合中懂得手刀的
		精髓。切记，切记！
	
	指令：perform blade.ranmu 

要求：  
	当前内力需求 1000 以上；
	最大内力需求 10000 以上；
	当前精力需求 800 以上；
	燃木刀法等级 350 以上；
	易筋经功等级 350 以上；
	基本刀法等级 350 以上；
	基本掌法等级 350 以上；	
	激发刀法为燃木刀法；
	激发招架为燃木刀法或慈悲刀；
	激发内功为易筋经神功；
	且手持木刀。

HELP
        );
        return 1;
}
