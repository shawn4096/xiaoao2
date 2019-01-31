// anying.c
#include <ansi.h>

inherit SKILL;
 
string *dodge_msg = ({
"ֻ��$nһ�С�������硹���������ϱ�ֱ���������࣬�����$N��һ�С�\n",
"$nһ�С�������֡�������ݳ�����֮Զ���ܿ���$N���������ơ�\n",
"$nʹ��������չ�᡹����һ��ƮȻ�ݳ��������ŵء�\n",
"����$nһ�С����ն�����������Ʈ��������һ�ݣ����ѱܿ���\n",
"$nһ�С�Ӱ�����ơ���������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
"����$nʹ��������޳���������һ�ã�$N��һ�����˸��ա�\n",
"ȴ��$n�㲻��أ�һ�С���ȥ���⡹������Ծ�����ߣ����˿�ȥ��\n",
"$nһ�С�������ҡ�������΢�Σ��о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage) 
{ 
	return usage == "dodge";
}

int valid_learn(object me)
{
	if ( me->query_skill("linji-zhuang", 1) < 10)
		return notify_fail("����ټ�ʮ��ׯ�ȼ�̫���ˡ�\n");
	return 1; 
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( me->query("jingli") < 30 )
		return notify_fail("�������̫���ˣ���������Ӱ���㡣\n");
	me->receive_damage("jingli", 25);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"anying-fuxiang/" + action;
}

int ob_hit(object ob, object me, int damage)
{
	string msg;
	int mdodge, tdodge;
	int j = 0;
	mdodge = me->query_skill("anying-fuxiang", 1);
	tdodge = ob->query_skill("dodge",1);
	
  
    if (me->query_skill("jiuyin-zhengong")< 150) return 0;
    if (!me->query_temp("ljz/fengyun")) return 0;
   

	if( random(me->query_dex(1)) > ob->query_dex(1)/3	 
	 && me->query_skill_mapped("dodge") == "anying-fuxiang"
	 && me->query("neili") > 2000
	 && me->query("env/�����ٳ�")
	 //&& random(10)>5
	 && mdodge > 450 ) {
		
		msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
			HIY+dodge_msg[random(sizeof(dodge_msg))]+NOR;
       		
		message_vision(BLU"$N�������ǣ���æ����ʹ�������澭�ϵĹ���ǡ�ö����$n�������Ĺ�����\n" NOR,me,ob);
		j = -damage;
				
		message_vision(msg, ob, me);
		return j;
	}  
	 return j;   
}
