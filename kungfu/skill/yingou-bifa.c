//yingou-bifa.c �����ʷ�
//by sohu@xojh
#include <ansi.h>

inherit SKILL;

string  *msg = ({
"$Nһ�в��´�ˮ����Хһ��������$w��������бֱ��������˳���ޱȣ��ʱ���գ��������ˣ�",
"$N˳��ʹ���������䱮���硸��Ůɢ�������鷨�ս���ȣ������������֮�$w��$n��$lɨ��",
"$Nת��������$w�ͳ����ʷ��ڿ��к���б�����ƺ�д��һ�㣬Ȼ�ʷ���ָ��ȴ�����������Ѩ����$n���ĵ�ȥ",
"$Nһ�����ֲ������������ף�$w��������ƽƽ��ɨ������$n��̫��Ѩ������ΰ��������һ�����ݵ������",
"$N����$w�����Ͻ�б�����½ǣ�ɨ��$n�����ߡ��鷨֮���е�Ѩ����Ѩ֮�����鷨����������������������������",
"$N����ֱ���������е�$w���һ�㣬�Աʴ�ָ��Ҳ�����з����Ͻ������翬����һ�ʲ���������$n��������Ѩ",
"$N��������$n����һ����һ�������������ɵ��ڿ���һ����������Զ����������裬�񱼼��ߣ�����ȫȻ�����·�",
"����$N�����񲡢���������а���������죬ָ����������$w���ӣ����ƴ�ס$n��һ�ǹ��ƣ�$w��һƲ��$n$lһ�㣬���ӽ��ƴ���",
"$N����������������ʥ������ñ¶������ǰ���Ӻ���ֽ�����̡����������磬���������ٿ��������$n��$l��",
"����$N��д��ÿһ�ֶ������ƾ�����������һ������С����һ����Ҳ��ʶ�á���Ȼ�佫$w�ڰ���м�������������$n��̫��Ѩ",
"$Nһ����һ����׭�����������ֹ�Ȼ�Ű£�����Ϊ�鷨֮����һ��ָҲ��Ӧ��ǿ���������е�$w�������죬����ǿ��",
"$N���һ��������$w����������$n������������һ����׭������һ����������",
"$N��Цһ����Ĭ��ھ���$w������������ǰ����Ȼ���飬ȴ��һ�����ˡ���",
"$N���Ӽ���ת����հ֮��ǰ��Ȼ�ں����е�$w�����û��ͻȻ����$n��$l��$l��д�ϡ������͡��ġ�",
});

int valid_enable(string usage)
{
    return usage == "brush" || usage == "parry";
}

mapping query_action(object me, object weapon)
{         
        return ([
                "action":msg[random(sizeof(msg))],
                "damage":150+random(100),
                "damage_type":random(2)?"����":"����",
                "dodge":random(40)-random(20),
                "force":random(200)+100,
               ]); 
}

int practice_skill(object me)
{    
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "brush")
                return notify_fail("��ʹ�õ��������ԡ�\n");
       if ((int)me->query("jingli") < 30)
               return notify_fail("��������������йٱʷ���\n");         
       if ((int)me->query("neili") < 50)
               return notify_fail("��������������йٱʷ���\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
       return 1;
}

int valid_learn(object me)
{
       int skill = me->query_skill("yingou-bifa", 1);
       if ((int)me->query("max_neili") < 500)
               return notify_fail("�������������\n");
       if ((int)me->query_skill("qiantian-yiyang", 1) < (skill-60))
               return notify_fail("���Ǭ��һ�������̫ǳ��\n");
       if (me->query_skill("yingou-bifa",1)<300)
     	   if ((int)me->query_skill("literate", 1) < (skill-60))
               return notify_fail("��Ķ���д�ּ���̫�ͣ��޷�����鷨�����\n");      
       return 1;
}

string perform_action_file(string action)
{
      return __DIR__"yingou-bifa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
    object weapon=me->query_temp("weapon");
	if (me->query_skill_mapped("force")!="qiantian-yiyang")
		return;
    if (me->query_skill("qiantian-yiyang",1)<250)
        return;
	if (!me->query("quest/tls/yiyangshu/pass")) return;

	if( me->query_temp("qtyy/yiyang") 
		&& me->query("neili")>1000
		&& !random(4)) 
	{
        message_vision(HIY"$Nͷ�������뵣���Ȼ��һ��ָ�Ĺ������õ���һ·�����ʷ�����ʽ�У��������͡�\n"NOR,me,victim);
		switch (random(2))
		{
		   case 0:
               if (random(me->query_int(1))>victim->query_int()/4)
               {
			     message_vision(HIR"$n��ûѧ����һ·�鷨���ۻ�����֮��Ϊ$N��һ��ָ����ס��Ѩ����\n"NOR,me,victim);
				 victim->add_busy(3+random(2));
				 victim->apply_condition("no_exert",1);
               }else {
				 message_vision(HIC"$n����$N��д����·�鷨��Ȼ���أ�˳�ƻ�����$N�Ĺ��ơ�\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;
			case 1:
			  if (random(me->query_skill("brush",1))>victim->query_skill("parry",1)/3)
               {
			     message_vision(MAG"$N����"+weapon->query("name")+MAG"��Ȼ��ù��̣�������죬$n���̵����۴��,����ƣ��������\n"NOR,me,victim);
				 victim->receive_damage("qi",random(3000),me);
				 victim->receive_damage("jing",random(1000),me);
               }else {
				 message_vision(HIC"$n����$N��д����·�鷨��Ȼ���أ�˳�ƻ�����$N�Ĺ��ơ�\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;		   
		
		}
        
    }
	return;
}
