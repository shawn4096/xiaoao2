// shuishangpiao.c 
// BY BOBO@SJ
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
"$n���һ֧��ȫ�������һ�С����㵹�����������ܳ����࣬�����$N�Ĺ�����\n",
"$n�������գ�����Ư��ˮ����һ��������Ʈ����������ˮ�аٺϣ�ҡҷ���ˡ�\n",
"$n�����Ȼ�����޹ǣ�����ҡ�ڣ�ʹ��һ�С����ƯƼ�����ܹ���$N�Ĺ�����\n",
"$nʹ�����ﻻ���ơ���������һ��ת����$N���Բ����������������$N���\n",
"$n��$N���Լ�����һ������ʽ�Ѿ����ϣ���ȻһЦ��ʩչ��ˮ��Ư������������һ�ԡ�\n",
"$n�������գ�����Ư��ˮ����һ��������Ʈ������,������Ĺ������确���ѵ�ˮ��һճ���ߡ�\n",
"$nһ�С���Ҷ��硹��������һƬ��Ҷһ��Ʈ�˳�ȥ������֮������Ѹ�ٵ��˼�����\n",
});

int valid_enable(string usage) 
{ 
	return usage == "dodge";
}

int valid_learn(object me)
{
	if ( me->query_skill("guiyuan-tunafa", 1) < 10)
		return notify_fail("��Ĺ�Ԫ���ɷ��ȼ�̫���ˡ�\n");
	return 1; 
}

string query_dodge_msg()
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( me->query("jingli") < 30 )
		return notify_fail("�������̫���ˣ�������ˮ��Ư��\n");
	me->receive_damage("jingli", 25);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"shuishangpiao/" + action;
}
int ob_hit(object ob, object me, int damage)
{
	string msg;
	int mdodge, tdodge;
	int j = 0;
	mdodge = me->query_skill("shuishangpiao", 1);
	tdodge = ob->query_skill("dodge",1);
	
  
    if (!me->query("tiezhang/pass")) return 0;
    if (!me->query_temp("piao")) return 0;
   

	if( random(me->query_dex(1)) > ob->query_dex(1)/2	 
	 && me->query_skill_mapped("dodge") == "shuishangpiao"
	 && me->query("neili") > 5000
	 && mdodge > 450 ) {
		
		me->add_temp("piao", 1);
		msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
			HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
       		
		tell_object(ob, BLU "���Ȼ���ֶԷ��ƺ���Ư����ˮ����һ����ҡ�ڲ�������ȴǡ�ö������Ĺ�����\n" NOR);
		if(random(mdodge*2) >= tdodge+random(tdodge)){
			msg +=HIY"���$N��������$n��΢��ҡ�ڸ��㿪�ˣ�\n"NOR, 
			j = -damage;
		}
		else if(random(me->query("dex")) > ob->query("str")/2){
			msg += MAG"���$N�������������һ�룡\n"NOR, 
			j=-damage/2;               
		}
		else {
			msg += HIW"���$nֻ�����$N���ٲ���������\n"NOR, 
			j = -(damage/2+random(damage/2)); 
		}
		message_vision(msg, ob, me);
		return j;
	  }
	//return j;   
}
