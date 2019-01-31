// liuxing.c  血刀经 [流星经天]
// cre by sohu@xojh
//突然红光一闪，血刀从斜刺里飞将过来，将兀鹰砍为两边，落在她身旁。
#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
 
string perform_name(){ return HIC"流"HIR"星"HIG"经"HIY"天"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int jixue;
    //流星经天无需战斗就可以发招！！
       // if( !me->is_fighting() )
                //return notify_fail("「流星经天」只能在战斗中使用。\n");
        if( !target ) target = offensive_target(me);
        if( !objectp(target))
                return notify_fail("这里没有这个人。\n");
        if(target==me)
                return notify_fail("你不能攻击自己。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("「流星经天」需要配备刀法方可使用，你使用的武器不对。\n");

        if((int)me->query_dex() < 35)
                return notify_fail("你的身法不够, 目前还不能使用这项绝技! \n");

        if((int)me->query_skill("dodge",1) < 200)
                return notify_fail("你的基本轻功修为不够, 不能使用「流星经天」！\n");
        if((int)me->query_skill("blade",1) < 200)
                return notify_fail("你的基本刀法修为不够, 不能使用「流星经天」！\n");

        if((int)me->query_skill("xuedao-jing",1) < 200)
                return notify_fail("你的血刀经修为不够， 目前不能使用「流星经天」! \n");

        if((int)me->query_skill("xuedao-daofa",1) < 200)
                return notify_fail("你的血刀刀法修为不够， 目前不能使用「流星经天」! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你必须使用血刀经，才能使用「流星经天」的绝技！\n");
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("你的招架不对，必须激发刀法为血刀刀法或金刚炼体术。\n");

        if( me->query_skill_mapped("force") != "shenzhao-jing" && me->query_skill_mapped("force") != "xuedao-jing")
	    	  return notify_fail("你现在所使用的内功同「血刀经」向抵触，不能使出「流星经天」的绝技！\n");

        if( (int)me->query("max_neili") < 2000 )
                return notify_fail("你的最大内力修为不够！\n");
        if((int)me->query("neili")<1000)
                return notify_fail("你的真气不够！\n"); 
        if((int)me->query("jingli")<600)
                return notify_fail("你的精力不够！\n"); 

        if(me->query_temp("xddf/liuxing"))
                return notify_fail("你正在施展「流星经天」！\n"); 


        
		msg =RED "\n突然红光一闪，$N将手中"+weapon->query("name")+RED"从斜刺里飞将过来，宛如一道流星向外飞去。\n"+
			"正是血刀经中的一招「流星经天」绝技！\n"NOR;
        message_vision(msg, me);
		//血祭刀次数，临时变量，杀人越多，血祭数越大
		
		jixue=weapon->query_temp("xdj/jixue");
		if (jixue<1) jixue=1;
		if (jixue>5) jixue=5;
		
		//target=me->select_opponent();

		me->add("jingli",-100-random(200));
		me->add("neili",-50-random(200));
		
		//call_out("lx_attack",5-jixue,me,target,weapon);
		call_out("lx_attack",5-jixue,me,target,weapon);
		
		//me->start_perform(2,"流星经天");
		me->set_temp("xddf/liuxing",1);
		return 1;

		      		
}
int lx_attack(object me,object target,object weapon)
{
	
	int damage,jixue;
	//兵器不在如何处理？
	if (!me) return 0;
	
	jixue=me->query_temp("xdj/jixue");
	
	if (!objectp(target)||!weapon) 
	{
			message_vision(RED"$N伸手一招，"+weapon->query("name")+RED"仿佛具有灵性一般又飞了回来。\n"NOR,me);
			me->add("jingli",-200);
			me->add("neili",-250);
			me->delete_temp("xddf/liuxing");
			return 1;
	}

	
	//target=me->select_opponent();
	damage=(me->query_skill("xuedao-jing",1)+me->query_skill("xuedao-jing",1))*jixue;
	damage=damage+random(damage);
	//npc无限杀伤，玩家限制
	if (userp(target)&&damage>3500) damage=3500+random(500);
	
	if (random(me->query_skill("blade",1))>target->query_skill("dodge",1)/2
		||random(me->query("combat_exp"))>target->query("combat_exp")/2)
	{
		message_vision(HIR"$n忽觉眼前暗色红光一闪，一把"+weapon->query("name")+HIR"飞来，躲闪不及，正中腰身！\n"NOR,me,target);
	//	tell_object(me,HIC"damage="+damage+NOR);
		
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/2,me);
		target->add_busy(1);
		if (objectp(target)&&me->is_fighting())
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	}
	else {
		message_vision(WHT"$n匆忙间一个懒驴打滚，虽然招式难看些，但终究是躲过了这柄刀！\n"NOR,me,target);
		target->add_busy(2);
	}
	message_vision(RED"$N纵身而起，跃起空中，将刀抓在手中，气定神闲！\n"NOR,me);
	me->delete_temp("xddf/liuxing");
	//me->start_perform(2,"流星经天");
	return 1;

}
int help(object me)
{
	write(RED"\n血刀刀法之「流星经天」："NOR"\n\n");
        write(@HELP

	流星经天乃是血刀老祖独门武技，变幻莫测的刀法绝技
	凭借高超的技艺和深厚的内功控制法门，一刀飞出，杀
	敌人与数丈之外。功力越深厚，发动速度越快威力越大。
	需要注意的是，血刀经讲究以血祭养刀，血祭数越多，
	刀的威力越大，流星经天的触发时间越短。
	
	指令: perform blade.liuxing

要求：
	最大内力 2000 以上；
	当前内力 1000 以上；
	当前精力 600  以上；
	当前身法 35   以上；
	血刀刀法 200  级以上；
	基本刀法 200  级以上；
	血刀经   200  级以上;
	激发刀法血刀刀法；
	激发招架为血刀刀法或金刚护体术；
	手持刀类武器；

HELP
        );
        return 1;
}