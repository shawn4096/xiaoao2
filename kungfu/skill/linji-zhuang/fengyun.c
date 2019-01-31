// fengyun.c
// Modified by Lane@SJ 2005/4/14

#include <ansi.h>

int exert(object me)
{
	int improve;

	if( me->query("class") != "bonze" && me->query("family/generation") >4)
		return notify_fail("你不是出家人，无法领会临济十二庄的「风云」字决！\n");
        
	if( (int)me->query_skill("linji-zhuang", 1) < 150 )
		return notify_fail("你的临济十二庄修为还不够。\n");
    if(me->query("family/family_name")!="峨嵋派")
		return notify_fail("你不是峨嵋派，怎么可能会这种绝技。\n");
	//if(me->query("family/master_name")!="灭绝师太")
	//	return notify_fail("你没有受到掌门师尊的单独指导，怎么可能会用这种心法绝技。\n");
	if((int)me->query("neili") < 500 )
		return notify_fail("你的真气不够。\n");
    if((int)me->query("max_neili") < 1500 )
		return notify_fail("你的最大内力不够。\n");
	if((int)me->query("jingli") < 500 )
		return notify_fail("你的精力不够。\n");
	if((int)me->query_skill("dodge",1) < 150 )
		return notify_fail("你的基本轻功不够。\n");
	if((int)me->query_skill("anying-fuxiang",1) < 150 )
		return notify_fail("你的暗影浮香技能不够。\n");
	if( me->query_temp("ljz/fengyun") )
		return notify_fail("你正在运用临济十二庄的「风云」字决！\n");

	tell_object(me,HIW"你暗运风云桩心法，心思浮云飘空之悠闲缓慢，默想狂风荡地之迅速紧急一股丹田热气分注四肢百骸，但觉身手敏捷了许多。\n"NOR, me);
	tell_room(environment(me), HIW"只见"+me->name()+"微闭双眼，身旁凝起一圈白雾，瞬息间一股旋风卷过，身形又复清晰。\n"NOR,({ me }));
	improve = (int)me->query("dex")+(int)me->query_skill("linji-zhuang",1)/20;
	if (me->query("class") != "bonze")
	   improve = (int)me->query("dex");
	if (me->query_skill("jiuyin-zhengong",1)>150)
	{
		message_vision(HBBLU+HIW"$N深吸一口气，将九阴真经的功夫和临济庄两相融合，身法更具飘逸！\n"NOR,me);
		improve=improve+me->query_skill("jiuyin-zhengong",1)/3;
	}
	me->add_temp("apply/dexerity", improve);
	me->set_temp("ljz/fengyun", improve);  
	me->add("neili", - 150);    
	me->start_exert(1 , "「风云」字决");
	call_out("remove_effect", (int)me->query_skill("dodge",1)/3 , me );
	return 1;
}

void remove_effect(object me)
{
	int i;
	if(!me || !me->query_temp("ljz/fengyun")) return;

		i = me->query_temp("ljz/fengyun");
		me->add_temp("apply/dexerity", -i);
		me->delete_temp("ljz/fengyun");
		if ( living(me) && ! me->is_ghost()) 
			tell_object(me, HIW"你风云诀行功已久，略觉步履沉重了一些。\n"NOR);
		return;

}

string exert_name(){ return RED"风云字决"NOR; }

int help(object me)
{
    write(HIR"\n临济十二庄「风云字诀」："NOR"\n\n");
    write(@HELP
	临济十二庄乃峨嵋著名的内功心法。是开山祖师郭襄融合了自己一生
	所见所闻的著名内功和心法后融合而成，既有九阳神功的刚猛，又有
	九阴真经功夫的阴柔，乃当世绝佳心法体系。
	「风云字诀」主要是通过运使临济庄心法来使得自身身法提升的法门
	出家弟子因得到当代掌门灭绝师太传授。效果更佳。请注意，只有拜
	师灭绝师太方可使用。出家俗家均可使用，但俗家有优势。

指令: exert fengyun

要求：
	当前内力的要求 500  以上；
	最大内力的要求 1500 以上；
	临济十二庄要求 150  以上；
	基本轻功的要求 150  以上；
	暗影浮香的要求 150  以上；

HELP
        );
        return 1;
}
