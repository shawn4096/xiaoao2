// By Darken@SJ
// BY SOHU@XOJH
#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIG"���ž�"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time, lvl,b;
        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                 return notify_fail("�����ž���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                 return notify_fail("��ʹ�õ��������ԡ�\n");
		if (!weapon->id("xiao"))
		         return notify_fail("������û������޷�ʩչ�������ž�����\n");
        if (!me->query("thd/wuji/yuxiao"))
				 return notify_fail("����δ���򡰱̺���������������У��޷�ʩչ�������ž�����\n");
		if((int)me->query_skill("yuxiao-jian",1) < 100 )
                 return notify_fail("������｣�����������ʹ���������ž�����\n");
        if((int)me->query_skill("qimen-bagua",1) < 100 )
                 return notify_fail("������Ű��Ի��������ʹ���������ž�����\n");
        if((string)me->query_skill_mapped("sword") != "yuxiao-jian" && userp(me))
                   return notify_fail("�������޷�ʹ�á����ž�����\n");
        if((string)me->query_skill_mapped("parry") != "yuxiao-jian" && (string)me->query_skill_mapped("parry") != "tanzhi-shentong"&&userp(me))
                   return notify_fail("�������޷�ʹ�á����ž�����\n");
        if((int)me->query_temp("yuxiao_lian") )
                return notify_fail("�������Ѿ��������ʹ�á����ž����ˡ�\n");
        if((int)me->query("max_neili", 1) < 1000 )
                 return notify_fail("���������Ϊ����ʹ�á����ž�����\n");
        if((int)me->query("max_jingli") < 500 )
                 return notify_fail("��ľ�����Ϊ����ʹ�á����ž�����\n");
        if((int)me->query("neili")<500)
                 return notify_fail("�������������\n"); 
        
        attack_time = me->query_skill("yuxiao-jian",1) / 2;

        if (attack_time < 2)  attack_time = 2;
        if (attack_time > 4)  attack_time = 4;
        if (me->query_temp("thd/is_fast")) attack_time += 2;

        msg = HIG "$N����"+weapon->name()+HIG"���̣��������磬���ж��ǹ��ƣ�һ�в���$n���⿪ȥ�����������������\n"+
                 "$N����һ��������һ�У�����"+chinese_number(attack_time)+"�У�����ѧ������ȫ�෴��\n"+
                 "$n��������������Ҫ������ȫ��"+weapon->name()+HIG"����֮�£�\n"NOR;
		if (random(me->query_skill("qimen-bagua",1) > target->query_skill("qimen-bagua",1)/2)&& weapon->query("skill_tyle")=="xiao")
		{
		   message_vision(HIC"\n$n���Ϻ���һ����ת���������������$n����һƬ�հף��ƺ��������м�һ�㡣\n"NOR,);
		   b=random(me->query_skill("qimen-bagua",1)/100);
		   target->add_busy(1+b);
		}
        message_vision(msg, me, target);
        lvl = me->query_skill("yuxiao-jian", 1) /10 + me->query_skill("qimen-bagua", 1)/ 2;
        me->add_temp("apply/attack", lvl);
        me->add_temp("apply/damage", lvl);
        me->add_temp("apply/sword", lvl);
        me->add("neili", -300);
        me->add("jingli", -80);
        /*
		for(i = 0; i < attack_time; i++)
                if (me->is_fighting(target))
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);*/
        //me->start_perform(4,"�����ž���");
        me->set_temp("yuxiao_lian", lvl);
		call_out("remove_effect",1,me,(int)lvl/10);
        //me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, lvl :), random(attack_time)+4);
        return 1;
}

void remove_effect(object me, int count)
{
        object weapon;
		int lvl;

		if (!me) return;
		lvl=me->query_temp("yuxiao_lian");
		weapon=me->query_temp("weapon");
		if (count<1
			|| !me->is_fighting()
			|| !weapon
			|| !weapon->id("xiao")
			|| me->query_skill("sword")!="yuxiao-jian"
			|| weapon->query("skill_type") != "xiao")
		{

			me->delete_temp("yuxiao_lian"); 
			me->add_temp("apply/attack", -lvl);
			me->add_temp("apply/damage", -lvl);
			me->add_temp("apply/sword", -lvl);
            if (weapon)
				message_vision(HIC"$N���ֽ����е�"+weapon->query("name")+HIC"���˸��������ݲ��ȣ�״��������\n"NOR,me);
			else message_vision(HIC"$N�������˸��������ݲ��ȣ�״��������\n"NOR,me);
			return;
		}
		call_out("remove_effect",1,me,count--);
}

int help(object me)
{
        write(HIG"\n�����ž�����"NOR"\n");
        write(@HELP
	���ž����һ������ص�һ���似���Ų����Ű��Է�λ
	���н�����ȡ���⹥�ƣ�����ֿ��ٹ���֮��������
	����֡���ʱ���ڻ���������Ľ���������
	
	ָ�perform sword.qimen

Ҫ��
	�̺������ȼ� 100 ���ϣ�
	���｣���ȼ� 100 ���ϣ�
	���Ű��Եȼ� 100 ���ϣ�
	������Ű��������г���
HELP
        );
        return 1;
}



