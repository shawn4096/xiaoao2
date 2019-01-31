// yinyun-ziqi.c ������

#include <ansi.h>
inherit FORCE;
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>
#include "force.h"
//#include "force1.h"
//�ڹ����𣬹�������ʱ������
string *fanzhen_msg = ({
"$n����ֻ���������޻����У�$N���ƾ���������ֻ���$n������������һ�뷭ת��\n",
"$N�����һ��������˿�����������ý���ж��֮�ʣ����ȷ��𣬽�$n��������ֽ��ȫ��Ѫɫ��\n",
"̫�������������ᾢʹ�������$n�ķ����ѣ�����������������\n",
"$N�����Ѳ���ȫ����$n�����������ȥ��\n",
"���$n������ת�������������߰˲���\n",
"��$nһײ��ֻ���$p�ؿ���Ѫ��ӿ��\n",
"$n����ײ��һ���޻����棬����Ϊ��ĺ�ǽ��һ�㣬����������\n",
"$n������$P��ͻȻ����һ�𣬵�ʱ���˳�ȥ��\n",
});

int get_bouns(int damage,int t,int level,int flag);

int valid_enable(string usage) { return usage == "force"; }
int valid_learn(object me)
{
	int lvl = (int)me->query_skill("yinyun-ziqi", 1);
	int t = 1, j;

	for( j = 1; j < lvl / 10; j++) t *= 2;
	if( t > 5000 ) t = 5000;
	if( me->query("gender") == "����" && lvl > 49 )
		return notify_fail("���޸����ԣ�����������������������������񹦡�\n");

	if( me->query("class") == "bonze" )
		return notify_fail("�����������������ϣ���Υ��������徻֮�⣬" +RANK_D->query_respect(me)+"���޴˹������������\n");

	if( (int)me->query_skill("force", 1) < 15 )
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	if( (int)me->query_skill("yinyun-ziqi", 1) > me->query_skill("force", 1) + 10
	&& me->query_skill("yinyun-ziqi", 1) >= 200 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	if( (lvl > 10 && lvl < 100 && (int)me->query("shen") < t * 200)
	|| ( lvl >=100 && (int)me->query("shen") < 10000) )
		return notify_fail("�����������̫���ˡ�\n");

	if( me->query("menggu") )
		return notify_fail("����Ͷ���ɹţ��޷��ٽ�һ�������������\n");

	return valid_public(me);
}

int practice_skill(object me)
{
	if( (int)me->query_skill("yinyun-ziqi", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("yinyun-ziqi", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ����������������ˡ�\n");
	}
	else return notify_fail("�����ڵ���������Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"yinyun-ziqi/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : MAG + me->name()+"ͷ�������������ɫ����" NOR,
		"start_my_msg" : "����ϥ������˫Ŀ���գ�������һ�������뵤�������һ����Ϣ�������Ѩ��������������֮����\n",
		"start_other_msg" : me->name()+"��ϥ����������˫�����ճ�ȭ����һ�ᣬͷ��ð����������\n",
		"halt_msg" : "$N΢һ��ü������Ϣѹ�ص������һ������վ��������\n",
		"end_my_msg" : "�㽫��Ϣ����������ʮ�����죬���ص��ֻ����ȫ��ů����ġ�\n",
		"end_other_msg" : me->name()+"����һ������һ���½�վ�����������о���һ����\n"
	]);
}

int ob_hit(object ob, object me, int damage)
{
    int m_yyzq,t_force,i,t,p;
	string msg;
    m_yyzq = random((int)me->query_skill("yinyun-ziqi",1)+(int)me->query_skill("force",1));
    t_force = (int)ob->query_skill("force",1);
    //set ������ ����˸� yun taiji�����ʱ����Ϊ yyzq/taiji
    //��˿�� ���� ж�� ���� 
    if((int)me->query_skill("yinyun-ziqi",1)>=350)
    {
       if(userp(me)&& me->query_temp("tj/taiji"))
		{
        
		 if (me->query("env/������")=="����˸�" )
        {
                me->add("jingli", -50);
				me->add("neili", -100);
                ob->add("jingli", -10);
               	ob->add("neili", -20);
				msg = HIY"ֻ����ž����һ����$N�ͶԷ������ഥ������������˸ա���˿�����Ĺ������ֳ�����\n"NOR;
				ob->receive_damage("qi", damage*2,me);
			    ob->receive_wound("qi", damage*2,me);
				ob->start_busy(random(2));
				message_vision(msg, me,ob);
				//damage=call_out(get_bouns(damage,6,me->query_skill("yinyun-ziqi",1),1));
				return -damage;
				
           }	
       /* if (me->query_temp("yinyun")&& random(1))
         {
			    msg += fanzhen_msg[random(sizeof(fanzhen_msg))]+NOR;
			    if(ob->query_skill("force") > me->query_skill("force")*3/2) p = p*2/3;

				if ( me->is_busy())
					p /= 2;

				if(p < 10) p = 10;

				ob->receive_damage("qi", p, me);
				ob->receive_wound("qi", p/5*2, me);
				p = (int)ob->query("qi") * 100 / (int)ob->query("max_qi");
				msg += "( $n"+eff_status_msg(p)+" )\n";
				damage = -8000+(-damage);
                message_vision(msg, me, ob);
				return damage;
        }*/
		if(m_yyzq > t_force*2/5 && !random(3)){
            i = - damage;
            message_vision(WHT"$N�����������뻯����$n��һ����$N,$N���ϱ�������ʢ�����������������"+
                "$n���и�����û��$N����κ��˺���\n"NOR,me,ob);
            me->add("neili",-800);
            return i;
        }
        else if(m_yyzq > t_force*3/5){
            i = - damage/2 - random(damage/2);
            message_vision(WHT"$N΢΢һЦ�����������Ķ�����$n������Ȼ��$N�����˾����Ĺ�����\n"NOR,me,ob);
            me->add("neili",-600);
            return i;
        }
        else if(m_yyzq > t_force/2){
            i = - damage/2;
            message_vision(WHT"$N���´���������ϼ�ھ�����ʱ��$n�Ĺ��ƻ�ȥ��һ��!\n"NOR,me,ob);
            me->add("neili",-400);
            return i;
        }
        else if(m_yyzq > t_force/3){
            i = - damage/3;
            message_vision(WHT"$N��$n���������쳣�����´󾪣������������������У�������$n�Ĳ��ֹ���!\n"NOR,me,ob);
            me->add("neili",-300);
            return i;
        }
        else{
            i = - damage/4 - random(damage/4);
            message_vision(WHT"$N�����߶������������ڻ���$n��һ�㹥�������²�����Ȼ!\n"NOR,me,ob);
            me->add("neili",-150);
            return i;
        }

	   }
         
    }
    return 0;
}
/*
int get_bouns(int damage,int t,int level,int flag)
{
	int dm;
	dm= (damage*(t+level/20))/(t+level/20+10);
	if(flag && level>350) dm += dm/2;
	if (falg && level>450) dm += dm/2;
	if (falg && level>550) dm += dm;
	return dm;
}*/