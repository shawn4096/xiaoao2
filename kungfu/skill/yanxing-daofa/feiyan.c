#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg,dodge_skill;
	int p, ap, dp,lvl,damage,skill;
    weapon=me->query_temp("weapon");  
	if( !target ) target = offensive_target(me);

	if(!objectp(weapon = me->query_temp("weapon"))
	 ||(string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("����������С�ֻ����ս���жԶ���ʹ�á�\n");

	if((int)me->query_skill("force", 1) < 350 )
		return notify_fail("��Ļ����ڹ��ȼ�����������ʹ�÷�������С�\n");       

	if(me->query_skill_prepared("strike") != "sixiang-zhang"
	 || me->query_skill_mapped("strike") != "sixiang-zhang")
		return notify_fail("�㲻�������ƣ������޷�ʹ�÷�������С�\n");

	

	if ((int)me->query_skill("yanxing-daofa", 1) < 350 )
		return notify_fail("������е����ȼ�����������ʹ�÷�������У�\n");    

	if( me->query_skill_mapped("blade") != "yanxing-daofa"
	 || me->query_skill_mapped("parry") != "yanxing-daofa")
		return notify_fail("�����ڲ���ʹ�÷�������У�\n"); 

	if ((int)me->query_skill("blade", 1) < 350 )
		return notify_fail("��Ļ�������������죬����ʹ�÷�������У�\n");    

	if ((int)me->query_skill("sixiang-zhang", 1) < 350 )
		return notify_fail("��������Ʋ�����죬����ʹ�÷�������У�\n");    

	if ((int)me->query_skill("strike", 1) < 350 )
		return notify_fail("��Ļ����Ʒ�������죬����ʹ�÷�������У�\n");    

	if ((int)me->query("neili") < 2500 )
		return notify_fail("����������̫��������ʹ�÷�������У�\n");

	if ((int)me->query("jingli") < 1500 )
		return notify_fail("�����ھ�������������ʹ�÷�������У�\n");

	if ((int)me->query("max_neili") < 5000 )
		return notify_fail("����������̫��������ʹ�÷�������У�\n");

	message_vision(HIY"$NͻȻ������"+weapon->query("name")+HIY"����һ�ӣ�\n"NOR, me, target);
	//˲�������
	me->add_temp("apply/dexerity", me->query_skill("dodge",1)/20);
	
	ap = me->query("combat_exp")/1000 * me->query_skill("strike",1);
	dp = target->query("combat_exp")/1000* target->query_skill("parry",1);
   
	if (me->query_skill("yanxing-daofa",1)<350)
       lvl=me->query_skill("yanxing-daofa",1)+me->query_skill("linji-zhuang",1)/4;
	else lvl=me->query_skill("yanxing-daofa",1)+me->query_skill("linji-zhuang",1)/2;
	damage=lvl;
	//�׼�������
	
	if (me->query_skill("jiuyin-zhengong",1)>150)
	{
		message_vision(HIB"$NĬ������澭Ҫ������������е�������֮��ǿ��\n"NOR,me);
		lvl=lvl+me->query_skill("jiuyin-zhengong",1)/2;
		
	}
	if (me->query("class")!="bonze")
	{
		damage+=lvl;
	}
	me->add_temp("apply/attack",lvl/2);
	me->add_temp("apply/strike",lvl/5);
	me->add_temp("apply/damage",lvl/10);
	me->add_temp("apply/blade",lvl/5);
	
	if (me->query_skill("jiuyin-zhengong",1))
	{
		skill=me->query_skill("yanxing-daofa",1)+me->query_skill("blade",1)/4+me->query_skill("jiuyin-zhengong",1);
		damage+=skill;
		
	}
	message_vision(HIR"$N��$nһ����������ʹ��һ�������Ƶľ�ѧ��Ʈѩ�����ơ���\n"NOR, me, target);

	if (random( ap + dp) > dp )
	{
		
	 	message_vision(HIY"$nһʱ�������$N���صĻ����ؿڣ�\n"NOR, me, target); 
		target->receive_damage("qi", damage*3,me);
		target->receive_wound("qi", damage,me);
		target->add_busy(1);
        if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ me->query_skill("sixiang-zhang", 1) * 3+ WHT"�㹥���˺���\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+me->query_skill("sixiang-zhang", 1) * 3+ WHT"���˺���\n"NOR);
		p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");
		msg = "( $n"+COMBAT_D->eff_status_msg(p)+" )\n"; 
		message( msg, me, target);
		COMBAT_D->report_status(target, userp(me)?3:1);
        //me->add_temp("apply/attack",damage);	
        
    if (me->is_fighting(target))
		{
		 weapon->unequip(); 
         me->add_temp("apply/strike", lvl/3);
		 me->add_temp("apply/attack", lvl/6);
		 me->add_temp("apply/damage", lvl/6);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
         me->add_temp("apply/strike", -lvl/3);
		 me->add_temp("apply/attack", -lvl/6);
		 me->add_temp("apply/damage", -lvl/6);
		 weapon->wield();
		}
		
	}
	else{
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		message( msg, me, target);
	}
	message_vision(HIR"\n$N�԰�Ӱ����֮�����𣬽��˿����������ĵ���������������\n"NOR, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	
	me->add_temp("apply/dexerity",-me->query_skill("dodge",1)/20);
	
	me->add_temp("apply/attack",-lvl/2);
	me->add_temp("apply/strike",-lvl/5);
	me->add_temp("apply/damage",-lvl/10);
	me->add_temp("apply/blade",-lvl/5);
	me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jinli", -100);
	me->start_perform(3+random(2), "����������С�");       
	return 1;

}
string perform_name(){ return HIG"���������"NOR; }

int help(object me)
{
        write(HIG"\n���е���֮����������С���"NOR"\n\n");
        write(@HELP
	���е������Ƕ�ü�׼ҵ����似��������º���
	ѧϰϰ�á������е����׼ҵ���ʹ�ã���������
	���ټ�ׯ���ʹ�ã�Ҳ��һ�Ų��׵��似��
	����������С��İ��ؾ����ں�Ȼ�����������
	�У��������ֵ�ע���������������鲻�ḻ����
	���ϵ���ƭ����ü����ֻ��ʩչ��ü��һ�ž���
	�������ơ��ͻ����Է����ؿڣ�����˺�����
	�˶�ü�������������ӡ�
	
	ָ�perform blade.feiyan
        
Ҫ��  
	��ǰ�������� 2500 ���ϣ�
	����������� 5000 ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	���е����ȼ� 350 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�
	��������Ϊ���е�����
	�����м�Ϊ���е�����
	�����Ʒ�Ϊ�����ƣ�
	���Ʒ�Ϊ�����ƣ�
	�����ڹ����ޣ�
	���ֳֵ��������

HELP
        );
        return 1;
}
