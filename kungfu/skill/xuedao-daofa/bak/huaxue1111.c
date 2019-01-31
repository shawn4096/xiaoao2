// huaxue.c  ��Ѫ��
// edit by sohu@xojh

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
int remove_effect(object me,int i);

string perform_name(){ return HIG"��Ѫ��"NOR; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg, weaname;
        int lvl,damage,i,ap,dp;
    
        if( !me->is_fighting() )
                return notify_fail("����Ѫ����ֻ����ս����ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if((int)me->query_dex() < 15)
                return notify_fail("���������, Ŀǰ������ʹ���������! \n");

        if((int)me->query_skill("dodge") < 100)
                return notify_fail("����Ṧ��Ϊ����, ����ʹ�á���Ѫ������\n");
 
        if((int)me->query_skill("xuedao-jing",1) < 100)
                return notify_fail("��ĵ�����Ϊ������ Ŀǰ����ʹ�á���Ѫ����! \n");

        if((int)me->query_skill("xuedao-dafa",1) < 100)
                return notify_fail("���Ѫ������Ϊ������ Ŀǰ����ʹ�á���Ѫ����! \n");

        if( me->query_skill_mapped("blade") != "xuedao-jing")
                return notify_fail("�����ʹ��Ѫ����������ʹ�á���Ѫ�����ľ�����\n");

        if( me->query_skill_mapped("force") != "shenzhao-jing" && me->query_skill_mapped("force") != "xuedao-dafa")
	    	  return notify_fail("��������ʹ�õ��ڹ�ͬ��Ѫ���󷨡���ִ�������ʹ������Ѫ�����ľ�����\n");

        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("���������Ϊ������\n");
        if((int)me->query("neili")<600)
                return notify_fail("�������������\n"); 
        if((int)me->query("jingli")<200)
                return notify_fail("��ľ���������\n"); 
		if (me->query_temp("xddf/huaxue"))
				return notify_fail("������ʹ�û�Ѫ����\n"); 
        target = me->select_opponent();
		

        lvl = (int)me->query_skill("xuedao-jing",1);
        weapon = me->query_temp("weapon");
        weaname = weapon->query("name");
        
		msg = HIG "\n$N����Ѫ�����С���Ѫ��������������"NOR+weaname+HIG"����һƬ����ɫ�ĵ�Ӱ������������������ȥ��\n"NOR;
        msg+=RED+weaname+RED"�ϵ�Ѫ�ۺ�Ȼ����һ����а�İ���֮ɫ����Ϊ���ۣ�\n"NOR;
		message_vision(msg, me);

        if(me->query_temp("xuedao/yuxue")) {
                damage = me->query_skill("xuedao-dafa",1)/4;
                me->add_temp("apply/damage", damage);
				me->set_temp("xuedao/hx",1);
                message_vision(HBRED"$N����Ѫ���󷨸��ڱ���֮�ϣ�"+weaname+HBRED"�����������ĺ�ɫ��â��\n"NOR, me,target);
        }
      //  me->add_temp("apply/blade", lvl/3);
        me->add_temp("apply/parry", lvl/5);
        me->add_temp("apply/dodge", lvl/5);
        //me->add_temp("apply/attack", lvl/3);
        //me->add_temp("apply/damage", lvl/4);
        me->set_temp("xddf/huaxue",lvl);
		
		call_out("remove_effect",1,me,lvl/20);
		me->start_perform(1,"Ѫ����");
        return 1;
}

int remove_effect(object me,int i)
{
	int lvl;
	object weapon;
	weapon=me->query_temp("weapon");
	if (!me) return 0;
	
	lvl=me->query_temp("xddf/huaxue");
    
	if (!me->is_fighting()
		||me->query_skill_mapped("blade")!="xuedao-jing"
		||me->query_skill_mapped("force")!="xuedao-dafa"
		||!me->query_temp("weapon")
		||weapon->query("skill_type")!="blade"
		||i<0 )
	{
		me->add_temp("apply/blade",- lvl/5);
        me->add_temp("apply/parry",- lvl/5);
        me->add_temp("apply/dodge",- lvl/5);        
        me->add_temp("apply/attack", -lvl/3);
        me->add_temp("apply/damage", -lvl/4);
		me->delete_temp("xddf/huaxue");
		if (me->query_temp("xuedao/hx"))
		{
                me->add_temp("apply/damage",-me->query_skill("xuedao-dafa",1)/4);

		}
		message_vision(HIG"$N������ɽ�����ǵ�"HIR"Ѫ��"HIG"��ͣ��������������Ц���ѡ�\n"NOR,me);
	}
	call_out("remove_effect",me,i--);
	return 1;

}


int help(object me)
{
	write(HIG"\nѪ������֮����Ѫ������"NOR"\n\n");
        write(@HELP

	��Ѫ�����ǻ�Ѫ���ĵ����ܸ٣�Ϊ�������쵶��
	�ĸ�Ҫ�ļ���Ѫ�������б��Ī��ĵ���������
	�ɴ˶�����Ѫ�����ǽ�ƽʱ�̲��ڵ����е�Ѫ��
	�������ڹ�������ɢ�������˵�ɱ�������޵ĺ�
	�⣬�����Ի���֣�Ҳͬʱ��������ս������
	500�����ɡ�
	
ָ��: perform blade.huaxue

Ҫ��
	�������  1200 ���ϣ�
	��ǰ����  1000  ���ϣ�
	Ѫ����  450  �����ϣ�
	350����С�ɣ�
	450���Ϊ����ʽ��

HELP
        );
        return 1;
}