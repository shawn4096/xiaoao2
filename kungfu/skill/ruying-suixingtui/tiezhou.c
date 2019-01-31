// tiezhou.c �����ȷ���
// by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	mapping pre;
	string *skill, a, b;
	int i;

	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("�������ȡ�ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("ʹ�á������ȡ�ʱ˫�ֱ�����ţ�\n");
	if( !me->query("quest/sl/rysxt/tiezhou/pass"))
		 return notify_fail("����δ��ϰ�ɹ��������ȡ��񹦣�\n");
	if( (int)me->query_skill("ruying-suixingtui", 1) < 500 )
		return notify_fail("����������Ȳ�����죬����ʹ�á������ȡ���\n");

	if( (int)me->query_skill("yijin-jing", 1) < 500 )
		return notify_fail("����׽�ȼ�����������ʹ�á������ȡ���\n");
	if( me->query_temp("fumo"))
		 return notify_fail("������ʹ�ô���ȭ�����⹥������շ�ħ����\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("��Ŀǰ���ڹ��޷�֧����ʹ�á������ȡ����й�����\n");  
	if( me->query_temp("fumo"))
		 return notify_fail("������ʹ�ô���ȭ�����⹥������շ�ħ����\n");

	if( (int)me->query_dex() < 60 )
		return notify_fail("���������ǿ������ʹ�á������ȡ���\n");

	if (me->query_skill_prepared("leg") != "ruying-suixingtui"
	|| me->query_skill_mapped("leg") != "ruying-suixingtui")
		return notify_fail("�������޷�ʹ�á������ȡ����й�����\n");  
											       
	if( (int)me->query("max_neili") < 15000 )
		return notify_fail("������������Ϊ̫��������ʹ�á������ȡ���\n");
	if( (int)me->query("neili") < 1500 )
		return notify_fail("��Ŀǰ����̫�٣�����ʹ�á������ȡ���\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("�����ھ���̫�٣�����ʹ�á������ȡ���\n");
	if( me->query_temp("rysxt/tiezhou"))
		return notify_fail("������ʩչ�������ȡ��񹦡�\n");

	message_vision(HBYEL+HIW"\n$N˫�Ŷ��ֲ�վ�������������������ϰ�Ļ���������˫�ȣ�����"HIR"���㣡\n" NOR,me, target);
 	
	i = (int)me->query_skill("ruying-suixingtui", 1);

    me->add_temp("apply/attack", i/5);
    me->add_temp("apply/strength", i/20);
    me->add_temp("apply/leg",i/5);
	me->add_temp("apply/damage",i/5);
    me->add_temp("apply/parry", i/5);

	me->set_temp("rysxt/tiezhou", i);
	if (me->query_skill("ruying-suixingtui",1)<550)
	{
		me->start_perform(1,"������");
	}
	call_out("remove_effect",1,me,(int)i/30);

	return 1;
}

int remove_effect(object me,int count)
{
	int i;
	if (!me) return;
	i=me->query_skill("ruying-suixingtui",1);
	if (count<0
		||!me->is_fighting()
		||me->query_skill_prepared("leg")!="ruying-suixingtui"
		||me->query_skill_mapped("leg")!="ruying-suixingtui")
	{
		me->add_temp("apply/attack", -i/5);
		me->add_temp("apply/strength", -i/20);
		me->add_temp("apply/leg",-i/5);
		me->add_temp("apply/parry", -i/5);
		me->add_temp("apply/damage",-i/5);
		me->delete_temp("rysxt/tiezhou");
		message_vision(YEL "\n$N������أ������ͨ�죬����һ��������������������˫�ȵ����㹦ɢȥ��\n" NOR,me);
		return 1;

	}
	call_out("remove_effect",1,me,count--);	
	
}

string perform_name(){ return HBYEL+HIW"������"NOR; }
int help(object me)
{
        write(HBYEL"\n��������֮�������ȡ���"NOR"\n");
        write(@HELP
	��Ӱ����Ϊ������ʮ������֮һ���������־������ȷ��ļ��¡�
	���ü�ʵ���ȹ���ǿ�������������������У�˫�Ȳ�������
	�߳�������ַ���ʤ�������޿ɶ㣬�˵��������ǳ���������
	�����Ħ��һ��ʥɮ����͵ѧ������Ӱ����������С���๦ʩ
	չ��������Ȼ�����������׽������Ч���ã�������ʽ֮��
	���Լ�����֮�ۻ룬ȴ��ģ�µ����켫�¡�
	�����������ǽ�������Ѫ�򰾵Ĺ�������˫�ȣ�������ʯ��
	Ӳ�����㣬���������ȷ������������µ����֡�550����
		
	ָ�perform leg.tiezhou

Ҫ��  
	������� 15000 ���ϣ�      
	��ǰ���� 1500  ���ϣ�  
	��Ӱ������ 500 ���ϣ�
	�׽�ȼ� 500 ���ϣ�
	�����ȷ�Ϊ��Ӱ�����ȣ�
	�����м�Ϊ��Ӱ�����ȣ�
	�����ޱ�����
	��Ч������С��60��
	�������ǧҶ�ֻ��������⹦Ч��
                
HELP
        );
        return 1;
}
