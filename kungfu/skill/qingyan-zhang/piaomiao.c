// snowyu piaomiao 
// 注解此代码描述抄官方侠客行，本人感觉此工夫能给大理玩家增加娱乐：）
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

void remove_effect(object me, int dam,int attack);
void checking(object me,int dam,int attack);
void checking2(object me,int dam,int attack,int old_dam,int old_att);

int perform(object me, object target)
{
        object weapon = me->query_temp("weapon");
        int lv, attack, dam,old_att,old_dam;

        old_att = (int)me->query_temp("apply/attack",1);
        old_dam = (int)me->query_temp("apply/damage",1);
        lv = (int)me->query_skill("qingyan-zhang", 1); 
        attack = lv/6;
		dam = lv/6;
		if (userp(target))
        {
			attack =attack/2;
			dam=dam/2;
		}

        if( !target ) target = offensive_target(me);
        else me->set_temp("offensive_target", target);

        if (me->query("family/family_name")!="天龙寺" && !wizardp(me))
                return notify_fail(HIW "你非大理弟子无法施展「云烟飘渺」！\n" NOR);
    
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail(HIW "云烟飘渺只能对战斗中的对手使用。\n");

        if( me->query_temp("piaomiao") )
                return notify_fail(HIW "你正在使用云烟飘渺！\n");

        if( me->query_skill("force",1) < 400 )
                return notify_fail(HIW "你的内功火候未到！\n");

        if( me->query_skill("qingyan-zhang", 1) < 400 )
                return notify_fail(HIW "你的基本五罗轻烟掌尚未纯熟，无法施展云烟飘渺！\n");

        if( me->query_skill("strike", 1) < 400 )
                return notify_fail(HIW "你的基本掌法尚未纯熟，无法施展云烟飘渺！\n");

        if( me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail(HIW "你所用的内功心法不是乾天一阳，无法聚集真气。\n");
        
        if (me->query("max_neili") <= 1500)
                return notify_fail(HIW "你的内力修为不足，无发体会出云烟飘渺！\n" NOR);
        
        if ((int)me->query("neili", 1) < 1000)
                return notify_fail(HIW "你的内力不够，内劲不足以施展云烟飘渺！\n" NOR);

        if (me->query("jingli") <= 1000)
                return notify_fail(HIW "你没有足够的体力施展云烟飘渺！\n" NOR);

        if(me->is_busy()) return notify_fail(HIW "你正忙着呢,没办法施展云烟飘渺！\n" NOR);

        message_vision(HIC"$N运起乾天一阳内功心法，将真气凝聚运往手掌，顿时$N手掌泛白，掌中泛起一阵袅袅"HIW"白烟"HIC"分成五股袭向$n。\n" NOR, me,target);

        me->add("neili", -250);
        me->add("jingli", -100);

        me->set_temp("piaomiao", 1);
        me->add_temp("apply/attack", attack);
        me->add_temp("apply/damage", dam);
        message_vision(CYN"这几股"HIW"白烟"CYN"在$N凝聚的劲气引导之下，倏然袭向$n！\n" NOR, me,target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->set_temp("piaomiao", 2);
        //me->start_call_out( (: call_other, __FILE__, "checking2", me,dam,attack,old_dam,old_att :), 12);
    //    me->start_call_out( (: call_other, __FILE__, "checking", me,dam,attack :), 1);
		//me->start_perform(1,"飘渺轻烟");
       // call_out("checking",0,me,dam,attack);
		checking(me,dam,attack);
		return 1;
}

void checking(object me, int dam, int attack)
{
        int pm, limit;
        object weapon, target;

        weapon = me->query_temp("weapon");
        target = me->query_temp("offensive_target");

        pm = me->query_temp("piaomiao");
        limit = 1 + (int)me->query_skill("qingyan-zhang", 1)/100;
        
        if( !target || !me->is_fighting(target) ) target = offensive_target(me);

        if( pm > limit 
			|| pm > 6 
			|| weapon
			|| me->query_skill_prepared("strike")!="qingyan-zhang"
			|| me->query_skill_mapped("strike")!="qingyan-zhang") {
                message_vision(BLU "\n$N长呼一口气，将轻烟掌劲力收回丹田。\n"NOR, me);
                remove_effect(me, dam, attack);
                me->start_busy(1);
                return;
        }

        if( !living(me) || me->is_ghost()  )
        {
                remove_effect(me, dam, attack);
                return;
        }
        if( !me->is_fighting() )
        {
                message_vision(HIM "\n$N纵身向后一跃，收起了聚起的内劲。\n"NOR, me);
                remove_effect(me, dam, attack);
                tell_object(me, MAG "\n你将气息调节至原本的状态。\n\n"NOR);
                return;
        }
		me->add_temp("apply/damage",dam/2);
		message_vision(HIC"$N将乾天一阳功不断积蓄，然后向外轻轻一掌推出，拍向$n的前胸。\n"NOR,me,target);
		if (objectp(me)&&objectp(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        me->add_temp("apply/damage",-dam/2);
        me->start_call_out( (: call_other, __FILE__, "checking", me,dam,attack :), 1);
        return;
}

void remove_effect(object me, int dam, int attack) 
{
        if (!me) return;
        me->add_temp("apply/attack", -attack);
        me->add_temp("apply/damage", -dam);
        me->delete_temp("piaomiao");
        me->start_busy(1);
		return;
}
string perform_name() {return WHT"云烟缥缈"NOR;}

int help(object me)
{
        write(BLU"\n五罗轻烟掌之「云烟缥缈」："NOR"\n\n");
        write(@HELP
	五罗轻烟掌乃是大理段氏绝技，当初段正淳以五罗轻烟掌
	不仅名震江湖，而且传给自己的情人。其状若轻烟，看似
	风轻云淡，实则将雄浑的内力夹杂在掌法中发出。令人防
	不胜防。为重要的辅助进攻技能。
	
	指令：perform strike.piaomiao

要求：
	当前内力 1000  以上；
	最大内力 15000 以上；
	当前精力 1000  以上；
	基本掌法 400   级；
	五罗轻烟 400   级；
	乾天一阳 400   级；
	激发掌法为五罗轻烟掌；
	激发招架为五罗轻烟掌；
	备掌法为五罗轻烟掌；
	且空手。


HELP
        );
        return 1;
}
