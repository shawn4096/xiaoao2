// sanhua.c 三花聚顶掌
// sohu@xojh

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
void remove_effect(object me, int amount);

int perform(object me, object target)
{
	int skill,i;
	string msg;


	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("三花聚顶只能对战斗中的对手使用。\n");

	if( !me->query("quest/qz/htz/sanhua/pass") )
		return notify_fail("你尚未学会这招的使用方法！\n");


	if( objectp(me->query_temp("weapon")) )
		return notify_fail("空手才能施展三花聚顶！\n");

	if( me->query_skill_mapped("strike") != "haotian-zhang" )
		return notify_fail("你所用的并非昊天掌，不能施展三花聚顶！\n");
	if( me->query_skill_mapped("parry") != "haotian-zhang"
		&& me->query_skill_mapped("parry") != "kongming-quan")
		return notify_fail("你所用的招架并非昊天掌或空明拳，不能施展三花聚顶！\n");
	if( me->query_skill_prepared("strike") != "haotian-zhang" )
                return notify_fail("你所备的并非昊天掌，不能施展三花聚顶！\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的并非先天功，施展不出三花聚顶！\n");

	if( me->query_skill("force") < 350 )
		return notify_fail("你的先天功火候未到，无法施展三花聚顶！\n");

	if( me->query_skill("strike") < 350 )
		return notify_fail("三花聚顶需要精湛的昊天掌方能有效施展！\n");

	if( me->query("neili") <= 1500 )
		return notify_fail("你的内力不够使用三花聚顶！\n");

	if( me->query("jing") <= 1200 )
		return notify_fail("你的精不够使用三花聚顶！\n");
  	
	if( me->query_temp("htz/juding") )
		return notify_fail("你正在使用三花聚顶绝技！\n");
	i=me->query("quest/qz/htz/sanhua/pass");
	
	if (i>0)
		msg = HIC"$N运起玄门先天功，内力遍布全身，头顶冒出丝丝热气，凝气于顶，状若"+chinese_number(i)+"朵"+HIW"莲花"+HIC"，手中掌法威力大增！\n\n"NOR;
	else msg=msg = HIC"$N运起玄门先天功，内力遍布全身，头顶冒出丝丝热气，凝气于顶，手中掌法威力大增！\n\n"NOR;
	message_vision(msg, me, target);

	skill =me->query_skill("haotian-zhang",1);
	
	me->set_temp("htz/sanhua", 3);

	if( me->query("quest/qz/htz/sanhua/pass")>1 )
	{
	   message_vision(HIW"$N将先天功运转周身，将昊天掌三花聚顶蕴含的威力显露无疑！\n"NOR,me);
	   skill =me->query_skill("haotian-zhang",1)+ me->query_skill("xiantian-gong",1)/ 3;
	}
	me->set_temp("htz/juding", skill);

	me->add_temp("apply/attack", skill/4);
	me->add_temp("apply/damage",  skill/6);
	me->add_temp("apply/strike",  skill/4);
	me->add_temp("apply/strength",skill/20);

	me->add("neili", -skill/2);
	me->add("jingli", -skill/3);
	me->add("jing", -100);
	remove_effect(me,skill/15);
	//call_out("remove_effect",1,me,(int)skill/15);
	return 1; 
}


void remove_effect(object me, int amount)
{
	int skill;
	if (!me||!me->query_temp("htz/juding")) return;
	skill=me->query_temp("htz/juding");
	if (!me->is_fighting()
		||me->query_skill_prepared("strike")!="haotian-zhang"
		||me->query_skill_mapped("strike")!="haotian-zhang"
		||me->query_skill_mapped("parry")!="haotian-zhang"
		||amount<0)
	{
		me->add_temp("apply/attack", -skill/4);
		me->add_temp("apply/damage", -skill/6);
		me->add_temp("apply/strike", -skill/4);
		me->add_temp("apply/strength",-skill/20);

		me->delete_temp("htz/juding");
		//me->delete_temp("htz/sanhua");

		message_vision(	HIC "\n$N吸了一口气，将散花聚顶的内力缓缓收回丹田！\n\n" NOR, me);
		return;
	}
	call_out("remove_effect",1,me,amount--);
}
string perform_name(){ return HIW"三花聚顶"NOR; }

int help(object me)
{
        write(HIC"\n昊天掌之「三花聚顶」："NOR"\n");
        write(@HELP
	昊天掌是全真教前期武功之一，属于门中核心弟子所修武功
	全凭一口真气存在，绵绵不绝，运使劲气攻击对方。此门武
	功是全真高级武功的基础，全真弟子须认真修炼。
	三花聚顶就是将全身真气逼出来，运转周身，功力到处，先
	天功和昊天掌水乳交融，内外兼修，短时期内大幅提升潜力
	使得掌法威力巨大。
	注意：此招需解密方可使用,需要修炼到三花聚顶境界方大成
		
	指令：perform strike.juding

要求：
	先天功法的等级 350  以上；
	昊天掌法的等级 350  以上；
	基本掌法的等级 350  以上；
	当前的内力要求 1500 以上；
	当前的精力要求 1200 以上；
	激发掌法为昊天掌；
	激发招架为昊天掌或空明拳；
	激发内功先天功；
	空手且备掌法为昊天掌。
HELP
        );
        return 1;
}
