// huagu.c ����

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIG"���Ǿ�"NOR;}

int perform(object me, object target)
{
        string msg;
		int count;
        int skill,damage;

       	if( !target ) 
       		target = offensive_target(me);
		
		skill=me->query_skill("huagu-mianzhang",1);
		skill=skill+me->query_skill("dulong-dafa",1)/5;
		damage=me->query_skill("huagu-mianzhang",1)*me->query_str(1)/10;
		count=(int)skill/50;
        if( !target || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me) 
        || target == me
        || !target->is_character())
        	return notify_fail("���뻯˭�Ĺǣ�\n");

        if(target->query("combat_exp") < 80000)
           	return notify_fail("ɱ������ţ����û��Ҫʹ�û��ǰɡ�\n");

        if(me->query("age") < 16) 
        	return notify_fail("����������̫С���в���ʹ�û��ǡ�\n");
		if(me->query("gender")=="Ů��") 
        	return notify_fail("�㲻�����ˣ��в���ʹ�û��Ǿ���\n");

        if(userp(me) 
        && userp(target) 
        && target->query("age") < 17)
                return notify_fail("����ĳ�̫����, �����޸���֮�������Ҳ�µ����֡�\n"); 

        if(userp(me) 
        && userp(target) 
        && target->query("combat_exp") < me->query("combat_exp")/10)
                return notify_fail("����ĳ�̫����, �����޸���֮�������Ҳ�µ����֡�\n");
		
		if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ��ܻ��ǣ�\n");

        if((int)me->query_skill("huagu-mianzhang",1)<350)
                return notify_fail("��Ļ������ƻ���������������ʹ�ã�\n");
		
		if(!me->query("quest/sld/hgmz/pass"))
                return notify_fail("��ֻ����˵���Ļ������Ƶ�������������ʹ�ã�\n");
        if( (int)me->query("neili") < 2000 )
                return notify_fail("�������������㣬���ܻ��ǣ�\n");     

        if( (int)me->query("jingli") < 1500 )
                return notify_fail("�����ھ������㣬���ܻ��ǣ�\n");     

        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("��Ķ����󷨹������㣬���ܻ��ǡ�\n");
		if( (int)me->query_skill("poison", 1) < 150 )
                return notify_fail("��Ķ��ƹ������㣬���ܻ��ǡ�\n");
		if( (int)me->query_skill("shenlong-yaoli", 1) < 200 )
                return notify_fail("�������ҩ�������㣬���ܻ��ǡ�\n");
		if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("û�ж�������Ϊ���������޷�ʹ�������ǡ������ģ�\n"); 
		
		if (me->query_skill_mapped("strike") != "huagu-mianzhang"
			||me->query_skill_prepared("strike") != "huagu-mianzhang"
			||me->query_skill_mapped("parry") != "huagu-mianzhang")
                return notify_fail("û�м����������ƣ����޷�ʹ�������ǡ������ģ�\n"); 
    	if (me->query_temp("hgmz/huagu"))
                return notify_fail("������ʹ�û��Ǿ���\n"); 
		
        msg = HBYEL+HIW "\n$N��Ȼ������Ц����Ц������˫�Ʋ���һ�㾢����ңң����$p���������һ�ƣ�\n"NOR;		

        if( random(me->query_skill("huagu-mianzhang",1)) > (int)target->query_skill("parry",1)/2
			||random(me->query_str(1))>target->query_str(1)/2)
        {
                //tneili = target->query("max_neili");
                //mneili = me->query("max_neili");
         	    msg+=HIR"$n����һ�ɰ�����Ȼ���ĵ����ص��У�һ���������޵�������Ϣ��ʱϮ����\n"NOR;
        		
				
				target->receive_damage("qi",random(1000),me);
				target->receive_damage("jingli",random(1000),me);
				if (target->query("neili")>1000)
					target->add("neili",-random(1000));

				target->apply_condition("huagu_poison",2);
               	me->add("neili",-300);
				me->add("huagu",-200);
       	} 
        else {
                msg += "$p���Ա�һ������������С�\n"NOR;
                //me->start_busy(1);
        }
        message_vision(msg, me, target);
		if (!me->query_temp("hgmz/huagu"))
		{
			message_vision(HIB"$N˫�ֺ�Ȼ��������ޱȣ�ʩչ���������ƾ�����"+HIW"����"+HIB"��!\n"NOR,me);
			me->add_temp("apply/attack",skill/3);
			me->add_temp("apply/damage",skill/6);
			me->add_temp("apply/strike",skill/6);
			me->set_temp("hgmz/huagu",skill);
			if (objectp(target)&&!target->query_condition("huagu_poison"))
			{
				target->apply_condition("huagu_poison",2);
			}
			call_out("remove_effect",1,me,target,count);	
		}
		
		me->add("jingli",-200);
		me->add("neili",-300);
        //me->kill_ob(target);
        if (objectp(target)&&userp(target))
			target->kill_ob(me);
        return 1;     
}

void remove_effect(object me,object target,int count)
{
	int skill;
	
	if (!me) return 0;
	skill=me->query_temp("hgmz/huagu");

	if (count<0 
		||!objectp(target)
		|| !me->is_fighting()
		|| me->query_skill_mapped("strike")!="huagu-mianzhang")
	{
		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/6);
		me->add_temp("apply/strike",-skill/6);
		message_vision(HIG"$N����һ�����������˵Ļ��Ǿ������ջص��\n"NOR,me);
		me->delete_temp("hgmz/huagu");
		return;
	}
	if (objectp(target)&&random(10)>7)
	{
	
		if (random(me->query("neili"))>target->query("neili")/2 && !random(2))
		{
			message_vision(HBGRN+HIW"$N�������󷨵ľ����������У�����������$nһ��С�����˻��Ƕ���\n"NOR,me,target);
			target->add_condition("huagu_poison",1);

		}
	}
	if (objectp(target)&&!random(4))
	{
		if (random(me->query("combat_exp"))>target->query("combat_exp")/2 && !random(3))
		{
			message_vision(HBGRN+HIW"$N���١��ĵͺ�һ�����������ƾ���������һ�ɰ���˳���ĵ�$n���ϡ�\n"NOR,me,target);
			target->add_condition("neishang",1);
		}
	}
	
	call_out("remove_effect",2,me,target,count-1);
	return;

}
int help(object me)
{
   write(WHT"\n�������ơ�"HIG"���Ǿ�"NOR"����"NOR"\n");
   write(@HELP
	�����������ߵ������似����һ�ּ�Ϊ��������������
	���������ƻ��е��˿�ʼ���粻����������ʱ��������
	������ȫ��������������࣬������ϣ��อ���ѣ���
	�����ԣ����޾��Ρ�
	���������С����Ǿ���������Ҫ������֮�ھ��˵У���
	��ʱ���������������Ƶ�������ͬʱ�и������ӶԷ���
	������Ч�������и��ʱ����Ƕ����ˡ�����й��ڴ���
	������������Է��ĳ�ɱ��Ϊ��Ҫ�ĸ��������似��
	
	ע�⣺������������������Ҫ�似����ԱȽϸ��𣬲�
	ͬ�����û������ͬ��Ӱ�졣
	���ã�set �������� <����>
	set �������� ����
	Ч�������и��ʶ�ȡ�Է����������ǶԷ�����ʧЧ
	set �������� ��Ѩ
	Ч�������и���ʹ�öԷ�����Ѩ�������С�������æµ
	set �������� ����ɢ��
	Ч����ͨ�������󷨽����ڶ���ɢ����ȥ������Բ���
	ǧ������ҩ����ɫ���ػ��������Ƕ����߶���Ч��
	set ɢ�� <ǧ����>/<���Ƕ�>/<���ɢ> ���С������
	�Է��ж��¼���Ĭ��ֵΪ�߶���
	ͬʱ����Ϊ�������ƾ��ж����ص㣬�������������ɫ
	���似�����ԣ���Ч��ȫ��������������Լ����ԡ�
	 
	ָ�perform strike.huagu

Ҫ��
	�������Ҫ�� 3000 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	�������Ƶȼ� 350 ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	�˵м���Ҫ�� 100 ���ϡ�
	����ҩ��Ҫ�� 200 ���ϣ�
	���Ƶȼ�Ҫ�� 150 ���ϣ�
	�����Ʒ�Ϊ�������ƣ�
	�ұ��Ʒ�Ϊ�������ƣ�	
	�����м�Ϊ�������ƣ�
	�����ڹ�Ϊ�����󷨣�
	�������ʹ�ã�
HELP
   );
   return 1;
}

