// jiuyang.c 九阳神功加力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);
//int hit_ob(object me,object victim,int damage)；
//int get_bouns(int damage,int t,int level,int flag)

string exert_name(){ return HIR"九阳神功"NOR; }

int exert(object me)
{
	int skill, i;
	if(!me->is_fighting() && me->query_skill("jiuyang-shengong", 1) < 300 ) 
	     return notify_fail("你只能在战斗中用九阳神功来提升自己的战斗力。\n");

	if( (int)me->query("neili") < 400  ) 
		return notify_fail("你的内力不够。\n");
		
	if( (int)me->query_temp("jiuyang/powerup") ) 
		return notify_fail("你已经在运功中了。\n");

    skill = ((int)me->query_skill("force",1) + (int)me->query_skill("jiuyang-shengong",1))/2;
    i = skill/3 + random(skill/5); //以前是skill/6+random(skill/10) 略微增加上限 By lsxk

	me->add("neili", -200+random(200));
	message_vision(HIR "$N微一凝神，运起九阳神功，只见$N的脸色变得红润多了。\n" NOR, me);

	me->add_temp("apply/attack", i);
	me->add_temp("apply/dexerity", i/10);
	me->set_temp("jiuyang/powerup", i);
    me->add_temp("apply/armor", i/4);
    me->set_temp("fanzhen", i/2);

	call_out("remove_effect", 1, me, skill/3);
	if( me->is_fighting() ) me->start_busy(random(2));
	me->start_exert(1,"九阳神功");
	return 1;
}

void remove_effect(object me, int count)
{    
     int amount;
     if( objectp(me) && me->query_temp("jiuyang/powerup") ) 
           {
              if( count-- > 0 ) {
                     call_out("remove_effect", 1, me, count);
                    return;
            }
	 amount = me->query_temp("jiuyang/powerup");
	 me->add_temp("apply/attack", - amount);
	 me->add_temp("apply/dexerity", - amount/10);
         me->add_temp("apply/armor", - amount/4);
         me->delete_temp("fanzhen",- amount/2);  
	 me->delete_temp("jiuyang/powerup");

     tell_object(me, HIW"\n你的"HIR"九阳神功"HIW"运行完毕，将内力收回丹田。\n"NOR);
       }
    
}
