// lianhuan.c ��צ��������ʽ
// By Spiderii ��̬�޸ġ��������趨Ϊ�߹��������˺��������ǽ�����������
/*
    ����ͻȻ����һ�����������ϣ�˫�����������꣬������ʽ������׽Ӱʽ����������ʽ��������ɪʽ����������ʽ����������ʽ����������ʽ��������ȱʽ������ʽ�������������������޼������У���ʽ��Ϊ������׽Ӱ�����ٹ�ɪ���������顢������ȱ���������У����к󷢶�������
    ������ɮ���ʽ��������צ�����಻����������һ���еİ˸��仯һ�㣬����ޱȣ�
*/

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return RED"������ʽ"NOR; }

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
                return notify_fail("��צ����������ʽ��ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�������ʽ����\n");   
        if( (int)me->query_skill("longzhua-gong", 1) < 250 )
                return notify_fail("�����צ����������죬ʹ������������ʽ��������\n");
        if (me->query_skill_prepared("claw") != "longzhua-gong"
        || me->query_skill_mapped("claw") != "longzhua-gong")
                return notify_fail("�������޷�ʹ�á�������ʽ�����й�����\n");  

	    if( me->query_skill_mapped("force") != "yijin-jing" )
		        return notify_fail("������ʹ�õ��ڹ�������ʹ�á�������ʽ����\n");
        if( (int)me->query_skill("yijin-jing", 1) < 250 )
                return notify_fail("����׽�ȼ���������ʹ������������ʽ��������\n");
        if (me->query("class") && me->query("class") != "bonze")
		            return notify_fail("������ڵ��ӣ�����ʹ�á�������ʽ����\n");
        if( me->query("max_neili") < 3500 )
                return notify_fail("����������̫����ʹ������������ʽ����\n");      
        if( (int)me->query("neili") <1500 )
                return notify_fail("����������̫����ʹ������������ʽ����\n");
      
        
        lv = me->query_skill("longzhua-gong",1);
		lvf=me->query_skill("yijin-jing",1)/2;
        hit = (lv/50);
        if(hit > 8) hit = 8;
        if(hit <2) hit = 2;
        lv += lvf;
		if (target->is_busy())
		{
			message_vision(HIY"$N��$n������æ��֮�У��Թ˲�Ͼ���׽����צ�У���צ��������ʱ���Ӳ��١�\n"NOR,me,target);
			lv+=lv/4;
		}
        me->add_temp("apply/attack", lv/3);
		me->add_temp("apply/claw", lv/3);
        me->add_temp("apply/damage", lv/5);
       // me->add_temp("apply/parry", -lv/5);
        lzg_msg = HIR"\n$NͻȻ����һ�����������ϣ�˫������������: \n";

        if(hit >= 2)lzg_msg += "������ʽ������׽Ӱʽ��";
        if(hit >= 4)lzg_msg += "��������ʽ��������ɪʽ��";
        if(hit >= 6)lzg_msg += "��������ʽ����������ʽ��";
        if(hit >= 8)lzg_msg += "��������ʽ��������ȱʽ��";
        
        lzg_msg += "��\n"+chinese_number(hit)+"ʽ����������������\n"NOR;

        message_vision(lzg_msg, me, target);
        me->set_temp("lzg_times",hit);
        me->set_temp("lzg_effect",1);
        me->add_temp("lzg/lianhuan", 3);
        me->set_temp("action_flag", member_array("claw", keys(me->query_skill_prepare())));
        //me->set_temp("baocan",hit);
		
        for( i=0; i < hit; i++ )
        {
                
				me->add_temp("lzg/lianhuan", 1);
                COMBAT_D->do_attack(me, target, weapon, random(2)?3:1);
        }


       message_vision(HIY"\n��"+chinese_number(hit)+"ʽ��������צ�����಻����������һ���е�"+chinese_number(hit)+"���仯һ�㣬����ޱȣ�\n"NOR, me);

        me->add("neili", -hit*20+20);
        me->add("jing", -hit*5);
        me->start_perform(3,"��������ʽ��");
        me->start_busy(1+random(2));
        me->delete_temp("lzg/lianhuan");
        me->delete_temp("lzg_times");
        me->add_temp("apply/attack", -lv/3);
        me->add_temp("apply/damage", -lv/5);
		me->add_temp("apply/claw", -lv/3);
       // me->add_temp("apply/parry", lv/5);
        return 1;
}


int help(object me)
{
        write(HIR"\n��צ��֮��������ʽ����"NOR"\n");
        write(@HELP
        ��צ��Ϊ������ʮ������֮һ��������ϰ��������ָ������Ҫ�������ֳ������֡�
        Ϊ��Ӳ���֮�������Ტ��֮�����������֮����������������ע������ָ�з�Ϊ
        ��ɡ��ˡ�������ʽ��һ��ʹ�������������꣬����ץ�������������������ޱȡ�
        ��ʽ����Υ�����ּ������������ɮϲ�������������ࡣ

        Ҫ��  ������� 3500 ���ϣ�      
                ��ǰ���� 1500  ���ϣ�  
                ��צ���ȼ� 250 ���ϣ�
                �׽�ȼ� 250 ���ϣ�
                ����צ��Ϊ��צ����
                �����м�Ϊ��צ����
                �����ޱ�����
                ��צ��ÿ�����ȼ� 100 lv��
                ��׷��2 hit ������
                ��߿��� 8 hit ������
				����һָ�����������⹦Ч��
                
HELP
        );
        return 1;
}

