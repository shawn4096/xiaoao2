// zhuan.c �򹷰���--ת�־�
// Creat by looklove@SJ 2001.4.10
// Modify by looklove 2001.5.2
// Modify by looklove 2001.5.4 ����ڿ�����
// Looklove modified at 2001.5.15

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int check_fight(object me,object target,int count);

string perform_name(){ return HBYEL+HIG"ת�־�"NOR; }

string *zhuan_msg = ({
HIM"$n�޷���ʩ��ֻ����ǰ���ݣ�ȴ�Ǳܿ�һ������һ��������������\n"NOR,
HIY"�ۿ�$n�޷���ʩ��ֻ����ǰ���ݣ�ȴ�Ǳܿ�ǰ�������������\n"NOR,
HIC"����$n���¼Ӿ��������û�ת����$n��Ծ���죬$W"HIC"������������\n"NOR,
HIG"$n����$N�ɱ���Ծ����תȦ�ӡ�$N����$W"HIG"ȴһֱ��$n���Ļζ���\n"NOR,
HIB"$N��ɫ�����ؿ���$n�ɱ���Ծ����תȦ�ӡ�$Nվ�����ģ��ٰ�����$n���ġ�\n"NOR,
HIR"$n����$N�ϴ�������$N��ɫ������$W"HIR"ʼ�ղ���$n���ġ�\n"NOR,
HIW"$N��$W"HIW"�����ֽ������֣��������ֽ������֣�ʼ�ղ���$n���Ĵ�Ѩ��\n"NOR,
RED"$N����$W"RED"����ԲȦ��ֱ��$n���Ĵ�Ѩ��$nֻ�ü�����ǰ��Ծ��\n"NOR,
YEL"$n���а����п࣬ȴ�޼ƿ�ʩ������һ��Ҳ����ͣ�١�\n"NOR,
WHT"ֻ��$n�ܵ�Ȧ��ԽתԽ��$N���е�$W"WHT"ȴһֱ��$n���Ĵ�ת��\n"NOR,
BLU"$nȦ��ԽתԽ�󣬺����б���$N���е�$W"BLU"���ɲ�����$n�����к���\n"NOR,
MAG"$nһ����Ȼ����ͷ�󺹣����¿�˿������ͣ����һֱ����Ȧ�Ӷ�ܡ�\n"NOR,
CYN"һʱ��$n��ɫ��䣬��ͷ�󺹣�$W"CYN"���ϵ�����ʹ��$nӦ�Ӳ�Ͼ��\n"NOR,
});

int check_fight(object me);
int halt_fight(object me);

int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int mexp, texp, mlvl, tlvl, b;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target))
		return notify_fail("��ת�־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	weapon = me->query_temp("weapon");
	if( !weapon
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang" 
	 || me->query_skill_mapped("parry") != "dagou-bang" )
		return notify_fail("�������޷�ʹ�á�ת�־�����\n");

	if( me->query_temp("dgb/zhuan") )
		return notify_fail("������ʹ�á�ת�־�����\n");

	if( me->query_temp("dgb/chan") )
		return notify_fail("������ʹ�á����־�����\n");

	if( target->is_busy() || target->query_temp("dgb/chan") )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");


	mlvl = (int)me->query_skill("dagou-bang",1);
	tlvl = (int)target->query_skill("dodge", 1);

	b = me->query_skill("bangjue",1);

	tweapon = target->query_temp("weapon");

	if( mlvl < 500 )
		return notify_fail("��Ĵ򹷰�����������죬����ʹ�á�ת�־�����\n");
	if( b < 200 )
		return notify_fail("��Ĵ򹷰���������죬�޷�ʹ����ת�־�����\n");
	if( me->query_skill("huntian-qigong",1) < 500 )
		return notify_fail("��Ļ��������������㣬�޷�ʹ����ת�־�����\n");
	if( me->query("neili") < 1000 )
		return notify_fail("������������ˡ�\n");
	if( me->query("jingli") <  1000 )
		return notify_fail("��ľ���������֧����ʹ����ת�־�����\n");
	if( me->query("max_neili") < 8000 )
		return notify_fail("�����������֧����ʹ�á�ת�־�����\n");

	me->set_temp("dgb/zhuan",1);	


	msg = HBYEL+HIR"$Nʹ���򹷰���"+HIC"��ת�־���"HBYEL+HIR"��ֻ��"+weapon->name()+HBYEL+HIR"������һ�ű�Ӱ��\n"NOR;
	if (tweapon)
	{	
		msg += HBYEL+HIR"$N������"+weapon->query("name")+HIR"����$n���е�"+tweapon->query("name")+HIR",$nֻ�����б���Խ��Խ����\n"NOR;
	}else 	msg += HBYEL+HIR"$N������"+weapon->query("name")+HIR"����$n������,$nֻ���Լ����Ӻ�Ȼһ����\n"NOR;

	msg += HBYEL+HIW"$N��"+HIC"��ת�־���"+HIW"Բת���⣬�͵�$n���ġ�ǿ�䡹�����縮��������׵��������̨���������ࡹ����ҪѨ��\n"NOR;

	
	if(random(me->query_skill("stick",1))>target->query_skill("dodge",1)/2
		||random(me->query_int(1))>target->query_int(1)/2)
	{
		msg += HIM "\n$N�İ�Ӱֻ��$n�����Ѩ�ϻ�����ȥ��������಻�ϣ�һ�㲻�У��ֵ�һѨ��\n" NOR;
//�Ʒ�,�⿪�޹����Ʒ� 
		if (me->query("quest/gb/dgb/wugou/pass")
			&&!target->query_temp("dgb/zhuan")
			&& me->query("env/�򹷰�ת�־�")=="�Ʒ�")
		{
			
			msg += HIC "\n$nֻ������һ����������ʱ��óٻ������������󽵣������ٳ���\n" NOR;

			target->add_temp("apply/parry",-mlvl/3);
			target->add_temp("apply/dodge",-mlvl/3);
			target->add_temp("apply/defense",-mlvl/3);
			target->add_temp("apply/armor",-mlvl/3);
			target->set_temp("dgb/zhuan",mlvl);

			me->add("neili", -600);
			call_out("tremove_zhuan",(int)b/50,target);

		}
		//û���޹��Ͷ��к͵���
		msg += HBYEL+HIG "\n$n��Ȼ��Щͷ�����ǣ���������Ĺ�Ӱ֮�У���ʱʧȥ�˹����ķ���\n" NOR;
		target->add_temp("lost_attack",b/20);
		if (objectp(target)&& me->is_fighting())
			call_out("check_fight",1,me,target,b/20);
		else call_out("remove_effect",1,me);
	}
	else {
		msg += HIW "\n$n����һ������æ��"+weapon->name()+HIW"��һ������ס��$N�Ĺ��ơ�\n" NOR;
		me->start_busy(random(2));
		me->add("neili", -200);
	}
	if (me->query_skill("dagou-bang",1)<450)
		me->start_perform(2, "ת�־�");
	message_vision(msg, me, target);
	return 1;
}

//target�ָ�����
int tremove_zhuan(object target)
{
	int mlvl;
	if (!target) return 1;
	mlvl=target->query_temp("dgb/zhuan");
	target->add_temp("apply/parry",mlvl/3);
	target->add_temp("apply/dodge",mlvl/3);
	target->add_temp("apply/defense",mlvl/3);
	target->add_temp("apply/armor",mlvl/3);
	target->delete_temp("dgb/zhuan");
	message_vision("$N�˹����˱��򹷰�����ס�Ĵ�Ѩ����ʱ���������\n",target);
	return 1;
}
//me�ָ�״̬
int remove_effect(object me)
{
        if(!me) return 0;

        me->delete_temp("dgb/zhuan");

		message_vision(HBYEL"\n$N�����а���������б�Ϸ�һ������Ӱ�����ˣ���ת�־���������ϣ����ص�������չ���\n"NOR, me);

        me->start_perform(2, "ת�־�");
        me->start_busy(random(2));
        return 0;
}
//ѭ������

int check_fight(object me,object target,int count)
{
	object wp;
	int n;
	string msg;
	
	//target = offensive_target(me);

	
	if (!me) return 1;
	n=me->query_skill("dagou-bang",1)+me->query_skill("bangjue",1);
	n=n+random(n);

	if( target->is_ghost()||!objectp(target))
	{
			msg = HBYEL"$N��"+wp->name()+HBYEL"���һ�ڣ��ջ�����ʽ��\n"NOR;
			message_vision(msg, me);
			return remove_effect(me);
	}
	else if(!objectp(wp = me->query_temp("weapon"))
		||wp->query("skill_type")!="stick")
	{
		msg = HIG"$N����������ʧ��ת�־�Ҳ��֮ͣ��������\n"NOR;
	
		message_vision(msg, me);
		return remove_effect(me);
	}	
	else if(!living(target))
	{
		msg = HIW"$N��м�ؿ���$nһ�ۣ���ɫ�����ؽ�"+wp->name()+HIW"���˻�����\n"NOR;
		message_vision(msg, me,target);
		return remove_effect(me);
	}

	else if(!me->is_fighting() || !living(me)||count<0)
	{
			msg = HBYEL"$N������"+wp->name()+HBYEL"һ�գ��Ų�ͣ��������\n"NOR;
			message_vision(msg, me);
			return remove_effect(me);

	}
	else if( me->query_skill_mapped("stick") != "dagou-bang"||me->query_skill_mapped("parry") != "dagou-bang")
	{
			msg = HBYEL"$N����һ�䣬ʹ����һ·��������\n"NOR;
			message_vision(msg, me);
			return remove_effect(me);
	}
	else if( me->query("jingli") <= 300 )
	{
			msg = HBYEL"$N���н�����ԭ���Ǿ��������ˡ�\n"NOR;
			message_vision(msg, me);
			return remove_effect(me);
	}
	else if( random((int)me->query_int()) < target->query_int()/4)
	{
			msg = HIW"$n�������𣬻�����"+wp->name()+HIW"��һ����$Nʼ�ϲ�������æ���С�\n"NOR;
			message_vision(msg, me,target);
			return remove_effect(me);
	}
		
	//��ʼ����
	msg = zhuan_msg[random(sizeof(zhuan_msg))];
	msg = replace_string(msg, "$W", wp->name());
	msg += "\n"NOR;
	message_vision(msg, me, target);
	
	
	//ÿ�غ϶�����
	me->receive_damage("neili",100);
	target->receive_damage("jingli", n, me);
	target->receive_damage("jing", n, me);
	if((int)target->query("jingli")< 0) target->set("jingli",0);
	message_vision(MAG"$n�о��Լ������ͻ�������䷨�����겻����������������Ϊ��ģ�\n"NOR,me,target);
	
	call_out("check_fight",1,me,target,count--);
}
int help(object me)
{
	write(HBYEL"\n�򹷰���ת�־�����"NOR"\n");
	write(@HELP
	��ת�־������򹷰����ᡱ���顱���桱���ɡ����ص㷢�ӵ���
	�쾡�£���ר�����ֵĺ��ļ���ҪѨΪ����һ��ʩչ��
	����������ʹ���ֲ�ͣ�������Ȱ���ת�������ܵ��
	��������Ӱ�Խ����������ʹ�����п�ȴҲ�޼ƿ�ʩ��
	�����ľ������;�����������ȥ��
	
	�⿪�����޹����ܰ�������ʽ�ں�֮�󣬷���ʹ�ñ���
	���е���Ҫ��ЧΪ�Ʒ��ͻغ������ĶԷ�������������
	Ϊ�򹷰�����Ĺ��򡣺Ͳ��־�������Ϲ���
	
	ע�⣺��Ч���ô򹷰�ת�־��������Ч
	
	set �򹷰�ת�־� �Ʒ�
	
	ָ�perform stick.zhuan

Ҫ��
	������� 2000 ���ϣ�
	��ǰ���� 800 ���ϣ�
	��ǰ���� 800 ���ϣ�
	�򹷰��ȼ� 180 ���ϣ�
	���������ȼ� 180 ���ϣ�
	�򹷰����ȼ� 180 ���ϣ�
	�����м�Ϊ�򹷰���
HELP
	);
	return 1;
}
