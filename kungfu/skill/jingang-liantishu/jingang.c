//jingang cred by sohu@xojh �������
//��Ҫ������������Ч���������Լ�����
//������cuff,strike,leg����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
  int lvl,i,j;
  string msg;
  lvl = (int)me->query_skill("jingang-liantishu", 1);
 // if (me->query("max_pot") >= 350 ) lvl = lvl /4 ;//250��˥��
  
  if( !target ) target = offensive_target(me);
  /*
  if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("��������ǡ�ֻ����ս���жԶ���ʹ�á�\n");*/

  // if( objectp(me->query_temp("weapon")))
	//	return notify_fail("�������ֲ���ʹ�á�������ǡ���\n");

   if( (int)me->query_skill("jingang-liantishu", 1) < 100 )
		return notify_fail("��Ľ����������������죬ʹ������������ǡ�������\n");
   if( (int)me->query_skill("xuedao-jing", 1) < 100 )
		return notify_fail("���Ѫ������������죬ʹ������������ǡ�������\n");

   if(me->query_skill("force", 1) <100)   
       return notify_fail("��Ļ������ܵȼ���������ʹ������������ǡ�������\n");

   if( (int)me->query_skill("cuff",1) < 100 )
		return notify_fail("��Ļ���ȭ���ȼ�����������ʹ�á�������ǡ���\n");
   if( (int)me->query_skill("strike",1) < 100 )
		return notify_fail("��Ļ����Ʒ��ȼ�����������ʹ�á�������ǡ���\n");
   if( (int)me->query_skill("leg",1) < 100 )
		return notify_fail("��Ļ����ȷ��ȼ�����������ʹ�á�������ǡ���\n");
   
   if(!me->query("quest/xd/jglts/jingang/pass"))
		return notify_fail("����δ�õ�����������洫������ʹ�á�������ǡ���\n");


   if( me->query_skill_mapped("strike") != "jingang-liantishu"
	 || me->query_skill_mapped("leg") != "jingang-liantishu"
	 || me->query_skill_mapped("cuff") != "jingang-liantishu")
		return notify_fail("������û�м����似���޷�ʹ�á�������ǡ���\n");


   if( me->query_skill_mapped("parry") != "jingang-liantishu")
		return notify_fail("����Ҫ�����м�Ϊ���������������ʹ�á�������ǡ���\n");

   if( me->query_skill_mapped("force") != "xuedao-jing")
		return notify_fail("����Ҫ�����ڹ�ΪѪ����������ʹ�á�������ǡ���\n");


   if( (int)me->query("max_neili") < 1300)
		return notify_fail("�������̫����ʹ������������ǡ���\n");

   if( (int)me->query("neili") < 500 )
		return notify_fail("����������̫����ʹ������������ǡ���\n");

   if( (int)me->query("jingli") < 500 )
           return notify_fail("������̫���ˣ�ʹ������������ǡ���\n");
   
   if (me->query_temp("jglts/jingang"))
   {
           return notify_fail("�������ڡ�������ǡ�״̬��\n");

   }
    message_vision(HIY"\n$N��Ѱ�����������Ľ��������ʩչ�������γɶ�ʱ��ġ�������ǡ�״̬��\n"
						"$Nֻ���û�����ת��Ϊ������������������Խ�׳���٣�\n"NOR,me);


	me->add_temp("apply/constitution", lvl/25);
	me->add_temp("apply/strength", lvl/30);
    me->add("jingli", -100);
    me->add("neili", -200);
	me->set_temp("jglts/jingang",lvl);
	call_out("remove_jingang",3+lvl/100,me);
  
	return 1;
}
int remove_jingang(object me)
{
	int lvl;
	if (!me||!me->query_temp("jglts/jingang")) return;
	lvl=me->query_temp("jglts/jingang");
	me->add_temp("apply/constitution", -lvl/25);
	me->add_temp("apply/strength", -lvl/30);
	me->delete_temp("jglts/jingang");
	message_vision(HIY"$N����һ�ڵ���ɫ��������������ǻ����չ���\n"NOR,me);
	return;

}


string perform_name(){ return HIR"�������"NOR; }

int help(object me)
{
	write(HIR"\n���������֮"+HIY"��������ǡ�"NOR"\n\n");
	write(@HELP
	�����������Ѫ���ŵ������书������ʽ���ķ�
	�����ں���һ�����ѧ�������书�������٣���
	Ѫ�����ز��⴫���似����ʹ����ʱ���ڴ��
	�����Լ������״̬���ӳ�״̬�ͽ����������
	���й������ȼ�Խ�ߣ�������ǳ�����ʱ��Խ��
	
	�����书����Ѫ���ŵ�����ѩ��������������
	���ɣ���Ѫ���ŷǺ��ĵ��Ӳ������������š�
	�����书ǿ������ȭ�����Ʒ����ȷ�����������
	�����Ż����书����Ҫ������ͬʱע��Э����չ
	��ˣ���־���ᶨ�����ؿ�����ϰ��
	����ʽ��õ��洫����ʹ�ã����򲻵����Ŷ���
	�����мܺ���û���ڹ��ķ�����Ч�������׳
	�Ϳ����������Ȼ��ǿ���١�

	ָ�perform jingang

Ҫ��
	������� 1300 ���ϣ�
	��ǰ���� 500  ���ϣ�
	��ǰ���� 500  ���ϣ�
	����������ȼ� 100 ���ϣ�
	Ѫ�����ڹ��ȼ� 100 ���ϣ�
	�����ڹ����Ṧ���мܡ�ȭ�����Ʒ����ȷ��ȼ� 100 ���ϣ�
	����ȭ��Ϊ�����������
	�����ȷ�Ϊ�����������
	����ȭ��Ϊ�����������
	�����м�Ϊ�����������
	�����ڹ�Ѫ������
	��ȭ��Ϊ����������ҿ��֡�

HELP
	);
	return 1;
}
