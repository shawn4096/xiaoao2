// dagou-bang.c �򹷰���
// Code By Looklove@SJ 2001/4/1
// Modify By Looklove 2001.4.7
// Modify By Looklove 2001.4.8
// Looklove modified at 2001.5.5
// Looklove modified at 2001.5.15
// Looklove modified at 2001.5.18
//update by jpei 2010 �������������԰�����������

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
        "action": "$Nһ������������$w��ʹ��һʽ����ݾ��ߡ�����ɨ��$n��$l",
        "force": 80,
        "lvl" : 0,
        "skill_name": "��ݾ���",
        "damage_type": "����"
]),
([
        "action": "$N������Ծ������$w���һζ���һ�С�����Ѱ�ߡ���$n��$l��ȥ",
        "force": 100,
        "lvl":10,
        "skill_name": "����Ѱ��",
        "damage_type": "����"
]),
([
        "action": "$N����$wһȦ��ʹ��һ�С����Ŵ򹷡���$n����˷�Χ���ܲ�͸��",
        "force": 140,
        "lvl" : 20,
        "skill_name": "���Ŵ�",
        "damage_type": "����"
]),

([
        "action": "$N��̤��λ��ʩ�����������졹�����ֽ�$w����������$n��ȥ",
        "force": 160,
        "lvl" : 30,
        "skill_name": "��������",
        "damage_type": "����"
]),
([
        "action": "$N���һ����������ǽ��������һ������$w��ͷ����$n��$l",
        "force": 180,
        "lvl" : 50,
        "skill_name": "������ǽ",
        "damage_type": "����"
]),
([
        "action": "$Nʹ��һ�С�����˫Ȯ��������$w���������������$n��$l",
        "force": 200,
        "lvl" : 80,
        "skill_name": "����˫Ȯ",
        "damage_type": "����"
]),
([
        "action": "$N����һ����һ�С���Ȯ��·����������$w��$n��ȥ�Ʒ��˹�ȥ",
        "force": 220,
        "lvl" : 100,
        "skill_name": "��Ȯ��·",
        "damage_type": "����"
]),
([
        "action": "$Nһ�С�����ͷ����ֻ��$wͻȻ����ֱ��$n�Ķ���",
        "force": 240,
        "lvl" : 120,
        "skill_name": "����ͷ",
        "damage_type": "����"
]),
([
        "action": "ֻ��$Nʹ��һ�С�б�򹷱���������š����$wб����$n��$l",
        "force": 260,
        "lvl" : 140,
        "skill_name": "б�򹷱�",
        "damage_type": "����"
]),
([
        "action": "$N���һ����ʹ��һ�С����ع��Ρ������ֽ�$w����$n��$l",
        "force": 270,
        "lvl" : 160,
        "skill_name": "���ع���",
        "damage_type": "����"
]),
([
        "action": "$Nһ�С����붴������$w���˸���������ɨ$n��$l",
        "force": 280,
        "lvl" : 180,
        "skill_name": "���붴",
        "damage_type": "����"
]),
([
        "action": "$N�����������$wһ�ϣ�ʹһ�С�ѹ�繷��������ͷ��������$n��$l",
        "force": 300,
        "lvl" : 200,
        "skill_name": "ѹ�繷��",
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return (usage == "stick") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((string)me->query("family/master_name")!="���߹�")
                return notify_fail("�򹷰�ֻ�ܴӺ��߹���ѧ����\n");
		//if (!me->query("quest/gb/dgb/pass"))
               // return notify_fail("��ֻ����˵���򹷰�������δ�ܹ����ڡ�\n");
        if ((int)me->query_skill("stick", 1) < 20)
                return notify_fail("��Ļ�������̫��, ����᲻�˴򹷰�����\n");

        if (me->query("gender") == "����")
                return notify_fail("��һ�����в�Ů֮�������ѧ�򹷰���\n");

        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        return 1;
}

string query_skill_name(int level)
{
        int i = sizeof(action);
        while (i--)
                if(level > action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, j, level, glvl, d, p;
        string msg;

        d = (int)me->query_dex() * (random(4)+1);
        p = (int)me->query_int() * (random(2)+2);
		level = me->query_skill("dagou-bang", 1);
		weapon = me->query_temp("weapon");

		if (me->query("gender")=="Ů��") glvl = level/3;
		else glvl = level/6; 
		
		//if (glvl > 100) glvl = 100;

		//�����޹�����
		if( me->query_temp("dgb/wugou")){
                switch((int)me->query_temp("dgb/wugou"))
				{
					case 6: msg = HIR"$Nʩչ���������޹��������䣬ֻ��"+ weapon->name() +HIR"���в���$n�����ţ������Ӱ����ǵذ����"NOR; break;
					case 5: msg = HIB"ֻ�������Ӱ��Ȼһͣ��$N���������޹��������ʹ��������"+ weapon->name() +HIB"һ��һ�ߣ�"+ weapon->name() +HIB"ͻȻ������$n�ĵ���Ѩ����"NOR; break;
					case 4: msg = HIG"$Nʹ���������޹������ı䣬��"+ weapon->name() +HIG"˫����ס����Ȼ�����$n���۾�����$n����ʶ��ܼ䣬һ������С��"NOR; break;
					case 3: msg = HIW"$N�������������ʹ���������޹��������䣬����"+ weapon->name() +HIW"��ɨ��$n�Ľ��ף����಻������Ӱ����"NOR; break;
					case 2: msg = HIY"��Ȼ$N��������������"+ weapon->name() +HIY"б����ʹ���������޹����ڶ��䣬�ڵ���žžž�������£���������֮����Ȼ����$n�ĺ󱳶�����Ѩ"NOR;break;
					case 1: msg = HIC"$N����ƫ�壬������ң���ǰ���󣬲���������ֻ����Ӱ��������"+ weapon->name() +HIC"��������Ӱ����Ȼʹ���ǡ������޹�����һ�����ʽ"NOR; break;
					default: msg = HIC"$N����ƫ�壬��"+ weapon->name() +HIC"��������Ӱ����Ȼʹ���ǡ������޹��������仯"NOR; break;
                }
                me->add_temp("dgb/wugou", -1);
                return ([
					"action": msg,
					"dodge":me->query("gender")=="Ů��"?level/10+d:level/15+d/2,
					"parry": glvl/2+p/2,
					"damage": me->query("gender")=="Ů��"?glvl/2+p/2:glvl/4+p/4,
					"force" : me->query("gender")=="Ů��"?action[j]["force"]:action[j]["force"]*3/2,
					"lvl" : action[j]["lvl"],
					"damage_type" : action[j]["damage_type"],
                ]);
        }
		//˫��
        if( me->query_temp("shuangjue/dgb")){
                switch((int)me->query_temp("shuangjue/dgb")){
                        case 2: msg = HIG"$N��ȻбŲһ�����������һ��������$w"HIG"��ɨ��$n��$l"NOR; break;
                        case 1: msg =  HIW"$N����ͻ�䣬��ȻԾ��ֻ��$w"HIW"����һ�Ű�Ӱֱ��$n��$l��ȥ"NOR;break;
                        default: msg = HIW"$N���������Ȼһ����Х�����������Ӱ����$n��$l"NOR; break;
                }
                me->add_temp("shuangjue/dgb", -1);
                return ([
                "action": msg,
                "dodge": glvl,
                "parry": p+d,
                "damage": glvl + p/2,
                "force": level+glvl+p,
                "damage_type": "����"
                ]);
        }


//Ѱ������
        for(i = sizeof(action); i > 0; i--)
		{
            if(level >= action[i-1]["lvl"]) 
				j = NewRandom(i, 20, level/5);
                       
                
			if (level > 450 && userp(me))
			{
				 return ([
                        "action" : action[j]["action"],
                        "dodge":(d+p)/2,
                        "parry": glvl/2+(p+d)/2,
                        "damage": glvl/4+(p+d)/2,
                        "force" : action[j]["force"]+glvl/2+p+d,
                        "lvl" : action[j]["lvl"],
                        "damage_type" : action[j]["damage_type"],
                        ]);
			}else {
				return ([
                "action" : action[j]["action"],
                "dodge":me->query("gender")=="Ů��"?level/10+d:level/15+d/2,
                "parry": glvl/2+p/2,
                "damage": me->query("gender")=="Ů��"?glvl/2+p/2:glvl/4+p/4,
                "force" : me->query("gender")=="Ů��"?action[j]["force"]:action[j]["force"]*3/2,
                "lvl" : action[j]["lvl"],
               "damage_type" : action[j]["damage_type"],
				]);
			}
		}
}

int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("dagou-bang", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if (!objectp(weapon = me->query_temp("weapon"))
         ||(string)weapon->query("skill_type") != "stick")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( me->query("gender") == "����")
                return notify_fail("��һ�����в�Ů֮����������򹷰���\n");

        if ((int)me->query("jingli") < 40)
                return notify_fail("��ľ����������򹷰�����\n");

        if ((int)me->query("neili") < 30)
                return notify_fail("��������������򹷰���\n");

        me->receive_damage("jingli",40);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dagou-bang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int b, x, p, level, damage, quest;
	object weapon, tweapon;
	string msg;

	quest = (int)me->query("dgb/wugou");
	//ȡ��death ����
	//b = me->query_skill("bangjue", 1) + me->query("death_times",1) ;
	b = me->query_skill("bangjue", 1) ;

	level = me->query_skill("dagou-bang", 1);
	weapon = me->query_temp("weapon");
	tweapon = victim->query_temp("weapon");

	if (me->query_skill_mapped("parry") != "dagou-bang") return 0;
	if (!me->is_fighting(victim) || !weapon || !userp(me)) return 0;
	if ( !living(me) || !living(victim)) return 0;
	//if ( damage_bonus < 100 ) return 0;
	//if ( damage_bonus > 300 ) damage_bonus = 300;

	//�򹷰��ھ� 1/5����,���ǣ�ƺ͸����˺�
	if ( random(b) >= 100
	 && random(level) > 100
	 &&	!me->query("quest/gb/dgb/bangjue/pass")
	 && random((int)me->query("neili")) > 400
	 && (int)me->query("max_neili") >= 1200
	 && random(20) > 15 )
	{
		victim->add_busy(1);
		damage = damage_bonus/10 + random(damage_bonus)/10*level/40;
		if (!random(2))
		{
			msg = MAG"������$N�����е�����������ǽ��δ� �����������β��������֮��$n���̽����������С�\n";
			msg += "$n�������ã����������мܣ���ǰ��Ծ���ܣ���֪$N�ĵ�����಻�ϣ�$nһ��������������!\n"NOR;
			victim->receive_damage("qi",damage/2,me);
			victim->recieve_wound("qi",damage/4,me);
			p = (int)victim->query("qi")*100/(int)victim->query("max_qi");
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			message_vision(msg, me, victim);
		}
		else {
			msg = YEL"$N����������������ӵ�ʩ���� �����˫ȮĪ��ͷ����, ��֮��Ӱ���Ӷ��£�$n�����������м��¡�\n"NOR;
			victim->receive_damage("qi",damage/3,me);
			victim->receive_wound("qi", damage/6,me);
                        p = (int)victim->query("qi")*100/(int)victim->query("max_qi");
                        msg += COMBAT_D->damage_msg(damage, "����");
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			message_vision(msg, me, victim);
        }
		me->add("neili", -100);
		
	}
	//������������������ת
	//write(HIC"��ʦ������ֵdamage="+damage_bonus+"\n"NOR);
	if (random(10)<5) return 0;

	switch (random(5))
	{
		case 0:
			message_vision(HBRED+HIW"$Nʹ���򹷰��������־���������������"+weapon->query("name")+HBRED+HIW"���籩������$n��ͷ������ȥ��\n"NOR,me,victim);
			if (random(me->query("combat_exp"))>victim->query("combat_exp")/3)
			{
				message_vision(CYN"$n������Ȼ���㣬����������Ϊ"+weapon->query("name")+CYN"������ǰ�أ�\n"NOR,me,victim);
				victim->receive_damage("qi",damage_bonus,me);
				victim->receive_wound("qi", damage_bonus/2,me);				
			}else {
				message_vision(HIY"$nս�������쳣�ḻ����΢һЦ��һ������Ծ���ţ����$N����Ϭ����ɱ�У�\n"NOR,me,victim);
				me->add_busy(1);
				
			}
			break;
		case 1:
			message_vision(HIY"$N�򹷰��������־�������ʩչ��˫����ס"+weapon->query("name")+HIY"����һƬ�����Х������$n�ĺ���Ȼ��ȥ����\n"NOR,me,victim);
			if (random(me->query_dex(1))>victim->query_dex()/2)
			{
				message_vision(HIG"$n��Ƿȱ������������Ϊ"+weapon->query("name")+HIG"�����к�"+HIR"����Ѩ"+HIG"��������й��\n"NOR,me,victim);
				victim->receive_damage("qi",damage_bonus,me);
				victim->apply_condition("neishang",2+random(3));	
				victim->apply_condition("no_exert",2);
				victim->add("neili",-damage_bonus);
			}else {
				message_vision(HIR"$n���������������Ṧ���$N���й������ʽ��\n"NOR,me,victim);
				me->add_busy(1);				
			}
			break;
		case 2:
			message_vision(WHT"$Nʹ���򹷰��������־���������"+weapon->query("name")+WHT"����һ�����߰���鶯�쳣�����ƹ��죡\n"NOR,me,victim);
			if (random(me->query_skill("dagou-bang",1))>victim->query_skill("parry",1)/2)
			{
				message_vision(HIY"$n�����Լ�ǰ�����Ҿ�ΪһƬ��Ӱ�����֣���ʱ��Щ�����޴�������\n"NOR,me,victim);
				victim->add_busy(2+random(2));
			}else {
				message_vision(HIY"$n������ת��Ϣ����ʽ����Ϊ�����ữ����$N�Ĺ�����\n"NOR,me,victim);
				me->add_busy(1);
				
			}
			break;
			case 2:
		case 3:
			message_vision(HIG"$Nʹ���򹷰�����ת�־���������"+weapon->query("name")+HIG"������$nǰ�����ң����ƹ�֮�������в���$n��ǰ���Ѩ��\n"NOR,me,victim);
			if (random(me->query_skill("staff",1))>victim->query_skill("dodge",1)/2)
			{
				message_vision(CYN"$n��æ��������ת����ת����ͼ��ܣ���"+weapon->query("name")+CYN"��Ӱ���Σ�$nת�˼���Ȧ���Ȼ����Щͷ��Ŀѣ������\n"NOR,me,victim);
				victim->add_busy(2+random(2));
				victim->receive_damage("jing",damage_bonus/3,me);
				victim->receive_damage("jingli",damage_bonus/6,me);
			}else {
				message_vision(CYN"$n�Ṧ�������������ܼ仯����$N�Ĺ�����\n"NOR,me,victim);
				me->add_busy(1);
				
			}
			break;
		case 4:
			if (!tweapon) break;
			
			message_vision(HIM"$Nʹ���򹷰��������־���������"+weapon->query("name")+HIM"������$n��"+tweapon->query("name")+HIM"֮�ϣ�$n�������ó����ޱȣ�\n"NOR,me,victim);
			if (random(me->query_str())>victim->query_str()/2)
			{
				message_vision(HIW"$n����Խ��Խ����Խ��Խ���ܿ��ƣ�����"+tweapon->query("name")+HIW"��$N�����ɣ����ֶ�����\n"NOR,me,victim);
				victim->add_busy(2+random(2));
				tweapon->move(environment(victim));
			}else {
				message_vision(HIY"$n������ʹ��˫��֮�䣬������ס�Լ���"+tweapon->query("name")+"�������ɣ�\n"NOR,me,victim);
				me->add_busy(1);
				
			}
			break;
	
	}
	return 1;
}

int ob_hit(object ob, object me, int damage)
{
	object wp,twp;
	string msg;
	int j, p, bj, level;
	if (!me||!ob) return 0;
	
	wp = me->query_temp("weapon");
	twp = ob->query_temp("weapon");
	level = (int)me->query_skill("dagou-bang",1);
	//ȡ��death ����
	//bj = me->query_skill("bangjue",1) + me->query("death_times",1);
	if (level<500) return 0;
	//û�������򲻳�
	if (me->query("quest/gb/dgb/bangjue/pass")) return 0;
	
	if (!wp ||wp->query("skill_type") != "stick") return 0;
	if (me->query_skill_mapped("stick")!="dagou-bang"||me->query_skill_mapped("parry") != "dagou-bang") return 0;
	
	//���Ƿ�����,��

	bj= me->query_skill("bangjue",1);
	
	if(random(level) > 100
	 && random(bj) > 100
	 && (int)me->query("neili") > 500
	 && random(level)> (int)ob->query_skill("parry",1)/2
	 && random(20) > 15) 
	{
		me->add("neili", -50);
		if(twp) {
			msg = HIM"$n"+ twp->name() +HIM"һ�и���������$Nʹ�������־�������ӰƮƮ����ʱ���Լ�\n"NOR;
			msg += HIM"��ǰ����֮�ؾ�����ס�ˡ�$n�����Ź���ʧЧ������֮�£�ֻ�к���һ�������۱仯��\n"NOR;
			
			if(!ob->is_busy())
			{
				ob->add_busy(1);
				me->add("neili",-70);
				ob->apply_condition("no_perform",2);
			}
			
			me->add("neili",-40);
			j = -damage;
		}
		else {
			msg = HIM"$n����ָ��Ҫ����$N����ͻȻֻ����Ӱ������"NOR;
			msg += HIM""+wp->name() +HIM "һ�ơ����־��������������޷���\n"NOR;
			msg += HIM"�����ѱ����ص�����һ�¡�$n��æ������������ɫб�������Ͼ�����һ���亹��\n"NOR;
			
			ob->add_busy(1);
			me->add("neili",-50);
			
			if (ob->query("max_qi")<damage) damage=ob->query("max_qi");//��ֹ����̫ǿ by renlai
			
			ob->receive_damage("qi", damage/3, me);
			ob->receive_wound("qi", damage/6, me);
			p = (int)ob->query("qi")*100/(int)ob->query("max_qi");
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			me->add("neili",-100);
			j = -damage/2;
		}
		
		message_vision(msg, me, ob);
		return j;
	}else if (random(me->query_int())>ob->query_int()/2)
	{
		//���־����öԷ��Լ�����
		
			message_vision(HIY"$N΢΢һЦ�����е�"+wp->query("name")+HIY"˳�ƴ���$n�����ϣ�$nֻ��һ�ɴ������������Ӳ���������Ϊ$N�����ƣ�\n"NOR,me,ob);
			message_vision(HIY"$N�����������������Ĵ򹷰�����"HIC"���־�"HIY"��$n��������ȫ�����Լ����ƣ�Ϊ$N������ң���ǰ����\n"NOR,me,ob);
			message_vision(HIG"��Ȼ��$N��"+wp->query("name")+HIG"������Ϊ���ɵķ�ѹ$n�ֱۣ�$n������һ�ж�ʱ�����Լ����ϣ�\n"NOR,me,ob);
			ob->set_temp("must_be_hit",1);
			//ob->add_temp("apply/damage",200);				
			COMBAT_D->do_attack(ob, ob, me->query_temp("weapon"), 3);
			//ob->add_temp("apply/damage",-200);
			ob->delete_temp("must_be_hit");
			return 0;
	}
}

int help(object me)
{
        write(HIG"\n�򹷰���"NOR"\n");
        write(@HELP
        �򹷰����а����������������������⡢ת�˾������������µ�
        ؤ�������������ᡢ�顢�桢����ƣ��轫�������Ĵ�ֻ����Ӱ
        ������Ӱ����ѧ�����Ե�����������ǧ����˴򹷰����ľ�����
        ���������֡���ϰʱ�粻ͬʱѧϰ�������ս��޷���ɡ�

HELP
        );
        return 1;
}

