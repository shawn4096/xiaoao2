// jixue.c  Ѫ���� [��Ѫ��]
// Edit by sohu@xojh
//���ӵ�����������
#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;

string perform_name(){ return RED"��Ѫ��"NOR; }

void jixue(object me,object target,int times,int now);
 
int perform(object me, object target)
{
	object ob,weapon;
	string msg;
	int lvl,times;
    
	if( !me->is_fighting() )
		return notify_fail("����Ѫ����ֻ����ս����ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
 
	if((int)me->query_skill("xuedao-jing",1) < 350)
		return notify_fail("���Ѫ������Ϊ������ Ŀǰ����ʹ�á���Ѫ����! \n");

	if(me->query_temp("xddf/jixue"))
		return notify_fail("������ʹ�á���Ѫ����! \n");

	if((int)me->query_skill("blade",1) < 350)
		return notify_fail("��Ļ���������Ϊ������ Ŀǰ����ʹ�á���Ѫ����! \n");

	if( me->query_skill_mapped("blade") != "xuedao-daofa")
		return notify_fail("�����ʹ��Ѫ������������ʹ�á���Ѫ�����ľ�����\n");
	if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("����мܲ��ԣ����뼤������ΪѪ������������������\n");
	
	if( me->query_skill("xuedao-daofa",1) < 350)
		return notify_fail("���Ѫ�������ȼ�����������ʹ�á���Ѫ�����ľ�����\n");

    if( me->query_skill_mapped("force") != "xuedao-jing" && me->query_skill_mapped("force") != "shenzhao-jing")
		return notify_fail("��������ʹ�õ��ڹ�ͬ��Ѫ���󷨡���ִ�������ʹ������Ѫ�����ľ�����\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("���������Ϊ������\n");
	if((int)me->query("neili")<800)
		return notify_fail("�������������\n"); 
	if((int)me->query("jingli")<500)
		return notify_fail("��ľ���������\n"); 

	ob = me->select_opponent();
	lvl = me->query_skill("xuedao-daofa",1);
	
	me->set_temp("xddf/jixue",1);
	times = me->query("env/Ѫ����Ѫ");
	
	if(times < 1) times = 1;
	if(times > lvl/40) times = lvl/40;
	if(times > 6) times = 6;

	msg = HIY"\n$N��ɫ��Ȼһ�䣬���������дʣ�ͬʱ��ת���У���֪��Ҫ��ʲô��\n\n"NOR;
	message_vision(msg, me);
	me->add("neili", -200);
	me->add_temp("apply/attack",lvl/3);
	me->add_temp("apply/damage",lvl/4);
	
	msg = BLU"\n$N��Ȼ���Լ����ϵ���ѪͿĨ�ڱ����ϣ�����Ц����"HIC"����Բ֮ҹ��ɱ��֮ʱ��"BLU"������С������\n\n"NOR;
	if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	
	me->add_temp("apply/attack",-lvl/3);	
	me->add_temp("apply/damage",-lvl/4);

	call_out("jixue",0,me,ob,times,0);


	return 1;
}

void jixue(object me,object target,int times,int now)
{
	string msg,weaname;
	object weapon;
	int lvl,force,damage,attack,qi;

	if( !objectp(me) ) return;
	if( !objectp(target) || !me->is_fighting(target) || (now >= times) || (me->query("neili")<200) || 
	  (!objectp(weapon = me->query_temp("weapon"))) || ((string)weapon->query("skill_type")!="blade") ) {
		me->delete_temp("xddf/jixue");
		me->start_perform(1,"��Ѫ��");
		if(living(me))
			message_vision(HIC"\n$N�����ջ��ھ�������Ҳ�ƺ�����Ѫɫ��\n"NOR, me);
		return;
	}

	weapon = me->query_temp("weapon");
	weaname = weapon->query("name");
	lvl = me->query_skill("xuedao-jing",1);
	force = me->query_skill("xuedao-dafa",1);

	now++;
	if(now <= 1)
		msg = HIR"\n$N��Хһ�����Ա����Կ��ֱۣ���ʱһ���Ѫ�ɽ���"NOR+weaname+HIR"֮�ϣ�"NOR+weaname+HIR"��������һ��Ѫɫ��";
	else
	if(now <= 3)
		msg = HIR"\n$N��Хһ�����Ա����Կ����ţ���ʱһǻ��Ѫ�ɽ���"+weaname+HIR"֮�ϣ�"NOR+weaname+HIR"����һ��Ѫɫ��";
	else
		msg = RED"\n$N��Хһ������ͷ�����Լ�һ������ʱһ����Ѫ�ɽ���"+weaname+RED"֮�ϣ�"NOR+weaname+RED"�������ͨ�죡����";
	
	attack = 7-now;
	damage = 8-now;
	if(me->query_temp("xuedao/yuxue")) {
		damage--;
		if(damage<2) damage=2;
		msg += "$N����Ѫ���󷨵��ھ����ڱ���֮�ϣ�";
	}
	msg += "\n"NOR;
	message_vision(msg, me);
	
	if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("damage:%d , attack:%d , qi:%d \n",force/damage,lvl/attack,-50*now));

	me->add_temp("apply/damage", force/damage);
	me->add_temp("apply/attack", lvl/attack);
	me->set_temp("xddf/jixue1",1);
	if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->delete_temp("xddf/jixue1");

	me->add_temp("apply/damage", -force/damage );
	me->add_temp("apply/attack", -lvl/attack);

	if(me->query("qi") < (60*now)) 
		qi = me->query("qi")-10;
	else
		qi = 60*now;
	if(qi<0) qi = 0;

	me->receive_damage("qi", qi,"����ʧѪ����");
	me->receive_wound("qi", qi/2,"����ʧѪ����");

	me->add("neili", -50*now);
	if(me->query("neili") < 0)	me->set("neili",0);

	call_out("jixue",1+random(3),me,target,times,now);
}
int help(object me)

{
        write(RED"\nѪ������֮����Ѫ������"NOR"\n\n");
        write(@HELP
	Ѫ��������Ѫ���Ŷ����书����Ϊ�ڹ���͵�����
	Ѫ�������Թ���������������Ѫ�������ѩɽѩ��
	���뽭������һս���������ǴӲ�����֮��������
	���˵Ĺ����Ѳ⡣
	��Ѫ���������˼������˵ľ������Ե���������
	Ѫ��������Ѫ�̼�ʩչ�ߵ�ս����ѭ����������
	�ϳ��С�

	ע�⣺set Ѫ����Ѫ x (1-6) �����⸽��Ч��

	ָ�perform blade.jixue

Ҫ��  
	��ǰ�������� 800 ���ϣ�
	����������� 2000 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	Ѫ�����ȼ�Ϊ 350 ���ϣ�
	Ѫ�������ȼ� 350 ���ϣ�
	��������ΪѪ��������
	�����м�ΪѪ���������ջ�������
	�����ڹ�ΪѪ������
	�ֳֵ���������
HELP
        );
        return 1;
}