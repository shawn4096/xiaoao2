// shendao.c  Ѫ���� [��������]
// changed by emnil@sj  2/5/2000

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
 
string perform_name(){ return HIB"��������"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, weaname;
        int lvl,damage,i;
        int d=me->query_skill("xuedao-jing",1) /2+ me->query_skill("xuedao-daofa",1) /2 ;
         
        if(!userp(me)){ 
            // i = i / 2; 
             d= d /2;
			 }
			 
		 if (me->query_temp("xd/chilian"))
			     return notify_fail("���������Ρ�����ʹ���С�\n");
			 
        if( !me->is_fighting() )			
                return notify_fail("���������Ρ�ֻ����ս����ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if((int)me->query_dex() < 30)
                return notify_fail("���������, Ŀǰ������ʹ���������! \n");

        if((int)me->query_skill("dodge",1) < 350)
                return notify_fail("����Ṧ��Ϊ����, ����ʹ�á��������Ρ���\n");
        
		if(!me->query("quest/xd/xddf/chilian/pass"))
                return notify_fail("��ֻ����˵���������ξ���,������ʹ�á��������Ρ���\n");

        if((int)me->query_skill("xuedao-daofa",1) < 350)
                return notify_fail("��ĵ�����Ϊ������ Ŀǰ����ʹ�á��������Ρ�! \n");

        if((int)me->query_skill("xuedao-jing",1) < 350)
                return notify_fail("���Ѫ������Ϊ������ Ŀǰ����ʹ�á��������Ρ�! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("�����ʹ��Ѫ������������ʹ�á��������Ρ��ľ�����\n");
		
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("����мܲ��ԣ����뼤������ΪѪ������������������\n");

        if( me->query_skill_mapped("force") != "xuedao-jing" && me->query_skill_mapped("force") != "shenzhao-jing")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��Ѫ���󷨡���ִ�������ʹ�����������Ρ��ľ�����\n");

        if( (int)me->query("max_neili") < 4000 )
                return notify_fail("���������Ϊ������\n");
        if((int)me->query("neili")<2000)
                return notify_fail("�������������\n"); 
        if((int)me->query("jingli")<1500)
                return notify_fail("��ľ���������\n"); 


       
        lvl = (int)(me->query_skill("xuedao-daofa",1)+me->query_skill("xuedao-jing",1)/2);
        weapon = me->query_temp("weapon");
        weaname = weapon->query("name");
	    message_vision(HIB"\n$N������ǰһ̽������"+weapon->query("name")+HIB"���������б���һ��������һ�㣬Ѹ�����׵���$n�ĸ첲�����ж������漴�յ����ʣ�\n"NOR, me,target);

		me->set_temp("xd/chilian", d);
	    me->receive_damage("neili", 300);
	    me->receive_damage("jingli", 250);

        me->add_temp("apply/attack", d /2);
	    me->add_temp("apply/damage", d /4 );
	    me->add_temp("apply/blade",d/4);
        me->add_temp("apply/dodge", d /3);


	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//me->delete_temp("xd/chilian");
	    if (me->query("quest/xd/xdj/xuedao/pass"))
	    {
			me->start_perform(2, "���������Ρ�");
	    }
		else me->start_perform(4, "���������Ρ�");
		//��������4�к����Ƕ��
	   i=7;
		call_out("check_fight", 1, me, i);
	return 1;
}

void remove_effect(object me)
{
	int d;
	if(!me) return;

	d=me->query_temp("xd/chilian");
  
    me->add_temp("apply/attack",- d /2);
	me->add_temp("apply/damage", -d /4 );
	me->add_temp("apply/blade",-d/4);
	me->add_temp("apply/dodge", -d /3);
    me->delete_temp("xd/chilian");
	if (living(me))
		message_vision(HIY"\n$N"HBRED"�ġ��������Ρ�����������ϣ����ص�������չ���\n"NOR, me);
	me->start_perform(3, "���������Ρ�");
	
	me->add_busy(2);
	return;
}

void check_fight(object me, int i)
{
	object weapon, target;

	if (!me||!me->query_temp("xd/chilian") ) return;
	
	weapon=me->query_temp("weapon");
	target = offensive_target(me);

	if(!i
	|| !living(me)
	|| !target
	||!weapon
	|| !me->is_fighting(target)
	|| environment(target)!=environment(me)
	|| me->query("neili") < 2000
	|| me->query("jingli") < 1500)
		return remove_effect(me);

	if(me->query_skill_mapped("blade") != "xuedao-daofa") {
		tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á��������Ρ�������\n");
		return remove_effect(me);
	} 
	else if(!objectp(weapon = me->query_temp("weapon"))
		|| weapon->query("skill_type") != "blade"){
		tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á��������Ρ�������\n");
		return remove_effect(me);
	} 
	else {
		me->receive_damage("neili", 200);
		me->receive_damage("jingli", 150);
		if (objectp(target) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		call_out("check_fight", 1, me, i--);
	}
}
int help(object me)
{
        write(HIG"\nѪ������֮���������Ρ���"NOR"\n\n");
        write(@HELP
	Ѫ��������Ѫ���Ŷ����书����Ϊ�ڹ���͵�����
	Ѫ�������Թ���������������Ѫ�������ѩɽѩ��
	���뽭������һս���������ǴӲ�����֮��������
	���˵Ĺ����Ѳ⡣
	������������������ע�뵶��֮�У�һ��������
	�ƽ����ֿ�ɱ���˵���ΪѪ������Ҫ�������似��
	���ĵ��Ӳ��ɴ��ڡ�

ָ�perform blade.chilian

Ҫ��
	��ǰ���� 2000 ���ϣ�
	������� 4000 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	Ѫ�����ȼ� 350 ���ϣ�
	Ѫ���󷨵ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��������ΪѪ������
	�����м�ΪѪ���������ջ�������
	�����ڹ�ΪѪ���󷨡�
	�ֳֵ�������
HELP
        );
        return 1;
}