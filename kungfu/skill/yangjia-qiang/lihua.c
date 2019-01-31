//  lihua.c �����滨 
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

 string perform_name(){ return HIG"�����滨"NOR; }
int perform(object me, object target)
{
        object weapon, ob;
        int speed, attack, lv, damage;

        lv = (int)me->query_skill("yangjia-qiang", 1); 
        damage = lv + random(lv/2) + (int)me->query_skill("spear",1);
        attack = lv + random(lv/2);
        speed = me->query_skill("spear")/80;

        if( !target ) target = offensive_target(me);

        if( !target ||  !living(target) ||!target->is_character() || !me->is_fighting(target) )
	               return notify_fail("�������滨��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("yjq/lihua"))
	               return notify_fail("������ʹ�á������滨����\n");
	               
	      if( me->query_temp("lihua"))
	               return notify_fail("���ʹ�ù��������滨�����ٵ�������Ϣ�ɣ�\n");

        if (!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "spear"
          || me->query_skill_mapped("spear") != "yangjia-qiang")
         // || me->query_skill_mapped("parry") != "yangjia-qiang"
                 return notify_fail("��������ǹ�����ʹ�á������滨����\n");
                 
        if((int)me->query("max_neili") < 15000 )
               return notify_fail("���������Ϊ�������޷�ʹ�á������滨����\n");

        if( (int)me->query("neili") < 2000 )
	             return notify_fail("�������������\n");

        if( me->query_skill("yangjia-qiang", 1) < 450 )
	              return notify_fail("��ġ����ǹ���ȼ��������޷�ʹ�á������滨����\n");
	               
        if( me->query_skill("spear", 1) < 450 )
                return notify_fail("��ġ�����ǹ�����ȼ��������޷�ʹ�á������滨����\n");
                 
        if( (int)me->query_con() < 25 )
		            return notify_fail("���������ǲ��㣬�������滨������������˵������̫���ˡ�\n");

        message_vision(HIC "\n$Nͻ�л����������������ޱȣ���"+weapon->query("name")+HIC"���ͻȻ�ٸ��������ģ���Ȼ��$n�ؿ��籩�������ͻ��\n"+
                            "ֻ��"+weapon->query("name")+HIC"ǹ�浽��ͻ�Գ�����"HIG"�����滨"HIC"����������ǹ���Ʋ��ɵ�,ʹ��Ŀ��Ͼ�ӣ��������ǹ֮��ּ��"NOR"\n" NOR, me,target);
        me->start_perform(5+random(3), "�������滨��");
        ob = me->select_opponent();
        me->set_temp("lihua",4);
        me->set_temp("yjq/lihua",1);
        call_out("checking", 1, me,target);
        return 1;
}

void checking(object me, object target, int speed, int damage, int attack)
{

        object weapon;
	      if ( !objectp( me ) ) return;
        weapon = me->query_temp("weapon");

        if (!objectp(weapon = me->query_temp("weapon"))
			|| me->query_skill_mapped("spear")!="yangjia-qiang"
		    || me->query_skill_mapped("parry")!="yangjia-qiang"
            || (string)weapon->query("skill_type") != "spear") {
		       tell_object(me, "\n��������ǹ������ֹͣ�˱����滨�ļ��ơ�\n" NOR);
		       me->delete_temp("lihua");
		       me->delete_temp("yjq/lihua");
		       return;
	    }
//�滨��һ��
        if ( me->query_temp("lihua") ==4 && objectp(target) && me->is_fighting(target))
         message_vision(HIM"\nֻ��"+weapon->name()+HIM"��Ȼ�ŷ���ǹ������ֱ��$n����"HIG"�����滨"HIM"����Ȼ�����������ٶȿ��Ѹ�޾��ף����˿ɵ���\n" NOR, me,target);
	    {
		 me->add_temp("apply/attack",  (int)me->query_skill("yangjia-qiang", 1)/4);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		 me->add_temp("apply/attack", -(int)me->query_skill("yangjia-qiang", 1)/4);
		 me->add("neili", -500);
		 me->add_temp("lihua",-1);
		 me->start_busy(1);
		}
		//�滨�ڶ���
		if ( me->query_temp("lihua") ==3 && objectp(target) && me->is_fighting(target))
	       message_vision(HIB"\n��Ȼһ��Ѥ����ɫ��������"+weapon->name()+HIB"��ǹ�⼲ȥ��$N�����ȵ�����"+target->name()+HIB"��С�ģ���\n" NOR, me,target);
           damage = (int)me->query_skill("yangjia-qiang", 1)+ (int)me->query_skill("spear", 1);
           damage = random(damage)*2 + random(damage);
        {       
        me->start_busy(1);      	  
		target->start_busy(1+random(1));
		me->add_temp("apply/attack",  (int)me->query_skill("yangjia-qiang", 1)/3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),2);
		me->add_temp("apply/attack", -(int)me->query_skill("yangjia-qiang", 1)/3);
		target->add("neili", -damage/10);
		me->add("neili", -400); 
		me->add_temp("lihua",-1);
        message_vision(RED"\n$nֻ������һ����"+weapon->name()+RED"�Ѿ���$N�ؿڶԴ���ȥ����Ѫ���أ�\n"NOR,me,target);
        }		
	    //�滨ǹ������
        if ( me->query_temp("lihua") !=3 && objectp(target) && me->is_fighting(target) )
    	   message_vision(WHT"\n$N��ȫ�������ᴩ��"+weapon->name()+WHT"ֻ���ղŻ����籩���滨���ͻ�̣�����Ȼת����ʽ���ǹ֮"HIY"������ǹ��"WHT"������\n" NOR, me,target);
        {        
          me->add("neili", -500);
          me->add("jingli",-500);
          me->set_temp("yjq/huima",1);

          me->add_temp("apply/attack",  (int)me->query_skill("yangjia-qiang", 1) /4 );
          me->add_temp("apply/damage", (int)me->query_skill("yangjia-qiang",1) /6);
    	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);    	 
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
          me->add_temp("apply/damage", -(int)me->query_skill("yangjia-qiang",1) /6 );
          me->add_temp("apply/attack",   -(int)me->query_skill("yangjia-qiang", 1) /4 );
    
         me->delete_temp("yjq/huima");
         me->start_busy(1+random(1));
       
         
		}

		call_out("lihua_finish", 6+random(4), me);
	        
	      	    
 }
 
void lihua_finish(object me,object target)
{
        object weapon;
	    if ( !objectp( me ) )
		       return;
        weapon = me->query_temp("weapon");
        message_vision(HIG"\n$Nһ�ס������滨��ʹ�꣬�ٶȽ�������������\n"NOR, me);
        me->delete_temp("lihua");
		me->delete_temp("yjq/lihua");
        me->start_busy(2);     
}

int help(object me)
{
   write(YEL"\n���ǹ��"HIG"�����滨"YEL"����"NOR"\n");
   write(@HELP
   ָ�perform lihua
	���ǹ���Ǵ��Ա��������ҽ���ǹ�����������ϻ���
	���¶���Ϊʵս���������滨ǹ���ǽ���ǹ�趯���滨
	���裬�����ޱȣ��������ǹ����֮�ؾ�����
	perform lihua

	Ҫ��	
		��ǰ���� 2000 ���ϣ�
		������� 15000 ���ϣ�
		��ǰ���� 500  ���ϣ�
		��ǰ���� 25 ���ϣ�
		���ǹ���ȼ� 450 ���ϣ�
		����ǹ���ȼ� 450 ���ϣ�
		����ǹ��Ϊ���ǹ��
		���������ޱ���������Ч����
  
HELP
   );
   return 1;
}
