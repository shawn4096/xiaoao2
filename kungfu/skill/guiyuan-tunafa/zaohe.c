// tu.c creat by sohu@xojh 
// Դ����ǧ�ߵ���˰���
// 
#include <ansi.h>
inherit F_SSERVER;
inherit F_CLEAN_UP;
#include "/kungfu/skill/eff_msg.h"

string exert_name(){ return HIY"���־�"NOR; }

int exert(object me, object target)
{
	int skill,num,damage,p;
	string msg;
	object zaohe;
	zaohe=present("zaohe",me);
	skill =  me->query_skill("guiyuan-tunafa", 1);
    if(!target) target = offensive_target(me);
    if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("���־�ֻ����ս���жԶ���ʹ�á�\n");
	
	if( me->query("max_neili") < 3000 )
		return notify_fail("����������������\n");
	if( me->query("neili") < 1200 )
		return notify_fail("��ĵ�ǰ�����������޷�ʩչ���־���\n");
    if( me->query("jingli") < 1000 )
		return notify_fail("��ĵ�ǰ����������\n");

	if( me->query_skill("guiyuan-tunafa", 1) < 300 )
		return notify_fail("��Ĺ�Ԫ���ɷ��ȼ�������\n");

	if( me->query_skill_mapped("force") != "guiyuan-tunafa" )
		return notify_fail("����ڹ����ԡ�\n");
    
	if (!me->query("quest/tiezhang/gytnf/pass"))
        return notify_fail("������˵�д˾�����������֪�����ʹ�á�\n");
	
	if( me->query_temp("gytnf/tu") )
		return notify_fail("���Ѿ�����ʹ����Ԫ���ɷ������־��ˡ�\n");

	
	if (!objectp(zaohe))
             return notify_fail("���Ȼ�������ϵ���˲������޷�ʹ�������־���\n");   
	
	if (userp(target)&&damage>4000) damage=4000+(damage-4000)/100;
	
	me->receive_damage("neili", -random(100)*num);
	me->receive_damage("jingli", -random(50)*num);
	
	message_vision(HBYEL+HIW "$N��Ȼ���ſڣ��������е�������һ��������й��ſ��е��������$n�����ţ�\n" NOR, me,target);
	
	me->set_temp("gytnf/tu",1);
	zaohe->add_amount(-1);
	//move(environment(me));
	me->add("jingli",-random(200));
	me->add("neili",-random(500));
    if (random(me->query("neili"))>target->query("neili")/2
		||random(me->query_dex(1))>target->query_dex(1)/2)
    {    
	  damage=me->query_skill("guiyuan-tunafa",1)+me->query_skill("force",1);
	  damage=damage*2+random(damage);
	  damage=damage*num;
	  if (damage>target->query("qi",1))
	     damage=target->query("qi")-1;
	  target->receive_damage("qi",damage,me);
	  //target->receive_wound("qi",damage/5,me);
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      tell_room(environment(target), HIR + target->name()+"�䲻��Ϊ��ö������У�ͻȻ��ʱΪ֮һ�ͣ���ȻѨ�������У�\n" NOR, ({ target }));  
           msg = damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
      target->add_busy(2+random(1));
	  if (!userp(target))
	  {
		  target->add_busy(1);
	  }
	}
	else {
     message_vision(CYN"$n�����������������������Ϯ�������ɵ�����һ���亹��\n"NOR,me,target);
	 me->add_busy(1+random(1)); 
	}
	if (zaohe->query_amount()<2)
	{
		zaohe->move(environment(me));
		tell_object(me, "\n���" + zaohe->query("name") + "�������ˣ�\n");
	}
	me->delete_temp("gytnf/tu");
	//if (me->query_skill("guiyuan-tunafa",1)<450)
	me->start_exert(3, "���־�");
	
	me->start_busy(1);
	return 1;
}



int help(object me)
{
	write(HIW"\n��Ԫ���ɷ�֮�����־�����"NOR"\n\n");
        write(@HELP
	��ǧ����������ǧ��������ӣ�һ����
	�����˵ã����������ɷ�������������
	��������Ԩ��������öҰ��������
	ͬʱ������佫�ڹ���Ϊ�ھ��й������
	�����˵ľ��������˷���ʤ����
	ע�⣺�������ö���淽��ʹ�á�

	ָ�yun zaohe

Ҫ��
	�������Ҫ��  3000 ���ϣ�
	��ǰ����Ҫ��  1200  ���ϣ�
	��ǰ����Ҫ��  1000  ���ϣ�
	��Ԫ���ɷ�  300  �����ϣ�
HELP
        );
        return 1;
}