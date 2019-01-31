// qingxin.c ���ľ���
#include <ansi.h>
//���������ľ�--by sohu@xojh

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
            return notify_fail("�����������䡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
            return notify_fail("��ʹ�õ��������ԡ�\n");
        if( me->query_skill("qinxin-jian",1) < 200 )
            return notify_fail("����������ƽ����������ʹ���������������䡹��\n");
        if( me->query_skill("force",1) < 200 )
            return notify_fail("��������޼������������ʹ���������������䡹��\n");
        if( me->query_skill_mapped("sword") != "qinxin-jian"
			||me->query_skill_mapped("parry") != "qinxin-jian" )
          return notify_fail("������û�����������ƽ����޷�ʹ��������У�\n");
     //   if( me->query_skill("force",1) <200)
       //     return notify_fail("�㲻�������޼��ڹ�֧�����޷�ʹ��������еģ�\n");
        if( me->query("quest/hmy/qxj/qingxin/pass") )
               return notify_fail("����δ�õ���ӯӯ�Ĵ��ڣ�����ʹ�á����������䡹�ˡ�\n");
        if( me->query_skill("art",1)<100 )
               return notify_fail("����ټ�̫�����ʹ�á����������䡹�ˡ�\n");

        if( me->query_temp("qxj/qingxin") )
               return notify_fail("�������Ѿ��������ʹ�á����������䡹�ˡ�\n");
       
        if( me->query("max_neili", 1) < 3000 )
               return notify_fail("������������Ϊ����ʹ�á����������䡹��\n");
        if( me->query("jingli") < 500 )
			return notify_fail("��ľ�����Ϊ����ʹ�á����������䡹��\n");
	 	if( me->query_dex() < 40 )
			return notify_fail("��ĺ�����Ч����Ϊ����ʹ�á����������䡹��\n");
        if( me->query("neili")<500)
            return notify_fail("�������������\n"); 

		msg = YEL "$N����"+weapon->name()+YEL"�����û����½��������ö������Ķ��˶���������$n��ϸ������ȴ�ǡ����������䡹��������\n"NOR;
        msg=HIW"$nֻ���ö�������������������һ����Ȫ�ڻ����������ֻ���ע������֫�ٺ�,$nȫ����ƮƮ�أ����ް��������\n";
		msg=HIW"����Ʈ�����ƶ�,$n����������������İ���֮�ϡ��������ã�����Խ��Խ�ͣ�����ϸ�����Ŷ�ֹ��\n"NOR;
		message_vision(msg, me, target);
        
		lvl = me->query_skill("art", 1) ;
        lvl = lvl/3;
		if (me->query("gender")!="Ů��")
		lvl=lvl/6;

		me->set_temp("qxj/qinxin", lvl);
        
		me->add_temp("apply/damage", lvl/3);
        me->add_temp("apply/sword", lvl);
        me->add_temp("apply/attack", lvl);
        
        if (me->query_skill("qinxin-jian",1)<200)
			me->start_perfrom(2,"�����������䡹");
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
			|| me->query_skill_mapped("sword")!="qinxin-jian")
        {      
			me->add_temp("apply/damage", -lvl/3);
			me->add_temp("apply/sword", -lvl);
			me->add_temp("apply/attack", -lvl);
			me->delete_temp("qxj/qingxin");

			message_vision(YEL"$N�ĵ���������������ͣ������������һ������\n"NOR,me);
			return;
		}
		call_out("remove_effect",1,me,count -2);
		return;

}
string perform_name() {return HIW"����������"NOR;}

int help(object me)
{
    write(HIY"\n�������ƽ���"HIW"����������"WHT"����"NOR"\n");
    write(@HELP
	�������ƽ���Դ����ӯӯ����ѧ���ݻ�����ʽ
	�󶼲ɼ�Ц������ԭ�������ֲ��ɿ�����Ϊ��
	������λ������ǣ��ĺ�������СħŮͬʱ��
	������Ů����ҵ����Լ��ص���ɶ��ɡ�
	���Ľ��˳����书��Ϊ�Ժ󽣷���·��������
	�ν���׼����Ů�������ƣ������ڹ���
	
	������������Ҫ�ҵ���ӯӯ����ɰ��������
	��ӯӯ��ǰ������ʱ�����ɵõ����ڡ�
	����������ĸ����˺���������ټ��йأ���
	��Խ�ߣ�Ч��Խ���ԡ�

	ָ�perform sword.qingxin
	
Ҫ��
	�������ƽ��ȼ� 200 �����ϣ�
	���������ȼ� 200 �����ϣ�
	�������Ҫ�� 3000 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	���������������ƽ���
	�����м��������ƽ���
	���ֳֽ���������    
HELP
	);
	return 1;
}

