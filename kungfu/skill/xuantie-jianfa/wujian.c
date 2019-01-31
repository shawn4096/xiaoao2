// wujian.c
// tiantian@sj
// modified by olives@SJ 4/31/2001
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIB"�޽�ʤ�н�"NOR;}

void remove_effect(object me, object weapon);
int perform(object me, object target)
{
	int skill;
	int i;
	object weapon;

	skill = (int)me->query_skill("xuantie-jianfa", 1);                

	if( !target ) target = offensive_target(me);

	if( !target || !me->is_fighting(target) )
		return notify_fail("���޽�ʤ�н���ֻ����ս����ʹ�á�\n");

	if(me->query_temp("wujian"))
		return notify_fail("������ʹ�á��޽�ʤ�н�����\n");

	if(!objectp(weapon = me->query_temp("weapon")) 
		|| weapon->query("skill_type")!="sword")
		return notify_fail("�������޽������ʹ�ĳ����������ľ�����\n");

	if(weapon->query("unique")
		|| !userp(me) )
		return notify_fail("����������������������ᡸ�޽�ʤ�н������⾳?\n");

	if( (int)me->query_skill("xuantie-jianfa", 1) < 350 ) 
		return notify_fail("�����������������죬����ʹ�á��޽�ʤ�н�����\n");
		
	if( (int)me->query_skill("force", 1) < 350 )
		return notify_fail("��Ļ����ڹ��ȼ�����������ʹ�á��޽�ʤ�н�����\n");

    if (me->query_skill_mapped("sword") != "xuantie-jianfa" )
		return notify_fail("�������޷�ʹ�á��޽�ʤ�н�����\n");
    //�޽�ʤ�н��˶��¾����������ڹ���
    //if( me->query_skill_mapped("force") != "yunu-xinjing" && userp(me))
                //return notify_fail("�������޷�ʹ�á��޽�ʤ�н�����\n");

	if( me->query("max_neili")<5000)
		return notify_fail("���������Ϊ̫�����ʹ�á��޽�ʤ�н�����\n");
	if( (int)me->query("neili") < 2000 )
		return notify_fail("����������̫��������ʹ�á��޽�ʤ�н�����\n");

    if (me->query_skill("xuantie-jianfa",1)<350)
             me->start_perform(1,"���޽�ʤ�н���");

	message_vision(HIB "\n$N��������ע���ϣ����������˽���������ؼ���һ����Ϊ�������롸�޽�ʤ�н����ľ��硣\n" NOR, me, target);
    
	i=(me->query_skill("xuantie-jianfa",1)+me->query_skill("force",1))/6;
	if (me->query("gm/wujian")>=2)
	{ 
	  i*=me->query("gm/wujian");//�޽����������
	  message_vision(HIB "\n$N�Ѿ�����������½��⣬�����������Ѵﲻ����������Ϊ�����ľ���\n" NOR, me, target);
	}
	i=i+random(i);
	if(me->query("gm/wujian")<2&& i> 350 && userp(me)) i=350+(i-350)/10; 
	//�޽���һ���������������ڶ��������η�Ծ
	
	me->add("neili",-i*2);
	me->add_temp("apply/damage",i);
	me->add_temp("apply/attack",i);
	me->add_temp("apply/sword",i);
	me->set_temp("wujian",i);
	call_out("check_fight",1,me,weapon);
	return 1;
}

void check_fight(object me, object weapon) 
{ 
	if (!me||!living(me)) return;
	
	if(!me->is_fighting()
	|| !me->query_temp("weapon")
	||  me->query_skill_mapped("sword")!="xuantie-jianfa"
	||  me->query_temp("weapon") != weapon) 
	{
		remove_effect(me,weapon);
		return;
	}
            call_out("check_fight", 1, me, weapon); 
} 

void remove_effect(object me, object weapon)
{
	int lvl;

	if (!me)
		return;
	lvl = me->query_temp("wujian");
	me->add_temp("apply/damage",-lvl);
	me->add_temp("apply/attack",-lvl);
	me->add_temp("apply/sword",-lvl);
	me->delete_temp("wujian");
	if (!weapon) {
		me->set_temp("last_damage_from", "����ʧ�ܱ��ͷ�");
    	me->unconcious();
		return;
	}

}

int help(object me)
{
        write(HIB"\n�����������޽�ʤ�н�����"NOR"\n\n");
        write(@HELP 
	�޽�ʤ�н��Ƕ�����ܵ��İ�ľ����ľ��磬
	�����������ڽ�ڣ�����ԣ���ʮ�������
	�����Կ�Ϊ����
	�޽���Ϊ���Σ���һ����Ȼʹ�á��ڶ�����Ҫ
	�����½���ȥ������ܡ������Σ���Ҫ��ĳ��
	��̲ȥ���򣬴Ӷ��ﵽ��󾳽硣�޽����Ǳ�
	���书�ĺ��ľ����似�����̺��˶�����ܵ�
	�����ľ�����⾳��Ҳͬʱ�̺�������ʤ����
	�⾳�ĸ�Զ��550�����ɡ�
        
	ָ�perform sword.wujian
	
Ҫ��
	��ǰ����Ҫ�� 5000 ���ϣ�
	�������Ҫ�� 3000 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��Ů�ľ��ȼ� 350 ���ϣ�
	��Ч�ڹ��ȼ� 350 ���ϣ�
	��������Ϊ����������
	�����м�Ϊ����������
	��װ���������ʱ���޷�ʹ�á�

HELP
        );
        return 1;
}
