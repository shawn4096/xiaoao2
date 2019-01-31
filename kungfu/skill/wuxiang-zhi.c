/* 
   wuxiang-zhi.c �����ָ
   �������޺�ȭ(luohan-quan)����
   ȡ�Է�ʮ���֡�����ǻۣ����磬�Ժ���ӱ��Բ������
   2/3/98 by snowman
*/

#include <ansi.h>
inherit SKILL;
#include <skill.h>
#include "/kungfu/skill/eff_msg.h";
string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
"ӿȪѨ","��׶Ѩ","�縮Ѩ",
});
mapping *action = ({
([
	"action" : "$N��˫��£������֮�У�һ�С��������١�����������������ӿ��������$n",
	"weapon" : "ָ��",
	"lvl"   : 0,
	"skill_name" : "��������" ,           
	"damage_type" : "����"
]),
([
	"action" : "$N΢΢һЦ��һ�С��ǻ�����١����������ڣ�ָ�����������������ĥ��͸���޷����",
	"weapon" : "ָ��",
	"lvl"   : 10,
	"skill_name" : "�ǻ������" ,           
	"damage_type" : "����"
]),
([
	"action" : "$N����վ����˿������������$n��ǰ���һ������������������С���������١�",
	"weapon" : "����ָ��",
	"lvl"   : 30,
	"skill_name" : "���������" ,           
	"damage_type" : "����"
]),
([
	"action" : "$Ņͷ���죬һָ���Ժ�����١���Ϯ$n$l������ȴ��˿���������������·���һ��",
	"weapon" : "ָ��",
	"lvl"   : 60,
	"skill_name" : "�Ժ������" ,           
	"damage_type" : "����"
]),
([
	"action" : "$Nһ�С�ӱ������١���$n������ŵ�һ�ƿ�֮����ȴ��$P΢Ц��ͷ��ȴ�����κζ���",
	"weapon" : "ָ��",
	"lvl"   : 100,
	"skill_name" : "ӱ�������" ,           
	"damage_type" : "����"
]),
([
	"action" : "��������������$n��ɫͻ�䣬$Nȴ�������ڣ����޶����ֵļ�������������С�Բ������١�",
	"weapon" : "ָ��",
	"lvl"   : 200,
	"skill_name" : "Բ�������" ,           
	"damage_type" : "����"
]),
});

int valid_enable(string usage)
{
	if ( this_player()->query("quest/sl/wxjz")!="pass")
		return usage=="finger" ||  usage=="parry"; 
}

int valid_combine(string combo)
{
	if(this_player()->query_skill("wuxiang-zhi", 1) >= 200
	&& this_player()->query_skill("luohan-quan",1) >= 200
	&& this_player()->query_con(1) > 45
	&& this_player()->query_int(1) > 45)
		return combo=="luohan-quan";
}

int valid_learn(object me)
{
	if (!me->query("wxz/done")) 
		return notify_fail("��ͻȻ�о��Լ�����ԪѨ�����е���ľ������һ���ľ���\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ָ������֡�\n");
	if ( me->query_skill("yijin-jing", 1) < 180)
		return notify_fail("����׽�ڹ���򲻹����޷�ѧ�����ָ��\n");
	if ( me->query("max_neili") < 3000 )
		return notify_fail("�������̫�����޷��������ָ��\n");
	if ( me->query_skill("wuxiang-zhi",1) < 200)
		return notify_fail("��������ָ��Ϊ������Ŀǰ���޷�������ϰ��\n");
	if ((int)me->query_int(1) < 50)
        return notify_fail("��ĺ������Բ���50��Ŀǰ���޷�������ϰ��\n");;
	
	if ( me->query_skill("mohe-zhi", 1) < 160)
	//|| me->query_skill("nianhua-zhi", 1) < 160
	//|| me->query_skill("yizhi-chan", 1) < 160 
		return notify_fail("��Ħڭָ���Ż���ָ����δ���գ��޷�ѧϰ�����ָ��\n");
	return 1;
}

void skill_improved(object me)
{
	int skill;
	int neili=me->query("max_neili");
	int poison;

	skill = me->query_skill("wuxiang-zhi", 1);
	if( skill<=100 && skill%20==0 && me->query("wxz/improve")<skill ) {
		tell_object(me, HIG"������һ�󣬲�������������Щ���ҡ�\n"NOR);
		tell_object(me,"��������ķ��˲��ˡ�\n");
		me->set_skill("buddhism",me->query_skill("buddhism",1)-1);
		me->set("wxz/improve",skill);
		return;
	}
	if( skill>100 && skill<=150 && skill%10==0 && me->query("wxz/improve")<skill ) {
		tell_object(me, HIG"���Ȼ������Щ��˼����������վ��������\n"NOR);
		me->set_skill("buddhism",me->query_skill("buddhism",1)-1);
		tell_object(me,"��������ķ��˲��ˡ�\n");
		me->set("wxz/improve",skill);
		return;
	}
	if( skill>150 && skill<=200 && skill%5==0 && me->query("wxz/improve")<skill ) {
		tell_object(me, HIG"���ķ����ң��������ĵ�����һ��ɱ����\n"NOR);
		me->set_skill("buddhism",me->query_skill("buddhism",1)-1);
		tell_object(me,"��������ķ��˲��ˡ�\n");
		me->set("wxz/improve",skill);
		return;
	}

	if( skill > 200 ) me->add("wxz/poison",skill+random(skill));
	else return;
	poison=me->query("wxz/poison");

	if (neili/poison>=10) tell_object(me, HIG"��ͻȻ�о��Լ�С���ϡ����š�����̫�ҡ���Ѩ������ʹ��\n"NOR);
	else if(neili/poison>=5) tell_object(me, HIG"��ͻȻ�о��Լ�����ԪѨ�����е���ľ������һ���ľ���\n"NOR);
	else if(neili/poison>=2) {
		tell_object(me, HIG"��ͻȻ�о��Լ����ס���Ȫ���縮����Ѩ�����������ܴ̣�ʹ���ɵ���\n"NOR);
		me->unconcious();
	} else if(neili/poison==1) {
		tell_object(me, HIG"��ͻȻ�о�������Ϣ�Ҵܣ��޷����ƣ���ǰһ�ڣ��赹�ڵء�\n"NOR);
		me->add("max_neili", -skill/2);
		me->set_skill("force",me->query_skill("force",1)-1);
		me->set_skill("yijin-jing",me->query_skill("yijin-jing",1)-1);
		me->unconcious();
	} else if(neili/poison==0) {
		tell_object(me, HIG"��ͻȻ�о�������Ϣ���ȣ����ˮ�㵽�������Ҵܣ�������ǰһ�ڣ����ڵ��ϡ�\n"NOR);

		me->die();
                log_file("skills/wxjz",sprintf("%s(%s)��������پ�����϶�����\n", me->query("name"),getuid(me)), me);
		message("channel:chat",	HIC"���������š�"+ me->query("name") +"��Ϊǿ�������书��������϶�����\n" NOR,users());
	}
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	string name,msg;
	level   = (int) me->query_skill("wuxiang-zhi",1);
	
	name= xue_name[random(sizeof(xue_name))];
	if (me->query_temp("wxz_wuxiang")){
		switch(me->query_temp("wxz_wuxiang")){
			case 6: msg = HIB"$N��ǰһ����������ʽ���̺��������١�����ʵ���⡣ֱϮ$nǰ�ء�"+HIC+name+NOR+HIB"��"NOR; break;
			case 5: msg = HIC"$N�ڶ�ʽ��꼻�����$n�پ���ǰ����꼻�һ�֣��Ʒ׻������$n��"+RED+name+NOR+HIC"���������ڡ�"NOR; break;
			case 4: msg = HIY"$Nʩչ����ʽ�����������˱����ԣ���ʱ���ܲ��Ƽ��죬���ѻ����Σ��������$n�ġ�"+HIB+name+NOR+HIY"��"NOR; break;
			case 3: msg = HIR"$Nʳָ����ָ���˸�����״�������һ������ʽ����ǡ���$n�پ�һ����������̣���֪���롣"NOR; break;
			case 2: msg = HIG"$N��ͷ��󣬵���ʽ�����졹���·���ִ�ԣ���������ھ�ֱ͸ָ�⣬��$n�ظ�����������ʮ�¡�"NOR; break;
			case 1: msg = HIW"��ʱ$N����һ��ǿ�ҵ����磬����ʽ���������ࡹʩչ������������ӿ������$n�ġ�"+HIB+name+NOR+HIW"��֮�ϡ�"NOR; break;
		}
		me->add_temp("wxz_wuxiang", -1);                  
		return([
			"action": msg,
			"force" : 300+random(200),
			"dodge" : random(35),
			"parry" : random(35),
            "damage": 200 + random(200),
			"damage_type" :"����",
		]);
	}
	
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 200 + random(350),
				"dodge": random(30)-10,
				"damage": 150 + random(100),
				"parry": random(20),
				"weapon": action[j]["weapon"],
			]);
		}
	}
}

int practice_skill(object me)
{
	if (!me->query("wxz/done")) 
		return notify_fail("��ͻȻ�о��Լ����ס���Ȫ���縮����Ѩ�����������ܴ̣�ʹ���ɵ���\n");

	if ( me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ( me->query("neili") < 20)
		return notify_fail("������������������ָ��\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

mixed hit_ob(object me, object target)
{
	string msg;
	int j;
	j = me->query_skill("wuxiang-zhi", 1)+me->query_skill("yijin-jing", 1);
	
 
  
	if ( random(me->query_str()) >= target->query_dex()/3
	 && j > 450 //450���Ծ 
	 && random(10) > 5
	 && me->query_skill("finger",1) > 449
	 && me->query("jingli") > 300
	 && random(me->query("combat_exp")) > target->query("combat_exp")/2
	 && me->query("neili") > 500) 
     {
		 switch(random(3)) {
			case 0 :
				message_vision(HIY"$NĬ���׽�񹦣�����΢����������Ǭ����������Ȼ������һ������֮����ָ����ƮƮ�ص���$n��\n"NOR,me,target);
				message_vision(HIC "$nֻ������ȫ��һ�飬����������״����Ȼ�ѱ�$Nһ�е��С���ԪѨ����\n"NOR,me,target); 
				target->add_busy(1+random(3));
				target->apply_condition("no_exert",1+random(2));
				break;
			case 1 :
				message_vision(HIR"$N��ʹָ��Ϭ���������໯���࣬�γ�һ��ʵ�ʵ����ν���������$n�ġ�����Ѩ����ȫ��������к������\n"NOR,me,target);
			  	target->recevied_damage("neili", j);
				if ( target->query("neili") < 0 )
					target->set("neili", 0);
				me->add("neili",-20);
				target->apply_condition("no_perform",1+random(2));
				break;
			case 2 :
			if (me->query_skill_mapped("cuff")=="luohan-quan" 
				&& me->query_skill_prepared("cuff")=="luohan-quan")
			{
				
				message_vision(HIY"$N�Ѿ����޺�ȭ����ʽ�ڻ��ͨ��һʽ����������˫�������绷����$n����ʽ�����������\n"NOR,me,target);
			  	target->recevied_damage("qi", j,me);
				target->add_busy(2);
				me->add_temp("apply/cuff",j/3);
				me->add_temp("apply/damage",j/4);
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				me->add_temp("apply/cuff",-j/3);
				me->add_temp("apply/damage",-j/4);
			}
				break;
			
		}
		//message_vision(msg, me, target);
	}
}
int ob_hit(object ob, object me, int damage)
{
        string name,msg;
        int skill, neili, neili1, sh;
        int j = 0;
		skill = me->query_skill("wuxiang-zhi", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");
        name = xue_name[random(sizeof(xue_name))];

          	                  
        if(random(me->query_str()) > ob->query_dex()/2
         && random(me->query("combat_exp")) > ob->query("combat_exp")/2
		 && random(me->query_skill("finger",1))>ob->query_skill("dodge",1)/2
         && me->query_skill_mapped("finger") == "wuxiang-zhi"
         && neili > 2000 
         && skill > 300 
         && me->query_temp("wxz_wuxiang") //ֻ�п�������ٲŻ��д˷���
         && random(10) > 6){
         	                    
                ob->receive_damage("qi", (damage>2000)?2000:damage , me);
                ob->receive_wound("qi", (damage>2000)?2000:damage , me);
              	j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              	message_vision(HIY "$N����$n���У�ָ��һתֱ��$n�ġ�"RED""+name+""HIY"����ȥ��$n���ܲ�������$Nһָ���С�\n"NOR,me,ob);
                msg = damage_msg(damage, "����") + "( $n"+eff_status_msg(j)+" )\n";
                j = -(damage*2+skill*3)/3;

				message_vision(msg, me, ob);
                return j;
          }
          else if(random(10) < 3 
                && !me->is_busy()
                && !ob->is_busy()  
                && me->query_skill_mapped("parry") == "wuxiang-zhi"
                && !me->query_temp("wxz_wuxiang")
                && random(me->query("neili"))> ob->query("neili")/2
                  ){
          	        //me->add_temp("yiyang-zhi", 5);
                    ob->receive_damage("jing", (damage>2000)?2000:damage , me);
                    ob->receive_wound("jing", (damage>1000)?1000:damage , me);
              		ob->start_busy(2);
              		//j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              		message_vision(BLU"$N����$n���У�ָ��һתֱ��$n�ġ�"HIW""+name+""BLU"����ȥ��$n��æ���ã����ƶ�ʱ���͡�\n"NOR,me,ob);
              		msg = damage_msg(damage, "����") + "( $n"+eff_status_msg(j)+" )\n";
              		message_vision(msg, me, ob);
                    j = -(damage*2+skill*3) /3;
 
				return j;
              	} 
              	    
          return j; 
        
          
}


string perform_action_file(string action)
{
	return __DIR__"wuxiang-zhi/" + action;
}

int help(object me)
{
	write(
@HELP
�����ָ
    ȡ�Է�ʮ���֡�����ǻۣ����磬�Ժ���ӱ��Բ������
    �ϳ˷��Ź��򣬵������ż������ߣ����ڻ���۽϶����Ϊ�������۵����������
    ����ʱ���⣬��ʹ�������𣬿�����������ʦ��̷�������֮��������۶�࣬��
    ��������ֿ��º������������������ֱ������߻���ħ������з�
    ���Ժ��޺�ȭ(luohan-quan)�������������Ҫ�������� 60���������� 60��������
    ����� 450 ��������ο�����pfm������
HELP
	);
	return 1;
}
