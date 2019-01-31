// jiuyang.c �����񹦼���

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);
//int hit_ob(object me,object victim,int damage)��
//int get_bouns(int damage,int t,int level,int flag)

string exert_name(){ return HIR"������"NOR; }

int exert(object me)
{
	int skill, i;
	if(!me->is_fighting() && me->query_skill("jiuyang-shengong", 1) < 300 ) 
	     return notify_fail("��ֻ����ս�����þ������������Լ���ս������\n");

	if( (int)me->query("neili") < 400  ) 
		return notify_fail("�������������\n");
		
	if( (int)me->query_temp("jiuyang/powerup") ) 
		return notify_fail("���Ѿ����˹����ˡ�\n");

    skill = ((int)me->query_skill("force",1) + (int)me->query_skill("jiuyang-shengong",1))/2;
    i = skill/3 + random(skill/5); //��ǰ��skill/6+random(skill/10) ��΢�������� By lsxk

	me->add("neili", -200+random(200));
	message_vision(HIR "$N΢һ������������񹦣�ֻ��$N����ɫ��ú�����ˡ�\n" NOR, me);

	me->add_temp("apply/attack", i);
	me->add_temp("apply/dexerity", i/10);
	me->set_temp("jiuyang/powerup", i);
    me->add_temp("apply/armor", i/4);
    me->set_temp("fanzhen", i/2);

	call_out("remove_effect", 1, me, skill/3);
	if( me->is_fighting() ) me->start_busy(random(2));
	me->start_exert(1,"������");
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

     tell_object(me, HIW"\n���"HIR"������"HIW"������ϣ��������ջص��\n"NOR);
       }
    
}