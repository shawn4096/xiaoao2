//jindao-heijian ������ת
//by fqyy 2003.5.9
/*
���óɽ𵶺ڽ�������ʽ�����ǵ������ǽ���ȫƾһ��������
��ǧ�����ԡ�
*/
//by sohu@xojh
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
void remove_po(object me);
void remove_nizhuan(object me,int count,object weapon,object weapon2);

int perform(object me, object target)
{
	int i,skill;
	object *inv;
	object weapon2;
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ת��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        
        if( me->query_skill("dodge") < 100 )
                return notify_fail("��ת����Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword") < 100 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ����ת����\n");
        if( me->query_skill("blade") < 100 )
                return notify_fail("�㵶��δ��¯����֮����������ʹ����ת����\n");
        if( me->query_skill("jindao-heijian",1) < 100 )
                return notify_fail("��𵶺ڽ��ȼ�������������ʹ�ý�Ȧ��նԷ���\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ����ת����\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ����ת����\n");

        if (!weapon)
                return notify_fail("�������޽�����ʹ����ת������\n");
        if (me->query_temp("jdhj/nizhuan"))
                return notify_fail("������ʹ����ת���޷�����ת����\n");
        if (me->query_temp("jdhj/ponizhuan"))
                return notify_fail("��Ľ𵶺ڽ��������޷�ʹ����ת������\n");

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
		if (!objectp(weapon2)) return notify_fail("��ֻ��һ�ֱ���������ת����\n");
		
		message_vision(MAG"\n$N��Ȼ�䳤��һ����������ס������Ѩ�����ҹ����ҽ������ʹ����ƽ����ѧ"HIW"����ת����"HIC"����\n" NOR, me);
		message_vision(YEL"\n$N�͵����ҹ����ҽ������ʹ����ƽ����ѧ"HIW"�����������з���"HIC"����\n"+
					"�����������ᣬ��ʱͻȻӲ��������������յĵ����������صĵ���ȴ������ϴ��\n"+
					"ȫ�ߵ���������·�ӣ����ɽ������䵶������������޷���\n\n" NOR, me);
		
		if (!me->query("quest/tz/jdhj/pass")
			&&target->query("quest/tz/jdhj/pass")
			&&random(target->query_int())>me->query_int()/2)
		{
			message_vision(HIC"$n�Ѿ�������ǧ�ߵ��洫�����ڽ𵶺ڽ�����ʽ����ָ�ƣ����ٸо��κ�����!\n"	
				+"ֻ��$n�����һЦ�������������ǵ������ǽ�����������������������������$N�Ľ𵶺ڽ�����ʽ��\n",me,target);
			me->add_temp("apply/parry", -skill/5);
			me->add_temp("apply/sword", -skill/5 );
			me->add_temp("apply/blade", -skill/5 );
			me->set_temp("jdhj/ponizhuan",skill);
			call_out("remove_po",skill/50,me);
			return 1;
		}

        skill = me->query_skill("jindao-heijian", 1);
        me->add_temp("apply/parry", skill/5 );
        me->add_temp("apply/sword", skill/5 );
        me->add_temp("apply/blade", skill/5 );

        me->set_temp("jdhj/nizhuan",skill);
		remove_nizhuan(me,skill/50,weapon,weapon2);

		me->add("neili", -200);
        me->add("jingli", -100);
        return 1;
}

void remove_nizhuan(object me,int count,object weapon,object weapon2)
{
        int skill;
		
		if ( !me||!me->query_temp("jdhj/nizhuan") ) return;
		skill=me->query_temp("jdhj/nizhuan");
	    if (count<0
			||!me->is_fighting()
			||me->query_skill_mapped("sword")!="jindao-heijian"
			||me->query_skill_mapped("blade")!="jindao-heijian"
			||me->query_skill_mapped("parry")!="jindao-heijian"
			||!me->query_temp("weapon")
			||!objectp(weapon2)
			||weapon != me->query_temp("weapon"))			
	    {
			me->add_temp("apply/parry", -skill/5);
			me->add_temp("apply/sword", -skill/5 );
			me->add_temp("apply/blade", -skill/5 );
			me->delete_temp("jdhj/nizhuan");
			message_vision(HIC"\n$N֪���Լ��⵶��������ת���������󣬲��Ҷ��ã������ջ��˹��ơ�\n\n" NOR, me);
			return;
	    }
		call_out("remove_nizhuan",1,me,count--,weapon,weapon2);
}
void remove_po(object me)
{
        int skill;
		if ( !me) return;
		skill=me->query_temp("jdhj/ponizhuan");
	    me->add_temp("apply/parry", skill/5);
		me->add_temp("apply/sword", skill/5 );
        me->add_temp("apply/blade", skill/5 );

        me->delete_temp("jdhj/ponizhuan");
        message_vision(MAG"\n$N���Է���ȥ�Ľ𵶺ڽ�����ʽ���𽥻ָ���\n\n" NOR, me);
        return;
}

string perform_name(){ return HBMAG+HIW"��ת��"NOR; }

int help(object me)
{
        write(HIC"\n�𵶺ڽ�"+HBYEL"����ת����"NOR"\n");
        write(@HELP
	�𵶺ڽ������˹ȹ����ƵļҴ��书�����ֽ����ֺڽ�
	������������֮�������ڽ��˴�����֮Ч�������Ը�
	��Ϊ�����ڽ�������Ϊ����������Ϻ�����˷���ʤ����
	������������ǧ�߼޸������ƺ󣬶������书ȥ���澫��
	�����ơ����ﵽ¯����֮�����������似��ȱ��Ҳ����
	Ȼ��������ǧ�����ԡ��������ơ�����������ȱ�㡣
	���Ƶ��ӿ���ƾ����ݽ����ǧ�߲������ǧ�ߵ�ָ�㣬
	����Ź��򽫸��ϲ�¥��
	��ת���������𵶺ڽ�������ʽ��Ҳ����ת���ķ�����
	�����н𵶺ڽ��Ļ�����һ�����б��ƣ����еĺ�����ʽ
	���������������������������ء�
		
	ָ�perform sword(blade).nizhuan

Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�𵶺ڽ��ȼ� 100 ���ϣ�
	�����Ṧ�ȼ� 100 ���ϣ�
	���������ȼ� 100 ���ϣ�
	���������ȼ� 100 ���ϣ�	
	��������Ϊ�𵶺ڽ���
	��������Ϊ�𵶺ڽ���
	�����м�Ϊ�𵶺ڽ���
	�����ڹ����ޣ�
	�ֳֵ�(��)�����������ϴ���Ӧ����������

HELP
        );
        return 1;
}

