// tiejiao.c  ����
// Modified by sohu@xojh
//������̷�������

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIR"������"NOR; }

int perform(object me, object target)
{
        int lvl,damage;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�����ɾ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("��������ʹ�á������ɾ�������\n");
        if( !me->query("quest/qz/yylht/tiejiao/pass") )
               return notify_fail("��ֻ����˵����������ʽ��Ŀǰ�޷�ʹ�á������ɡ�������\n");

		if( (int)me->query_skill("yuanyang-lianhuantui", 1) < 300 )
                return notify_fail("���ԧ�������˲�����죬�޷�ʩչ�������ɾ�����\n");
        if ((int)me->query_skill("xiantian-gong", 1) < 300)
                return notify_fail("������칦��򲻹����޷�ʩչ�������ɾ�����\n");
		if ((int)me->query_skill("leg", 1) < 300)
                return notify_fail("��Ļ����ȷ���򲻹����޷�ʩչ�������ɾ�����\n");
 
        if ( (int)me->query("max_neili") < 4000)
                return notify_fail("�����������������޷�ʩչ�������ɾ�����\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ�������ɾ�����\n");
        if (me->query_skill_prepared("leg") != "yuanyang-lianhuantui"
            || me->query_skill_mapped("leg") != "yuanyang-lianhuantui")
                return notify_fail("�������޷�ʹ�������ɾ������й�����\n");
        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("�����ɾ�����Ҫ���칦����������\n");
        if (me->query_temp("yylht/tiejiao"))
                return notify_fail("������ʹ�������ɾ�����\n");
        
		lvl = me->query_skill("yuanyang-lianhuantui",1);
		damage=lvl+me->query_skill("xiantian-gong",1)/2;
		damage=damage*3+random(damage);

		message_vision(HBYEL+HIW "$N�����³������칦������˫��������������һ�������أ����ǡ������ɡ�������\n"NOR,me, target);


		me->add_temp("apply/attack",lvl/4);
		me->add_temp("apply/damage",lvl/6);
		me->add_temp("apply/leg",lvl/5);

        me->set_temp("yylht/tiejiao",lvl);

		call_out("remove_attack", 1, me);
        return 1;
}

void remove_attack(object me)
{
        int lvl;
        if (!me) 
return;
		lvl=me->query_temp("yylht/tiejiao");

		if (!me->is_fighting()
			||me->query_skill_mapped("leg")!="yuanyang-lianhuantui"
			||me->query_skill_prepared("leg")!="yuanyang-lianhuantui")
		{
			me->add_temp("apply/attack",-lvl/4);
			me->add_temp("apply/damage",-lvl/6);
			me->add_temp("apply/leg",-lvl/5);

			me->delete_temp("yylht/tiejiao");
			message_vision(CYN"$N�����³�һ�������������ɾ����������չ���\n"NOR,me);
			return;
		}
		call_out("remove_attack",1,me);
}

int help(object me)
{
        write(HIG"\nԧ��������֮�������ɡ�������"NOR"\n");
        write(@HELP
	ԧ����������ȫ��̵��������书֮һ���ýŷ�
	ȫƾһ�������Ƴ������������һ������������
	�Է�����Է�����ʤ����
	�����ɾ�����ȫ������̷����ĳ�������������
	�����±��ϵ��Ŷ�������Ȼ����Х������Ȼ��
	˿������ƾ��һս������������ԧ�������ŵ���
	Ҫ����������ʽ��

	ָ�perform leg.tiejiao

Ҫ��
	���칦���ĵȼ� 300  ���ϣ�
	ԧ�������ȵȼ� 300  ���ϣ�
	�����ȷ��ĵȼ� 300  ���ϣ�
	��������Ҫ�� 4000 ���ϣ�
	��ǰ������Ҫ�� 500  ���ϣ�
	�����ȷ����м�Ϊ����ԧ���ȣ�
	�����ڹ����칦��
	�����ұ�ԧ��������
HELP
        );
        return 1;
}


