// yinsuo-jinling.c ��������
// By River
#include <ansi.h>
inherit SKILL;

string  *msg = ({
"$N�����������$w����˦�˳�����ֱ��$n��$l��������Ϣ�����Ⱦ�û�������",
"$N�ֳ�$w��ʸ�����߻���$n���ټ���ö���򲻶Ϸ�������֮����������������",
"$n�����ý����з����������죬���䲻��ȴ��ʮ�ֹ��죬�������ҡ�ǡ�",
"$N����һ�䣬ת��һ��$w��$n��֮�£�����������$w�������缱�Ӷ���",
"$N����΢����$w������ȥ�����¶��ϣ�����$n����$l���ġ��Ϲ�Ѩ��",
"$N��������$w����ˮ�߰����Ѷ������������죬$n�����ϵġ����Ѩ������$w����",
"$N΢΢һЦ��ǰһ��������$wһ����$w��ز���裬�ñȲʷﳯ��һ�����$n",
});

int valid_enable(string usage)
{ 
	return usage == "whip" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
	//�������������һ��
	if(me->query_temp("sanwu/buwei")){
		if((int)me->query_skill("yinsuo-jinling",1)>549)
			return ([
                "action":HIW +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIW)+NOR,
                "damage":       150 + random(100),
                "damage_type":  "����",
                "dodge":        10+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
		
		else if((int)me->query_skill("yinsuo-jinling",1)>450)
	        return ([
                "action":HIR +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIR)+NOR,
                "damage":       120 + random(100),
                "damage_type":  "����",
                "dodge":        20+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
     }
     //���־�
	 if(me->query_temp("juan") && (int)me->query_skill("yinsuo-jinling",1)>=350)
        return ([
                "action":HIG +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIG)+NOR,
                "damage":       120 + random(150),
                "damage_type":  "����",
                "dodge":        10+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
	 //��ͨ��ʽ
	 return ([
		"action":	msg[random(sizeof(msg))],
		"damage":	60 + random(100),
		"damage_type":	"����",
		"dodge":	random(30),
		"force":	random(300) + 150,
		"parry":	random(30),
     ]);
}

int valid_learn(object me)
{
	object weapon;
	if( (int)me->query("max_neili") < 500 )
		return notify_fail("����������㣬û�а취����������, ����Щ���������ɡ�\n");
	if ((int)me->query_skill("yunu-xinjing", 1) < 100)
		return notify_fail("�����Ů�ľ��ڹ����̫ǳ��\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	 || ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("��ʹ�õ��������ԡ�\n");
	return 1;
}
 
int practice_skill(object me)
{
	if ( me->query("jingli") < 40)
		return notify_fail("��������������������塣\n");
	if ( me->query("neili") < 20)
		return notify_fail("��������������������塣\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	object weap,weap1,ob;
	int ap, dp,damage,i;
	string msg;
	weap = victim->query_temp("weapon");
	
	if (!me->query_temp("weapon"))
	{
		return;
	}

	weap1 = me->query_temp("weapon");
	damage=me->query_skill("yinsuo-jinling",1)+me->query_skill("throwing",1);
	if (objectp(present("yufeng zhen", me)))
	   ob=present("yufeng zhen", me);
//�������
	if(me->query("env/��������")=="����" 
	 && me->query_skill("yinsuo-jinling", 1) > 450
	 && me->query("neili") > 700
	 && victim->query_temp("weapon")
	 && random(me->query_skill("yinsuo-jinling",1)) > victim->query_skill("dodge", 1)/2 
	 && random(10) > 7) 
	{
		
		message_vision(CYN"ֻ��$N���ٻ���"+ weap1->query("name") + CYN"��ת����������СȦ�ӣ�������֮����ס�Է���" + weap->query("name") +CYN"��\n" NOR, me );
		message_vision(weap->query("name")+HIC"��˵�������Ȼ����𣬵���$n�ĺϹ�Ѩ��$n��ʱ����һ�飡\n"NOR,me,victim);
		victim->add_busy(1);
		ap = me->query("combat_exp", 1) /10000 * me->query_dex(1);
		dp = victim->query("combat_exp", 1) /10000 * victim->query_dex(1);
		if (random(ap + dp ) > dp ) {
			message_vision(HIY"$N�����ֱ�����һק��"+ weap->query("name")+ HIY"ȴ�޷���"+weap1->query("name")+HIY"�Ĳ������ѿ����鼱֮��ֻ�÷��������еı��С�\n" NOR, victim );
			weap->move(environment(me));
			victim->reset_action();
		}
		else {
			message_vision(YEL"$N�����ɾ���"+ weap->query("name")+YEL"˳�ŷ��������ת���£��⿪��"+weap1->query("name")+YEL"�Ĳ��ơ�\n" NOR, victim );
			victim->add("neili", -500);
		}		

		me->add("neili", -(200+random(100)));
	}
	else if (me->query("env/��������")=="����" 
	 && me->query_skill("yinsuo-jinling", 1) > 450
	 && me->query("neili") > 700
	 && random(10) > 7
	 && !victim->query_temp("weapon"))
	{
		message_vision(HIR"ֻ��$N����"+ weap1->query("name") + HIR"��ת����������СȦ�ӣ�������֮����ס�Է���������ֱۡ�\n" NOR, me );
		message_vision(HIC"��˵���ϵ������Ȼ���������Ϯ��$n�ĺϹ�Ѩ���ٻ㡢ӡ�����Ѩ��$n��ʱ��Ѫ��ӿ���������ͣ�\n"NOR,me,victim);
		victim->receive_damage("qi",random(1000),me);
		victim->receive_wound("qi",random(500),me);
		victim->add_busy(2);
		victim->add_condition("no_exert",2);

	}
    else if ( me->query("env/��������")=="�����" 
		&& me->query_skill("yinsuo-jinling",1)>450
		&& random(10)>6
		&& objectp(ob))
	{
		message_vision(HIY"$N��$n�����⣬�ӻ����ͳ���ö����룬������"+weap1->query("name")+HIY"�ļ�ˣ���������Ϭ����\n"NOR,me,victim);
		if (random(me->query_skill("whip",1))>victim->query_skill("parry",1)/3)
		{
			message_vision(HIR"$nһʱ���飬Ϊ$N���е�"+weap1->query("name")+HIR"����������������й�ԪѨ��\n"NOR,me,victim);
			victim->apply_condition("bee_poison",5);
			victim->receive_damage("qi",random(800),me);
		}
	}
    else if (me->query("env/��������")=="��������"
		&& random(10)>6 
		&& present("bingpo yinzhen",me))
	{
		message_vision(HIW"$N��$n�����⣬�ӻ����ͳ���ö�������룬������"+weap1->query("name")+HIW"�ļ�ˣ���������Ϭ����\n"NOR,me,victim);
		if (random(me->query_skill("whip",1))>victim->query_skill("parry",1)/3)
		{
			message_vision(HIB"$nһʱ���飬Ϊ$N���е�"+weap1->query("name")+HIB"��������õı���������кϹ�Ѩ��\n"NOR,me,victim);
			victim->apply_condition("bing_poison",5);
			victim->receive_damage("qi",random(1500),me);
		}
	}

	
//���˾������Ծ
    if (me->query("quest/jiuyingm/pass")
		&&objectp(victim)
		&&random(10)>5
		&&me->is_fighting())
    {
  
	 switch (random(3)){
		case 0:
	   case 1:
	 	
	    msg = HIW"\n$N����"+weap1->name()+HIW"Ʈ�����ó�һƬ�����ַ����������죬����������������أ�����������һ�㡣\n"NOR;
        msg +=HIW"��������ѭ������������Ȼ���Ķ���ɣ��ǹ���������֮�ö�����������֮�ķ���\n"NOR;
		if (random(me->query_per(1))>victim->query_per(1)/3 )
		{
		 // i=(int)me->query_skill("yinsuo-jinling",1)/100;
		  msg+=HIC"$n���ɵ�һ���ķ�����ʱ��æ��������,һʱ���飬Ϊ$N��"NOR+weap1->name()+HIC"����������\n"NOR;
		  victim->add_busy(3);
		  victim->receive_damage("jing",500+random(800),me);
		 }
		 else msg+=HIY"$nƽʱ���Ĺ������úܺã������ң�˫���ô򷢳�һ��������ʹ��$N���������Ŷ�ʱʧЧ��\n"NOR;
		 message_vision(msg,me,victim);
		 break;

	 case 2:
		 msg = HIM "\n$N��"NOR+weap1->query("name")+HIM"�����ڿ���ת�䣬ֻ�����������������죬���򼲲����£�\n"+
                  "�ֵ�$n���ϡ�ӭ�㡹�����������������С�����Ѩ����\n";
         //me->start_busy(random(1));
         if((random(me->query("combat_exp")) > victim->query("combat_exp")/3 ) 
            && ((random(me->query_per(1) ) >= victim->query_per(1)/3 )
            || (random(me->query_dex()) >= victim->query_dex()/3) ))
		{
          msg += HIY "���$p��$P���˸����ֲ�����\n" NOR;
          victim->add_busy((int)me->query_skill("yinsuo-jinling")/50);
		  victim->receive_damage("qi",random(1000),me);
          } 
        else {
          msg += HIW "����$p������$P����ͼ������������֮�ʣ����Ա�һ������˹�ȥ��\n" NOR;
          me->start_busy(2);
          }
          message_vision(msg, me, victim);        
        break;
	
	  }
    }
	return ;
}

string perform_action_file(string action)
{
	return __DIR__"yinsuo-jinling/" + action;
}
