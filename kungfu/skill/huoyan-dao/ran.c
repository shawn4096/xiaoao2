// by darken@SJ

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;
string perform_name(){ return HIC"ȼ�־�"NOR; }

int perform(object me)
{
        string msg;
        object target;
        int hs, ls,hit_qi,p,damage,damaged;

       
        hs = me->query_skill("huoyan-dao",1);
        ls = me->query_skill("longxiang-boruo",1);
        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
         || environment(target)!= environment(me))
		 return notify_fail("��ȼ��ֻ����ս���жԶ���ʹ�á�\n");
     
        if (objectp(me->query_temp("weapon")))
                return notify_fail("��ֻ�ܿ������á�ȼ���ľ�����\n");
        if( hs < 350)
                return notify_fail("��ġ����浶���ȼ�����, ����ʹ����ȼ���ľ�����\n");
        if( ls < 350)
                return notify_fail("��ġ��������������������, ����ʹ����ȼ���ľ�����\n");
        if( me->query("neili") < 1000 )
                return notify_fail("������������þ�����������ȼ���ˣ�\n");
        if( me->query("jingli") < 1000 )
                return notify_fail("��ľ��������þ�����������ȼ���ˣ�\n");
        if( me->query("max_neili") < 4500 )
                return notify_fail("����������������ܴ߶�����������ȼ��������\n");
        if( me->query_skill_mapped("strike") != "huoyan-dao"
         || me->query_skill_prepared("strike") != "huoyan-dao")
                return notify_fail("�����ʹ�á����浶��������ʹ����ȼ���ľ�����\n");
        if( me->query_skill_mapped("force") != "longxiang-boruo")
                return notify_fail("��������ʹ�õ��ڹ�ͬ���������������ִ�������ʹ����ȼ���ľ�����\n");
 
        msg = HIR "\n$N˫�Ƽ��ٴ궯����Ȼ�����һ����������ӿ����˫�Ʒ�ʹ��Ю������������$n������\n"NOR;
       // if (me->query_temp("honglian/lianxu") && me->query("neili")>target->query("neili")*2/3)
		if (random(me->query("neili"))>target->query("neili")/2
			||random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
        { 
           msg += RED "$N����һ�����ۼ���������ӿ�������������˵���������ɽ��������$n\n"+
           HIW "$n��ͣ��ʹ�������ţ�����$N�����ɵ�"HIY"���������"HIW"һ�����һ��һ����������Ϣ���ң�\n"NOR;
           damage =  8 * ((int)me->query_skill("huoyan-dao", 1)+(int)me->query_skill("longxiang-boruo", 1));
           damage = damage  + random(damage);
		   if (me->query_temp("hyd/power"))
		   {
			   if (damage>6000) damage=6000+(damage-6000)/10;
		   }
		   else if (damage>4000) damage=4000+(damage-4000)/100;
		   if(userp(me) && me->query("env/damage")) 
	             tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
           me->add("neili", -300);
           me->add("jingli",-100);
		   if (target->query("qi")<damage)
			   damage=target->query("qi")-100;
		    
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/2,me);
           msg += "( $n"+eff_status_msg(p)+" )\n";
           target->set_temp("last_damage_from", "��"+me->query("name")+"ɱ");
           
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
           //me->delete_temp("honglian/lianxu");
        }
        else if(random(me->query_skill("force",1)) >  target->query_skill("force",1)*2/5){
                msg+= RED "$nΪ$Nǿ����ڹ����ȣ��������У�ֻ����ȫ�����ȣ���Ϣ��ʱ�ҳ壡\n"NOR;
                target->add("qi", -target->query("qi")*(ls+hs)/2000);
                //target->set("eff_qi", target->query("eff_qi")*(ls+hs)/2000);
                target->add("neili", -target->query("neili")*(ls+hs)/2000);
				target->apply_condition("no_exert",(me->query_skill("huoyan-dao,1")/100+random(5)));
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                target->start_busy(2);
                me->add("neili",-400);
        } 
        else {
                msg += HIY "$n�ڹ����Ǽ�Ϊ�˵ã�����ȫ������Ӳ�ǽ��˹���������������\n" NOR;
                msg+= HIR "$Nֻ����ȫ�����ȣ���Ϣ�ҳ壡"NOR;
                me->set("qi", target->query("qi")*(ls+hs)/1000);
                me->set("eff_qi", target->query("eff_qi")*(ls+hs)/1000);
                me->add("neili",-400);
                target->add("neili",-800);
                target->start_busy(2);
        }

        if (me->query_skill("huoyan-dao",1)<449
			|| me->query_skill("longxiang-boruo",1)<449) 
		{
			me->start_perform(4, "ȼ�־�");
		}
        else 
        {
        	me->start_perform(3,"ȼ�־�");
		}       //���ø�С��Ծ��450�Ժ�pfmbusy�Լ�
        
        message_vision(msg, me, target);
        return 1;
}

int help(object me)
{
	write(HIY"\n���浶�ؼ���ȼ�־�����"NOR"\n");
	write(@HELP
	���浶ȼ�־��Ǵ����³����������ǽ����浶֮������������֮����
	ȼ�־����������Ĺ����д��Ʒ���ʩչ���ǹ���������޷�ʩչ��
	һ�����д󷽣�����Է���������Ѫ�ܵ���ͬ�̶ȵ����ˣ�ע����
	��ϻ��浶����һ�ž���ʹ�ã�������������
	
	ָ�perform strike.ran

Ҫ��
	������������� 4500 ���ϣ�
	��ǰ���������� 1000 ���ϣ�
	����������ȼ� 350 ���ϣ�
	���浶�ȼ����� 350 ���ϣ�
	�����ڹ��ĵȼ� 350 ���ϣ�    
HELP
	);
	return 1;
 }
