// bujue.c ���಻��

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIC"���಻��"NOR;}

void attackob(object me,object target,int lvl,int hits,int);
void dohit(object,object);

int perform(object me, object target)
{
        string msg;
        int lvl,effect,i; 
        
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("�����಻����ֻ����ս��ʱ�ã�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ����á����಻������\n"); 

        if( (lvl=(int)me->query_skill("huagu-mianzhang", 1)) < 400 )
                return notify_fail("��Ļ������ƻ���������������ʹ�ã�\n");

        if ( me->query_skill_prepared("strike") != "huagu-mianzhang"
        || me->query_skill_mapped("strike") != "huagu-mianzhang" 
        || me->query_skill_mapped("parry") != "huagu-mianzhang" )
                return notify_fail("��û�м����������ƣ�����ʹ�á����಻������\n");

          if(me->query_skill("dulong-dafa",1) < 400 )
                return notify_fail("��Ķ����󷨹������㣬���������಻����\n");

        if ( me->query_skill_mapped("force") != "dulong-dafa" )
                return notify_fail("��û�м��������󷨣�����ʹ�á����಻������\n");

        if((int)me->query("neili") < 1000)
                return notify_fail("�������������㣬�����á����಻������\n"); 

        if((int)me->query("jingli") < 1000)
                return notify_fail("�����ھ������㣬�����á����಻������\n"); 

        if((int)me->query("jiali") < 150)
                return notify_fail("�����̫���ˣ������á����಻������\n"); 

		//if( target->query_temp("bujue_busy") )
	 			//return notify_fail("�Է��Ѿ����ˡ����಻������\n"); 
	 	if( me->query_temp("hgmz/bujue") )
	 			return notify_fail("������ʩչ�����಻������\n"); 
		if(me->query("gender")=="Ů��") 
        	return notify_fail("�㲻�����ˣ��в���ʹ�����಻����\n");
		i = 3;
        
		msg = HIY"\n$N��Ȼ��һ����������Ծ��˫��һ������$n����ػ����ĳ���\n"+ 
              HIC"$N�ƺ����ֲ��أ����䲨��״���������˻�ǰ�ˣ�һ�˸߹�һ�ˣ����಻����\n"NOR;
        message_vision(msg, me, target);
		//�ڹ��ӳ�
		effect = SKILL_D("dulong-dafa")->force_effect(target->query_skill_mapped("force"));

        me->set_temp("hgmz/bujue",1);
		//target->add_temp("apply/defense",-lvl/5);
 
       // target->set_temp("hgmz/bujue", 1);
                me->add("jingli",-100);
                me->add("neili",-300);
        me->add_temp("apply/attack",lvl/5);
        if(i==3) 
			me->add_temp("apply/strength",lvl/20);
        COMBAT_D->do_attack(me, target,0, i);
        
		if(i==3) 
			me->add_temp("apply/strength",-lvl/20);
        COMBAT_D->do_attack(me, target,0, 3);
		//COMBAT_D->do_attack(me, target,0, 3);
        me->add_temp("apply/attack",-lvl/5);
        if(wizardp(me)) 
			write("�����غ���:"+(5-effect)*3 +"!\n");
		
		me->start_perform(4,"�����಻����");
        call_out("attackob",1, me, target,lvl,(5-effect)*3,i);
    
        return 1;       
}

void attackob(object me,object target,int lvl,int hits,int i)
{
	
   if (!me) return;
  
 /*   if( !target && me) 
   {

		message_vision(HIC"\n$N����һ�٣������ջ����ƣ�\n"NOR, me);
        me->delete_temp("sld/pfm/bujue");
		me->delete_temp("hmgz/bujue");
        me->start_perform(3,"�����಻����");
        return;
   }
  if( !me )
   {
		if(target) 
		{
				target->delete_temp("bujue_busy");
		
				target->add_temp("apply/defense",lvl/5);
				target->clear_condition("no_perform");
		}
                        
		if( userp(me) ) 
		{
				me->delete_temp("sld/pfm/bujue");
				me->delete_temp("hmgz/bujue");
		}
		return;
	}*/
    if (hits<1 
      //  || !target
        //|| !living(target)
        || me->query_temp("weapon")
        //|| target->is_ghost() 
        //|| me->is_ghost()  
        || !me->is_fighting(target) 
        || me->query("neili") < 800 
        || me->query_skill_prepared("strike") != "huagu-mianzhang" )
	{
        	message_vision(HIY"\n$N����һ�٣���Ҳ֧�ֲ�ס�����ʱ�յ�������ֻ�ܻ����ջ����ƣ�\n"NOR, me);
              //  target->delete_temp("bujue_busy");
              //  target->clear_condition("no_perform");
             // if( userp(me) ) {
                //me->delete_temp("sld/pfm/bujue");
				me->delete_temp("hgmz/bujue");
			  //}
            //  if( userp(me) ) 
                me->start_perform(3,"�����಻����");
		return;
	}

        if(wizardp(me)) write("�����غ���:"+hits+"!\n");
        me->add_temp("apply/attack",lvl/5);
        COMBAT_D->do_attack(me, target,0, 3);
        if(i==3) 
			me->add_temp("apply/strength",lvl/20);
        COMBAT_D->do_attack(me, target,0, 3);
		COMBAT_D->do_attack(me, target,0, 3);
        if(i==3)
			me->add_temp("apply/strength",-lvl/20);
        me->add_temp("apply/attack",-lvl/5);
        //me->start_perform(2,"�����಻����");  //ȡ�� һ��ʼbujue��û��halt�� ���⡣
        call_out("attackob", 2, me,target, lvl, --hits,i);
}

int help(object me)
{
   write(WHT"\n�������ơ�"HIC"���಻��"WHT"����"NOR"\n");
   write(@HELP
	�����������ߵ������似����һ�ּ�Ϊ��������������
	���������ƻ��е��˿�ʼ���粻����������ʱ��������
	������ȫ��������������࣬������ϣ��อ���ѣ���
	�����ԣ����޾��Ρ�
	 
	perform strike.bujue

Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������Ƶȼ� 400 ���ϣ�
	�����󷨵ȼ� 400 ���ϣ�
	�˵м�����Ҫ 150 ���ϣ�
	�����ұ��Ʒ�Ϊ�������ƣ�
	�����м�Ϊ�������ƣ�
	�����ڹ�Ϊ�����󷨣�
	ʹ���Ա�Ϊ���ԣ�
	
HELP
   );
   return 1;
}
