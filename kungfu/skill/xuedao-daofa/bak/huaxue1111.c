// huaxue.c  化血诀
// edit by sohu@xojh

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
int remove_effect(object me,int i);

string perform_name(){ return HIG"化血诀"NOR; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg, weaname;
        int lvl,damage,i,ap,dp;
    
        if( !me->is_fighting() )
                return notify_fail("「化血诀」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        if((int)me->query_dex() < 15)
                return notify_fail("你的身法不够, 目前还不能使用这项绝技! \n");

        if((int)me->query_skill("dodge") < 100)
                return notify_fail("你的轻功修为不够, 不能使用「化血诀」！\n");
 
        if((int)me->query_skill("xuedao-jing",1) < 100)
                return notify_fail("你的刀法修为不够， 目前不能使用「化血诀」! \n");

        if((int)me->query_skill("xuedao-dafa",1) < 100)
                return notify_fail("你的血刀大法修为不够， 目前不能使用「化血诀」! \n");

        if( me->query_skill_mapped("blade") != "xuedao-jing")
                return notify_fail("你必须使用血刀经，才能使用「化血诀」的绝技！\n");

        if( me->query_skill_mapped("force") != "shenzhao-jing" && me->query_skill_mapped("force") != "xuedao-dafa")
	    	  return notify_fail("你现在所使用的内功同「血刀大法」向抵触，不能使出「化血诀」的绝技！\n");

        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("你的内力修为不够！\n");
        if((int)me->query("neili")<600)
                return notify_fail("你的真气不够！\n"); 
        if((int)me->query("jingli")<200)
                return notify_fail("你的精力不够！\n"); 
		if (me->query_temp("xddf/huaxue"))
				return notify_fail("你正在使用化血诀！\n"); 
        target = me->select_opponent();
		

        lvl = (int)me->query_skill("xuedao-jing",1);
        weapon = me->query_temp("weapon");
        weaname = weapon->query("name");
        
		msg = HIG "\n$N运起血刀经中「化血诀」绝技，手中"NOR+weaname+HIG"幻起一片暗红色的刀影，向四周依次劈将出去！\n"NOR;
        msg+=RED+weaname+RED"上的血槽忽然发出一阵妖邪的暗红之色，极为刺眼！\n"NOR;
		message_vision(msg, me);

        if(me->query_temp("xuedao/yuxue")) {
                damage = me->query_skill("xuedao-dafa",1)/4;
                me->add_temp("apply/damage", damage);
				me->set_temp("xuedao/hx",1);
                message_vision(HBRED"$N更把血刀大法附于兵刃之上，"+weaname+HBRED"流淌着异样的红色光芒！\n"NOR, me,target);
        }
      //  me->add_temp("apply/blade", lvl/3);
        me->add_temp("apply/parry", lvl/5);
        me->add_temp("apply/dodge", lvl/5);
        //me->add_temp("apply/attack", lvl/3);
        //me->add_temp("apply/damage", lvl/4);
        me->set_temp("xddf/huaxue",lvl);
		
		call_out("remove_effect",1,me,lvl/20);
		me->start_perform(1,"血刀诀");
        return 1;
}

int remove_effect(object me,int i)
{
	int lvl;
	object weapon;
	weapon=me->query_temp("weapon");
	if (!me) return 0;
	
	lvl=me->query_temp("xddf/huaxue");
    
	if (!me->is_fighting()
		||me->query_skill_mapped("blade")!="xuedao-jing"
		||me->query_skill_mapped("force")!="xuedao-dafa"
		||!me->query_temp("weapon")
		||weapon->query("skill_type")!="blade"
		||i<0 )
	{
		me->add_temp("apply/blade",- lvl/5);
        me->add_temp("apply/parry",- lvl/5);
        me->add_temp("apply/dodge",- lvl/5);        
        me->add_temp("apply/attack", -lvl/3);
        me->add_temp("apply/damage", -lvl/4);
		me->delete_temp("xddf/huaxue");
		if (me->query_temp("xuedao/hx"))
		{
                me->add_temp("apply/damage",-me->query_skill("xuedao-dafa",1)/4);

		}
		message_vision(HIG"$N舔了舔飞溅在嘴角的"HIR"血迹"HIG"，停刀伫立，连连淫笑不已。\n"NOR,me);
	}
	call_out("remove_effect",me,i--);
	return 1;

}


int help(object me)
{
	write(HIG"\n血刀刀法之「化血诀」："NOR"\n\n");
        write(@HELP

	化血诀乃是化血经的刀法总纲，为整个诡异刀法
	的纲要文件，血刀刀法中变幻莫测的刀法绝技均
	由此而来，血刀诀是将平时蕴藏在刀槽中的血气
	精华以内功激发，散发出慑人的杀气和妖艳的红
	光，既能迷惑对手，也同时提高自身的战斗力，
	500级后大飞。
	
指令: perform blade.huaxue

要求：
	最大内力  1200 以上；
	当前内力  1000  以上；
	血刀大法  450  级以上；
	350级后小飞，
	450后成为起手式。

HELP
        );
        return 1;
}