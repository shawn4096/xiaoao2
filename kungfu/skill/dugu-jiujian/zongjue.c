#include <ansi.h>
inherit F_SSERVER;

string perform_name() {return HIW"�ܾ�ʽ"NOR;}

int perform(object me, object target)
{
	string msg, *skill;
	object weapon;
	mapping skills;
	int i,lvl;
	
	lvl=me->query_skill("dugu-jiujian",1);
	if( !target ) target = offensive_target(me);

    if( !objectp(target)
	||  !target->is_character()
	||  !me->is_fighting(target) )
		return notify_fail("���ܾ�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if((int)me->query_skill("dugu-jiujian",1) < 550 )
		return notify_fail("��Ķ��¾Ž�����������޷�ʵʩ�������۵ľ��硣\n");
    if((int)me->query_skill("sword",1) < 550 )
		return notify_fail("��Ļ�����������������޷�ʵʩ�������۵ľ��硣\n");
	if((int)me->query_skill("force",1) < 550 )
		return notify_fail("��Ļ����ڹ�����������޷�ʵʩ�������۵ľ��硣\n");
	if((int)me->query("max_neili")<20000)
		return notify_fail("����������������\n"); 
	if((int)me->query("jingli")<1500)
		return notify_fail("��ľ���������\n"); 
	if((int)me->query("neili")<2500)
		return notify_fail("��ĵ�ǰ����������\n"); 
	if((string)me->query_skill_mapped("sword") != "dugu-jiujian" && userp(me))
		  return notify_fail("�������޷�ʹ�á��ܾ�ʽ����\n");

	if((string)me->query_skill_mapped("parry") != "dugu-jiujian" && userp(me))
		  return notify_fail("�ܾ�ʽ��Ҫ�������¾Ž����������޷�ʹ�á��ܾ�ʽ����\n");


	if(target->query_temp("dgjj/zongjue") )
	       return notify_fail("�����Ѿ����ˡ��ܾ�ʽ���ˡ�\n");
	
	//if(me->query_temp("dgjj/zongjue") )
	       //return notify_fail("���������������ʹ�á��ܾ�ʽ���ˡ�\n");

	
	message_vision(HBYEL+HIG"\n$N���¾Ž���Ȼ��ɣ�������ȫ�����������������У������·�����ȴ����ָ��$n���������ڣ�\n"NOR,me,target);
	
	message_vision(HIC"\n$N������¾Ž��ܾ�ʽ�Ŀھ���������������������ͬ�ˣ�ͬ�������С���ת������ת������ת�\n"
						+"�ӳ�֮��������֮������δ֮����������һ�䣬ɽ����һ�䣬ˮ����һ�䡣Ǭ���༤������༤��\n"
						+"�����༤�����������壬�������ɾš�,�ڡ��ܾ�ʽ�����⼤���£�����������\n"NOR,me,target);
	
	if (!me->query_temp("dgjj/zongjue"))
	{	
		me->add_temp("apply/attack",lvl/3);
		me->add_temp("apply/damage",lvl/5);
		me->add_temp("apply/sword",lvl/3);
		me->add_temp("apply/parry",lvl/3);
		me->add_temp("apply/defense",lvl/3);	
		me->set_temp("dgjj/zongjue",lvl);	
		call_out("zongjue_effect",1,me,(int)lvl/20);
	}
	me->add("jingli",-800);
	me->add("neili",-1000);

    if ( random(me->query_int(1)) > target->query_int(1)/2
	 ||random(me->query("combat_exp")) > target->query("combat_exp")/2)
 //ԭ��Ʋ���Ϊtarget->query_int(),��ʱ��ǿһ��,����ֵѹ��+����
    {
		
		message_vision(HBGRN+HIW"\n$nֻ�����Լ����������ƣ��书Ϊ���¾Ž������ƣ���Щ����֮����ȫ�޷����ӳ�����\n"NOR,me,target);
		skills = target->query_skill_map();
		if (!skills) return notify_fail("����û�м������⼼�ܡ�\n");
			skill = keys(skills);
		i = sizeof(skill);
		while (i--)
			target->map_skill(skill[i]);
		target->delete("jiali");

		target->set_temp("no_enable",1);
		target->set_temp("dgjj/zongjue",1);
		
		me->start_perform(2,"�ܾ�ʽ");
		me->add_busy(1);
		me->set("jiali",0);
		if (objectp(target))
			call_out("remove_effect",(int)me->query_skill("dugu-jiujian",1)/10,me,target);
	} 
	else {
		message_vision(HIG"\n$n���һ�������潣�ߣ���Ȼ$N���ܾ���ʽ��Ҳ�޷��ﵽ������еľ��硣\n"NOR,me,target);
		me->add_busy(2);
		me->start_perform(4,"�ܾ�ʽ");
	}
	return 1;
}

void remove_effect(object me, object target)
{
	if (!objectp(target))return;
	
	//if (me) me->delete_temp("dgjj/zongjue");

	if (target) target->delete_temp("no_enable");
	if (target) target->delete_temp("dgjj/zongjue");
	return;
}

void zongjue_effect(object me, int count)
{
        int skill;
		object weapon;
        if (!me) return;
		weapon=me->query_temp("weapon");

		skill=me->query_temp("dgjj/zongjue");
		if (count<0
		    ||!me->is_fighting()
			||me->query_skill_mapped("sword")!="dugu-jiujian"
			||me->query_skill_mapped("parry")!="dugu-jiujian"
			||!weapon
			||weapon->query("skill_type")!="sword")
		{
			me->add_temp("apply/attack",-skill/3);
			me->add_temp("apply/damage",-skill/5);
			me->add_temp("apply/sword",-skill/3);
			me->add_temp("apply/parry",-skill/3);
			me->add_temp("apply/defense",-skill/3);
			me->delete_temp("dgjj/zongjue");
			message_vision(HBGRN+HIW"\n$N���¾Ž�֮���ܾ�ʽ���������У��ɶ��뾲�������Ľ�������ɢ��\n"NOR,me);
			return;
		}
		call_out("zongjue_effect",1,me,count--);
		return;
}

int help(object me)
{
	write(HIG"\n���¾Ž����ܾ�ʽ����"NOR"\n");
	write(@HELP
	���¾Ž����н�����������أ����йؼ����ǿ�ݺ��ϵл��ȣ�
	�����ƵС���Ȼ�������˶��¾Ž�����ǳ���Ҫ���Ƶ�֮������
	������ʤ���С����¾Ž��ų��ƽ������似���˵���������
	550�����ڻ��ͨ����ʽ���ᣬ�������ۣ���豹��棬����ʩչ��
	
	ָ�perform sword.zongjue

Ҫ��
	�����ڹ����� 550  ���ϣ�
	���¾Ž��ȼ� 550  ���ϣ�
	���������ȼ� 550  ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	��ǰ�������� 2500 ���ϣ�
	����������� 20000 ���ϣ�
	�������¾Ž�Ϊ������
	�������¾Ž�Ϊ�мܣ�
	��ս���гֽ�ʹ�á�
HELP
        );	
        return 1;
}
