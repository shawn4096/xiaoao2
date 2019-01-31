//by snowyu
//updated by lara 2001/12/07
//五罗轻烟掌
/*
   段正淳不答，站起身来，忽地左掌向后斜劈，飕的一声轻响，身后一枝红烛随
掌风而灭，跟着右掌向后斜劈，又是一枝红烛陡然熄灭，如此连出五掌，劈熄了五
枝红烛，眼光始终向前，出掌却如行云流水，潇洒之极。
木婉清惊道：“这……这是‘五罗轻烟掌’，你怎样么也会？”
*/
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	string weapon;
	int strike, force, amount; 
	strike = me->query_skill("strike",1);
	force  = me->query_skill("force",1);
	amount = (strike+force)/4;
	
    if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("五罗轻烟只能对战斗中的对手使用。\n");
	
	if ( me->query_temp("weapon") )
                return notify_fail("五罗轻烟必须空手方可施展。\n");

   // if( me->query_temp("piaomiao") ) 
			//	return notify_fail(HIW "你正在使用云烟飘渺！\n"); 
	
  	if( me->query_skill_mapped("strike") != "qingyan-zhang" )
                return notify_fail("你所用并非五罗轻烟掌!");

	if( me->query_skill_prepared("strike") != "qingyan-zhang" )
                return notify_fail("你所备并非五罗轻烟掌!");
          
    //if( me->query_skill_prepared("cuff") != "jinyu-quan" )
      //          return notify_fail("五罗轻烟需和金玉拳配合使用!");

	if( me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("你所用内功心法不对,无法施展五罗轻烟！\n");

	if( me->query_skill("kurong-changong",1) < 350 &&
            me->query_skill("qiantian-yiyang",1) < 350)
				return notify_fail("你的内功修为不够，无法施展五罗轻烟！\n");
	if( me->query_skill("strike",1) < 350 )
				return notify_fail("你基本掌法功力不够，无法施展五罗轻烟！\n");
	if( me->query_skill("qingyan-zhang",1) < 350 )
				return notify_fail("你五罗轻烟掌功力不够，无法施展五罗轻烟！\n");
		
	if (me->query("dali/betrayer")>=1)
				return notify_fail("你已叛出大理，还好意思使用大理绝学！\n");   
	
	//if (!me->query("can_perform/qingyan-zhang/qingyan") )
	  //      return notify_fail("你未经段正淳指点，不会使用五罗轻烟！！\n");
	   
	if( (int)me->query("max_neili") <15000)
				return notify_fail("你的内力修为不足，无法施展五罗轻烟！\n");
	        
	if( me->query("neili") < 1500 )
				return notify_fail("你的内力不够使用五罗轻烟！\n");

    if( me->query("jingli") <1000 )
				return notify_fail("你的精力不够使用五罗轻烟！\n");
    if( me->query_temp("qyz/qingyan") )
				return notify_fail("你正在使用五罗轻烟！\n");  
               

    message_vision(MAG "$N突然间纵身越起，忽地左掌向后斜劈，跟着右掌向后斜劈，瞬间向$n连劈五掌,出掌却如行云流水，潇洒之极!\n\n" NOR, me, target);
    message_vision(YEL "这五掌带起五股若隐若现的轻烟，将$n包裹起来，正是五罗轻烟掌中的"HIM"「五罗轻烟」"YEL"绝技!\n\n" NOR, me, target);

	if (userp(target))
    {
		amount = amount/2; 
    }   
        
	me->add_temp("apply/damage", amount/3); //降低一半伤害
	me->add_temp("apply/attack", amount); //降低一半攻击
	me->set_temp("qyz/qingyan",5);	
   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
    if (me->is_fighting()&&objectp(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
    if (me->is_fighting()&&objectp(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
    if (me->is_fighting()&&objectp(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
    if (me->is_fighting()&&objectp(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		
        me->add("neili", - amount+random(80));
        me->add("jingli",-amount+random(40));

	me->start_busy(1 + random(2));

    me->add_temp("apply/damage", -amount/3);
	me->add_temp("apply/attack", -amount);
	me->start_perform(4,"五罗轻烟");
	me->delete_temp("qyz/qingyan");	
	return 1;
}
string perform_name() {return BLU"五罗轻烟"NOR;}

int help(object me)
{
        write(BLU"\n五罗轻烟掌之「五罗轻烟」："NOR"\n\n");
        write(@HELP
	五罗轻烟掌乃是大理段氏绝技，当初段正淳以五罗轻烟掌
	不仅名震江湖，而且传给自己的情人。其状若轻烟，看似
	风轻云淡，实则将雄浑的内力夹杂在掌法中发出。令人防
	不胜防。
	
指令；perform strike.qingyan

要求：
	当前内力 1000  以上；
	最大内力 15000 以上；
	当前精力 1000  以上；
	基本掌法 350   级；
	五罗轻烟 350   级；
	乾天一阳 350   级；
	激发掌法为五罗轻烟掌；
	激发招架为五罗轻烟掌；
	备掌法为五罗轻烟掌；
	且空手。

HELP
        );
        return 1;
}
