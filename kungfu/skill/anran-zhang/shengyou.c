// shengyou.c ��������
// cre by sohu@xojh 2014
// ����ֱ��´������ް�������ʽ�������ܲ�ͨȭ�й����������ͻȻ�������붯���������䡢˫��ͷ���������ر�������������ʽ��������һ�������˵С�
//�ܲ�ͨ��Ȼ����������о��У�ȴ�������벻�������᡾ȫ���빥����˲Ϣ֮�䣬��ʮ������ͬʱ��������˵�����������С�ֻ��һ�У��м�ʵ��ʮ���б�ʽ���ţ������ܲ�ͨ��ѧ��տ��Ҳ���˸���æ���ҡ�
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
int perform(object me, object target)
{
        int lvl, i;

        lvl = me->query_skill("anran-zhang", 1);

        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target) )
                return notify_fail("���������С�ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á��������С���\n");   
		if (me->query("gender")=="����")
			return notify_fail("�����������ͣ����������С�ֻ����ս����ʹ�á�\n");
        
		if( (int)me->query_skill("anran-zhang", 1) < 200 )
                return notify_fail("�����Ȼ�����ƻ�������죬ʹ�������������С�������\n");
		if( (int)me->query_skill("strike", 1) < 200 )
                return notify_fail("��Ļ����Ʒ���������죬ʹ�������������С�������\n");
        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("��Ļ����ڹ��ȼ���������ʹ�������������С�������\n");

        if ( me->query_skill_mapped("strike") != "anran-zhang"
		  || me->query_skill_mapped("parry") != "anran-zhang"
          || me->query_skill_prepared("strike") != "anran-zhang"
)
                return notify_fail("�������޷�ʹ�á��������С�������\n");

      	if ((int)me->query("divorce")>0)
					return notify_fail("��������飬����ʹ�÷��ӳ���Ȼ�����������\n"); 

        if((int)me->query("max_neili") < 3000 )
                return notify_fail("�������������̫����ʹ�������������С���\n");      

        if((int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ�������������С�������\n");
		if((int)me->query("jingli") < 500 )
                return notify_fail("����������̫����ʹ�������������С�������\n");
        if((int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("����������ܺã���ôʹ�ó����������С�������\n");

        if( me->query_temp("arz/shengyou")) 
                return notify_fail("����������ʹ�á��������С�������\n"); 
		if (me->query("divorce"))
					return notify_fail("��������飬����ʹ�÷��ӳ������ˮ������\n");
        if((int)me->query("qi") == 0 )
			   return notify_fail("�������޷�ʹ�á��������С�������\n");

        
		me->set_temp("arz/shengyou", 3);
        i = (int)me->query("max_qi") / (int)me->query("eff_qi");

        if( i > 3 ) i = 3;
        if( i < 1 ) i = 1;

        if( i > 1 ){
           me->add_temp("apply/strength",lvl/3);
           me->set_temp("hurt", 1);
        } 
		message_vision(HIR"$N�ֱ��´������ް�������ʽ������$nȭ�й����������ͻȻ�������붯���������䡢\n"
							+"˫��ͷ���������ر�������������ʽ��������һ�������˵С�����һ��"HIY"���������С���\n"NOR,me,target);
        me->add_temp("apply/damage", lvl/2);
        me->add_temp("apply/strike", lvl);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
     
		me->add_temp("apply/damage", -lvl/2);
        me->add_temp("apply/strike", -lvl);

        if(me->query_temp("hurt")){
            me->add_temp("apply/strength",-lvl/3);
            me->delete_temp("hurt");
        }
        me->add("neili", -random(500));
        me->add("jingli", -random(200));
        me->delete_temp("arz/shengyou");
        me->start_perform(4,"��������");
		if (me->is_fighting())
			call_out("shengyou_attack",0,me,target);

		
		//me->start_busy(1+random(2));
        return 1;
}
// �������е�10���ܼ��͹���

int shengyou_attack(object me,object target)
{
	int count,arg,damage;
	string *limbs;
	
	if( !arrayp(limbs = target->query("limbs")) )
		limbs = ({ "����", "����", "����" });
	//�Ӹ��жϣ��������� by renlai
	//limbs = target->query("limbs");
	arg=(int)(me->query_skill("anran-zhang", 1) / 50);
	//if (arg<4) arg=4;
	damage=me->query_skill("anran-zhang",1);
	damage=damage+me->query_skill("force",1)/5;
	message_vision(CYN"\n\n$n��Ȼ�����$N���о��У�ȴ�������벻��$N����ȫ���빥��˲Ϣ֮�䣬ʮ������ͬʱ������\n"
					+"˵�����������С�ֻ��һ�У��м�ʵ��ʮ���б�ʽ���ţ�����$n��ѧ��տ��Ҳ���˸���æ���ҡ�\n\n"NOR,me,target);
	
	for(count = 0; count < arg; count++)
	{
	  message_vision(replace_string( HIW+SKILL_D("anran-zhang")->query_action(me, me->query_temp("weapon"))["action"]+NOR,	"$l", limbs[random(sizeof(limbs))]) + "��\n\n", me, target);
	}   	
	target->add_busy(1+random(3));
       
	damage = damage*arg;

	if( arg*(random(me->query("combat_exp"))) > target->query("combat_exp") )
	{
		message_vision(HIR"$nΪ$N����ʮ��Ѹ�ݵĶ��������ˣ��۵��³�һ����Ѫ��\n"NOR,me,target);
	
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		target->receive_damage("jingli", damage/10,me);

		COMBAT_D->report_status(target, 1);
		COMBAT_D->report_status(target, 0);
	}
	
	me->set_temp("arz/shengyou", 3);
	target->set_temp("must_be_hit",1);
    COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
    target->delete_temp("must_be_hit");
	me->delete_temp("arz/shengyou");
	me->start_perform(4,"��������");
	me->add_busy(2);
	return 1;
}

string perform_name(){ return HIG"��������"NOR; }
int help(object me)
{
         write(HIB"\n��Ȼ������֮���������С���"NOR"\n");
        write(@HELP
	����Ժ�С��Ů�ھ���ȶϳ���ǰ���֣�������ҹ˼��
	����С��Ů����������������������Ȥ�����ں���֮��
	���������������һʮ�����Ʒ������������Ʒ�����Ϊ
	��Ȼ��������ƣ�ȡ���ǽ��͡��𸳡����Ǿ���Ȼ���
	�����ߣ�Ψ�������֮�⡣���Ʒ�������������������
	�壬��һ������ۺ�������Խ������Խ��ʵ������
	�ض��ú���!
	����������ԭ�����������ͶԷ���ʽ�������ɾ��䶯
	ȫ���޴�������ȫ�����ǻ������Ѹ���ޱȣ����˷�
	��ʤ�����������޷�ʹ�á�
	
	perform strike.shengyou

Ҫ��
	�����Ʒ�Ҫ�� 200 ������
	��Ȼ�Ʒ�Ҫ�� 200 ������
	�����ڹ�Ҫ�� 200 ������
	�������Ҫ�� 3000 ����
	��ǰ����Ҫ�� 1000 ����
	��ǰ����Ҫ�� 500 ����
	�����Ҽ����Ʒ����м�Ϊ��Ȼ��
HELP
        );
        return 1;
}
