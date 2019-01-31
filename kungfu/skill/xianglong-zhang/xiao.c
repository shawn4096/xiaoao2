// By Snowman@SJ
// modified by snowman 20/06/2000
// modify by looklove 2001.5.22 update help
// add 450 ��Ծ by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;

void check_fight(object me,object target);
string perform_name(){ return HIY"����Х"NOR; }

int perform(object me, object target)
{
       int skill = me->query_skill("xianglong-zhang",1);

    if(!userp(me)) skill = skill /6; //����npc������
	else skill=skill/3;


	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("ֻ����ս����ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("�������ֲ���ʹ�á�����Х����\n");

	if( (int)me->query("neili") < 5000 )
		return notify_fail("��������Ҫ�����ڹ�֧�ţ��������������\n");

	if( (int)me->query_temp("xlz/xiao") )
		return notify_fail("���Ѿ���ʼ�˽���Х��\n");

	if( (int)me->query_skill("xianglong-zhang", 1) < 450 )
		return notify_fail("��Ľ���ʮ���ƻ�������죬ʹ����������Х������\n");

	if( (int)me->query_skill("force") < 450 )
		return notify_fail("����ڹ��ȼ�������ʹ����������Х������\n");

	if( (int)me->query_str(1) < 60 )
		return notify_fail("�������������ǿ����ʹ����������Х������\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 450 )
		return notify_fail("��Ļ��������ȼ���������ʹ����������Х��������\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

	if( me->query_skill_prepared("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("parry") != "xianglong-zhang")
		return notify_fail("�������޷�ʹ�á�����Х����\n");

	me->add("neili", -400);
	me->add("jingli", -150);
	message_vision(YEL "\n����ʮ�����������似�۷壬ԽսԽ�£�$N�����Х����ʹ����ʮ���ƾ�Ȼ���������������ɵ���\n"+
		"$NԴԴ������������ɽ�������ѹ��$n��$nֻ����$N������������ӿ����ʱ��ѹ�ƵĶ������á�\n\n" NOR, me, target);
	if( me->query("jiali") < 50 )
		me->set("jiali", 50);
	me->set_temp("xlz/xiao", skill);
    me->add_temp("apply/attack", skill /2);
    me->add_temp("apply/strike",skill/5);
    //me->add_temp("apply/parry",skill/5);
    me->add_temp("apply/damage",skill/5);
        //me->set_temp("double_attack",1);        
    me->add_temp("apply/strength", skill/15); //�����ʱ����
	if (random(3)&&me->query_skill("xianglong-zhang",1)>500)
	{  
		message_vision(HIR"$N��ʮ���������������ڽ�����������¯���࣬������˸��������á�$nһʱ���죬Ϊ$N�����ƾ������ơ�\n"NOR,me,target);
		target->apply_condition("no_perform",  1+random(2)); //������ǣ��
    }
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	if (me->query_skill("xianglong-zhang",1)<500)
	{
		me->start_perform(3, "������Х��"); //450����
	}
	call_out("check_fight", 1 , me, (skill/3 > 10?skill/3:10));
    return 1;
}

void check_fight(object me, int i)
{
	int j;

	if( !me ) return;
	if( !intp(j = me->query_temp("xlz/xiao"))) return;

	i--;
	if( !me->is_fighting()
	 || i < 1
	 || me->query_temp("weapon")
	 || me->query_temp("secondary_weapon")
	 || me->query_skill_prepared("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("force") != "huntian-qigong"
	 || me->query_skill_mapped("parry") != "xianglong-zhang"
	 || me->query("neili") < j + 200) {

                me->add_temp("apply/attack", -j /2);
                me->add_temp("apply/strength", -j/15);
                me->add_temp("apply/strike",-j/5);
               // me->add_temp("apply/parry",-j/4);
                me->add_temp("apply/damage",-j/5);
		        me->delete_temp("xlz/xiao");
               // me->delete_temp("double_attack");

		        me->add("neili", -j );
                me->start_perform(6, "������Х��");
		message_vision(YEL "\n$N��Х��ϣ��������������˲��ٵ�����������ʮ���Ƶ�����Ҳ�ָ�Ѱ���ˡ�\n" NOR, me);
		return;
	}
	call_out("check_fight", 1, me, i);
}

int help(object me)
{
	write(HIY"\n����ʮ����֮������Х����"NOR"\n");
	write(@HELP
	����ʮ�����������ֵ�һ���ؤ��������������֮һ���������Ტ�ã�������գ�
	�������ᣬ���ظ��������������վ��ᾢ���Ϊһ��������ǿ���������̺��£���
	����֮���������ᣬ�������յ�һ���Ʒ�֮�������˫����������������˵����
	����ѧ�е��۷���裬�������Ƽ����棬���������������������������ʽ��
	��������������书����Ҫ֮����ȫ���˾�������ȫƾ��ǿ����ȡʤ���������޼�
	���ݡ��޹̲��ƣ����������ޣ���ÿ��һ�ƾ���������Х֮�ơ�ÿ��һ�о��߾���
	��������
	����ʮ���Ʊ���õ������Ĵ��ڷ���ϰ�ã���������Х�����ǽ����ƾ����������
	��������ʩչ���ɶ�ʱ���ڿ�������������������ͬʱ���������޴�500���ɡ�
	
	ָ�perform strike.xiao
	
Ҫ��	
	��ǰ���� 5000��
	�����Ƶȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	���� 60 ���ϣ�
	�����Ʒ������ƣ�
	�����ڹ�Ϊ����������
	�����м�Ϊ�����ơ�
HELP
	);
	return 1;
}
