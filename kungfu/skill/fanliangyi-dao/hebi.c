//双刀合璧
//hebi.c 参见倚天屠龙记
//by sohu@xojh

#include <ansi.h>


int check_fight(object me, object target, int amount);
private int remove_effect(object me, object target, int amount);

int perform(object me, object target)
{
        object *enemy;
        int i,j,k,amount;
        object wep1, wep2;
		wep1 = me->query_temp("weapon");

        if( !target || target == me) return notify_fail("你要和谁合璧？\n");

        if (me->query_temp("flyd/hebi")) return notify_fail("你已经在合璧了。\n");
        if (target->query_temp("flyd/hebi")) return notify_fail("对方已经在合璧了。\n");
        if (me->query("jingli") < 200) return notify_fail("你的精力不够了。\n");
        if (target->query("jingli") < 200) return notify_fail("对方的精力不够了。\n");
        if (!me->is_fighting()) return notify_fail("合璧只能在战斗中使用。\n");
        if (me->is_fighting(target)) return notify_fail("你正在和对方打架，合璧干什么？\n");
        if (me->query_skill("qimen-bagua",1)<200) return notify_fail("你对于易经八卦尚未领悟圆满，如何能施展这反两仪刀法？\n");
        if (target->query_skill("qimen-bagua",1)<200) return notify_fail("对方对于易经八卦尚未领悟圆满，如何能施展这反两仪刀法？\n");
		
		if (!me->query("quest/hs/flyd/hebi/pass"))
			return notify_fail("你尚未领悟这反两仪刀的奥义，如何能施展这反两仪刀法？\n");
		if (!target->query("quest/hs/flyd/hebi/pass"))
			return notify_fail("对方尚未领悟这反两仪刀的奥义，如何能施展这反两仪刀法？\n");

        if( (int)me->query_skill("fanliangyi-dao", 1) < 450 )
                return notify_fail("你的反两仪刀法不够450级，尚未娴熟，不会使用合璧。\n");
        if( (int)me->query_skill("zixia-gong", 1) < 450 )
			if( (int)me->query_skill("huashan-qigong", 1) < 450 )
                return notify_fail("你的华山内功未到火候，如何会有合璧的威力？\n");
        if (!wep1 || wep1->query("skill_type") != "blade"
			|| me->query_skill_mapped("parry") != "fanliangyi-dao"
			|| me->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("你现在激发刀法和招架不对，无法双刀合璧。\n");
        
        enemy = me->query_enemy();
        i = sizeof(enemy);
        
		while (i--) if (target->is_fighting(enemy[i])) break;
        
		if (i<0) return notify_fail(target->name()+"并没有和你的对手在交战。\n");

        if( (int)target->query_skill("fanliangyi-dao", 1) < 450 )
                return notify_fail("对方的反两仪刀法不够娴熟，不会使用合璧。\n");
        if( (int)me->query_skill("zixia-gong", 1) < 450 )
			if( (int)me->query_skill("huashan-qigong", 1) < 450 )
                return notify_fail("对方的华山内功未到火候，如何会有合璧的威力？\n");

        wep2 = target->query_temp("weapon");
        if (target->is_busy() || !wep2 || wep2->query("skill_type") != "blade"
			|| target->query_skill_mapped("parry") != "fanliangyi-dao"
			|| target->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("对方现在无法合璧。\n");
        
		message_vision(HIY "\n$N和$n使了个眼色，向左前方斜斜迈出一小步。\n" NOR, me, target);
		message_vision(HIG "\n$n微微点头，向右前方斜斜跟上迈出一小步。\n" NOR, me, target);

        message_vision(HIR "\n$N和$n正好呈现反两仪的方位，两人忽然双刀一交,招式顿时你攻我守，攻守兼备，反两仪刀威力大增。\n" NOR, me, target);
        
		me->set_temp("flyd/hebi", target->query("id"));
        target->set_temp("flyd/hebi", me->query("id"));
        
		me->receive_damage("jingli", 100);
        target->receive_damage("jingli", 100);
        me->receive_damage("neili", 200);
        target->receive_damage("neili", 200);
        
		k = (int)me->query_skill("fanliangyi-dao", 1);
        j = (int)target->query_skill("fanliangyi-dao", 1);
        amount = (k + j)/10;
        
		me->add_temp("apply/dexerity", amount);
        me->add_temp("apply/strength", amount);
		me->add_temp("apply/dodge", amount);
        me->add_temp("apply/armor", amount);
        me->add_temp("apply/blade", amount);
        me->add_temp("apply/parry", amount);
        me->add_temp("apply/damage", amount);
		
        target->add_temp("apply/dexerity", amount);
        target->add_temp("apply/strength", amount);
        target->add_temp("apply/dodge", amount);
        target->add_temp("apply/armor", amount);
        target->add_temp("apply/blade", amount);
        target->add_temp("apply/parry", amount);
        target->add_temp("apply/damage", amount);

		check_fight(me, target, amount);
        return 1;
}

int check_fight(object me, object target, int amount)
{  
    object wep1, wep2;
    //若有一人离开队伍，则解散队伍
	if(!me || !target) return remove_effect(me, target, amount);
    
	wep1 = me->query_temp("weapon");
    wep2 = target->query_temp("weapon");
    
	if(!me->is_fighting() 
		|| !living(me) 
		|| me->is_ghost() 
		|| !wep1 
		|| !target->is_fighting() 
		|| !living(target) 
		|| environment(me)!=environment(target)
		|| target->is_ghost() 
		|| !wep2)
			remove_effect(me, target, amount);
    else {
        call_out("check_fight", 1, me, target, amount);
    }
    return 1;
}
//离开阵法或失效判断
private int remove_effect(object me, object target, int amount)
{
	
	
	if(me && target && living(me) && !me->is_ghost() && living(target) && !target->is_ghost())
        message_vision(HIY "\n$N和$n一路反两仪刀法合璧用完，长吁一口气，相视一笑，各自收招。\n" NOR, me, target);

	
	if (me) {
		me->add_temp("apply/dexerity", amount);
        me->add_temp("apply/strength", amount);
		me->add_temp("apply/dodge", amount);
        me->add_temp("apply/armor", amount);
        me->add_temp("apply/blade", amount);
        me->add_temp("apply/parry", amount);
        me->add_temp("apply/damage", amount);
		me->delete_temp("hebi");
	}
	if (target) {
        target->add_temp("apply/dexerity", amount);
        target->add_temp("apply/strength", amount);
        target->add_temp("apply/dodge", amount);
        target->add_temp("apply/armor", amount);
        target->add_temp("apply/blade", amount);
        target->add_temp("apply/parry", amount);
        target->add_temp("apply/damage", amount);

		target->delete_temp("hebi");
	}
	return 0;
}

string perform_name(){ return HIC"双刀合璧"NOR; }
int help(object me)
{
        write(HIC"\n反两仪刀之「双刀合璧」："NOR"\n");
        write(@HELP
	此套刀法的步法招数与「昆仑派」的「正两仪剑法」一样，
	均从四象八卦中变化而出，都有八八六十四般变化。当初
	华山高矮二长老在光明顶一战，世人方知道这反两仪刀也
	是了不得的绝学。
	双刀合璧是两个人组成反两仪刀的刀阵，威力大增。此招
	需向两位长老请教。

	指令：perform blade.hebi

要求：
	华山气功（紫霞功）的等级 450  以上；
	反两仪刀的等级 450  以上；
	基本刀法的等级 450  以上；
	奇门八卦的等级 200  以上
	当前内力的要求 1000  以上；
	当前精力的要求 1000  以上；
	激发刀法为反两仪刀；
	激发招架为反两仪刀；
	激发内功不限；
	手持刀且对方条件雷同。
HELP
        );
        return 1;
}
