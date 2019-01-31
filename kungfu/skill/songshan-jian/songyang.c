// songyangjue.c by darken@SJ
// Lklv@SJ modified 2001.10.22

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int ssj_songyang(object me,int count);

int perform(object me, object target)
{
	int i,skill;
	object weapon = me->query_temp("weapon");
    skill=me->query_skill("songshan-jian",1);
	if( !target ) target = offensive_target(me);
   
	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	
	if( me->query_skill("hanbing-zhenqi", 1) < 350 )
		return notify_fail("��ĺ��������������޷�ʩչ��������\n");
	if( !me->query("quest/ss/ssj/songyang/pass"))
		return notify_fail("��û�еõ������ŵĴ��ڣ��޷�ʩչ��������\n");

	if( me->query_skill("songshan-jian", 1) < 350 )
		return notify_fail("��Ľ����̶Ȼ�����ʹ����������\n");

	if( me->query_skill("songyang-shou", 1) < 350 )
		return notify_fail("��Դ���������ʶ��������\n");

	if( me->query("neili") < 1500 )
		return notify_fail("�����������ʹ����������\n");

	if( me->query("jingli") < 300 )
		return notify_fail("��ľ�������ʹ����������\n");

 	if (!weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "songshan-jian"
	 || me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("�����ʹ����ɽ������\n");
	
	if( me->query_temp("ssj/songyang"))
		return notify_fail("������ʹ����������\n");

	    message_vision(HIY"\n$N��Хһ��������ͻ�䣬ʩչ����������֮��"HIC"��������"HIY"����\n" NOR, me);
		message_vision(HIY"\n��ɽ�����������Ǻ�����ʵ�����󽣳�����ʽ�ۻ룬�󿪴�����̲�ɱ����\n" NOR, me);

        if (!userp(target))
          i=skill+me->query_skill("hanbing-zhenqi",1)/6;

        
		me->add_temp("apply/attack", i/6);

        me->add_temp("apply/damage", i/6);

        me->add_temp("apply/sword", i/6);
		me->add_temp("apply/hand", i/6);
		me->add_temp("apply/strike",i/6);

	    me->set_temp("ssj/songyang", i);


		
 
		me->add("neili", -200);
		me->add("jingli", -100);

		call_out("ssj_songyang",1,me,(int)skill/40);
		return 1;
}

int ssj_songyang(object me,int count)
{
	int i;
	object target,weapon;

	if (!me) return 1;
	i=me->query_temp("ssj/songyang");
	weapon=me->query_temp("weapon");
	if (count<0
		||!weapon
		||weapon->query("skill_type")!="sword"
		|| me->query_skill_mapped("sword") != "songshan-jian"
		|| me->query_skill_mapped("parry") != "songshan-jian" 
		||!me->is_fighting())
	{
		me->add_temp("apply/attack", -i/6);
        me->add_temp("apply/damage", -i/6);
        me->add_temp("apply/sword", -i/6);
		me->add_temp("apply/hand", -i/6);
		me->add_temp("apply/strike",-i/6);


		me->delete_temp("ssj/songyang");
		message_vision(HIY"$N�Ѿ������������ķ����ӵ����켫�£�����һ�������������˽��ƣ�\n"NOR,me);
		me->start_perform(2+random(2), "������");
		me->start_busy(random(2));

		return 1;
	}
	target=offensive_target(me);
	switch (random(7))
	{
		case 0:
			break;
		case 1:
			if( me->is_fighting()&& objectp(target)
				&&me->query_skill("songyang-shou", 1) > 350 
				&&me->query_skill_mapped("hand")=="songyang-shou" 
				&&me->query_skill_prepared("hand")=="songyang-shou" )  
			{
					target->add_busy(1);
					weapon->unequip();
					message_vision(CYN"\n$NĬ���������ķ�Ҫּ����$n��ע��������ĳ�һ�С��������֡���\n" NOR, me,target);
					me->add_temp("apply/hand",i/4);
					COMBAT_D->do_attack(me, target,me->query_temp("weapon"),userp(me)?3:1);
					me->add_temp("apply/hand",-i/4);
         			weapon->wield();
			}
			break;
		case 2:
			if( me->is_fighting()&& objectp(target)
				&&me->query_skill("hanbing-shenzhang", 1) > 450 
				&&me->query_skill_mapped("strike")=="hanbing-shenzhang" 
				&&me->query_skill_prepared("strike")=="hanbing-shenzhang" )  
				{
					target->add_busy(1+random(1));
					weapon->unequip();
					message_vision(HIW"\n$NĬ���������ķ�Ҫּ������ת$n����Ƴ����ơ��������ơ���\n" NOR, me,target);
					me->add_temp("apply/strike",i/4);
					COMBAT_D->do_attack(me, target,me->query_temp("weapon"),userp(me)?3:1);
					me->add_temp("apply/strike",-i/4);
         			weapon->wield();
				}

			break;
		case 3:
		case 4:
		case 6:
		default:
			break;
	
	}

	call_out("ssj_songyang",1,me,count--);

}



string perform_name(){ return YEL"������"NOR; }

int help(object me)
{
        write(HIW"\n��ɽ����֮������������"NOR"\n\n");
        write(@HELP
	��ɽ�����С��ڰ�·�����·��֮�ƣ��ܹ�ʮ��·���̿����Ľ���
	Ӧ�о��С���������������ħ��ʮ�������Ȼ�ս��ɽ����������
	�ĺ������˴��������ɽ�������ྪ�����������ɸ��ֶ����š�
	��ɽ�������������Ἧ���ɲд�����ϣ����������ǵõĽ��в�
	�۴־�������¼�����������һ�����ס�
	����������ɽ�������ķ����似���ǽ���ɽ�������书���ں���
	һ��ı�Ҫ�ķ����������似��Ϊ��ɽ�ɲ���֮��,�����������

	ָ�perform sword.songyang
	
Ҫ��
	��ǰ�������� 1500 ���ϣ�
	��ǰ�������� 300 ���ϣ�
	��ɽ�����ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�������ֵȼ� 350 ���ϣ�
	��������Ϊ��ɽ������
	�����м�Ϊ��ɽ������
	�����ַ�Ϊ�������ֻ򺮱����ƣ�
	���ֱֳ�����


HELP
        );
        return 1;
}
