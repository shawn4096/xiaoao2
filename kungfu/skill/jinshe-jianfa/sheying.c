//sheying.c ������Ӱ
//cre by sohu@xojh
 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

 int perform(object me, object target)
 {
         string msg;
         object weapon;
         int jf,zf,sf,lvl;
         jf = me->query_skill("jinshe-jianfa", 1);
         zf = me->query_skill("jinshe-zhang", 1);
         sf = me->query_skill("wudu-yanluobu", 1);
         lvl=( jf + zf +sf ) /3;        
         weapon = me->query_temp("weapon");
 
         if( !target ) target = offensive_target(me);
        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || environment(target)!= environment(me))
                return notify_fail("��������Ӱ��ֻ����ս���жԶ���ʹ�á�\n");
 
     //   if((int)me->query_temp("hmg_nizhuan") )
       //          return notify_fail("�������˾���������ʲô��,�����߻���ħ��!\n");
 
        if (!weapon || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "jinshe-jianfa")
                 return notify_fail("�������ʹ�ý�ʱ����ʹ����������Ӱ����\n");
         if (me->query_skill_mapped("strike") != "jinshe-zhangfa"
			||me->query_skill_prepared("strike") != "jinshe-zhangfa")
                 return notify_fail("����뼤�������Ʒ�����ʹ����������Ӱ����\n");

         if(me->query_skill("jinshe-jianfa", 1) < 250 )
                 return notify_fail("��Ľ��߽�����������죬ʹ������������Ӱ��������\n");

         if( (int)me->query_skill("force",1) < 250 )
                 return notify_fail("��Ļ����ڹ��ȼ�������ʹ������������Ӱ��������\n");
         if( (int)me->query_skill("strike",1) < 250 )
                 return notify_fail("��Ļ����Ʒ��ȼ�������ʹ������������Ӱ��������\n");
         if( (int)me->query_skill("jinshe-zhangfa",1) < 250 )
                 return notify_fail("��Ľ����Ʒ��ȼ�������ʹ������������Ӱ��������\n");

         if( (int)me->query_dex() < 50)
                 return notify_fail("��ĺ�����������50��ʹ������������Ӱ��������\n");        
              
         if( (int)me->query("max_neili") < 3000 )
                 return notify_fail("����������̫����ʹ������������Ӱ����\n");      
 
         if( (int)me->query("neili") < 500 )
                 return notify_fail("�������������㣬ʹ������������Ӱ����\n");
         if( (int)me->query("jingli") < 500 )
                 return notify_fail("�����ھ������㣬ʹ������������Ӱ����\n");

         lvl = me->query_skill("jinshe-jianfa", 1);
      
         //weapon = me->query_temp("weapon");    

         message_vision(HIC"\n$N������"+weapon->query("name")+HIC"�ζ����������ⷴ�䣬����һƬ���⣬���������䶯�����ǡ�������Ӱ��������\n"NOR,me);
            
			me->add_temp("apply/damage", lvl /6);
            me->add_temp("apply/attack", lvl /4);
       
	   if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		   ||random(me->query_skill("dodge",1))>target->query_skill("dodge",1)/2)
	   {
			message_vision(HIY"\n$nһ��Ȼ�䣬��Ȼ���������Ǵ�˵�еġ�������Ӱ������ȴΪ$N���߽����������Ի�\n"NOR,me,target);
			target->add_busy(2);
			if (!userp(target))
			{
				target->add_busy(2+random(1));
			}
			target->add_temp("apply/attack",-lvl/4);
			target->add_temp("apply/parry",-lvl/4);
			target->set_temp("jsjf/sheying",lvl);
			call_out("remove_effect",(int)lvl/100,target,lvl);

	   }
		
		if (me->is_fighting() && target->is_busy()) 
		{
			message_vision(HIR"\n$N�ۼ�$nΪ�������Ի���Ц������˲������һ�����ƣ�\n"NOR,me,target);

            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            weapon->unequip(); 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			weapon->wield();
		
		 }else {
			message_vision(YEL"\n$N�ۼ�$n��û��Ϊ�������󣬲��ò�������һ�գ�һ�����˳�ȥ��\n"NOR,me,target);

            weapon->unequip();             
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			weapon->wield();
			me->start_busy(2);
		}
 			me->add_temp("apply/damage", -lvl /6);
            me->add_temp("apply/attack", -lvl /4);

           me->start_perform(4,"��������Ӱ��");
           me->add("neili", -300);
           me->add("jingli", -200);
		   return 1;
 }
int remove_effect(object target,int lvl)
{
	if (!target) return 0;
	
    if (!target->query_temp("jsjf/sheying")) return 0;
   
    target->add_temp("apply/attack",lvl/4);
	target->add_temp("apply/parry",lvl/4);
	message_vision(WHT"$NĿ������Ӧ������ѣ�Σ����ʵ�״���õ��ָ���\n"NOR,target);
	return 1;
}

int help(object me)
{
        write(HIY"\n���߽���֮��������Ӱ����"NOR"\n\n");
        write(@HELP
	�����ɾ���ѩ�������������ĵľ����书. ������Ӱ������
	���ལ�����������ⷴ�䣬�Ӷ��Ի�Է�˫�۵�һ�ž�����
	�Է����������Ի������󹥻�һ��һ�ƣ������������
	�����һ�ơ�
	
	ָ�perform sword.sheying

Ҫ��
	��ǰ�������� 500 ���ϣ�
	����������� 3000 ���ϣ�
	���������� 50 ���ϣ�
	���߽����ȼ� 250 ����
	�����Ʒ��ȼ� 250 ����
	�����Ʒ��ȼ� 250 ����
	���������ȼ� 250 ����
	�����ڹ��ȼ� 250 ����
	��������Ϊ���߽�����
	�����Ʒ�Ϊ�����Ʒ���
	���Ʒ�Ϊ�����Ʒ���
	�ֽ������������ν�����Ч

HELP
        );
        return 1;
}

string perform_name(){ return HIC"������Ӱ"NOR; }
