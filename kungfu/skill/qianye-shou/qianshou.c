// qianshou ǧ������
// bren

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object target, int skill);
void check_fight(object me,object target,int improve);
int perform(object me, object target)
{
        string msg;
        int skill,ap,dp,i;
        skill = (int)me->query_skill("qianye-shou", 1)+(int)me->query_skill("yijin-jing", 1)/2;                

       if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("��ǧ��������ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("ʹ�á�ǧ��������ʱ˫�ֱ�����ţ�\n");

        if( (int)me->query_skill("qianye-shou", 1) < 350 )
                return notify_fail("�������ǧҶ�ֲ�����죬����ʹ�á�ǧ����������\n");

        if( (int)me->query_skill("yijin-jing", 1) < 350 )
                return notify_fail("����׽�ڹ��ȼ�����������ʹ�á�ǧ����������\n");

        if( (int)me->query_dex() < 27 )
                return notify_fail("���������ǿ������ʹ�á�ǧ����������\n");

        if (me->query_skill_prepared("hand") != "qianye-shou"
        || me->query_skill_mapped("hand") != "qianye-shou")
                return notify_fail("�������޷�ʹ�á�ǧ�����������й�����\n");
        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("����������̫��������ʹ�á�ǧ����������\n");
        if( (int)me->query("neili") < 1500 )
                return notify_fail("����������̫��������ʹ�á�ǧ����������\n");
		if( me->query_temp("fumo"))
				return notify_fail("������ʹ�ô���ȭ�����⹥������շ�ħ����\n");

        if( target->query_temp("qianshou")   )
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ���\n");

// 42          me->start_perform(2,"����ǧҶ��")
        msg = HIY "$N˫�ֺ�ʮ��������Ȼ����һ�֣�˫�ƶ�ʱ�������Ʈ�ݣ��鶯�쳣���������־���֮һ��ǧ��������\n" NOR;
		msg += HIW "$N����һ��һ�ֶ��������ģ���������֮�ƣ���ʱ�����������Ӱ����\n" NOR;
        message_vision(msg, me, target);
		ap=me->query("combat_exp")/10000;
		dp=target->query("combat_exp")/10000;
		i=2;
		if (me->query("quest/sl/qys/pass"))
		{
			message_vision(HBYEL+HIW"$N��ǧҶ�ֹ�����Ȼ��ˣ�˫��һ����ʽ����������\n"NOR,me);
			i=3;
			skill=skill+me->query_skill("hand",1)/3;
		}
        if (random(ap) > dp/i
			||random(me->query_skill("hand",1))>target->query_skill("parry",1)/i)
		{
          msg = HIR "$nֻ�������ܶ���$N����Ӱ�����ɵû���������\n" NOR;
          message_vision(msg, me, target);
          target->add_temp("apply/attack", -skill/3);
          target->add_temp("apply/dodge", -skill/3);
          target->add_temp("apply/parry", -skill/3); 
          target->set_temp("qianshou",skill);   
          me->add("neili", -400);
          me->add("jingli",-150);
          me->start_call_out( (: call_other, this_object(), "check_fight",  me, target, skill :), 1);                             
          return 1;
        }
        message_vision(HIC"$N��������������ϸ������$n����Ӱ��\n"NOR,target,me);
        if (me->query_skill("qianye-shou",1)<449)
        {
			me->start_busy(1);
			me->start_perform(2,"��ǧ��������");
        } 
		if (me->query_skill_mapped("leg")!="ruying-suixingtui"
			||me->query_skill_prepared("leg")!="ruying-suixingtui")
        {
			me->start_perform(1,"��ǧ��������");
        }
        me->add("neili", -100);
        me->add("jingli", -100);
        return 1;
}

void check_fight(object me, object target, int improve) 
{ 
       object weapon;     

       if (!target) return;
       if( !me) {
          remove_effect(target,improve);
       }
       else 
       if(target->query_temp("qianshou") && !me->is_fighting(target))
	   {
          remove_effect(target, improve);
       }
       else if( (target->query_temp("qianshou")) 
        && (!target->is_fighting() 
        || !me->is_fighting() 
        || !living(me) 
        || target->is_ghost() 
        || me->is_ghost() )){
               remove_effect(target, improve);
        }
        else if((target->query_temp("qianshou"))
         && objectp(weapon = me->query_temp("weapon"))){
                remove_effect(target, improve);
        }
        else{
//            target->apply_condition("no_perform",1);
			if (random(10)>6&&me->query("quest/sl/qys/pass")&&objectp(target)&&me->is_fighting())
			{
				message_vision(HIY"$N���з�ţ����ް����ӷ�ǧҶ������һ�֣���ǧ�ֹ���״����ʽ��Ȼ�ӿ죡\n"NOR,me,target);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_RIPOSTE);

			}
            call_out("check_fight", 1, me, target, improve); 
            return;
        }
}

void remove_effect(object target, int skill)
{
        if (!target) return;
        
		target->add_temp("apply/attack", skill/3);
        target->add_temp("apply/dodge", skill/3);
        target->add_temp("apply/parry", skill/3);
        target->delete_temp("qianshou");
        tell_object(target, HIB"�㽥����Ӧ�����ֱ仯��״̬�ָֻ��糣��\n"NOR);
}

string perform_name(){ return HIY"ǧ������"NOR; }
int help(object me)
{
        write(HIB"\n����ǧҶ��֮��ǧ����������"NOR"\n");
        write(@HELP
	����ǧҶ��Ϊ������ʮ������֮һ����������һ����Ҫ���ַ�������
	һ�мȳ��������ݻ���һ�ֶ�����Ϊ�ģ��ĳɰˣ��������������
	�˵Ĺ����վ������޵ģ���Ҫ������һ�����֡�һ�мȳ�����û�ȶ�
	�����У���һ���Ѿ�������ң�뵱�����ַ�֤��ʦ�Դ˾�����ħ����
	����һ��ƴ��������ʽ�仯֮�죬��Ȼ�����������Ц�������Ĵ�ħ
	ͷ���ò������ѧ����׾�Ʒ����࿹�⡣��Ҫע���������ǧҶ����Ҫ
	�����ڹ�֧�֡�
		
	ע�⣺��ǧ���������������Ĺ�Ч�ǽ��ͶԷ��Ĺ������⿪ǧҶ��
		�����ǧ��������ʽ�ӿ죡ֻ�кͻ����书��Ϸ��ɴ�����

	ָ�perform hand.qianshou

Ҫ��  
	������� 3500 ���ϣ�      
	��ǰ���� 1500  ���ϣ�  
	ǧҶ�ֵȼ� 350 ���ϣ�
	�׽�ȼ� 350 ���ϣ�
	�����ַ�Ϊ����ǧҶ�֣�
	�����м�Ϊ����ǧҶ�֣�
	�����ޱ���,450���Ծ��
	���𷨴���180����������Ч�����֡�
	������Ӱ�����Ȼ��������⹦Ч��
                
HELP
        );
        return 1;
}

