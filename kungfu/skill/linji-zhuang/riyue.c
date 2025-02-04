// riyun.c
// by snowman@SJ 27/01/2000
// Modified by Lane@SJ 2005/4/14


#include <ansi.h>
int check_fight(object me);

int exert(object me)
{       
	int nh, neili;
       
	if( !me->is_fighting() )
		return notify_fail("「日月」字决必须在战斗中使用。\n");

	if( (int)me->query_skill("linji-zhuang", 1) < 350 )
		return notify_fail("你的临济十二庄修为还不够。\n");

	if( me->query("class") != "bonze" && me->query("family/generation") > 4)
		return notify_fail("你不是出家人，无法领会临济十二庄的「日月」字决！\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的真气不够。\n");

	if( me->query_temp("ljz/riyue") )
		return notify_fail("你正在运用临济十二庄的「日月」字决！\n");

	if( me->query_temp("ljz/wuwo") )	// 改成 不能和 wuwo 同时使用
		return notify_fail("你正在运用临济十二庄的「无我」字决！\n");


	tell_object(me,MAG"\n你五心向天，潜运日月二庄，益气升阳，益阴潜阳，升降反正，天地二气交泰于身，顿觉自己内力源源不止了。\n"NOR);
	message_vision(HIW"\n只见$N脸上红光时隐时现，一下变得神采弈弈。\n\n"NOR, me);

	if( me->query_temp("weapon") )
		me->set_temp("ljz/weapon", 1);
	else me->set_temp("ljz/weapon", 0);

	nh = (int)me->query_skill("linji-zhuang", 1)/10;
	neili = (int)me->query("neili");
	me->set_temp("ljz/riyue", neili);

    me->add("neili", -nh*20);
	if (me->query_skill("linji-zhuang",1)<450)
	   me->start_busy(1+random(1));
	
	check_fight(me);
	//me->start_exert(1, "「日月」");	// 因为无法和 wuwo 共同使用，故减短 yun busy
	return 1;

}

int check_fight(object me)
{
	int i;
	if( !me || !(int)me->query_temp("ljz/riyue") ) return 0;

	if( me->is_ghost() || !living(me) )
		me->delete_temp("ljz/riyue");

	if( me->query_temp("weapon") )
		i = 1;
	else
		i = 0;

	if( !me->is_fighting()
	|| me->query("neili") <= 10
	|| me->query_temp("ljz/weapon") != i
	|| (userp(me)
	&& me->query_skill_mapped("force") != "linji-zhuang") )
		call_out("remove_effect", 1, me);
	else {
		if( me->query("neili") < (int)me->query_temp("ljz/riyue") ) {
			tell_object(me, "你体内日月之力运转不息，使你感觉不到任何内力的消耗！\n");
			me->set("neili", me->query_temp("ljz/riyue"));
		}
		call_out("check_fight", 1, me);
	}       
	return 1;
}       

void remove_effect(object me)
{
	if( !me || !me->query_temp("ljz/riyue") ) return;
	me->start_exert(1, "日月");
	me->delete_temp("ljz/weapon");
	me->delete_temp("ljz/riyue");
	message_vision(HIR"$N所聚天地之精气已散回日月之间，$N又恢复了原有的气力消耗。\n\n"NOR, me);
}

string exert_name(){ return YEL"日月字决"NOR; }

int help(object me)
{
    write(YEL"\n临济十二庄「日月字诀」："NOR"\n\n");
    write(@HELP
	临济十二庄乃峨嵋著名的内功心法。是开山祖师郭襄融合了自己一生
	所见所闻的著名内功和心法后融合而成，既有九阳神功的刚猛，又有
	九阴真经功夫的阴柔，乃当世绝佳心法体系。
	「日月字诀」主要是通过运使临济庄心法来使得自身功力保持饱和状
	态，几乎不消耗内力。450级大飞，取消busy。

指令；exert riyue

要求：  
	当前内力 1000 以上；
	临济十二庄等级 350 以上；
	出家俗家弟子均可用；
	不能和「无我」字诀同时使用。
HELP
        );
        return 1;
}
