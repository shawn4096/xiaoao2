// xuantian-wuji �����޼���
// by augx@sj  8/28/2001

#include <ansi.h>

inherit FORCE;
#include "/kungfu/skill/force.h"

int valid_enable(string usage)
{
	return usage == "force";
}

int valid_learn(object me)
{
	int na, nf, nx;
	nf = (int)me->query_skill("force", 1);
	na = (int)me->query_skill("art", 1);
	nx = (int)me->query_skill("xuantian-wuji", 1);

	if ( nf < 20)
		return notify_fail("��Ļ����ڹ���򻹲������޷���������޼�����\n");

	if ( me->query("gender") == "����")
		return notify_fail("���޸����ԣ���������������������������޼�����\n");

	if ( me->query("family/master_name") == "�����" ) {
		if ( na < 120 && na <= nx )
			return notify_fail("��������黭����̫ǳ���޷���������޼�������Ϊ��\n");
	}

	if ((int)me->query_skill("xuantian-wuji", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("xuantian-wuji", 1) >= 200 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	return valid_public(me);
}

int practice_skill(object me)
{
	if((int)me->query_skill("xuantian-wuji", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("xuantian-wuji", (int)me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ��������������޼����ˡ�\n");
	}
	else return notify_fail("�����޼���ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"xuantian-wuji/" + func;
}

int ob_hit(object ob, object me, int damage)
{
	int i, j, lvl, jing, cur = 0;
	lvl = me->query_skill("xuantian-wuji",1);
	if( lvl > 500 ) lvl = 500;
	
	if (me->query_temp("txwh/taxue") > 0 ) {
		if (me->query_skill_mapped("dodge") == "taxue-wuhen"
		 && me->is_busy()
		 && !random(3)) {
			message_vision(CYN"$n����ʽ����$N��ֻ�о�������޻��У��޷�ʹ��������\n"NOR, me,ob);
			cur = damage/2;
		}
	}

/*	// ������ǰ�� riyue

	if (me->query_temp("xtwj/riyue") > 0 ) {
		i = 0;
		lvl = me->query_skill("xuantian-wuji",1);
		if(lvl>350) lvl = 350;
		if (me->query("neili")>100) {
			i = damage * (23 - lvl*2/100)/10;
			if( lvl>400 ) i = i * 6/7;
			jing = i / 3;
			if( (me->query("jing")-100) < jing ) jing = 0;
			me->add("jing",-jing);
			me->add("neili",-(i-jing));
			if(me->query("neili")<0) me->set("neili",0);

			if(wizardp(me) && me->query("env/test"))
				tell_object(me,sprintf("d:%d, n:%d, j:%d ",damage,i-jing,jing));
			message_vision(MAG"$n����ʽ��$N��ǰ���޼���ǽ���赲���������ܶ�$N����κ��˺���\n"NOR, me,ob);
			i = damage;
		}
*/

	

	if( me->query_temp("xtwj/riyue") > 0 && me->query("neili") > lvl ) {

		if( damage < 1000 && !userp(ob) && !random(3)) { // �˺���С��û��Ҫ�ж�
			me->add("neili", -(random(60)+20));
			message_vision(MAG"$n����ʽ��$N��ǰ���޼���ǽ���赲���������ܶ�$N����κ��˺���\n"NOR, me,ob);
			i = damage;
		}

	else if( random(me->query_con()) > ob->query_str()*2/3 && random(2) ) { // �жϻ���ı���
	
			if( damage > lvl*3 ) { // ����˺��������ֻ�ܻ��� lvl 3 �����˺�
				i = lvl*3 * (23 - lvl*2/100)/15;
				if( lvl > 400 ) i = i * 4/5;
				jing = i/4; // ��ֻ�ܴ��� 1/4 ������
				if( (me->query("jing")-100) < jing ) jing = 0;
				me->add("jing", -jing);
				me->add("neili", -(i-jing));
				if( me->query("neili") < 0 ) me->set("neili",0);
				if( wizardp(me) && me->query("env/test") )
					tell_object(me,sprintf("-damage lvl*3, d:%d, n:%d, j:%d ",damage,i-jing,jing));
				message_vision(MAG"$n����ʽ����$N��ǰ���޼���ǽ�ϣ�����ȥ�˲��ֵľ�����\n"NOR, me,ob);
				i = lvl*3;
			}			
			else { // �˺�С�� lvl 3 ���Ļ���ȫ������
				i = damage * (23 - lvl*2/100)/15;
				if( lvl > 400 ) i = i * 4/5;
				jing = i/4; // ��ֻ�ܴ��� 1/4 ������
				if( (me->query("jing")-100) < jing ) jing = 0;
				me->add("jing", -jing);
				me->add("neili", -(i-jing));
				if( me->query("neili") < 0 ) me->set("neili",0);
				if( wizardp(me) && me->query("env/test") )
					tell_object(me,sprintf("d:%d, n:%d, j:%d ",damage,i-jing,jing));
				message_vision(MAG"$n����ʽ��$N��ǰ���޼���ǽ���赲���������ܶ�$N����κ��˺���\n"NOR, me,ob);
				i = damage;
			}

		}

	else { // ������������ɵĲ����˺�
			j = 3 + random(4);
			i = damage/j * (23 - lvl*2/100)/15; // ������������
			if( lvl > 400 ) i = i * 4/5;
			jing = i/3; // �����Դ��� 1/3 ������
			if( (me->query("jing")-100) < jing ) jing = 0;
			me->add("jing", -jing / 10);
			me->add("neili", -(i-jing));
			if( me->query("neili") < 0 ) me->set("neili",0);
			if( wizardp(me) && me->query("env/test") )
				tell_object(me,sprintf("-damage/"+j+", d:%d, n:%d, j:%d ",damage,i-jing,jing));
			message_vision(MAG"$n����ʽϬ���ޱȣ�$N��ǰ���޼���ǽ����������ȫ�赲$n�Ĺ�����\n"NOR, me,ob);
			i = damage/j;
		}
		

		if( me->query("neili") <= lvl ) {
			message_vision(MAG"\n$N��ǰ����ǽ����С��������ʧ�����Ρ�\n\n"NOR,me);
			me->delete_temp("xtwj/riyue");
		}
		cur += i;
	}
	return -cur;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIC + me->name()+HIC"������һ��Ʈ����޼�������Χ�š�" NOR,
		"start_my_msg" : "�����������޼��񹦣����۵��һ����������֫������������\n",
		"start_other_msg" : me->name()+"���������޼��񹦣����۵��һ����������֫������������\n",
		"halt_msg" : "$N�Ҵҽ���Ϣ���˻�ȥ����һ��������վ��������\n",
		"end_my_msg" : "����Ƭ�̣���о��Լ��Ѿ��������޼������۵����������վ��������\n",
		"end_other_msg" : "����Ƭ�̣�"+me->name()+"�о����Ѿ��������޼������۵����������վ��������\n",
		"heal_msg" : HIW"$N��ϥ���£���Ȼ����"HIC"���񳯷�"HIW"�������ڶ�������Ʈ����ʵ����͵����ɵ������ơ�\n"NOR,
		"heal_finish_msg" : HIW"�������ã�������ֹ��$N���һ�����İ����ĸо���͸ȫ����\n"NOR,
		"heal_unfinish_msg" : HIR"����һ�ᣬ$Nͷ�����ǣ���Ѫ��ӿ����������ƣ���ǳ�����������ܵ�����\n"NOR,
		"heal_halt_msg" : HIW"ͻȻ���������Ժ���ֹЪ��$N�㼴���ѣ�������һ������վ��������\n"NOR,
	]);
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
	int j, k,damage;
	object weapon;
	weapon=me->query_temp("weapon");
	
	j = me->query_skill("art", 1);
	k = me->query_skill("xuantian-wuji",1);
    // && !me->query_temp("yxj_qimen")
	// && !me->query_temp("thd/feiying")
	//if (me->query_skill_mapped("sword")!="liangyi-jian") return;
	
 
	//�ٽ�˫��
	damage = me->query_skill("liangyi-jian",1) + me->query_skill("art",1)+(int)me->query_skill("xuantian-wuji", 1)*2+(int)me->query_skill("liangyi-jue", 1)*2;
	damage = damage +random(damage);
	damage *= 2;			
	if (damage>3500) damage = 3500;

	if( random(10) >= 5 
		&& random(j) > 150
		&& k > 450
		&& me->query_skill_mapped("sword")=="liangyi-jian"	
		&& me->query_skill_mapped("parry")=="liangyi-jian"	
		&& objectp(weapon) 
		&& me->query_temp("xtwj/riyue")
		&& weapon->query("skill_type") == "sword"
		&& me->query_temp("xtwj/qinjian"))
	{
		
		message_vision(HIC"$N����΢΢�������ң�����һ����������ʢ��\nͬʱ�����˽���磬���糵�֣���Ȼû�н�������֮�Σ���ȴ��Ϊ����������������\n\n"NOR, me, victim );

		if( random(me->query_skill("force",1)) > victim->query_skill("force",1)/2 
			|| victim->is_busy())
		{        
			message_vision( HIY "$nһʱ���飬Ϊ���������ţ�ãȻ�����β��ɵ�һ��,���ϵ�����һ�ɣ�\n\n"NOR, me, victim );
			victim->add_busy(2);
			victim->add_condition("no_exert",1);
			victim->set("jiali",0);
			message_vision( RED "$n��æ�����ж����������Ѿ�����ɢ�Ľ������У�����С����Ѫ��ע��\n\n"NOR, me, victim );

            victim->receive_damage("jing", random( damage/2 ),me);
            victim->receive_damage("qi", 20 + random(damage),me);
            victim->receive_wound("qi", 20 + damage,me);
            
                
        }
		else if( random(me->query_int()) > victim->query_int()/2 || victim->is_busy())
		{
 
          message_vision( BBLU+HIW "$N�������޼����ӵ�������"HIG"��������"BBLU+HIW"���������������ʱ�����޽����н���\n\n"
						+ NOR + RED"$n�ҽ�һ���������Ѿ������ν������У�\n"NOR, me, victim );
 
                        damage *= 2;
                        victim->receive_wound("jing", random( damage/2 ),me);
                        victim->receive_damage("qi", 20 + random(damage),me);
                        victim->receive_wound("qi", 20 + damage,me);
                        victim->add_condition("no_perform",1);
         }
	}
	
	

            
}