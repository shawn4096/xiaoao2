//cre by sohu@xojh 2013
#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me,object target)
{
        object weapon;
        string msg;
        int i = me->query_skill("huifeng-jian",1);

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("���𽣡�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (!me->query("em/mie/pass"))
                return notify_fail("����δ�õ����ʦ̫�Ĵ��ڣ��޷�ʹ�á��𽣡�������\n");
        if(me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("����ڹ����Ƕ����ķ����޷�ʹ�á��𽣡�������\n");
        if( me->query_skill("linji-zhuang", 1) < 350 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á��𽣡�������\n");
        if( me->query_skill("huifeng-jian", 1) < 350 )
                return notify_fail("��Ľ�����δ���ɣ�����ʹ�á��𽣡�������\n");
        if (!objectp(weapon = me->query_temp("weapon")) 
			|| weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("������û�н����޷�ʹ�á��𽣡�������\n");

        if(me->query_skill_mapped("parry") != "huifeng-jian")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�á��𽣡�������\n");
        if(me->query("max_neili") < 5000 )
                return notify_fail("���������Ϊ����������ʹ�á��𽣡�������\n");
        if(me->query("neili") < 2000 )
                return notify_fail("�������������㣬����ʹ�á��𽣡�������\n");
        if(me->query("jingli") < 1500 )
                return notify_fail("�����ھ������㣬����ʹ�á��𽣡�������\n");
        if(target->query_temp("em/mie"))
                return notify_fail("�Է��Ѿ�������ġ��𽣡����������ֽ����ɡ�\n");
        if(me->query_skill("sword", 1) < 350 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ������ķ���\n");
		//if( !userp(me) )
              //  return notify_fail(me->query("name")+ "��һ��npc��ɶ�𽣡�\n");
        if( me->query_temp("em/mie") )
               return notify_fail(me->query("name") + "����ʹ���𽣾�����\n");
	
        msg = HBRED+YEL"$NƮ�����ʹ���ط���������𽣡���������ʱ�������Ʈ�ݣ�����ǧ�������裬����ͷ����������\n"NOR;
        
        if(random(me->query("combat_exp"))>target->query("combat_exp")/3
			||random(me->query_int())>target->query_int()/2) {
                msg += HIG "���$n���һ��������֮��������������$N���˸����ֲ�����\n" NOR;
                me->set_temp("em/mie",1);
				target->add_busy(2);
				if (me->query_skill("huifeng-jian",1)>350)
                  target->add_busy(1);
				if (me->query_skill("huifeng-jian",1)>450)
                  target->add_busy(1+random(2));
				if (me->query_skill("huifeng-jian",1)>550)
                  target->add_busy(1+random(2));
				if (me->query_skill("jiuyin-zhengong"))
				{
					//write("1111");
					msg += HBBLU+HIW "$N��������澭�ϵ��ڼҹ��������𽣡���ʽ���޼���Ѱ,����������\n"NOR;
					i+=me->query_skill("linji-zhuang",1)/3+me->query_skill("jiuyin-zhengong",1);
					target->apply_condition("no_exert",1+random(1));
					//i/=2;				
				}
				//�Դ����̵����ж���ɱ��
				if (target->query("family/family_name")=="����"&&!userp(target))
				   i+=i/6;
				//ϴ������������
				if (me->query("clas")=="bonze"&&me->query("gender")=="Ů��"&&me->query_per(1)>35)
				{
					i+=i/5;
				}
				if (!target->query_temp("em/mie"))
				{				
					target->add_temp("apply/attack", -i);
					target->add_temp("apply/parry", -i);
					target->add_temp("apply/dodge", -i);
					target->add_temp("apply/armor", -i);					
					target->set_temp("em/mie",i);
				}
                call_out("remove_effect", 1, target, i/100);
        }
        else {
                msg = msg + MAG "����$n�侲�Ƿ���˿����Ϊ����õ���������������ֵ�����©���������\n" NOR;
				me->add_busy(1);
		}
        if (me->query_skill("huifeng-jian",1)<450)
        {
			me->start_perform(2+random(2),"���𽣡�����"); 
        }
		me->add("neili",-300);
		me->add("jingli",-200);

		me->delete_temp("em/mie");
		message_vision(msg, me, target);
        return 1;
}
void remove_effect(object target, int count)
{
        int i;
		if (!target) return;

		
	    i=target->query_temp("em/mie");
	 
		if (!target->query_temp("em/mie")) return;
		
        if (count<0)
		{
            tell_object(target, HIY"���𽥻ָ������С��𽣡�����������״̬��\n"NOR);
			//tell_object(me,target->query("name")+HIY"�𽥻ָ�����������ʩչ���𽣡�����������״̬��\n"NOR);
            target->add_temp("apply/attack", i);
            target->add_temp("apply/dodge", i);
            target->add_temp("apply/parry", i);
			target->add_temp("apply/armor",i);

            target->delete_temp("em/mie");
			return;
        }
		call_out("remove_effect",1,target,count-3);
		return;
   
}

string perform_name(){ return HBRED+YEL"�𽣾���"NOR; }

int help(object me)
{
        write(HBRED+HIY"\n�ط������֮���𽣾�������"NOR"\n\n");
        write(@HELP
	�ط���������Ƕ�ü����֮�أ���ɽ��ʦ����������ʱ�ھ���
	��Ϊ�ḻ�������ǳ�������һ���������ϣ���ϼҴ���ѧ��
	�书���輫Ϊ��񡣺�������������ã�������������ʮ��
	��󳹴��򣬳���Ϊ�ᣬ������ü��ѧ--�ط��������
	�������ҵ��������������ʦ̫���У������ԭ�����ʦ̫
	���ط�����������󣬸���ʦ�ֹº��ӵĲ���������ʹ����
	��ʦ̫������������Ҫ�ľ������𽣺;���������
	���𽣾�����ƾ��ḻս�����飬������Чѹ�ƶ��֣������
	ʦ̫��ϲ�����ӣ������ҳ��ڶ�ü������𷨵ĵ����ж����
	��������Ե�ɺϣ�ϰ�ö�ü��ѧ�����澭�ٳ�ƪ��������
	������һ��¥,450�����ɡ�ע���������׵�Ů�������ʦ̫
	����������
		
ָ�perform sword.mie

Ҫ��
	��ǰ���������� 2000 ���ϣ�
	������������� 5000 ���ϣ�
	��ǰ���������� 1500 ���ϣ�
	�ط�������ȼ� 350 ���ϣ�
	�ټ�ʮ��ׯ�ȼ� 350 ���ϣ�
	�����ڹ�Ϊ�ټ�ʮ��ׯ��
	��������Ϊ�ط��������
	�����м�Ϊ�ط��������
	�ֳֽ��������

HELP
        );
        return 1;
}


