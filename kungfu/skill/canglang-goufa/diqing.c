// diqing.c ���ཱུ��
// created by Olives@SJ
// Update By lsxk@hsbbs 2007/6/6

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIY"���ཱུ��"NOR;}

void back(object target);

int perform(object me, object target)
{
        int skill,ap,pp,time;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("�����ཱུ����ֻ�а��˽���������ã�\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 200 )
                return notify_fail("�������ذ��������죬����ʹ�õ��ཱུ����\n");

        if( (int)me->query_skill("hook", 1) < 200 )
                return notify_fail("��Ļ�������������죬����ʹ�õ��ཱུ����\n");
		if(!weapon || weapon->query("skill_type")!="hook" )
                return notify_fail("�������޷�ʹ�õ��ཱུ����\n");
        if( (int)me->query_skill("dulong-dafa", 1) < 200 )
                return notify_fail("��Ķ����󷨲�����죬����ʹ�õ��ཱུ����\n");

    	if( (int)me->query("neili", 1) < 800 )
       		return notify_fail("�������������㣡\n");
       	if( (int)me->query("jingli", 1) < 500 )
       		return notify_fail("�����ھ������㣡\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       		return notify_fail("��������Ϊ���㣡\n");
        if( (int)me->query_str() < 50  )
                return notify_fail("��ı���̫�ͣ�����ʹ�õ��ཱུ����\n");
        if (me->query_skill_mapped("hook") != "canglang-goufa"
			||me->query_skill_mapped("parry") != "canglang-goufa")
                return notify_fail("����ʹ�õ��似���ԣ������޷�ʹ�õ��ཱུ����\n");
		if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("�㼤���ڹ����ԣ������޷�ʹ�õ��ཱུ����\n");

        if (!weapon
			||weapon->query("skill_type")!="hook")
                return notify_fail("�������޷�ʹ�õ��ཱུ����\n");

        if(target->query_temp("clgf/diqing")
        || target->query_temp("block_msg/all"))
                return notify_fail("�����۾��Ѿ�Ϲ�ˣ��������õ��ཱུ���ˣ�\n");
        if (me->query_temp("clgf/diqing"))
				return notify_fail("�����Ÿ��ù����ཱུ���ˣ�\n");
		skill = (int)me->query_skill("canglang-goufa", 1);

	    ap = COMBAT_D->skill_power(me,"dagger",SKILL_USAGE_ATTACK);
        pp = COMBAT_D->skill_power(me,"parry",SKILL_USAGE_ATTACK);
        if(target->is_busy())
        	pp /= 2;
        if (me->query("gender")=="����")
           ap=ap+skill;
        me->add("neili", -350);
        me->add("jingli", -200);
        message_vision(HIY "\n$N�����չ�������ʹ��һ�С����ཱུ������������ײ��ʮָ��$n�ؿ���ץ���������֮�ʣ�ͻȻһ������������\n"
							+"����Ծ��˫��һ�֣�������$n��ͷ��ͬʱ˫��Ĵָѹס$n̫��Ѩ��ʳָ��ü����ָ���ۡ�\n"NOR,me,target);

        message_vision(HIY"$n���һ������æ������ʶ��˫�ۻ�ת���뻤ס˫�ۣ�\n"NOR, me, target);;

 	   if(random(ap+pp)>pp
		||random(me->query_str(1))>target->query_str(1)/2)
       {
                message_vision(HIR"\nֻ��$n�ҽ�һ����$N����֧��ָ�Ѿ�����$n���ۿ���ֻ��$n���۽���Ѫֱ����\n"NOR, me, target);
                if (!target->query_temp("clgf/diqing"))
                {
					target->add_temp("apply/attack", - skill/3);
					target->add_temp("apply/defense", -skill/3);
					target->add_temp("apply/parry", -skill/3);
					target->set_temp("block_msg/all",1);
					target->set_temp("clgf/diqing",skill);
					time = 3+skill/10;
					if(time>60) time = 60;
					call_out("back", time, target);

                }

                target->receive_damage("qi", skill*5,me);
                target->receive_wound("qi", skill*5/2,me);
                if(userp(me) && me->query("env/damage"))  
					tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ skill*5+ WHT"�㹥���˺���\n"NOR); 
                if(userp(target)&& target->query("env/damage"))  
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ skill*5+ WHT"���˺���\n"NOR);
				COMBAT_D->report_status(target);
                target->kill_ob(me);
                me->start_perform(3,"���ཱུ��");
        }
		 else {
                message_vision(HIY"$n��ͷ����һ������������㿪��$N��һ�С�\n"NOR, me, target);
                if((int)me->query_skill("canglang-goufa",1)>150){
                  message_vision(HIR"\n$N�ĿϾʹ˰��ݣ���æ������ǰһ��ǿ����$n�پ����ɾ���Ϯ��!\n"NOR, me, target);
                  me->add_temp("apply/damage",skill/5);
                  me->set_temp("clgf/diqing",1);
                  COMBAT_D->do_attack(me,target,weapon,1);
                  COMBAT_D->do_attack(me,target,weapon,2);
                  COMBAT_D->do_attack(me,target,weapon,3);
                  me->delete_temp("clgf/diqing");
                  me->add_temp("apply/damage",-skill/5);
                }
                me->start_perform(2+random(3),"���ཱུ��");
                me->start_busy(2);
                target->kill_ob(me);
        }

        return 1;
}

void back(object target)
{
        int lvl;
        if(!target) return;
        lvl = target->query_temp("clgf/diqing");
        target->add_temp("apply/attack", lvl/3);
        target->add_temp("apply/defense", lvl/3);
		target->add_temp("apply/parry", lvl/3);
        target->set_temp("block_msg/all", 0);
        if(living(target))
              tell_object(target, HIW "��������˫Ŀû�б�ץϹ�����ֿ��Կ�����������\n" NOR);
        target->delete_temp("clgf/diqing");
}

int help(object me)
{
   write(WHT"\n���˹���֮��"HIY"���ཱུ��"WHT"����"NOR"\n");
   write(@HELP
	���˹�������������������������Լ�����ѧ�似
	��������������һ�׹����似��ȥ���ͼ򣬹���Ϭ
	��������ʤ����������ڱ����ϴ��е��Ӷ��ԣ���
	�Ƿǳ�ʵս�Ĺ������е��ཱུ�����ǵ��͵�͵Ϯ
	�似���ȿ��Դ�Ϲ�Է���˫�ۣ���û���У��ֿ���
	�������С��˵��������ǳ���
	  
	perform hook.diqing

Ҫ��
	�������Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 800 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	���˹����ȼ� 200 ���ϣ�
	���������ȼ� 200 ���ϣ�
	�����󷨵ȼ� 200 ���ϣ�
	��ǰ�����ȼ� 50 ���ϣ�
	�Ա����� ���ԡ�
HELP
   );
   return 1;
}
