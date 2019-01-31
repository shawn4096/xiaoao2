// chuang.c ������
// sohu@xojh
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage;
	string msg;
        int ap, dp;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("�������֡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("luohan-quan", 1) < 100)
		return notify_fail("����޺�ȭ��������죬���ڻ��޷�ʹ�á������֡���\n");
	if (me->query_skill("cuff", 1) < 100)
		return notify_fail("��Ļ���ȭ��������죬���ڻ��޷�ʹ�á������֡���\n");
  	if (me->query_skill("force", 1) < 100)
		return notify_fail("��Ļ����ڹ�������죬���ڻ��޷�ʹ�á������֡���\n");  
	if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
           // me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ�������֡���\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�����������������޷����á������֡���\n");
	if ((int)me->query("jingli") < 200)
		return notify_fail("�����ھ����������޷����á������֡���\n");			
	
	if (me->query_skill_mapped("cuff") != "luohan-quan"
		||me->query_skill_prepared("cuff") != "luohan-quan") 
		return notify_fail("��û�м����޺�ȭ���޷�ʹ�ô����־�����\n");

	message_vision(HIY "$N" HIY "˫ȭ���գ�վ�ɹ���������ƣ����һ����˫ȭѸ������һʮ���У�ȭ���Х�������޺�ȭ�С������֡�����ʽ��\n" NOR,me,target);

        ap = me->query_skill("cuff",1);
        dp = target->query_skill("parry",1);
    if (ap / 2 + random(ap) > dp || !living(target))
	{
		damage = me->query_skill("luohan-quan",1)*me->query_str(1)/10;
		damage=damage+random(damage);
		//COMBAT_D->do_chemis_attack(me,ob,1,damage);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/5,me);
		me->add("neili", -30);
		message_vision(HIR"ֻ��$n" HIR "һ���м�ʧ�󣬵�ʱ����ȭ���˸����ţ��ƺ�һ��������������\n" NOR,me,target);
		target->add_busy(2);
	} else 
	{
		message_vision(CYN "����$p" CYN "����һ�񣬼�ס��$P"
                       CYN "����ȭ��\n" NOR,me,target);
		me->add("neili", -10);
		me->start_busy(1);
	}
	me->add("neili",-100);
	me->add("jingli",-60);
	me->start_perform(2,"������");
	return 1;
}
string perform_name(){ return HIC"������"NOR; }

int help(object me)
{
        write(HIG"\n�޺�ȭ֮"+HIC"�������֡���"NOR"\n\n");
        write(@HELP
	�����޺�ȭ�������������似��Ѱ��ɮ�˽Կ�ѧ��
	����ΪҪ�������ŵ�����������ȭ������ԭ����
	���������ֲ����Ż��Ƴ³��£���Ȼ��ʽ��ͨ����
	���̺�����ѧԭ����С������������ǧ��
	������Ѱ����ʽ������Ҳ��޴�
	
	ָ�perform cuff.chuang

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