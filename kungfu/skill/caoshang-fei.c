// caoshang-fei.c ���Ϸ��Ṧ
// Created by snowman@SJ 06/03/2001
#include <ansi.h>
inherit SKILL;
 
string *dodge_msg = ({
  	"ֻ��$n˫��һ�㣬���ӷ����ۼ��޷��ܿ��Ĺ�������Ȼ��$n���˿�ȥ��\n",
  	"$n����һŤ������$N��ʽ֮�����˹�ȥ�������ڲ��Ϸ���һ�㣬�����ë��\n",
  	"$n��һ��ƮȻ�ݳ��������ŵء�\n"
  	"����$n����Ʈ��������һ�ݣ����ѱܿ���\n",
  	"$n������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
  	"$N������ǰ��Ӱһ����$n�Կ�����׵����Ѿ�Ʈ�˿�ȥ��\n",
  	"ȴ��$n�㲻��أ�����Ծ�����ߣ����˿�ȥ��\n",
  	"$n����΢�Σ��о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage) 
{ 
    	return usage == "dodge"; 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("jingli") < 30 )
            	return notify_fail("�������̫���ˣ����������Ϸ��Ṧ��\n");
        me->receive_damage("jingli", 25);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"caoshang-fei/" + action;
}


int ob_hit(object ob, object me, int damage)
{
	string msg;	
	int mdodge, tdodge,i;
	int j = 0;
	mdodge = me->query_skill("caoshang-fei", 1);
	tdodge = ob->query_skill("dodge",1);
	

    if (me->query_skill_mapped("dodge") != "caoshang-fei") return 0;
	if (me->query_skill_mapped("force") != "baduan-jin") return 0;
	if (me->query("neili") < 4000) return 0;
	if (mdodge<450) return 0;	
	// && (damage>2000) && (random(3))
	if (me->query("quest/baduanjin/pass2") && (!me->query("family")) && (damage>2000) && (random(3)))
	 {
		
		message_vision(HIW "$N��Ȼ���˶ν��ش�����ʩչ������������鶯�쳣�����������һ����\n" NOR,me,ob);
	    return -damage;
	 } 

}


