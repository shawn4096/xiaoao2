//COOL@SJ 200001009 add yyz liao yyz_hurt
#include <ansi.h>

string exert_name() {return HIC"��������"NOR;}

int exert(object me, object target)
{
	int i;
	if( !objectp(target) )
		return notify_fail("��Ҫ��һ��ָΪ˭���ˣ�\n");

	if (target->is_corpse() || !target->is_character())
		return notify_fail("�ǲ��ǻ���Ү��\n");

	if (target->is_busy())
		return notify_fail("�Է�����û�пս���������ˡ�\n");

	if((int)me->query_skill("force") < 250 )
	      return notify_fail("���Ǭ��һ����������죬�޷��������ˣ�\n");

	if((int)me->query_skill("yiyang-zhi",1) < 250 )
	      return notify_fail("���һ��ָ�񹦲�����죬�޷��������ˣ�\n");

	if (me->query_skill_prepared("finger") != "yiyang-zhi"
	|| me->query_skill_mapped("finger") != "yiyang-zhi")
		return notify_fail("�������޷�ʹ��һ��ָ�������ˣ�\n");

	if( me->is_fighting() && target != me)
		return notify_fail("ս�����޷���������ˣ�\n");

        if( target->is_fighting()&&target != me)
                return notify_fail("�Է�����ս�����޷��������ˣ�\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("���������Ϊ������\n");

	if( (int)me->query("neili") < 400 )
		return notify_fail("�������������\n");

	if((int)me->query_skill("medicine", 1) < 120 )
	       return notify_fail("���������ҽ��֪ʶ��֪���٣���֪�������? \n");

	if (!target->query_condition("yyz_hurt")
	&& target->query("eff_qi") >= target->query("max_qi"))
		return notify_fail( target->name() + "��û�����ˣ�\n");
    if (me->query_temp("yideng/ronghe")=="pass")
    {
		i=me->query_skill("qiantian-yiyang",1)+me->query_skill("jingmai-xue",1)+me->query_skill("medicine",1);
		message_vision(HIC"$N������ת����,������������\n"NOR,me);
    }
	else i=me->query_skill("qiantian-yiyang",1)/2;
	if (me->is_fighting()) {
		message_vision(
			HIY"\n$N�ֱ۲������������ѵ�ˮ��һ����������Լ��ؿڵ�ʮ������Ѩ��������������͸�롭��\n\n"
			HIM"ֻ��Ƭ��֮�䣬$N��ɫ�����˺��Σ����ƺö��ˡ�\n" NOR, me);
		if (target->query_condition("yyz_hurt")) target->clear_condition("yyz_hurt");
		if ((int)target->query("eff_qi") < (int)target->query("max_qi"))
		{
			me->add("neili",-me->query_skill("force",1)/3);
			me->receive_curing("qi", i );
			me->receive_heal("qi", i );
		}
		me->start_exert(6-i, "����");
	} else {
		target->start_busy(2);
	    if (target != me){
			me->start_busy(2);
	    		message_vision(HIY"\n$N�������ʳָ��΢һ������������������, ʳָ���Ρ���������Ѩ���˵���������$n�ؿڵ����д�Ѩ�ϣ���������ԴԴ͸�롣����\n\n"
			   	HIM"\n$Nͷ��ð��˿˿������$n�о�һ������ƽ�͵�����������ѭ������������һյ��ʱ�֣�$N�ŷſ���ָ��ֻ��Ƭ��֮�䣬$n˫��\n"
			   	HIM"�����˺��Σ���ɫ������Ҳ�ö��ˡ�\n" NOR,me,target);
		}
		else
	   		message_vision(HIY"\n$N�������£�΢һ������ʳָ���Ρ���������Ѩ���˵����ʳָһ�գ����ư����ؿ����д�Ѩ����������ԴԴ͸�롣����\n\n"
				HIM"$Nͷ��ð��˿˿����������һյ��ʱ�֣��ŷſ���ָ,$N����ɫ������Ҳ�ö��ˡ�\n" NOR,me);
	   	if( (target != me)
	    	&& userp(target)
	    	&& target->query("eff_qi") < target->query("max_qi")/5) {
	     		if (!random(4)) me->add("max_neili",-1);
	     		me->add("yyz_cure",1);
		}
		if (target->query_condition("yyz_hurt")) target->clear_condition("yyz_hurt");
		if (target->query("eff_qi") < target->query("max_qi"))
		{
		   	me->add("neili", -me->query_skill("force")/2);
	   		target->receive_curing("qi", i );
	   		target->receive_heal("qi", i );
	   		me->start_busy(3);
	   		target->start_busy(3);
	 	}
	}
	return 1;
}

int help(object me)
{
        write(HIY"\nǬ��һ��֮�����˾�����"NOR"\n\n");
        write(@HELP
	�����׼��ڹ�Ǭ��һ�����Ǵ��������似�ĺ��Ļ��������书
	�ʹ���һ��ָ�ศ��ɣ�������á����˾����ǽ���һ��ָ��
	�ص��ַ����Դ����������ˣ��м����Ч����
	Ҫ��
		��ǰ���� 400 ���ϣ�
		������� 2000 ���ϣ�
		�����ڹ� 250 ����
		һ��ָ   250 ����		
		Ǭ��һ�� 250 ����		

HELP
        );
        return 1;
}
