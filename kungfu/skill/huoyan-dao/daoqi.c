// fen.c ��
// by iceland
// modefied by emnil@sj 2/3/2k
 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
 
string perform_name(){ return HBRED+HIW"����"NOR; }
int check_fight(object me,int count);
int perform(object me,object target)
{
        
        int skill,damage;

        skill= me->query_skill("huoyan-dao",1);
		damage=skill+me->query_skill("longxiang-boruo",1);
        if( !target ) target = offensive_target(me);
        if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
         || environment(target)!= environment(me))
		    return notify_fail("�����浶����ֻ����ս���жԶ���ʹ�á�\n");
       
        if (me->query_temp("hyd/power"))
                return notify_fail("������ʩչ�����浶����������\n");          
         if (objectp(me->query_temp("weapon")))
                return notify_fail("��ֻ�ܿ�������"HIR"�����浶����"NOR"�ľ�����\n");
        if( skill < 350)
                return notify_fail("��ġ����浶���ȼ�����, ����ʹ��"HIR"�����浶����"NOR"�ľ�����\n");
        if( me->query_skill("longxiang-boruo",1) < 350)
                return notify_fail("��ġ��������������������, ����ʹ��"HIR"�����浶����"NOR"�ľ�����\n");
        if( me->query("neili") < 2500 )
                return notify_fail("��������޷�֧��"HIR"�����浶����"NOR"��ʩչ�ˣ�\n");
        if( me->query("jingli") < 1500 )
                return notify_fail("��ľ����޷�֧��"HIR"�����浶����"NOR"��ʩչ�ˣ�\n");
        if( me->query("max_neili") < 5000 )
                return notify_fail("û��ǿ�������֧�����ʩչ"HIR"�����浶����"NOR"������\n");
        if( me->query_skill_mapped("strike") != "huoyan-dao"
         || me->query_skill_prepared("strike") != "huoyan-dao")
                return notify_fail("�����ʹ�á����浶��������ʹ��"HIR"�����浶����"NOR"�ľ�����\n");
        if( me->query_skill_mapped("force") != "longxiang-boruo")
                return notify_fail("��������ʹ�õ��ڹ�ͬ���������������ִ�������ʹ�����١��ľ�����\n"); 
		message_vision(HBRED+HIY"\n$N����бб�����������������������������������ʵ�ʣ�\n����ʹ�������Ǵ����¡����浶���еġ�������������\n"NOR, me, target);         
        
		if (me->query("quest/dls/longxiang/pass"))
        {
			skill=skill+me->query_skill("longxiang-boruo",1)/6;
        }
		
        me->add("jingli",-150);
		me->add("neili",-400);
		me->set_temp("hyd/power",skill);
		me->add_temp("apply/attack",skill/6);
	    me->add_temp("apply/damage",skill/6);
		me->add_temp("apply/strike",skill/6);
        if( random(me->query_skill("huoyan-dao",1)) > target->query_skill("parry",1)/3
         || random(me->query("combat_exp"))>target->query("combat_exp")/2
         || random(me->query("neili"))> target->query("neili")/2)
        {
        	message_vision(HIR "\n$nֻ��������������󣬹����Լ�����һ��С��Ϊ�������ˣ�\n"NOR,me,target);			
			if (me->query("lx/gree")>10)
			{
				damage=damage*2;
			}else 
				damage+=damage+random(damage/2);			
			if (damage>4000) damage=4000+(damage-4000)/100;
			//if (target->query("qi")<damage)
			  // damage=target->query("qi")-100;
			target->receive_damage("qi",damage,me);
			target->start_busy(1+random(2));
			target->set_temp("hyd/power",1);
			if (me->is_fighting() && me->query_skill("huoyan-dao",1)>450)
				COMBAT_D->do_attack(me, target, 0, me->query_temp("xs/longxiang")?3:1);
			call_out("check_fight", 1, me);
        }
        else
        {
         	message_vision(HIB"\n$nһ���������������ڹ�ӭ����$N�����ɽ�$N�Ĺ��ƻ��⣡\n"NOR,me,target);
        	me->start_busy(1);
        }
        if (me->query_skill("huoyan-dao",1)<450)
        {
			me->start_perform(2,"���浶��");
        }
        call_out("check_fight",1,me,skill);
        return 1;
}

int check_fight(object me,int count)
{
      int skill;
	  
      if ( !me || !me->query_temp("hyd/power")) return 0;
	  skill=me->query_temp("hyd/power");
/*
      if (me->query_skill_prepared("strike") !="huoyan-dao")
	  {
        me->delete_temp("hyd/power");
		me->add_temp("apply/attack",-skill/6);
	    me->add_temp("apply/damage",-skill/6);
		me->add_temp("apply/strike",-skill/6);
        tell_object(me, HIR"����ʽһ����ɢȥ�����浶������\n"NOR);		
        return 0;
      }
	  */
      if ((!me->is_fighting())
          ||(me->query_skill_prepared("strike") !="huoyan-dao")	)  {
          me->delete_temp("hyd/power");
		  me->add_temp("apply/attack",-skill/6);
	      me->add_temp("apply/damage",-skill/6);
		  me->add_temp("apply/strike",-skill/6);
          tell_object(me, HIR"�㽫ע��˫��֮�ϵ������ջأ�ɢȥ�ˡ����浶����������\n"NOR);
          return 0;
      }
    
       call_out("check_fight", 1, me,count -2);
       return 0; 
}
int help(object me)
{
	write(HIR"\n���浶�ؼ�����������"NOR"\n");
	write(@HELP
���浶�ؼ�����������

	���浶���Ǵ����¾���������ǿ������������������ʩչ��������ǿ��
	�뵱���Ħ���ڳ�����һս���Ի��浶���ܿ�����ʦ����ɮ�����ľ�����
	���񼼡��������ǽ������������У�����ǿ����ڹ���ʹ����ʩչ��Ϊ��
	�浶������Ҫ�ĸ������ܡ�450��ɡ�
	
	ָ�perform strike.daoqi

Ҫ��
	�������  5000 ���ϣ�
	����Ҫ��  2500 ���ϣ�
	��������� 350 ���ϣ�
	���浶�ȼ� 350 ���ϣ�
	�����ڹ�   350 ���ϣ�    
HELP
	);
	return 1;
 }
