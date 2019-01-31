// qishang-quan.c ����ȭ
// Modifed damage by snowman@SJ 22/08/2000

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N�ڳ��б��ߣ����ּȿ��Һݣ��������죬һȭ��׼��$n���ϵ�$lֱ������",
	"lvl" : 0,
	"damage_type" : "����"
]),
([
	"action" : "$N������֮��������һ������$n�ֱۣ��������һȭ���ѽ��ʵʵ����$n$l",
	"lvl" : 20,
	"damage_type" : "����"
]),
([
	"action" : "$N��$n����˵������Ȼ��ȭ��ȥ��ֻ�����һ�����죬��һ�������Ǵ���$n$l��",
	"lvl" : 40,
	"damage_type" : "����"
]),
([
	"action" : "$Nȭ����磬���������ȭ��������$n���ϣ���ȴ�Ʋ���ʹ�������������壬��˿����",
	"lvl" : 60,
	"damage_type" : "����"
]),
([
	"action" : "$N˫Ŀ���࣬һ��ߺ�ȣ�����ƾ�մ��˸��������������У�һȭֱ������$n��$l֮��",
	"lvl" : 80,
	"damage_type" : "����"
]),
([
	"action" : "$N���˼�������������һ�����ֱ۹Ǹ�����죬��������һ����һȭ����$n$l",
	"lvl" : 100,
	"damage_type" : "����"
]),
([
	"action" : "$Nһȭ�����������ֱۣ��ַ�ȭ������һ����������ת��������ǰ��ͦȭ�ͻ�",
	"lvl" : 120,
	"damage_type" : "����"
]),
([
	"action" : "$N˫��һ��һ�ȭ����п�ɽ������һ���������ڣ�ֱ����$n��$n�ؿ�һ����ֻ��������Ż",
	"lvl" : 140,
	"damage_type" : "����"
]),
([
	"action" : "$N���һ����˫ȭ�������������δ��ȭ�ϰ�������ŭ�����࣬��Х���Ϯ��$n",
	"lvl" : 160,
	"damage_type" : "����"
]),
([
	"action" : "$N˫Ŀ΢�أ�����Ʈ������ƮƮ������ȭ��ȴ�ǰ����ϢҲ�ޣ�$n��ز��΢����壬ȭ��������Ϯ�����",
	"lvl" : 180,
	"damage_type" : "����"
]),
});

string  *msg = ({
"$Nһȭ������ȭ���о����и������ֲ�ͬ�ľ������ֻ�$n��ȫ��������ʮ����ҪѨ",
"$N����һ��������˫ȭƽ�죬����������������ȭ���������ֲ�֮ͬ������$n��$l",
"$NĬ���񹦣�˫ȭ�����޶���ͻȻ�ڿ����г������ֲ�ͬ�ľ�����Ȼ����$n��ǰ��",
"$N��ȭһ�գ�Ĭ����Ϣ�����ֲ�ͬ�������Ŵ����ȭ���ֵ��ֿ�Ļ���$n��$l",
"$Nȭ����磬���������ȭ��������$n���ϣ���ȴ�Ʋ���ʹ�������������壬��˿����",
"ֻ��$N˫Ŀ��������������Ȼ���͵Ĵ����һ�����������£��������ޱ�֮��������$n��ȫ��",
"$Nһ����Х��˫Ŀ��죬ȭ·�󿪴��أ�ÿһȭ������������ŭ��ʯ���쾪���Ժ������ڼ������Ĵ�����",
"$N�����ŵڶ�ȭ�ֳ�������Ѹ�����磬��Ŀ�������·���ε�һ�Σ�ȴֱ��$nǰ��",
});

int valid_enable(string usage) { return  usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ȭ������֡�\n");
	if ( !me->query_skill("jiuyang-shengong"))
	if ( me->query_skill("shenghuo-shengong", 1) < 100)
                return notify_fail("���ʥ���񹦻�򲻹����޷�ѧ����ȭ��\n");
	if ( me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷�������ȭ��\n");
	if (!me->query("xie_qishang") && me->query_skill("qishang-quan", 1) > 50)
		return notify_fail("��û��ѧ��"HIR"����ȭ��"NOR"���޷��ټ�����ϰ����ȭ��\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i,j, level, neili, force, jiuyang;
	string msgs;
        
	level   = (int) me->query_skill("qishang-quan", 1);
	jiuyang = me->query_skill("jiuyang-shengong", 1);
	force = me->query_skill("force");
	neili = me->query("neili");
	me->delete_temp("qishang_hit", 1);
    //�������죬��ͨ����
	if (level > 100 
	 && force > 150 
	 && neili > 500 
	 && random(jiuyang) > 50
	 && me->query("max_neili") > 1200
	 && me->query("jiali") > 100
	 && random(me->query_str(1)) > 15
	 && !me->query_temp("qsq/duanhun")){
		me->set_temp("qishang_hit", 1);
		return([      
			"action": msg[random(sizeof(msg))],
			"force" : 350 + random(250),
			"dodge" : random(30),
			"force" : random(30),
			"damage_type" : random(2)?"����":"����",
		]);
	}
	// ������Ǭ����Ų�ƽ��ܺ����
	if( intp(j = me->query_temp("qsq/duanhun")) && j > 0 ){
		switch(j) {
			case 7: msgs =HIR"$Nȭ����磬���������ȭ��������$n���ϣ���ȴ�Ʋ���ʹ�������������壬��˿����"NOR;break;
			case 6: msgs =HIR"$N�����ھ�������۰��پ�����ȭȭ���磬ÿһȭ�Ժ������ڼ������Ĵ�����"NOR; break;
			case 5: msgs =HIR"$N˫Ŀ��������������Ȼ���͵Ĵ����һ�����������ޱ�֮��������$n��ȫ��"NOR; break;
			case 4: msgs =HIR"$Nһȭ������ȭ���о����и������ֲ�ͬ�ľ������ֻ�$n��ȫ��������ʮ����ҪѨ"NOR;break;
			case 3: msgs =HIR"$Nһ����Х��˫Ŀ��죬ȭ·�󿪴��أ�ÿһȭ������������ŭ��ʯ���쾪"NOR ;break;
			case 2: msgs =HIR"$N���һ����˫ȭ�������������δ��ȭ�ϰ�������ŭ�����࣬��Х���Ϯ��$n"NOR;break;
			case 1: msgs =HIR"$N˫Ŀ΢�أ�����Ʈ������ƮƮ������ȭ��$n��ز��΢����壬ȭ��������Ϯ�����"NOR;break;
			default:msgs =HIR"$N˫Ŀ��������������Ȼ���͵Ĵ����һ�����������ޱ�֮��������$n��ȫ��"NOR; break;
		}
		if( me->query_temp("qsq/duanhun") > 0 )
			me->add_temp("qsq/duanhun", -1);
		return ([
			"action": msgs,
			"damage_type" : "����",
			"dodge": random(30),
			"parry": random(30),
			"force": 250 + random(350),
			"damage": 100 + random(100),
		]);
	}
	//��ͨ����
	for(i = sizeof(action); i > 0; i--){
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 +random(300),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("qishang-quan", 1);
	int i = sizeof(action);
	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("�����������������ȭ��\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"qishang-quan/" + action;
}

void skill_improved(object me)
{
	object *ob;
	int i, skill;
	skill = me->query_skill("qishang-quan", 1);
	if(me->query("max_neili") < skill * 15 && skill < 200){
		switch(random(5)){
			case 0 : 
				tell_object(me, HIR"���ͷ����ѨͻȻһ����΢��ʹ���Ƿ������ˣ�\n"NOR);
				me->add("max_neili", -(3+random(10)));
				break;      
			case 1 : 
				tell_object(me, HIR"����������ѨͻȻ��ʹ�ѵ����Ǹ������ˣ�\n"NOR);
				me->add("combat_exp", -(2500+random(4000)) );
				break;
			case 2 : 
				message_vision(HIR"$N�������ˣ�ͻȻ���Դ󷢡��޷������ˣ�\n"NOR, me);
				ob = all_inventory(environment(me));
				for(i=0; i<sizeof(ob); i++) {
					if( ob[i]== me ) continue;
					if(!ob[i]->is_killing(me) ) ob[i]->kill_ob(me);
				}
				break;
			case 3 : 
				tell_object(me, HIR"���ϱ�����ѨͻȻһʱ�����ѵ������������ˣ�\n"NOR);
				me->add("max_jingli", -(30+random(70)));
				break;
			case 4 : 
				tell_object(me, HIR"��ͻȻ�������������������н�ľˮ�������У��޷������ˣ�\n"NOR);
				me->set_skill("qishang-quan", skill-(2+random(3)));
				break;
		}
		me->unconcious();
	}
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	string msg;
	int lvl, i,damage;
        

	lvl= me->query_skill("qishang-quan", 1);
	i = 1;
    damage=lvl+me->query_skill("force",1)+me->query_skill("cuff",1);
	damage*=2;
	damage=damage+random(damage/2);
	
	
	if( random(10) > 7
	&& lvl >= 500
	&& me->query_temp("qsq/qishang") //�����ܾ�����Ч
	&& (me->query("mj/jiuyang/pass")>2||me->query("mjqkdny/pass"))         //���˶ϻ�ſ�
	&& me->query("neili") > victim->query("neili")/3*2
	&& me->query("neili") > 1000
	&& me->query("combat_exp") > victim->query("combat_exp") /2
	&& me->query("jiali") > 100
	&& random(me->query_str())>victim->query_dex()/3
	&&(me->query_skill("jiuyang-shengong", 1)||me->query_skill("qiankun-danuoyi",1)))
	{
			 me->add("neili", -50);
		switch(random(7))
		{
			case 0 :
				message_vision(MAG"$N��������ʹ������ȭ�ܾ��еġ�"HIR"���ľ�"MAG"����˫ȭһ�ɸ���֮����$n�����ѻ�ȥ��\n"NOR,me,victim);
				victim->add_condition("qishang_poison",1);
				
				if (me->query("mjqkdny/pass")&&me->query_skill_mapped("parry")=="qiankun-danuoyi")
				{
					message_vision(HIY"\n$NǬ����Ų���񹦵ľ�������������ȭ�ϣ���ʱ�������ȡ�$n�ٸ��Լ���������\n"NOR,me,victim);
                    victim->receive_damage("qi", damage,me);
				}
				if (me->query("mj/jiuyang/pass")=="3"&& me->query_skill_mapped("force")=="jiuyang-shengong")
				{
					message_vision(HIR"\n$N�ľ����񹦷���������ȭ������������$n�ٸ��Լ�������Ϊ����\n"NOR,me,victim);
                    victim->receive_wound("qi", damage,me);					
				}				
				break;
			case 1 :
				message_vision(HIB"$N����һ��������ȭ��ʹ������ȭ�ܾ��еġ�"HIR"�˷ξ�"HIB"����˫ȭƮ��������$n��ʱ�о�һ������֮��ӭ�������\n"NOR,me,victim);
				victim->receive_damage("jing", damage/2,me);
				victim->receive_wound("jing", damage/5,me);
				break;
			case 2 :
				message_vision(HIC"$N��ȭ����ʹ������ȭ�ܾ��еġ�"HIR"�ݸγ���"HIC"����˫ȭ�������ᣬ��$n��ȥ��\n"NOR,me,victim);
				victim->add("jingli", -lvl);
                
				if (me->query("mjqkdny/pass")&&me->query_skill_mapped("parry")=="qiankun-danuoyi")
				{
					message_vision(HIC"\n$NǬ����Ų���񹦷������ɸջ��ᣬ������$n�ĸ���,����һ���ʹ��\n"NOR,me,victim);
                    victim->receive_damage("neili", damage/4);
				}
				if (me->query("mj/jiuyang/pass")=="3" && me->query_skill_mapped("force")=="jiuyang-shengong")
				{
					message_vision(BLU"\n$N������Ȼ��ɣ�$N��Ȼ��������ȭ��Ҫ��ȭ�ƶ�Ȼ��ǿ,$n��ʱ�о��Լ��γ�����\n"NOR,me,victim);
                    victim->add("max_neili",-random(10));
				}
				break;
			case 3 :
				message_vision(HIG"$N��������ʹ������ȭ�ܾ��еġ�"HIR"�����"HIG"����˫ȭ�����иգ����һ������֮������$n��ȥ��\n"NOR,me,victim);
				victim->add("neili", -lvl*2);
				victim->receive_wound("qi",damage/2,me);
				if( victim->query("neili") < 0) 
					victim->set("neili", 0);
				break;
			case 4 :
			    message_vision(HIY"$N��������ʹ������ȭ�ܾ��еġ�"HIR"��ʧ��"HIY"����˫ȭ����������������ֱ��$n������������ȥ��\n"NOR,me,victim);
				if( !victim->is_busy())
				{
					victim->add_busy(2 + random(2));
				    victim->receive_damage("jingli", lvl,me);
					victim->receive_damage("jing", lvl,me);
				}
				else
					{
						victim->add_temp("lost_attack", 2);
						victim->receive_damage("jingli", lvl);
					}
				break;
			case 5:
				message_vision(HIM"$N��������ʹ������ȭ�ܾ��еġ�"HIR"���㱾�"HIM"������$n�ͳ�һ�ɺᾢ��\n"NOR,me,victim);
			    
				if (me->query("mjqkdny/pass")&&me->query_skill_mapped("parry")=="qiankun-danuoyi")
				{
					message_vision(HIB"\n$NǬ����Ų�������������˴�˲��ת�����ƿ�$n�ķ�������ʱ���ơ�\n"NOR,me,victim);
                    victim->apply_condition("no_exert", 1+random(2));
					victim->apply_condition("no_perform", 1+random(2));
				}
				if (me->query("mj/jiuyang/pass")=="3" && me->query_skill_mapped("force")=="jiuyang-shengong")
				{
					message_vision(HIR"\n$N�ľ����񹦾�����ӿ��$n�����Լ��·������һ������¯��һ������ʱ�������������ķ����\n"NOR,me,victim);
                    victim->add_condition("no_exert", 2);
				}							
				
				break;
			case 6:
				message_vision(HIR"$N���һ�����뷢���ţ�ʹ���������ܾ���������˫ȭ����������������ٱ������$n��\n"NOR,me,victim);
				message_vision(HIW"$nֻ����$N��һȭ֮�й����߹ɲ�ͬ��������ðٶˣ���ԥ���ѱ������������ȫ��\n"NOR,me,victim);
		        victim->add_condition("no_exert", 1+random(2));
				victim->add_condition("no_perform", 2);
				victim->add_temp("lost_attack", 2);


				break;
		}
		
	}
}
