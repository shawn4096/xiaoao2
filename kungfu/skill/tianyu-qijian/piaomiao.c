// ��翽���
#include <ansi.h>
#include <combat.h> 
#include <skill.h>
string perform_name(){ return HBMAG"��翽���"NOR; }
inherit F_SSERVER;

int perform(object me, object target)
{
    string dodge_skill,msg;
    int i, j;
    object weapon;

		 if( !target ) target = offensive_target(me);
     
		 if(!objectp(target) || !me->is_fighting(target) || !living(target)
			|| environment(target)!=environment(me))
                return notify_fail("����翽�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

 
		 if (me->query_skill_mapped("force") != "beiming-shengong")
			if (me->query_skill_mapped("force") != "bahuang-gong" )                
                return notify_fail("����ڹ������޷�ʹ�á���翽�������\n");

		 if(!wizardp(me) && (int)me->query_skill("beiming-shengong", 1) < 400 )
       		if(!wizardp(me) && (int)me->query_skill("bahuang-gong", 1) < 400 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á���翽�������\n");

		 if((int)me->query_skill("force", 1) < 400 )
                return notify_fail("��Ļ����ڹ�������죬�޷�֧�֡���翽�������\n");

		 if( (int)me->query_skill("tianyu-qijian", 1) < 400 ) 
                return notify_fail("��Ľ�����δ���ɣ�����ʹ�á���翽�������\n");

		 if((int)me->query_skill("sword", 1) < 400 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�á���翽�������\n");

		 if((int)me->query_skill("dodge", 1) < 400 )
                return notify_fail("��Ļ����Ṧ������죬����ʹ�á���翽�������\n");

		 if (!objectp(weapon = me->query_temp("weapon")) 
			|| weapon->query("skill_type") != "sword")
                return notify_fail("�������޽������ʹ�á���翽�������\n");
         if (me->query_skill_mapped("sword") != "tianyu-qijian"
			|| me->query_skill_mapped("parry") != "tianyu-qijian")
                return notify_fail("��û�м��������潣�����ʹ�á���翽�������\n");       
		 if((int)me->query("max_neili") < 10000 )
                return notify_fail("������������㣬����ʹ�á���翽�������\n");

		 if((int)me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ�á���翽�������\n");

		 if((int)me->query("jingli") < 1000 )
                return notify_fail("������̫���ˣ�����ʹ�á���翽�������\n");

		 msg = HBMAG "$N��ͨ���չ���ѧ��ʹ�������չ������潣�ľ�ѧ֮���裡\n" NOR;
	    

		 message_vision(msg, me, target);          
         me->set_temp("tyqj/piaomiao", 1);

         message_vision(MAG"\n$N"+weapon->name()+MAG"΢΢�ζ��������������۷�ʱ��˫ü��������ǰ�磬һ�ɳ��ǵĽ�����������ӿ��ȥ��\n"NOR,me,target);
         i = me->query_skill("tianyu-qijian", 1);
         j = me->query_skill("sword", 1) ;
         
		 me->add_temp("apply/attack", j/2);
         me->add_temp("apply/damage", j/5); 
         
		 msg = HIC "$w"HIC"��$N�þ���ָ���£����������������ƿ�֮����������������ɳ��۵ĺ�Х������ʹ���ĺ���������ƣ�" NOR;  
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3,msg); 
         msg = HIG "$N�ӽ����裬һʱ�����ݺᣬ�����ྲ�ද����ʱ������ƽ�羵�Ĵ󺣣���ʱ����ŭ�����Σ��仯Ī�⣡" NOR;             
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3,msg);      
         msg = HIM "$Nÿһ��̬���������ۣ�����Ʈ�ݣ���������,��$nһմ���ߣ��������һ�Ի�����������Ѳ��������⡰��ң�����ַ����˵����쾡�£�" NOR; 
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3,msg);	

         me->add_temp("apply/attack", -j/2);
         me->add_temp("apply/damage", -j/5);
		 
		 message_vision(HIW"\n$N��$n��һ�����֣�����һ��������㣬�������ɣ�һ������ƮƮ���������磬���绨�������\n"
		                    +"������������գ�����Է�Ҫ����ƫ����ʽȴ����������ۣ�ֱ���赸��\n"NOR,me,target);
	     if (random(me->query("combat_exp")) > target->query("combat_exp")/2 ){
		     message_vision(HIR"���$n����������$N�������ţ�" + weapon->name() + HIR"һ������$n���ؿڡ�\n"NOR,me,target);
			 target->reveive_damage("qi",target->query("qi")/3,me);
			 target->reveive_wound("qi",random(1000),me);
			 target->add_busy(1+random(2));
			}
	     else  {
			   message_vision(HIR"���$nһ����¿��������$N��" + weapon->name() + HIR"����$n���ؿ�һ�С�\n"NOR,me,target);
               /*
			   dodge_skill = target->query_skill_mapped("dodge");
	           if( !dodge_skill ) dodge_skill = "dodge";
			   if (target) message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);	
			   */
		   }
		
         weapon->unequip();

         me->add_temp("apply/strength", i/10);
         if (me->query("family/family_name") == "���չ�")
			 me->add_temp("apply/damage",j/4);
         
		 message_vision(HIM"\n$N�������б�������Ȼʩչ����ɽ��÷�ֺ���ɽ�����Ƶ���ʽ���㡢��������ץ���������Ͳʷ׳ʡ�\n"NOR,me,target);
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"), userp(target)?3:1,msg);                                
         
		 message_vision(HIC"���� ÷��"NOR, me, target); 
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(target)?3:1,msg);                                     
         
		 message_vision(HIW"���� ѩ��"NOR, me, target); 
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3,msg);                                       
         message_vision(HIM"��ɢ���㡿\n"NOR, me, target); 
         me->start_busy(2);
         me->add_temp("apply/strength", -i/10);
         if (me->query("family/family_name") == "���չ�") 
			 me->add_temp("apply/damage",-j/4);
         me->delete_temp("tyqj/piaomiao");
         weapon->wield();
         me->add("neili", -300);
         me->add("jingli", -300);
		 me->start_perform(4+random(3),"����翽�����");

		 return 1;
 }

int help(object me)
{
    write(WHT"\n�����潣֮��"MAG"��翽���"WHT"����"NOR"\n");
         write(@HELP
	�����潣������ɽͯ�Ѿ�ѧ֮һ������ɽ��
	ԨԴ����ң��������أ��������֧֮һ��
	���������潣���⾳������Ȼ�����Ʈ��֮
	�⣬���Ʒ����Ƶ���������ȴ�̲�����ɱ��
		 
	�����潣֮������翽��������������֮��
	�������������ơ������׵絯÷��ѩɢ���㡣
	
	perform sword.piaomiao

Ҫ��
	�˻Ĺ��ĵȼ� 400 ����;
	�����潣�ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	�����Ṧ�ȼ� 400 ���ϣ�
	����������� 10000 ����
	��ǰ�������� 1000  ����
	��ǰ�������� 1000  ����
	��������Ϊ�����潣��
	�����м�Ϊ�����潣��
	�ֳֽ���������
HELP
    );
        return 1;
}
 