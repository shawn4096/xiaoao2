// xuanfeng.c ������
// by sohu@xojh
//�ȷ���·ͼ
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{

	int i,damage,p,skill;
	string msg;
	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("�������ȡ�ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("ʹ�á������ȡ�ʱ˫�ֱ�����ţ�\n");

	if( (int)me->query_skill("shaolin-tantui", 1) < 300 )
		return notify_fail("����������Ȳ�����죬����ʹ�á������ȡ���\n");
	if( (int)me->query_skill("leg", 1) < 300 )
		return notify_fail("��Ļ����ȷ��Ȳ�����죬����ʹ�á������ȡ���\n");
	if( (int)me->query_skill("yijin-jing", 1) < 300 )
		if( (int)me->query_skill("hunyuan-yiqi", 1) < 300 )
		return notify_fail("����׽���Ԫһ���ȼ�����������ʹ�á������ȡ���\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		if (me->query_skill_mapped("force") != "hunyuan-yiqi")
		return notify_fail("��Ŀǰ���ڹ��޷�֧����ʹ�á������ȡ����й�����\n");  
	
	if (me->query_skill("leg",1)<100)
		return notify_fail("��Ŀǰ�Ļ����ȷ�����100����֧����ʹ�á������ȡ����й�����\n");  
		
	if( (int)me->query_dex() < 50 )
		return notify_fail("���������50������ʹ�á������ȡ���\n");

	if (me->query_skill_prepared("leg") != "shaolin-tantui"
	|| me->query_skill_mapped("leg") != "shaolin-tantui")
		return notify_fail("�������޷�ʹ�á������ȡ����й�����\n");  
											       
	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("�������������̫��������ʹ�á������ȡ���\n");
	if( (int)me->query("neili") < 800 )
		return notify_fail("��Ŀǰ����̫�٣�����ʹ�á������ȡ���\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("�����ھ���̫�٣�����ʹ�á������ȡ���\n");


	message_vision(HIW"\n$N˫�ųʶ��ֲ�վ�������һ���������Ϊԭ�㣬ʩչ"HIG"�������ȡ�"HIW"����ʽ��$n�����������ȣ�Ѹ���ޱȣ������籩�꣡\n" NOR,me, target);
	
	skill=me->query_skill("shaolin-tantui",1);

	if(random(me->query_dex()) > target->query_dex()/2
	  ||random(me->query_skill("leg",1))>target->query_skill("dodge",1)/2)
	{
		   message_vision(HIR"\n$nһʱ���飬���������$N�ġ������ȡ���ʽ���У����ɵ�һ����Ѫ���ڣ�\n\n"NOR,me,target);            

           damage = me->query_skill("leg",1)+me->query_skill("shaolin-tantui",1)+me->query_skill("dodge",1);
		   damage=damage*me->query_dex()/5;
           damage =3*damage;
		   damage += random(damage);
           
           
		   if (wizardp(me))
           {
			   message_vision("damage="+damage+"\n",me);
           }
		   
		   if (damage>3500) damage=3500+random(100);
		   if (userp(target)&& damage > 2500) damage = 2500;

	      
           
		   target->receive_damage("qi", damage, me);
		   target->apply_condition("neishang",3+random(2));
           target->receive_wound("qi", damage/4, me);
           
           
		 //  limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"����ȫ����ѹ��һ���ʯһ����һ��һ��ѣ�α�����\n" NOR, ({ target }));  
           msg = damage_msg(damage, "����");
            msg += "( $n"+eff_status_msg(p)+" )\n";
          
		   message_vision(msg, me, target);
           
		   if(userp(me) && me->query("env/damage"))
	          tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);
           
			if(userp(target)&& target->query("env/damage"))
	         tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	}
		

		message_vision(HIC "\n$N��һ�����꣬���н��ƻ�����������ת������������������\n" NOR,me);
		if (objectp(me)&&objectp(target))
			call_out("remove_xuanfeng",1,me,skill/50);
		
		me->add_temp("apply/leg",skill/4);
		me->set_temp("sltt/xuanfeng", skill);
		me->add("neili", -280);
		me->add("jingli", -180);


		return 1;
}



int remove_xuanfeng(object me,int count)
{
	int skill;
	object target;
	if (!me) return 0;
	skill=me->query_temp("sltt/xuanfeng");
	target = offensive_target(me);
	if (!objectp(target)
		||!me->is_fighting()
		||me->is_busy()
		||count<0)
	{
		me->add_temp("leg",-skill/4);
		me->delete_temp("sltt/xuanfeng");
		message_vision(HIC "\n$N˫��վ�����������У�����ͻ��һ��������ɢ�������ȹ�����\n" NOR,me);
		return 1;
	}
	if (objectp(me)&&me->is_fighting())
	{
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/5);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/5);
	}
	call_out("remove_xuanfeng",1,me,count--);
}
string perform_name(){ return HIG"������"NOR; }
int help(object me)
{
        write(HIC"\n���ֵ���֮�������ȡ�������"NOR"\n");
        write(@HELP
	���ֵ���Ϊ���������ȷ������ü�ʵ���ȹ���ǿ�����������
	��������У��öԷ�������Է��߳�һ�ž���ɱ�У�����ַ�
	��ʤ�������޿ɶ㣬�˵��������ǳ���
	����������һ��Ϊ���ģ�������ת��Ϊ�����ս�е�Զ��Ϯ��
	�似��һ��ʩչ��ѭ�����У��������󡣴��м�Ϊ���������
	��ҵ����á�

	ָ�perform leg.xuanfeng

Ҫ��  
	����������� 5000 ���ϣ�      
	��ǰ�������� 800  ����
	��ǰ�������� 500  ���ϣ�  
	���ֵ��˵ȼ� 300 ���ϣ�
	�׽���ȼ� 300 ���ϣ�
	�����ȷ��ȼ� 300 ���ϣ�	
	�����ȷ�Ϊ���ֵ��ȣ�
	�����м�Ϊ���ֵ��ȣ�
	�����ޱ�����
	��Ч������С��50��
                
HELP
        );
        return 1;
}
