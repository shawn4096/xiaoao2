// shuang.c ˫Ȧ��
// sohu@xojh
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int remove_shuang(object me,int count);

int perform(object me, object target)
{
	int skill;
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("��˫Ȧ�֡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("luohan-quan", 1) < 100)
		return notify_fail("����޺�ȭ��������죬���ڻ��޷�ʹ�á�˫Ȧ�֡���\n");
	if (me->query_skill("cuff", 1) < 100)
		return notify_fail("��Ļ���ȭ��������죬���ڻ��޷�ʹ�á�˫Ȧ�֡���\n");
  	if (me->query_skill("force", 1) < 100)
		return notify_fail("��Ļ����ڹ�������죬���ڻ��޷�ʹ�á�˫Ȧ�֡���\n");  
	if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
           // me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ��˫Ȧ�֡���\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�����������������޷����á�˫Ȧ�֡���\n");
	if ((int)me->query("jingli") < 200)
		return notify_fail("�����ھ����������޷����á�˫Ȧ�֡���\n");			
	
	if (me->query_skill_mapped("cuff") != "luohan-quan"
		||me->query_skill_prepared("cuff") != "luohan-quan") 
		return notify_fail("��û�м����޺�ȭ���޷�ʹ��˫Ȧ�־�����\n");
	skill=me->query_skill("luohan-quan",1);

	message_vision(MAG"$N" MAG "Σ��֮�У�������ת�ɺ����ƣ�˫�ƾٹ���ǣ����ֻ��������ֻ���ңң��ԣ�ȴ���޺�ȭ�е�һ�С�"HIG"˫Ȧ��"MAG"����ʽ��\n"
	+"��һ��������ɽ�����в����Խ⡣����$n����һ��λ��Ϯ��ȫ��$N�ġ�"HIG"˫Ȧ��"MAG"������֮�¡�\n" NOR,me,target);


    me->add_temp("apply/parry",skill/4);
	me->set_temp("lhq/shuang",skill);
	//call_out("remove_shuang",1,me,(int)skill/50);
	remove_shuang(me,skill/50);
 
	me->add("neili",-100);
	me->add("jingli",-60);
	me->start_perform(2,"˫Ȧ��");
	return 1;
}
int remove_shuang(object me,int count)
{
	int skill;
	if (!me) return;
	skill=me->query_temp("lhq/shuang");
	if (me->is_busy()
		||!me->is_fighting()
		||me->query_skill_mapped("cuff")!="luohan-quan"
		||me->query_temp("weapon")
		||me->query_skill_prepared("cuff")!="luohan-quan")
	{
		message_vision(MAG"$N����һ��������ȥ��˫Ȧ�ֵķ���������\n"NOR,me);
		me->add_temp("apply/parry",-skill/4);
		return 1;
	}
	call_out("remove_shuang",1,me,count--);
}
string perform_name(){ return HIR"˫Ȧ��"NOR; }

int help(object me)
{
        write(HIG"\n�޺�ȭ֮"+HIR"��˫Ȧ�֡���"NOR"\n\n");
        write(@HELP
	�����޺�ȭ�������������似��Ѱ��ɮ�˽Կ�ѧ��
	����ΪҪ�������ŵ�����������ȭ������ԭ����
	���������ֲ����Ż��Ƴ³��£���Ȼ��ʽ��ͨ����
	���̺�����ѧԭ����С������������ǧ��
	������Ѱ����ʽ������Ҳ��޴�
	˫Ȧ����˫��һ��һ�����γ�һ�����֣����Է����
	���ڣ��Է�һ����������˳�ƾ�����ת���ǵ��͵�
	���ط�������ʽ��������ѧ����������֮����Ҫ��
	������̷�������
	
	ָ�perform cuff.jinglan

Ҫ��
	��ǰ�������� 200 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 200 ���ϣ�
	����ȭ���ȼ� 100 ���ϣ�
	�����ڹ��ȼ� 100 ���ϣ�
	�޺�ȭ���ȼ� 100 ���ϣ�
	����ȭ���ұ��޺�ȭ��
	���������ڹ���
HELP
        );
        return 1;
}