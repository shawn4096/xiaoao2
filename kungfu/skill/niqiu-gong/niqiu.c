//niqiu.c 泥鳅功的pfm
//cre by sohu@xojh

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me,object target)
{
	string msg;
	int i;
	if( !target ) target = offensive_target(me);
        else me->set_temp("offensive_target", target);
	if( me->query_skill("force",1) < 200 )
		return notify_fail("你的基本内功还不够火候，使不出泥鳅身法。\n");  

	if( me->query_skill("niqiu-gong",1) < 200 )
		return notify_fail("你的泥鳅功还不够火候，使不出泥鳅身法。\n");  

	if (me->query_skill_mapped("dodge") != "niqiu-gong")
		return notify_fail("你现在无法使用泥鳅身法。\n");
	
	if( me->query("jingli", 1) < 200 )
		return notify_fail("你现在精力不够。\n");

	if( me->query("neili", 1) < 200 )
		return notify_fail("你现在内力不够。\n");

	if (me->query_temp("niqiu/fast"))
		return notify_fail("你正在使用泥鳅身法。\n");
    if (!me->is_fighting())
  		return notify_fail("泥鳅身法只有在战斗中才能施展。\n");
	if (!me->query("quest/shediao/nqg/pass"))
		return notify_fail("泥鳅身法只能通过解密获得瑛姑真传才能施展。\n");
	if ( me->query_skill("dodge",1) <200)
		return notify_fail("你基本身法不够，现在无法使用泥鳅身法。\n");

	msg = HIB"\n突见黑影晃动，$N宛如一条泥鳅，身形弯转，两扭三曲，滑不留手，但速度却极快，已然攻至$n身畔！\n"NOR; 

	me->add("neili", -100);
	me->add("jingli", -100);
	message_vision(msg, me,target);
	i = me->query_skill("niqiu-gong", 1)/5;
	
	me->add_temp("apply/dexerity", i/4);
	me->add_temp("apply/dodge", i/2);
	me->add_temp("apply/parry",i/2);
	
	me->set_temp("niqiu/fast", i);
	if (me->query_skill("niqiu-gong",1)<500)
	   me->start_perform(2, "泥鳅身法");
	
	call_out("remove_effect", 1, me,target, (int)me->query_skill("niqiu-gong", 1)/5);
	return 1;
}

void remove_effect(object me,object target, int count)
{
	int i;
	if (!me) return;
	
	i = me->query_temp("niqiu/fast");

	if (!objectp(target) 
		||me->query_skill_mapped("dodge") != "niqiu-gong"
		|| count-- < 1
		||!me->is_fighting())
	{
		me->add_temp("apply/dexerity", - i/4);
		me->add_temp("apply/dodge", -i/2);
		me->add_temp("apply/parry",-i/2);
		me->delete_temp("niqiu/fast");
		message_vision(HIB"$N停止了泥鳅功的运转，身法恢复了正常。\n"NOR, me);
		return;
	}

    if (objectp(target)
		&& target->query("id")!=me->query("id")
		&& me->query_skill("qimen-bagua",1)>180
		&& me->is_fighting()
		&& !random(6)	
		&& random(me->query_skill("niqiu-gong",1))>target->query_skill("dodge",1)/2)
    {
		message_vision(HIB"$N揉身而上，$n吃了一惊，急忙收力，但$N身手快捷之极，早已乘势直上，\n"
						+"双手五指成锥，分截$n胸口“神封”、“玉书”两穴，确是上乘点穴功夫。\n"NOR,me,target);
		target->add_busy(1+random(2));
		target->add_condition("no_exert",1);
    }
	
	call_out("remove_effect", 1, me,target,count);
}

string perform_name(){ return HIC"泥鳅身法"NOR; }

int help(object me)
{
        write(HIC"\n泥鳅功之「泥鳅身法」："NOR"\n\n");
        write(@HELP
	泥鳅功乃是瑛姑在黑龙潭中苦修所创立的一门身法
	在瑛姑独上桃源仙境寻找一灯复仇的过程中，将这
	门独特的轻功发挥的淋漓尽致。这门轻功甚是奇特，
	宛如一条泥鳅一样穿梭于泥泞的水中，灵活自如。
	
	注意：set 泥鳅功 泥鳅 有特效躲避效果

	perform dodge.niqiu

要求：
	当前内力 200 以上；
	当前精力 200 以上；
	基本轻功等级 200 以上；
	基本内功等级 200 以上；
	激发身法为泥鳅功。

HELP
        );
        return 1;
}
