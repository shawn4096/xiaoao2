// shenyuan.c yun shenyuan 可以在战斗中增加相当的防御

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

string exert_name(){ return HIB"神元功"NOR; }

int exert(object me, object target)
{
	int skill;
	
	if (!me->is_fighting() && !me->query("shenyuan/powerup"))
		return notify_fail("你只能在战斗中使用神元功。\n");

	skill = me->query_skill("shenyuan-gong",1);
	
	if( (int)me->query_skill("shenyuan-gong",1) < 100 )
		return notify_fail("你目前等级不够，尚不能使用神元功。\n");

	if( (int)me->query("neili") < skill  )
		return notify_fail("你的内力不够。\n");
 
	if( (int)me->query_temp("shenyuan") ) 
		return notify_fail("你已经在运用神元功了。\n");

	me->add("neili", -300);
	
	message_vision(HIY "$N运起慕容绝学神元功，似乎熟知武功路数，攻守上轻松多了。\n" NOR, me);
	if (me->query("shenyuan/powerup"))
	{
		message_vision(HIC "$N将斗转星移心法融合到神元功之中，彻底融汇贯通。\n" NOR, me);
		me->add_temp("apply/parry", skill/2);	
		me->add_temp("apply/dexerity", skill/15);
		me->add_temp("apply/strength",skill/15);
		me->add_temp("apply/attack", skill/4);
	}
	else {
		me->add_temp("apply/parry", skill/10);	
		me->add_temp("apply/strength",skill/30);
		me->add_temp("apply/attack", skill/5);
    }

    if(me->query_skill("shenyuan-gong",1) < 450)
    {
		me->start_busy(1);
		me->start_exert(1, "神元功");
    }

	me->set_temp("shenyuan", skill);
	me->set_temp("sy/shenyuan", skill);
	call_out("remove_effect", 1, me, skill);

	return 1;
}

void remove_effect(object me, int skill)
{
	int skill1;
	if(!me) return;
	else skill1 = me->query_temp("sy/shenyuan");
	
	if (me->query_temp("shenyuan") && me->query("shenyuan/powerup"))
	{
		if (skill > 0) {
			skill = skill - 6;
			call_out("remove_effect", 1, me, skill);		  
			return;
		}
		message_vision(HIB"$N缓缓收功，又恢复到清冷状态。\n"NOR,me);
        me->delete_temp("shenyuan");
        me->add_temp("apply/parry", -skill1/2);	
   	    me->add_temp("apply/dexerity", -skill1/15);
	    me->add_temp("apply/strength",-skill1/15);
	    me->add_temp("apply/attack", -skill1/4);
	} 
	else 
	{
		if (me->is_fighting()){         
			call_out("remove_effect", 2, me, skill);		  
			return;
		}
		me->delete_temp("shenyuan");
		message_vision(HIB"$N缓缓收功，又恢复到清冷状态。\n"NOR,me);
		me->add_temp("apply/parry", -skill1/10);	
		me->add_temp("apply/strength",-skill1/30);
		me->add_temp("apply/attack", -skill1/5);
	}
	return;
}

int help(object me)
{
        write(YEL"\n神元功"+HIB"「神元劲」"NOR"\n");
        write(@HELP
		神元功乃是姑苏慕容世家的独门内功修习法门，江湖人言，“北乔峰，南慕容”。
		可见姑苏慕容的名声只响亮。慕容氏以斗转星移绝学名扬江湖，其本质就是一种
		借力打力的巧妙法门，初期主要靠技巧和对对方武技的熟悉和了解，但后期却
		主要靠自身功力的深厚程度。
		神元功之神元劲乃是提升具有自身防御以及劲力运使的神妙法门。若解开谜题
		神元功将和斗转星移技巧法门融会贯通，运使慕容武技将更胜一筹。功力越高
		威力越大。
		要求：
			基本内功等级 100 以上；
			吸星大法等级 100 以上；
			350后小飞，450后大飞。

HELP
        );
        return 1;
}
