// modified by darken@SJ

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int focus, i, j;
	string str;

	focus = me->query_temp("ss/focus");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill("songshan-jian", 1) < 250 )
		return notify_fail("�����ɽ��������̫ǳ���޷�ʹ�÷��蹥����\n");

	if( me->query_skill("sword", 1) < 250 )
		return notify_fail("��Ļ�����������̫ǳ���޷�ʹ�÷��蹥����\n");

	if( me->query_skill("hanbing-zhenqi", 1) < 250 )
		return notify_fail("����ڹ�����̫ǳ���޷�ʹ�÷��蹥����\n");
                
	if( me->query("max_neili") < 2000 )
		return notify_fail("�������̫ǳ���޷�ʹ�÷��蹥����\n");

	if( me->query("neili") < 800 )
		return notify_fail("����������㣬�޷�ʹ�÷��蹥����\n");

	if (me->query_skill_mapped("force") != "hanbing-zhenqi")
		return notify_fail("����ʲôΪ������ʹ��ɽ������ô?\n");

	if (!objectp(weapon = me->query_temp("weapon")) 
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "songshan-jian"
	|| me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("��ʹ������ɽ������ô?\n");

	i = me->query_skill("songshan-jian", 1);

	message_vision(HIB"\n$N��Хһ�����ٽ�ͦ�̣��ڰ���л����������⣬����������������������$n��Ϯ��ȥ��\n" NOR,me,target);
  if(me->query_temp("ss/hb"))
	message_vision(HIB"\n$N�����������������ӵ����쾡�£����ܺ����ʢ��\n" NOR,me);
 
	j = i / 4;
        if ( i > 200 )
	j = to_int(i/ 4.0 * i/ 200.0);

	if ( focus > 20 ) focus = 20;
	j += 5 * focus;
	
	//����NPC����
    if(!userp(me)) j = j /4;

		
		me->add_temp("apply/attack", j/2);
	    
		me->add_temp("apply/sword",  j/4);
        //me->add_temp("apply/hand",  j );
	    me->add_temp("apply/damage", j/4 );
	if(me->query_temp("ss/hb"))
	{
       	me->add_temp("apply/damage", j/4);
		me->set_temp("ssj/fwhanbing",1);
	}
    if (me->query("quest/ss/ssjf/feiwu/pass"))
    {
		message_vision(HIG"\n$N�����Լ�������ġ����η��衹�������ӳ������������ʩչ�������ǳ����뻯������������\n" NOR,me,target);
		if (!userp(target))
			target->add_busy(2+random(1));
		else target->add_busy(1);
		me->add_temp("apply/damage", j/5);
		me->add_temp("apply/sword", j/5);
    }
	me->set_temp("ss/feiwu",j);
	
	if (wizardp(me)) write("damage="+j);
	//1
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	//2
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
    //3
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//4,,,,250���ٳ�һ��
    if(me->is_fighting(target) && (int)me->query_skill("songshan-jian", 1) > 250 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    //5,,,300���ٳ�һ��������
	if( me->is_fighting()&& objectp(target)
		&&me->query_skill("songyang-shou", 1) > 300 
		&&me->query_skill_mapped("hand")=="songyang-shou" 
		&&me->query_skill_mapped("hand")=="songyang-shou" )  
		{
		  target->add_busy(1+random(1));
	      weapon->unequip();
		  message_vision(HIC"\n$N��Хһ��������ͻ�䣬���н����һ������ʯ������Ȼʩչ���������ֵ�������\n" NOR, me);
		  me->add_temp("apply/hand",j/3);
		  COMBAT_D->do_attack(me, target,0, userp(me)?3:1);
		  me->add_temp("apply/hand",-j/3);
          weapon->wield();
		}
/*
	
if(me->is_fighting(target)&&me->query_skill("songshan-jian",1)>300)
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	*/
	if(me->query_temp("ssj/fwhanbing"))
	{
		me->add_temp("apply/damage", -j/4);	
		me->delete_temp("ssj/fwhanbing");
    }
	if (me->query("quest/ss/ssjf/feiwu/pass"))
    {
		me->add_temp("apply/damage", -j/5);
		me->add_temp("apply/sword", -j/5);
    }
	me->add_temp("apply/attack",-j/2);
	me->add_temp("apply/sword",  -j /4);
       // me->add_temp("apply/hand",  -j );
	me->add_temp("apply/damage", -j/4 );
    me->delete_temp("ss/feiwu");
	me->add("neili", -350);
	me->add("jingli", -150);
	me->start_busy(1+random(2));
	me->start_perform(3+random(2), HIB"����"NOR);
	message_vision(HIB"\n$N�⼸����ʸ��磬�����ɷ��裬ʩչ��󣬳���һ�����������չ���\n" NOR,me);

	return 1;
}

string perform_name(){ return HBBLU+HIW"�������"NOR; }

int help(object me)
{
        write(HIB"\n��ɽ����֮�����衹��"NOR"\n\n");
        write(@HELP
	��ɽ�����С��ڰ�·�����·��֮�ƣ��ܹ�ʮ��·���̿����Ľ���
	Ӧ�о��С���������������ħ��ʮ�������Ȼ�ս��ɽ����������
	�ĺ������˴��������ɽ�������ྪ�����������ɸ��ֶ����š�
	��ɽ�������������Ἧ���ɲд�����ϣ����������ǵõĽ��в�
	�۴־�������¼�����������һ�����ס�
	���������ʽ����ɽ�ɵľ���֮һ������ƾ��һ�������ڶ�ʱ��
	���������У����������ɽ�ɶ����ڹ����������������������
	������ע����Ƿ���ÿ200��������Ծһ�Ρ�
	
	ָ�perform sword.feiwu

Ҫ��
	��ǰ�������� 800 ���ϣ�
	����������� 2000 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��ɽ�����ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	�����ַ�Ϊ�������֣�
	��������Ϊ��ɽ������
	�����м�Ϊ��ɽ������
	�����ڹ�Ϊ����������
	���ֱֳ�����

HELP
        );
        return 1;
}
