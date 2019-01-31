// kong.c  
// by tiantian@sj 2000.6.19

#include <ansi.h>
inherit SKILL;
inherit F_SSERVER;
#include <combat_msg.h>
int hurt(object me,object target, int damage);
string perform_name(){ return HIW"��"NOR; }

int perform(object me,object target)
{
	
	int ap,dp,j;
	int damage;
	string msg;
    ap = me->query("combat_exp")/ 100 * me->query_str();
	dp = target->query("combat_exp")/100 * target->query_dex();
	damage = me->query_skill("cuff",1) + me->query_skill("kongming-quan",1)+me->query("jiali") * 2;	
	if (!target) target = offensive_target(me);
	if (!objectp(target)|!living(target) || !me->is_fighting(target))
		return notify_fail("���ա��־�ֻ����ս����ʹ�á�\n");                
    if (me->query_temp("weapon"))
		return notify_fail("���ֱֳ���������ʹ�á��ա��־���\n");     
	if (me->query_skill("kongming-quan", 1) < 350)
		return notify_fail("��Ŀ���ȭ�в����죬������ʹ�á��ա��־���\n");        
	if (me->query("max_neili") < 5000)
		return notify_fail("�������������㣬����ʹ�á��ա��־���\n");
    if (!me->query("quest/jiebai/pass"))
        return notify_fail("��û�к��ܲ�ͨ���壬����ʹ�á��ա��־���\n");
	
	if (me->query_temp("kongming/kong"))
		return notify_fail("������ʹ�á��ա��־���\n");      
//	if (me->query_temp("kongming/ming"))
//		return notify_fail("������ʹ�á������־���\n");      
	 message_vision(HIW"\n$Nȭ�����䣬һȭ�������������˸յľ�����ѧ��$n�;��öԷ�ȭ���������ޣ��Լ�����\n"
		+"ʹʵ�˹�Ȼ���ԣ�ʹ����Ҳ�Ǽ���Σ�գ����������Ծ���\n"NOR, me,target);
	

	if( random(ap + dp) > dp ){
		message_vision( HIY"\n$n������������ˮ���ƺ����Ȳ����ۼ�$P����������ʶ����ͼ��ס$N��һȭ��\n"NOR,me,target);
		me->add("neili", -100);
		me->add("jingli", -50);
		if (me->query("quest/hubo/pass")&&me->is_fighting()&&objectp(target))
		{
			call_out("hurt", 1, me, target, damage);	
		}
		else message_vision(HIC"\n$Nû���������칦�����ʵ�İ��أ����־�������ʩչ������ֻ�����ա�\n"NOR,me,target);
	}
	
	if( random(ap) > dp/3 ){
		
		target->receive_damage("qi", damage, me);
        target->receive_wound("qi", damage/4, me);
		if (wizardp(me))
		{
			write("damage="+damage);
		}
        j = (int)target->query("qi")*100/(int)target->query("max_qi");
		msg = HIR"������صĴ���$n���ؿڣ���ʱ��Ѫ���硣\n"NOR;
	    msg += "( $n"+eff_status_msg(j)+" )\n"; 
       // message_vision(msg, me, target);
        msg += damage_msg(damage, "����")+"( $n"+eff_status_msg(j)+" )\n"; 
		COMBAT_D->report_status(target,random(2));
        
		if(userp(me) && me->query("env/damage"))
		    tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
	
        if(userp(target)&& target->query("env/damage"))
		    tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR); 
	    me->add("neili", -150);
		me->add("jingli", -50);
	  }
 	   else {
		msg = HIY"����$n��Ȼ������·���������𽭺��Ŀ���ȭ�����ж�ʱ���ˣ�����һ�ˣ����������С����־�����\n"NOR;
	}
     message_vision(msg, me, target);
     //return 1;
	

	me->add("neili", -300); 
	
	if (!me->query("quest/hubo/pass"))
		me->start_perform(4,"���ա��־�");
	else 
	{
		me->start_perform(2,"���ա��־�");
        me->add_temp("apply/attack",me->query_skill("kongming-quan",1));
	    me->add_temp("apply/damage",me->query_skill("kongming-quan",1)/3);
	}
	me->set_temp("kongming/kong", 1);
	call_out("remove_effect",1,me,(int)me->query_skill("kongming-quan",1)/10);
	return 1;
}

int hurt(object me,object target, int damage)
{
    string msg;
	if ( ! me) return 0;

    if( !target || !target->is_character() )
                return 0;
    
	damage=me->query_skill("kongming-quan",1)+me->query_skill("xiantian-gong",1);
	damage=damage+me->query_skill("taoism",1);
	damage=damage*2;
	damage=damage*me->query_str()/10;
	
	if (userp(target)&&damage>3000) damage=3000+random(1000);
	
	if (damage>6000) damage=damage+(damage-6000)/10;
	
    msg = HIB"\n�������ǵ���֮�ʣ�ͻȻ������ȭ������ת��Ϊʵ������ȫ��һ����Ϣ���ڣ�\n"NOR;
    if (me->query("neili")>target->query("neili")*3/2
		|| random(me->query_skill("xiantian-gong",1))>target->query_skill("force",1)/2)
    {
		  msg += RED"\n$N��һȭ�����������ۼ�������������࣬��֪һ�����д��͵�ȭ�����ӭ���������Ƶ����ǵ��˲��ɣ���\n"NOR;
          me->set_temp("fanzhen",1);
		  target->receive_damge("qi",damage,me);
          target->receive_wound("qi",damage/3,me);
		  target->apply_condition("neishang", 1);
		  target->apply_condition("no_exert",1);
		  target->add_busy(1+random(2));
		  if (!userp(target))
		  {
			  target->add_busy(2+random(2));
		  }
	}
	else if( target->query("neili") <= 200 || target->query("qi") <= 500 ){
		   tell_object(target, CYN"����Ȼ�����Լ�������Ȼ�ݽߺľ����޷��˾��࿹�ˣ�\n"NOR);
		   msg += RED"���ֻ��$n�͵ؿ�����Ѫ���磬ȫ��������Ϊ�����Թ����������ѣ��ۼ��ǻ���ˣ���\n"NOR;
		   target->receive_damage("qi", (int)target->query("qi")+1, me);
		   target->set("eff_qi", 10);
           msg += "( $N"+eff_status_msg(1)+" )\n";   
	}
	
	else if( target->query_skill("force",1) > 450 ) 
		target->apply_condition("neishang",1);
	else target->apply_condition("neishang", 2);
	message_vision(msg, me);
    return 1;
}

void remove_effect(object me,int count)
{
	if (!me) return;
	
	if (!me->is_fighting()
		||me->query_skill_mapped("cuff")!="kongming-quan"
		||count<1)
	{
		if (me->query("quest/hubo/pass"))	
		{
			me->add_temp("apply/attack",-(me->query_skill("kongming-quan",1)));
			me->add_temp("apply/damage",-(me->query_skill("kongming-quan",1)/3));
		}
		me->delete_temp("kongming/kong");
		tell_object(me, HIW"\n�㻺������һ��������������ת�����������뵤�\n"NOR);
		return;
	}
	call_out("remove_effect",2,me,count--);
	
}
int help(object me)
{
	write(WHT"\n����ȭ֮�����־�����"NOR"\n\n");
	write(@HELP
	����ȭ�����������ȭ�������ܲ�ͨ�ӡ����¾����л�
	�����ģ������¾��������Ե�������ǿ����ľǿ���ۡ�
	��ǿ���£��������ϡ������ƣ�������Ī������ˮ������
	��ǿ��Ī֮��ʤ����������֮����֮ʤǿ����֮ʤ�գ�
	����Ī��֪��Ī���С��ǽ���ʮ����ȴ����ѧ��������
	���ȭ��������ȭ֮���־��������ǿգ�ʵ�������黯
	ʵ�ĸ����ھ��������ޱȡ������Բ�ǿ�����������ȿ�
	�����ʵ����
	
	ָ�perform cuff.kong

Ҫ��
	������� 3000 ���ϣ�
	��ǰ���� 1500  ���ϣ�
	��ǰ���� 1500  ���ϣ�
	����ȭ�ȼ� 350 ���ϣ�
	����ȭ���м�Ϊ����ȭ��
	��ȭ��Ϊ����ȭ�ҿ��֡�
	�⿪˫�ֻ������������ʹ�á�

HELP
	);
	return 1;
}
