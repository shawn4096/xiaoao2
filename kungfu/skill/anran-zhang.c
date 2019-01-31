// anran-zhang.c ��Ȼ������
// By River 98.10.28
// Modified by snowman@SJ 20/06/2000

#include <ansi.h>
#include <combat.h>

inherit SKILL;

#include <combat_msg.h>
mapping *action = ({
([
	"action" :"$N��Ӱ��ת������Ȱ��ǰ����˲��˲�ң�һʽ���ǻ��չȡ��Ʒ�����$n��$l",
	"lvl" : 0,
	"skill_name" : "�ǻ��չ�",
	"damage_type" : "����"
]),
([
	"action" :"$N��̾һ�����������أ�һ�С��������ġ����յ�$nȫ������֮�ʣ�����ֱ��$n��$l",
	"lvl" : 15,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([
	"action" :"$N��Ŀ��Ȼ����ֱ֫ͦ���������ۣ��ơ���ʬ���⡹�㣬���۽��ȣ���նֱ��$n��$l",
	"lvl" : 30,
	"skill_name" : "��ʬ����",
	"damage_type" : "����"
]),
([
	"action" :"$Nһʽ��ӹ�����š������ִ��أ�һ�߻��ײ�ֹ��ٿ�����Ƶ�������Ʊ���$n��$l",
	"lvl" : 45,
	"skill_name" : "ӹ������",
	"damage_type" : "����"
]),
([
	"action" :"$NͻȻͷ�½��ϣ��������ӣ��ִ����У�ֻ��һ�С�������ʩ�����������$n��$l",
	"lvl" : 60,
	"skill_name" : "������ʩ",
	"damage_type" : "����"
]),
([
	"action" :"$N���ֳ��ƣ������Ƴ�һ�С�������ʳ����$nֻ��һ��ǿ�����׵��ƹܷ��ѹ����",
	"lvl" : 75,
	"skill_name" : "������ʳ",
	"damage_type" : "����"
]),
([
	"action" : "$N���۸�����ĿԶ����һʽ������ֻӰ����$n��һ���ɣ�������Ϊ$N��������",
	"lvl" : 90,
	"skill_name" : "����ֻӰ",
	"damage_type" : "����"
]),
([
	"action" : "$N����һ�С�������������$n�����Ʒ�֮�С�$n�������ݺ��ξ��ˣ�����$N���Ʒ�ת��",
	"lvl" : 105,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([
	"action" : "ȴ��$N��������������������У�ƾ��һʽ�����񲻰�������$n���������ˣ��޷�Ӳ��",
	"lvl" : 120,
	"skill_name" : "���񲻰�",
	"damage_type" : "����"
]),
([
	"action" : "$N������$n��ǰһ����һ�С���;ĩ·������$n��ǰ���֮����ͻȻת�䣬����$n��$l",
	"lvl" : 135,
	"skill_name" : "��;ĩ·",
	"damage_type" : "����"
]),
([
	"action" : "$N����ϲŭ���֣���״�ٳ�����$n������������֮�ʣ�һ�С�������ɫ������$n��$l",
	"lvl" : 150,
	"skill_name" : "������ɫ",
	"damage_type" : "����"
]),
([
	"action" : "$N��Ȼ��Ц��ֹ�����ֵ߿�����$n���Գ�����У�$N��һʽ������Ƿǡ�����$n��$l",
	"lvl" : 165,
	"skill_name" : "����Ƿ�",
	"damage_type" : "����"
]),
([
	"action" : "ͻ��$N���λζ����ѹ���$n���ϣ�һʽ������ľ��������$n���֮ʱ������$n��$l��",
	"lvl" : 180,
	"skill_name" : "����ľ��",
	"damage_type" : "����"
]),
});

int valid_enable(string usage)
{
	if ( this_player()->query("gender")=="����")
		return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
	int skill = me->query_skill("anran-zhang", 1);
	
	if (!me->query("quest/anran/pass")) return notify_fail("�����δ�õ����ͬ�⡣\n");

	if ( me->query("max_neili") < 1500)
		return notify_fail("�������������\n");
	if ( me->query("gender")!="����")
		return notify_fail("��Ȼ����Ҫ���˲���������\n");
	if ( me->query_str(1) < 30 )
		return notify_fail("��û��ǿ���������޷�ѧ��Ȼ�����ơ�\n");

	if ( me->query_con(1) < 26 )
		return notify_fail("��û���ۺ�������޷�ѧ��Ȼ�����ơ�\n");

	if ((int)me->query_skill("force", 1) < (skill-30)
	&& (int)me->query_skill("anran-zhang", 1) < 230)
		return notify_fail("��Ļ����ڹ����̫ǳ��\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

string *xue_name = ({
HIW"�ǻ��չ�"NOR,BLU"��������"NOR,HIC"��ʬ����"NOR,HIG"ӹ������"NOR,HIY"������ʩ"NOR,
HIR"������ʳ"NOR,YEL"����ֻӰ"NOR,CYN"��������"NOR,MAG"���񲻰�"NOR,GRN"��;ĩ·"NOR,
HIM"������ɫ"NOR,RED"����Ƿ�"NOR,WHT"����ľ��"NOR,
});

mapping query_action(object me, object weapon)
{
	int i, j,n, level,tmp;
	object target;
	string msg, name;

	level = (int) me->query_skill("anran-zhang",1);
	if (!userp(me))
		tmp = 1 + random(level/20);
	else
		tmp = 1 + random(level/5);

	name = xue_name[random(sizeof(xue_name))];
	
	if( me->query("gender") != "����") tmp = tmp /3*2;

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			target = offensive_target(me);
			if(me->query_temp("arz/shengyou")){
				switch(me->query_temp("arz/shengyou")){
					case 2: msg = HIY"$N���������ң�û����ɵĻ��������ĳ�һ�ƣ�ֻ�����۵�һ������һ�����û���$n��ͷ"NOR; break;
					case 1: msg = HIR"������$N�߳�һ�š���һ�ŷ���ʱ�л��㱣�����ԼԼ���������ޡ����һ�죬��$n�ؿ�Ϯȥ"NOR; break;
					default: msg = HIC"$N���������ң�û����ɵĻ��������ĳ�һ�ƣ�ֻ�����۵�һ������һ�����û���$n��ͷ"NOR; break;
				}
				me->add_temp("arz/shengyou", -1);
				return ([
					"action":msg,
					"force" : 250+random(350),
					"dodge": random(30),
					"parry": random(20)+10,
					"damage" : 150 + random(50),
					"damage_type" : "����",
				]);
			}
			if ( me->query_temp("jishi")){
				switch(me->query_temp("jishi")){
					case 2: msg = HIY"$N��������Х����һʽ��"+xue_name[random(sizeof(xue_name))]+HIY"��ʹ���ǳ����뻯���뽫$n������Ӱ֮��"NOR; break;
					case 1: msg = HIY"$N����$n�������У�ʹ�������ѧ��"+xue_name[random(sizeof(xue_name))]+HIY"����$n��������Ӱ֮�У�����ͷ��Ŀѣ"NOR; break;
					default : msg = HIY"$N��������Х����һʽ��"+xue_name[random(sizeof(xue_name))]+HIY"��ʹ���ǳ����뻯���뽫$n������Ӱ֮��"NOR; break;
				}
				me->add_temp("jishi", -1);
				return ([
					"action": msg,
					"force" : 250+random(350),
					"dodge": random(30),
					"parry": random(20)+10,
					"damage" : 180 + random(50),
					"damage_type" : "����",
				]);
			}
			if(me->query_temp("arz/sanzhao")){
				switch(me->query_temp("arz/sanzhao")) {
					case 1 :
						msg =  HIW"$Ņͷ���죬��������������һ����ͷ���տ��ĳ�������б�£��������ɻ��Σ���ɢ����\n"NOR;
						msg += RED"���$n����һ�С�������졹���ñ�˵����������վ���Ų�Ҳ�ǲ���"NOR;
						break;
					case 2 :
						msg =  YEL"$N��������Ʈ����������ˮ������ȴ����֮�������ƴ��ż�ǧ����ɳһ��\n"NOR;
						msg += RED"���$n����һ�С������ˮ�������������ݺ��ξ��ˣ�����ײײ"NOR;
						break;
					case 3 :
						msg =  HIB"ͻȻ��$N�����붯���������䡢˫��ͷ���������ر�������������ʽ����\n"NOR;
						msg += RED"���$n����һ�С��������С���������ȫȻ�������ľ���"NOR;
						break;
				}
				return ([
					"action": msg,
					"force" : 250+random(350),
					"dodge": random(30),
					"parry": random(20)+10,
					"damage" : 250 + random(50),
					"damage_type" : "����",
				]);
			}
			if( me->query_temp("arz/qiren") && me->query("jiali")) {
				return ([
					"action" : random(2)? HIB+action[j]["action"]+NOR :MAG+action[j]["action"]+NOR,
					"force" : 350+random(350),
					"dodge": random(30)+10,
					"parry": 30,
					"damage" : 200 + random(50),
					"damage_type" : "����",
				]);
			}
			return ([
				"action" : action[j]["action"],
				"lvl" : action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force" : 200+random(350),
				"dodge": random(30)-10,
				"parry": random(20),
				"damage" : 120 + random(50),

			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("anran-zhang", 1);
	int i = sizeof(action);
	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query_temp("weapon") || (int)me->query_temp("secondary_weapon"))
		return notify_fail("����Ȼ�����Ʊ�����֡�\n");

	if ( me->query("jingli") < 50)
		return notify_fail("���������������Ȼ�����ơ�\n");

	if ( me->query("neili") < 20)
		return notify_fail("���������������Ȼ�����ơ�\n");
	

	me->receive_damage("jingli", 40);
	me->add("neili", -15 );
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"anran-zhang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int j;
	string who;
	if( damage_bonus < 100 ) return 0;
	j = me->query_skill("anran-zhang", 1);

	if ( random(10) > 6
	 && !victim->is_busy()
	 && j > 140
	 && me->query_skill_mapped("strike") == "anran-zhang"
	 && me->query_skill_prepared("strike") == "anran-zhang"
	 && me->query("neili") > 1000
	 && me->query("max_neili") > 1500
	 && random(j) > victim->query_skill("dodge",1)/2
	 //&& !me->query_temp("anran")
	 //&& !me->query_temp("jishi")
		 ) {
		victim->add_busy(1+random(2));
		me->set_temp("sanzhao", 1);
		call_out("check_fight", 5, me, victim);
	}
    //����������ɫ�����Ĵ�Ч��
	/*���������������һ�У���ʵ�м�仯���.����ϲŭ���֣���״�ٳ�������һ������
ʱ�����������ƣ���ϲ��ϲ�����ǵ��ǣ������������ҡ�������������Ӱ��ʤ��֮��������֮��Х��������ָ߳�һ����ܲ�ͨ���������Ǵ�
�����澭�����Ĵ��б仯������ô����������������ǣ���*/
	if (me->query_temp("arz/wuse")
		&& random(me->query_per(1))>(victim->query_per(1)/3)
		&& random(10)>5)
	{
		if (me->query("gender")=="����")
		{
			who="ʦ��";
			message_vision(HIY"$n����$N�ǳ����Լ�����ʱ�չ��Լ���ʦ�֣�һ��һ������Ϊ���ƣ�$n������޵�����ʦ�֣���\n"NOR,me,victim);
		}
		if (me->query("gender")=="Ů��")
		{
			who="ʦ��";
			message_vision(HIC"$n����$N�ǳ����Լ�����ʱ�չ��Լ���ʦ�㣬���ƻ�Ȼ�䣬$n������޵�����ʦ�㣡��\n"NOR,me,victim);
		}
		switch (random(3))
		{
			case 0:
				message_vision(HIY"$n��������ɫ��ʽӰ�죬�ж��������óٻ��������Ų����ģ���������\n"NOR,me,victim);
				victim->add_busy(2);
				victim->add_condition("no_exert",1);
				break;
			case 1:
				message_vision(HIR"$n�о��Լ��·�û����ʶ�����Կհף��ֺ����ڿ��зɣ�������������ɫ�԰ף���Ȼ�޷����У�\n"NOR,me,victim);
				victim->receive_damage("jing",random(1000),me);
				victim->add_condition("no_perform",1);
				break;
			case 2:
				message_vision(HIC"$n����ص��Լ�����ʱ�����Լ��ڸ���"+who+HIC"ѧϰ�似��һ��һʽ��ģ��������\n"NOR,me,victim);
				victim->add_temp("apply/damage",j/4);
				COMBAT_D->do_attack(victim, victim, me->query_temp("weapon"), 3);
				victim->add_temp("apply/damage",-j/4);
				break;		
		}
	}
}

void check_fight(object me,object victim)
{
	if(!me) return;
	if(!me->query_temp("sanzhao")) return;
	if( !victim
	 || !me->is_fighting(victim)
	 || me->query_skill_prepare("strike") != "anran-zhang"
	 || me->query_skill_mapped("strike") != "anran-zhang"
	 || me->query_temp("weapon")) {
	 	me->delete_temp("sanzhao");
		return;
	}
	call_out("check_fight", 1, me, victim);
}

int ob_hit(object ob, object me, int damage)
{
	object weapon;
	string msg;
	int ap, dp, j = 0, skill;

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 1;
	}

	if( ob->query("env/invisibility") ) return 0;

	if (me->query_skill("anran-zhang", 1) < 100
	 || me->query_skill_mapped("parry") != "anran-zhang"
	 || me->query("combat_exp") < ob->query("combat_exp")/2
	 || me->query_temp("weapon")) return 0;

	skill = me->query_skill("anran-zhang", 1);
	weapon = ob->query_temp("weapon");

	if ( me->query("neili") < ob->query("neili")/5 ) return 0;

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	if ( weapon ) ap *= 2;
	if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;

	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
	if ( me->is_busy() ) dp /= 2;
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;
	if ( userp(me) && ! userp(ob)) dp /= 2;

	ap = ABS(ap);
	dp = ABS(dp);

	if ( skill > 400 ) dp += random(dp);

	if ( random(dp + ap) > ap && ! random(5)) {
		me->set_temp("fanzhen", 1);
		if( me->query("neili") > random(ob->query("neili"))){
			if( weapon ) msg = HIY"$n����"+weapon->name()+HIY"��Ҫ����$N���ϣ�ͻ��$PС�����������ͬʱ�ؿ�����һ����ٿ�ص�����\n"NOR;
			else msg = HIY"$n��Ҫ����$N���ϣ�ͻ��$PС�����������ͬʱ�ؿ�����һ����ٿ�ص�����\n"NOR;
			ob->receive_damage("qi", damage/3 + ob->query("jiali")*2, me);
			ob->receive_wound("qi", ob->query("jiali")+1, me);
			j = (int)ob->query("qi") * 100 / (int)ob->query("max_qi");
			msg += damage_msg(damage, "����") + "( $n"+eff_status_msg(j)+" )\n";
			if( weapon ) {
				msg += "ͬʱ��$n����"+weapon->name()+"Ҳ��һ����Щ���ղ�ס��\n";
				ob->add_busy(2+random(2));
				if (random(me->query_str())>ob->query_str()/3)
				{
					msg+=weapon->name()+HIY"��$n��������˻Σ��ѳֲ�ס�������Ծ��Ǳ������ľ�������������ϡ�\n"NOR;
					weapon->move(environment(ob));
				}
			}
			j = -6000;
		}
		else {
			msg = "$N��ĿԶ���������鸡��һʽ���ľ������������ذ������ܿ�$n��������\n";
			j = -6000;
		}
	}
	else
		return 0;
	message_vision(msg, me, ob);
	return j;
}

int help(object me)
{
        write(HIB"\n��Ȼ�����ƣ�"NOR"\n\n");
        write(@HELP
        ����Ժ�С��Ů�ھ���ȶϳ���ǰ���֣����ñ����������ں���֮��������
        ����֮�󣬳����ڹ�ѭ�򽥽�֮�⣬����޿��������������ռ�˼��С��Ů��
        ����������������������Ȥ��һ���ں�����Ȼ���ã���������֮������ȭ���
        �ߣ���ʱ���ڹ�����ѵ���һ���־��߼�������������һ�ƣ�����̲��һֻ��
        ����ı��Ǵ�÷��顣���ɴ���˼��������һ���������Ʒ���������Ѱ���书
        ���죬����֮����ȫ��������һ����һʮ���С�����ƽ�ܹ�������ѧ���ҵ�ָ
        �㣬��ȫ���ѧ�����������ڹ��Ŀھ�����С��Ůѧ�á���Ů�ľ������ڹ�Ĺ
        �м����������澭����ŷ�����Ը�󡹦����ת���������߹���������Դ򹷰�
        ������ҩʦ���Ե�ָ��ͨ�����｣��������һ��ָ֮�⣬��а����������ؤ��
        ����ͨ����ѧ��������������Ĺ�ɵ���ѧ����������֮����辶����ʱ��
        ���ͨ������׿Ȼ�ɼҡ�ֻ������ʣһ�ۣ����Բ��������仯ȡʤ����������
        ����ѧͨ���෴�����������Ʒ�����Ϊ����Ȼ�����ơ���ȡ���ǽ��͡��𸳡�
        ����һ�䡰��Ȼ�����ߣ�Ψ������ӡ�֮�⡣

        Ҫ��
               ������� 1500;
               ������� 26;
               �������� 30;
               ��Ȼ������ 230 ��ǰ������Ů�ľ� 30 ����

HELP
        );
        return 1;
}
