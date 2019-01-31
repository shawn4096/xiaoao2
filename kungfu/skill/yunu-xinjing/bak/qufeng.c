// qufengshu.c  ������
// cre by sohu@xojh 2014/9
// ģ��С��Ů����ʹ��壬��job�й�

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
	object weapon;
	object ob,yfj;
	string msg;
	weapon=me->query_temp("weapon");
	
	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("��Ҫ��ʹ��乥��˭��\n");
	
	if((int)me->query_skill("yunu-xinjing",1) < 200)
		return notify_fail("����Ů�ľ��Ĺ���������������ʹ���!\n");
	if(!me->query("quest/gm/ynxj/yufeng/pass") )
		return notify_fail("��ֻ����˵��ѵ������������,��ȴû��˿�����鲻����ʹ���!\n");
	if((int)me->query_skill("force",1) < 200)
		return notify_fail("��Ļ����ڹ���Ϊ����,������ʹ���!\n");

	if((int)me->query("neili") < 2000)
		return notify_fail("���������ڲ���, ������ʹ���! \n");
	if((int)me->query("neili") < 800)
		return notify_fail("�㾫�����ڲ���, ������ʹ���! \n");
	if(me->query_skill_mapped("force")!="yunu-xinjing")
		return notify_fail("�㼤�����ڹ�����,������ʹ���!\n");

	if(!present("yufeng jiang",me)&& !me->query("quest/gumu/ynxj/pass"))
		return notify_fail("������û�д������,������ʹ���!\n");
	
	if (me->query_skill("qufengshu",1)<50)
		return notify_fail("�����������δ�������죬����ȥ��С��Ů��̰ɣ�\n");


	if( target->query_temp("ynxj/fengmi") )
		return notify_fail(target->name() + "�����Ѿ������˷��ۣ�\n");

	message_vision(HBYEL+HIW"$N��ת��Ů�ľ����������߷��£���彬����һ�������㣬������Ƣ��������ɢ����ȥ��\n"NOR,me);
	
	call_out("yufeng_come",1+random(3),me,target,);
	
	if (random(me->query_dex(1))>target->query_dex(1)/3)
	{
		message_vision(HIG"$N���ᵯ��һ����ۣ���������ס������$n���ϡ�\n"NOR,me,target);
		target->set_temp("ynxj/fengmi",1);
	}else {
		message_vision(HIC"$n��Ц�������ڹ�����һ������Щ���۵�����\n"NOR,me,target);
		me->add_busy(1);
	}
	me->add("neili",-random(600));
	me->add("jingli",-random(200));
	if (me->query_skill("yunu-xinjing",1)<450) me->start_exert(2,"Ԧ����");
	
	return 1;
}

int yufeng_come(object me,object target)
{
	int i,j;
	object yufeng;
	if (!me||!target) return 0;

	
	i=(int)me->query_skill("qufengshu",1)/50;
	
	
	message_vision(HBYEL"��Ȼ��Զ������һƬ�ܼ�������֮������Ȼ���˴��������,˲�佫$nΧ��������\n"NOR,me,target);
	
	target->apply_condition("bee_poison",1);
	
	for (j=0;j<i;j++ )
	{
		if (present("yufeng jiang",me)) yufeng=new("d/gumu/npc/bee3");
		
		yufeng->move(environment(me));	
		yufeng->set_temp("ynxj/attackname",target->query("id"));
		yufeng->set("owner",me->query("id"));
	}
	return 1;
}

string exert_name(){ return HIY"������"NOR; }

int help(object me)
{
   write(WHT"\n��Ů�ľ�֮��"HIY"������"WHT"����"NOR"\n");
   write(@HELP
	������ǹ�Ĺһ����С��Ů������һ�����ط���
	����������о綾�����Ҿ�С��Ůѵ���󣬸���
	�����Ұ�����ǰ���Χ�Ⱦ������ƣ���֮���м�
	Ϊ��Ч�����ֹ�ʦ֮ͽ����Ϊ������ɽ��С��Ů
	���ף��������ڶ�����֮ͽǰ����Ĺ��С��Ů��
	��������������ˡ�������Ů�ľ���һ�κ󣬿�
	��ƾ�軨���ǿ����ڹ���ʹ����䡣450����ȡ
	��busy
	
ָ�exert qufeng
  
Ҫ��
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 2000 ���ϣ�
	��ǰ����Ҫ�� 2000 ���ϣ�
	��Ů�ľ��ȼ� 200 ���ϣ�
	�������ȼ��� 200 ���ϣ�
	�����ڹ�Ϊ��Ů�ľ�,
	��������ۻ��ʽ�;
	450���ɣ�ȡ��busy��

HELP
   );
   return 1;
}
