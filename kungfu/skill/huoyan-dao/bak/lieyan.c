//2006��12��24��KinGSo�±༭,���HELP
// lieyan.c  ���浶 [����]
// �޸�by hongba kingso������̫��å����cutһ������������һ���Ѷ�
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
string perform_name(){ return HBRED HIR "����"NOR; }
int perform(object me, object target)
{
        int damage, p;
        int lieyan;
        string msg;
        
        if( !target ) target = offensive_target(me);

        
        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("�����桹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������\n");   
        if( (int)me->query_skill("huoyan-dao",1) < 250 )
                return notify_fail("����Ʒ���Ϊ���㣬ʹ�������档\n");
        if( (int)me->query("neili") < 2000 )
                return notify_fail("����������̫�������ܴ�����档\n");
        if( (int)me->query("max_neili") < 4000 )
                return notify_fail("������������Ϊ̫�������ܴ�����档\n");

        if( (int)me->query("jiali") < 50 )
                return notify_fail("�����ڼ�����ô������ôʹ�����档\n");
        if (me->query_skill_prepared("strike") != "huoyan-dao"
            || me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("�������޷�ʹ�����棡\n");
                
        
        msg = HBRED HIR "ֻ��$N˫�ֺ�����ǰ�����б���һ�����ȵ���������һ��"HIY"ȼ�յ�����"HIR",������$n��\n"
                        "ͻȻ��$N˫��ƽ�ƣ������Ÿ��ܶȵ�������������$n���˹�ȥ��\n"NOR;
                       
        if (me->query_skill("strike")  > target->query_skill("strike")*3/4)
                   {
                me->start_busy(1);
              //  lieyan = (int)me->query_skill("strike") /60; ���û����
              // damage = (int)me->query_skill("strike"); ���̫����
                 damage = (int)me->query_skill("strike"); 
                damage += random(me->query("jiali") * 100);
                damage *= 3;
                if(target->query("neili") < me->query("neili")) damage *= 2;
             //   if (damage>8500) damage=7000+random(9000);  ��Ҳ���ݰ�
               if (damage>2500) damage=2500;  
                
                me->add("neili", -1500);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HBRED HIY "ֻ������¡һ�����죬$n���������ź��˸����ţ����$n��ط���,�۶��ڱ�ȫ������Ѫ,����ɲ���\n"NOR;
                if(damage>= target->query("qi",1)) damage= target->query("qi",1)-1;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                target->start_busy(1);
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
                if(me->query_skill("strike")*2 > target->query_skill("strike")*3 /2)
                call_out("perform2", 1, me, target, p, damage); 
                
        }
else {
                me->start_busy(2);
                msg += HIW"$n������"HBRED ""HIR"����"NOR""HIW"������������ͣ�Ӳƴ�϶������ܾ����Ľ�֣�����һ����Ծ�㿪�����С�\n"NOR;

                      }

        message_vision(msg, me, target);
        me->start_perform(3,"����"); // busy ��һ��
        return 1;
}

int perform2(object me, object target)
{  
       string msg, dodge_skill;
       int lev;
       int damage;
       int p;
       lev = me->query_skill("huoyan-dao", 1);
       
       p = (int)target->query("qi")*100/(int)target->query("max_qi");
       damage = (int)me->query_skill("strike"); 
        if( !target || !me || !living(me)
           || !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target)
           || (int)me->query("neili") < 500)
                return 0;

       
         message_vision(HBRED HIW "$N����$nѪ������,��������֮ʱ,��ͻȻ���٣��Ƶ�$n������Ŵ���ʹ��ɱ�֣��������ƣ�\n"NOR,me, target);
    
         // ���ܼ�must be hit������������   
// target->start_busy(1);
                
               
           if (me->query_dex() > target->query_dex())
target->set_temp("must_be_hit",1);

                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                   if ( me->is_fighting(target) )
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                 if ( me->is_fighting(target) )
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                  if ( me->is_fighting(target) )
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                  if ( me->is_fighting(target) )
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

         
         if (random(me->query_skill("strike")*4) > target->query_skill("dodge"))
        
           {

               me->add_temp("apply/strike", lev/4);
                 me->add_temp("apply/attack", lev*10);
                  me->add_temp("apply/damage", lev*5);
                  me->add_temp("apply/strength", lev/4);
                target->delete_temp("must_be_hit",1);

                msg = HBRED HIY "�������顯����������֮����������$N�������������Ѹ�������$n���ϣ�ÿһ�ƾ���$n���һ����Ѫ��\n"NOR;
               msg += "( $n"+eff_status_msg(p)+" )\n"; 
            // ȥ���Ǹ�ʲô���˵�����
               
                

                me->add("neili", -500);
                me->add("jingli", -200);   
          
               me->add_temp("apply/strength", -lev/4);
                me->add_temp("apply/strike", -lev/4);
                me->add_temp("apply/attack", -lev*10);
                me->add_temp("apply/damage", -lev*5);

                target->start_busy(1);
                target->apply_condition("hyd_condition",8); // ������浶����
                 me->start_busy(2);
                   if (me->query("neili") < 0)
                      me->set("neili",0);
                 
               me->add("neili", -1500);
                me->add("jingli", -200);  
                
         
            } 
        else 
        {
         
                msg = HIY "$n" HIY "���Է�������˺��ţ����������ܲ��������ѱ�����"
                      "����ǿ��һ������������غ�«�㣬�Ǳ��Ķ��˿�ȥ�����Ѵ�����Ԫ��\n" NOR; 
        
               me->add("neili", -500);
                me->add("jingli", -200);  
                target->add("max_neili", -random(500));                            
                target->start_busy(2);
                target->add("neili", -random(5000));

                 me->start_busy(3);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                if (target->query("neili") < 0)
                      target->set("neili",0);


        }
        message_vision(msg, me, target); 
me->start_perform(5, "�����桹");  // busy��һ�㣬ԭ����8��

        return 1;
}

int help(object me)
{
	write(HIR"\nѩɽ�ؼ������桹��"NOR"\n");
	write(@HELP
	���浶����������˼���Ϊ���浶�ռ����塣
       �ݴ�����һ����û���˻���վ�š�
       

	Ҫ��	������� 4000 ���ϣ�
		����     2000  ���ϣ�
              ���浶   �ȼ� 250 ���ϣ�
		
HELP
	);
	return 1;
 }
