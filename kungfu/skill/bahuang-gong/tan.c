// tan.c creat by sohu@xojh 
// Դ�������˲���ɽͯ�ѽ������񹦷�
// ���ڱ����а������֣�������ת��Ϊ������������ʢˮ�Ĵ��ӣ�ˮ�к�������ж�����Ч��
#include <ansi.h>
inherit F_SSERVER;
inherit F_CLEAN_UP;
#include "/kungfu/skill/eff_msg.h"

string exert_name(){ return HIY"���־�"NOR; }

int exert(object me, object target)
{
	int skill,num,damage,p;
	string msg;
	object weapon;
	weapon=me->query_temp("weapon");
	skill =  me->query_skill("bahuang-gong", 1);
    //if(!target) target = offensive_target(me);
    if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("���־�ֻ����ս���жԶ���ʹ�á�\n");
	if( me->query("max_neili") < 3000 )
		return notify_fail("����������������\n");
	if( me->query("neili") < 1200 )
		return notify_fail("��ĵ�ǰ�����������޷�ʩչ���־���\n");
    if( me->query("jingli") < 1000 )
		return notify_fail("��ĵ�ǰ����������\n");

	if( me->query_skill("bahuang-gong", 1) < 350 )
		return notify_fail("��İ˻�����Ψ�Ҷ��𹦵ȼ�������\n");

	if( me->query_skill_mapped("force") != "bahuang-gong" )
		return notify_fail("����ڹ����ԡ�\n");
    if ((int)me->query_skill("bahuang-gong",1)<500 || me->query("bhg/biguan",1)<3)
  	  if (!weapon ||weapon->query("skill_type")!="throwing")
        return notify_fail("��˻�����Ψ�Ҷ�����δ��ɣ��дﲻ���ɻ�ժҶ֮�ز������ְֳ�����\n");
	
	if( me->query_temp("bhg/tan") )
		return notify_fail("���Ѿ�����ʹ���˻�����Ψ�Ҷ��𡹵��־��ˡ�\n");

	if (me->query_skill("bahuang-gong",1)<350) num=3;
	else if (me->query_skill("bahuang-gong",1)<450) num=6;
	else num=12;
	if (me->query("bhg/biguan")<3 && weapon->query_amount() < num)
             return notify_fail("���Ȼ�������ϵİ����������޷�ʹ���ⵯ�־���ֻ�÷������а�����\n");   
	if (userp(target)&&damage>4000) damage=4000+(damage-4000)/100;
	
	me->receive_damage("neili", -random(100)*num);
	me->receive_damage("jingli", -random(50)*num);
	message_vision(HBYEL+HIW "$N�������е����������˵���ͷ�޹�Ѩ�����͵������쾮Ѩ��Ȼ���͵���������Ѩ��\n"
	                   +"���������ȡ�������Ѩ����ת��ת��Ȼ���˵�����ָ�س�Ѩ��\n" NOR, me);
    message_vision(HIY+chinese_number(num)+"���ڹ��$N���Ϸ��Ӷ������ڰ˻Ĺ���������֮������$n��\n"NOR,me,target);
    if (me->query("bhg/biguan")<3 && weapon->query_amount() < num)      
	   weapon->add_amount(-num);
	me->set_temp("bhg/tan",1);
    if (random(me->query("neili"))>target->query("neili")/2||random(me->query_skill("force",1))>target->query_skill("dodge",1)/2)
    {    
	  damage=me->query_skill("bahuang-gong",1)+me->query_skill("force",1);
	  damage=damage*2+random(damage);
	  damage=damage*num;
	  if (damage>target->query("qi",1))
	     damage=target->query("qi")-1;
	  target->receive_damage("qi",damage,me);
	  //target->receive_wound("qi",damage/4);
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      tell_room(environment(target), HIR + target->name()+"ͻȻ��ʱΪ֮һ�ͣ���ȻѨ�������У�\n" NOR, ({ target }));  
           msg = damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
      target->start_busy(2+random(1));
	  if (me->query("bhg/biguan")>=2)
	  {
		message_vision(HIY"$N�˻Ĺ���Ȼ��ɣ���Ȼ��ͨ�����ɾ�������$n����������ӿ����,�������졣\n"NOR,me,target);
		message_vision(HIC"$nΪ$N������ס��������ʱ��Ѫ��ӿ��\n"NOR,me,target);
		target->apply_condition("no_exert",1+random(1));
		//target->apply_condition();
		target->add_busy(1+random(2));
	  }
	}
	else {
     message_vision(CYN"$n�����������������������Ϯ�������ɵ�����һ���亹��\n"NOR,me,target);
	 me->add_busy(1+random(1)); 
	}
	me->delete_temp("bhg/tan");
	//if (me->query_skill("bahuang-gong",1)<450)
	me->start_exert(3, "���־�");
	me->start_perform(3, "���־�");
	me->start_busy(1);
	return 1;
}



int help(object me)
{
	write(HIW"\n�˻�����Ψ�Ҷ���֮�����־�����"NOR"\n\n");
        write(@HELP
	�������ڽ����ɽͯ�ѵĹ����У���ͯ��ָʹ
	ѧϰ�������ڹ���ʹ���š��������ڴ����⵺
	������׷������У���������氵������ʹ��
	�����Ͼ������·Ӣ���Ǳ���ͻ�����־��ľ�
	����ʹ�����𵽹ؼ������á�
	���־�����С��ǰ����������ֻ�ܵ�������
	���������ǰ�ܵ���������������ɺ��ܵ�
	��ʮ�����������������Ź�����Ҫ���ж�˫��
	����ǿ�����������ڹ�Խ��ǿ�����к��˺�
	Խ�ߡ�
	ע����� 500��ǰ��������������Ҫ�ְֳ�
	�������ǵ� 500�����ҹ�����ͨ���⿪������
	�չص����Σ�����Դﵽ�ɻ�ժҶ����������
	�ĵز���

	ָ�yun tan
	
Ҫ��
	�������  3000 ���ϣ�
	��ǰ����  1200  ���ϣ�
	��ǰ����  1000  ���ϣ�
	�˻�����Ψ�Ҷ���  350  �����ϣ�
HELP
        );
        return 1;
}