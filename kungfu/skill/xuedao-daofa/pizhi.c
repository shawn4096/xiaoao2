// pizhi.c  Ѫ���� [��ֽ����]
// changed by sohu@xojh 2016/7

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
#include <combat_msg.h>
 
string perform_name(){ return HIW"��ֽ"HIB"����"HIC"��"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, weaname;
        int lvl,damage,i,skill;
		lvl=me->query_skill("xuedao-daofa",1);
        if( !me->is_fighting() )
                return notify_fail("����ֽ��������ֻ����ս����ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if((int)me->query_dex() < 28)
                return notify_fail("���������, Ŀǰ������ʹ���������! \n");

        if((int)me->query_skill("blade") < 500)
                return notify_fail("��Ļ���������Ϊ����, ����ʹ�á���ֽ����������\n");
 
        if((int)me->query_skill("xuedao-daofa",1) < 500)
                return notify_fail("���Ѫ��������Ϊ������ Ŀǰ����ʹ�á���ֽ��������! \n");
        
		if(!me->query("quest/xuedao/xddf/pizhi"))
                return notify_fail("����δ����ͨ���ž����� Ŀǰ����ʹ�á���ֽ��������! \n");

        if((int)me->query_skill("xuedao-jing",1) < 500)
                return notify_fail("���Ѫ������Ϊ������ Ŀǰ����ʹ�á���ֽ��������! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("�����ʹ��Ѫ������������ʹ�á���ֽ���������ľ�����\n");
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("����мܲ��ԣ����뼤������ΪѪ������������������\n");

        if( me->query_skill_mapped("force") != "xuedao-jing" &&me->query_skill_mapped("force") != "shenzhao-jing")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��Ѫ��������ִ�������ʹ������ֽ���������ľ�����\n");

        if( (int)me->query("max_neili") < 15000 )
                return notify_fail("������������Ϊ������\n");
        if((int)me->query("neili")<1600)
                return notify_fail("�������������\n"); 
        if((int)me->query("jingli")<1200)
                return notify_fail("��ľ���������\n"); 

        target = me->select_opponent();

      //  if( !userp(me) && userp(target) )
               // return notify_fail("����ֽ��������ֻ�������ʹ�ã�\n");

        lvl = (int)me->query_skill("xuedao-jing",1);
        weapon = me->query_temp("weapon");
        weaname = weapon->query("name");
        msg = HIW "\n$N��Х���У�����"HIC"��ֽ"HIB"����"HIW"�����ؾ���ɲʱ����磬"NOR+weapon->query("name")+HIW"һ��Ϊ������һ��ѪӰ���������ȥ��\n"NOR;
        message_vision(msg, me);

     
//��ֽ��  
        message_vision(CYN"$N�����˼磬��ͨ�ڱۣ��������飬��������ġ���ֽ����������ԣ��������棬����ʮ�㣡\n"
						+"$N���ֿ켫,$nֻ�����⻮�ɵ�ԲȦ����ָ����ǰ����ȦԽ��Խ��ɲ�Ǽ��Х��������ս�ľ���\n"
						+"�����ʱ��ֻ����$nǰ��תȦ������һ��������$nС��Ҳ���ڵ�Ȧ֮�У���ʹ���У���Ȧ����$n��ͷ��\n"
						+HIR"$nֻ���Ծ�����������Ҫ���Ѿ�������������֮�£���������󺢣�\n"NOR,me,target);
		
		if(random(me->query_skill("xuedao-daofa",1))>target->query_skill("parry",1)/2
		   ||random(me->query_dex())>target->query_dex()/2)
		{
			message_vision(HBYEL"\n$nΪ��Ƭ�����Ѫ�����Ի��ƺ��ŵ�һ��Ī�������㣬��ʼ��æ����������\n",me,target);

			damage = me->query_skill("xuedao-daofa",1);
			damage += me->query_skill("blade",1);
			damage +=me->query_skill("xuedao-jing",1);
			damage =damage*3 + random(damage);
			target->start_busy(lvl/200);
			target->add_temp("lost_attack", lvl/200);
			target->apply_condition("no_perform", 1);
			target->apply_condition("no_exert", 1);
			target->add("neili",-(500+random(150)));
			target->receive_damage("qi", damage,me);
			target->receive_wound("qi", damage/3,me);
		  	msg = damage_msg(damage, "����");
			msg = replace_string(msg, "$w", weapon->name());
			msg = replace_string(msg, "$l", "С��");
			message_vision(msg, me, target);
			COMBAT_D->report_status(target, random(2));
			me->add("neili",-300);
			me->add("jingli",-100);	
		}
		//���У�Ѫ�����У�������
	
		target->set_temp("must_be_hit",1);
		
		message_vision(HIC"\n$Nһ���ȳ���������ʽ������Ӱ��ȫƾ���ܵ�����ʶ��Ӧ,������ֽƬ��һ��һƬ��һ��һƬ��ˢˢˢ���ػӳ���\n"NOR,me);

		if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		target->delete_temp("must_be_hit");

		me->delete_temp("xddf/shendao");
        

		me->add("neili", -200-random(300));
        if(me->query("neili")<0) me->set("neili",0);
        me->add("jingli", -80);
       	
		me->start_busy(random(2)+ 2);        
		me->start_perform(5,"��ֽ������");
		if (objectp(me)&&objectp(target)&&me->is_fighting())
			call_out("xddf_xiaofu",1,me,target);
        return 1;
}
//������

int xddf_xiaofu(object me,object target)
{
		int skill,lvl;
		object weapon;

        if (!me||!target) return;
        lvl=me->query_skill("xuedao-jing",1);
		weapon=me->query_temp("weapon");

		message_vision(HBWHT+HIB"$NѪ����������ת����ʱ���޾�����������ʩչ�����޾�ʤ�о��������������������ġ������������ι���\n"
						+"��"HIR"������"HIB"�����Ź���ԭ������һ�鶹������ľ��֮�ϣ�һ����������Ҫ��������һ�鶹�����ɶ�ʮ�飬ÿһƬ\n"
						+"����������,��ʱ����������С�ɣ���$n������һ�ճ����������У���ʱʩչ�����Բ���ͬ�ն��\n"NOR,me,target);
//550������
 	   if(lvl>550)
		{           
            me->add_temp("apply/attack", lvl/10);
            me->add_temp("apply/damage", lvl/10);
			message_vision(HIB"$N������Ȼ��ˣ�Ѫ������������ʱ�������ԣ�Ѫ�������������ݺᣡ\n"NOR,me);
        } 
//ԡѪ�����мӳ�

		if(me->query_temp("xdj/yuxue")) 
		{
                skill = me->query_skill("xuedao-jing",1)/10;
                me->add_temp("apply/damage", skill);
				me->set_temp("xddf/pzyxadd",skill);
                message_vision(RED"$N����Ѫ���������ھ����ڱ���֮�ϣ�"NOR+weapon->query("name")+RED"ͨ�������������ĺ�ɫ��â��\n"NOR, me,target);
        }

        me->add_temp("apply/blade", lvl/5);
        me->add_temp("apply/parry", lvl/5);
        me->add_temp("apply/dodge", lvl/5);
		me->set_temp("xddf/xiaofu",lvl);

				
		if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(lvl >250)
                if (present(target,environment(me)) && me->is_fighting(target))
                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(lvl >350)
                if (present(target,environment(me)) && me->is_fighting(target))
                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if(lvl >450)
                if (present(target,environment(me)) && me->is_fighting(target))
                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if(lvl >550)
                if (present(target,environment(me)) && me->is_fighting(target))
                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			
		me->add_temp("apply/blade",- lvl/5);
        me->add_temp("apply/parry",- lvl/5);
        me->add_temp("apply/dodge",- lvl/5);
        //����550Ӱ��
        if(lvl>550)
		{
            me->add("neili", -300-random(200));
            me->add_temp("apply/attack", -lvl/10);
            me->add_temp("apply/damage", -lvl/10);
        }
		//����ԡѪ�ӳ�Ӱ��
        if(me->query_temp("xddf/pzyxadd"))
		{
            me->add_temp("apply/damage", -skill);
			me->delete_temp("xddf/pzyxadd");
        }
		me->add("neili", -500-random(300));
        if(me->query("neili")<0) me->set("neili",0);
        me->add("jingli", -380);

		me->start_busy(random(2)+ 2);        
		me->start_perform(6,"����ֽ��������");
		message_vision(HIW"$N�յ����ʣ�����бվ������Ц���ѣ����ǵ��⣡\n"NOR,me);     
	    return;

}
int help(object me)

{
        write(RED"\nѪ������֮��"HIW"��ֽ"HIB"����"RED"������"NOR"\n\n");
        write(@HELP
	Ѫ�������Ǵ�����һ��֧���ݻ������Ĺ��쵶���似
	��ʼ��ΪѪ���ŵ�Ѫ�����棬��Ѫ���š������ɾ�ѧ��
	��Ϊ�ڹ������������֣�ȫ����¼�ڡ�Ѫ�������ϣ�
	��Ѫ������������������ÿ�ж����ھ������ܵķ�λ
	����������ַ���ʤ������������Ѫ�����𽭺���
	����ֽ������������ƽʱ��������������ֽ��������
	�������뵽ʵս�У���ֽ�������ѹ�������֣�����
	�����ǳöԷ�������˲����������������Խǿ������
	Խ���׺ݣ�550������������Ծ��

ָ�perform blade.pizhi

Ҫ��
	��ǰ���� 1600 ���ϣ�
	������� 15000 ���ϣ�
	��ǰ���� 1200 ���ϣ�
	Ѫ�����ȼ� 500 ���ϣ�
	Ѫ���󷨵ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	��������ΪѪ��������
	�����м�ΪѪ���������ջ�������
	�����ڹ�ΪѪ������
	�ֳֵ�������
HELP
        );
        return 1;
}