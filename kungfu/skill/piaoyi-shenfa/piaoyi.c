// piaoyi.c ������
// cre by sohu Ʈ����������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,damage;
	string msg;
    int ap, dp;

    if (! target)
    {
	        me->clean_up_enemy();
	        target = me->select_opponent();
    }
	if (! target || ! me->is_fighting(target))
		return notify_fail("����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!me->query("quest/mj/pysf/pass") )
		return notify_fail("��ֻ����˵��Τ������Ʈ������������δϰ�á�\n");

	if ((int)me->query_skill("force", 1) < 350)
		return notify_fail("��Ļ����ڹ�������죬���ڻ��޷�ʹ�á�����������\n");
	if ((int)me->query_skill("dodge", 1) < 350)
		return notify_fail("��Ļ����Ṧ������죬���ڻ��޷�ʹ�á�����������\n");
	if (me->query_dex(1) < 60)
		return notify_fail("��Ļ�������������죬���ڻ��޷�ʹ�á�����������\n");
	
	if ((int)me->query_skill("piaoyi-shenfa", 1) < 350)
		return notify_fail("���Ʈ������������죬���ڻ��޷�ʹ�á�����������\n");
	                        
	if ((int)me->query("neili") < 200)
		return notify_fail("�����������������޷����á�����������\n");
	if ((int)me->query("jingli") < 200)
		return notify_fail("�����ھ����������޷����á�����������\n");
	if (me->query_temp("pysf/piaoyi"))
		return notify_fail("����������ʩչ������������\n");
		
	message_vision(HIG "$N" HIG "��Ȼ����һֻ�������Ƶã�����һ����Ӱ��������Ȼ������󻬳����࣬��ȥ��磬��������\n"
          HIG "��������������ס�Կ�Ѹ���ڵ��ַ���󳶶�һ��������һ����������Ӳק�����˼��ƹ����ȣ�\n"NOR,me);

        ap = me->query_skill("piaoyi-shenfa",1);
        dp = target->query_skill("dodge",1);
    
	skill=me->query_skill("piaoyi-shenfa",1);
	
	me->add_temp("apply/dodge",skill/4);
	me->add_temp("apply/parry",skill/4);
	me->add_temp("apply/dexerity",skill/5);	
	me->set_temp("pysf/piaoyi",skill);
	call_out("remove_effect",1,me);
	if (me->query_skill_mapped("strike")=="hanbing-mianzhang"
		||me->query_skill_prepared("strike")=="hanbing-mianzhang")
	    if (ap / 2 + random(ap) > dp || !userp(target))
		{
			target->add_busy(2);
			damage = (int)me->query_skill("force") + (int)me->query_skill("piaoyi-shenfa");
					damage = damage / 3;
					damage += random(damage);

			me->add("neili", -100);
			message_vision( HIR "ֻ��$n" HIR "���һ�����ֻ�֮�²������㣬��$N���������ҧס$n��������������Ѫ����\n" NOR,me,target);
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/2,me);
			target->apply_condition("hb_poison",5+random(3));

		} 

	return 1;
}


int remove_effect(object me)
{
	int skill;
	if (!me) return 0;
	skill=me->query_temp("pysf/piaoyi");
	
	if (!me->is_fighting()
		||me->query_skill_mapped("dodge")!="piaoyi-shenfa"
		||!me->query_temp("pysf/piaoyi"))
	{
		me->add_temp("apply/dodge",-skill/4);
		me->add_temp("apply/parry",-skill/4);
		me->add_temp("apply/dexerity",-skill/5);	
		me->delete_temp("pysf/piaoyi");
		message_vision(HIG"$N�о������������أ���æֹͣ����������ת��\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me);

}

string perform_name(){ return HIW"������"NOR; }

int help(object me)
{
        write(HIW"\nƮ������֮"HIG"������������"NOR"\n");
        write(@HELP
	Ʈ�������������Ĵ���֮���������Ķ����Ṧ����
	���书������������ϵ�ж������֣���ռ��ͷ������
	�����������񹦵����޼�Ҳ�Ը���������̾��������
	�������������������������Ԯ���䵱ɽ�����ս
	���б��ּ�Ϊ��ɫ����ѧ̩��������Ҳ���Ƶ�������
	���Ṧ�������������У�����һ�������������鴫��
	��������Τ������������еķ���ѧԭ��������Ķ�
	�����ֵľ�ѧ��һ��ʩչ�������мܽ������������
	��������ú������ƣ����и��ʳû�ʩչ����Ѫ����
	��͵Ϯ�Է���
	������Ҫ��Τ������̷�����ϰ��Ϊ���̶���������
	������
	ע�⣺set Ʈ������ ���� ���ܺ���Ч���������

	ָ�perform dodge.piaoyi
	
Ҫ��
	Ʈ�������ȼ� 350 �����ϣ�
	�����ڹ��ȼ� 350 �����ϣ�
	�����Ṧ�ȼ� 350 �����ϣ�
	������������ 60  ���ϣ�
	��ǰ����Ҫ�� 200 ���ϣ�      
	��ǰ����Ҫ�� 200  ���ϣ�
			    
                
HELP
        );
        return 1;
}