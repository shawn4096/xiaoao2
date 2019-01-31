// wuwo.c
// Modified by Lane@SJ 2005/4/14
// edit by sohu@xojh 2004.1
#include <ansi.h>
int check(object me);
int exert(object me)
{

	int nh = me->query_skill("linji-zhuang", 1);
	if( !me->is_fighting() )
		return notify_fail("你只能在战斗中，运用「无我」字决！\n");
	if( me->query_skill("linji-zhuang", 1) < 200 )
		return notify_fail("你的临济十二庄修为还不够。\n");
	if( me->query("class") != "bonze" && me->query("family/generation") > 4 )
		return notify_fail("你不是出家人，无法领会临济十二庄的「无我」字决！\n");

	if( me->query_skill("medicine", 1) < 120 )
		return notify_fail("你的本草术理等级不够。\n");

	if( me->query("neili") < 500 )
		return notify_fail("你的真气不够。\n");

	if( me->query("jingli") < 300 )	// 增加精力要求
		return notify_fail("你的精力不够。\n");

	if( me->query_temp("ljz/wuwo") )
		return notify_fail("你正在运用临济十二庄的「无我」字决！\n");

	if( me->query_temp("ljz/riyue") )
		return notify_fail("你正在运用临济十二庄的「日月」字决！\n");

	if( me->query_temp("ljz/youming") )
		return notify_fail("你正在运用临济十二庄的「幽冥」字决！\n");

	message_vision(HIW"只见$N深深吸了一口气，脸上露出慈祥的笑容。\n"NOR, me);
	me->set_temp("ljz/wuwo", nh);  
	me->add("neili", - 200);
	check(me);
	me->start_exert(1,"「无我」字决");
	me->start_busy(1+random(1));
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), nh/3);
	return 1;
}

int check(object me)
{
	if( !me || !(int)me->query_temp("ljz/wuwo") ) return 0;

	if( me->is_ghost() || !living(me) )
		me->delete_temp("ljz/wuwo");

	if( me->query("jingli") < 100 
	|| me->query("neili") < 120
	|| me->query("qi") < 1		// 避免 BUG，气（-1）还恢复
	|| !me->is_fighting()
	|| (userp(me) && me->query_skill_mapped("force") != "linji-zhuang") ) {
		message_vision(HIC"$N暂缓呼吸，停止了内息的流动。\n"NOR, me);
		me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), 1);
	}
	else {
		if( me->query("qi") < (int)me->query("max_qi") && ( !me->is_busy() || random(2) ) ) {
			message_vision(HIY"$N脸色一沈又回复正常，想是正在调节内息。\n"NOR,me);
			me->add("neili", -50 );
			me->add("eff_qi", me->query_skill("medicine", 1));
			me->add("eff_qi", me->query_skill("linji-zhuang", 1)/10); // 增加上限恢复
			if( me->query("eff_qi") > me->query("max_qi") )
				me->set("eff_qi", me->query("max_qi"));
                me->add("qi", me->query_skill("force")*3/2);
                if( me->query("qi") > me->query("eff_qi") )
				  me->set("qi", me->query("eff_qi") );
		}
		call_out("check", 2+random(2), me);	// 缩短运行时间，增加效果
	}
	return 1;
}       

void remove_effect(object me)
{
        int nh;
        if( !me || !me->query_temp("ljz/wuwo") ) return;
        nh = me->query_temp("ljz/wuwo");
        me->start_exert(0);
        me->delete_temp("ljz/wuwo");
        message_vision(HIR"$N散去了「无我」心法，又恢复了原来的$N。\n\n"NOR,me);
}

string exert_name(){ return CYN"无我字决"NOR; }

int help(object me)
{
        write(HIW"\n临济十二庄「无我字诀」："NOR"\n\n");
        write(@HELP
	峨嵋临济庄乃是开派祖师郭襄女侠集成了家传武学以及九阴真经和
	九阳神功所创建。因历代掌门均为女性，所以峨嵋内功具有显然的
	阴柔特征且极为实用。
	天地诀，乃是战斗中疗伤所用。和本草以及经脉学和特殊内功等级
	都有影响。功力越高疗伤效果越好，且只能战斗中疗伤，和日月诀
	幽冥诀有冲突。
指令：exert wuwo

要求：  
	当前内力 500 以上；
	当前精力 300 以上；
	临济十二庄等级 200 以上；
	本草术理 120 以上；
	出家或俗家三代弟子；
	不能和「日月」「幽冥」字诀同时使用。
       
HELP
        );
        return 1;
}
