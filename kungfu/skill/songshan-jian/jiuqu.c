// jiuqu.c by sohu@xojh
// ������ �������
//�����仯֮��
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int ssj_songyang(object me,int count);

int perform(object me, object target)
{
	int damage,skill,p;
	string msg;

	object weapon = me->query_temp("weapon");
    skill=me->query_skill("songshan-jian",1);
	if( !target ) target = offensive_target(me);
   
	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if( me->query_skill_mapped("force")!="hanbing-zhenqi")
		if( me->query_skill_mapped("force")!="lengquan-shengong" )
		return notify_fail("�㼤�����ڹ��Ǻ�����������Ȫ�񹦣��޷�ʩչ������������\n");
	if( me->query_skill("hanbing-zhenqi")<450)
		if( me->query_skill("lengquan-shengong")<450)
		return notify_fail("��ĺ�����������Ȫ����Ϊ�������޷�ʩչ������������\n");
	if( userp(me)&&!me->query("quest/ss/ssj/jiuqu/pass"))
		return notify_fail("��û�еõ�����ʦ���Ĵ��ڣ��޷�ʩչ������������\n");

	if( me->query_skill("songshan-jian", 1) < 450 )
		return notify_fail("��Ľ����̶Ȼ�����ʹ�á�����������\n");

	if( me->query_skill("force", 1) < 450 )
		return notify_fail("��Ļ����ڹ���Ϊ��������\n");

	if( me->query("neili") < 1500 )
		return notify_fail("�����������ʹ�á�����������\n");

	if( me->query("jingli") < 1000 )
		return notify_fail("��ľ�������ʹ�á�����������\n");

 	if (!weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "songshan-jian"
	 || me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("�㼤������ʹ����ɽ������\n");
	
	if( me->query_temp("ssj/jiuqu"))
		return notify_fail("������ʹ�á�����������\n");

	message_vision(CYN"\n$N���л��䣬�Ų����Ƽ�˲����$n�̳��Ž���ÿһ�������м��أ�Ѹ���ޱȣ��仯Ī�⣬���ǡ�"HIG"������"CYN"���Ľ����仯��\n" NOR, me,target);
	message_vision(CYN"\n$N���л����������������о������鶯�쳣���������ȥ��֮�����綾�ߣ�\n" NOR, me);

  

        
	me->set_temp("ssj/jiuqu",1);

	//����busy
	if (random(me->query_skill("songshan-jian",1))>target->query_skill("parry",1)/2
		||random(me->query("combat_exp"))>target->query("combat_exp")/2)
	{
		message_vision(HIC"\n$N���鼫Ϊ�ḻ����ʽ�仯���죬$n�����б仯���Ѹ�ݣ�ʼ�ϲ�������ʱһ����æ���ң�\n" NOR, me,target);
		target->add_busy(1);
		if (!userp(target))
		{
			target->add_busy(3);
		}
	}
	//��������˺�
	if (random(me->query_skill("songshan-jian",1))>target->query_skill("parry",1)/2
		||random(me->query_int(1))>target->query_int(1)/2)
	{
		message_vision(HIR"\n$N��$n��ʽ���ϣ���Ȼһ���Ӳ����ܵĽǶȴ���$n��\n" NOR, me,target);
		damage=skill+me->query_skill("force",1);
		damage=damage*me->query_str(1)/10;
		damage=damage+random(damage);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
		p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
		msg = COMBAT_D->damage_msg(damage, "����");
		msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		
		msg = replace_string( msg, "$w", weapon->query("name"));
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		message_vision(msg,me,target);
	}
	if (objectp(me)&&objectp(target))
		call_out("attack_jiuqu",2+random(3),me,target);
	else {
		me->delete_temp("ssj/jiuqu");
		me->start_temp(2,"������");
	}
 
	me->add("neili", -300);
	me->add("jingli", -150);
	return 1;
}

int remove_jiuqu(object me,object target)
{
	int i,j,skill;
	
	if (!me||!me->is_fighting()) return 0;
	if (!target)
	{
		me->delete_temp("ssj/jiuqu");
		me->start_temp(2,"������");
		return 1;
	}
	skill=me->query_skill("songshan-jian",1);
	j=me->query_skill("songshan-jian",1)/150;
	if (random(me->query("combat_exp")>target->query("combat_exp")/2)
		||!userp(target))
	{

		message_vision(HIY"$N����������������������˲���ͷţ���������������$n�����·�����ƺ�����ˮ�����������\n"NOR,me);
		me->add_temp("apply/sword",skill/4);
		me->add_temp("apply/attack",skill/4);
		for (i=0;i<j;i++ )
		{
			
			if (me->is_fighting()&&objectp(target))
			{
				COMBAT_D->do_attack(me, target,me->query_temp("weapon"),userp(me)?3:1);

			}
		}
		me->add_temp("apply/sword",-skill/4);
		me->add_temp("apply/attack",-skill/4);
				
	}	
	me->delete_temp("ssj/jiuqu");
	me->start_perform(3+random(2), "����������");

	return 1;
}



string perform_name(){ return HIG"������"NOR; }

int help(object me)
{
        write(HIW"\n��ɽ����֮������������"NOR"\n\n");
        write(@HELP
	��ɽ�����С��ڰ�·�����·��֮�ƣ��ܹ�ʮ��·���̿����Ľ���
	Ӧ�о��С���������������ħ��ʮ�������Ȼ�ս��ɽ����������
	�ĺ������˴��������ɽ�������ྪ�����������ɸ��ֶ����š�
	��ɽ�������������Ἧ���ɲд�����ϣ����������ǵõĽ��в�
	�۴־�������¼�����������һ�����ס�
	��������������ɽʮ��̫��֮һ���������������似����ɽ��
	���ػ��ӵ���ʽ������������·�ߣ�һ�����У����������
	���쳣�����綾���ŷ�һ�࣬һ�����������һ�����ģ��˵���
	�ݶ���������Ҫ��������̡�

	ָ�perform sword.jiuqu
	
Ҫ��
	��ǰ�������� 1500 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	��ɽ�����ȼ� 450 ���ϣ�
	�����ڹ��ȼ� 450 ���ϣ�
	�������ֵȼ� 450 ���ϣ�
	��������Ϊ��ɽ������
	�����м�Ϊ��ɽ������
	�����ڹ�Ϊ��ϵ������	
	���ֳֽ��������	

HELP
        );
        return 1;
}
