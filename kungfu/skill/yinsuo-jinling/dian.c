// dian.c �������� ��Ѩ
// keinxin@sj2 2003.4
// edit by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;

string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
"ӿȪѨ","��׶Ѩ","�縮Ѩ",
}); 
int perform(object me, object target)
{
	object weapon;
	object ob;		
	string msg,xue;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("����Ѩ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "whip")
			return notify_fail("��ʹ�õ��������ԡ�\n");

	if( (int)me->query_skill("yinsuo-jinling", 1) < 300 )
		return notify_fail("����������岻�����죬��������Ѩ\n");
	if( (int)me->query_skill("whip", 1) < 300 )
		return notify_fail("��Ļ����޷��������죬��������Ѩ\n");
	if( (int)me->query_skill("yunu-xinjing",1)< 300)
		return notify_fail("����ڹ���Ϊ̫������޷����Ѩ��\n");
	
	if( (int)me->query("max_neili")<5000)
		return notify_fail("����������������ʩչ��Ѩ����.\n");
	if(target->is_busy())
		return notify_fail("�Է��Ѿ�����æ��֮�У��ŵ�������.\n");
			
	if ( (int)me->query("neili") < 1500 )
		return notify_fail("��ĵ�ǰ����������Ѩ��\n");
	
	me->add("neili", - 300);
	xue = xue_name[random(sizeof(xue_name))];

	msg = HIW"$N"HIW"����"+weapon->query("name")+HIW"�ɳ�,ʹ�������������,ʸ��������ֱȡ$p"HIW"��"+HIR+xue+NOR"��\n";
	ob = target->query_temp("weapon");
	
	if( random( me->query_skill("force",1) ) > target->query_skill("force",1)/2
		||random(me->query_dex(1))> target->query_dex(1)/2)
	{
		if (me->query("yueyin")
			&&me->query("env/��������")=="����"
			&&me->query_skill("yinsuo-jinling",1)>350
			&&me->query_temp("weapon")
			)
			call_out("yueyin_attack",1,me,target,(int)me->query_skill("yinsuo-jinling",1)/40);
		//�Է�����

		if (!objectp(ob))
		{
			int damage = 0;
			if (target->query_skill("dodge",1) > 300 && !random(2))
			{
				switch (random(2)){
				case 0:
					msg += HIR "$p�������˼����ϳ���������û�ܶ����"
						"$N�Ľ���������$p��̴��Ѩ�ϣ�$pֻ����һ��"
						"�������Ե�����ϣ���������˵���������ܡ�\n"NOR;
					damage = 3;
					break;
				case 1:
					msg += HIR "$p����Ʈ�������鶯֮����������Ҫ�Ȳʣ�"
              					"�����ۡ���һ��������ܸ$p��ɫɷ�ף�ҡҡ��׹��\n"NOR;
					damage = 5;
					break;
				}
			} 
			else if (target->query_skill("force",1) > 300 && random(2) == 0)
			{
				switch(random(2))
				{
				case 0:
					msg += HIR "$p���һ�����Գ�������ǿ�����ֳ��У���࣡�"
						"��һ�����죬�����ཻ��$p����΢�Σ������ֽ��\n"NOR;
					damage = 3;
					break;
				case 1:
					msg += HIR "$pһ����Х��˫�ֻû���������Ӱ����ס��ǰ��"
						"ֻ�����͡���һ������Ӱ������$p�Ѿ������ɫ�Ұס�\n"NOR;
					damage = 4;
					break;
				}
			}
			else
			{
				switch(random(2))
				{
					case 0:
						msg += HIR "$p�������У���Ȼ��֪��ܣ����͡���һ����$N"
						"�Ľ���������$p�Ĵ�׵Ѩ��,$pȫ������,�����ڵء�\n"NOR;
						target->receive_damage("qi", target->query("qi")/2,me);
						target->receive_wound("qi", target->query("qi")/3,me);
						target->add_busy(1);
						damage = 0;
						break;
					case 1:
						msg += HIR "$pһת��Ѿ�����˾�ʮ���ֻ���İ취��"
						"��δ���ü�ʩչ��ֻ�����͡���һ�����ѱ�$N����ӡ��Ѩ,$p��ʱ��ð���ǣ����������ʧ��\n"NOR;
						target->receive_damage("jing", target->query("jing")/2,me);
						target->receive_wound("jing", target->query("jing")/3,me);
						target->add_busy(1);
						damage = 0;
					break;
				}
			}
			if (damage > 0) 
			{
				target->receive_damage("qi", target->query("qi")/3,me);
                target->receive_wound("qi", target->query("qi")/5,me);
			}
			if (damage > 2) 
			{
				target->receive_damage("jing", target->query("jing")/2,me);
				 message_vision(HIB"$N����һ�������춯���������ǣ������ʱʧ�أ���ǰ������ð!\n"NOR,me);
               // target->receive_wound("jing", target->query("qi")/5,me);
			}

			//���жԷ���ǣ����Ӷ�̻����������Ӵ�
			target->set_temp("ysjl/dian",1);
			message_vision(msg, me, target);
			//����æ����
			if (userp(target))
				target->add_busy(1);
			else target->add_busy(3);
			
			return 1;
		}

//�����������Ǳ�����
	 if (ob && ob->query("imbued") < 3 && ob->query("sharpness") > 0 && !random(3)&& me->query("env/��������")=="����")
     {
				msg += HIW "$p��æ�мܣ�ֻ������ž����һ����$p���е�" + ob->name()
				+ "�����ѣ�ɢ��һ�أ�\n";
				ob->unequip();
				ob->move(environment(target));
				ob->set("name", "�ϵ���" + ob->query("name"));
				ob->set("value", 0);
				ob->set("weapon_prop", 0);
           
	  }
	  target->add_busy(2);
//��û����
	} else
	  {
		int busy = 0;
		if (target->query_skill("dodge") > 200 && random(2) == 0)
		{
			switch (random(2))
			{
			case 0:
				msg += "$pһ����Ц�������仯�˼����������˶�Ŀ��һʱ��$N�޷�������\n";
				busy = 2;
				break;
			case 1:
				msg += "$pͻȻ���Ʈȥ���������磬��$N���еĺ�̱仯�޴�ʩչ��\n";
				busy = 1;
				break;
			}
		} else
		if (target->query_skill("force") > 200 && random(2) == 0)
		{
			switch (random(2))
			{
			case 0:
				msg += "$p��ɫ���أ��ӿ��ܣ����ɶ��ɣ���$N�޴����֣�ֻ���ջؽ��塣\n";
				busy = 3;
				break;
			case 1:
				msg += "$p������м����Цһ����˫�����������ޱȣ���$Nֻ�ܻ����Ծȡ�\n";
				busy = 1;
				break;
			}
		} else
		{
			switch (random(3))
			{
			case 0:
				msg += "$p��ҡ�һΣ�����ȥ�����·���ƫƫ�����$N��һ����\n";
				busy = 2;
				break;
			case 1:
				msg += "$p������������ȥ�鶯���$Nһ�������ƶٻ���\n";
				busy = 2;
				break;
			case 2:
                if (ob)
                {
				   msg += "$p��ס����������ע" + ob->query("name")
					 + "��������ס��$N�Ľ�����\n";
                 }
				busy = 2;
				break;
			}
		}
		target->start_busy(busy);
		//me->start_busy(2);
	}
	message_vision(msg + NOR, me, target);

	return 1;
}

int yueyin_attack(object me,object target,int num)
{
	object weapon;
	int damage;
	if (!me||!target || !me->query_temp("weapon")) return 0;

	weapon=me->query_temp("weapon");
	damage=me->query_skill("yinsuo-jinling",1)+me->query_skill("yunu-xinjing",1)+me->query_skill("whip",1);
	damage=damage+random(damage);
	
	if (!me->is_fighting()
		||num<0)
	{
		message_vision(WHT"$N����һ��������жȥ�������������չ���\n"NOR,me);
		return 1;
	}
	message_vision(BLU"$N������"+weapon->query("name")+BLU"˦�����������ֱ۵İڶ������У���ͷ�����������н�������ɡ�\n"NOR,me,target);
	
	switch (random(3))
	{
		case 0:
			target->receive_damage("qi",damage/2,me);
			break;
		case 1:
			target->receive_damage("jing",damage/4,me);
			break;
		case 2:
			target->receive_damage("qi",damage/2,me);
			target->receive_damage("jing",damage/4,me);
			target->add_busy(1);
			break;
		
	}
	num=num-1;
	if (me->query_temp("weapon")) call_out("yueyin_attack",1,me,target,num);
	return 1;
}

string perform_name(){ return HIC"��Ѩ"NOR; }
int help(object me)
{
        write(WHT"\n��������֮"HIC"����Ѩ����"NOR"\n");
        write(@HELP
	�����������ǹ�Ĺ�����似��Դ��С��Ů��ս
	���ַ�����������λӢ�ۺ���ʱ���似������
	���ǲ�����ɽ���˿���죬��Ϊ���ͣ�������
	�ޱȣ�ǰ��Ϊһ��ɫ���������и��ŶԷ�ʩչ
	�����似�Ĺ��ܡ�������������С��Ůָ���
	����ʹ�ã�����Ĺ�����������뵽�����У���
	�����˵Ľ��ᣬ����һ�������������ŶԷ���
	����������Ư����Ů�ԣ��Ա��似��Ӧ�ø���
	�������������书�ж���ò������Ů��ʹ��
	�����ơ�
	��Ѩ�������������������˵�����������Ӳ
	��������Է�Ѩ���ľ�����
	ע�⣺����ͨ����ͬ���������ﵽ��ͬЧ����
	
	set �������� ����
		��Ч���з��б�Ѩ�ص����и��ʴ���Է�
		�����Ĺ�Ч�����⿪������������������
		��������Ϯ�ŶԷ���
	set �������� �����
		��Ч�����öԷ�������빦Ч
	set �������� ��������			
		��Ч�����öԷ��б��Ƕ���Ч
	
	perform whip.dian
	
Ҫ��
	�������Ҫ�� 5000 ���ϣ�      
	��ǰ����Ҫ�� 1500 ���ϣ�
	��Ů�ľ��ȼ� 300 ���ϣ�
	��������ȼ� 300 ���ϣ�
	��Ů���ȼ� 300 ���ϣ�
	���������޷�Ϊ�������壻
	�����м�Ϊ�������壻
	�����ڹ�Ϊ��Ů�ľ���
	�ֱֳ��������
                
                
HELP
        );
        return 1;
}
