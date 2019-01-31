// kuihua-shengong.c ������

inherit FORCE;
#include <ansi.h>

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
	int i = (int)me->query_skill("kuihua-shengong", 1);
	int t = 1, j;
	for (j = 1; j < i / 10; j++) t*= 2;
	if ((int)me->query_skill("force", 1) < 10)
        return notify_fail("��Ļ����ڹ�����㣬����ѧ�����ķ���\n");
	
	if ( !QUEST_D->queryquest(me,"kuihua/book") || me->query("gender") == "Ů��" )
		return notify_fail("������ô�õ����������䡹�ģ�\n");
        
//	if (i > 100 && (int)me->query("shen") > t )
//		return notify_fail("ѧ�����ķ���Ҫ�ĺ���������������������ò���ѽ��\n");
		
	if ( me->query_skill("buddhism",1) || me->query_skill("taoism",1) )
		return notify_fail("������ͺ¿ţ�����ǵ��ķ�����ѧ�����ķ���ʲ�ᣡ\n");

	if (
	   me->query_skill("shenzhao-jing",1)
	|| me->query_skill("taixuan-gong",1)
	|| me->query_skill("jiuyin-zhengong",1)
	|| me->query_skill("hamagong",1))

		return notify_fail("�㲻��ɢ�˱����ڹ�������ѧ�����ķ�����\n");
	return 1;
}

int practice_skill(object me)
{
	if((int)me->query_skill("kuihua-shengong", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("kuihua-shengong", me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ��������߿������ˡ�\n");
	}
	else return notify_fail("�����񹦲��������ϰ��\n");
}

string exert_function_file(string func)
{
	return __DIR__"kuihua-shengong/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : MAG + me->name()+"�����廨�룬˫Ŀ�ʹ�����"NOR ,
		"start_my_msg" : MAG"�������廨�룬��ϥ���£�Ĭ�˿����񹦣�ֻ����������������ʼ�����ڻ����ζ���\n"NOR,
		"start_other_msg" : MAG + me->name()+"�����廨����ϥ���£������ƺ�������һ������֮�С�\n"NOR,
		"halt_msg" : MAG"$N�����廨�룬��������Ѹ�ٽ������ڡ�\n"NOR,
		"end_my_msg" : MAG"�㽫����������������һ�����죬�����������ڵ������̧�����۾���\n"NOR,
		"end_other_msg" : MAG"ֻ��"+me->name()+"���������۾����������ֵ���������ȥ��\n"NOR,
	]);
}



mixed ob_hit(object ob, object me, int damage)
{
	 //By kingso 2007 01 26���±༭��Ҳ��лCounterС��������ҵײ㲻֧��+= ([   
        int ap, dp;
        int  lvl;
        lvl = me->query_skill("kuihua-shengong", 1);
        if ( lvl < 150
          || me->query("neili") < 300
          || me->query_skill_mapped("force") != "kuihua-shengong")
         	return 0;
         	
        ap = ob->query_skill("parry");
        dp = me->query_skill("force");
        if (random(dp)> ap/2)
        {
	        me->add("neili", -50);
          me->receive_curing("qi", damage);
          me->receive_heal("qi", damage);

                return random(2) ?  HBMAG HIY "$N"HBMAG HIY"�۾�һ����$n"HBMAG HIY"��û����Ӱ��ͻȻ$n" 
                                    HBMAG HIY"���������һ��$N"HBMAG HIY"��ͷ������Ծ����\n" NOR:
                                                        
                                    HBMAG HIC"��Ȼ�䣬ֻ��$n"HBMAG HIC"��֦һ�ڣ���ʱ����������"
                                    HBMAG HIC"$n"HBMAG HIC"��Ӱ�ӣ�$N"HBMAG HIC"ȴ�޷�����$n"HBMAG HIC"�ķ�λ��\n" NOR;
                     }
}


mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("kuihua-shengong", 1);
   
    if (random(me->query_dex()) >= (target->query_dex()/4) && j > 120 &&
        me->query_skill("dodge",1) > 120 &&
        me->query("jingli")>300 && 
        !target->is_busy() &&
        me->query("combat_exp")/2 > random(target->query("combat_exp")) && 
        me->query("neili")>500)
   {
          switch(random(2))
          {
            case 0 :
               msg = HIC "$NĬ�˿����񹦣�����Ʈ�����������м���.һ��ָ��$n�����Ѩ��\n";
               msg = msg + "$nֻ��ȫ��һ�飬�ѱ����е���"HIY"������Ѩ�����縮Ѩ������׵Ѩ����\n"NOR; 
               target->recevied_damage("qi", j +random(300));
               target->start_busy(2+random(2));
               break;
            case 1 :
               msg = HIW "$N���й��죬ָ������.��ʱ��������,��$n�������ڣ�\n";
               msg += "$nֻ������ҪѨһ�飬�ѱ����е���"HIY"�����Ѩ�����͹�Ѩ�����ٻ�Ѩ����\n"NOR;
               target->recevied_damage("qi", j + random(300));
               target->start_busy(3+random(2));
               me->add("neili",-50);
               message_vision(msg, me, target);
               return j/(4-random(2));
               break;
            
          }         
          message_vision(msg, me, target);
   }
}