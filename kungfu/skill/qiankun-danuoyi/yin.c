#include <ansi.h>
inherit F_SSERVER;
int check_fight(object me);
string perform_name(){ return HIG"���־�"NOR; }

int perform(object me,object target,string arg)
{
	//int ski;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("�������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(!me->is_fighting())
		return notify_fail("��û��ս�����أ�\n");

	if(me->query_skill("qiankun-danuoyi", 1) < 400 )
		return notify_fail("���Ǭ����Ų�ƻ�δ�������߲㡣\n");

	if (!me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 400 )
		return notify_fail("���ʥ���񹦵ȼ�������\n");

	if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("��û��ʹ��Ǭ����Ų����Ϊ�мܣ�\n");

	if((int)me->query("neili") < 5000)
		return notify_fail("��Ŀǰ������������\n");
    if (!me->query("mjqkdny/pass"))  //�ںϺ�Ǭ����Ų�ƽ�������Ծ
    {
		if((int)me->query_temp("qkdny/yi") )
		    return notify_fail("������ʩչ���ơ��־��أ�\n");
	    if((int)me->query_temp("qkdny/xu") )
		    return notify_fail("������ʩչ����־��أ�\n");
    	if((int)me->query_temp("qkdny/hua") )
	    	return notify_fail("������ʩչ�������־��أ�\n");
        me->start_perform(1, "���־�");
		//ski=150;
    }
	
	if((int)me->query_temp("qkdny/yin") )
		return notify_fail("������ʩչ�������־��أ�\n");

	if(target->query_temp("qkdny/yin"))
		return notify_fail( target->query("name") +"����ʹ�á������־��ء�\n");

	me->add("neili", -400);
	tell_object(me,HIG"\n������Ǭ����Ų���ķ��������˹�����ʹ�á������־�������רעǣ����\n"NOR);
	me->set_temp("qkdny/yin", 1);
	//me->set_temp("lost_attack", 1);
	//if (me->query_skill("qiankun-danuoyi",1)<450)
	  // me->start_perform(2, "���־�");
	me->add_temp("apply/dodge", -150);
	me->add_temp("apply/parry", -150);
	check_fight(me);
	return 1;
}

int check_fight(object me)
{
	if (!me || !me->query_temp("qkdny/yin")) return 0;

	if(me->is_ghost() 
	 || !living(me)
	 || !me->is_fighting()
	 || (me->query("jingli") < 500)
	 || (me->query("neili") < 500)
	 || (me->query("jing") < 500))
	 {
		tell_object(me, HIG"\n�㽫Ǭ����Ų�����־������������չ���\n"NOR);		
		me->add_temp("apply/dodge", 150);
		me->add_temp("apply/parry", 150);
		me->delete_temp("qkdny/yin");
	 }
	else {
		//me->set_temp("lost_attack", 1);
		call_out("check_fight", 1, me);
	}
	return 1;
}

int help(object me)
{
        write(HIG"\nǬ����Ų�ơ����־���"NOR"\n");
        write(@HELP
	�����������ǡ������޼ɵ������书������ԭ���̵Ľ�����ϰ�á�
	����Դ�Բ�˹�ݻ�̣������֮������ѧ�����Ԫ����仯��
	�棬�������������۷���书���˹����߲㾳�磬���Ը�����ϰ��
	��һ�������꣬�ڶ���ӱ�������������ѣ��������߱���ֻ��
	�������㣬ϰ�����߲���ʵ�ǹ���������һ�ˡ���Ҫ�оŴ��ܣ�
	�����������Ǳ�������书�����ɣ���������������������
	ճס������ǣ��Ų�Ƶо����������֣�ת��������������������
	�ȡ�
	�ر�ע�⣺���⿪Ǭ����Ų�Ƶĵ��߲���ʱ��Ǭ����Ų�ƿ���
	����ʹ�ø�������,
	
	perform parry.yin

Ҫ��
	��ǰ���� 5000 ���ϣ�
	Ǭ����Ų�Ƶȼ� 400 ���ϣ�
	�����ڹ��ȼ� 400 ���ϣ�
	ʥ���񹦵ȼ� 400 ���ϣ�
	�����м�ΪǬ����Ų�ơ�
	�����ںϺ�������Ծ��
HELP
        );
        return 1;
}
