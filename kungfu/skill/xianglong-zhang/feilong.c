// feilong.c ��������
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
         return notify_fail("���������졹ֻ����ս�����á�\n");

  if( me->query_temp("weapon")) 
         return notify_fail("���������������ʹ�ó����������졹��\n");
         
  if( me->query_temp("combat_yield") )
         return notify_fail("�㲻���֣����ʹ�ó����������졹��\n");

  if( (int)me->query_temp("xlz/feilong") )
         return notify_fail("���ʩչ�꡸�������졹���ȵ�Ϣһ�°ɣ�\n");
         
  if( (skill = (int)me->query_skill("xianglong-zhang", 1)) < 400 )
         return notify_fail("��Ľ���ʮ���Ʋ�����죬����ʹ���������졹��\n");

  if( (int)me->query_skill("huntian-qigong", 1) < 400 )
         return notify_fail("��Ļ���������򲻹�������ʹ�á��������졹��\n");

  if( me->query_skill_mapped("force") != "huntian-qigong")
         return notify_fail("�����õ��ڹ��͡��������졹�໥��ͻ��\n");

  if (me->query_skill_prepared("strike") != "xianglong-zhang" ||
      me->query_skill_mapped("strike") != "xianglong-zhang"
      ||me->query_skill_mapped("strike") != "xianglong-zhang")
         return notify_fail("������Ƚ�����ʮ�����������Ʒ�֮�в��С�\n");

  if( (jiali = (int)me->query("jiali")) < 200 )
         return notify_fail("����ʮ����������Ҫ����������ôʹ�ó����������졹����\n");
  if( (int)me->query_dex() < 40 )
         return notify_fail("����������Ҫ�ϸߵ�������������40������ʩչ���������졹��\n");
  if( (neili = (int)me->query("neili")) < 3000 )
         return notify_fail("����������㣬����ʩչ���������졹��\n");
  if( (int)me->query("max_neili") < 5000 )
         return notify_fail("����������㣬����ʩչ���������졹��\n");
  if( (int)me->query("jingli") < 1500 )
         return notify_fail("��ľ������㣬����ʩչ���������졹��\n");

  me->start_busy(1+random(2));
  me->receive_damage("neili", 800);
  me->receive_damage("jingli", 100);
  
  message_vision(HBRED"$N���ӷ�Ծ�����ڿ���ͷ���£�˫�ƽ����ĳ����Ӹ��»�������������ǽ������С��������졹��\n"NOR,me,target);
  if( random( me->query("combat_exp") ) < target->query("combat_exp")/2&&userp(target)) {
         dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         msg = HIC"$n�о�$N���Ʒ��쳣������������������С�\n" + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
         message_vision(msg+NOR, me, target);
         return 1;
         }
  
  msg =HIY "$n��֪��$N���е��������أ���æ���֣�˫���漴�ཻ��\n"NOR;
  neili = me->query("neili");
  neili2 = target->query("neili");
  
  if( me->query_skill("force",1) < target->query_skill("force",1)/2
     && neili < neili2/2){
         msg +=HIG "���˫����ƴ֮�£�$nȫ�����������������������$N�����ȥ��\n";
         damage = target->query_skill("force",1) * 2;
         me->receive_damage("qi", damage, target);
         me->receive_wound("qi", random(damage/2), target);
         p = (int)me->query("qi")*100/(int)me->query("max_qi");
         msg += damage_msg(damage, "����") + "( $N"+eff_status_msg(p)+" )\n";     
         }
  else if( me->query_skill("force",1) < target->query_skill("force",1)/3*2
         && neili < neili2/3*2)        
         msg += "�����ƴ֮�£����˶�����һ�Σ�˭Ҳû��ռ���ô���\n";
            
  else {
         damage = me->query_skill("force",1) +me->query_skill("huntian-qigong",1)+ jiali * (3+random(5));
		 damage=damage+me->query_skill("xianglong-zhang",1)+me->query_skill("strike",1);
		 if (me->query("gender")=="����") damage*=3;		 
         if(neili > neili2*2) damage *= 2;
         if(!userp(me) && damage > 3000) damage = 3000;
         if(damage < 1500) damage = 1500;         
           
         if(!target->is_busy())
                 target->start_busy(1+random(2));
         target->receive_damage("qi", damage,  me);
         target->receive_wound("qi", damage/2, me);
         p = (int)target->query("qi")*100/(int)target->query("max_qi");
         msg += damage_msg(damage, "����") + "( $n"+eff_status_msg(p)+" )\n"; 
         if(target->is_killing(me->query("id"))
            || me->is_killing(target->query("id")))
                 call_out("perform2", 0, me, target, p, damage);
                 
         p = 30 - skill/10;
         if(p < 7) p = 7;
         call_out("remove_effect", p, me);
         }
         message_vision(msg, me, target);

  return 1;
}

int perform2(object me, object target, int p, int damage)
{
        string msg, dodge_skill;

        if( !target || !target->is_character() ||  !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target))
                return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( (int)me->query("neili") < me->query_skill("force",1) )
                return notify_fail("���Ҫ�ٷ�һ�ƣ�ȴ�����Լ������������ˣ�\n");     

        msg = HIY "\n$n"HIY"û����ʶ��$N���е����������������ٴ���������Ȼ������$N"HIY"����������ɽ������ѹ����\n"NOR;        
        if ( me->query("neili") > target->query("neili") / 2 
          || random( me->query("combat_exp") ) > target->query("combat_exp")/3){
                //me->start_busy(2);
                me->receive_damage("neili", me->query_skill("force")*2);
                me->receive_damage("jingli", 20);                              
                damage = damage*2;
                if(me->query("neili") > target->query("neili")*2 ) 
                       damage += random(damage);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
				target->apply_condition("no_force",1+random(1));
				if (damage<target->query("neili"))
					target->receive_damage("neili",damage);
				else target->receive_damage("neili",target->query("neili")-100);
				message_vision(HIB"�ܵ���ɾ޴�������𶯣�$n�о�������֫�ٺ��·���ɢ���Ƶģ�һ�����������ؿڡ�\n"NOR,me,target);
				target->add_busy(1);
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
        me->start_perform(4,"���������졹");
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("xlz/feilong");
        if(living(me))
            tell_object(me, "\n��������ӿ���Դ�ƽϢһ��ʱ������ʹ�á��������졹�ˡ�\n"); 
}
string perform_name(){ return HBRED+HIW"��������"NOR; }
int help(object me)
{
        write(HBRED"\n����ʮ���Ʒ�֮���������졹��"NOR"\n\n");
        write(@HELP 
	����ʮ�����������ֵ�һ���ؤ��������������֮һ���������Ტ�ã�������գ�
	�������ᣬ���ظ��������������վ��ᾢ���Ϊһ��������ǿ���������̺��£���
	����֮���������ᣬ�������յ�һ���Ʒ�֮�������˫����������������˵����
	����ѧ�е��۷���裬�������Ƽ����棬���������������������������ʽ��
	��������������书����Ҫ֮����ȫ���˾�������ȫƾ��ǿ����ȡʤ���������޼�
	���ݡ��޹̲��ƣ����������ޣ���ÿ��һ�ƾ���������Х֮�ơ�ÿ��һ�о��߾���
	��������
	����ʮ���Ʊ���õ������Ĵ��ڷ���ϰ�ã������������졹���ǽ��������վ���֮
	һ���������������ʩչ��
	
	ָ�perform strike.feilong

Ҫ��	
	������� 5000 ���ϣ�
	��ǰ���� 3000 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	�����Ƶȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	��Ҫ���������� 200��
	��Ч�� 40 ���ϣ�
	�����Ʒ������ƣ�
	�����ڹ�Ϊ����������
	�����м�Ϊ�����ơ�
HELP
        );
        return 1;
}
