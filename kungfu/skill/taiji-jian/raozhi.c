// 2005.7.4 by Lane@SJ

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
"ӿȪѨ","��׶Ѩ","�縮Ѩ",
}); 
int perform(object me, object target)
{
	string msg, dodge_skill;
	object weapon;
	int ap, dp,i,skill;
    
	if( !target ) target = offensive_target(me);

	if( !me->query("raozhi") )
		return notify_fail("��δ�ô��ڡ���ָ�ὣ����\n");

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !living(target) )
		return notify_fail("����ָ�ὣ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	//if( me->query_temp("tjj/lian") )
		//return notify_fail("������ʹ�á������־���\n");

	//if( me->query_temp("tjj/chan") )
		//return notify_fail("������ʹ�á������־���\n");

	if( (int)me->query_skill("taiji-jian", 1) < 200 )
		return notify_fail("���̫����������̫ǳ�ˡ�\n");

	if( (int)me->query_skill("sword", 1) < 200 )
		return notify_fail("��Ļ�����������̫ǳ�ˡ�\n");

	if( (int)me->query_skill("yinyun-ziqi", 1) < 200 )
		return notify_fail("����ڹ�����̫ǳ�ˡ�\n");

	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("�������̫ǳ�ˡ�\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("�������������\n");

	if( me->query_skill_mapped("force") != "yinyun-ziqi" )
		return notify_fail("����ʲôΪ�ڹ�������ʹ����ָ�ὣ����\n");
	if( me->query_temp("tjj/raozhi") )
		return notify_fail("������ʹ�á���ָ�ὣ��\n");
	if( target->query_temp("tjj/raozhi") )
		return notify_fail("�Է��Ѿ�Ϊ�㡸��ָ�ὣ�����ơ�\n");
	if( !objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "taiji-jian"
	 || me->query_skill_mapped("parry") != "taiji-jian" )
		return notify_fail("��ʹ���ˡ���ָ�ὣ��ô?\n");
	
	//if( target->is_busy() )
		//return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
	//For npc Chan+Raozhi ��å����
      
	ap = me->query("combat_exp")/100000;
	dp = target->query("combat_exp")/100000;
	//550������������
	if( me->query_skill("taiji-jian", 1) > 549 )
	{
		ap += random(ap/2);
       // me->set_temp("apply/armor",me->query("yinyun-ziqi",1)/3);
	}	      

	message_vision(HIY"\n$Nʩչ��̫�������е���ָ�ὣ������"+weapon->query("name")+HIY"������һ�����ߣ��������磬������\n"NOR,me,target);
	
	skill=(int)me->query_skill("taiji-jian",1);
	
	if (me->query("quest/wd/yyzq/taiji/pass"))
	{
		skill=skill+me->query_skill("yinyun-ziqi",1)/2;
	}
	
	if ( random( ap + dp ) > dp 
		||random(me->query_dex())>target->query_dex()/2) {
		message_vision(HIC"\n$n���ɸе����£�ֻ�о�ǰ�����Ҷ�����$N������һ���Ӳ�֪������Ǻã�\n"NOR,me,target);		
		
		if (userp(target)) target->add_busy(2);
		else target->add_busy(5);
		
		if( target->query_temp("lost_attack") < 1 )
			target->add_temp("lost_attack", 1+random(3));
		me->add("neili", -300);
		me->add("jingli", -100);
		//���ͶԷ�����
		me->set_temp("tjj/raozhi",skill);

		target->add_temp("apply/dodge",-skill/4);
		target->add_temp("apply/attack",-skill/4);
		target->add_temp("apply/parry",-skill/4);
		
		target->set_temp("tjj/raozhi",skill);
		call_out("rz_back",skill/40,target);

	//350�����ӷ���
		if( me->query_skill("taiji-jian", 1) > 349 )
                me->add_temp("apply/parry",me->query("yinyun-ziqi",1)/3);
	//450�������Ṧ
		if( me->query_skill("taiji-jian", 1) > 449 )
                me->add_temp("apply/dodge",me->query("yinyun-ziqi",1)/3);
	//550 ����������

		
		//if (objectp(target) && me->is_fighting())
		call_out("raozhi_effect",1,me,target,(int)skill/20);

		if (me->query_skill("taiji-jian",1)< 550)
				me->start_perform(2, "����ָ�ὣ��");
	}
	else {
		//dodge_skill = target->query_skill_mapped("dodge");
		//if( !dodge_skill ) dodge_skill = "dodge";
		//msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		message_vision(HIC"$n����һ�ݣ����˿�ȥ��$Nһ��ʧ�֣���ʱ��Щæ�ҡ�\n"NOR, me, target);
		me->add("neili", -100);
		me->add("jingli", -50);
		me->start_busy(1);
		me->start_perform(2+random(2), "����ָ�ὣ��");
	}	
	return 1;
}
int rz_back(object target)
{
	int skill;
	if (!target) return 0;
	if (target->query_temp("tjj/raozhi"))
	{
		skill=target->query_temp("tjj/raozhi");
		tell_object(target, HIW"���𽥻ָ������С���ָ�ὣ��������������״̬��\n"NOR);
				//tell_object(me,WHT+target->query("name")+WHT"�𽥻ָ�����������ʩչ����ָ�ὣ���������ĸ���״̬��\n"NOR);
		target->add_temp("apply/attack", skill/4);
		target->add_temp("apply/dodge", skill/4);
		target->add_temp("apply/parry", skill/4);
		target->delete_temp("tjj/raozhi");
		return 1;
		
	}

}

int raozhi_effect(object me,object target,int count)
{

        object weapon;
		int skill;
		string xname;
	    
		//name=xue_name[random(sizeof(xue_name))];
		xname = xue_name[random(sizeof(xue_name))];
		//�����������������������
		//1��������������ˣ������������ˣ��ָ����������ĸ���Ч��,���ܹ���������
	
	//if (!objectp(target)) return 0;
		//������̫�������ý��˳�			
		if (!me) return 1;
		
		weapon=me->query_temp("weapon");

		if (!objectp(target)
			|| !me->is_fighting()
			|| me->query_skill_mapped("sword")!="taiji-jian"
			|| me->query_skill_mapped("parry")!="taiji-jian"
			|| !weapon
			|| !me->query_temp("tjj/raozhi")
			|| count-- < 0
			|| weapon->query("skill_type")!="sword")
		{				
			//350�������ӷ���
			if( me->query_skill("taiji-jian", 1) > 349 )
                me->add_temp("apply/parry",-me->query("yinyun-ziqi",1)/3);
			//450�������Ṧ
			if( me->query_skill("taiji-jian", 1) > 449 )
                me->add_temp("apply/dodge",-me->query("yinyun-ziqi",1)/3);
			
			me->delete_temp("tjj/raozhi");
			if (objectp(weapon))
				message_vision(HIY"$N�����е�"+weapon->query("name")+HIY"��������������뽣��֮�У���ָ�ὣ�����չ���\n"NOR,me);	
			else message_vision(HIY"$N��������������ͷţ���ָ�ὣ�����չ���\n"NOR,me);	
			return 1;
		}
		//��ָ�����⹥�� 
        //��ָ�����ĸ�������
		if (!random(3))
		{	
				switch (random(3))
				{
					case 0:
						if (objectp(target) && target->query_temp("tjj/raozhi"))
						{	
							message_vision(HIY"$N�����Ĺ������뵽�����У���ָ�ὣԽ��Խ�����Ѳ⣬$nһ��С��Ϊ$N������"+HIR+xname+HIY"!\n"NOR,me,target);
							target->receive_damage("qi",100+random(1000),me);
						}
						break;
					case 1:
						if (objectp(target) && target->query_temp("tjj/raozhi"))
						{
							message_vision(RED"$N���н��ⶶ������ָ�ὣ��ŷ�����$n��������������繭�����⾹˲�����$n��"+HIG+xname+RED"!\n"NOR,me,target);
							target->receive_damage("jingli",100+random(500),me);
							target->apply_condition("neishang",1);
						}
						break;
					case 2:
						if (objectp(target) && target->query_temp("tjj/raozhi"))
						{
							message_vision(MAG"$N��������ת���ݣ�������죬����һ�����߰�Ĵ�����$n�ı۰�˳���Խ�������$n��"+HIR+xname+MAG"!\n"NOR,me,target);
							target->receive_wound("qi",100+random(500),me);
							target->apply_condition("no_exert",1);
						}
						break;
				}							
                 target->add_busy(1);						
			}
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);                        
			if (objectp(target)&&me->is_fighting())
				call_out("raozhi_effect", 2, me, target, count);  
			else call_out("remove_effect",1,me);
            
			return 1;
	  
}

int remove_effect(object me)
{
	

	object weapon;
	if (!me) return 0;
	weapon=me->query_temp("weapon");
	if( me->query_skill("taiji-jian", 1) > 349 )
                me->add_temp("apply/parry",me->query("yinyun-ziqi",1)/3);
	//450�������Ṧ
    if( me->query_skill("taiji-jian", 1) > 449 )
                me->add_temp("apply/dodge",me->query("yinyun-ziqi",1)/3);
	//550 ����������
	me->delete_temp("tjj/raozhi");
	message_vision(HIY"$N�����е�"+weapon->query("name")+HIY"���뽣���У���ָ�ὣ�����չ���\n"NOR,me);	
    
	
	return 1;

}

string perform_name(){ return MAG"��ָ�ὣ"NOR; }

int help(object me)
{
        write(MAG"\n̫������֮����ָ�ὣ����"NOR"\n\n");
        write(@HELP
	��ָ�ὣ���䵱������Ī���������������ǽ�����ڹ�
	���뵽���У���ʹ�����Σ��Ӷ���ɶԷ������У��ﵽ
	��Чɱ�˶Է���Ŀ�ġ����书��Ҫ��Ī������̡�
	
	perform sword.raozhi

Ҫ��  
	��ǰ����Ҫ�� 1000 ����;
	�������Ҫ�� 3000 ���ϣ�
	̫�������ȼ� 200 ���ϣ�
	�������ȼ� 200 ���ϣ�
	���������ȼ� 200 ���ϣ�
	��������Ϊ̫��������
	�����м�Ϊ̫��������
	�����ڹ�Ϊ��������
	��õ����ڡ���ָ�ὣ����

HELP
        );
        return 1;
}
