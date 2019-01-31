// yufeng.c ��������--�����
// By River
inherit F_SSERVER;
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
string perform_name(){ return HIY"�����"NOR; }
int perform(object me, object target)
{
       string msg;
       object ob,weapon = me->query_temp("weapon");
       int i, damage, p;
      
       if( !target ) target = offensive_target(me);

       if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
             return notify_fail("�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

       if( !weapon
			|| me->query_skill_mapped("whip") != "yinsuo-jinling"
			|| me->query_skill_mapped("parry") != "yinsuo-jinling") 
             return notify_fail("�������޷�ʹ������빥���Է���\n");

       if(!objectp( ob= (present("yufeng zhen", me))))
             return notify_fail("������û������룬��ôʹ������룿\n");

       if((int)me->query_skill("yunu-xinjing", 1)  < 150 )
             return notify_fail("�����Ů�ľ��ȼ���������ʹ��������롣\n");

       if((int)me->query_skill("yinsuo-jinling",1) < 150 ) 
             return notify_fail("����������廹������죬����ʹ������롣\n");

       if((int)me->query_skill("throwing",1) < 150 ) 
             return notify_fail("��İ������򻹲�����죬����ʹ������롣\n");

       if((int)me->query("neili") < 500)
             return notify_fail("������������������֡�\n");

       if( userp(me) && (string)me->query("family/master_name") != "С��Ů")
             return notify_fail("�㲻��С��Ů�ĵ��ӣ���ô��ʹ������룡\n"); 

       msg = HIW"\n$N"+weapon->name()+HIW"�����֣���������һ�ӣ�һö��������׷ɳ�ֱ��$n�����ȥ��\n"NOR;
       
	   if (me->query_skill("yinsuo-jinling",1)<450)
       {
		   me->start_busy(2);
       }
       me->add("neili", -150);
       me->add("jingli", -60);
       i = (int)target->query_skill("dodge", 1) + (int)target->query_skill("parry", 1);
       i = random(i/2) - 10;
       damage = (int)me->query_skill("throwing", 1)*me->query_dex(1)+me->query_skill("yinsuo-jinling", 1);
	   if (damage>4000)
	   {
		   damage=4000+random(1000);
	   }
       if(random(me->query_skill("throwing", 1)) > target->query_skill("parry",1)/3
			|| random(me->query("combat_exp")) > target->query("combat_exp")/2
			|| !living(target)) 
	  {
          msg += HIR"$n�ͼ����һ������æ�����ܣ�����һ���ҽУ�������Ǳ��������У�\n"NOR;
          target->add_condition("bee_poison",5);
          target->receive_wound("jing", damage/5,me);
          target->receive_damage("qi", damage,me);
          target->receive_wound("qi", damage/4,me); 
          p = (int)target->query("qi")*100/(int)target->query("max_qi");
          msg += "( $n"+eff_status_msg(p)+" )\n";
          target->set_temp("last_damage_from", "��"+me->name()+"ɱ");
          me->start_perform(4,"�����");
       }
       else {
          msg +=CYN"$n��æ�����Ծ��ֻ����һ�����죬���������$p��ǰ������֮�С�\n"NOR;
          target->add("jingli", -50);
          me->add("neili",-150);
          me->start_busy(2);
          me->start_perform(2,"�����");
       }              
       message_vision(msg, me, target);
       if(!target->is_killing(me->query("id"))){
         me->kill_ob(target);
         target->kill_ob(me);
       }
       ob->add_amount(-1);
       return 1;
}
int help(object me)
{
        write(WHT"\n��������֮"+HIY+"������롹��"NOR"\n");
        write(@HELP
	�����������ǹ�Ĺ�����似��Դ��С��Ů��ս���ַ���
	��������λӢ�ۺ���ʱ���似���������ǲ�����ɽ���
	˿���죬��Ϊ���ͣ��������ޱȣ�ǰ��Ϊһ��ɫ��������
	�и��ŶԷ�ʩչ�����似�Ĺ��ܡ�����������С��Ů
	����Ͼ֮�࣬��ֳ�˴�����ɫ���۷䣬���仨�ۣ�����
	�䶾ͿĨ�ڽ������ƶ��ɣ���ս����ʩչ������ʤ����
	����һ���ж���ȫ�������ѵ�����Ϊʹ�����ǹ�Ĺ����
	���׽�ȡ�
	
	perform whip.yufeng
		
Ҫ��
	�������Ҫ�� 1500 ���ϣ�      
	��ǰ����Ҫ�� 500  ���ϣ�
	��Ů�ľ��ȼ� 150 ���ϣ�
	��������ȼ� 150 ���ϣ�
	���������ȼ� 150 ���ϣ�
	���������޷��������壻
	���������м��������壻
	����Я������룻               
                
HELP
        );
        return 1;
}