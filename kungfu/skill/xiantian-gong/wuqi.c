// wuqi.c
// action@SJ 2009/1/17
// update sohu

#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return HBMAG+HIW"������Ԫ"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("neili") < 2000 )
		return notify_fail("�������������\n");
	if( me->query("jingli") < 1000 )
		return notify_fail("��ľ���������\n");

	if( me->query_skill("xiantian-gong", 1) < 550 )
		return notify_fail("������칦�ȼ�������\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("����ڹ����ԡ�\n");

	if( me->query_temp("xtg/wuqi") )
		return notify_fail("���Ѿ����ˡ�������Ԫ���ˡ�\n");
	if(!me->query("quest/qz/xtg/wuqi/pass") )
		return notify_fail("����δ�õ�����ʦ���Ĵ��У������޷�ʩչ������Ԫ��\n");
	skill =me->query_skill("xiantian-gong",1);
	
	me->add("neili", -500);
	me->add("jingli", -300);

	message_vision(
    HIC"$NĬ��Ĳ��񣬸βػ꣬Ƣ���⣬���ؾ����β��ǡ��ķ��������ϵ���[������Ԫ]֮�����Լ���������������Ҫ��\n"+

    "ʩչ����������Ĭ���֮�޵����������й����ϣ������������壬ʼ�ܹ�ԭ�޼����壬����Բͨ�������ķ��š�\n" NOR, me);
     if (me->query("quanzhen/force") =="pass")
     {
        me->add_temp("apply/defense", skill/3);
	    me->add_temp("apply/armor", skill/5);
		me->add_temp("apply/sword", skill/8);
		me->add_temp("apply/attack", skill/5);
		me->add_temp("apply/parry", skill/8);
		me->add_temp("apply/cuff", skill/5);
		me->add_temp("apply/strike", skill/5);

		me->set_temp("xtg/dywq",1);
		message_vision(HBYEL+HIW"\n\n$N���칦��Ȼ��ɣ����칦��ת��Ϣ�����������γ�һ���������ֵ����������\n"NOR,me);
	   //�������˺�ǿ������
     }
     me->set_temp("xtg/wuqi", skill ); 
	 me->add_temp("apply/attack", skill/5);
     me->add_temp("apply/parry", skill/10);	
     me->add_temp("apply/sword", skill/5);
	 me->add_temp("apply/armor", skill/5);
	 me->add_temp("apply/dodge", skill/5);
		
	call_out("remove_effect", 1, me, skill/15);
	
	//me->start_exert(1, "������Ԫ");
	//if( me->is_fighting() )
		//me->start_busy(random(2));
	return 1;
}

void remove_effect(object me, int count)
{
        int amount;
        if(!me)  return;
      	
		if( count-- > 0 ) 
		{
			call_out("remove_effect", 1, me, count);
			return;
		}
		amount = me->query_temp("xtg/wuqi"); 
		
		if (me->query("quanzhen/force") =="pass" )
        {
			me->add_temp("apply/defense", -amount/3);
			me->add_temp("apply/armor", -amount/5);
			me->add_temp("apply/sword",-amount/8);
			me->add_temp("apply/attack", -amount/5);
			me->add_temp("apply/parry",-amount/8);
			me->add_temp("apply/cuff",-amount/5);
			me->add_temp("apply/strike",-amount/5);

	   //�������˺�ǿ������
        }
		
			me->add_temp("apply/attack" ,-amount/5);
			me->add_temp("apply/parry",-amount/10);
			me->add_temp("apply/sword",-amount/5);
			me->add_temp("apply/armor", -amount/5);
			me->add_temp("apply/dodge", -amount/5);
			me->delete_temp("xtg/wuqi");
       
		tell_object(me, HIW"���["+HIR+"������Ԫ"+HIW+"]������ϣ��������ջص��\n"NOR);
		return;
      
}

int help(object me)
{
	write(HIC"\n���칦֮��������Ԫ����"NOR"\n\n");
        write(@HELP
	���칦��ȫ�����������Ϊ��Ҫ���ڹ��ķ����޵�
	����磬�ɷɻ�ժҶ���������Σ�����������Ԫ
	�������칦�������ķ�����ת�󣬿�������
	Ч�������˺��ͷ���Ч�������н⿪�����������
	���칦�����������������֡�

	��Ч��set ���칦 ������� 

	Ч����������ӷ���Ч�����������������������
	���Ӽ��¡�
	
	ָ�exert wuqi

Ҫ��
	��ǰ����  2000 ���ϣ�
	��ǰ����  1000 ���ϣ�
	���칦��  550  �����ϣ�
	�����ڹ����칦��
	���˶��������󱾼��ܷ�Ծ��

HELP
        );
        return 1;
}
