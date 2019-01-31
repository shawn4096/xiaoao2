// qianjin.c for tjj
// By KinGSo ������ǧ�� 01 25 2007

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
int remove_mujian(object me,object weapon);

int perform(object me, object target)
{
	int damage, p,i;
	object weapon;
	int qianjin,ap,dp;
	string msg;
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);

    if (!weapon) return notify_fail("�������޽������ʩչ��������ǧ���\n");  
	
	if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
		return notify_fail("��������ǧ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_temp("tjj/lian"))
		return notify_fail("������ʹ������\n");

	if( (int)me->query_skill("taiji-jian", 1) < 500 )
		return notify_fail("���̫����������̫ǳ���������ˡ�\n");

	if( (int)me->query_skill("taiji-quan", 1) < 500 )
		return notify_fail("���̫��ȭ������̫ǳ���������ˡ�\n");

	if( (int)me->query_skill("sword", 1) < 500 )
		return notify_fail("��Ļ�����������̫ǳ���������ˡ�\n");

	if( (int)me->query_skill("cuff", 1) < 500 )
		return notify_fail("��Ļ���ȭ������̫ǳ���������ˡ�\n");

	if( (int)me->query_skill("yinyun-ziqi", 1) < 500 )
		return notify_fail("�������������̫ǳ���������ˡ�\n");

	if( !me->query("quest/wd/tjj/qianjin/pass"))
		return notify_fail("��ֻ����˵��̫��������ǧ��֮�����������޷�ʹ�á�������ǧ���\n");

	if( (int)me->query_skill("force", 1) < 500 )
		return notify_fail("����ڹ�����̫ǳ���������ˡ�\n");

	if( (int)me->query("max_neili") < 15000 )
		return notify_fail("����������̫ǳ���������ˡ�\n");

	if (me->query_skill_prepared("cuff") != "taiji-quan"
	|| me->query_skill_mapped("cuff") != "taiji-quan"
	|| me->query_skill_mapped("force") != "yinyun-ziqi"
	|| me->query_skill_mapped("sword") != "taiji-jian")
		return notify_fail("�������޷�ʹ��������ǧ�\n");

	if( (int)me->query("neili") < 3000 )
		return notify_fail("��ĵ�ǰ�����������������ˡ�\n");

	//ľ�������ӳ�
	if(((weapon->query("material") == "wood"
	|| weapon->query("material") == "bamboo"
	|| (weapon->query("id") == "songwen gujian" && weapon->query("from")=="zhang sanfeng")
	|| weapon->query("material") == "paper")
	|| weapon->query("weapon_prop/damage") < 20)
	&& !me->query_temp("tjj/mujianadd"))
	{
		i = me->query_skill("taiji-jian", 1)/3; //������������3����Ϊ2
		me->add_temp("apply/damage", i);
		me->add_temp("apply/attack", i);
		me->set_temp("tjj/mujianadd", i);
		if( wizardp(me) ) 
			tell_object(me, "������޷桸"HIW"������ǧ��"NOR"�������ӳɣ� "+i+"��\n"NOR);
		target->add_busy(2);//����޸���ADDģʽ������start
		call_out("remove_mujian", 1, me, weapon);
	}
	
	msg =  BCYN HIW "\n\n$N" HIW "��Ȼ��Ц���������ὣָб��������"+weapon->query("name")+BCYN+HIW"��������Ȧ�ӣ���ʱ���ܵ�����������ԴԴ���ϵı�ǣ��������\n"
					"\n��Ȼ�����ﵽ��һ���ܼӣ�һӬ������ľ��硱��$nֻ�����Լ����׽������ε������У����Գ���\n" NOR;

	ap=me->query("combat_exp")/100000;
	dp=target->query("combat_exp")/200000;
	if (random(me->query_skill("force",1)*3) > target->query_skill("dodge",1)/2 || random(ap) > dp)
	{
		//me->start_busy(1);
		qianjin = (int)me->query_skill("yinyun-ziqi",1) /40;
		damage = (int)me->query_skill("force",1)+me->query_skill("taiji-jian",1)+me->query_skill("sword",1);
		damage += random(me->query("jiali") * 100);
		damage *= 3;

		if(target->query("neili") < me->query("neili")) damage *= 2;
		if (damage>6500) damage = 6500+(damage-6500)/100;  

		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		target->receive_damage("jing", damage/6, me);

		if (target->query("jingli")>damage/3)
			target->add("jingli", -damage/3);
		else 
			target->set("jingli",1);

		target->apply_condition("neishang", qianjin);
		target->start_busy(2);

		//��ģ��ѵ�Ҫ�ƶԷ����������
		//target->add("max_neili", -random(50)); 
		me->add("neili", -200);
		if (me->query("neili") < 0)
			me->set("neili",0);
		p = (int)target->query("qi")*100/(int)target->query("max_qi");
		msg += HBRED HIY "\nֻ�����������죬$n�۵�һ���³�һ����Ѫ,��Ȼ�����˺��ص����ˡ�\n"NOR;
		msg += "( $n"+eff_status_msg(p)+" )\n"; 

		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		if((int)me->query_skill("force", 1) > 350 && (int)me->query_skill("taiji-quan", 1) > 350 && (int)me->query_skill("taiji-jian", 1) > 350)
			call_out("perform2", 1, me, target, p, damage); 
	}
	else {
		me->start_busy(1);
		me->add("neili", -100);
		target->add("max_neili", -random(50));                            
		target->start_busy(1);
		target->add("neili", -random(1000));
		msg += HIW"$n�ۼ���Ҫ���������������룬һҧ������ϧ�����Ԫ�������ˡ�\n"NOR;
		if((int)me->query_skill("force", 1) > 350 && (int)me->query_skill("taiji-quan", 1) > 350 && (int)me->query_skill("taiji-jian", 1) > 350)
			call_out("perform2", 1, me, target, p, damage); 
	}

	message_vision(msg, me, target);
	me->start_perform(4,"������ǧ��");
	return 1;
}


int perform2(object me, object target)
{  
	string msg, dodge_skill;
	int lev;
	lev = me->query_skill("force", 1);

	if( !target || !me || !living(me)
	|| !me->is_fighting(target) 
	|| environment(target)!=environment(me) || !living(target)
	|| (int)me->query("neili") < 500)
		return 0;

	message_vision(BCYN HIC"������$Nһ����Х,����Ϊ��ָ�����ֻ���һ����ԲȦ���绷��̫���������绷��һ����������Ȧ��$n����\n"NOR,me, target);
	message_vision(BCYN HIB"̫����������˸յ��ᾢ�������ں�$n��ս�Ĺ����о�Ȼû���κνӴ�����$nȴ�о���������������֮�С�\n"NOR,me, target);

	if (random(me->query_skill("force",1)) > target->query_skill("dodge",1)/2 || random(me->query_int())>target->query_int()/2)      
	{
		msg = BCYN HIR "�˿�$N���н���������һ��һ����֮�䣬����$n������ȫ����������$n�Լ���\n"NOR;

		target->add_temp("apply/attack",lev*2);

		target->add_temp("apply/dodge",- lev/2);
		target->add_temp("apply/parry",- lev/2);

		target->add_busy(2);
		me->add("neili", -200);
		me->add("jingli", -100);                              
		COMBAT_D->do_attack(target, target, target->query_temp("weapon"), random(2)?1:3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"), random(2)?1:3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 3);

		target->add_temp("apply/attack",-lev*2);
		target->add_temp("apply/dodge", lev/2);
		target->add_temp("apply/parry", lev/2);  

		//me->start_busy(1);
		if (me->query("neili") < 0)
			me->set("neili",0);

		me->add("neili", -100);
		me->add("jingli", -100);             

	} 
	else 
	{
		msg = HIY "$n" HIY "ǿ��һ������������غ�«�㣬�Ǳ��Ķ��˿�ȥ��\n" NOR; 

		me->add("neili", -100);
		me->add("jingli", -100);  
		target->add("max_neili", -random(50));                            
		target->start_busy(1);
		target->add("neili", -random(500));

		me->start_busy(2);
		if (me->query("neili") < 0)
		me->set("neili",0);
		if (target->query("neili") < 0)
		target->set("neili",0);
	}
	if(random(10) > 3 &&(int)me->query_skill("force", 1) > 450 &&(int)me->query_skill("taiji-quan", 1) > 450 && (int)me->query_skill("taiji-jian", 1) > 450)
		call_out("perform3", 1, me, target);

	message_vision(msg, me, target); 
	me->start_perform(5, "��������ǧ�");
	return 1;
}


int perform3(object me, object target)
{  
	string msg, dodge_skill;
	int lev;
	lev = me->query_skill("taiji-jian", 1);

	if( !target || !me || !living(me)
	|| !me->is_fighting(target) 
	|| environment(target)!=environment(me) || !living(target)
	|| (int)me->query("neili") < 500)
		return 0;

	message_vision(BYEL HIW "$N����$n�����ѽߣ��������õļ�϶��̫�������糤����ӣ����ϲ���������������ʹ��ɱ�֣�\n"NOR,me, target);
	message_vision(BYEL HIR "$N��Ȼ�����������¡�����ʽ���뵽������ǧ�����������з�����\n"NOR,me, target);

	if (random(me->query_skill("force",1)) > target->query_skill("dodge",1)/2
	||random(me->query_skill("sword",1))>target->query_skill("parry",1)/2)        
	{
		msg = BCYN HIW "\n��ʱ��$n���������м�$N���������Ľ��������ɵ����а��Խп࣡\n"NOR;
		me->add_temp("apply/cuff", lev/4);
		//me->add_temp("apply/sword", lev/3);
		me->add_temp("apply/attack", lev/2);
		me->add_temp("apply/damage", lev/6);
		//me->add_temp("apply/strength", lev/8);
		me->set_temp("tjj/sanhuan", 3);
		me->add("neili", -200);
		me->add("jingli", -200);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		//me->add_temp("apply/strength", -lev/8);
		me->add_temp("apply/cuff", -lev/4);

		//me->add_temp("apply/sword", -lev/3);

		me->add_temp("apply/attack", -lev/2);
		me->add_temp("apply/damage", -lev/6);
		me->delete_temp("tjj/sanhuan");
		target->start_busy(1);
		me->start_busy(2);
		if (me->query("neili") < 0)
			me->set("neili",0);

		me->add("neili", -200);
		me->add("jingli", -200);
	} 
	else 
	{
		msg = HIY "$n" HIY "���Է������˾���Ҫȡ�Լ��������ĸҵ�����ǿ��һ���������Ǳ��Ķ��˿�ȥ��\n" NOR; 

		me->add("neili", -100);
		me->add("jingli", -200);  
		target->add("max_neili", -random(100));                            
		target->start_busy(1);
		target->add("neili", -random(2000));

		me->start_busy(3);
		if (me->query("neili") < 0)
			me->set("neili",0);
		if (target->query("neili") < 0)
			target->set("neili",0);
	}

	message_vision(msg, me, target); 
	me->start_perform(6, "��������ǧ�");
	return 1;
}

//����ľ���޷�ӳ�Ч��
int remove_mujian(object me,object weapon)
{
	int i;
	object wep;
	if (!me) return 1;
	i = me->query_temp("tjj/mujianadd");
	wep = me->query_temp("weapon");
	if (!me->query_temp("tjj/mujianadd")) return 0;

	if (!me->is_fighting()
	||!wep
	||wep->query("id")!=weapon->query("id")
	||me->query_skill_mapped("sword") != "taiji-jian"	)
	{
		me->add_temp("apply/damage", -i);
		me->add_temp("apply/attack", -i);
		me->delete_temp("tjj/mujianadd");
		message_vision(HIW"$N�����������չ������б����𽥻ָ�ԭ����\n"NOR,me);
		return 1;
	}
	call_out("remove_mujian", 1, me, weapon);
	
}

string perform_name(){ return BCYN+HIC"������ǧ��"NOR; }

int help(object me)
{
        write(BCYN HIC"\n�䵱̫������ѧ֮��������ǧ���"NOR"\n\n");
        write(@HELP
	�䵱̫������ѧ֮��������ǧ�������̫����ѧ֮���壬
	��Ҫ����̫�������з���ʩչ������̫�����ռ������似
	����̫����֮�����ʽ��
	
	perform sword.qianjin

Ҫ��
	��ǰ�������� 3000 ����;
	����������� 15000 ���ϣ�
	̫�������ȼ� 500 ���ϣ�
	̫��ȭ���ȼ� 500 ���ϣ�
	�����ڹ��ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	����ȭ���ȼ� 500 ���ϣ�
	�������ȼ� 500 ���ϣ�
	��������Ϊ̫��������
	����ȭ��Ϊ̫��ȭ����
	�����ڹ�Ϊ��������
	�����м�Ϊ̫������
	����300ʱ�ɳ���һ��;
	����350ʱ�ɳ��ڶ���;
	����450ʱ�п��ܳ�������;

HELP
        );
        return 1;
}
