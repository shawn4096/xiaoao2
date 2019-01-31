// sanhuan.c for tjj
// Created and Modified by snowman@SJ 23/02/2001

#include <ansi.h>

inherit F_SSERVER;
int perform1(object me, object target, object weapon, int ap, int dp, int skill, int i);
int perform2(object me, object target, object weapon, int ap, int dp, int skill, int i);



int perform(object me, object target)
{
	object weapon;
	int i, j,t, lvl = me->query_skill("taiji-jian", 1);
	if (me->query("quest/wd/tjj/sanhuan/pass"))	t=2;
	else t=3;
	if( !target ) target = offensive_target(me);
	
	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("���������¡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_temp("tjj/lian") )
		return notify_fail("������ʹ������\n");
 
    if( (int)me->query_skill("taiji-jian", 1) < 450 )
		return notify_fail("���̫����������̫ǳ���������ˡ�\n");
 
    if( (int)me->query_skill("sword", 1) < 450 )
		return notify_fail("��Ļ�����������̫ǳ���������ˡ�\n");

	//if( (int)me->query_temp("tjj/chan") )
		//return notify_fail("����������ʹ�á������־���\n");

    if( (int)me->query_skill("yinyun-ziqi", 1) < 450 )
		return notify_fail("�������������̫ǳ���������ˡ�\n");

    if( (int)me->query("max_neili") < 12500 )
		return notify_fail("����������̫ǳ���������ˡ�\n");

	if( (int)me->query("neili") < 2000 )
		return notify_fail("��ĵ�ǰ�����������������ˡ�\n");

	if( me->query_skill_mapped("force") != "yinyun-ziqi" )
		return notify_fail("����ʲôΪ�ڹ�������ʹ���������¡�?\n");

	if( !objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "taiji-jian" )
		return notify_fail("��ʹ���ˡ��������¡�ô?\n");

  	j = lvl /2; //ԭ1/3
	if (lvl>350)
	   j = to_int(lvl/1.5);
	if ( lvl > 450 )
		j = to_int(lvl * lvl/825);

        if(!userp(me)) j = j/4; //����npc������
	    me->set_temp("tjj/sanhuan", 3);
	    me->add_temp("apply/sword", j/t);
        me->add_temp("apply/attack", j/t);
        me->add_temp("apply/damage", j/t);
	if( wizardp(me) )
           tell_object(me, "��ġ�"HIW"��������"NOR"�����ӣ���Ч���� "+j/t+"�������� "+j/t+"���˺� "+j/t+"��\n"NOR);

	if( (( weapon->query("material") == "wood"
	   || weapon->query("material") == "bamboo"
       || (weapon->query("id") == "songwen gujian" && weapon->query("from")=="zhang sanfeng")
       || weapon->query("material") == "paper" )
	   || weapon->query("weapon_prop/damage") < 20)
	   && !me->query_temp("tjj/sanhuan_damage"))
	    {
                   i =  me->query_skill("taiji-jian", 1)/t; //�������������ܺ���3����Ϊ2
			       me->add_temp("apply/damage", i);
                   me->add_temp("apply/attack", i);
			       me->set_temp("tjj/sanhuan_damage", i);
				   message_vision(HBYEL+HIW"$N���е�"+weapon->query("name")+HBYEL+HIW"�޷棬�������������£�ȴ�����д��գ�\n"NOR,me,target);
	               if( wizardp(me) ) 
                         tell_object(me, "������޷桸"HIW"��������"NOR"�������ӳɣ� "+i+"��\n"NOR);
	               target->add_busy(2); //����޸���ADDģʽ������start
        }

         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	if( me->is_fighting(target) )
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	if( me->is_fighting(target) )
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	 
	 
	 
	    me->add_temp("apply/sword", -j/t);
        me->add_temp("apply/attack", -j/t);
	    me->add_temp("apply/damage", -j/t);

	if( me->query_temp("tjj/sanhuan_damage") ){
		me->add_temp("apply/damage", -me->query_temp("tjj/sanhuan_damage") );
		me->add_temp("apply/attack", -me->query_temp("tjj/sanhuan_damage") );
		me->delete_temp("tjj/sanhuan_damage");

	}
	
	me->delete_temp("tjj/sanhuan");
	me->delete_temp("tjj/sanhuan_damage");

	me->start_busy(1+random(1));
	me->add("neili", -300);
	me->add("jingli", -150);
	me->start_perform(4, "���������¡�");
	
	
	if (objectp(target)&&me->query("quest/wd/tjj/sanhuan/pass"))
	{
		message_vision(YEL"$N����̫����������������ɣ���������䣬��ʦ�������ġ����־���˳��ʩչ������\n"NOR,me,target);
		//me->start_call_out( (: call_other, __DIR__"lian", "perform", me, 1 :), 1 );
		
		call_out("sanhuan_lian",1,me,target);
	}	    
	
	return 1;
}

int sanhuan_lian(object me, object target)
{
	string msg, dodge_skill;
	object weapon = me->query_temp("weapon");
	int ap, dp, damage, p, skill, i = 0;

	if( !target ) return 0;

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("�������־�ֻ����ս���жԶ���ʹ�á�\n");

	if( !living(target) )
		return notify_fail("�������־�ֻ����ս���жԶ���ʹ�á�\n");

	if( !weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("�������޽������ʹ�á������־���\n");

	if( me->query_skill_mapped("sword") != "taiji-jian" )
		return notify_fail("����������̫���������޷�ʹ�á������־���\n");

	if( me->query_skill_mapped("parry") != "taiji-jian" )
		return notify_fail("�������̫������Ϊ�мܲ���ʹ�á������־���\n");  
//��������⿪̫���񹦺������������
	if( me->query_temp("tjj/chan") && !me->query("quest/wd/yyzq/taiji/pass"))
		return notify_fail("������ʹ�á������־���\n");

	if( (int)me->query_temp("tjj/lian") )
		return notify_fail("����������ʹ�á������־���\n");

	if( (int)me->query_skill("taiji-jian", 1) <300 )
		return notify_fail("���̫��������Ϊ�в�����,�޷�ʹ�á������־���\n");             

	if( (int)me->query_skill("yinyun-ziqi",1) < 300 )
		return notify_fail("�����������Ϊ��ǳ������ʹ�á������־���\n");

	if( (int)me->query_skill("sword",1) < 300 )
		return notify_fail("�����������Ϊ�в�����,����ʹ�á������־���\n");  

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("���������Ϊ̫��������ʹ�á������־���\n");

	if( (int)me->query("neili") < 800 )
		return notify_fail("�������̫���ˣ�����ʹ�á������־���\n");  

	message_vision(CYN"\n$N΢΢һЦ��ʹ��̫������"+RED+"������"+CYN+"�־����������ӻ�����ת,���ֳֽ��������𣬽��������ǰ��\n"
			"����������ԣ��籧Բ������"+weapon->name()+CYN"δ������Ȼ�������\n"NOR,me,target);

	me->set_temp("tjj/lian",1);

	ap = me->query("combat_exp", 1) / 1000 * me->query_int(1);
	dp = target->query("combat_exp", 1) / 1000 * target->query_int(1);

	skill = me->query_skill("taiji-jian", 1);

	msg = CYN"\n$N����"+weapon->name()+CYN"������ǰ��������һ���Σ�һ��ɭɭ������ֱ����$n��ͻȻ֮�䣬$N�������֣�����һ������$n��ȥ��\n"NOR;

	if ( random( ap + dp) > dp
		||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		damage = me->query_skill("sword") * 2;
		damage = to_int( damage * skill/100.0);
		damage = damage/2 + random(damage);
		if (damage > 4000 ) damage = 4000 + random(damage-4000)/50;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -200);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		i = 1;
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	message_vision( msg, me, target);
	me->start_perform(2, "�������־�");
	me->start_busy(random(2));
	me->delete_temp("tjj/lian");
	if ( skill > 150 ) {
		me->set_temp("tjj/lian", 1);
		perform1(me, target, weapon, ap, dp, skill, i);
	}
	return 1;
}

int perform1(object me, object target, object weapon, int ap, int dp, int skill,int i)
{
	string msg, dodge_skill;
	int damage, p;

	if ( !me) return 1;
	if( !weapon || !objectp(target)) {
		me->delete_temp("tjj/lian");
		return 1;
	}

	msg =YEL"\n$N�ֽ��������֣�����ǰ��������ԲȦ���������໤סȫ�����ް�ֿ�϶���������Ž�����\n"+
		"����"+weapon->name()+YEL"��ס�Ķ���������$n�����ߴ�ҪѨ�����⼱��������������δ���\n"NOR;     

	if ( random( ap + dp) > dp ) {
		damage = me->query_skill("sword",1) +me->query_skill("taiji-jian",1)+me->query_skill("yinyun-ziqi",1);
		damage = to_int( damage * skill/150.0);
		damage = damage + random(damage);
		if (damage > 4500 ) damage = 4500 + random(damage-4500)/50;
		if ( i ) damage -= random(damage/2);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi",damage/4, me);
		me->add("neili", -250);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		i = 0;
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	message_vision( msg, me, target);
	me->start_perform(3, "�������־�");
	me->delete_temp("tjj/lian");
	if ( skill > 200 ) {
		me->set_temp("tjj/lian", 1);
		perform2(me, target, weapon, ap, dp, skill, i);
	}
	return 1;
}

int perform2(object me, object target,object weapon, int ap, int dp, int skill, int i)
{
	string msg, dodge_skill;
	int damage, p;

	if ( !me) return 1;
	if( !weapon || !objectp(target)) {
		me->delete_temp("tjj/lian");
		return 1;
	}

	msg = HIC"\n$N�������õ�"+RED+"��Ȧ"+HIC+"Խ��Խ�࣬������ʱ��ȫ������������"+RED+"��Ȧ"+HIC+"֮�У�"+RED+"��Ȧ"+HIC+"��Ȧһ��δ������һ��������\n"
		"����"+weapon->name()+HIC"��ʹ�ü��죬ȴ˿����������������֮�����������֮�����Ѵ��ڻ�����\n"
		HIC"$n���ӽ�����������"+RED+"��Ȧ"+HIC+"�����Լ������޿��˱ܣ�ֻ��ð��һ���������ֱ�һ�죬��"+RED+"��Ȧ"+HIC+"�����Ļ���ֱ�롣\n"NOR;

	if ( random( ap + dp) > dp
		||random(me->query_str())>target->query_dex()/2) {
		damage = me->query_skill("sword",1) * 4;
		damage = to_int( damage * skill/100.0);
		damage = damage + random(damage);
		if (damage > 5000 ) damage = 5000 + random(damage-5000)/100;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2+random(damage/2), me);
		me->add("neili", -300);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", "�ֱ�");
		me->start_perform(3+random(2), "�������־�");
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
		me->start_perform(3, "�������־�");
	}

	msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
	me->delete_temp("tjj/lian");
	message_vision( msg, me, target);
	return 1;
}

string perform_name(){ return HIG"��������"NOR; }

int help(object me)
{
        write(HIG"\n̫������֮���������¡���"NOR"\n\n");
        write(@HELP
	̫���������䵱�����������۷�֮����������˸�
	�ľ�ѧ����������ָ��󣬷�����ϰ�����������¡�
	����̫�������۷�������������������У����䵱
	���������м��߹����Ե�һ�У����ʹ�������÷���
	����������
	���⿪̫�����ںϵ����⣬������������ʵķ�Ծ
	���䵱����Ҫ���ʦ�����ù�ϵ��

	perform sword.sanhuan
	
Ҫ��
	��ǰ����Ҫ�� 2000 ����;	
	�������Ҫ�� 12500 ���ϣ�
	̫�������ȼ� 450 ���ϣ�
	�������ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	��������Ϊ̫��������
	�����м�Ϊ̫��������
	�����ڹ�Ϊ��������

HELP
        );
        return 1;
}
