// benlei.c ���׽���
#include <ansi.h>
//�����б��׾�---by daidai 2007-06-26
inherit F_SSERVER;
void remove_effect(object me, int count);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time, lvl;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
            return notify_fail("�����׾���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
            return notify_fail("��ʹ�õ��������ԡ�\n");
        if( me->query_skill("xunlei-jian",1) < 200 )
            return notify_fail("���Ѹ�׽������������ʹ���������׾�����\n");
        if( me->query_skill("force",1) < 200 )
            return notify_fail("��Ļ����ڹ����������ʹ���������׾�����\n");
        if( me->query_skill_mapped("sword") != "xunlei-jian")
		//	||me->query_skill_mapped("parry") != "xunlei-jian" )
          return notify_fail("������û����Ѹ�׽����޷�ʹ��������У�\n");
        if( me->query_skill("xuantian-wuji",1) <200)
            return notify_fail("�㲻�������޼��ڹ�֧�����޷�ʹ��������еģ�\n");
        
        if( me->query_temp("xlj/benlei") )
               return notify_fail("�������Ѿ��������ʹ�á����׾����ˡ�\n");
       
        if( me->query("max_neili", 1) < 3000 )
               return notify_fail("������������Ϊ����ʹ�á����׾�����\n");
        if( me->query("jingli") < 500 )
			return notify_fail("��ľ�����Ϊ����ʹ�á����׾�����\n");
	 	if( me->query_dex() < 40 )
			return notify_fail("��ĺ�����Ч����Ϊ����ʹ�á����׾�����\n");
        if( me->query("neili")<500)
            return notify_fail("�������������\n"); 
   
		msg = HBMAG "$N����"+weapon->name()+HBMAG"�������죬����ָ�죬ͻȻ���ΰθߣ�����$n��Ӧ������������$n��ȥ��\n"NOR;
        message_vision(msg, me, target);
        if (me->query("quest/kl/xlj/wuxue/pass"))
        	lvl = me->query_skill("xunlei-jian", 1) + me->query_skill("xuantian-wuji", 1)/ 6;
        else lvl=me->query_skill("xunlei-jian", 1);

		lvl = lvl/8;
		me->set_temp("xlj/benlei", lvl);
        
		me->add_temp("apply/damage", lvl/3);
        me->add_temp("apply/sword", lvl);
        me->add_temp("apply/attack", lvl);
        
        if (me->query_skill("xunlei-jian",1)<300)
			me->start_perfrom(2,"�����׾���");
        me->add("neili", -300);
        me->add("jingli", -80);
       
        call_out("remove_effect",0,me,(int)lvl/10);
        return 1;
}

void remove_effect(object me,int count)
{
        int lvl;
		object weapon;
		if (!me) return;
		lvl =(int)me->query_temp("xlj/benlei");
		weapon=me->query_temp("weapon");

        if (count < 0 
			|| !me->is_fighting()
			|| !weapon
			|| weapon->query("skill_type")!="sword"
			|| me->query_skill_mapped("parry")!="xunlei-jian"
			|| me->query_skill_mapped("sword")!="xunlei-jian")
        {      
			me->add_temp("apply/damage", -lvl/3);
			me->add_temp("apply/sword", -lvl);
			me->add_temp("apply/attack", -lvl);
			me->delete_temp("xlj/benlei");

			message_vision(MAG"$N�ı��׹��ƽ���������������������һ��������\n"NOR,me);
			return;
		}
		call_out("remove_effect",1,me,count -2);
		return;

}
string perform_name() {return HIW"���׾�"NOR;}

int help(object me)
{
    write(HIY"\nѸ�׽�����"HIW"���׾�"WHT"����"NOR"\n");
    write(@HELP
	Ѹ�׽��������صĳ����������ɺ����������ر仯���á�
	������ɽ��ߵغ����ױ������Ķ࣬�ɴ����򽣷��Ŀ��
	���⣬��Ҫ�������֧�֡�
	Ѹ�׾���Ѹ�׽�������Ҫ�ĸ��������似����ҿ����Լ�
	��Ҫ��ϸ���,300����С�ɣ�ȡ��busy��

	ָ�perform benlei
	
Ҫ��
	�����ڹ��ȼ� 200 �����ϣ�
	Ѹ�׽����ȼ� 200 �����ϣ�
	��Ч���ȼ� 40    ���ϣ�
	���������ȼ� 200 �����ϣ�
	�������Ҫ�� 3000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��������Ѹ�׽���
	�ڹ����ޣ�
	���ֳֽ���������    

HELP
	);
	return 1;
}

