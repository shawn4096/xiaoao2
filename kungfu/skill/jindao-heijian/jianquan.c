// jindao-heijian ��Ȧ��ն���
/*
    �������������ս�������е��������������ڽ����������ش�ȥ�����ǽ��Ⲣ��ֱ����
ȴ��������ǰ��תȦ�ӡ������֪��ڽ�Ҫ����η�����֮�£������Ծ��
    ����������ֿ켫�������Ծ�˱ܣ��ڽ����ɵ�ԲȦ����ָ������ǰ����ȦԽ��Խ��
��ʱ��ֻ������ǰ��תȦ������һ����������С��Ҳ���ڽ�Ȧ֮�У���ʹ���У���Ȧ������
������ͷ��������Ծ�����������Ҫ���Ѿ�������������֮�¡����ַ�������������������
����ƽ��δ������㻮Ȧ�ƵеĽ������޲���Ϊ���졣
*/
#include <ansi.h>
inherit F_DBASE;
inherit F_SSERVER;
#include <combat_msg.h>
void remove_jianquan(object me);

int perform(object me, object target)
{
		int i,skill;
 		object *inv;
		object weapon,weapon2;
		string msg;
		weapon = me->query_temp("weapon");  
			
		skill=me->query_skill("jindao-heijian",1);
        
		if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��Ȧ��նԷ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if (!me->query_temp("jdhj/nizhuan"))
		{
			return notify_fail("�𵶺ڽ�ȫƾһ������������ת�𵶺ڽ�����ת����ʽ��\n");
		}

        if( me->query_dex() < 60 )
                return notify_fail("�������������������㣬����ʹ�ý�Ȧ��նԷ���\n");
        
        if( me->query_skill("dodge",1) < 400 )
                return notify_fail("��Ȧ��նԷ���Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword",1) < 400 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ�ý�Ȧ��նԷ���\n");
        if( me->query_skill("jindao-heijian",1) < 450 )
                return notify_fail("��𵶺ڽ�δ��¯����֮����������ʹ�ý�Ȧ��նԷ���\n");

		if( me->query_skill("blade",1) < 400 )
                return notify_fail("�㵶��δ��¯����֮����������ʹ�ý�Ȧ��նԷ���\n");

       if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ�ý�Ȧ��նԷ���\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ�ý�Ȧ��նԷ���\n");

        if (!weapon)
                return notify_fail("�������޽�����ʹ�ý�Ȧ��նԷ�����\n");
        if (target->is_busy())
                return notify_fail("�Է����Թ˲�Ͼ����Էŵ�������\n");
        //�͵����г�ͻ
	//	if (me->query_temp("jdhj/daoluanren"))
               // return notify_fail("������ʹ�����������з��޷����ý�Ȧ��նԷ���\n");

        if ( me->query_skill_mapped("sword") != "jindao-heijian"
          || me->query_skill_mapped("parry") != "jindao-heijian"
          || me->query_skill_mapped("blade") != "jindao-heijian"
          && userp(me))
             	return notify_fail("������Ƚ��ڽ����໥��ϡ�\n");
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
		if (weapon->query("skill_type") == "blade") {
        	   if( inv[i]->query("skill_type") == "sword" ) 
		   {
			   weapon2 = inv[i];
			   i = 3;
			   break;
		   }
		}
		if (weapon->query("skill_type") == "sword") {
   	        if( inv[i]->query("skill_type") == "blade" ) 
		   {
			   weapon2 = inv[i];
			   i = 2;
			   break;
		   }
		}
       }
	if (!objectp(weapon2)) return notify_fail("��ֻ��һ�ֱ������뽣Ȧ��նԷ���\n");
 	if (i>2) weapon=weapon2; 
		
		message_vision(HIM"$N�е�������������"+weapon->name()+HIM"���������ش�ȥ�����ǽ��Ⲣ��ֱ����ȴ����$n��ǰ��תȦ�ӡ�\n\n"+
		HIW"$n��֪��"+weapon->name()+HIW"Ҫ����η�����֮�£������Ծ��\n"+
		HIM"$N���ֿ켫��$n��Ծ�˱ܣ�"+weapon->name()+HIM"���ɵ�ԲȦ����ָ��$n��ǰ����ȦԽ��Խ��\n"+
		"��ʱ��ֻ����$nǰ��תȦ������һ��������$nС��Ҳ���ڽ�Ȧ֮�У���ʹ���У���Ȧ��������$n��ͷ����\n"+
		HIR"$n�Ծ�����������Ҫ���Ѿ�������������֮�¡�\n"NOR,me,target);

	//�������
	/*
	if(random(me->query_skill("sword",1)> target->query_skill("parry",1)/2
		||random( me->query_skill("force",1)) >target->query_skill("force",1))/2)
	    ||target->is_busy())
	{
		damage = me->query_skill("jindao-heijian",1);
		damage += me->query_skill("sword",1);
		damage += random(damage);
		target->add_busy(damage/300);
    	target->add_temp("lost_attack", damage/100);
        target->apply_condition("no_perform", damage/1000);
        target->apply_condition("no_exert", damage/1000);
		target->add("neili",-(500+random(150)));
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		msg = damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "С��");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		damage=600;
		me->add_busy(1);
	}*/
        me->add("neili", -500);
        me->add("jingli", -500);
		//me->start_perform(damage/300,"��Ȧ��նԷ�");
		me->set_temp("jdhj/jianquan",1);
		call_out("remove_jianquan",skill/60,me);
        return 1;
}

void remove_jianquan(object me)
{
	if (!me) return;
	me->delete_temp("jdhj/jianquan");
	message_vision(HIM"$N�����չ���������Ľ�Ȧ����£��\n"NOR,me);
	return;
}
string perform_name(){ return HBYEL+HIW"��Ȧ"NOR; }

int help(object me)
{
        write(HIC"\n�𵶺ڽ�"+HBYEL"����Ȧ��"NOR"\n");
        write(@HELP
	�𵶺ڽ������˹ȹ����ƵļҴ��书�����ֽ����ֺڽ�
	������������֮�������ڽ��˴�����֮Ч�������Ը�
	��Ϊ�����ڽ�������Ϊ����������Ϻ�����˷���ʤ����
	������������ǧ�߼޸������ƺ󣬶������书ȥ���澫��
	�����ơ����ﵽ¯����֮�����������似��ȱ��Ҳ����
	Ȼ��������ǧ�����ԡ��������ơ�����������ȱ�㡣
	���Ƶ��ӿ���ƾ����ݽ����ǧ�߲������ǧ�ߵ�ָ�㣬
	����Ź��򽫸��ϲ�¥��
	��Ȧ�ǽ��������Է��Ӽ��£��γ�һ����Ȧ�����Է�Ȧ��
	�ڣ��öԷ��������㣬Ȼ��һ��������һ��ʩչ���У���
	���ڽ��Ĺ���������ΪϬ����
		
	ָ�perform sword(blade).jianquan

Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�𵶺ڽ��ȼ� 400 ���ϣ�
	�����Ṧ�ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�	
	�������ȼ� 60 ���ϣ�	
	��������Ϊ�𵶺ڽ���
	��������Ϊ�𵶺ڽ���
	�����м�Ϊ�𵶺ڽ���
	�����ڹ����ޣ�
	�ֳֵ�(��)�����������ϴ���Ӧ����������

HELP
        );
        return 1;
}

