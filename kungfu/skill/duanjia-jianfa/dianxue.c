// Code of xojh
//dianxue.c ����ע���������Խ����Ѩ
//sohu@xojh ���¶�λ�μҽ���Ϊ��ү��ʽ

#include <ansi.h>

inherit F_SSERVER;

void checking(object me,object target,int count);

int perform(object me, object target)
{
        object weapon;
        int skill, skill1, damage;

        if (me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("�����õ��ڹ��ķ����ԣ��޷�����һ��ָ��\n");

        if (!me->query("quest/dl/djjf/yiyang/pass"))
                return notify_fail("��ֻ��֪�����ž���������������δ�ڻ��ͨ��\n");
        
		if (me->query_skill("force",1)<350
                || me->query_skill("qiantian-yiyang",1)<350
                || me->query_skill("duanjia-jian",1)<350 )
                return notify_fail("��Ĺ����������޷����������ķ���\n");

        if (!objectp(weapon = me->query_temp("weapon")) 
			|| weapon->query("skill_type")!="sword")
                return notify_fail("��û��ʹ����ȷ���������޷���һ��ָ�������ϡ�\n");

       if (me->query_skill("jingmai-xue",1)<200)
               return notify_fail("��ľ���ѧ�ȼ��������޷�ʩչ��\n");
        if (me->query_skill_mapped("sword") != "duanjia-jianfa" &&
            me->query_skill_mapped("parry") != "duanjia-jianfa")
                return notify_fail("�㼤���Ľ��в��ԣ��޷�ʹ��һ��ָ���ڱ����ϡ�\n");

        if (me->query("neili") <= 1000)
                return notify_fail("�㵱ǰ������������һ��ָ����\n");

        if (me->query("jingli") <= 1000)
                return notify_fail("�㵱ǰ�ľ���������һ��ָ����\n");

        if (me->query_temp("djjf/yiyang"))
                return notify_fail("������һ��ָָ�����������ˣ�\n");

        message("vision", HIY "\n"+me->query("name")+"����"+weapon->query("name")+"��������,Ƭ������һƬ���졣\n\n" NOR, environment(me), me);
        
		tell_object(me, HIY "\n��������������һ��ָ������ע��"+weapon->query("name")+"�ϡ�\n\n" NOR);



        skill = me->query_skill("qiantian-yiyang",1);
		
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/sword",skill/6);
		me->add_temp("apply/damage",skill/6);

		me->set_temp("djjf/yiyang",skill);
		if (me&&target)
			checking(me,target,skill/35);
        me->add("neili", -300);
        me->add("jingli", -250);

        return 1;
}

void checking(object me,object target,int count)
{
	int skill;
	object weapon;
	if (!me) return 0;
	skill=me->query_skill("duanjia-jianfa");
	if (count<0
		||!objectp(target)
		||me->query_skill("sword")!="duanjia-jianfa"
		||me->query_skill("parry")!="duanjia-jianfa"
		||!me->is_fighting())
	{
		message_vision(YEL"$N��һ��ָ�������չ������������ټ���\n"NOR,me);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/sword",-skill/6);
		me->add_temp("apply/damage",-skill/6);
		return;
	}
	if (random(10)>7)
	{
		switch (random(3))
		{
			case 0:
				message_vision(HIR"$N��һ��ָ�������뽣�⣬һ�ɾ���ֱ͸����������$n�Ĵ�׵Ѩ��\n"NOR,me,target);
				target->add_busy(1);
				break;
			case 1:
				message_vision(MAG"$N��ɫ˲�䳱�죬�����������죬����$n�������Ѩ����Լ��������$n���ؿڣ�\n"NOR,me,target);
				target->apply_condition("no_exert",1);
				target->receive_wound("qi",1000+random(1000),me);
				break;
			case 2:
				message_vision(HIC"$N���ε��ˣ���ת��֮��ͻȻԾ�𣬷����Խ�����������$n�Ĵ����Ѩ��\n"NOR,me,target);
				if (objectp(weapon=target->query_temp("weapon")))
				{
					weapon->move(environment(target));
					message_vision(CYN"$nһʱ���飬���е�"+weapon->query("name")+CYN"�����ڵأ�\n"NOR,me,target);
					
				}
				break;
		}
	}
	call_out("checking",1,me,count--);
     
}       
string perform_name() {return HIY"�Խ���Ѩ"NOR;}

int help(object me)
{
        write(HIR"\n�μҽ���֮���Խ���Ѩ����"NOR"\n\n");
        write(@HELP
	�μҽ������Ǵ���μҽ����ľ��⣬�����˻��壬ͬʱ
	Ҳ��������ʿ�����˴���һ��ָ�����书�⣬��������
	�似�����������Խ���Ѩ���ǽ�һ��ָ�������뵽����
	֮�У��Խ����ס�Է���ѧ���ܷ�����ϰ��
	
	perform sword.dianxue

Ҫ��
	��ǰ�������� 1000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	���������ȼ� 350  ����
	�����ڹ��ȼ� 350  ����
	�μҽ����ȼ� 350  ����
	Ǭ��һ���ȼ� 350  ����
	����ѧ�ĵȼ� 200  ����
	��������Ϊ�μҽ�����
	�����м�Ϊ�μҽ�����
	�����ڹ�ΪǬ��һ����
	���ֳֽ��������

HELP
        );
        return 1;
}
