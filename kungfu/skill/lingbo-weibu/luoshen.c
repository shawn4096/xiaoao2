// By sohu@xojh ����
#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
       	string msg;
       	int i;
		object target;
	
		if(!target)
			target = offensive_target(me);
		if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("����ڹ���������򣬲���350,ʹ��������\n");  
       	if( (int)me->query_skill("lingbo-weibu",1) < 350 )
                return notify_fail("����貨΢�����������ʹ��������\n");  
       	if( (int)me->query("max_neili",1) < 5000 )
                return notify_fail("���������Ϊ���������ʹ��������\n");  
       	if( (int)me->query("jingli", 1) < 1500 )
                return notify_fail("�����ھ���������\n");
       	if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("����������������\n");
       	if (me->query_temp("lbwb/ls"))
                return notify_fail("������ʹ������\n");
	     if (!me->query("quest/�����˲�/�书/pass"))
			 return notify_fail("����δ�õ��貨΢�������С�\n");
			    

       	message_vision(HIC "$NԽ��Խ�죬ÿһ��̤���������������֮��,��Ϣ���Ų�����ס��ת,ת�ۼ�������һ����\n\n"NOR,me);
		if (me->query("gender")=="����")
		{
       		message_vision(HIW"$N�������������߼����ƮƮ���˵�����̬���ݣ���������!\n\n"NOR,me);
		}else
			message_vision(HIW"$N��ò��������Ѹ���죬Ʈ�������貨΢��������������һ����������̬֮��\n\n"NOR,me);
		
		if (objectp(target)
			&&me->query_skill("qimen-bagua",1)>=200 
			&&(random(me->query_int(1))>target->query_int()/2 || random(me->query_skill("dodge",1))>target->query_skill("dodge",1)/3))
		{
			message_vision(HIR"\n$N�����׾���ʮ���Ե�Ҫ��̤������λ�н���˲��ӵ�һ�������һ����������һ����Ȧ��\n\n"NOR,me);
			if (me->is_fighting() && objectp(target))
			{
				message_vision(HBBLU+HIW"$nһ��С��Ϊ$N����ת���������Ի�ɲ�Ǽ���Щʧ��\n\n"NOR,me,target);
				target->add_busy(3+random(2));
			}
		}
       	me->add("neili", -(200+random(300)));
       	me->add("jingli", -(100+random(50)));
       	
		i = me->query_skill("lingbo-weibu", 1)/5 + me->query_int()+me->query_skill("qimen-bagua",1)/10;
       // i = i - random(i/6);
       	if (me->query_skill("lingbo-weibu", 1) < 350)
                i = i/3;
		else if (me->query_skill("lingbo-weibu", 1) < 450)
			 i = i/2;
		
       	me->add_temp("apply/dexerity", i);
       	me->add_temp("apply/dodge", i*2);
		me->add_temp("apply/parry", i);
       	me->add_temp("apply/armor", i);
		me->add_temp("apply/defense", i);

		me->set_temp("lbwb/ls", i);
       	if (me->query_skill("lingbo-weibu",1)<450)
			me->start_perform(1, "����");
		
       	call_out("remove_effect", 1, me, i, i);
       	return 1;
}

void remove_effect(object me, int count,int dex)
{
        if (!me) 
        	return;
        if( me->query_skill_mapped("dodge") != "lingbo-weibu" 
        || me->query("neili") < 100
        || count < 1)
        {
           	me->add_temp("apply/dexerity", -dex);
            me->add_temp("apply/dodge", -dex*2);
			me->add_temp("apply/parry", -dex);
       		me->add_temp("apply/armor", -dex);
			me->add_temp("apply/defense", -dex);
           	
			me->delete_temp("lbwb/ls");
           	message_vision(HIW"$N����һ���������貨΢����������������\n"NOR, me);
           	return;
        }
 		call_out("remove_effect", 1 , me, count -1,dex);
}
string perform_name(){ return HBBLU+HIG"����"NOR; }

int help(object me)
{
	write(HIW"\n�貨΢��֮�����񡹣�"NOR"\n\n");
	write(@HELP
	�貨΢������ң�ɵĶ����Ṧ���������׾��˰���ʮ����
	Ϊ������ʹ���߰��ض�˳��̤������λ�н����ӵ�һ��
	�����һ����������һ����Ȧ���˲��������쳣��ϰ�߿�
	����������ڶ���˵Ľ�����
	�貨΢�����齣�е�һ�Ṧ�����м�ǿ�Ķ�ܹ��ܣ�����
	�������Ű��Ծ�Ҫ������书�����ֽ�������Ծ��
	
	ָ�perform dodge.luoshen

Ҫ��
	��ǰ����Ҫ�� 1500 ���ϣ�
	�������Ҫ�� 5000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	�貨΢���ȼ� 350 ���ϣ�
	�����Ṧ�ȼ� 350 ���ϣ�
	�����ṦΪ�貨΢����    
	ע�⣺set �貨΢�� ���� �����Ṧ���������Ч��
             

HELP
        );
        return 1;
}