// huoyan-dao.c ���浶
// by snowman@SJ

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N��Ϣת�����˾���˫�ۣ�ȫ��ǽ�һ���죬����һʽ��ʾ��������$n��������$nȫ�������ڳ��ȵ��Ʒ���",
	"skill_name" : "ʾ����",
	"lvl" : 0,
	"damage_type" : "����",
]),
([
	"action" : "$N�����Ц��һ�С�ʼ�ľ��������浶�ھ����ڼ�������ӿ����$P˫���籦���ʮ����ǰ������$n����һ��",
	"skill_name" : "ʼ�ľ�",
	"lvl" : 20,
	"damage_type" : "����",
]),
([
	"action" : "$N˫�ƺ�ʮ���ִ򿪣����С��ֱ������Ի��浶���Ϲ����۳�һ�������ʢ���Ļ��������ת��������$n����",
	"skill_name" : "�ֱ���",
	"lvl" : 50,
	"weapon" : "��������",
	"damage_type" : "����",
]),
([
	"action" : "$N�������࣬˫�ƴ�Բ��ʹ�������ȵĵ�����ۣ����С��Ʒ�ִ������һֻ�޴�����ƣ������$n��ץ����",
	"skill_name" : "�Ʒ�ִ",
	"lvl" : 70,
	"damage_type" : "����",
]),
([
	"action" : "$N����һ������Ȼʹ����ħ���ϵġ�����Բ����������쫷��Χ��$P������������$nһ��������$P��������",
	"skill_name" : "����Բ",
	"lvl" : 120,
	"damage_type" : "����",
]),
([
	"action" : "$N�����ħ�澭��˫��������������$n����������֮�£����絶�и����ġ����泣�������ƺ�Ҫ��$p��������",
	"skill_name" : "���泣",
	"lvl" : 140,
	"weapon" : "���ε���",
	"damage_type" : "����",
]),
([
	"action" : "$N�ֱ��࣬�����������֡����淨�������ĳ�������е������᲻ɢ�����������Ƶ�����ȴ��ɽ�������ӿ��$n",
	"skill_name" : "���淨",
	"lvl" : 160,
	"damage_type" : "����",
]),
([
	"action" : "$N�������ƣ�һʽ�������š���������ת������ȫ�������޷��Զ���$P����΢�㣬��������һ����ն��$n$l",
	"skill_name" : "������",
	"lvl" : 180,
	"weapon" : "��������",
	"damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����浶������֡�\n");
	if ( me->query("max_neili") < 1500)
		return notify_fail("�����������Ϊ������������ϰ���浶��\n");
	if ( me->query_con(1) < 30)
		return notify_fail("��ĸ���̫�ͣ����ܼ������浶��\n");
	if ( me->query_skill("longxiang-boruo", 1) < 100)
		return notify_fail("���浶��Ҫ������������ڰ˲����ϵĻ�����ѧϰ��\n");
	if ( me->query_skill("force") < 100)
		return notify_fail("��Ļ����ڹ����̫ǳ������ѧ���浶��\n");
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
	int i,j,k, level, neili, force, jiuyang;
	string msgs;
        
	level   = (int) me->query_skill("qishang-quan", 1);
	jiuyang = me->query_skill("jiuyang-shengong", 1);
	force = me->query_skill("force",1);
	neili = me->query("neili");

	level = (int) me->query_skill("huoyan-dao",1);

// 	��� pfm ran
	if( me->query_temp("hyd_ran") ) {
		return ([
			"action" : RED"$N�͵���ת�ڹ����۾���˫�ƣ����浶�ھ����ڼ�������ӿ����Ю��һ�����ȵĵ�����$nֱӿ��ȥ��"NOR,
			"force":300+random(250)+me->query_str(),
			"dodge":random(30)-10,
			"damage":200+random(200),
			"parry":random(10)+10,
			"damage_type" : "����",
		]);
		me->delete_temp("hyd_ran");
	}
//������ʽ
	if( intp(j = me->query_temp("hyd/honglian/power")) && j > 0 ){
		switch(j) {
			//case 5: msgs =HIB"$Nһ�����ȣ��������У�˫�Ʋ�����$nʩѹ����ʱ��������"NOR; break;
			case 4: msgs =RED"$N������ţ�˫�Ƹ�ն��Ϊֱ�������浶�����ɴ�ʢ��$n�Ѿ����粨�ΰ���������"NOR;break;
			case 3: msgs =HIC"$N˫��һ�գ���$n���ܻ��浶����֮ʱ��һ��ת������$n����󣬽��������$n��$l��"NOR ;break;
			case 2: msgs =HIR"$N˫�ֺ�ʲ��˫�Ƶ������Ƶ������һ��ն�����������浶���ϳ�һ����$n���"NOR;break;
			case 1: msgs =HIY"$N��Ȼ�����񹦴�ɣ�������ϢԴԴ����ӿ����˫�ֲ�ͣ�趯��"HIR"������"HIY"˲�䱬����"NOR;break;
			default:msgs =HIR"$N�����浶����Ȼ��������ɫ�Ʒ����ǿ�Ҹ��£�ͻȻ��������һ��ն����ȷʵ�����Ƿ���"NOR; break;
		}
		if( me->query_temp("hyd/honglian/power") >= 1 )
			me->add_temp("hyd/honglian/power", -1);
		return ([
			"action": msgs,
			"damage_type" : "����",
			"dodge": 30+random(30),
			"parry": 30+random(30),
			"force": 250 + random(150),
			"damage": 150 + random(100),
		]);
	    me->delete_temp("hyd/honglian/power");
	}
//�����ݺ���ʽ
	  if( intp(k = me->query_temp("hyd/zongheng")) && k>0){
		switch(k) {
			case 6: msgs =HBBLU+HIG"$N��������������������鰴������бб���������������������ʹ�������ǡ����浶���е�һ���ֵ�����"NOR; break;
			case 5: msgs =HBBLU+HIG"$N�˿�˫�����𣬺ݿ�����ȫ���������书��·�ӡ�$Nһ�����䣬�����浶��������ӿ������һ����"NOR; break;
			case 4: msgs =HBBLU+HIG"$N��ʹ�����浶�������������޷����������������ӿ���������̺�Ȼ����$n��$l"NOR;break;
			case 3: msgs =HBBLU+HIG"$N˫���籧Բ�������˳����������������������Ѷ�ȥ��ңңָ�Ż���$n�������Ѩ"NOR ;break;
			case 2: msgs =HBBLU+HIG"$N�����ڹ�����ǿ���������浶������������������ȻĪ�ܵ����������������죬��$n���ҳ����ȥ"NOR;break;
			case 1: msgs =HBBLU+HIG"$N��ʹ���浶��һ�С��׺���ա�������ʽ�о���֮����һ����Ҫ����$n��$l��������"NOR;break;
			default:msgs =HBBLU"$N�����浶������������⾳ʩչ���������ɾ������ű��̶�ȥ�����ƻ�������ȴѸ���ޱ�"NOR; break;
		}
		if( me->query_temp("hyd/zongheng") > 0 )
			me->add_temp("hyd/zongheng", -1);
		return ([
			"action": msgs,
			"damage_type" : "����",
			"dodge": 30+random(30),
			"parry": 30+random(30),
			"force": 250 + random(350),
			"damage": 180 + random(100),
		]);
		
	}
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"weapon": action[j]["weapon"],
				"force":250+random(350),
				"dodge":random(30)-10,
				"parry":random(20),
				"damage":100+random(50),
			]);
		}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("huoyan-dao", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if ( me->query("jingli") < 50 || (int)me->query("neili") < 20)
		return notify_fail("������������������˻��浶��\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"huoyan-dao/" + action;
}

int ob_hit(object ob, object me, int damage)
{
	string msg;
	int j, skill, neili, neili1;

	skill = me->query_skill("huoyan-dao", 1);
	neili = me->query("neili");
	neili1 = ob->query("neili");

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 1;
	}
    
	if( random(skill) > ob->query_skill("parry", 1)/2
	&& me->query("combat_exp") > ob->query("combat_exp")/2
	&& me->query_skill_mapped("parry") == "huoyan-dao"
	&& me->query_skill("longxiang-boruo", 1) > 450  //��ɺ��з���
	&& neili > 1000 
	&& skill > 450 
	&& random(neili) > random(neili1)/2
	&& living(me)
    && !random(3)
	&& !me->query_temp("weapon")
	&& !ob->query_temp("weapon")
	&& !ob->is_visible(me)) {       
		if( me->query_temp("dazhuan_npc") ) neili += neili/2;

		msg = HBRED"ֻ����$N��ǰ��������������ĵ����������������������죬�����浶�����ƴ�ʢ��\n"NOR;            
		if (me->query("lx/gree")>10) me->set_temp("fanzhen", 1);
	    if (random(me->query_str(1))>ob->query_dex(1)/2 && me->query("lx/gree")>10 )
           { 
		      msg += YEL "$N��һ���Ͽ�ͬʱ������������������$n��η���������$NҲ���ܷ�����ȥ��\n"NOR;
			  ob->receive_damage("qi",skill*3+random(skill),me);
			  ob->receive_wound("qi",skill,me);
			  //ob->set_temp("lost_fight",3);              
	         // message_vision(msg, me, target);
		}
		else if ( neili >= neili1+random(neili1)+damage*2&& skill >449 ){
			msg += HIY"$N������������Ķ��𣬽�$n��ʽ�ϵ����������������ޣ�\n"NOR, 
			j = -damage;
		}
		else if(neili >= neili1+damage) {
			msg += HIY"$P�����ﴦ���Ի��浶����������$n������������\n"NOR, 
			j = -(damage/2+random(damage/2));               
		}
		else {
			msg += HIY"$P���浶������ӿ�����ֵ�ס��һЩ$n�Ĺ�����\n"NOR, 
			j = -damage/3; 
		}
		if ( wizardp(me)) tell_object(me, "Target damage = "+damage+" ��\n");   
		message_vision(msg, me, ob);
		return j;
	}
}

// ��� pfm huoyan-dao ���� �ĸ�������
mixed hit_ob(object me, object target)
{
	string msg;
	int j,ls,hyd,damage;
	j = me->query_skill("strike",1);
    ls=me->query_skill("longxiang-boruo",1);
	hyd=me->query_skill("huoyan-dao",1);
	damage=ls+hyd+j;
	damage=damage+random(damage);
	if( !me->query("quest/dls/hyd/pass") ) return ;
    if (!me||!target) return;
    
    if (random(10)>6)
    {   
	 switch (random(3))
	 {
	  case 0:
             if(random(j) >target->query_skill("parry",1)/2
	            || random(me->query("neili")) > target->query("neili")/2 ) 
			{
				msg = CYN"$nֻ��$N�Ļ��浶��ɽ�������ӿ�����������񣬸����޷��ֵ�,����һ�������ؿڣ�\n"NOR;
				target->receive_wound("qi", damage, me);
	         } 
			 else {
				msg = HIR"$nֻ��$N�Ļ��浶��ɽ�������ӿ������������ȫ������׼��Ӳ����һ�ƣ�\n"NOR;
				target->add("neili",-j);
	     		if( !target->is_busy() )
					target->add_busy(2+random(2));
	          }
	         message_vision(msg, me, target);
	         break;
	 case 1:
            if (random(me->query("combat_exp"))>target->query("combat_exp")/2 && hyd >449&&objectp(target) )
             { 
		      message_vision(RED "\n$N�˿̺�����������״���ݿ�����ȫ���������书��·�ӡ�һ�����䣬�����ŷ�����һ�죬$n��ʱ�ұ����У�\n"NOR,me,target);
			  target->receive_damage("qi",damage,me);
			  target->apply_condition("no_perform",1);
              }
	        // message_vision(msg, me, target);
			 break;
	case 2:
             message_vision(RED"���浶�������޼᲻�ݣ�$n��Ȼ���ű��ۣ����������׸ȫ���࿹֮����\n",me,target);
		     target->add_busy(1+random(1));
		     if(random(me->query_skill("force",1)) >  target->query_skill("force",1)/3
				 && me->is_fighting()
				 && ls>449)
			{
                message_vision(HIR "$nֻ����ȫ�����ȣ���Ϣ�Ĵ��ҳ壡\n"NOR,me,target);
                target->receive_damage("qi", damage,me);
                target->apply_condition("no_exert",1);
				target->apply_condition("hyd_condition",3);
                target->add("neili", -random(damage));               
                me->add("neili",-400);
             } 
             else {
                message_vision( YEL "����$n������$N����ͼ����������ȫ��������������������˻�ȥ��\n" NOR,me,target);
                if (!me->query("quest/longxiang/pass"))
				{
                   message_vision(HIR "$Nֻ����ȫ�����ȣ���Ϣ�ҳ壬�����ѵ���\n"NOR,me);
				   me->apply_condition("no_exert", 1);
                   me->receive_damage("qi", damage,me);
                   me->add("neili",-800);
				   me->start_busy(2);  
				}
				else {
				  message_vision(WHT"$N�����������Ȼ��ɣ�˲�佫�������ѹ����ȥ��������ȴ��$n����������������\n"NOR,me,target);
				}
                me->add("neili",-400);    
               
			}
		    break;
	    }
	  }
}

int help(object me)
{
	write(HIR"\nѩɽ�ؼ������浶����"NOR"\n");
	write(@HELP
	�Ħ���Ի񴫻��浶���Դ�ɨ���ڽ̡���춶�������ʮ�����������Ȥ��
	�Ħ�Ǳ��Ի��浶������Ľ�ݲ�����������ʮ�����־�����Ľ�ݲ������
	Ħ����Լ�����Ħ����ȡ�ô�����ϵġ������񽣾�������ɵ��κ�ׯȥ
	ȡ����������ʮ���������ر������պ�ŷ��������¶ᾭ֮ս��
	������Ħ���Ի��浶������ȼ���ػ�ҩ�Ĳ��㣬�������ƶ����̹�����
	�ٵ���ɮ���������Ծ��ƶ����Ħ���ڿ���ͻϮ�°��󡣼����Ħ�ǽ�
	���浶����һ��Ϊ�����Ӷ�����򹥻���������֪���У���һ��ָ������
	�١������񽣾��������ױ���ʹ�Ħ���������½��³�Թ���Ħ�Ǳ�����
	������Ϊ���ʡ������鼱���֣�����һ�����ε���֮ս�����ջ�𵶲���
	�����񽣣�������ȴ���Ħ�����¡��Դ�һս�����浶���𽭺���
	
Ҫ��
	������� 1500 ���ϣ�
	������� 30 ���ϣ�
	����������ȼ� 100 ���ϣ�
	�ڹ��ȼ� 100 ���ϡ�     
HELP
	);
	return 1;
}
