//���ص���֮��ɰ��
//����������
// By sohu

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HBRED+HIY"��ɰ��"NOR; }

void checking(object me,int count);

int perform(object me, object target)
{
        int skill;

        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("����ɰ�ơ�ֻ����ս����ʹ�á�\n");       
        if( (int)me->query_skill("strike", 1) < 350 )
                return notify_fail("��Ļ����Ʒ�������죬�޷�ʹ�����ص���֮��ɰ�ơ�\n");  
 		if((int)me->query_skill("kunlun-zhang", 1) < 350 )
                return notify_fail("������ص��ƻ�������죬����ʹ�����ص���֮��ɰ�ơ�\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 350 )
                return notify_fail("��������޼�����Ϊ�����Խ�������š�\n");

		//��ζ��550�����������������
		
		if( objectp(me->query_temp("weapon")) )
                return notify_fail("��ɰ����Ҫ����ʹ�á�\n");  
        
        if (me->query_skill_prepared("strike") != "kunlun-zhang"
           || me->query_skill_mapped("strike") != "kunlun-zhang")
                return notify_fail("�㲻ʹ�����ص��ƣ�������ʹ�ú�ɰ�ƣ�\n");   
        
		if( (int)me->query("max_neili", 1) < 6000 )
                return notify_fail("��������Ϊ̫ǳ���޷���ɰ�ƣ�\n");                
        if( (int)me->query("neili", 1) < 2000 )
                return notify_fail("�����������������޷���ɰ�ơ�\n");

        if( me->query_skill("poison",1)<150 )
                return notify_fail("��Ķ��Բ���150���޷����Ӳ�����ɰ��֮����\n");   
        if( me->query_str(1) < 70 )
                return notify_fail("��ĺ����������70���޷�ʹ�����ص���֮��ɰ�ơ�\n");  

		if( !me->query("quest/kl/klz/hongsha/pass") )
                return notify_fail("��δ�õ��������Ĵ��ڣ��޷����Ӳ�����ɰ��֮����\n");   
        
		if( me->query_temp("klz/hongsha") )
                return notify_fail("������ʩչ��ɰ��������\n");
                                                                               
        skill=me->query_skill("kunlun-zhang",1);

        message_vision(HBRED+HIY"\n$N�����ڹ�����ɫ����һƬ�쳱��������������˫�֣�˫�ֳ�һƬ���״����Ϊ���ˣ��������ؾ�ѧ����ɰ��������\n" NOR, me);
  //      message_vision(HBRED+HIY"\n��\n" NOR, me);
		if (me->query("gender")!="����")
		{
			skill=skill/3;
		}
		me->set_temp("klz/hongsha",skill);
		me->add_temp("apply/attack",skill/5);
		me->add_temp("apply/strike",skill/5);
		me->add_temp("apply/damage",skill/8);

        me->add("neili", -500);
		me->add("jingli",-200);
        call_out("checking",0,me,(int)skill/30);
        return 1;
}

void checking(object me,int count)
{
		int skill;
		if( !me )  return;	
		
		skill=me->query_temp("klz/hongsha");
		
		if (count<0
		||me->query_skill_mapped("strike")!="kunlun-zhang"
		||me->query_skill_prepared("strike")!="kunlun-zhang"
		||!me->is_fighting())
		{
			me->add_temp("apply/attack",-skill/5);
			me->add_temp("apply/strike",-skill/5);
			me->add_temp("apply/damage",-skill/8);

			me->delete_temp("klz/hongsha");

			message_vision(RED"$N����һ�ڰ���ɫ��������������ɰ�����չ���\n"NOR,me);
			return;
		}
		
		call_out("checking",1,me,count-3);

}  


int help(object me)
{
	write(WHT"\n���ص���֮��"HBRED+HIY"��ɰ��"WHT"����"NOR"\n");
	write(@HELP
	���غ�ɰ�����������޷�������������ʽ�����ھ�
	��ʹ˫�ƣ��ʳ��֮ɫ�����жԷ��󣬶Է����ϻ�
	�����Ե�Ѫ����ӡ������������ʱ������������֮
	�ǡ�ʵ�������Ʒ�����֮��ʽ����������ǿ��Ů��

	�����������ۼ�������ƶ��������Զ���ˮ׼
	�㹻���Һ�������ϵõ�����������������������
	������󣬻��ö�������ж���


	ע��:���������������̣��������ؾ�ѧ֮һ
	
	ָ�perform strike.hongsha

Ҫ��     
	��ǰ���� 2000 ���ϣ�
	������� 6000 ���ϡ�
	�����Ʒ� 350  ���ϣ�
	���ص��� 350  ���ϣ�
	����ˮƽ 150  ���ϣ�
	������� 70   ���ϣ�
	�����ڹ����ޣ�
	�����Ʒ�Ϊ�����ƣ�
	�����м�Ϊ�����ƣ�
	�����ұ��Ʒ�Ϊ�����ƣ�
	���ܷ���������ʹ�á�
HELP
	);
	return 1;
}
