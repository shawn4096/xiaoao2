//liandao.c 
//by sohu@xojh ��������
//�����̵������ǰ������ղ�ʹ����Ȧס�㣬������һ�����������µĽ�ħ������������һ�����ǹ�����ɽ�����Ϻ��Ĳ�ʮ��·��
//��ת��������һ�����ֱ����˽���ʷ�ҵġ��ط�����������˺���ʹһʮһ��������һʮһ���ɱ�ĵ�����������ת�����������ͷ
//����һ�ǣ�����������ͯ���Ĺ��Ϻ��������ġ��ȱ�������ֻ�Ƶж���ɱ�ˡ����õ������㾱�У����Ǳ���������������ܵе�������
//�ǡ���ɽ�����С�֮һ�����ǳ����󿳵������������Ķ����ڵ��������ɽ�����һ���������������Ļ��˵ĵ��ȡ�����һ��һ�е�����
//�����������䣬����˵����Դ���ɱ𣬶�������ȴ��һ�ϲ�ͨ���Ŀ�Զԣ������֮��ء�

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j;
        object weapon = me->query_temp("weapon");
         j = me->query_skill("murong-daofa",1)/2+ me->query_skill("xingyi-zhang",1)/2;
        
		if (!userp(target)) j=j/2;
        else j =j /3;
 
		
		if(!userp(me)) j = j/ 3;
     
        if( !target ) target = offensive_target(me);

        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))               
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");                

        if( (int)me->query_skill("murong-daofa", 1) < 350 )
                return notify_fail("��ĵ�����δ���ɣ�����ʹ������������\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("������û�е����޷�ʹ������������\n");

        if((int)me->query_skill("xingyi-zhang", 1) < 350 )
                return notify_fail("����Ʒ���δ���ɣ�����ʹ������������\n");  

       /* if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("����ڹ�������Ԫ�����޷�ʹ������������\n");     
        if(me->query_skill_mapped("strike") != "xingyi-zhang" 
         || me->query_skill_prepared("strike") != "xingyi-zhang")
                return notify_fail("��û�����ƣ��޷�ʹ������������\n"); */


        if(me->query_skill_mapped("parry") != "xingyi-zhang")
		if(me->query_skill_mapped("parry") != "douzhuan-xingyi")

			if(me->query_skill_mapped("parry") != "murong-daofa")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ������������\n");

        if((int)me->query("max_neili") < 6000 )
                return notify_fail("������������Ϊ����������ʹ������������\n");      

        if((int)me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ������������\n");      

        if((int)me->query_skill("blade", 1) < 350 )
                return notify_fail("��Ļ�������������죬�����ڵ����м���ʹ������������\n");

        if((int)me->query_skill("force", 1) < 350 )
                return notify_fail("��Ļ����ڹ�������죬�����ڵ����м���ʹ������������\n");     
        message_vision(HIG"\n$N�������е�"+weapon->query("name")+HIG"ɲ�Ǽ�׹�����������Ȧ��֮�ڣ�ȫ�ǵ�Ӱ��$n��������\n"+
			"$Nÿһ��������ȫ��ͬ���书�е�һ�У��ƺ���ƴ���������似������Ϻ�ȴ��������������Ľ�ݵ���������������\n"NOR, me,target);
        
		me->add("neili", -500); 
        me->add("jingli", -250);
        
        me->add_temp("apply/attack", j); 
        me->add_temp("apply/strength",j /10);
        me->add_temp("apply/blade",j);      
        me->add_temp("apply/damage",j/2);
		
		if (random(me->query_skill("blade",1))>target->query_skill("parry",1)/2)
		{
			message_vision(HIR"\n$n��û���ü��粽�����Ѹ������ϼ�ͷ��������һ�£���������һ�����Ų����ġ�$n�Ų�һ�ң�\n$N��ʱ����ֱ�ϣ��������з�������$n�ĺ󾱡�\n"NOR,me,target);
			target->receive_damage("qi",1000+random(2000),me);
			target->add_busy(2);
			if (!userp(target)) target->add_busy(3);
			
		}
		me->set_temp("mrdf/liandao",7);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		
if(objectp(target) && me->is_fighting(target))
        {
              
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
				
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
		
        if(objectp(target) && me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		if(objectp(target) && me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		if(objectp(target) && me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

		if(objectp(target) && me->is_fighting(target))
        {
               // weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				//weapon->wield();
        }
	    me->add_temp("apply/damage",-j/2);
        me->add_temp("apply/strength",-j /10);
        me->add_temp("apply/blade",-j);
        me->add_temp("apply/attack", -j);
		me->delete_temp("mrdf/liandao");
        //me->start_busy(1+random(2));
		me->start_perform(5,"������");  
		return 1;
}
string perform_name(){ return HIY"������"NOR; }

int help(object me)
{
        write(HIC"\nĽ�ݵ���֮"+HIB+"������������"NOR"\n\n");
        write(@HELP
	Ľ�ݵ�������Ľ�ݼ����д����ҳ��ǵ���Ҫ�����似��Ľ����
	�������Ǵ�������ᣬ��Ľ�ݴ���ʼ�������ھ���֮�䣬����
	����ʵս���������Ѿ��ںϲ����������ɵĵ���������һ����
	�����˵��������ޱȣ�����ʤ������Ϊ��Ϊ�ҳ����ã�������
	����������Ҫ��������Խ����������ǿ��
	�����������ǽ�Ľ���ϼҴ���ѧ�ڻ��ͨ���γ�ǿ��ĵ�����
	��ɣ��򹥻�Ϭ�����������϶���仯��ˣ���Ϊ������
	
ָ�perform blade.liandao
	
Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 6000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�
	Ľ�ݵ����ȼ� 350 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�
	�����Ʒ�Ϊ�����ƣ�
	��������ΪĽ�ݵ���
	�����м�ΪĽ�ݵ�����ת���ƣ�
	�ֳֵ�������
                
HELP
        );
        return 1;
}
