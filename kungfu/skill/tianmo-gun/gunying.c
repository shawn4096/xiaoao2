//gunying.c
//棍影如山，侧重防守（反弹）和进攻
#include <ansi.h>
#include <combat.h>
//inherit SKILL;
//#include <combat_msg.h>
inherit F_SSERVER;
int remove_effect(object me,int num);

int perform(object me, object target)
{
   int lvl;
   object weapon;
   lvl = (int)me->query_skill("tianmo-gun", 1);
   
   if( !target ) target = offensive_target(me);
   if( !objectp(target)
      || !me->is_fighting(target)
      || !living(target)
      || environment(target)!=environment(me))
      return notify_fail("「棍影如山」只能在战斗中对对手使用。\n");

   if( (int)me->query_skill("tianmo-gun", 1) < 450 )
                return notify_fail("你的天魔棍还不够娴熟，使不出「棍影如山」绝技。\n");

   if (me->query_skill_mapped("force") != "tianmo-gong" 
	   && me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("你所使用的特殊内功不对。\n");  

   if(me->query_skill("xixing-dafa", 1)<450)
      if(me->query_skill("tianmo-gong", 1) < 450)
         return notify_fail("以你现在的内功修为还使不出「棍影如山」。\n");  

   if(  me->query_skill_mapped("club") != "tianmo-gun")
                return notify_fail("你现在无法使用「棍影如山」！\n");
   

   if (!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "club"
          || me->query_skill_mapped("club") != "tianmo-gun"
          || me->query_skill_mapped("parry") != "tianmo-gun")
                 return notify_fail("你手里无棍，如何使用「棍影如山」？\n");

   if( (int)me->query("max_neili") < 14000)
                return notify_fail("你的内力太弱，使不出「棍影如山」。\n");

   if( (int)me->query("neili") < 1500 )
                return notify_fail("你现在真气太弱，使不出「棍影如山」。\n");

   if( (int)me->query("jingli") < 1500 )
           return notify_fail("你现在太累了，使不出「棍影如山」。\n");
   if( me->query_temp("tmgf/gunying"))
           return notify_fail("你现在正在施展「棍影如山」。\n");

	message_vision(RED"\n$N手执"+weapon->query("name")+RED"快速转动，形成一片棍影！天魔棍法威力陡增！\n"NOR,me,target);
	
	message_vision(HIY"\n$n只觉$N棍影如山，一股庞大的压力迎面而来。\n"NOR,me,target);
    if (me->query_skill_mapped("force")=="xixing-dafa")
    {
		lvl=lvl+me->query_skill("xixing-dafa", 1)/3;
    }else if (me->query_skill_mapped("force")=="tianmo-gong")
    {
		lvl=lvl+me->query_skill("tianmo-gong", 1)/6;
    }
	if (me->query("quest/hmy/tmgf/jueji")=="pass")
	{
		lvl=lvl+me->query_skill("club",1)/4;
		message_vision(HIR"$N已经将天魔棍融会贯通，已达到返璞归真之境，信手一棍，都带有莫大威力！\n"NOR,me);
	}
	me->set_temp("tmgf/gunying",lvl);

	me->add_temp("apply/attack",lvl/4);
	me->add_temp("apply/damage",lvl/5);
	me->add_temp("apply/club",lvl/5);
	me->add_temp("apply/defense",lvl/4);
	me->add_temp("apply/parry",lvl/3);
	
        me->add("jingli", -100);
        me->add("neili", -500);
       
       // me->start_busy(1+random(2));
        
        //me->start_perform(2+ random(2),"「棍影如山」");
		call_out("remove_effect",1,me,(int)lvl/10);

        return 1;
}

int remove_effect(object me,int num)
{
	int lvl;
	
	if (!me) return 0;
	lvl=me->query_temp("tmgf/gunying");
	if (num<0
		||!me->is_fighting()
		)
	{
		me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		me->add_temp("apply/club",-lvl/5);
		me->add_temp("apply/defense",-lvl/4);
		me->add_temp("apply/parry",-lvl/3);
		me->delete_temp("tmgf/gunying");
		message_vision(RED"$N长吁一口浊气，棍法逐渐停了下来，向后一纵，渊停岳恃！\n"NOR,me);
		return 1;
	}
	num=num-2;
	call_out("remove_effect",1,me,num);
	return 1;
}

string perform_name(){ return RED"棍影如山"NOR; }

int help(object me)
{
        write(HIR"\n天魔棍之「棍影如山」："NOR"\n\n");
        write(@HELP
	天魔棍乃是日月神教十大神魔之”金猿神魔“张乘风和
	”白猴神魔“张乘云兄弟二人所创棍法，威震江湖。后
	来十长老围攻华山后下落不明，使得这门绝技从此失
	传。不过有人听说在华山后山石洞发现过天魔棍招式。
	具体情况有待于玩家自己探索。
	棍影如山乃是以慢破快的绝技，在自身形成一片棍影
	技能增加棍法的威力，同时又提高棍法的防御能力，
	并且在不经意间会随手出一棍，以拙破巧，防不胜防
	注意：解开华山石壁谜题后，此招威力彻底释放。

	指令：perform club.gunying

要求：
	最大内力需求 14000 以上；
	当前内力需求 1500  以上；
	当前精力需求 1500  以上；
	天魔棍法等级 450 以上；
	特殊内功等级 450 以上；
	基本棍法等级 450 以上；
	激发招架为天魔棍：
	激发内功为天魔功或吸星大法

HELP
        );
        return 1;
}
