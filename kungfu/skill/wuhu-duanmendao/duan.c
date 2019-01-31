#include <ansi.h>
inherit F_SSERVER;
string perform_name() {return CYN"断字诀"NOR;}

int perform(object me, object target)
{
    int lvl;
	object weapon;
    
	lvl = me->query_skill("wuhu-duanmendao", 1);
    
	if( !target ) target = offensive_target(me);
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))                
        return notify_fail("你只能对战斗中的对手使用断字诀。\n");
    if( (int)me->query_skill("wuhu-duanmendao", 1) < 220 )
        return notify_fail("你的五虎断门刀不够娴熟，无法施展出断字诀。\n");
    if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "blade") 
                return notify_fail("你手上无刀如何能使出「断字诀」？\n");
    if (me->query_skill_mapped("blade") != "wuhu-duanmendao")
        // || me->query_skill_mapped("parry") != "wuhu-duanmendao")
         return notify_fail("你现在无法使用「断字诀」！\n");  
    if ( (int)me->query("max_neili") < 3000)
        return notify_fail("你的内力不够，无法施展出断字诀。\n");
    if ( (int)me->query("neili") < 1000)
        return notify_fail("你的真气不够，无法施展出断字诀。\n");
    if ((int)me->query("jingli") < 1000)
        return notify_fail("你的精气不够，无法施展出断字诀。\n");
     message_vision(HIY"$N猛然伏地，使出五虎断门刀"NOR+HIR"「断」"NOR+HIY"字诀，卷起一片白光直向$n滚去！\n"NOR,me, target);
    me->add("neili", -(300 +random(100)) );
    me->add("jingli", -150);
   
    //busy_time = me->query_skill("wuhu-duanmendao", 1) / 50;
    
    me->add_temp("apply/attack",lvl/2);
    me->add_temp("apply/strength",lvl/20);
    me->add_temp("apply/damage",lvl/5);
    
	if (userp(target)) target->start_busy(1+random(3));
	else target->start_busy(4);
    
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    
	if (!me->query("family")&&me->is_fighting(target)&&lvl>449&&userp(me))
    {
		message_vision(RED"$N心无杂念，将平素所身经百战积累的经验豁然贯通，陡然使出一招五虎断门刀的绝技！"NOR,me,target);
        me->add_temp("apply/attack",lvl/2);
		me->add_temp("apply/damage",lvl/5);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?3:1);
        me->add_temp("apply/attack",-lvl/2);
		me->add_temp("apply/damage",-lvl/5);
    }
    me->start_busy(random(2) + 1);
    me->add_temp("apply/attack",-lvl/2);
    me->add_temp("apply/strength",-lvl/20);
    me->add_temp("apply/damage",-lvl/5);

	me->start_perform(4,"「断字诀」");
    return 1; 
}

int help(object me)
{
        write(HIC"\n五虎断门刀之"HIY"「断字诀」："NOR"\n\n");
        write(@HELP
	五虎断门刀为云州秦家寨绝学，乃数十年前的其中一任寨主秦公望自创。
	全套刀法本来共有六十四招，后来秦家后人忘了“白虎跳涧”、“一啸风生”
	“剪扑自如”、“雄霸群山”，“伏象胜狮”五招，只有五十九招流传下来。后
	流传至秦家寨现任当家姚伯当的师父这一辈时，又有“负子渡河”和“重节
	守义”两招失传，只剩下五十七招。姚伯当为顾全颜面，将“负子渡河”和
	“重节守义”两个变招稍加改动，补足了五十九招之数，但在以此门刀法与
	青城派掌门司马林交手时仍被王语嫣窥破。
	该五虎断门百姓使用，大飞后会再出一招，其他门派和NPC无效。
	
	指令：perform blade.duan

 要求：
	当前内力 1000 以上；
	最大内力 3000 以上；
	当前精力 1000 以上；
	五虎断门刀等级 220 以上；
	需基本刀法等级 220 以上；
	激发招架为五虎断门刀；
                

HELP
        );
        return 1;
}

