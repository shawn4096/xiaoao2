// �ϻ����
// by Looklove@SJ
// Update By lsxk@hsbbs 2007/6/11

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
   int i, j, p, flag;
   i = (int)me->query_skill("qishang-quan", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("���ϻ���ǡ�ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�á��ϻ���ǡ���\n");

    if( (int)me->query_skill("qishang-quan", 1) < 520 )
		return notify_fail("�������ȭ��������죬ʹ�������ϻ���ǡ�������\n");

    if(!me->query_skill("jiuyang-shengong", 1) || (int)me->query_skill("jiuyang-shengong",1)<520)
    if( (int)me->query_skill("force", 1) < 520 )
           return notify_fail("��Ļ����ڹ��ȼ���������ʹ�������ϻ���ǡ�������\n");

    if( (int)me->query_skill("cuff",1) < 520 )
		return notify_fail("��Ļ���ȭ���ȼ�����������ʹ�á��ϻ���ǡ���\n");

    if( me->query_str() < 80 )
		return notify_fail("�������������ǿ����ʹ�������ϻ���ǡ�����\n");

	if( me->query_skill_prepared("cuff") != "qishang-quan"
	 || me->query_skill_mapped("cuff") != "qishang-quan")
		return notify_fail("�������޷�ʹ�á��ϻ���ǡ���\n");


	if( me->query_skill_mapped("parry") != "qishang-quan"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("����Ҫ�����м�Ϊ����ȭ������ʹ�á��ϻ���ǡ���\n");


    if ( me->query_temp("qsq/duanhun"))
		return notify_fail("������ʹ�á��ϻ���ǡ���\n");

    if( (int)me->query("max_neili") < 15000)
		return notify_fail("�������̫����ʹ�������ϻ���ǡ���\n");

    if( (int)me->query("neili") < 1500 )
		return notify_fail("����������̫����ʹ�������ϻ���ǡ���\n");

    if( (int)me->query("jingli") < 1500 )
           return notify_fail("������̫���ˣ�ʹ�������ϻ���ǡ���\n");

	message_vision(HBRED+HIG"\n$N���һ�����ϻ���ǡ��������������˶ϻ���Ǹ����������ȭ�ⷢ�ӵ����쾡�£����һ��ȫ��������У���\n"NOR,me);

    if( me->query_skill_mapped("force") == "jiuyang-shengong" && userp(me)||me->query("mjqkdny/pass"))
      {
		flag=1;        
		}
    else flag = 0;

	p = me->query_skill("qishang-quan", 1) / 70;
	if ( p > 7 ) p = 7;

	if (!me->query_skill("jiuyang-shengong", 1)&&!me->query("mjqkdny/pass"))
		if ( p > 5 ) p = 5;

   i = i/5*3 + (int)me->query_skill("jiuyang-shengong", 1)/5*2;   

   j = i/(8-p);                //��9yang��1/2,������1/3

	if ( i > 300 && p>4 )
		j = to_int( i/3.0 * i/ 300.0);  // 9yang 300��С��

   if(userp(me) && !userp(target)) target->add_busy(1);
   
   me->add_temp("apply/cuff", j/2);
   me->add_temp("apply/attack", j/2);
   me->add_temp("apply/damage", j/2);
   
   if (wizardp(me))
   {
	   write("j="+j);
   }

 

   if(me->query_skill("jiuyang-shengong",1)>450 || me->query("mjqkdny/pass"))
	me->set_temp("qsq/duanhun",p);
//no1
    
	COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);

	if ( me->is_fighting(target) && p > 1)
           COMBAT_D->do_attack(me, target, 0,  userp(me)?3:1);
	
	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);

	if ( me->is_fighting(target) && p > 2)
           COMBAT_D->do_attack(me, target, 0,  userp(me)?3:1);

	if ( me->is_fighting(target) && p > 4)
           COMBAT_D->do_attack(me, target, 0, (flag==1)?3:1);
	//Ǭ�����˶�һ��
    if ( me->is_fighting(target) && me->query("mjqkdny/pass")&&me->query_skill("qiankun-danuoyi",1)>450)
	{
           message_vision(HBBLU"$N�����߲�Ǭ����Ų������ʹ������ȫ����������һȭ���������һƬ��Х֮����\n"NOR,me,target);
		   target->set_temp("must_be_hit",1);
		   target->add_temp("apply/damage",me->query_skill("qiankun-danuoyi",1)/4);
		   COMBAT_D->do_attack(me, target, 0, 3);
		   target->add_temp("apply/damage",-me->query_skill("qiankun-danuoyi",1)/4);
		   target->delete_temp("must_be_hit");
	}
	//���������ٶ�һ��
	if ( me->is_fighting(target) && me->query("mj/jiuyang/pass")&&me->query_skill("jiuyang-shengong",1)>450)
	{
           message_vision(HBRED"$N�������ڻ��ͨ������ȭ������������������ȭ���������Դ�ɡ�\n"NOR,me,target);
		   target->set_temp("must_be_hit",1);
		   target->add_temp("apply/damage",me->query_skill("jiuyang-shengong",1)/4);
		   COMBAT_D->do_attack(me, target, 0, 3);
		   target->add_temp("apply/damage",-me->query_skill("jiuyang-shengong",1)/4);
		   target->delete_temp("must_be_hit");
	}

    me->add_temp("apply/cuff", -j/2);
    me->add_temp("apply/attack",-j/2 );
    me->add_temp("apply/damage", -j/2);
	
  
	me->delete_temp("qsq/duanhun");
    me->add("jingli", -100*p);
    me->add("neili", -200*p);
    me->start_busy(random(3));
    me->start_perform(5+ random(1),"���ϻ���ǡ�");
	return 1;
}

string perform_name(){ return HBRED+HIY"�ϻ����"NOR; }
int help(object me)
{
	write(HIR"\n����ȭ֮���ϻ���ǡ�"NOR"\n");
	write(@HELP
	ԭ��Ϊ����ɴ����书���������̽�ëʨ��лѷ���
	������ȭ�ס��ų������������ɡ���ȭ����ȭʱ����
	�Ӻգ�һȭ�����߹ɲ�ͬ�ľ���������͡������ᡢ
	��������ᣬ�������иգ���������ֱ�ͣ�������
	���˵ֵ���ס��ԴԴ�����ľ���������������ˡ�л
	ѷ���Դ�ȭ����������ɮ�ռ���ʦ����������ȭ����
	����δ�黯���������������Լ����м����˺�������
	����������������ľˮ�������У�һ�����ˣ����߽�
	�ˡ�������ν�����ˡ����������˼��������ˡ�
	���ϻ���ǡ����ڶ�ʱ���������������У����б���
	�Ĵ򷨣������޴�
	ע�⣺����ȭ�⿪Ǭ����Ų���ںϺ;����񹦺���
	�ұ����书����лѷ͵������似�����豾���ڹ�

	ָ�perform cuff.duanhun

Ҫ��
	����������� 15000 ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	����ȭ���ȼ� 520 ���ϣ�
	�����ڹ��ȼ� 520 ���ϣ�
	������������ 80 ���ϣ�
	����ȭ��Ϊ����ȭ��
	�����м�Ϊ����ȭ��Ǭ����Ų�ƣ�
	��ȭ��Ϊ����ȭ�ҿ��֡�
HELP
        );
        return 1;
}