// junji.c
// by snowman@SJ 13/05/99

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return WHT"��������"NOR;}

int perform(object me, object target)
{
  string msg, dodge_skill;
  int damage, p, jiali, skill, neili, neili2;
  int focus = me->query_temp("ss/focus");

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) 
      || environment(target)!=environment(me) || !living(target))
         return notify_fail("���������ơ�ֻ����ս�����á�\n");

  if( me->query_temp("weapon")) 
         return notify_fail("���������������ʹ�ó����������ơ���\n");
         
  if( (skill = (int)me->query_skill("songyang-shou", 1)) < 200 )
         return notify_fail("��Ĵ������ֲ�����죬����ʹ���������ơ���\n");

  if( (int)me->query_skill("hanbing-zhenqi", 1) < 200 )
         return notify_fail("����ڹ���򲻹�������ʹ�á��������ơ���\n");

  if( me->query_skill_mapped("force") != "hanbing-zhenqi")
	  if( me->query_skill_mapped("force") != "lengquan-shengong")
         return notify_fail("�����õ��ڹ��͡��������ơ��໥��ͻ��\n");

  if (me->query_skill_prepared("hand") != "songyang-shou" ||
      me->query_skill_mapped("hand") != "songyang-shou")
         return notify_fail("������Ƚ����������������ַ�֮�в��С�\n");

  if( (jiali = (int)me->query("jiali")) < 50 )
         return notify_fail("�����ϲ�����������ôʹ�ó����������ơ�����\n");

  if( (neili = (int)me->query("neili")) < 500 )
         return notify_fail("����������㣬����ʩչ���������ơ���\n");
  if( (int)me->query("max_neili") < 1500 )
         return notify_fail("����������㣬����ʩչ���������ơ���\n");
  if( (int)me->query("jingli") < 300 )
         return notify_fail("��ľ������㣬����ʩչ���������ơ���\n");

  me->receive_damage("neili", random(100) );
  me->receive_damage("jingli", 50);
  msg = HIC "\n����ζ���ֻ����ž����һ���죬$N"HIC"����ǰ������$n"HIC"Ѹ�ٻ���һ�ƣ�\n";

  if( random( me->query("combat_exp") ) < target->query("combat_exp")/3) {
         dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         msg += "�Ʒ�����������С�ӣ�\n"NOR + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
         message_vision(msg, me, target);
         return 1;
         }
 
  
  msg += HIY"$p��æ���֣�˫���漴�ཻ��\n"NOR;
  neili = me->query("neili")*(focus+1);
  neili2 = target->query("neili");
  
  if( me->query_skill("force",1) < target->query_skill("force",1)/2
     && neili < neili2/2){
         msg += "�����ƴ֮�£�$n��ռ�Ϸ磬��$Nһ�������˿�����\n";
         damage = target->query_skill("force",1) / 2;
         me->receive_damage("qi", damage,  target);
         me->receive_wound("qi", damage/2, target);
         p = (int)me->query("qi")*100/(int)me->query("max_qi");
         msg += RED+damage_msg(damage, "����") +NOR+ "( $N"+eff_status_msg(p)+" )\n";     
         }
  else if( me->query_skill("force",1) < target->query_skill("force",1)/3*2
         || neili < neili2/3*2)        
         msg += "�����ƴ֮�£����˶�����һ�Σ�˭Ҳû��ռ���ô���\n";
            
  else {
         damage = me->query_skill("hanbing-zhenqi",1) +me->query_skill("songyang-shou",1)+ jiali * (5+random(5))*focus;
         if(neili > neili2*2) damage *= 2;
         if (userp(target)) damage= damage +random(1000);
         else damage=damage+500+random(1000);
		// if( userp(target)&& damage > 2000) damage = 2000;
         if(damage < 1500) damage = 1500;         
         if(damage > 3000) damage = 3000;         
         if(!target->is_busy())
                 target->start_busy(1+random(2));
		 if (damage>2000&&userp(target))
         {
					damage=2000+random(1000);
         }
         target->receive_damage("qi", damage,  me);
		 
		 if (!userp(target))
		     target->receive_wound("qi", damage/2, me);
		 else target->receive_wound("qi", damage/4, me);
		 if (me->query_temp("ss/hb")){
			 message_vision(HIB"$N���𺮱��������������£�һ�ɼ�������ĺ�����������$n�ľ���!\n"NOR,me,target);
		     target->add_condition("cold_poison",1);
		 }
         p = (int)target->query("qi")*100/(int)target->query("max_qi");
         msg += HIW+damage_msg(damage, "����")+NOR + "( $n"+eff_status_msg(p)+" )\n"; 
         //if(target->is_killing(me->query("id"))
           // || me->is_fighting(target->query("id")))
         if (me->is_fighting()
			&&objectp(target)
			&&me->query_skill("songyang-shou",1)>120)
            	 call_out("perform2", 0, me, target, p, damage);
                 
         }
		message_vision(msg, me, target);
		me->start_busy(1+random(1));
		me->start_perform(3,"��������");
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

        msg = WHT "\n$N"WHT"΢΢һЦ��˫�ƶ�Ȼ�ཻ��$n"WHT"�����ٴ���������Ȼ������$P����������ɽ������ѹ����\n"NOR;        
        if ( me->query("neili") > target->query("neili") / 2 
        || random(me->query_str())>target->query_str()/2  
		|| random( me->query("combat_exp") ) > target->query("combat_exp")/3){
                target->start_busy(1);
                me->receive_damage("neili", me->query_skill("force",1));
                me->receive_damage("jingli", 100);                              
                damage = damage*2;
                if(me->query("neili") > target->query("neili")*2 ) 
                       damage += random(damage);
                if (damage>3500) damage=3500;
               
				if (damage>2500&&userp(target))
                {
					damage=2500+random(1000);
                }
				target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HIW+damage_msg(damage, "����") +NOR+ "( $n"+eff_status_msg(p)+" )\n"; 
        } 
        else 
        {
                me->start_busy(3);
                me->add("neili", -200);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target); 
		me->start_perform(3,"��������");
        return 1;
}
int help(object me)
{
	write(HIW"\n��������֮��������������"NOR"\n\n");
        write(@HELP
	��������������ɽ���������似����������ȡ��ɽ��
	����֮�⣬�������书���̺����⾳ȥ����С���
	�е��ص��������Լ�ǿ�������Լ������ͶԷ����ƶ�
	�ƿ��⣬���������������ߣ����ô��У��ٸ����Զ�
	���ھ��������������ʹ�öԷ�����ʤ������Ȼ����
	�ȶԷ������ͣ����Ϊ�Է�����������ɽ�������
	��ʹ�á�ע�⣬120������к��б仯��
	
	ָ�perform hand.junji

Ҫ��
	�������  1400 ���ϣ�
	��ǰ����  500  ���ϣ�
	��ǰ����  300  ���ϣ�
	��������  200  �����ϣ�
	��������  200  �����ϣ�
	�����ַ�Ϊ�����֣�
	�����м�Ϊ������
	�����ڹ�Ϊ���������������ڹ�;
	���ַ�Ϊ�����֣�
	���֣�
HELP
        );
        return 1;
}