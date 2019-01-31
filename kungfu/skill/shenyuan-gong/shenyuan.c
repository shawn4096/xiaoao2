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

	
	if (!me->is_fighting())
	    if (!me->query("quest/mr/dzxy/pass"))
		  return notify_fail("你只能在战斗中使用神元功。\n");

	skill = me->query_skill("shenyuan-gong",1);
	
	if( (int)me->query_skill("shenyuan-gong",1) < 100 )
		return notify_fail("你目前等级不够，尚不能使用神元功。\n");

	if( (int)me->query("neili") < skill  )
		return notify_fail("你的内力不够。\n");
 
	if( (int)me->query_temp("shenyuan") ) 
		return notify_fail("你已经在运用神元功了。\n");

	me->add("neili", -300);
	me->set_temp("shenyuan", skill);
	me->set_temp("sy/shenyuan",skill);

	message_vision(HIY "$N运起慕容绝学神元功，似乎熟知武功路数，攻守上轻松多了。\n" NOR, me);
	if (me->query("quest/mr/dzxy/pass"))
	{
		message_vision(HBGRN+HIW "$N将领悟的斗转星移心法融合到神元功之中，彻底融汇贯通，斗转星移神功威力至此方显。\n" NOR, me);
		me->add_temp("apply/parry", skill/2);	
   	    me->add_temp("apply/dexerity", skill/15);
	    me->add_temp("apply/strength",skill/15);
	    me->add_temp("apply/attack", skill/4);
		me->set_temp("syg/sypowerup",1);
	}
	else {

	    me->add_temp("apply/parry", skill/10);	
	    me->add_temp("apply/strength",skill/30);
	    me->add_temp("apply/attack", skill/5);
    }
    if (me->query_skill("shenyuan-gong",1)<450)
    {
		me->start_busy(1);
		me->start_exert(1, "神元功");
    }
	
	call_out("remove_effect", 1, me, skill);
	
	
	//me->start_busy(1);

	return 1;
}

void remove_effect(object me, int skill)
{
	int skill1;
	if (!me) return;
	skill1=me->query_temp("sy/shenyuan");

	if ( !me->is_fighting() || skill<0)
	{

		if (me->query("quest/mr/dzxy/pass"))
		{
		    message_vision(HBGRN+HIW"$N神元功一滞，长吁一口气，缓缓收功，又恢复到清冷状态。\n"NOR,me);

			me->delete_temp("shenyuan");
			me->add_temp("apply/parry", -skill1/2);	
   			me->add_temp("apply/dexerity", -skill1/15);
			me->add_temp("apply/strength",-skill1/15);
			me->add_temp("apply/attack", -skill1/4);


		}else {
			message_vision(HIB"$N缓缓收功，又恢复到清冷状态。\n"NOR,me);
			me->delete_temp("shenyuan");
			me->add_temp("apply/parry", -skill1/10);	   			
			me->add_temp("apply/strength",-skill1/30);
			me->add_temp("apply/attack", -skill1/5);
		}
		return;
	}	
	call_out("remove_effect",2,me,skill-6);	
	return;
}

int help(object me)
{
        write(YEL"\n神元功"+HIB"「神元劲」"NOR"\n");
        write(@HELP
	神元功乃是姑苏慕容世家的独门内功修习法门，
	江湖人言，“北乔峰，南慕容”。可见姑苏慕容
	的名声只响亮。慕容氏以斗转星移绝学名扬江
	湖，其本质就是一种借力打力的巧妙法门，初
	期主要靠技巧和对对方武技的熟悉和了解，但
	后期却主要靠自身功力的深厚程度。
	神元功之神元劲乃是提升具有自身防御以及劲
	力运使的神妙法门。若解开谜题神元功将和斗
	转星移技巧法门融会贯通，运使慕容武技将更
	胜一筹。功力越高威力越大。

	使用指令：yun shenyuan

要求：
	基本内功等级 100 以上；
	神元功法等级 100 以上；
	350后小飞，450后大飞。

HELP
        );
        return 1;
}
