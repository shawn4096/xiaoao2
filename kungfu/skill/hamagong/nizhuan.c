
// nizhuan.c ��ת����
// by snowman@SJ
// edit by sohu@xojh ���Ӹ��3����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

string exert_name()
{
        return HBWHT+HIB"��ת����"NOR;
}

int exert(object me, object target)
{
        int skill,sk;

        if( !target )
                target = me;

        if(!(int)me->query_skill("hamagong", 1) )
                return 0;
        if( me->query("oyf/hamagong") < 2 )
                return notify_fail("����δ�õ�ŷ������ת�ķ����޷����˸�󡹦ʹ������ת��\n");
        if((int)me->query("neili") < 3000  )
                return notify_fail("�������������\n");
        if((int)me->query("jingli") < 2000  )
                return notify_fail("��ľ���������\n");
		if (me->query_skill("hamagong",1)<500)
				return notify_fail("��ĸ�󡹦����500������δ�ڻ��ͨ���޷���ʹ��\n");
        if((int)me->query_temp("hmg_nizhuan") )
                return notify_fail("���Ѿ��þ����ķ������˸�󡹦��\n");

     
       skill = me->query_skill("force",1) + me->query_skill("hamagong", 1);
	   sk=skill/2;
       me->add("neili", -200);
       me->add("jingli", -20);


      message_vision(HIW "\n$N˫�ֳŵأ����з���һ���ܵͺ�����һ�ɹ��ھ�����ʹ$N˫����أ���ͷ������֮�ơ�\n" NOR, me);
	  message_vision(HIC"$N���д�����߶��˹���ǣ������ɵã�˹��ȷ�飬�����Ĳ�Ӣ��,״����񣬵����е�����ȴ�޴�\n"NOR,me);
      tell_object(me, HIR "�����ڸ�󡹦������ת�������йɾ޴������Ҫ��������һ����\n" NOR);
	  
	  if( me->query("quest/hama/nizhuan/pass")) {
         message_vision(HBMAG+HIW"$N����ŷ���洫�ڵ���ת���ϣ���󡹦�Ĵ��������˷��ԣ�ȫ������ӿ���ȣ��Ʋ��ɵ���\n"NOR,me);
		 me->add_temp("apply/strength",skill/5);
		 me->add_temp("apply/armor",skill/5);
		 me->add_temp("apply/defense",skill/5);
		 me->add_temp("apply/parry", skill/4);
         me->add_temp("apply/dodge", skill/4);
		}
		else
		{
     // me->start_call_out( (: call_other, this_object(), "remove_effect", me :), skill);
     
          if (me->query_skill("hamagong", 1) > 450)
            {
                me->add_temp("apply/parry", skill/4);
                me->add_temp("apply/dodge", skill/4);
            }
       if (userp(me))
       {
		   me->add_temp("apply/strength", skill/6);
		   me->add_temp("apply/damage", skill/10); 
		   me->add_temp("apply/cuff", skill/10);
		   me->add_temp("apply/staff", skill/10);
       }
		}
        me->add_temp("apply/dexerity", skill/10);
        me->add_temp("apply/attack", skill/10);
		me->add_temp("apply/strike", skill/10);
		
		
  
        me->set_temp("hmg_nizhuan", skill);
		
		call_out("remove_effect",60,me); //֮ǰ�Ǹ���ȫ��������Ч�� by renlai
        
        if( me->is_fighting() ) me->start_busy(1);

        return 1;
}

void remove_effect(object me)
{
        int amount;
        if(!me) return;

        if( !intp(amount = me->query_temp("hmg_nizhuan")) )
                return;

			
			
	 if( me->query("quest/hama/nizhuan/pass") ) {
			me->add_temp("apply/strength",-amount/5);
			me->add_temp("apply/armor",-amount/5);
			me->add_temp("apply/defense",-amount/5);
			me->add_temp("apply/parry", -amount/4);
            me->add_temp("apply/dodge", -amount/4);
		}
		else
		{
        if (me->query_skill("hamagong", 1) > 450)
        {
                me->add_temp("apply/parry", -amount/4);
                me->add_temp("apply/dodge", -amount/4);
        }
        if (userp(me))
        {
		   me->add_temp("apply/strength", -amount/6);
		   me->add_temp("apply/damage", -amount/10); 
		   me->add_temp("apply/cuff", -amount/10);
		   me->add_temp("apply/staff", -amount/10);
        }
		}
		
        me->add_temp("apply/dexerity", - amount/10);
        me->add_temp("apply/attack", - amount/10);
		me->add_temp("apply/strike", - amount/10);
		
        me->delete_temp("hmg_nizhuan");
        tell_object(me, HIW "���󡹦���˹��ã����ǽ������壬ֻ����ֹ����ת��\n" NOR);      
}

int help(object me)
{
write(WHT"\n��󡹦����ת��������"NOR"\n");
write(@HELP
	ŷ����Ķ��ž�����󡹦����������ѧ�еľ�������
	�Դ������������ɷ���ֶ�����µ�һ�ĳƺź���
	��󡹦������Ѱ���书�����ӹ������ס�����ת����
	֮�������ǵ�������������ľ�����
	��ת��Ч������Ч���������쳣���Ҳ���Ϊ�Է�����
	�ڴ���������������������Ч���⿪��󡹦������
	����ȫ���ͷ�

	ָ�exert nizhuan

Ҫ��
	��ǰ���� 3000 ���ϣ�
	��ǰ���� 2000 ���ϣ�
	��󡹦�� 500  ������
	�⿪��󡹦�������
	����ʩչ��ת������
	�⿪��󡹦��������
	�����ͷ���ת��������������
HELP
);
return 1;

}
