
//wuhu.c  跟王语嫣请教
//cre by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
string perform_name() {return HBRED+HIY"五虎绝刀"NOR;}


int perform(object me, object target)
{
    int lvl;
	object weapon,tweapon;

    lvl = me->query_skill("wuhu-duanmendao", 1);
    
	if( !target ) target = offensive_target(me);
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))                
        return notify_fail("你只能对战斗中的对手使用五虎绝刀。\n");
    
	if( (int)me->query_skill("wuhu-duanmendao", 1) < 350 )
        return notify_fail("你的五虎断门刀不够娴熟，无法施展出五虎绝刀。\n");
    if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "blade") 
                return notify_fail("你手上无刀如何能使出「五虎绝刀」？\n");
    tweapon=target->query_temp("weapon");
	if (me->query_skill_mapped("blade") != "wuhu-duanmendao")
        // || me->query_skill_mapped("parry") != "wuhu-duanmendao")
         return notify_fail("你现在无法使用「五虎绝刀」！\n");  

    if ( (int)me->query("max_neili") < 5000)
        return notify_fail("你的内力不够，无法施展出五虎绝刀。\n");
    if ( (int)me->query("neili") < 1000)
        return notify_fail("你的真气不够，无法施展出五虎绝刀。\n");
    if ((int)me->query("jingli") < 1000)
        return notify_fail("你的精气不够，无法施展出五虎绝刀。\n");
    if (!me->query("quest/whdmd/wuhu/pass"))
        return notify_fail("你尚未领悟这招绝技，需向王语嫣请教，才能施展出五虎绝刀。\n");

    me->add("neili", -(300 +random(100)) );
    me->add("jingli", -150);
    
    
    me->add_temp("apply/attack",lvl/5);
  //  me->add_temp("apply/strength",lvl/20);
	me->add_temp("apply/damage",lvl/5);
	me->add_temp("apply/blade",lvl/4);
	
	message_vision(HIR"$N施展五虎断门刀终极绝技，「白虎跳涧」「一啸风生」「剪扑自如」「雄霸群山」「伏象胜狮」五招连出\n"
						+"这五招刀法乃是失传的绝学，现在融会贯通后，断门刀的威力陡然剧增！\n"NOR,me,target);
	
	me->set_temp("whdmd/wuhu",4);
	if (objectp(target)&&me->is_fighting())
    {
		target->receive_damage("qi",1000,me);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add_temp("whdmd/wuhu",-1);
    }
	if (objectp(target)&&me->is_fighting())
    {
		//target->receive_damage("jingli",1000,me);
		target->add_busy(2);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("whdmd/wuhu",-1);
    }
	if (objectp(target)&&me->is_fighting())
    {
		//target->receive_damage("qi",2000,me);
		
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("whdmd/wuhu",-1);
    }
	if (objectp(target)&&me->is_fighting()&& lvl>400)
    {
		//target->receive_damage("jingli",2000,me);
		//target->apply_condition("no_exert",1);
		
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		message_vision(CYN"$N这招「"HIR"雄霸群山"CYN"」施展出来，刀势陡然大盛！\n"NOR,me,target);
		me->add_temp("whdmd/wuhu",-1);
    }
	if (objectp(target)&&me->is_fighting()&& lvl>450)
    {
		//target->receive_damage("jingli",1000,me);
		//target->apply_condition("no_perform",1);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("whdmd/wuhu",-1);
    }
	me->add_temp("apply/attack",-lvl/5);
    //me->add_temp("apply/strength",-lvl/20);
	me->add_temp("apply/damage",-lvl/5);
	me->add_temp("apply/blade",-lvl/4);

	me->start_busy(2);
	me->start_perform(5,"「五虎绝刀」");
    return 1;
}

int help(object me)
{
        write(HIC"\n五虎断门刀之"HIY"「五虎绝刀」："NOR"\n\n");
        write(@HELP
	五虎断门刀为云州秦家寨绝学，乃数十年前的其中一任寨主秦公望自创。
	全套刀法本来共有六十四招，后来秦家后人忘了“白虎跳涧”、“一啸风生”
	“剪扑自如”、“雄霸群山”，“伏象胜狮”五招，只有五十九招流传下来。后
	流传至秦家寨现任当家姚伯当的师父这一辈时，又有“负子渡河”和“重节
	守义”两招失传，只剩下五十七招。姚伯当为顾全颜面，将“负子渡河”和
	“重节守义”两个变招稍加改动，补足了五十九招之数，但在以此门刀法与
	青城派掌门司马林交手时仍被王语嫣窥破。
	注意：该招需向王语嫣请教方可习得,400,450级后招式出全。
	
	指令：perform blade.wuhu

 要求：
	当前内力 1000 以上；
	最大内力 5000 以上；
	当前精力 1000 以上；
	五虎断门刀等级 350 以上；
	需基本刀法等级 350 以上；
	激发招架为五虎断门刀；
                

HELP
        );
        return 1;
}

