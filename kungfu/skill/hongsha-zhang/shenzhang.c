// hongsha.c
// by sohu@xojh 2015

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return RED"��ɰ����"NOR;}

int perform(object me, object target)
{
  string msg, dodge_skill;
  int damage, p, jiali, skill, neili, neili2;
  

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) 
      || environment(target)!=environment(me) || !living(target))
         return notify_fail("����ɰ���ơ�ֻ����ս�����á�\n");

  if( me->query_temp("weapon")) 
         return notify_fail("���������������ʹ�ó�����ɰ���ơ���\n");
         
  if( (skill = (int)me->query_skill("hongsha-zhang", 1)) < 100 )
         return notify_fail("��ĺ�ɰ�Ʋ�����죬����ʹ����ɰ���ơ���\n");

  if( (int)me->query_skill("xuedao-jing", 1) < 100 )
         return notify_fail("����ڹ���򲻹�������ʹ�á���ɰ���ơ���\n");

  if( me->query_skill_mapped("force") != "xuedao-jing")
         return notify_fail("�����õ��ڹ��͡���ɰ���ơ��໥��ͻ��\n");

  if (me->query_skill_prepared("strike") != "hongsha-zhang" ||
      me->query_skill_mapped("strike") != "hongsha-zhang")
         return notify_fail("������Ƚ���ɰ���������Ʒ�֮�в��С�\n");

  if( (jiali = (int)me->query("jiali")) < 50 )
         return notify_fail("�����ϲ�����������ôʹ�ó�����ɰ���ơ�����\n");

  if( (neili = (int)me->query("neili")) < 500 )
         return notify_fail("����������㣬����ʩչ����ɰ���ơ���\n");
  if( (int)me->query("max_neili") < 1500 )
         return notify_fail("����������㣬����ʩչ����ɰ���ơ���\n");
  if( (int)me->query("jingli") < 300 )
         return notify_fail("��ľ������㣬����ʩչ����ɰ���ơ���\n");

  me->receive_damage("neili", random(100) );
  me->receive_damage("jingli", 50);
  
  message_vision(RED "\n$N�������𣬲��Ӳ��ܣ���Ӱ�ζ�����Ц����������$n"RED"��˫���Ƴ���\n"NOR,me,target);

  if( random( me->query("combat_exp") ) < target->query("combat_exp")/5) 
  {
         dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         msg = "�Ʒ����һ���������ֵĵ���ɫѪ����Ϣ������С�ӣ�\n"NOR + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
         message_vision(msg, me, target);
         return 1;
  }
 
  
  msg = HIY"$p�ִټ��æ���֣�˫���漴�ཻ��ֻ�������ۡ����������죡�������ɵ���ɫѪ������������޻�һ�㡣\n"NOR;
  
  neili = me->query("neili");
  neili2 = target->query("neili");
  
  if( me->query_skill("force",1) < target->query_skill("force",1)/3
     && neili < neili2/3)
 {
         msg += "�����ഥ֮�£�$n��ռ�Ϸ磬��$Nһ�������˿�����\n";
         damage = target->query_skill("force",1) / 2;
         me->receive_damage("qi", damage,  target);
         me->receive_wound("qi", damage/2, target);
         p = (int)me->query("qi")*100/(int)me->query("max_qi");
         msg += damage_msg(damage, "����") + "( $N"+eff_status_msg(p)+" )\n";     
  }
  else if( me->query_skill("force",1) < target->query_skill("force",1)/3*2
         || neili < neili2/3*2)        
         msg += "�����ƴ֮�£����˶�����һ�Σ�˭Ҳû��ռ���ô���\n";
            
  else {
         damage = me->query_skill("xuedao-jing",1) +me->query_skill("hongsha-zhang",1)+ jiali * (5+random(5));
         if(neili > neili2*2) damage *= 2;
         if (userp(target)) damage= damage*2 +random(1000);
         else damage=damage+500+random(1000);
		// if( userp(target)&& damage > 2000) damage = 2000;
         
		 if(damage < 1500) damage = 1500;         
           
         target->add_busy(1+random(2));
         target->receive_damage("qi", damage,  me);
		 
		 if (!userp(target))
		     target->receive_wound("qi", damage/2, me);
		 else target->receive_wound("qi", random(damage/3), me);
		 
		 if (me->query_temp("xdj/yuxue"))
		    target->add_condition("neishang_poison",1);
         p = (int)target->query("qi")*100/(int)target->query("max_qi");
         msg +=HIR+damage_msg(damage, "����") +NOR+ "( $n"+eff_status_msg(p)+" )\n"; 
         //if(target->is_killing(me->query("id"))
           // || me->is_fighting(target->query("id")))
         if (me->is_fighting()
			 &&objectp(target)
			 &&me->query_skill("hongsha-zhang",1)>=120)
            	 call_out("perform2", 0, me, target, p, damage);
                 
			//call_out("remove_effect", p, me);
         }
		message_vision(msg, me, target);
		
		me->start_busy(1+random(1));
		me->start_perform(3,"��ɰ���ƾ���");
		return 1;
}

int perform2(object me, object target, int p, int damage)
{
        string msg, dodge_skill;

        if( !target || !target->is_character() ||  !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target))
                return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( (int)me->query("neili") < me->query_skill("force")*2 )
                return notify_fail("���Ҫ�ٷ�һ�ƣ�ȴ�����Լ������������ˣ�\n");     

        msg = HIR "\n$N"HIR"���а�������������ˡ���˫�ƺ�Ȼ�Ƴ���$n"HIR"�����ٴ���������Ȼ������$P����������ɽ������ѹ����\n"NOR;        
        if ( me->query("neili") > target->query("neili") / 2 
        || random(me->query_str())>target->query_str()/2  
		|| random( me->query("combat_exp") ) > target->query("combat_exp")/3){
                me->start_busy(1);
                me->receive_damage("neili", me->query_skill("force",1)*3);
                me->receive_damage("jingli", 20);                              
                damage = damage*2;
                if(me->query("neili") > target->query("neili")*2 ) 
                       damage += random(damage);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);

                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg +=RED+ damage_msg(damage, "����")+NOR + "( $n"+eff_status_msg(p)+" )\n"; 
        } 
        else 
        {
                me->start_busy(3);
                me->add("neili", -100);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target); 
		me->start_perform(4,"��ɰ���ƾ���");
        return 1;
}
int help(object me)
{
	write(RED"\n��ɰ��֮����ɰ���ơ���"NOR"\n\n");
        write(@HELP
	��ɰ������Ѫ���ŵ��������似����ɰ����ȡ��ѩɽ
	�綾֮���������Ѫ�������ö���֮��ѪҺ�д���
	���ԡ�ͬʱ��ΪѪҺ���̺���Щ����֮�������ɰ��
	����Ѫ���ŵ��ķ�ȴ������֮�⡣
	��ɰ���ƾ���ƾ�������ɰ��֮���ͶԷ�Ӳƴ������
	������ƴ�⣬ͬʱ�öԷ����˺�ɰ֮�����˵����ն�
	��֡�ע�⣬120������к��б仯��
	
	ָ�perform strike.hongsha

Ҫ��
	�������  1500 ���ϣ�
	��ǰ����  500  ���ϣ�
	Ѫ����  100  �����ϣ�
	��ɰ�Ʒ�  100  �����ϣ�
HELP
        );
        return 1;
}