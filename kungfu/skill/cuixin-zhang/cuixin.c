inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int perform(object me, object target)
{
	int damage, p,level,damage2;
	string msg;
        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("���Ķϳ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	//if( !target->is_busy())
	//	return notify_fail("���Ķϳ�ֻ�ܶ�æ���еĶ���ʹ�á�\n");

	if( me->query_temp("weapon"))
		return notify_fail("������������\n");   

	if( (int)me->query_skill("cuixin-zhang",1) < 180 )
		return notify_fail("����Ʒ���Ϊ���㣬ʹ�������Ķϳ���\n");

	if( (int)me->query("neili") < 800 )
		return notify_fail("����������̫�������ܴ�����Ķϳ���\n");

	if( (int)me->query("jiali") < 100 )
		return notify_fail("�����ڼ���̫�������ܴ�����Ķϳ���\n");

	if (me->query_skill_prepared("strike") != "cuixin-zhang")
			return notify_fail("�������޷�ʹ�ô��Ķϳ���\n");
            
	msg = HIR"\n$N����$n��æ����֮ʱ��ʹ�������Ķϳ�����\n"NOR;
	
	damage=200;//û�⿪���˺�
	
	damage=(int)me->query_skill("cuixin-zhang",1)+me->query_skill("strike",1);	
	
	damage += random(me->query("jiali") * 3);
	
	if(me->query("quest/jiuyin2/cuixin/pass")) {
       message_vision(RED"\n$N��Ȼ��������������ؾ������Ķ�ʱӿ��һ�ź�⡣",me);		
	   damage *= 10;
	  if(target->query("neili") < me->query("neili")) damage *= 2;	
	}
   else
   {
	   damage *= 5;
   }
   
   if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("cuixin-zhang",1))> target->query_skill("dodge",1)/2)
	{    
      damage2=COMBAT_D->do_chemis_attack(me,target,1,damage,"������صĴ���$n���ؿڣ�$n��ʱ��Ѫ���硣");
  if (wizardp(me)) write("\n�˺�Ϊ:"+damage2);	  
	//p = (int)target->query("qi")*100/(int)target->query("max_qi");
	//msg += "������صĴ���$n���ؿڣ�$n��ʱ��Ѫ���硣\n";
	//msg += "( $n"+eff_status_msg(p)+" )\n"; 
   //     message_vision(msg, me, target);
	}
	else
	{
		msg  =  msg + CYN"$nƾ�����ɵ����㿪����һ�С�\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
	}
   
	me->add("neili", -350);
	//me->add("jingli", -150);
	me->start_busy(random(2)+1);
	me->start_perform(2,"���Ķϳ�");
	return 1;
}

string perform_name(){ return HIR"���Ķϳ�"NOR; }

int help(object me)
{
        write(HIR"\n������֮�����Ķϳ�����"NOR"\n\n");
        write(@HELP
        Ҫ��  ��ǰ���� 800 ���ϣ�
                ������� 1500 ���ϣ�
                ��ǰ���� 1000 ���ϣ�
                �����Ƶȼ� 180 ���ϣ�
                �����Ʒ�Ϊ�����ƣ�
                �����м�Ϊ�����ƣ�
                ���Ʒ�Ϊ�����ƣ�
                �����ޱ�����
		���ó���������ؾ��������������ȫ����

HELP
        );
        return 1;
}
