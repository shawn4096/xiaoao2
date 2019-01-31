// Modified by Darken@SJ
// Modify by server@sjty 2007.7.27 ����ʧ��������


#include <ansi.h>
inherit F_SSERVER;

void remove_effect(object me, object target, int count, int skill);

string exert_name() { return HIM"�����Ի���"NOR; }

int exert(object me, object target)
{
        int skill;
        skill = me->query_skill("qimen-bagua", 1);
        if( !target ) target = offensive_target(me);
        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (me->query_temp("thd/mazed")) 
                return notify_fail("������������˲��������С�\n");

        if (me->is_busy())
             return notify_fail("��Ŀǰ���Թ˲�Ͼ����Ͼ��������\n");
		//��ֹNPC�ã�����bug
		if (!userp(me)) return 0;
		
        if( (int)me->query("neili") < 300  ) 
                return notify_fail("�������������\n");
        if( (int)me->query("jingli") < 200  ) 
                return notify_fail("��ľ���������\n");
        if( (int)me->query_temp("thd/maze") ) 
                return notify_fail("���Ѿ�����һ�������ˡ�\n");

        me->add("neili", -200+random(300));
        me->add("jingli",-100);
        me->start_exert(5,"�����Ի���");
		if (me->query("thdjj/ronghe")=="pass") 
		{
		  message_vision(HBRED+HIY"$NƮȻԾ������һ�ƣ�����һ�ȣ��ж������ɽ���Χ��ʯ�顢��֦��Ȼ�ƶ���λ�ã�\n"NOR, me, target);
		  skill=skill+me->query("bihai-chaosheng",1)/6;
	   }
		else
			message_vision(HIY"$NͻȻԾ������һ�ƣ�����һ�ȣ�����Χ��ʯ�顢��֦�ƶ���λ�ã�\n"NOR, me, target);

               me->set_temp("thd/maze", skill);    
			   
               me->add_temp("apply/dexerity", skill/10);
               me->add_temp("apply/dodge",  skill /2);
               me->add_temp("apply/parry",  skill /2);
			   if (me->query("thdjj/ronghe")=="pass") {
				   me->add_temp("apply/defense", skill/2);
                   me->add_temp("apply/attack", skill/5);
			   }


       if(random(me->query_dex()) > target->query_dex()/3 
		   || random(skill) > target->query_skill("qimen-bagua",1)/3 )
       {
                message_vision(HBYEL"$n���������У���ʱ�����޴롣\n" NOR, me, target);
                target->add_temp("apply/dexerity", -skill/10);
                target->add_temp("apply/damage", -skill/2);
                target->add_temp("apply/dodge",   -skill/2);
                target->add_temp("apply/parry",     -skill/2);
                target->set_temp("thd/mazed", skill);
				
                if (me->query("thdjj/ronghe")=="pass") target->start_busy(4+random(2));
				else target->start_busy(2+random(1));
				//call_out("remove_effect", 1, me, target, skill / 2, skill);
       }
       else {
                message_vision(HBGRN"$nѸ����ǰ�ˣ�������������������֮�⡣\n" NOR, me, target);
                me->start_exert(3,"�����Ի���");
				me->add_busy(1+random(2));
        }
	    call_out("remove_effect", 1, me, target, skill / 2, skill);
       return 1;
}
void remove_effect(object me, object target, int count, int skill)
{
        if (objectp(me) && me->query_temp("thd/maze")){
                if (count-- > 0 && me->is_fighting(target)) {
                        call_out("remove_effect", 1, me, target, count, skill);
                        return;
                }
			//�����maze����npc����npc���ˣ�����û�г���
                if (me->query("thdjj/ronghe")=="pass") {
			        me->add_temp("apply/defense", -skill /2);
                    me->add_temp("apply/attack", -skill /5);
	            }
                me->add_temp("apply/dexerity", -skill/10);
                me->add_temp("apply/dodge",   -skill /2);
                me->add_temp("apply/parry",   -skill /2);
                me->delete_temp("thd/maze");

                if (!target) return;

                me->delete_temp("thd/maze");

                if (objectp(target) && me->is_fighting(target)) {
                        
						tell_object(me, "�㲼�������Ѿ���" + target->name() + "�ƻ��ˡ�\n");
                        if (userp(target) && living(target))
                                tell_object(target, me->name() + "���㲼�������Ѿ�����ʶ���ˡ�\n");
                }
                else {
                        tell_object(me, "�㲼�������Ѿ�ʧЧ�ˡ�\n");
                  }
        }
        if (objectp(target) && target->query_temp("thd/mazed")){

                target->delete_temp("thd/mazed");
                target->add_temp("apply/dexerity", skill/10);
                target->add_temp("apply/damage", skill/2);
                target->add_temp("apply/dodge",  skill/2);
                target->add_temp("apply/parry",  skill/2);

        }
		return;


}

int help(object me)
{
        write(HIG"\n�������Ի��󡹣�"NOR"\n");
        write(@HELP

	ʹ�����Ű���֮�����������Ա̺�����֮�ھ�
	Ѹ��������֦����ʯ����������һ���ر�Ϊ�̱�
	�����׼����������������Ķ��ֲ�������æ
	�ң�ͬʱս������Ҳ�ή�ͣ�����ķ������м�
	��Ե���ߡ�
	Ч����˫�����Ű��Եȼ�����Ա�������ء�
	
	ָ�exert maze

Ҫ��
	�̺������ȼ� 50 ���ϣ�
	���Ű��Եȼ� 50 ���ϣ�
	������� 300 ���ϣ�
	��������������ֵ��������޷�ʹ�á�
HELP
        );
        return 1;
}

