//pokuai.c �Կ��ƿ�
// ���˶Է�����צ��

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return RED"�Կ��ƿ�"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lv,lvf, i, hit;
         string weapon, lzg_msg;

        if( !target ) target = offensive_target(me);
         
		if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("�������ָ���Կ��ƿ졹ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á��Կ��ƿ졹��\n");   
        if( (int)me->query_skill("jingang-zhi", 1) < 500 )
                return notify_fail("��Ĵ������ָ��������죬ʹ�������Կ��ƿ졹������\n");
        if (me->query_skill_prepared("finger") != "jingang-zhi"
        || me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("�������޷�ʹ�á��Կ��ƿ졹���й�����\n");  
 
        if( (int)me->query_skill("force", 1) < 500 )
                return notify_fail("��Ļ����ڹ��ȼ���������ʹ�������Կ��ƿ졹������\n");
        if (me->query("class") && me->query("class") == "bonze")
		            return notify_fail("�������ڵ��Ӻʹ������ָ������֮����㣣�����ʹ�á��Կ��ƿ졹��\n");
        if( me->query("max_neili") < 15000 )
                return notify_fail("����������̫����ʹ�������Կ��ƿ졹��\n");      
        if( (int)me->query("neili") <2000 )
                return notify_fail("����������̫����ʹ�������Կ��ƿ졹��\n");
      
       
        lv = me->query_skill("jingang-zhi",1);
		lvf=me->query_skill("force",1)/2;
        hit = (lv/50);
        if(hit > 8) hit = 8;
        if(hit <3) hit = 3;
        lv += lvf;
		if (target->is_busy())
		{
			message_vision(HIY"$N��$n������æ��֮�У��Թ˲�Ͼ�������������������ָ������ʱ���Ӳ��١�\n"NOR,me,target);
			lv+=lv/4;
		}
        me->add_temp("apply/attack", lv/3);
		me->add_temp("apply/finger", lv/3);
        me->add_temp("apply/damage", lv/5);
       // me->add_temp("apply/parry", -lv/5);
        lzg_msg = HIR"\n$N̤��һ��������һȭ������$n�ؿڴ򵽣���һ��������磬ȭ����;������ȭ����Ѹ�ݵ����ϣ���������ײ��$n���š� \n";

      //  if(hit >= 2)lzg_msg += "������ʽ������׽Ӱʽ��";
     //   if(hit >= 4)lzg_msg += "��������ʽ��������ɪʽ��";
      //  if(hit >= 6)lzg_msg += "��������ʽ����������ʽ��";
     //   if(hit >= 8)lzg_msg += "��������ʽ��������ȱʽ��";
        
        lzg_msg += "\n\n�漴��ɫ�Ժ�ת�࣬ŭ��һ�����������ϣ����ֻ�ȭ���ƣ����Ī�⣬����ȴ������ָ�Ĺ�����ץ��������ڷ�����\n�����ָ���йٱʣ����Ѩ��絶�罣����ǹ��ꪣ���������֮����\n"NOR;

        message_vision(lzg_msg, me, target);
        me->set_temp("lzg_times",hit);
        me->set_temp("lzg_effect",1);
        me->add_temp("jgz/pokuai", 1);
        me->set_temp("action_flag", member_array("finger", keys(me->query_skill_prepare())));
        //me->set_temp("baocan",hit);
		
        for( i=0; i < hit; i++ )
        {
                
				//me->add_temp("jgz/pokuai", 1);
                COMBAT_D->do_attack(me, target, weapon, 3);
        }


       message_vision(RED"\n��"+chinese_number(hit)+"ʽָ�������籩�꣬�Կ��ƿ죬���಻��������ޱȣ�\n"NOR, me);

        me->add("neili", -hit*20+20);
        me->add("jing", -hit*5);
        me->start_perform(5,"���Կ��ƿ졹");
        me->start_busy(1+random(2));
        me->delete_temp("jgz/pokuai");
        me->delete_temp("lzg_times");
        me->add_temp("apply/attack", -lv/3);
        me->add_temp("apply/damage", -lv/5);
		me->add_temp("apply/finger", -lv/3);
       // me->add_temp("apply/parry", lv/5);
        return 1;
}


int help(object me)
{
        write(HIR"\n�������ָ֮���Կ��ƿ졹��"NOR"\n");
        write(@HELP
	�������ָΪ������ʮ������֮һ��������ϰ��������ָ��
	����Ҫ�������ֳ������֡�Ϊ��Ӳ���֮�������Ტ��֮
	�����������֮����������������ע������ָ�з�Ϊ��ɡ�
	�ˡ��Կ��ƿ졹һ��ʹ�������������꣬��������������
	�����������ޱȡ���ʽ����Υ�����ּ�����������׼ҵ���
	ϲ�������������ࡣ
	
	ָ��;perform finger.pokuai

Ҫ��
	������������� 3500 ���ϣ�      
	��ǰ���������� 1500  ���ϣ�  
	�������ָ�ȼ� 500 ���ϣ�
	�����ڹ��ĵȼ� 500 ���ϣ�
	����ָ��Ϊ�������ָ��
	�����м�Ϊ�������ָ��
	�����ޱ�����
	�������ָÿ�����ȼ� 100 lv��
	��׷��2 hit ������
	��߿��� 8 hit ������
	���ʹ��������ƻ��������⹦Ч��
                
HELP
        );
        return 1;
}


