// shenghuo-lingfa ʥ���
// 1997-5-14
inherit SKILL;
#include <ansi.h>
inherit F_SSERVER;
int hit_ob(object me,object victim,int damage);
string  *msgl = ({
"$Nһʽ���������󡹺��ط��֣�$w��β�����ϵ��������벻����λ������$n��ȥ",
"$Nƽƽһ�������һʽ�����·ת����$w�ڰ�չŹŹֵֹ�ת�˸��䣬����$n��$l",
"$NͻȻһ����Х��˫��һ�С�������ʵ������ʵʵ�����Ƕ��ǵĻ���$n��$l",
"$N��Ȼ��ͷ��һʽ��ͷͷ�ǵ�����һ��ͷ����$nײȥ������$wȴ���е���$n��$l��ȥ",
"$NͻȻ�������һʽ�����������������������Ľ���׹������$w��$n��$l��ȥ",
"$N���ش��أ�һʽ������������������صĿ޺ţ�ͻȻ����߷�ɳ�����$w��$n����",
"$NĬ��ھ���$wһ�С�Ӧ����󡹣���ָǰ�أ�ͻ��һת�䣬��$n�ı��Ĵ�Ѩ��ȥ",
"$Nʹ������ʥ�����е�һ�С�������ǰ����������$n�ұۣ�$wȴ��Է���ǰ��Ѩ��ȥ",
"$Nһ�С��������С�����֪��Σ������Ѿ����$w������һ�ڣ������ޱȵĴ���$n��$l",
"$N���е�$w����һ������Ȧ�ӣ����С��췽��԰��һ������ʱ����$n�ۻ����ң���֪����"
});
string  *msgc = ({
"$N����Ϊ����һ�С�������ʤ��������б�ɣ���������$n�߳��Ľ�",
"$Nһʽ��������ȫ���������ڵ���һ�������ֱ���$n��$l�����ֻ����ж���Ѩ",
"$NͻȻ��һʽ���Խ�Ϊ�ˡ���������ǰһ�����Ľ��������£�˫����$n$l��ȥ",
"$N����һ����һʽ��������ա��������շ��˼������Ľ�������$n��$lץȥ",
"$Nһ�����һʽ���������ڡ������ڰ�գ�����ʱ�ҽŵ�ϥ����$n�ض�һ��",
"$N��ǰһ����һʽ��Ͷ���ͱ�����ײ��$n�Ļ��У�˫����$n$l��Ѩ��ײȥ",
"$N���ش��أ�һʽ����ɳ��ʯ�����������صĿ޺ţ�ͻȻ����߷�ɳ��������$n����"
});

string  *msg2 = ({
HIW"$Nֱ����ǰ������һ�٣���Ȼһ���ˤ�˹�ȥ��˫��$w"HIW"ȴ����$n�ؿ����˹�ȥ"NOR,
HIR"$Nƽƽһ�������$w"HIR"�ڰ�;�ŹŹֵֹ�ת�˸��䣬�ĵ�һ�죬����$n��$l"NOR,
MAG"$N��$w"MAG"���뻳�У�����һ̽����ץס$n��ţ�Ӳ������$n�ڰ�������˻���"NOR,
HIY"$N˫��$w"HIY"���Ӻ�ɨ��$n����һת������ܿ��������ĵ�һ�죬$l�ѱ�$w"HIY"����"NOR,
YEL"$n����ٿ��ץס��$N���ֵ�$w"YEL"����֪��$w"YEL"β�����ϵ����ĵ�һ�죬���ô���$n����"NOR,
GRN"$N�����ڵأ�˫ȭ�ʹ��Լ����ţ���$n����ͻȻ����߷�ɳ�����$w"GRN"��$n��$l����"NOR,
HIG"$N����΢б���ұ������$w"HIG"��Ī������ķ�λת�˹������ĵ�һ������$n��$l���ش�ȥ"NOR
});

int valid_enable(string usage)
{
        
		if (!this_player()->query("quest/mj/shlf/givezhang"))
        {
			return notify_fail("�������֪��ʥ�����ʹ��֮�������ڼ�������ʥ�����\n");
        }
		return usage == "dagger" || usage== "cuff" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
	string msg;

	if(me->query_temp("tisha")){
		switch(me->query_temp("tisha")) {
			case 4: msg = CYN"$Nֱ����ǰ������һ�٣���Ȼһ���ˤ�˹�ȥ��˫������$n�ؿ����˹�ȥ"NOR; break;
			case 3: msg = CYN"$N�����ڵأ�˫ȭ�ʹ��Լ����ţ���$n����ͻȻ����߷�ɳ�����$w"CYN"��$n��$l����"NOR;break;
			case 2: msg = CYN"$n����ʱ֮�䣬������ѩ���棬˫�۲��ܼ��ãȻ��֪���룬$N�����ü粿�ӱ�����$nײȥ"NOR; break;
			case 1: msg = CYN"$N����$n��ȥʽ������Ǭ����Ų���񹦣��굽$n����ǰ��������$w"CYN"��$n��$l��ȥ"NOR;break;
			default: msg = CYN"$Nֱ����ǰ������һ�٣���Ȼһ���ˤ�˹�ȥ��˫������$n�ؿ����˹�ȥ"NOR; break;
		}  
		me->add_temp("tisha", -1);
		return ([
			"action": msg,
			"force" : 150 + random(150),
			"dodge": random(30),
			"parry": random(30),
			//"damage": me->query_temp("type")? 50+random(50):100 + random(100),//ԭ����130+random(140)
			"damage":200+random(100),
			"damage_type" : me->query_temp("type")? "����":"����",
		]);
	}
	if(me->query_temp("shlf/lianji")){
		switch(me->query_temp("shlf/lianji")) {
			case 12: msg = YEL"$N����ֱ�������ֳ�$w��$n�������ƽƽ����,������һ˲֮�䣬$N�������󣬳����Ȼһȭ����$n��$l��"NOR; break;
			case 11: msg = YEL"$n����һ�㣬����˿����������֮�䣬��������������$Nһȭ��ֻ������ظ������������ƺ�������λ��"NOR;break;
			case 10: msg = YEL"$nһ�����ģ�$N��$w"YEL"����$n�ĺ��ģ�ͻȻ��$N�����������ޱȣ���������"NOR; break;
			case 9: msg = YEL"$n����һת������ܿ��������ĵ�һ�죬�����ѱ�$Nһ����С���һ�´��У�$n��ǰһ�ڣ�������ȥ"NOR;break;
			case 8: msg = YEL"��$w"YEL"β�����ϵ����ĵ�һ�죬���ô���$n����"NOR; break;
			case 7: msg = YEL"$n���������ָһ����ľ��ֻ�÷�����������Ȼ�ᵽ�ı��У��ֱ������쳣��ʹ�����"NOR;break;
			case 6: msg = HIY"$n����������֪$N��һ����׾ʵ�ɣ��ض����������쳣�ĺ���,$N���л�û���ϣ���Ȼ����������߳���������"NOR; break;
			case 5: msg = HIR"�����$NԾ���գ���$nͷ��������������һ�и��ǹ��죬�����β����ˣ�������ѧ֮���䷱����δ����һ·�����á��ֱ�׾������"NOR;break;
			case 4: msg = CYN"$n������ɫ����������һ�ã�ͻ���ؿ�һʹ���ѱ�$N����ײ��"NOR; break;
			case 3: msg = HIR"$N˫�ּ��Ӻ�ɨ��$NͻȻ�����������Ľ��$n��֪���Ǻ����⣬���뻹�Ǳ�֮Ϊ�������̤��һ������ǰ�׹⼱�����Ҽ��ѱ�$N��$w���ػ���"NOR;break;
			case 2: msg = YEL"$n��ûת��������������в��һ����ʹ���ѱ�$N��һ��Ī���ĽǶȣ�������һ�ţ���Ϊ����˼��"NOR; break;
			case 1: msg = CYN"$nԾ���������������ᣬͻȻ���͵�һ���죬����������$Nץ��һ���������$Nָ����$n�����ϻ����˼���צ�ۣ�������ʹ"NOR;break;
			default: msg = CYN""NOR; break;
		}  
		me->add_temp("shlf/lianji", -1);
		return ([
			"action": msg,
			"force" : 150 + random(150),
			"dodge": random(30),
			"parry": random(30),
			//"damage": me->query_temp("type")? 50+random(50):100 + random(100),//ԭ����130+random(140)
			"damage":150+random(100),
			"damage_type" : me->query_temp("type")? "����":"����",
		]);
	}
	if (!weapon)
		return ([
			"action":msgc[random(sizeof(msgc))],
			"damage_type":"����",
			"dodge":random(30),
			"parry":random(30),
			"force":random(300)+ 150,
		]);
	if( me->query_temp("lian"))
		return ([
			"action" :msg2[random(sizeof(msg2))],
			"force" : random(350) + 300,
			"dodge": random(30),
			"parry": random(30),
			"damage": 180+ random(100),
			"damage_type":random(2)?"����":"����",
		]);
	
	return ([
		"action":msgl[random(sizeof(msgl))],
		"damage": 80 + random(100),
		"damage_type":random(2)?"����":"����",
		"dodge": random(30)-10,
		"force": random(350)+200,
		"parry": random(20),
		"post_action": (: call_other, WEAPON_D, "bash_weapon" :)
	]);
}

int practice_skill(object me)
{
	if ( me->query("jingli") < 50)
		return notify_fail("�������������ʥ�����\n");         
	if ((int)me->query("neili") < 10)
		return notify_fail("�������������ʥ�����\n");
	me->receive_damage("jingli", 40);
	me->receive_damage("neili", 15);
	return 1;
}

int valid_learn(object me)
{
	object weapon = me->query_temp("weapon");
	int skill = me->query_skill("shenghuo-lingfa", 1);
       
	if (!weapon || weapon->query("skill_type") != "dagger")
		return notify_fail("��û��ʹ�õ�������\n");

	if (me->query("max_neili") < 1000)
		return notify_fail("�������������\n");
	if (!me->query_skill("jiuyang-shengong"))
	if (me->query_skill("shenghuo-shengong", 1) < (skill-10)
	&& me->query_skill("shenghuo-shengong", 1) < 200)
		return notify_fail("���ʥ���񹦻��̫ǳ��\n");
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"shenghuo-lingfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
       int lvl;
        object weapon, weapon2;
        int i, ap, dpp, dpd, dpf,damg;
        string type, msg;
        weapon=me->query_temp("weapon");
		weapon2=victim->query_temp("weapon");
        lvl = me->query_skill("shenghuo-lingfa", 1);
        damg=lvl+me->query_skill("qiankun-danuoyi",1)/2;
        if (me->query("neili") < 2000
           || me->query_skill_mapped("dagger") != "shenghuo-lingfa"
           ||!objectp(weapon = me->query_temp("weapon"))
           || weapon->query("skill_type") != "dagger"
		   || me->query_skill_mapped("parry")!="qiankun-danuoyi"
           || !me->query("mjqkdny/pass"))
         return 0;

        ap = me->query_skill("dagger") + me->query_dex() + me->query_int();
        dpp = victim->query_skill("parry");
        dpd = victim->query_skill("dodge");
        dpf = victim->query_skill("force");
        me->add("neili", -100); 
 
        switch(random(5))
        {
            case 0:
              if (ap * 3/4 + random(ap) > dpp/3)
              {
                  
				  me->add("neili", -220);                  
                  //victim->receive_wound("qi", (me->query("max_qi")/3), me);
				 // victim->add_busy(1+random(2));
				  //victim->receive_wound("jingli", (me->query("max_jingli")/3), me);
                  msg=random(2)? BLU "$N�Ѿ���Ǭ����Ų���ؼ��������������ɽ���˾������洫,����ʹ�����죬������������" + weapon->name() +BLU
                                     "\n֮���ֵá�Ų��Ǭ�����ķ��ศ����Ȼ����ǰ�кܴ�ͬ,������Ȼ������\n" NOR:		  
             				     HBMAG "$N�੿�Ц��ֻ������������" + weapon->name() + HBMAG "�������������ռ��գ����й����ޱȣ���������������ѧ��$nһ��֮�£����д󺧡�\n" NOR;	
				  victim->add_busy(1+random(2));
				  me->add_temp("apply/damage",damg/2);
				  COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);	
				  me->add_temp("apply/damage",-damg/2);
				  message_vision(msg, me, victim);
             }
             break;
          case 1:
			   // ���öԷ�busy�����������϶���͸��������й�
              if (random(me->query_int(1))> victim->query_int(1)/3)
              {
                  me->add("neili", -200);                  
                  if (random(2))
                     message_vision(HBRED "$N����Ǭ����Ų�Ƶĸ����ķ�����ȻĪ֮����ȫ��, �������������ռ��գ�һ��ȫƾ������֮��\n"NOR,me,victim);
				  else
                     message_vision(HIY "$N����" + weapon->name() + HIY "������ң���ǰ����ָ�ϴ򱱣�ָ�����ϣ�$n���öԷ���ʽû���κι켣��ѭ��һ������Ϊ������͸���������ھ����ˡ�\n" NOR,me,victim);                 ;
				  victim->apply_condition("no_exert",1+random(2));
				  COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);	
             }
             break;

          case 2:
            
		     if (random(me->query("combat_exp",1)) > victim->query("combat_exp",1)/3)
		      {		  		  
			   
		        message_vision(HBBLU"\nǬ����Ų�����ó�Ѱ覵�϶,����������$N"+HBBLU+ "���Լ������"+HIR+"��Ų��Ǭ����"+HBBLU+"�ķ������Ĺ�������\n"+
				   weapon->query("name")+HBBLU+"��$n�ټƷ��������Ҳ��ȣ��ο��Գ������� $n��$N��ָ����ɾ���˿˿����,ֱָ�Լ���ʽ�е�������\n"NOR,me,victim);
			   //��������
               victim->apply_condition("no_fight",1+random(2));
			   victim->apply_condition("no_perform",1+random(2));
                if (!me->is_busy())
                 {
                    weapon = me->query_temp("weapon");
                    weapon2 = victim->query_temp("weapon");
                    if (weapon2)type = weapon2->query("skill_type");

                    if (ap * 3 / 4 + random(ap) >= dpf/2 && weapon2
                      && type != "pin")
                    {
                           msg = BLU"$n" HIR "�������з��Ʋ���������"
                                 "��" + weapon2->name() + BLU "һʱ��"
                                 "Ȼ����ס�����ֶ��ɣ�\n" NOR;
                           weapon2->move(environment(me));      
                           me->add("neili", -100);                 
                      } else
                        {
                           msg = HIY "$n" HIR "�Եÿ�϶��Ϣ��һʱ��ȴ"
                                 "Ҳ����������\n" NOR;
                           me->add("neili", -40);
                         }
               }else 
			     if (ap * 4 / 5 + random(ap) > dpd/2)
                 {
                          msg = HIY "$n" HIY "��æ�ֵ���һʱ�䲻����æ���ң�"
                                "��Ͼ������\n" NOR;

                          me->start_busy(1+random(2));
                          victim->add_busy(1 + random(lvl / 100));
                    }
                  else
                   {
                          msg = HIC "$N" HIC "��"HIR"��Ų��Ǭ����"HIC"�ķ�����" + weapon->name() +
                                HIC "֮��" HIC "������$n" HIC "���ص��쳣���ܣ�$N"
                                HIC "һʱ��Ȼ�޷�ʩΪ��\n" NOR;
                          me->start_busy(1 + random(2));
                          victim->start_busy(1);
                    }
               message_vision(msg, me, victim);
			 //COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);	
		  			   
			  }
             break;
          //��Ǭ����Ų���ķ��������Ĺ���һ�������ĳ����������������һ�������ˣ����ǡ�Ǭ����Ų�ơ��ľ��������书��
		  //���¿���֮�䣬�ѽ����������µ�һ�ɾ�������Ϊ��������
  
        case 3:
             if (ap * 4 / 5 + random(ap) > dpd/2 && 
                  me->query_dex() >= 40) 
                {
			    weapon = me->query_temp("weapon");
                message_vision(HIB "\n$N" HIB "����[Ǭ����Ų��]��,������һ����һ�ɵ��书������ȡΪ����,����΢΢һЦ������" + weapon->name() + HIB 
                             "\n����"HIR"��Ų��Ǭ����"HIB"���ķ�����Ȼ�ѽ�$n�����е����������۵�,$n��֪������ʽ�������Լ���\n" NOR, me, victim);
                COMBAT_D->do_attack(victim, victim, weapon, 3);
                me->add("neili", -320);                
             }
             break;                        
      case 4 : 
		   if (ap * 4 / 5 + random(ap) > dpd/2 && 
                 ! me->is_busy() &&
                 ! me->query_temp("shenghuo-lingfa/lian") &&
                 me->query("dex") >= 40)
                {
			     weapon = me->query_temp("weapon");
                 message_vision(HIB "\n$N" HIY "���쳤Х��Ǭ����Ų�Ƶ��߲��񹦾����ŷ�����$n��ʽ�п�϶���������С�\n" NOR, me, victim);
                 me->add("neili", -320);				
			  	 me->set_temp("shenghuo-lingfa/lian", 1);
                for (i = 0; i < 3; i++) //��6����3��6̫���˵�
                {
                    if (! me->is_fighting(victim))
                            break;                   
                    if (! victim->is_busy() && random(2) == 1)
                            victim->add_busy(1);
                    COMBAT_D->do_attack(me, victim, weapon, random(4)?1:3);
                }
                me->delete_temp("shenghuo-lingfa/lian");
                
             }
             break;                        
	   }
}

