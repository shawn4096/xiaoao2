// 空明双绝


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
   int lvl;
  lvl = (int)me->query_skill("kongming-quan", 1)+(int)me->query_skill("xiantian-gong", 1)/2;
  
  if( !target ) target = offensive_target(me);
  if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("「空明双绝」只能在战斗中对对手使用。\n");

  if( objectp(me->query_temp("weapon")))
		return notify_fail("你必须空手才能使用「空明双绝」！\n");

   if( (int)me->query_skill("kongming-quan", 1) < 500 )
		return notify_fail("你的空明拳还不够娴熟，使不出「空明双绝」绝技。\n");

   if(me->query_skill_mapped("force")!="xiantian-gong")
        return notify_fail("空明双绝需要先天功激发，使不出「空明双绝」绝技。\n");
   if( (int)me->query_skill("parry", 1) < 500 )
           return notify_fail("你的基础技能等级还不够，使不出「空明双绝」绝技。\n");

   if( (int)me->query_skill("dodge",1) < 500 )
		return notify_fail("你的轻功等级不够，不能使用「空明双绝」。\n");
		
   if( (int)me->query_skill("xiantian-gong",1) < 500 )
		return notify_fail("你的先天功等级不够，不能使用「空明双绝」。\n");
   if( !me->query("quest/jiebai/pass")||!me->query("quest/hubo/pass"))
		return notify_fail("你并未获得周伯通传授，不能使用「空明双绝」。\n");

   if( me->query_skill_prepared("cuff") != "kongming-quan"
	 || me->query_skill_mapped("cuff") != "kongming-quan")
		return notify_fail("你现在无法使用「空明双绝」！\n");

   if( me->query_skill_mapped("parry") != "kongming-quan")
		return notify_fail("你需要激发招架为空明拳，方能使用「空明双绝」。\n");
    if(me->query_temp("kmg/shuangjue"))
	    return notify_fail("你正在使用这个绝招。\n");

   if( (int)me->query("max_neili") < 15000)
		return notify_fail("你的最大内力太弱，使不出「空明双绝」。\n");

   if( (int)me->query("neili") < 2000 )
		return notify_fail("你现在真气太弱，使不出「空明双绝」。\n");

   if( (int)me->query("jingli") < 1500 )
           return notify_fail("你现在太累了，使不出「空明双绝」。\n");


    message_vision(HIW"\n$N凝神屏气，默念口诀：“空朦洞松、风通容梦、冲穷中弄、童庸弓虫。”使出空明拳绝技「"NOR+HBCYN+HIW"空明双绝"NOR+HIW"」！\n"NOR,me);
	message_vision(HBYEL+HIW"\n\n一股阴柔劲气和阳刚之气混合在一起，相辅相成，轰向$n！\n"NOR,me,target);
  

	me->add_temp("apply/attack", lvl/2);
	me->add_temp("apply/damage", lvl/5);
	me->add_temp("apply/cuff", lvl/3);
	me->add_temp("apply/strength", lvl/10);
	
	if (me->query_temp("xtg/wuqi")) {
		me->set_temp("xtg/wuqi1",lvl);
		me->add_temp("apply/damage", lvl/5);
    }
	me->set_temp("kmq/shuangjue",1);
    
	COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, 3);


	if ( me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, 3);
 
	if ( me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, 3);
	if (wizardp(me))
	{
		write("lvl="+lvl);
	}
	me->add_temp("apply/attack",-(lvl/2));
	me->add_temp("apply/damage", -(lvl/5));
	me->add_temp("apply/cuff", -(lvl/3));
	me->add_temp("apply/strength",-(lvl/10));
   if (me->query_temp("xtg/wuqi1"))	me->add_temp("apply/damage", -(lvl/5));
   me->add("jingli", -100);
   me->add("neili", -200);
   me->delete_temp("xtg/wuqi1");
   me->start_busy(1+random(2));
   me->delete_temp("kmq/shuangjue");
   me->start_perform(5,"「空明双绝」");

   return 1;
}


string perform_name(){ return WHT"空明双绝"NOR; }

int help(object me)
{
	write(HIC"\n空明拳之「空明双绝」："NOR"\n\n");
	write(@HELP
	空明拳是天下至柔的拳术，是周伯通从《道德经》中化
	出来的，《道德经》中有言道：“兵强则灭，木强则折。
	坚强处下，柔弱处上。”又云：“天下莫柔弱于水，而攻
	坚强者莫之能胜，其无以易之。弱之胜强，柔之胜刚，
	天下莫不知，莫能行。那降龙十八掌却是武学中至刚至
	坚的拳术。空明拳之空字诀，看似是空，实际是以虚化
	实的高明口诀，阴柔无比。攻击性不强，但反击力度靠
	自身的实力。
	「空明双诀」是将空明拳融会贯通后，以阴阳两股劲气
	混杂在一起，结合老顽童独创的双手互搏绝技，威力极
	大，此招只有将先天功修炼到极致后方可施展。非全真
	弟子不传。
	
	指令; perform cuff.shuangjue

要求：
	最大内力需求 15000 以上；
	当前内力需求 2000  以上；
	当前精力需求 1500  以上；
	空明拳法等级 500 以上；
	基本轻功等级 500 以上；
	先天功法等级 500 以上；
	基本招架等级 500 以上；
	激发拳法招架为空明拳；
	备拳法为空明拳且空手。
			

HELP
	);
	return 1;
}