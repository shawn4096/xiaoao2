// chuanxin.c ���ĵ�
// edit by sohu@xojh 2015

#include <ansi.h>
//#include <skill.h>
//#include <combat.h>
//#include <weapon.h>
//inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
 
string perform_name(){ return HIC"���ĵ�"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, weaname;
        int lvl,damage,p;


        lvl = (int)me->query_skill("xuedao-daofa",1);
        
        
		target = me->select_opponent();

        if( !me->is_fighting() )
                return notify_fail("�����ĵ���ֻ����ս����ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if((int)me->query_dex() < 28)
                return notify_fail("���������, Ŀǰ������ʹ���������! \n");

        if((int)me->query_skill("dodge",1) < 100)
                return notify_fail("����Ṧ��Ϊ����, ����ʹ�á����ĵ�����\n");
 
        if((int)me->query_skill("xuedao-jing",1) < 100)
                return notify_fail("��ĵ�����Ϊ������ Ŀǰ����ʹ�á����ĵ���! \n");

        if((int)me->query_skill("xuedao-daofa",1) < 100)
                return notify_fail("���Ѫ��������Ϊ������ Ŀǰ����ʹ�á����ĵ���! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("�����ʹ��Ѫ������������ʹ�á����ĵ����ľ�����\n");
		
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("����мܲ��ԣ����뼤������ΪѪ������������������\n");

        if( me->query_skill_mapped("force") != "xuedao-jing" && me->query_skill_mapped("force") != "shenzhao-jing")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��Ѫ����������ִ�������ʹ�������ĵ����ľ�����\n");

        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("���������Ϊ������\n");
        if((int)me->query("neili")<600)
                return notify_fail("�������������\n"); 
        if((int)me->query("jingli")<200)
                return notify_fail("��ľ���������\n"); 

        weaname = weapon->query("name");

		msg = YEL "\n$N��Х���У�����"HIR"�����ĵ���"YEL"�ؾ���ɲʱ����磬���������У���Ȼ��ת\n˫����ס"NOR+weaname+YEL"������ֱ��$n�����ѣ�\n"NOR;
        message_vision(msg,me,target);

        damage=me->query_skill("xuedao-jing",1)+me->query_skill("blade",1)+lvl;
		damage=damage*4;
		damage=damage+random(damage);
		if (damage>4000) damage=3000+random(1000);
		if (damage<1500) damage=1500;

		if (random(lvl)>target->query_skill("parry",1)/2
			||random(me->query("combat_exp"))>target->query("combat_exp")/2)
        {
						
		   msg = RED"$Nӭ���$nһ����ȣ����ţ�����"+weapon->query("name")+RED"��$n�ؿڶԴ�����!\n������Ѫ˲���$n�ؿ����˳������ۼ��ǻ���ˡ�\n"NOR;
		   p = (int)target->query("qi")*100/(int)target->query("max_qi");
           
		   target->receive_damage("qi", damage,me);
		   target->receive_wound("qi", damage/3,me);
 
		  // target->set_temp("last_damage_from", me);
           
		   msg += damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           msg = replace_string( msg, "$l", "�ؿ�" );
           msg = replace_string( msg, "$w", weapon->query("name"));
		   message_vision(msg, me, target);
		   
		  if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage*4/3+ WHT"�㹥���˺���\n"NOR); 
			
		   if (!userp(target)&&random(target->query("kar")) < 5){
                 message_vision(CYN"$n���������˺�����������˫�۾��ֵؿ���$N,һ�����ģ����ض�����"NOR, me, target);
                 target->die();
           }


        }
		

		me->add_temp("apply/blade", lvl/5);
        me->add_temp("apply/attack", lvl/3);
        me->add_temp("apply/damage", lvl/4);
		me->set_temp("xddf/chuanxin",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("xddf/chuanxin");
		
		me->add_temp("apply/blade", -lvl/5);
        me->add_temp("apply/attack", -lvl/3);
        me->add_temp("apply/damage", -lvl/4);

        me->add("neili", -50-random(200));
        if(me->query("neili")<0) me->set("neili",0);
        me->add("jingli", -80);
        me->start_busy(1);
        me->start_perform(3,"���ĵ�");        
        return 1;
}

int help(object me)
{
	write(RED"\nѪ������֮�����ĵ�����"NOR"\n\n");
        write(@HELP

	���ľ�����Ѫ����������似�����Ī��ĵ�������
	�ڽ�ս�����У���Ȼת���Թ���ĽǶȳ�����һ��
	���Ķ������˵��Ƿ���ʤ��������Ѫ���������似��
	ע���Է������һ������Ч����
	
	ָ��: perform blade.chuanxin

Ҫ��
	������� 1200 ���ϣ�
	��ǰ���� 600  ���ϣ�
	��ǰ���� 400  ���ϣ�
	������ 28   ���ϣ�
	�������� 100  ������
	Ѫ����   100  ������
	Ѫ������ 100  �����ϣ�
	��������Ѫ��������
	�����м�ΪѪ���������ջ�������
	�����ڹ�Ѫ������
	װ������������
HELP
        );
        return 1;
}