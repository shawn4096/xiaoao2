// shendao.c  血刀经 [赤练蛇形]
// changed by emnil@sj  2/5/2000

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
 
string perform_name(){ return HIB"赤练蛇形"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, weaname;
        int lvl,damage,i;
        int d=me->query_skill("xuedao-jing",1) /2+ me->query_skill("xuedao-daofa",1) /2 ;
         
        if(!userp(me)){ 
            // i = i / 2; 
             d= d /2;
			 }
			 
		 if (me->query_temp("xd/chilian"))
			     return notify_fail("「赤练蛇形」正在使用中。\n");
			 
        if( !me->is_fighting() )			
                return notify_fail("「赤练蛇形」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        if((int)me->query_dex() < 30)
                return notify_fail("你的身法不够, 目前还不能使用这项绝技! \n");

        if((int)me->query_skill("dodge",1) < 350)
                return notify_fail("你的轻功修为不够, 不能使用「赤练蛇形」！\n");
        
		if(!me->query("quest/xd/xddf/chilian/pass"))
                return notify_fail("你只是听说过赤练蛇形绝技,但不能使用「赤练蛇形」！\n");

        if((int)me->query_skill("xuedao-daofa",1) < 350)
                return notify_fail("你的刀法修为不够， 目前不能使用「赤练蛇形」! \n");

        if((int)me->query_skill("xuedao-jing",1) < 350)
                return notify_fail("你的血刀经修为不够， 目前不能使用「赤练蛇形」! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你必须使用血刀刀法，才能使用「赤练蛇形」的绝技！\n");
		
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("你的招架不对，必须激发刀法为血刀刀法或金刚炼体术。\n");

        if( me->query_skill_mapped("force") != "xuedao-jing" && me->query_skill_mapped("force") != "shenzhao-jing")
                return notify_fail("你现在所使用的内功同「血刀大法」向抵触，不能使出「赤练蛇形」的绝技！\n");

        if( (int)me->query("max_neili") < 4000 )
                return notify_fail("你的内力修为不够！\n");
        if((int)me->query("neili")<2000)
                return notify_fail("你的真气不够！\n"); 
        if((int)me->query("jingli")<1500)
                return notify_fail("你的精力不够！\n"); 


       
        lvl = (int)(me->query_skill("xuedao-daofa",1)+me->query_skill("xuedao-jing",1)/2);
        weapon = me->query_temp("weapon");
        weaname = weapon->query("name");
	    message_vision(HIB"\n$N身子向前一探，手中"+weapon->query("name")+HIB"颤动，刀刃便如一条赤练蛇一般，迅速无伦地在$n的胳膊上爬行而过，随即收刀入鞘！\n"NOR, me,target);

		me->set_temp("xd/chilian", d);
	    me->receive_damage("neili", 300);
	    me->receive_damage("jingli", 250);

        me->add_temp("apply/attack", d /2);
	    me->add_temp("apply/damage", d /4 );
	    me->add_temp("apply/blade",d/4);
        me->add_temp("apply/dodge", d /3);


	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//me->delete_temp("xd/chilian");
	    if (me->query("quest/xd/xdj/xuedao/pass"))
	    {
			me->start_perform(2, "「赤练蛇形」");
	    }
		else me->start_perform(4, "「赤练蛇形」");
		//赤练蛇形4招后可以嵌套
	   i=7;
		call_out("check_fight", 1, me, i);
	return 1;
}

void remove_effect(object me)
{
	int d;
	if(!me) return;

	d=me->query_temp("xd/chilian");
  
    me->add_temp("apply/attack",- d /2);
	me->add_temp("apply/damage", -d /4 );
	me->add_temp("apply/blade",-d/4);
	me->add_temp("apply/dodge", -d /3);
    me->delete_temp("xd/chilian");
	if (living(me))
		message_vision(HIY"\n$N"HBRED"的「赤练蛇形」绝技运行完毕，气回丹田，缓缓收功。\n"NOR, me);
	me->start_perform(3, "「赤练蛇形」");
	
	me->add_busy(2);
	return;
}

void check_fight(object me, int i)
{
	object weapon, target;

	if (!me||!me->query_temp("xd/chilian") ) return;
	
	weapon=me->query_temp("weapon");
	target = offensive_target(me);

	if(!i
	|| !living(me)
	|| !target
	||!weapon
	|| !me->is_fighting(target)
	|| environment(target)!=environment(me)
	|| me->query("neili") < 2000
	|| me->query("jingli") < 1500)
		return remove_effect(me);

	if(me->query_skill_mapped("blade") != "xuedao-daofa") {
		tell_object(me, HIR"你临时改换刀法，决定不再使用「赤练蛇形」绝技。\n");
		return remove_effect(me);
	} 
	else if(!objectp(weapon = me->query_temp("weapon"))
		|| weapon->query("skill_type") != "blade"){
		tell_object(me, HIR"你临时改换武器，决定不再使用「赤练蛇形」绝技。\n");
		return remove_effect(me);
	} 
	else {
		me->receive_damage("neili", 200);
		me->receive_damage("jingli", 150);
		if (objectp(target) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		call_out("check_fight", 1, me, i--);
	}
}
int help(object me)
{
        write(HIG"\n血刀刀法之「赤练蛇形」："NOR"\n\n");
        write(@HELP
	血刀经乃是血刀门独门武功，分为内功卷和刀法卷
	血刀刀法以诡异闻名于世，经血刀老祖大雪山雪谷
	中与江南四侠一战，往往都是从不可能之处劈出，
	极端的诡异难测。
	赤练蛇形是以自身功力注入刀法之中，一鼓作气，
	势将对手砍杀，此刀法为血刀中重要的中期武技非
	核心弟子不可传授。

指令：perform blade.chilian

要求：
	当前内力 2000 以上；
	最大内力 4000 以上；
	当前精力 1500 以上；
	血刀经等级 350 以上；
	血刀大法等级 350 以上；
	基本刀法等级 350 以上；
	激发刀法为血刀经；
	激发招架为血刀刀法或金刚护体术；
	激发内功为血刀大法。
	手持刀类武器
HELP
        );
        return 1;
}