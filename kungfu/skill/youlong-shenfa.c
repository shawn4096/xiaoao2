// Skill: youlong-shengfa.c ������
// 19990811001
#include "ansi.h"

inherit SKILL;

string *dodge_msg = ({
  "ֻ��$nһ�С��������졹�����κ������ϸ߸����𣬶����$N��һ�С�\n",
  "$n��������һ����һ�С������볲������ಡ���һ����$N�Ŀ��������\n",
  "$nͻ����������һ����ʹ��һ�С�����������������������һ�Աܹ���\n"
  "����$nһ�С��������֡��������������һ�ݣ��ܿ���$N��һ�С�\n",
  "$nһ�С�����ǧ�ơ��������������£�Ӳ�Ǳܹ���$N��һ�С�\n",
  "$n���Ų�æ��ʹ��һ�С������پ塹�����Ա�һ���Ӵܳ����ߣ������ù���$N��һ�С�\n",
  "ֻ��$n����һ����ʹ��һ�С�����һ�֡������ؾ�ת����$N���\n",
});

int valid_enable(string usage) 
  { return (usage == "dodge") || (usage == "parry"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
  return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
   if( (int)me->query("jingli") < 30 )
      return notify_fail("�������̫���ˣ�������ϰ��������\n");
   me->receive_damage("jingli", 20);
   return 1;
}

int ob_hit(object ob, object me, int damage)
{
    int sf,tsf,exp,texp,t,i,dam,f=1;

	if(damage<=0)
		return 0;
	
	if(!me->query_temp("dldf/dulong") && !me->query_temp("ylsf/youlong"))
		return 0;
	if (!me->query("quest/sld/ylsf/youlong/pass")) return 0;

	if(me->query_temp("dldf/wudi1"))
	{
		f=2;
	}
	sf=me->query_dex()+me->query_skill("dodge")*f;
	tsf=ob->query_dex()+ob->query_skill("dodge");
	exp=me->query("combat_exp")*f/1000;
	texp=ob->query("combat_exp")/1000;
	if(random(sf)>tsf/2
	  &&random(exp)>texp/2)
	{ 
        message_vision(HIG"\n$N�������ڹ��������Ųȡ��������С�����һת���������߰����˲���$n�Ĺ�����\n"NOR, me, ob);
        return -damage;
	}
	
}

string perform_action_file(string action)
{
       return __DIR__"youlong-shenfa/" + action;
}
