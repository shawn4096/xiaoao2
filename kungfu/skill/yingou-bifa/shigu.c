//shigu.c ʯ����
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int do_1(object me,object target);

string perform_name(){ return HIY"ʯ����"NOR; }

string *buwei = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
"ӿȪѨ","��׶Ѩ","�縮Ѩ",
}); 
int perform(object me, object target)
{
      string msg; 
      int i, damage,p;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("������û�бʣ��޷�д��ʯ���ģ�\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("ʯ����ֻ����ս���жԶ���ʹ�á�\n");
             
      if((int)me->query_skill("yingou-bifa",1) < 350 )
         return notify_fail("��������ʷ���������죬����дʯ���ģ�\n");
       if((int)me->query_skill("brush",1) < 350 )
         return notify_fail("��Ļ����ʷ���������죬����дʯ���ģ�\n");     
      if((int)me->query_skill("literate",1) < 250 )
         return notify_fail("��Ķ���д�ֵȼ�����������д��ʯ���ģ�\n");  
      if((int)me->query_int() < 50 )
         return notify_fail("������Բ���������д��ʯ���ģ�\n");  
      if((int)me->query_skill("qiantian-yiyang",1) < 350 )
         return notify_fail("���Ǭ��һ���ȼ�����������д��ʯ���ģ�\n");
      
      if((int)me->query("max_neili") < 4000 )
         return notify_fail("�������̫�����޷�д��ǿ��������ʯ����! \n");
      
      if((int)me->query("neili") < 1000 )
         return notify_fail("�������̫���ˣ�д����ʯ�����޸���֮����\n");       

      if((int)me->query("jingli") < 500 )
         return notify_fail("��ľ���̫���ˣ�д����ʯ�����޸���֮����\n");       
         
      if(me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("�㼤�����ԣ������޷�д����ʯ���ġ���\n");

      i = random((int)(me->query_skill("yingou-bifa",1)/15));
      if(i < 1) i=1;
      if(i > 15) i=15;                                                                                 

      msg = HIY"$N��Ȼ��ʷ��ֱ䣬�˱ʲ���д�֣�ȴ�����˸�ͷ��ʯͷ�����һ�㡣��һ·�ʷ���ʯ���ģ�\n"+
               "���Ǵ���֮���ø������ʯ���ϵ����֣�������ŵĴ�׭�֡�$n����һ·��׭��Ȼֻʶ��һ��\n"+
               "���֣��Ȳ�֪�Է���д���֣���Ȼ�²����鷨��ܺͱʻ����ƣ���ʱ�����мܡ�\n" NOR;

      me->add("neili", - 450);
      me->add("jingli", -100);

      if((random(me->query_skill("literate",1)) > target->query_skill("literate",1)/6)
       ||(random(me->query_skill("force",1)) > target->query_skill("force",1)/5)){
           //me->start_busy(1);
           target->start_busy(3);
           damage = (int)me->query_skill("yingou-bifa", 1);
           damage = damage + random(damage);
           damage = damage * i * 2 / 3;
           if (damage > 4000 ) damage = 4000+random(1000);
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/4,me);
           msg += MAG"$Nһ����һ����׭�����������ֹ�Ȼ�Ű£�����Ϊ�鷨֮���������ʷ�Ҳ��Ӧ��ǿ������\n"+
                     "$N��ʻ��裬�ڿ��������������֣�$n����õ�ȥ�������֣�ϥ��Ѩ��һ�飬ǿ��һ����\n"+
                     "��ϥ��Ѩ����ȥ��$N������磬��������һ���������У�$n����������̱���ڵ��ϡ�\n"NOR;
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           msg += "( $n"+eff_status_msg(p)+" )\n";
		   message_vision(msg, me, target);
		   me->add_temp("apply/attack",me->query_skill("yingou-bifa",1)/4);
		   me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/5);
		   me->add_temp("apply/brush",me->query_skill("yingou-bifa",1)/5);

		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		   me->add_temp("apply/attack",-me->query_skill("yingou-bifa",1)/4);
		   me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/5);
		   me->add_temp("apply/brush",-me->query_skill("yingou-bifa",1)/5);
           if (me->is_fighting(target)&& objectp(target)){
			  do_1(me,target);
		   }

       }
       else{
           msg += CYN"$Pһ�ֿ��һ�֣��ʷ��ӹ�$p����ߣ�ֻ�������쬵ģ�$p������ȥ��$P��\n"+
                     "д���֣�ֻ�û�ס���ź����ϸ���ҪѨ��ͻȻ����һ�飬ǿ��һ����ȥ��Ѩ����\n"+
                     "����������Ѩ�ɹ��������ֱ���������������ǿ���мܡ�\n"NOR;
           if( random(me->query("combat_exp", 1)) > target->query("combat_exp", 1)/ 2
            && me->is_fighting(target)
            && present(target,environment(me))){
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
              if (present(target,environment(me)) && me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
           }
           me->start_busy(2);
           if ( target->query("neili") > 400 ) target->add("neili",- random(200));
		   message_vision(msg, me, target);
       }
      
       me->start_perform(4,"��ʯ���ġ�");
       return 1;
}
int do_1(object me,object target)
{
    object wp1,wp2;
	string name;
	name = buwei[random(sizeof(buwei))];
	wp1=me->query_temp("weapon");
	//wp2=target->query_temp("weapon");
	if (!wp1) return 0;
	
	if (!me||!target) return 0;
	
	message_vision(HIC"$Nһ����һ����׭�����������ֹ�Ȼ�Ű£�����Ϊ�鷨֮����һ��ָҲ��Ӧ��ǿ������\n"+
		"$N���е�"+wp1->query("name")+HIC"����������$n��"+HIR+name+HIC"������һ����׭,����һ���������֣�\n"NOR,me,target);
	message_vision(HIC"$nһ����ãȻ�ʵ��������ǡ��������᣿��,$NЦ��������һ���������֣�\n"NOR,me,target);
	target->add_busy(2);
	me->add_temp("apply/attack",me->query_skill("yingou-bifa",1)/4);
    me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-me->query_skill("yingou-bifa",1)/4);
    me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/5);
	if (me->is_fighting(target)&& objectp(target)) 
		call_out("do_nai",1,me,target);
	return 1;

}
int do_nai(object me,object target)
{
    object wp1;
	string name;
	if (!me||!target) return 0;

	wp1=me->query_temp("weapon");
	if (!wp1) return 0;

	name = buwei[random(sizeof(buwei))];
	message_vision(CYN"$N�漴���"+wp1->query("name")+CYN"����$n��"+HIR+name+CYN"��д��һ�֡�$n�����������ǡ��¡��֣���$Nҡͷ˵���������ˣ����ǡ��ˡ��֡���\n"NOR,me,target);
	me->add_temp("apply/attack",me->query_skill("yingou-bifa",1)/4);
    me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-me->query_skill("yingou-bifa",1)/4);
    me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/4);
	if (me->is_fighting(target)&& objectp(target)) 
		call_out("do_manyi",1,me,target);
	return 1;

}
int do_manyi(object me,object target)
{
    object wp2;
	string name,name2;
	if (!me||!target) return 0;

	wp2=target->query_temp("weapon");
	

	name = buwei[random(sizeof(buwei))];
	if (wp2) 
	{ 
		name2=wp2->query("name");
		message_vision(HIG"\n$n�����ɥ������"+name2+HIG"��Ҫ�㿪$N�ıʷ棬������$N��"+name2+HIG"�����֣�����$N���ƶ�Ȼ�Ӳ���ǿ����\n"
					+"$næ���ƵֵУ�ȴ��$N������룬����"+name2+HIG"�����������֣�ֻ��д�ü��ˣ��ѷǴ�׭��ȴ�ǲ��顣\n"NOR,me,target);

	}
	else {
		
		message_vision(HIG"\n$n�����ɥ������˫�ƣ���ͼҪ�㿪$N�ıʷ棬������$N��"+HIR+name+HIG"�����֣�����$N���ƶ�Ȼ�Ӳ���ǿ����\n"
					+"$næ���ƵֵУ�ȴ��$N������룬����"+HIR+name+HIG"�����������֣�ֻ��д�ü��ˣ��ѷǴ�׭��ȴ�ǲ��顣\n"NOR,me,target);

	}
	
	
	message_vision(HIC"��Ȼ�ȵ���������$n��ʶ���ˣ��ѿڶ������е��������ģ�����\n"NOR,me,target);
	me->add_temp("apply/attack",me->query_skill("yingou-bifa",1)/2);
    me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-me->query_skill("yingou-bifa",1)/2);
    me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/4);
    message_vision(HIY"$N������Ц���е����������ǡ��������ģ������ĸ��֣�\n"NOR,me);
	return 1;

}

int help(object me)
{
	write(HIC"\n�����ʷ�֮��ʯ���ġ�������"NOR"\n");
	write(@HELP
	�����ʷ�����һ�ƴ�ʦ������������Ķ����似������״Ԫ����
	�����Ըߣ����԰�ʦһ�ƴ�ʦ���似ͻ���ͽ�����Ϊ�Ĵ����
	���书����ߡ����Ź�������֮�����ڽ�һ��ָ���鷨�ں���һ
	����ʽ�м����ŵ�Ѩ�����˷���ʤ����
	�����ڴ�ʤ�������һս������ʯ���ľ���������ͨë�ʶ�ս��
	������׭��ʩչ����ʯ���ġ��������������¡�
	
ָ�perform brush.shigu

Ҫ��	
	������� 4000 ���ϣ�		
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 500  ���ϣ�
	�����ʷ��ȼ� 350 ���ϣ�
	��Ч���� 50 ���ϣ�
	����д�ֵȼ� 250 ���ϣ�
	�����ʷ�Ϊ�����ʷ�
	�����м�Ϊ�����ʷ���
	�ֱֳ���������
HELP
	);
	return 1;
}