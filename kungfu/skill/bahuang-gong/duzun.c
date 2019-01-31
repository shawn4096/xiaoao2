// duzun.c
// action@SJ 2009/1/17
// edited by sohu@xojh  第一段30岁以前闭关一次就可以，第二段40岁前，第三段60岁
#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name(){ return HIR"唯我独尊功"NOR; }

int exert(object me, object target)
{
	int skill,i;
    i=1;
	if( me->query("neili") < 2000 )
		return notify_fail("你的内力不够。\n");
	if( me->query("jingli") < 1000 )
		return notify_fail("你的精力不够。\n");
    if( me->query("bhg/biguan") < 1 )
		return notify_fail("你尚没有闭关参悟八荒功，不能激发此内功。\n");
	if( me->query_skill("bahuang-gong", 1) < 350 )
		return notify_fail("你的八荒六合唯我独尊功等级不够。\n");

	if( me->query_skill_mapped("force") != "bahuang-gong" )
		return notify_fail("你的内功不对。\n");

	if( me->query_temp("bhg/duzun") )
		return notify_fail("你已经在运「八荒六合唯我独尊」了。\n");

	skill = me->query_skill("bahuang-gong")/5;
	if (me->query("bhg/biguan")<0) return 0; 
	//必须参悟一次才有效果，也就是说26岁时候可以使用，有点高了
	i=me->query("bhg/biguan");
    skill=skill*i;
	me->receive_damage("neili", -300);
	message_vision(HBGRN+HIW "$N鼻中吐出来的白气缠住$N脑袋周围，缭绕不散，渐渐愈来愈浓，成为一团白雾，将$N面目都遮没了，\n"
	                          +"跟着长吸一口真气，内力流转不绝,只听得$N全身骨节格格作响，犹如爆豆。！\n" NOR, me);
    
    
	me->set_temp("bhg/duzun", skill); 
   // me->add_temp("apply/armor", me->query_skill("bahuang-gong", 1)/5); 
    me->add_temp("apply/hand", skill);
	me->add_temp("apply/strike", skill);
    me->add_temp("apply/attack", skill);
    me->add_temp("apply/damage", skill/4);
	call_out("remove_effect", 1, me, skill);
	me->start_exert(1, "唯我独尊");
	if( me->is_fighting() )
		me->start_busy(random(2));
	return 1;
}

void remove_effect(object me, int count)
{
	int skill;
	if( objectp(me) && me->query_temp("bhg/duzun") ) {
		if( count-- > 0 ) {
			call_out("remove_effect", 1, me, count);
			return;
		}
		skill = me->query_temp("bhg/duzun");
     me->add_temp("apply/hand", -skill);
	 me->add_temp("apply/strike",- skill);
     me->add_temp("apply/attack", -skill);
     me->add_temp("apply/damage", -skill/4);
     me->delete_temp("bhg/duzun");
		message_vision(HIR"$N爆豆声渐轻渐稀，跟着那团白雾也渐渐淡了，$N鼻孔中不断吸入白雾，待得白雾吸尽，$N睁开双眼，缓缓站起。\n"NOR,me);
	}
}

int help(object me)
{
	write(HIW"\n八荒六合唯我独尊功之「唯我独尊功」："NOR"\n\n");
        write(@HELP
	八荒六合唯我独尊神功乃是逍遥派三大镇派绝技之一
	当初童姥修持此功和无崖子师兄的北冥神功、师妹李
	秋水修炼的小无相神功相抗衡。八荒六合唯我独尊原
	本是阳刚之气强劲的功法，每三十年需要闭关一次，
	返老还童一次，每一次还童攻击属性威力都会大幅上
	升,闭关三次后威力彻底释放，独霸武林。
	
	指令；yun duzun

要求：
	当前精力  1000 以上；
	当前内力  2000  以上；
	八荒六合唯我独尊功  350  级以上；
HELP
        );
        return 1;
}