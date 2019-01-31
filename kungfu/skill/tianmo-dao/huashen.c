// chuanliu.c
//xjqx@sj 2008/12/30
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object me,int count);
int perform(object me, object target)
{
	object weapon;
	int skill;
	weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("��ֻ����ս����ʹ�û�����ǧ��\n");
	if (!me->query("quest/hmy/tmd/pass"))
		return notify_fail("��ֻ����˵��������ǧ��������û������ָ�㣬������ս����ʹ�û�����ǧ��\n");
	if (!objectp(weapon) || (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

    if (me->query_skill_mapped("force") != "tianmo-gong" )
       if(me->query_skill_mapped("force") != "xixing-dafa")
          return notify_fail("����ʹ�õ������ڹ����ԡ�\n"); 

    if(!me->query_skill("xixing-dafa", 1))
       if(me->query_skill("tianmo-gong", 1) < 250)
          return notify_fail("�������ڵ��ڹ���Ϊ��ʹ������������ǧ����\n");  

	if ((int)me->query_skill("blade", 1) < 250 )
		return notify_fail("��Ļ���������������죬����ʹ�û�����ǧ��\n");

	if ( me->query_skill_mapped("blade") != "tianmo-dao"
	 || me->query_skill_mapped("parry") != "tianmo-dao" )
		return notify_fail("�������޷�ʹ�û�����ǧ��\n");

	if ((int)me->query("neili") < 1000 )
		return notify_fail("����������̫��������ʹ�û�����ǧ��\n");

	if ((int)me->query("max_neili") < 3000 )
		return notify_fail("����������̫��������ʹ�û�����ǧ��\n");

	if (me->query_temp("tmd/huashen") ) 
		return notify_fail("���Ѿ���ʹ�û�����ǧ�ˣ�\n");
    if (me->query_skill_mapped("force")=="tianmo-gong")
       message_vision(HIY"\n$N��������ħ����������" + weapon->query("name")+HIY"��������Ӱ�����������������Ʋ��ɵ���\n"NOR, me);
    else if (me->query_skill_mapped("force")=="xixing-dafa")
       message_vision(HIG"\n$N���������Ǵ󷨣�������" + weapon->query("name") +HIG"��������Ӱ�����������������Ʋ��ɵ���\n"NOR, me);
    	
	skill = me->query_skill("tianmo-dao",1);
	
	if (me->query_skill_mapped("force")=="tianmo-gong") skill += me->query_skill("tianmo-gong",1)/8;
	if (me->query_skill_mapped("force")=="xixing-dafa") skill += me->query_skill("xixing-dafa",1)/4;
	
	
	me->add_temp("apply/attack", skill/4);
	me->add_temp("apply/damage", skill/5);
	me->add_temp("apply/parry", skill/4);
	me->add_temp("apply/dodge", skill/4);
	me->add_temp("apply/blade", skill/4);
	
	me->set_temp("tmd/huashen", skill);
    message_vision(HIR"\n$N�����ٱ仯���������ߣ���Ӱ��˸�������ɷ磬��ʱ�����������һ����\n"NOR, me);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	//if ( me->query_skill("tianmo-dao", 1) > 349)
		//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    if (me->query_skill("tianmo-dao",1)<350)
    {
		me->start_perform(1, "������ǧ");
	   
    }
	me->add("neili", -300);
	//if (objectp(target)&&me->is_fighting())
		call_out("remove_effect", 1, me, (int)skill/30);
	remove_effect(me,(int)skill/30);
	return 1;
}

void remove_effect(object me,int count)
{
	int skill;
	object target,weapon;
	if( !me||!me->query_temp("tmd/huashen")) return;
	skill=me->query_temp("tmd/huashen");
	weapon=me->query_temp("weapon");
	if(!me->is_fighting()
		|| count<0
		|| !me->query_temp("weapon") 
		|| me->query_skill_mapped("blade") != "tianmo-dao"
		|| me->query_skill_mapped("parry") != "tianmo-dao")
	{
		if(me->query_temp("weapon"))
			message_vision(HIY"$N����һ�ͣ������ջ������ĵ�Ӱ����ħ����������ʱɢ����\n"NOR, me);
		else message_vision(HIY"$N����һ�ͣ������ջ��ڹ�����ħ����������ʱɢ����\n"NOR, me);
		me->add_temp("apply/attack", -skill/4);
		me->add_temp("apply/damage", -skill/5);
		me->add_temp("apply/parry", -skill/4);
	    me->add_temp("apply/dodge", -skill/4);
	    me->add_temp("apply/blade", -skill/4);
		me->delete_temp("tmd/huashen");
		return;
	}   
	//����ս�������򴥷�Э������
	target = offensive_target(me);
    
	if (objectp(target)
		&&random(me->query("combat_exp"))>target->query("combat_exp")/2
		&&me->query_skill_prepared("strike")=="tianmo-zhang"
		&&me->query_skill_mapped("strike")=="tianmo-zhang")
    {
		message_vision(HIY"$N��$n����֮�ʣ����ٽ����������֣����ֺ�Ȼʩչ����ħ�ƾ�ѧ��Ѹ���ޱȵ�����$n�ĺ󱳡�\n"NOR, me, target);
		
		if (random(me->query_skill("strike",1))>target->query_skill("parry",1)/3)
		{
			message_vision(HIR"$nһ��С�ģ���$Nһ�ƴ��к󱳡�\n"NOR, me, target);
			target->add_busy(1+random(1));
			target->receive_damage("qi",3*skill,me);
            target->receive_wound("qi",skill,me);
			weapon->unequip(); 
			me->add_temp("apply/strike",skill/2);
			COMBAT_D->do_attack(me, target,0, 3);
            me->add_temp("apply/strike",-skill/2);
			weapon->wield();
		}
		else message_vision(HIC"$n������$N����ͼ����Цһ�������˿�ȥ��\n"NOR, me, target);
    }
	//��Ŀ����������ѭ������
	if (objectp(me))
		call_out("remove_effect", 1, me,count--);
	
	return;
}

string perform_name(){ return HIB"������ǧ"NOR; }

int help(object me)
{
        write(HIB"\n��ħ��֮��������ǧ����"NOR"\n\n");
        write(@HELP
	�Ը߳��������ƣ�����ת�����ݻ��������ͬʱ
	��Է�������������ħ�����зǳ���Ҫ�ĸ���������
	�ܣ�ʵʩ������ǧ�󹥷�����������
	
	ָ��:perform blade.huashen

Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 3000 ���ϣ�
	��ħ���ĵȼ� 250 ���ϣ�
	��ħ�������Ǵ󷨵ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	��������Ϊ��ħ����
	�����м�Ϊ��ħ����
	�����ڹ�Ϊ���Ǵ󷨻���ħ����
	���ֳֵ��������350����С�ɡ�

HELP
        );
        return 1;
}
