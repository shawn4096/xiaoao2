// xixing.c 吸星大法

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string exert_name(){ return HIR"吸星诀"NOR; }

int exert(object me)
{
	int skill, i;

	if( (int)me->query("neili") < 2000  ) 
		return notify_fail("你的内力不够。\n");
	if( (int)me->query_skill("xixing-dafa",1) < 100  ) 
		return notify_fail("你的吸星大法等级不够。\n");
	if( (int)me->query_skill("force",1) < 100  ) 
		return notify_fail("你的基本内功等级不够。\n");
	
	if( (int)me->query_temp("xxdf/xixing") ) 
		return notify_fail("你已经在运功中了。\n");

    skill = (int)me->query_skill("xixing-dafa",1);
    i=skill;
	
	me->add("neili", -200+random(200));
    message_vision(HBBLU+HIW "\n$N凝神一聚，吸星大法神功发动，一股劲气在$N周身流转不息，形成一股若隐若现的吸力。\n" NOR, me);
    
//吸星大法绝世威力
	if (me->query("quest/xxdf/pass")==2)
    {
      message_vision(HBBLU+HIW "\n$N已经尽得任我行的真传，将自己所吸来的内力彻底融合，功力倍增。\n" NOR, me);
      i=i+(int)me->query_skill("xixing-dafa",1)/5;
      me->add_temp("apply/defense", i/6);
	  me->add_temp("apply/armor", i/6);
	  me->add_temp("apply/damage", i/10);
    }
	
	me->set_temp("xxdf/xixing", i);

	me->add_temp("apply/attack", i/4);
	//me->add_temp("apply/dexerity", i/10);	
    me->add_temp("apply/parry", i/5);

    
	call_out("remove_effect", 1, me, (int)skill/15);

	if( me->is_fighting() && me->query_skill("xixing-dafa",1)<450 ) me->start_busy(1+random(1));
	me->start_exert(1,"吸星大法");
	return 1;
}

void remove_effect(object me, int count)
{    
     int amount;
	 if (!me) return;
	 
	 amount = me->query_temp("xxdf/xixing");

	 if( count < 0 || !me->is_fighting()) 
	 {

		me->add_temp("apply/attack", - amount/4);
	// me->add_temp("apply/dexerity", - amount/10);
		me->add_temp("apply/parry", - amount/5);
	
		if (me->query("quest/xxdf/pass")==2)
		{          
			me->add_temp("apply/defense",- amount/6);
			me->add_temp("apply/armor", - amount/6);
			me->add_temp("apply/damage",- amount/10);
		}
		me->delete_temp("xxdf/xixing");
		message_vision(HBBLU+HIW "\n$N的"HIR"吸星大法"HIC"运行完毕，将内力收回丹田。\n" NOR, me);
		//tell_object(me, HIC"\n你的"HIR"吸星大法"HIC"运行完毕，将内力收回丹田。\n"NOR);
		return;
	 
	 }
     call_out("remove_effect", 2, me, count-1);
     return;      
    
}
int help(object me)
{
        write(HIR"\n吸星大法"+HIB"「吸星诀」"NOR"\n");
        write(@HELP
	吸星大法乃是日月神教前教主任我行的秘传武技，想当初日月神教有两大神技，
	其一为葵花宝典，其二为吸星大法，前人教主任我行在位时选择修习吸星大法。
	固然有其陷害东方不败的嫌疑，但吸星大法的诡异和强横也是他选择的主要原因
	以至于，江湖中为之谈虎色变。后来任我行在少林一战，以吸星大法重出江湖
	可见其威力无铸。
	金庸老先生在重新修订的笑傲江湖中将吸星大法归因于北冥神功，所以在本站
	的吸星大法中，更加强调吸星的特点。本站吸星大法总共分为二段来解。
	第一段：从梅庄中成功解救任我行，并在地牢中破解谜题。
		主要功效;增加防御和身法以及相应命中				
	第二段：成功拜师任我行并获得任我行亲自指点【融功】，唯有日月神教弟子可用
		功效;大幅提升防御，并开放其他特效激发。
	
要求：
	基本内功等级 100 以上；
	吸星大法等级 100 以上；
	350后小飞，450后大飞。

HELP
        );
        return 1;
}
