// qixian-wuxingjian.c
// modified by action@SJ 2009/1/10
//updated by Zmud@Sjmud 10/3/2009

#include <ansi.h>
#include <skill.h>

inherit SKILL;

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ", "�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ",
"����Ѩ", "����Ѩ", "���Ѩ", "�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", }); 

string  *msg = ({
"$Nʹһ�С�����������������$w����һ�����������һ�����$n��$l",
"$N��ָ��$w��һ����һ�С����������������������ʱ����һ����������Х��ն��$n��$l",
"$Nһ�С����������������$w��â��ʱ�������ߣ��⻪���䣬ֱֱ����$n��$l",
"$N����$wһʽ�����̾�ɲ����׼$n��$lһ���̳�������ɲʱ�����ݺᣬ�Ʋ��ɵ�",
"$N��$wƾ��һָ��һ�С��������项ֱֱ�̳������ⶸȻ����������²�������â����$n��$l",
"$N����$w����һ�֣�ʹһ�С��������ơ��������ڽ������ᵯ������ʱһ�ɽ���ֱӿ$n$l��ȥ",
"$N��Ȼ���о������䣬һ�С��Ǻ���������һ�ɴ����ޱȵĽ�����$w�ϼ��������ֱ��$n",
});

string *feiyue_msg = ({
"$N��Сָ�ᵯ��һ�й�����Ȼ����$n�ĺ��ģ�$w��ס��������$n$l��ȥ",
"$N��������ָ�������޵�һ���������Ҳ���һ���������ѽ�$n����ס�ڽ���֮��",
"$N��ָ���ӣ�һʽ�������εĴ���$n�����ߣ���Ȼ��$Nһ��ת������$n���ߴ�ȥ",
"$N�����н���ɨ��ͬʱ�������������Ƶļ���������һ��֧�ϣ��о������ޱ�",
"$Nʹ�����ϣ������������ߣ���ͬ��������������������$n��$l",
"$N����ɫ���ˣ��˽�һ�ϣ�ʹ�����ϣ�$N�����ֶ���һ�������͵���$n��ȥ",
"$Nʹһ�й��ϣ�����$w����һ�����������һ�����$n��$l����ʽ��ΪƮ��",
"$N��ָ��$w��һ����һ�����ϣ����������ʱ����һ����������Х��ն��$n��$l",
"$Nһ�н��ϣ�����$w��â��ʱ�������ߣ��⻪���䣬ֱֱ����$n��$l��$n��Ȼ�޷����",
"$N����$wһʽ���϶�׼$n��$lһ���̳�������ɲʱ�����ݺᣬ�Ʋ��ɵ�������������",
"$N��$wƾ��һָ��һ��֧��ֱֱ�̳������ⶸȻ����������²�������â����$n��$l",
"$N����$w����һ�֣�ʹһ�����ϣ������ڽ������ᵯ������ʱһ�ɽ���ֱӿ$n$l��ȥ",
"$N��Ȼ���о������䣬һ�й��ϣ�һ�ɴ����ޱȵĽ�����$w�ϼ��������ֱ��$n",
});
string *qianbian_msg = ({
"$N��$w�ڿ�������һ������һ�����϶��£�ֻ�����ƶ������߹⾰��$n�������о�Ȼ����֮������",
"$N��$wб��$n���أ����д������������أ�����һ�й��ؼ汸����������",
"$N��$w��ת��ָ��$n�Ҽ磬�������д������������ص����š�$nһ�ݣ�ֻ�������о��ް������",
"$N��$wֱ�����ţ���ͼ��$nҪ����$nֻ�úὣһ�⣬����бָ��$N��һ�����д���$nС��֮�⣬Ҳ�������й�������",
"$N��ʽ���䣬����ǰ�����ܻ����󿪴�ϣ������쳣������һ�������ɴ�Ħ�����ġ�����������ʽ����������",
"$N�Ľ��к����������ת֮�ƣ��˽���һ��ʹ��̫����������ָ���ƽ�����������˸����$n��ȥ",
"$N����$w����һ�����������һ�����$n��$l����ʽ��ΪƮ�ݣ����Ƕ��ҽ����еĻط��������ʽ",
"$N��ָ��$w��һ����һ����ɽ�����ġ��������顿�����������ʱ����һ����������Х��ն��$n��$l",
"$N���¿��ٱ��ܣ����ֲ������㣬����$w��Ȼ�������ߣ��⻪���䣬ֱֱ����$n��$l��ȴ��̩ɽ��̩ɽ��������֮��--������",
"$N���к�Ȼ���ɻ�ɽ�����ġ������������ɽ�����ʽ������$w��׼$n��$lһ���̳�������ɲʱ�����ݺᣬ�Ʋ��ɵ�������������",
"$N��ʽ��Ȼ��ù����ޱȣ����Ǻ�ɽ�ɾ���--����ɽ����ط�ʮ��ʽ�������ⶸȻ����������²�������â����$n��$l",
"$N��$w����һ�֣�ʹ����ɽ�ɵġ�������롿���������ⲻ�����������ᵯ������ʱһ�ɽ���ֱӿ$n��$l��ȥ",
});

int valid_enable(string usage)
{
	//if (this_player()->query("quest/xxdf/pass")) 
	return usage == "sword" || usage == "parry";
}
int practice_skill(object me)
{
	mapping fam  = me->query("family");
	
	if (!fam || fam["family_name"] != "�������" || fam["master_name"] != "������")
		return notify_fail("�������ν�ֻ�ܴ������д�ѧ����\n");
	
	if( (int)me->query("jingli") < 50 || me->query("neili") < 20 )
		return notify_fail("��������������������ν���\n");
    if (me->query_skill("dali-shenmofu",1)>1)
		return notify_fail("������ħ����ǿ��ı���Ϊǰ����������ͽ������鶯���򲻷������޷���ϰ�������ν���\n");
	if (me->query_skill("tianmo-gun",1)>1)
		return notify_fail("��ħ����׾�����ͽ������鶯���򲻷���������壬���޷���ϰ�������ν���\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

int valid_learn(object me)
{
	mapping fam  = me->query("family");
	object weapon = me->query_temp("weapon");
	
	if (!fam || fam["family_name"] != "�������" || fam["master_name"] != "������")
		return notify_fail("�������ν�ֻ�ܴ������д�ѧ����\n");
	
    if (me->query_skill("dali-shenmofu",1)>1)
		return notify_fail("������ħ����ǿ��ı���Ϊǰ����������ͽ������鶯���򲻷������޷���ϰ�������ν���\n");
    if (me->query_skill("tianmo-gun",1)>1)
		return notify_fail("������������鶯Ʈ�ݣ���������ħ����Ӱ�죬�޷���ϰ�������ν���\n");
	if( !weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( (int)me->query("max_neili") < 800 )
		return notify_fail("�������������\n");

	//if( (int)me->query_skill("xixing-dafa", 1) < 200 )
		//return notify_fail("������Ǵ󷨻��̫ǳ��\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, j, level, damage,n;
	string str;

	level = me->query_skill("qixian-wuxingjian", 1);
	i = random(me->query_skill("sword"))+50;
	if( i<100 ) i = 100;
	j = random(40)-5;
	damage = (random(6)+1)*35;
	if( damage < 50 ) damage =50;
	//�����еĹ���,ǧ���򻯣�������������pfm�����
	
	if (intp(n=me->query_temp("qxwxj/qianbian")) && n>=0)
	{
		switch(n){
			case 12: str = HIW"$N"HIW"��$w"HIW"�ڿ�������һ������һ�����϶��£�ֻ�����ƶ������߹⾰��$n"HIW"�������о�Ȼ����֮������"NOR;break;
			case 11: str = HIC"$N"HIC"��$w"HIC"б��$n"HIC"���أ����д������������أ�����һ�й��ؼ汸����������"NOR; break;
			case 10: str = HIY"$N"HIY"��$w"HIY"��ת��ָ��$n"HIY"�Ҽ磬�������д������������ص����š�$n"HIY"һ�ݣ�ֻ�������о��ް������"NOR; break;
			case 9: str = HIG"$N"HIG"��$w"HIG"ֱ�����ţ���ͼ��$n"HIG"Ҫ����$n"HIG"ֻ�úὣһ�⣬����бָ��$N"HIG"��һ�����д���$n"HIG"С��֮�⣬Ҳ�������й�������"NOR; break;
			case 8: str = HIR"$N"HIR"��ʽ�����󿪴�ϣ��������ͣ��������������һ�������ɴ�Ħ������"HIC"��Ħ������"HIR"����"NOR; break;
			case 7: str = HIC"$N"HIC"�Ľ��к����������ת֮�ƣ��˽���һ��ʹ��̫����������ָ�����ƽ�������������˸����$n"HIC"��ȥ"NOR; break;
			case 6: str = HIY"$N"HIY"����$w"HIY"����һ�����������һ�����$n"HIY"��$l����ʽ��ΪƮ�ݣ����Ƕ��ҽ����еġ��ط����������ʽ"NOR; break;
			case 5: str = HIG"$N"HIG"��ָ��$w"HIG"��һ����һ����ɽ�����ġ��������顿�����������ʱ����һ����������Х��ն��$n"HIG"��$l"NOR; break;
		    case 4: str = HIB"$N"HIB"���¿��ٱ��ܣ����ֲ������㣬����$w"HIB"��Ȼ�������ߣ��⻪���䣬ֱֱ����$n"HIB"��$l��ȴ��̩ɽ��̩ɽ��������֮�ա�"HIG"������"HIB"��"NOR; break;
			case 3: str = HIC"$N"HIC"���к�Ȼ���ɻ�ɽ�����ġ�"HIR"�����������ɽ�"HIC"����ʽ������$w"HIC"��׼$n"HIC"��$lһ���̳�������ɲʱ�����ݺᣬ�Ʋ��ɵ�������������"NOR; break;
			case 2: str = HIY"$N"HIY"��ʽ��Ȼ��ù����ޱȣ����Ǻ�ɽ�ɾ���--��"HIR"��ɽ����ط�ʮ��ʽ"HIY"�������ⶸȻ����������²�������â����$n"HIY"��$l"NOR; break;
			case 1: str = HIG"$N"HIG"һ�����ؽ����С�������������졹,��ʽ����һ���ٲ����϶��£���Х��ȥ"NOR; break;
		    case 0: str = HIR"$N"HIR"��$w"HIR"����һ�֣�ʹ����ɽ�ɵġ�"HIC"�������"HIR"�����������ⲻ�����������ᵯ������ʱһ�ɽ���ֱӿ$n"HIR"��$l��ȥ"NOR; break;
			
		}
		me->add_temp("qxwxj/qianbian", -1);
		return ([
			"action":str,
            "damage": me->query("quest/hmy/qxwxj/qianbian/pass")?200 + random(100):100+random(100),
			"damage_type": "����",
			"dodge": random(30),
			"parry": random(30),
			"force": 250 + random(250),
		]);

	}
	
	//��ī���齣
	if(me->query_temp("qxwxj/pomo")){
		switch(me->query_temp("qxwxj/pomo")){
			case 3: str = HIC"$N���𿴵�����������Ǹ���ī���黭����⾳������΢��Ѭ�⣬��"HIY"�������"HIC"����$nʹ����������ī���齣���������ӵ����쾡��"NOR; break;
			case 2: str = HIY"$N�Ľ�����˸���������ʣ�շת��Ų�������б�������ī���齣�ڶ��С�"HIR"�������"HIY"��"NOR; break;
			case 1: str = HIG"$N�Խ����ʣ������ݺᣬ��ʱ�⾳���뵱ʱ������΢��ʱ�Ľ���״̬�����е����С�"HIC"��������"HIG"��˳�ƶ���"NOR; break;
		    default: str = HIR"$N��$w"HIR"�ϵ�����ȴ������ǡ���෴��$N���п��ٶ�����ȴ�ӱ����У�$n�Ʊ��޷��мܣ����й����ͬС�ɣ�������ǿ"NOR; break;
		}
		me->add_temp("qxwxj/pomo", -1);
		return ([
			"action":str,
            "damage": 150 + random(50),
			"damage_type": "����",
			"dodge": random(30),
			"parry": random(30),
			"force": 250 + random(250),
		]);
	}
//����
	   if(me->query_temp("qxwxj/lianhuan") ) {
			return ([
                "action": WHT+replace_string(replace_string(feiyue_msg[random(sizeof(feiyue_msg))], "$w", "$w"), "$w", "$w"WHT)+NOR,
				"damage": 200 + random(100),
				"damage_type": "����",
				"dodge":  random(20),
				"parry":  random(20),
				"force":  300 + random(250),

			]);
		}
//��ͨ��ʽ	
		return ([
			"action": msg[random(sizeof(msg))],
			"damage": 100 + random(100),
			"damage_type": "����",
			"dodge":  random(30),
			"force":  250 + random(300),
		]);
}
	
string perform_action_file(string action)
{
	return __DIR__"qixian-wuxingjian/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon, weapon1;
	string name;
	int i,j;
	weapon = me->query_temp("weapon");
	weapon1= victim->query_temp("weapon");

	if( !objectp(weapon) ) return;
    

	i = me->query_skill("qixian-wuxingjian", 1);	
	
	
	
	//�������� �����̡��ǡ��硢��
  	
	if (present("qin",me) 
		&& random(10)>7 
		&& me->query_temp("qxwxj/wuxian")
		&& me->query("quest/hmy/qxwxj/wuxian/pass")	)
	{

	 switch (!random(4))
	 {
	   case 0:
          message_vision(HIY"$N��ָ�ḧ���ң����ڡ��������ϣ��������ص�������$n�о��Լ��ĵ���һ������������ƺ�Ҫ����һ�㡣\n"NOR,me,victim);
	      if (random(me->query_skill("qixian-wuxingjian",1))>me->query_skill("parry",1)/3)
	      {
			  message_vision(HIW"$n�о��Լ��ľ����ڲ�����ʧ��\n"NOR,me,victim);
			  victim->receive_damage("jing",random(1000),me);
			  victim->receive_wound("jing",random(1000),me);
			  if (victim->query("neili")>3000)
			     victim->add("neili",-1000-random(3000));
	      }
		  else message_vision(HIC"$n��Ȼ��ʶ������$N���������������ֶΣ����ɵ���Цһ����Ĭ��������\n"NOR,me,victim);
		  break;
	   case 1:
		  message_vision(HIW"$N��£�������̡����������н�����ײ֮����$n�о��Լ��ĵ���һ�ۣ��ƺ���һ�������ڴ˴��Ƶá�\n"NOR,me,victim);
	      if (random(me->query_skill("force",1))>me->query_skill("dodge",1)/3)
	      {
			  message_vision(HIC"$n�о��Լ��ĵ���������ɢ���Ĵ����ߣ��ҳ�һ�š�\n"NOR,me,victim);
			  me->apply_condition("no_force",1);
			  me->add_condition("neishang",1);
			  me->add_condition("no_exert",1);
			  if (victim->query("neili")>3000)
			     victim->add("neili",-1000-random(3000));
	      }
		  else message_vision(HIY"$n��֪����,��������$N����������ʧЧ��\n"NOR,me,victim);
		  break;
       case 2:
		  message_vision(HIG"$N����������״������һ���������ǡ�����������ľ�ѣ�������\n"NOR,me,victim);
	      if (random(me->query_skill("neili",1))>me->query_skill("neili",1)/2)
	      {
			  message_vision(HIB"$n�о�������������֮�أ�������ת֮�ʣ����������������ζ�ʱ���ƣ�����������\n"NOR,me,victim);
			  victim->add("jingli",-1000-random(1000));
			  //victim->add("jingli",-random(1000));
			  victim->add_busy(1);
			  if (victim->query("neili")>3000)
			     victim->add("neili",-1000-random(3000));
	      }
		  else message_vision(HIY"$n��֪����,��������$N����������ʧЧ��\n"NOR,me,victim);
		  break;

		case 3:
		  message_vision(HIG"$N����ʳָ�Ծ����������������ϣ����硹�������������һ���������������ԭ֮�ơ�\n"NOR,me,victim);
	      if (random(me->query_int(1))>me->query_int(1)/2)
	      {
			  message_vision(HIW"$n����������Ѫӿ����������ѹ�Ʋ�������ɫ��ʱһƬ�Ұס�\n"NOR,me,victim);
			   victim->receive_damage("qi",-1000-random(4000),me);
			  victim->receive_wound("qi",-random(4000),me);
			  victim->add_busy(1);
	      }
		  else message_vision(HIC"$n��֪����,��������$N����������ʧЧ��\n"NOR,me,victim);
		  break;
		 case 4:
		  message_vision(HIC"$N���ִ�Ĵָ��ʳָ����Ծʽ������������Ȫ��ˮ������ˮ���Ľ������ǡ�������\n"NOR,me,victim);
	      if (random(me->query_con(1))>me->query_con(1)/2)
	      {
			  message_vision(HIB"$n����ȫ����Ϊ$N�������أ��������ơ�\n"NOR,me,victim);
			  victim->add_condition("no_exert",1);
			  if (victim->query("neili")>3000)
			     victim->add("neili",-1000-random(3000));
			  
	      }
		  else message_vision(HIY"$n��֪����,��������$N����������ʧЧ��\n"NOR,me,victim);
		  break;	
	    }
	}
   if(i>=550 && !random(4)){
       if(random(i)>(int)victim->query_skill("parry",1)*2/3
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HIG"\n$N�������࣬��סȫ�����ް�ֿ�϶��������˺���������$n�������죡\n"NOR,me,victim);
            victim->set_temp("must_be_hit",1);
            call_out("qxwxj_must_be_hit",2,me,victim,random(i/50));
       }
   }

   else if(i>=500 && !random(3)){
       if(random(i)>(int)victim->query_skill("dodge",1)/2
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HBRED"\n$n��δ���������ǿ�У�$N������Ҳ����û��������ֻ����������޷����޷�����Ͼ϶��\n"NOR,me,victim);
            //victim->set_temp("no_fight",1); //̫���ˣ�����Ȼû��ȡ�����
            victim->apply_condition("no_exert",1);
       }
   }  
  else if(i>=450 && !random(5)){
       if(random(i)>(int)victim->query_skill("dodge",1)/2
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HIW"\n$N����һ�𣬽����ڵ����ν������������һ�󵭵�����������$n��ȫ��Ѩ����\n"NOR,me,victim);
            //victim->set_temp("no_fight",1);
            victim->apply_condition("no_perform",1);
            victim->add_busy(1);
       }
   }  
   
   name = xue_name[random(sizeof(xue_name))];
   if(i>=350 && !random(3)){
   	if(random(i)>(int)victim->query_skill("dodge",1)/3
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HIB "\nֻ��һ�󴾺��������" + weapon->query("name") +HIB "��������$n" HIY "��" + name + "��"
                       NOR + HIB "��ʱ��������������ȫ�������Ҵܲ�ֹ��\n" NOR,me,victim);
            //victim->set_temp("no_fight",1);
            victim->add_busy(2+random(2));
            victim->apply_condition("no_exert",1);
       }
   }  
   	 
}

void qxwxj_must_be_hit(object me,object target,int i)
{
    if(!target) return;
    if(!me) {
        target->delete_temp("must_be_hit");
        if(living(target))
            message_vision(HIY"$n�������˿������ֽŻָ���������\n"NOR,target);
        return;
    }
    if(wizardp(me) && me->query("env/qxwxj_test")) write("i is "+i+"\n"NOR);
    
	if(me->query_skill_mapped("sword")!="qixian-wuxingjian"
     ||me->query_skill_mapped("parry")!="qixian-wuxingjian"
     ||i<=0){
        if(living(target))
            message_vision(HIY"$n�������˿������ֽŻָ���������\n"NOR,me,target);
        target->delete_temp("must_be_hit");
		target->delete_temp("no_fight");
        return;
    }
    call_out("qxwxj_must_be_hit",1,me,target,--i);
}
