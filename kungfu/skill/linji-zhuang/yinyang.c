// yinyang.c
// Modified by Lane@SJ 2005/4/14

#include <ansi.h>
int exert(object me)
{
	int improve = (int)me->query_skill("force",1) * 3;

	if( (int)me->query_skill("linji-zhuang", 1) < 350 )
		return notify_fail("你的临济十二庄修为还不够。\n");

	if( me->query("class") != "bonze" && me->query("family/generation") > 4)
		return notify_fail("你不是出家人，无法领会临济十二庄的「阴阳」字决！\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的内力不够。\n");

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("你的真气不够。\n");

	if( me->query_temp("ljz/yinyang")   )
		return notify_fail("你正在运用临济十二庄的「阴阳」字诀！\n");

	message_vision(HIW"只见$N吸取天地之间的"HIR"阴阳"HIW"两气，顿然气力大增！\n"NOR,me);
/*
	me->add("max_qi", improve);
	me->add("eff_qi", improve);
	me->add("qi", improve);
   */ 
	me->add_temp("apply/armor",me->query_skill("linji-zhuang",1)/6);
	me->add_temp("apply/parry",me->query_skill("linji-zhuang",1)/6);

	if (me->query("emjy/pass"))
    {
	  message_vision(HIC"$N在所领悟的峨嵋九阳奥秘两相对照，浑身劲气混元成圈，宛如气罩！\n"NOR,me);
	  me->add_temp("apply/armor",me->query_skill("linji-zhuang",1)/4);

	  me->add_temp("apply/parry",me->query_skill("linji-zhuang",1)/4);
	  me->add_temp("apply/defense",me->query_skill("linji-zhuang",1)/4);
    }
//	修改以前的直接恢复气血
/*
	me->add("max_jing", improve);
	me->add("eff_jing", improve);
	me->add("jing", improve);
*/
//	增加精血

	me->set_temp("ljz/yinyang", improve);
	me->add("neili", - 500);
	//if( me->is_fighting() ) me->start_busy(random(2));
	me->start_exert(1, "阴阳字决");
//	me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), improve );
	call_out("remove_effect",1,me,improve/60);
	return 1;
}

void remove_effect(object me,int count)
{      
	int improve;
	//if( me->is_ghost() ) return;

	if( !me || !me->query_temp("ljz/yinyang") ) return;
	
	if (!me->is_fighting()
		||count<0)
	{
		improve = me->query_temp("ljz/yinyang");
		me->delete_temp("ljz/yinyang");
		/*
		if (me->query("qi")<improve)
		{
			me->set("qi",1);
			me->add("max_qi", - improve);
		}else me->add("max_qi", - improve);

		if (me->query("jing")<improve)
		{
			me->set("jing",1);
			me->add("max_jing", - improve);
		}
		else me->add("max_jing", - improve);	
    
	// 修改原来恢复上限问题
		if( me->query("eff_qi") > me->query("max_qi") )
			me->set("eff_qi", me->query("max_qi") );
		if( me->query("qi") > me->query("max_qi") )
			me->set("qi", me->query("max_qi") );

		if( me->query("eff_jing") > me->query("max_jing") )
			me->set("eff_jing", me->query("max_jing") );
		if( me->query("jing") > me->query("max_jing") )
			me->set("jing", me->query("max_jing") );
*/
		me->add_temp("apply/armor",-me->query_skill("linji-zhuang",1)/6);
		me->add_temp("apply/parry",-me->query_skill("linji-zhuang",1)/6);

		if (me->query("emjy/pass"))
		{
			me->add_temp("apply/parry",-me->query_skill("linji-zhuang",1)/4);
			me->add_temp("apply/defense",-me->query_skill("linji-zhuang",1)/4);
			me->add_temp("apply/armor",-me->query_skill("linji-zhuang",1)/4);

		}


		tell_object(me, HIC"你的临济十二庄"HIR"「阴阳」"HIC"字诀运功完毕，临济庄的护体效果回复了正常。\n"NOR);
		return;
			
	}
	if (objectp(me))
		call_out("remove_effect",1,me,count--);
	
}

string exert_name(){ return HIC"阴阳字决"NOR; }

int help(object me)
{
    write(HIC"\n临济十二庄「阴阳字诀」："NOR"\n\n");
    write(@HELP
	临济十二庄乃峨嵋著名的内功心法。是开山祖师郭襄融合了自己一生
	所见所闻的著名内功和心法后融合而成，既有九阳神功的刚猛，又有
	九阴真经功夫的阴柔，乃当世绝佳心法体系。
	「阴阳字诀」主要是通过运使临济庄心法来提高自身的防御体系，若
	开了峨眉九阳谜题可大幅提升自身防御。

指令：exert yinyang

要求：
	当前内力 1000 以上；
	最大内力 1500 以上；
	临济十二庄等级 350 以上；
	出家或俗家三代弟子。

HELP
        );
        return 1;
}
