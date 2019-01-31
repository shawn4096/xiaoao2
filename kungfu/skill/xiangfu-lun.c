// /kungfu/skill/xiangfu-lun.c
// xiangfu-lun.c ������
// dubei
// snowman(98,12,22)
// iceland(99.8.3)
#include <ansi.h>
inherit SKILL;
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
mapping *action = ({
([
	"action" : "$Nһ�С�����̾�����ơ����������ƻ��أ����ֵ�������$w�����ؿ���$n��$l",
	"skill_name" : "����̾������",
	"lvl" : 0,
	"damage_type" : "����",
]),
([
	"action" : "$N������$w���ϰ�գ�Ծ��һ������$w�ϣ����С�����������ơ���������׹�أ�ֱ��$n",
	"skill_name" : "�����������",
	"lvl" : 20,
	"damage_type" : "����",
]),
([
	"action" : "ƾ������һ��ѩ�׵Ĺ�Ļ�������˸��$wЮ���󹦵¹����ơ������Ͼ�������$N���зɳ�����$n��$l",
	"skill_name" : "�󹦵¹�����",
	"lvl" : 40,
	"damage_type" : "����",
]),
([
	"action" : "$N˫�ۿıգ�ȫ������ȴ���ھ��ĵ�������������$w���⡸���ֹ����ơ����ƶ��£���$n����ѹȥ",
	"skill_name" : "���ֹ�����",
	"lvl" : 60,
	"damage_type" : "����",
]),
([
	"action" : "$N˫��ԽתԽ������Ļٲ��һ�����£���$n���֣��⡸��������ơ��ľ�������$w����ɽ����֮�Ʒ�������",
	"skill_name" : "���������",
	"lvl" : 80,
	"damage_type" : "����",
]),
([
	"action" : "$N���и߳�����ħ�䡹��һ�С������������ơ��ӳ���$w�û����������Ӱ����������ˮ��ӿ��$n",
	"skill_name" : "������������",
	"lvl" : 100,
	"damage_type" : "����",
]),
([
	"action" : "$N���������������Ͻ�ħ�󷨴߶�������������ơ���$w����Ĺ��������ƽ�$n��",
	"skill_name" : "�����������",
	"lvl" : 120,
	"damage_type" : "����",
]),
([
	"action" : "$N��һ������������$w���·��ɣ��ַ��ҳ����⡸���ǻ۹����ơ���$n��ǰ��Ӱ���裬Ӧ�Ӳ�Ͼ��",
	"skill_name" : "���ǻ۹�����",
	"lvl" : 140,
	"damage_type" : "����",
]),
([
	"action" : "$N���΢Ц����¶�ȹ⣬ȫ����ɢ�����ġ���ȱ������ơ��������羪�κ��ˣ�$wһ����һ����ӿ��$n",
	"skill_name" : "��ȱ�������",
	"lvl" : 160,
	"damage_type" : "����",
]),
([
	"action" : "$N˫�ָ߾�$w�����һ��ʹ������Բ�������ơ����϶���ն��$n�������ޱȣ�������ӿ���Ѵ�Բ��֮��",
	"skill_name" : "��Բ��������",
	"lvl" : 180,
	"damage_type" : "����",
]),
});

string *wushuai_msg = ({
HIR"$N���ִ��ڷ�������б��һ���������ڿ��л���һ�����ߣ���$n��ȥ��������ţ��"NOR,
HIR"$N����������أ�����ǰ���һ��һ�ͣ����ֶ�Ȼ���𣬴Ӳ���˼��ĽǶ�ײ��$n"NOR,
HIR"$N����������˫�����ƣ�����ȥ�ƾ������ص�һ������$n��"NOR,
HIR"$N˫�ֻ��ţ�����$n��ǰ�������ڿ�����ת���أ�Ϯ��$n�ĺ��ԡ�"NOR,
HIR"$N������һ���Ϻȣ�����ȭӲ�������ڷ����ϣ����ַ����͵�һת��ֱ׷��$n��"NOR,
HIR"$N����Ȧת���������������ɽ������У����������󼱷�������ƽ�ƣ���������$n��ǰ�ء�"NOR,
HIR"$Nƾ���������ֶ����������ϼ������۹�ɨ��$n�����ֽ����ŷ��˹�ȥ��"NOR,
HIR"$NԾ���գ�˫�����϶����Ƴ�������ƾ�ռ��٣����ƾ��ˡ�"NOR,
HIR"$N��ǰ����������һת�������ͳ����֣������$n���ļ��ƣ���ס��$n����·��"NOR,
});

string *parry_msg = ({
HIC"$n���㲻�ܣ����з��ְڿ�����$N��ǰ�γ���һ����Ļ��$N���и����޷��ݳ���\n"NOR,
HIM"ȴ��$n̤ǰһ�������з��ַ��ɣ��������ͣ�$N�������ӣ�������ˡ�\n"NOR,
HIY"$n�ַ�ͻ�䣬���ִ��ŷ��������ȥ������������$N��û����ʱ������$N��������\n"NOR,
MAG"����$n����˫�ۣ��ٷ���Ӳ�ܣ�ƹ��һ�������������ڵ�$N��\n"NOR,
MAG"$n��׼���ƣ����ְڸ�����ƣ���$N��·������$N����ֻ����һ��͹�����ȥ�ˡ�\n"NOR,
MAG"$Nһ�����㣬�ŷ���$n���з���ָ���Լ���$l�����Ǵ��еĿ��ţ���æ�������ܡ�\n"NOR,
});

string  *msg = ({
CYN"$w"CYN"���ݷ�û�����ǧ��������費Ϣ���������Ӱ�γ���һ������ε�ͼ����ÿһ�ֵĹ��������������������"NOR,
HIY"�����Ǽ�ֻ���ֶԻ����������������Ʋ���������$nһ��֮�ʣ����ַ����˳�ȥ��"NOR,
YEL"���������У�������ת������ײ��$n����$p��Ҫ����ʱ��ȴ�ƹ����ɵ�������"NOR,
YEL"$w"YEL"�������������������ɻأ�����$n����Ȧ�ӣ����ߺ��ͣ�������б����������Ҳ���������죬�ŵ�$n�ۻ����ң����񲻶�"NOR,
YEL"һ����С���ˣ�������Ȼ�䷨�ֺ����һ��������$nײȥ��������ţ���������ɵ�"NOR,
HIC"���$n��ǰ���ɷ�Բ������һ������ķ籩���⻪��Ȼ�У����ַ��������������������"NOR,
HIG"��$w"HIG"���Ʊ˱�������һ��ľ�������$n��ǰ�����ݺᣬ�ۼ���˸����������֮�䣬��ȫ��������������"NOR,
MAG"ֻ��$w"MAG"������������������$n���·��ɣ��Ƶ����������絶���Ҫ��$n��������"NOR,
YEL"ͻȻ����������������$w"YEL"������ײ�����ֹ�һ���ϲ�����$n��ȥ"NOR,
HIM"�����ٴκ�Χ���ϵ羫âΧ��$n�������������䣬ǧ����Ӱ��ӳ��һ��������ѣĿ��ͼ��������һƬ����ε���ɫѩ����"NOR,
YEL"������$n��ǰ���ģ��͵���$pӭͷ���£������ַ���һ�֣�һ��һ�ͣ��������죬����$n$l"NOR,
YEL"������Х���У��Ǽ�ֻ���ֻ�ֱ�ɡ���б�ɡ������������׹������������ʱ��$n��ȫ����·�ѱ�����"NOR,
BLU"�͵���$w"BLU"��$n$l�����£���$p����ж��֮ʱ��������ͻȻ�Ϸɻ���������$p��$l"NOR,
YEL"�Ƿ��ַ����ҵ���$nȴ������ͷ�����������һһ�����������ֱ��糤�����۾�һ�㣬��Ȼ�����ɵ���$n$l"NOR,
HIY"����$N������$w"HIY"��������ζ��������������죬ҫĿ�ĵ���������������������⣬Ѹ����ƥ�Ļ���$n"NOR,
});

string  *msga = ({
HIY"$N���ִ��ڷ�������б��һ���������ڿ��л���һ�����ߣ���$n��ȥ��\n"NOR,
HIC"$N����������أ�����ǰ���һ��һ�ͣ����ֶ�Ȼ����ײ��$n�ġ�\n"NOR,
BLU"$N����������˫�����ƣ�����ȥ�ƾ������ص�һ������$n��\n"NOR,
HIY"$N˫�ֻ��ţ�����$n��ǰ�������ڿ�����ת���أ�Ϯ��$n�ĺ��ԡ�\n"NOR,
HIY"$N����Ȧת���������������ɽ������У����������󼱷�������ƽ�ƣ���������$n��ǰ�ء�\n"NOR,
HIY"$NԾ���գ�˫�����϶����Ƴ�������ƾ�ռ��٣����ƾ��ˡ�\n"NOR,
HIW"$N��ǰ����������һת�������ͳ����֣������$n���ļ��ƣ���ס��$n����·��\n"NOR,
});

string  *msgd = ({
HIC"$n��������ת�漲������ֻ�����絶������æһ���Ծ�𣬷��ֺ��Ĵӽ��·ɹ���\n\n"NOR,
HIC"$n���Ų�æ�������ݰ㼱ת�˸�Ȧ�����˿�����\n\n"NOR,
HIC"$n���ֲ�����Σ����������ͷ�����ָպô�ͷ���ɹ���\n\n"NOR,
HIC"$nһ���෭�������ڿ��к����ȥ���ܹ���������һ����\n\n"NOR,
HIC"$n�������֮�⣬����֮��ֻ�ù����ڵأ���Щδ�ܱܹ���\n\n"NOR,
HIC"$n��׼���ƣ�˫��һ��һ�֣������ֵ��˿�ȥ��\n\n"NOR,
HIC"$n���˼�����š��һ�������������˿�ȥ��\n\n"NOR,
HIC"$n˫�������������ģ����ֱ�����ʧ��׼ͷ����$n���Է��˹�ȥ��\n\n"NOR,
});
int valid_enable(string usage) { return usage == "hammer" || usage == "parry"; }

void skill_improved(object me)
{
	int skill = me->query_skill("xiangfu-lun", 1);
	if( skill >= 200 && !me->query("ryl_add")){
		me->set("ryl_add", 1);   
		tell_object(me, HIW"\n��Ȼ����е���ϢԽתԽ�죬˲ʱ�����Ѿ���������һ���µľ��磡"NOR);
		me->add("max_jingli", skill/2+random(skill));
		me->add("max_neili", skill/2+random(skill));
	}
}

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon")) || ((string)weapon->query("skill_type") != "hammer") && ((string)weapon->query("skill_type") != "lun"))
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if( me->query_str(1) <=35)
		return notify_fail("��ı�������ѧ�����֡�\n");
	if( me->query("max_neili") < 2000)
		return notify_fail("�������������\n");
	if( me->query_skill("longxiang-boruo", 1) <= 160)
		return notify_fail("��Ҫ�еڰ˲�����������������,����ѧ�����֡�\n");
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
	int i, level, j;
	level = (int) me->query_skill("xiangfu-lun",1);
    //npc ֻ��������ʽ������û��Ҫ
	
	if( !userp(me)
	 && me->query("env/invisibility")
	 && me->query("master_user/user")){
		return ([
			"action": msg[random(sizeof(msg))],
			"damage": 200+random(100),
			"damage_type":random(2)?"����":"����",
			"dodge": 5,
			"force": 250+random(250)
		]);
	}
	//��˥��pfm
	/*
	if(me->query_temp("xfl/wushuai")) {
	   for(i = sizeof(wushuai_msg); i > 0; i--) {
		if(level > wushuai_msg[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
                    return ([
                            "action": wushuai_msg[random(sizeof(wushuai_msg))],
                            "damage_type":random(2)?"����":"����",
                            "dodge":random(25),
                            "force":250+random(100),
                            "parry":random(30),
                            "damage":250+random(100),
                            ]);
	    }
	   }
	}*/
     if(me->query_temp("xfl/wushuai")) {
	   
                    return ([
                            "action": wushuai_msg[random(sizeof(wushuai_msg))],
                            "damage_type":random(2)?"����":"����",
                            "dodge":random(25),
                            "force":250+random(100),
                            "parry":random(30),
                            "damage":250+random(100),
                            ]);
	    
	   }
	//����˥
	return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":200+random(350),
				"dodge":random(30)-10,
				"damage":180+random(50),
				"parry":random(20),
			]);
	
}

mixed query_parry_msg(object weapon, object me, int attack_type)
{
	if (objectp(weapon = me->query_temp("weapon")) 
	&& (((string)weapon->query("skill_type") == "hammer") || ((string)weapon->query("skill_type") == "lun"))  //|| ((string)weapon->query("skill_type") == "lun")
	&& me->query_skill_mapped("hammer") == "xiangfu-lun"
	&& me->query_skill_mapped("parry") == "xiangfu-lun")
		return parry_msg[random(sizeof(parry_msg))];
}

int practice_skill(object me)
{
	int lvl = me->query_skill("xiangfu-lun", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if ( me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ( me->query("neili") < 20)
		return notify_fail("������ڵ���������,�޷������������֡�\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xiangfu-lun/" + action;
}


mixed hit_ob(object me, object victim,int damage)
{
	object wp1, wp2; 
	string msg;
	int p, lx=me->query("lx/gree");
    damage = (int)me->query_skill("xiangfu-lun",1) + (int)me->query_skill("longxiang-boruo",1)/2; 
	wp1 = me->query_temp("weapon");
    wp2= victim->query_temp("weapon");
	//if( !objectp(wp2= victim->query_temp("weapon")) )
   // if( !objectp(wp1)||wp1->query("type")!="hammer" )
		//return;
            
	if( me->query_skill("longxiang-boruo",1)<350
        ||  me->query_skill("xiangfu-lun", 1) < 350 
	    || !me->query("jiali")
	    || me->query("neili") < 1000 
		|| me->query_skill_mapped("force")!="longxiang-boruo"
	    || me->query_skill_mapped("parry") != "xiangfu-lun" )
		return;

	if (me->query("env/��")
		&& wp2 
		&& random(me->query("combat_exp")) > victim->query("combat_exp")/ 2 )

    {
		message_vision(HIC"$N�ֱ۱�����ʩչ�������־���"+wp1->name()+HIC"̽�������һ����ס��$n"+wp2->name()+HIC"��\n"NOR, me,victim);
		if( random(me->query_str(1)) > victim->query_str(1) ) {
			me->add("neili", -150);
			message_vision(HIR+me->query("name")+HIR"�˾�������ֻ����$N�۹ǿ���һ������Щ�ͱ����ϣ�$N��ʹ֮����һ�ɣ�"+wp2->name()+HIR"�����˹�ȥ���ڵ��ϣ�\n"NOR, victim);
			wp2->unequip();
			wp2->move(environment(victim));
            victim->start_busy(2+random(2)); 
		}
		else if(random(me->query_str(1)) > victim->query_str(1)/3*2){           
			me->add("neili", -50);
			message_vision(HIR+me->query("name")+HIR"�˾�������$N���������ļ������������ھ�ʹ����Ѫ�ɽ���"+wp2->name()+HIR"���ַɳ���\n"NOR, victim);
			victim->receive_wound("qi",victim->query_str(1)*me->query_skill("xiangfu-lun", 1)/3,me);
			victim->receive_damage("qi",victim->query_str(1)*me->query_skill("xiangfu-lun", 1),me);
			victim->apply_condition("no_perform",1+random(2));
			wp2->unequip();
			wp2->move(environment(victim));
		}
		else if( me->query_temp("shield") ){           
			me->add("neili", -50);
			message_vision(HIY"$N����ǰ�壬"+wp2->name()+HIY"ֱ�̹�ȥ������"+me->query("name")+"�����������û��˿�ȥ��\n"NOR, victim);
		}
		//else message_vision(HIY"$N����ǰ�壬"+wp2->name()+HIY"ֱ��"+me->query("name")+"��"+me->query("name")+"������죬"+wp1->name()+HIY"һ�����ѣ��������˿�ȥ��\n"NOR, victim);
	}
  
    if (me->query("quest/wulun/pass")&&random(10)>5)
	{

	    switch(random(5)) {
                         case 0:
                                //msg=msga[random(sizeof(msga))];
						        message_vision(HBRED"$N�����������Ȼ������ƾ���������ֶ����������ϼ������۹�ɨ��$n�����ֽ����ŷ��˹�ȥ��\n"NOR,me,victim);
                                if (random(me->query_skill("hammer",1)) > random(victim->query_skill("parry",1) /3) ) {
                                        
                                        damage = damage*lx/7 + random(damage);
                                        message_vision(YEL"$nһ��С��Ϊ������ת�ķ��ֱ߳������ˣ�һ���ʹ��������ʱ��Ѫ�ɽ���\n"NOR,me,victim);
										if( victim->query("qi")> 0)
                                        {  
                                             victim->receive_damage("qi", damage,me);
                                             victim->receive_wound("qi", damage/3,me);
                                        }
                                        me->add("neili", -200);
                                        me->add("jingli", -100);
                                       // p = (int)victim->query("qi")*100/(int)victim->query("max_qi");
                                        //msg += damage_msg(damage, "����");
                                      //  msg += "( $n"+eff_status_msg(p)+" )\n";
                                     //   if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("1-hit:damage:%d   ",damage));
                                        
                                }
                                else {
                                        me->add("neili", -100);
                                        //msg += msgd[random(sizeof(msgd))];
                                }
                               // message_vision(msg, me, victim);
                                break;
                    
                         case 1:
                                me->add_temp("apply/damage", me->query_skill("xiangfu-lun",1)/6 );
                                //msg=msga[random(sizeof(msga))];
								message_vision(HBRED"$N������һ���Ϻȣ�����ȭӲ�������ڷ����ϣ����ַ����͵�һת��ֱ׷��$n��ȥ��\n"NOR,me,victim);
                                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);                                
                                me->add_temp("apply/damage", -me->query_skill("xiangfu-lun",1)/6  ); 
                                me->add("neili", -100);
                                me->add("jingli", -50);
                                break;
                         case 2:
                                //msg=msga[random(sizeof(msga))];
                                message_vision(HIB"$N������������������в��������дʣ��ƺ���һ���󳪣�������Χ�Ŀ����������졣\n"NOR,me,victim);
                                if (random(me->query("combat_exp")) > random(victim->query("combat_exp") /3) ) {
                                        //damage = (int)me->query_skill("xiangfu-lun",1) + (int)me->query_skill("longxiang-boruo",1);
                                        damage = damage/2 + random(damage);
										damage=damage/3;
										message_vision(RED"$n��û�������������һʱ���飬����һ����ҵ�ͷ�۴�����\n"NOR,me,victim);
                                        if( victim->query("neili")> 0)
                                        {  
                                             victim->add("neili", -damage);
                                             victim->receive_wound("jing",random(500),me);
                                        }
                                        me->add("neili", -200);
                                        me->add("jingli", -100);
                                       
                                }
                                else {
                                        me->add("neili", -150);
										message_vision(HIC"$n���鼫��ḻ��������$n����ͼ����Цһ�����˹���˫�����Σ�˿����Ϊ��Ӱ�졣\n"NOR,me,victim);
                                        //msg += msgd[random(sizeof(msgd))];
                                }
                                //message_vision(msg, me, victim);
                                break;
                        case 3:
                                me->add_temp("apply/hammer", me->query_skill("force",1)/5); 
                                me->add_temp("apply/damage", me->query_skill("xiangfu-lun",1)/6  ); 
                                message_vision(HBBLU"$N���䲻���������ٷɻص���������ٴ������ɳ�������һ������һ�㣬���ǡ����ַ�ת��������\n"NOR,me);
								victim->add_busy(1+random(1));
								COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
                                me->add_temp("apply/damage", -me->query_skill("xiangfu-lun",1)/6 ); 
                                me->add_temp("apply/hammer", -me->query_skill("force",1)/5 ); 
                                me->add("neili", -100);
                                me->add("jingli", -50);
                                break;
                       case 4:
                                msg=msga[random(sizeof(msga))];
                                if ( random(me->query_con()+me->query_str())*3 > victim->query_dex() ) {
                                        msg+=HIY"��ֻ�����ڿ����������죬��������������󳪾�����$n�о�һ�����ƣ�ͷ�����ѡ�\n"NOR;
                                        damage = damage+ random(damage);
										damage=damage/4;
                                        if( victim->query("jingli")> 1000)
                                        {  
                                             msg+=HIR"$n���Ժ��лص���һ����һ����󳪣��ƺ���С�������Ķ����Ͽ��ڣ���Ȼ��������\n"NOR;
											 victim->add("jingli", -random(1000));
                                            
                                        }
                                        me->add("neili", -400);
                                        me->add("jingli", -100);
                                     
                                }
                                else {
                                        me->add("neili", -150);
                                        msg += msgd[random(sizeof(msgd))];
                                }
                                message_vision(msg, me, victim);
                                break; 
                
				//return 1;
		}
	  }

}
