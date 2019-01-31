// lushuang.c ��˪����
// by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
  string msg, dodge_skill;
  int damage, p, jiali, skill, neili, neili2;

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) 
      || environment(target)!=environment(me) || !living(target))
         return notify_fail("����˪������ֻ����ս�����á�\n");

  if( me->query_temp("weapon")) 
         return notify_fail("���������������ʹ�ó�����˪��������\n");
         
  if( me->query_temp("combat_yield") )
         return notify_fail("�㲻���֣����ʹ�ó�����˪��������\n");
  if( !me->query("quest/gb/xlz/slbw/pass") )
         return notify_fail("����δ�õ����߹����ڴ��У����ʹ�ó�����˪��������\n");
  if( (int)me->query_temp("xlz/lushuang") )
         return notify_fail("���ʩչ�꡸��˪���������ȵ�Ϣһ�°ɣ�\n");
         
  if( (skill = (int)me->query_skill("xianglong-zhang", 1)) < 450 )
         return notify_fail("��Ľ���ʮ���Ʋ�����죬����ʹ����˪��������\n");

  if( (int)me->query_skill("huntian-qigong", 1) < 450 )
         return notify_fail("��Ļ���������򲻹�������ʹ�á���˪��������\n");

  if( me->query_skill_mapped("force") != "huntian-qigong")
         return notify_fail("�����õ��ڹ��͡���˪�������໥��ͻ��\n");

  if (me->query_skill_prepared("strike") != "xianglong-zhang" ||
      me->query_skill_mapped("strike") != "xianglong-zhang"
      ||me->query_skill_mapped("strike") != "xianglong-zhang")
         return notify_fail("������Ƚ�����ʮ�����������Ʒ�֮�в��С�\n");

  if( (jiali = (int)me->query("jiali")) < 200 )
         return notify_fail("����ʮ����������Ҫ����������ôʹ�ó�����˪����������\n");
  if( (int)me->query_str() < 60 )
         return notify_fail("��˪������Ҫ�ϸߵı��������������60������ʩչ����˪��������\n");
  if( (neili = (int)me->query("neili")) < 3000 )
         return notify_fail("����������㣬����ʩչ����˪��������\n");
  if( (int)me->query("max_neili") < 8000 )
         return notify_fail("����������㣬����ʩչ����˪��������\n");
  if( (int)me->query("jingli") < 1500 )
         return notify_fail("��ľ������㣬����ʩչ����˪��������\n");

  me->set_temp("xlz/lushuang",5);
  me->receive_damage("neili", 1200);
  me->receive_damage("jingli", 200);
 // me->start_perform(2,"��˪����");
  message_vision(HBBLU+HIW"$N����һ��������������΢̧����ȭ���ƣ�ֱ�����ƣ�������һ��һ���Ĵ򽫳�ȥ��\n"NOR,me,target);
  message_vision(HBBLU+HIW"$N��һ��֮�и��Ტ�ã�������ɣ�ʵ������������ǽ����ƾ�������˪��������\n"NOR,me,target);
  if( random( me->query("combat_exp") ) < target->query("combat_exp")/2 && userp(target)) {
         dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         msg = HIW"$n�о�$N�������쳣�������һ�������ת���У������Լ�վ�����ȣ����гԾ��������С�\n" + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
         message_vision(msg+NOR, me, target);         
         }
  
  msg =HIB "$n�о�$N�����о���������������֮�䣬�Լ���������һ�������У����������������Լ�վ�����ȣ�\n"NOR;
  neili = me->query("neili");
  neili2 = target->query("neili");
  if (me->query_skill("jiuyin-zhengong",1)>450)
  {
     message_vision(HIR"$N����"HIW"�����湦"HIR"����ʱ�����Ѵ����֮��������������������˸����.\n"NOR);
	 //skill=skill+me->query_skill("jiuyin-zhengong",1)/4;
  }
  target->add_busy(2+random(2));
//˫���Ա�������

  if( me->query_skill("force",1) < target->query_skill("force",1)/2
     && neili < neili2/2){
         msg +=HIG "���˫����ƴ֮�£�$nȫ�����������������������$N�����ȥ��\n";
         damage = target->query_skill("force",1) * 2;
         me->receive_damage("qi", damage, target);
         me->receive_wound("qi",damage/2, target);
         p = (int)me->query("qi")*100/(int)me->query("max_qi");
         msg += damage_msg(damage, "����") + "( $N"+eff_status_msg(p)+" )\n";     
         }
  else if( me->query_skill("force",1) < target->query_skill("force",1)/3*2
         && neili < neili2/3*2)        
         msg +=HIC "�����ƴ֮�£����˶�����һ�Σ�˭Ҳû��ռ���ô���\n"NOR;
            
  else {
         msg+=HIY"$nֻ���Լ�����ײײ�������Լ��������Լ����������������º��������������ޱȡ�\n"NOR;
		 damage =me->query_skill("xianglong-zhang",1) + me->query_skill("force",1) +me->query_skill("huntian-qigong",1)+ jiali * (3+random(5));
		 damage=damage+random(damage);
		 if (me->query("gender")=="����") damage*=3;		 
         if(neili > neili2*2) damage *= 2;
         if(userp(me)&& damage > 4000) damage = 4000;
         if(damage < 1000) damage = 1000;         
           
         if(random(3)) {
          target->apply_condition("no_fight",1);
		 //target->set_temp("no_fight",1);
		 }
         target->receive_damage("qi", damage,  me);
         target->receive_wound("qi", damage/3, me);
         //p = (int)target->query("qi")*100/(int)target->query("max_qi");
         msg += damage_msg(damage, "����") + "( $n"+eff_status_msg(p)+" )\n"; 
         if(objectp(target)&&me->is_fighting())
            call_out("perform2", 0, me, target, p, damage);
         else call_out("remove_effect", 3, me);		 
		 
		        
         //p = 5;
         //if(p < 7) p = 7;
         //call_out("remove_effect", p, me);
   }
         message_vision(msg, me, target);
		 
		 message_vision(HIY"$N����ɽ���������˸��������"HIW"��"NOR"ת"HIR"��"HIY"��$n��Щ�����޷���Ӧ�������ı仯��ˣ�ֻ�ܱ�������!\n"NOR,me,target);
		 me->add_temp("apply/attack",(int)me->query_skill("xianglong-zhang",1)/3);
		 me->add_temp("apply/damage",(int)me->query_skill("xianglong-zhang",1)/5);

		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		 me->add_temp("apply/attack",-(int)me->query_skill("xianglong-zhang",1)/3);
		 me->add_temp("apply/damage",-(int)me->query_skill("xianglong-zhang",1)/5);
		 call_out("remove_effect",4,me);
		 me->start_perform(4,"��˪����");
         return 1;
}

int perform2(object me, object target, int p, int damage)
{
        string msg, dodge_skill;
		int skill;
		skill=me->query_skill("xianglong-zhang",1);

        if( !target || !target->is_character() ||  !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target))
                return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( (int)me->query("neili") < me->query_skill("force",1) )
                return notify_fail("���Ҫ�ٷ�һ�ƣ�ȴ�����Լ������������ˣ�\n");     

        msg = HBRED+HIY"\n$n"HBRED+HIY"�������ε���ײײ֮�䣬$N"HIY"��������Ȼ����һ�ɸ��͵�����֮��������ʮ���Ʊ��Ǵ�������һ·��\n"+
			"���յ���������Ȼ��Ȼ�ĸ������ᣡ���д��ա�\n"NOR;        
       if ( me->query("neili") > target->query("neili") / 2 
          || random( me->query("combat_exp") ) > target->query("combat_exp")/3){
                //me->start_busy(2);
                me->receive_damage("neili", me->query_skill("force")*2);
                me->receive_damage("jingli", 20);                              
                if (me->query("gender")=="����")
                damage = damage*2;
				
                if(me->query("neili") > target->query("neili")*2 ) 
                       damage += random(damage);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
				target->apply_condition("no_force",1+random(1));
				target->apply_condition("no_perform",1+random(1));
				if (damage<target->query("neili"))
					target->add("neili",-damage);
				else target->receive_damage("neili",target->query("neili")-100);
				message_vision(HIB"��\n"NOR,me,target);
				//target->add_busy(1);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += damage_msg(damage, "����") + "( $n"+eff_status_msg(p)+" )\n"; 
        } 
        else 
        {
                me->start_busy(3);
                me->add("neili", -200);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += HIW+SKILL_D(dodge_skill)->query_dodge_msg(target, 1)+NOR;
        }
         message_vision(msg, me, target); 
		 me->add_temp("apply/damage",skill/4);
		 me->add_temp("apply/attack",skill/3);
		 me->add_temp("apply/strike",skill/4);
		 if (objectp(target)&&me->is_fighting())
		 {
		
			message_vision(HBYEL+HIR"$Nһ�ƽ�һ�Ƶķ�������ʱ$N�Ľ�������Ȼ�ڻ��ͨ����ʽ���ް���ɬ�������ƵĴ��������˷��ԣ�\n"NOR,me,target);
			target->set_temp("must_be_hit",1);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			target->delete_temp("must_be_hit");
		 
			me->add_temp("apply/damage",-skill/4);
			me->add_temp("apply/attack",-skill/3);
			me->add_temp("apply/strike",-skill/4);
		}
		me->start_perform(4,"��˪����");
		call_out("remove_effect",4,me);
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("xlz/lushuang");
        if(living(me))
            tell_object(me, "\n�㽫�����������գ��ֿ���ʹ�á���˪�����������ˡ�\n"); 
}
string perform_name(){ return HBRED+CYN"��˪"+HIW"����"NOR; }
int help(object me)
{
        write(HBBLU+HIW"\n����ʮ���Ʒ�֮����˪��������"NOR"\n\n");
        write(@HELP 
	����ʮ�����������ֵ�һ���ؤ��������������֮һ���������Ტ
	�ã�������գ��������ᣬ���ظ��������������վ��ᾢ���Ϊһ��
	������ǿ���������̺��£�������֮���������ᣬ�������յ�һ����
	��֮�������˫����������������˵��������ѧ�е��۷���裬��
	�����Ƽ����棬���������������������������ʽ������������
	����书����Ҫ֮����ȫ���˾�������ȫƾ��ǿ����ȡʤ����������
	�᲻�ݡ��޹̲��ƣ����������ޣ���ÿ��һ�ƾ���������Х֮�ơ�ÿ
	��һ�о��߾����������
	����ʮ���Ʊ���õ������Ĵ��ڷ���ϰ�ã�������˪���������ǽ���
	�����վ���֮һ���������������ʩչ���˺��߹������ڱ�Ӧ������
	����������һ��֮�и��Ტ�ã�������ɣ�ʵ�����������Ҫ���
	�߹���̡�
	
	ָ�perform strike.lushuang

Ҫ��	
	������� 8000 ���ϣ�
	��ǰ���� 3000 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	�����Ƶȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	��Ҫ���������� 200��
	��Ч���� 60 ���ϣ�
	�����Ʒ������ƣ�
	�����ڹ�Ϊ����������
	�����м�Ϊ�����ơ�
HELP
        );
        return 1;
}
