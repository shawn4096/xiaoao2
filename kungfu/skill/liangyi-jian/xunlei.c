
//xunlei.c Ѹ�׽�����
// cre by sohu@xojh 
//��Ҫ���Ǿ��ǽ�Ѹ�׽�����书��ǰ��Ѹ�׽����⴫�й�����
//��Ҫ���ǿ칥��ʽ�������ڹ����г��У��������ݡ�

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
void checking(object me, object target, int count);
void xunlei_end(object me);

int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
        int speed, attack, lv, damage;

        lv = (int)me->query_skill("liangyi-jian", 1); 
      
        speed = me->query_skill("lianyi-jian",1)/20;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("���ǽ�֮��Ѹ�׽��⡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if( !me->query("quest/kl/lyj/xunlei/pass"))
                return notify_fail("��ֻ�����������ž������޷�ʩչ��"HIG"Ѹ�׽���"NOR"��\n");
        if( me->query_temp("lyj/xunlei"))
			return notify_fail("������ʩչѸ�׽��⣬����δ����������ʩչ��Ѹ�׽��⡹��\n");
	//	if( me->query_temp("lyj/hundun") )
                //return notify_fail("�������ʹ�û��罣���������޷�ʩչ��"HIG"Ѹ�׽���"NOR"������\n");
        if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
			 return notify_fail("��ʹ�õ��������ԡ�\n");
		if( me->query_dex() < 70 )
			return notify_fail("��ĺ�����������\n");

        if( (int)me->query("neili") < 1500 )
			return notify_fail("�������������\n");
		if( (int)me->query("neili") < 1000 )
			return notify_fail("��ľ���������\n");
        if( me->query_skill("liangyi-jian", 1) < 450 )
			return notify_fail("��ġ����ǽ�����δ�����磬�޷�ʹ�á�Ѹ�׽��⡹��\n");
		if( me->query_skill_mapped("sword") !="liangyi-jian"
			||me->query_skill_mapped("parry") !="liangyi-jian" )
			return notify_fail("��û���������ǽ��������޷�ʹ�á�Ѹ�׽��⡹��\n");
        if( me->query_skill_mapped("force") !="xuantian-wuji")
			return notify_fail("��û�����������޼��������޷�ʹ�á�Ѹ�׽��⡹��\n");
		
		if( me->query_skill("xuantian-wuji", 1) < 450 )
             return notify_fail("��������޼���Ϊ�������޷�ʹ�á�Ѹ�׽��⡹��\n");

        msg = HIG "\n$N����"+weapon->query("name")+HIG"����ָ���Լ��ؿڣ�����бб���⣬����֮�������ƻؽ�����һ�㣡\n" NOR;
        msg += HIG "�����������ǽ��ľ�����Ѹ�׽��⡹����ʽʩչ�н�����磬�����з���֮����\n" NOR;

		message_vision(msg, me,target);
        
		if (me->query_skill("liangyi-jian",1)<550)
			me->start_busy(1);
        
        me->set_temp("lyj/xunlei",lv);
        me->add("neili", -500);
        if (me->is_fighting()&& objectp(target))
            call_out("checking", 1, me, target,speed);
        else
			call_out("xunlei_end",1);
		return 1;
}

void checking(object me, object target, int count)
{
		int damage,k;
        object weapon;
		if (!me) return;
		
		damage = (int)me->query_skill("liangyi-jian", 1)+ (int)me->query_skill("xuantian-wuji", 1);
        damage = damage*2 + random(damage);
		
		if ( !objectp( me ) ) return;
        
		if( !target ) target = offensive_target(me);
		
		//weapon = me->query_temp("weapon");
	    //����Խ�ߣ�����Խ��
		//if (random(me->query_skill("liangyi-jian",1))>450) k=3;
	  //  else k=2;
	    

        if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
		{
			tell_object(me, HIR"\n�������޽�������ֹͣ��Ѹ�׽���ļ��ơ�\n" NOR);
			me->delete_temp("lyj/xunlei");
			call_out("xunlei_end", 2, me);
			return;
		}
		else if ( weapon->query("weapon_prop") == 0 ) {
			tell_object(me,HIC "\n���"+weapon->name()+HIC"�ѻ٣��޷�����Ѹ�׽���Ĺ��ƣ�\n\n" NOR);
            //�˳�
			call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}
         else if ( (int)me->query("neili") < 1500  ) {
			message_vision(HIR"$N���ھ�������������ò�ֹͣѸ�׽���Ĺ��ƣ�\n" NOR, me,target);
            call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}
		else if ( me->query_skill_mapped("sword") != "liangyi-jian" ) {
			tell_object(me, HIR "\n��ת��ʩչ�����������޷�����Ѹ�׽��⹥�У�\n\n" NOR);
            call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}

        else if ( //count <= 0 
			!me->is_fighting()
			|| !objectp(target)) 
		{
			tell_object(me, HIC "\n������Ľ��ƺľ��������ջ���Ѹ�׽���Ĺ��ơ�\n" NOR);
            call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}

		if( environment(target) != environment(me) ) {
			tell_object(me, "����Է��Ѿ������������ֹͣ��Ѹ�׽���Ĺ��ơ�\n");
            call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}
		me->set_temp("lyj/xunlei1",1);
        switch (random(3))
        {
			
			case 0:
				message_vision(HIY"$N�����ǰ��"+weapon->name()+HIY"��Ȼ���䵯��������ֱ��$n������֮�켲�����磬�������ף�\n" NOR, me,target);
				
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
				//COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				me->add("neili", -random(600));
				me->add("jingli", -random(500));

				message_vision(HIG"���$n���������ƣ������������˺ü�����\n"NOR,me,target);
				target->add_busy(1+random(3));
				break;
		 	case 1:
				message_vision(HIW"$N��ָ��"+weapon->name()+HIW"��һ�����������ˣ�����������"+weapon->name()+HIW"�������������������޷���\n" NOR, me,target);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				//COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				if ( random(me->query_dex(1))>target->query_dex(1)/2 )
				{   
					message_vision(RED"�����$n�ѱ������Ѵ���ͷ�������������Ѫ��ע��\n"NOR,me,target);
					target->receive_damage("qi",damage/2,me);
					target->receive_wound("qi",damage/4,me);        			
        		}
				me->add("neili", -random(200));
				me->add("jingli", -random(100));
				break;
			case 2:
				message_vision(HIG"$N��Ȼ����һ����"+weapon->name()+HIG"�Ϻ����������ȵ�����"+target->name()+HIG"����С���ˣ���\n" NOR, me,target);
				message_vision(HIR"ֻ��$N���ֻӽ���"+weapon->name()+HIR"������ǰ�����ң�˲Ϣ֮���ѹ���������һʮ���У�\n" NOR, me,target);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				//COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
				message_vision(HIR"���$n�ѱ�����������������Ѫ���������\n"NOR,me,target);    
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);		
				target->receive_damage("qi", damage,me);
				target->receive_wound("qi", damage/2,me);
				me->add("neili", -random(300));
				me->add("jingli", -random(200));
				break;
        }
		me->delete_temp("lyj/xunlei1");
		call_out("checking",2,me,target,count -1);
		return;
        	    
}

void xunlei_end(object me)
{
        object weapon;
		if ( !objectp( me ) ) return;
        
		weapon = me->query_temp("weapon");
        me->delete_temp("lyj/xunlei");

		message_vision(HIG "\n$N���������뽣�ʣ���Ѹ�׽�����Ϊ�ķ�������$N���Ե�Ϣ������ƽ����ӿ��������\n\n" NOR,me);
      
		return;

}

string perform_name() {return HIR"Ѹ�׽���"NOR;}

int help(object me)
{
    write(WHT"\n���ǽ�����"HIR"Ѹ�׽���"WHT"����"NOR"\n");
    write(@HELP
    ���ǽ������������ɾ���������������ʥ������Դ˽�����ɨ�������ۡ�
	���������ִ�ս��һս������ƾ��ľ��Ǵ˽��������ǽ��������ڵ���
	���ǽ�������������Ѹ�ݣ�������ʤ����ȴ�������鶯��䷢�ӵ����¡�
	�������Ṧ�ã������ǽ�������������һ��¥��
	Ѹ�׽����ǽ��������Ѹ�׽��������ںϺ󣬽�Ѹ�׽����Ѹ�ݿ칥��
	�ɣ����뵽���ǽ��У�ʹ�����ǽ��������Ѳ⣬�仯����и���Ѹ�ݡ�
	500����һ�η�Ծ��550���󳹵״�ɡ�
    
	ָ�perform xunlei
	
Ҫ��
	�����޼��ȼ� 450 �����ϣ�
	���ǽ����ȼ� 450 �����ϣ�
	��Ч���ȼ� 70    ���ϣ�
	���������ȼ� 450 �����ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�����ڹ������޼�����
	�����������м�Ϊ���ǽ���
	���ֳֽ���������    

HELP
	);
	return 1;
}


