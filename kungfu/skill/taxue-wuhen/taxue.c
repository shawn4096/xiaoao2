
//taxue.c ̤ѩ�޺�
//cre by sohu@xojh 2014 ��ֲ���Ṧ����
// ����Ϊ�����ݣ��Ǻ��ڽ�������Ҫ����

#include <ansi.h>
void remove_effect(object me,int count);

string perform_name() {return HIY"̤ѩ"NOR;}

int perform(object me,object target)
{                               
        int improve;
      
        if( !me->is_fighting() && (int)me->query_skill("xuantian-wuji",1)<450 )
                return notify_fail("������ֻ����ս����ʹ�á�̤ѩ����\n");

        if( (int)me->query_skill("xuantian-wuji",1) < 200 )
                return notify_fail("��������޼�����������죬����ʹ�á�̤ѩ����\n");
		
		if( me->query_skill("taxue-wuhen",1)< 200 )
                return notify_fail("��������޼�����������죬����ʹ�á�̤ѩ����\n");
        
		if (me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("����ڹ����ԣ�����ʹ�á�̤ѩ����\n");
      
        if((int)me->query("max_neili")<2000)
                return notify_fail("������������Ϊ̫��������ɡ�\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("�������������\n");

        if( me->query_temp("txwh/taxue")   )
                return notify_fail("������ʹ�á�̤ѩ����\n");
       
      
        message_vision(HIW"$N�����޼�����ת��Ϣ��������Ծ������������������շ��У�̤ѩ���У�ƮȻ���ɣ�\n" NOR, me);
      
        improve = (int)me->query_dex();
        if (me->query_skill("xuantian-wuji",1)<350)
        {
			me->start_perform(2,"��̤ѩ��");
        }
        me->add_temp("apply/dodge", improve);
        me->add_temp("apply/dexerity", improve);
        me->set_temp("txwh/taxue",improve);  
        me->add("neili", -(350-(int)me->query_skill("xuantian-wuji",1)/10));            
        call_out("remove_effect", 1, me, improve);
        return 1;
}

void remove_effect(object me,int count)
{
         int improve;
         if( !me ) return;
         if( !intp(improve = me->query_temp("txwh/taxue"))) return;
         if( count < 1 || !me->is_fighting()){
          me->add_temp("apply/dodge", - improve);
          me->add_temp("apply/dexerity", -improve);
          me->delete_temp("txwh/taxue");
          tell_object(me, HIW"��ɢȥ����ۼ��������������˽Ų������ظ���������\n"NOR);
          tell_room(environment(me), HIW + me->name()+"���ص��ɢȥ������Ĺ�����\n"NOR,  ({ me })); 
          return;
        }
        call_out("remove_effect", 1 , me ,count -1);
}

int help(object me)
{
        write(WHT"\n̤ѩ�޺�֮��̤ѩ��������"NOR"\n");
        write(@HELP
	̤ѩ�޺���������Ҫ���Ṧ����Ҫ�����޼���������
	�ˡ�̤ѩ�����ɺ������Ծ������������������֮��
	����֮ʱ���ڿ��з�Ծ����ʮ�ɵľ��롣���ķ�һ��
	ʹ���ɴ���������Ṧ����350��С�ɣ�450�����
	
	perform dodge.taxue

Ҫ��
	̤ѩ�޺۵ȼ� 200 ���ϣ�
	�����޼��ȼ� 200 ���ϣ�
	�������Ҫ�� 2000 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
HELP
        );
        return 1;
}
