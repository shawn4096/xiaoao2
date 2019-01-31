// fenmo.c ��ħ��
// by sohu@xojh 

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i,ap,dp;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("����ħ��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!weapon || weapon->query("skill_type") != "blade"
           || me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("�������޷�ʹ������ħ����������\n");

        if (weapon->query("sharpness") > 3)
                return notify_fail("������֮�����Ƿ���֮����ʹ�á���ħ��������û��ʲô���ã�\n");

        if (weapon->query("unique"))
                return notify_fail("������֮�����Ƿ���֮����ʹ�á���ħ��������û��ʲô���ã�\n");
                
        if(me->query_skill("ranmu-daofa", 1) < 400 )
                return notify_fail("���ȼľ������򲻹���ʹ��������ħ����������\n");

        if(me->query_skill("blade", 1) < 400 )
                return notify_fail("��Ļ�������������죬ʹ��������ħ����������\n");
	   if (me->query_skill_mapped("parry")!="ranmu-daofa"&&me->query_skill_mapped("parry")!="cibei-dao")
                return notify_fail("����мܲ��ԣ��޷�ʹ�á���ħ����������\n");  

        if( (int)me->query_skill("yijin-jing", 1) < 400 )
                return notify_fail("����׽�ȼ�������ʹ��������ħ����������\n");

        if( (int)me->query_str() < 65)
                return notify_fail("�������������ǿ��������65��ʹ��������ħ����������\n");

        if( (int)me->query_int() < 30)
                return notify_fail("û�д��ǻ۴��������ʹ��������ħ���������ġ�\n");
 
        if ( me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("û���׽��Ϊ���������޷�ʹ������ħ���������ģ�\n"); 

        if(me->query_temp("rmdf/fenmo")) 
                return notify_fail("����������ʹ�á���ħ����������\n"); 

        if (me->query_temp("jgq/fumo"))
                return notify_fail("����������ʹ�á���շ�ħ���񹦡�\n"); 

        if (me->query("max_neili") < 1000)
                return notify_fail("���������Ϊ������\n");

        if (me->query("neili") < 650)
                return notify_fail("�������������\n");

        if (me->query("jingli") < 200)
                return notify_fail("��ľ���������\n");

        me->add("neili", -600);
        me->add("jingli", -150);        

		//fenwo's damage depends on how many times u pfmd       

        i = me->query("rmdf/fenmo");
        if (i > me->query_skill("blade",1)) 
			i = me->query_skill("blade",1);
        ap = me->query_dex(1);
	    dp = target->query_dex(1);
	
//and it will not be over ur enable blade skill

		me->add_temp("apply/damage",i);
		me->add_temp("apply/attack",i/2);//ԭ����/2
        
		me->set_temp("rmdf/fenmo", i);
        
		message_vision(HIY"\n$N������������������������Ϳ���ȼ�շ�����ž������������������ȼ��һ�����й�һ������ֱ��$n���Ŷ�ȥ��\n"NOR,me,target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);   
    /*    	
        if(random( ap + dp ) > dp&&me->is_fighting()) 
		{ 
        	message_vision(HIC"\n$N����ǿ���ֳöԷ��޻�Ϣ֮�ʣ���ʹ��һ������������֮������$n��ֱ����ȥ��\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
        if(me->is_fighting()) 
		{ 
        	message_vision(HIR"\n$N����Ĭ��𷨣����к㶨��ʯ����������аħ��������������ߺ죬�ȵ�������ħ���¡���\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
*/
        weapon->add("fenmo", 1);
        
		if (weapon 
        && !weapon->query("unique")
		&& me->query("yjj/powerup")!="pass"
        && weapon->query("rigidity") < 2
        && weapon->query("fenmo") >= (3+weapon->query("rigidity"))) 
		{
           	message_vision(HIY"\nֻ�������ǡ�������$N���е�$n"HIY"�����ܻ������ѳ�����Ƭ��\n"NOR,me,weapon);
           	weapon->unequip();
           	weapon->move(environment(me));
           	weapon->set("name", "���ѵ�" + weapon->query("name"));
           	weapon->set("value", 49);
           	weapon->set("weapon_prop", 0);
           	me->reset_action();
        }
        me->add_temp("apply/damage", -i);
        me->add_temp("apply/attack", -i/2);//ԭ����/2
        me->delete_temp("rmdf/fenmo");
        me->start_busy(1);
        me->start_perform(3,"��ħ��");
        me->add("fenmo", 1);
        return 1;
}
string perform_name(){ return HBWHT+HIR"��ħ��"NOR; }
int help(object me)
{
        write(HIY"\nȼľ����֮����ħ������"NOR"\n\n");
        write(@HELP
	ȼľ�����������������ռ�����֮һ���ǵ����ļ�����似
	��������������ʮ�������в���֮�أ��书���������
	ƾ����������������������ƻ����������ޱȡ������书��
	���������ʦ��ϰ���������ʦԲ�ź󣬴��似�����޳ɣ�
	��һ����ɮ�Ħ��ƾ��С�������ݻ�ȼľ������ս������
	ʱ��ʹ�ô����似�������¡�ͬʱ�������׽�����ڹ���
	�������������磬�������顣
	��ħ����Ȼ��һ�У�������������أ���ϰȼľ��Խ������
	����Խ��Ϭ����ʵ��ȼľ����һ��ɱ�У�

	ָ�perform blade.fenmo 

Ҫ��  
	��ǰ�������� 1000 ���ϣ�
	����������� 10000 ���ϣ�
	��ǰ�������� 800 ���ϣ�
	ȼľ�����ȼ� 400 ���ϣ�
	�׽���ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	��������Ϊȼľ������
	�����ڹ�Ϊ�׽�񹦣�
	���ֳ�ľ����

HELP
        );
        return 1;
}
