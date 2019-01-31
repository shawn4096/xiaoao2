#include <ansi.h>
inherit FORCE;
#include <combat.h>

int valid_enable(string usage) 
{ 
    //�⿪����ȫ������Ϊ�书������ֻ����Ϊ��ѧ
    if (this_player()->query("quest/jiuyin1/pass")) return usage == "force"; 
}
int valid_learn(object me)
{
	if((int) me->query_skill("jiuyin-zhengong", 1) < 220)
		return notify_fail("��ֻ��ͨ���ж������澭����߾����湦��\n");

	if ((int)me->query_skill("jiuyin-zhengong", 1) > me->query_skill("force", 1) + 10
	&& me->query_skill("jiuyin-zhengong", 1) >= 220 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        if ((int)me->query_skill("jiuyin-zhengong", 1) + 10 > me->query_skill("daode-jing", 1)
			|| me->query_skill("daode-jing", 1) < 221)

			return notify_fail("��ĵ��¾����������ܼ�����ϰ�����湦��\n");
       
        if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("�㲻ɢȥ���վ�����ô���������湦��\n");
    
        if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��󡹦����ô���������湦��\n");

        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��Ȫ�񹦣���ô���������湦��\n");

        if((int)me->query_skill("kuihua-mogong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ����ħ������ô���������湦��\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô���������湦��\n");  
     
        if((int)me->query_skill("luohan-fumogong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�޺���ħ������ô���������湦��\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ̫��������ô���������湦��\n");  
      
        if (me->query("gender") == "����")
                return notify_fail( HIW"���޸�����֮�˺����޵�����������ķ�����\n");
 

        if ((int)me->query_dex()< 35)
                return notify_fail("������Լ����������鶯��������������ôƮ�"
                                   "������ڹ��ķ���\n");
 
        if ((int)me->query_int()< 40)
                return notify_fail("������Լ����������Բ�����������������ô����"
                                   "������ڹ��ķ���\n");
		if ((int)me->query_str()< 28)
                return notify_fail("������Լ����������������������������ô����"
                                   "������ڹ��ķ���\n");

       

	return 1;
}

int practice_skill(object me)
{
	if((int)me->query_skill("jiuyin-zhengong", 1) >= 220 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("jiuyin-zhengong", (int)me->query_int());
			me->add("neili", -150);
			me->add("potential", -1*(1+random(2)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ��������߾����湦�ˡ�\n");
	}
	else return notify_fail("�����ڵľ����湦��Ϊֻ���ж�(study)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return SKILL_D("jiuyin-zhengong/") + func;
}

void skill_improved(object me)
{
	if( me->query_skill("jiuyin-zhengong",1) > 0
	&& !me->query("jiuyin/bonus")){
		tell_object(me, "��ľ����湦���������������Ϊ��\n");
		me->set("jiuyin/bonus", 1);
		me->add("max_neili", 10); 
	}
	if( me->query_skill("jiuyin-zhengong",1) >= 250
	&& me->query("jiuyin/bonus") < 2 ){
		tell_object(me, "��ľ����湦���������������Ϊ��\n");
		me->add("jiuyin/bonus", 1);
		me->add("max_neili", 200);
	}
	if( me->query_skill("jiuyin-zhengong",1) >= 350
	&& me->query("jiuyin/bonus") < 3 ) {
		tell_object(me, "��ľ����湦���������������Ϊ��\n");
		me->add("jiuyin/bonus", 1);
		me->add("max_neili", 400); 
	}
	if( me->query_skill("jiuyin-zhengong",1) >= 450
	&& me->query("jiuyin/bonus") < 4 ) {
		tell_object(me, HIC"��ľ����湦��������ľ�����Ϊ��\n"NOR);
		me->add("jiuyin/bonus", 1);
		me->add("max_jingli", 400);
		tell_object(me, HIC"��ľ����湦���������������Ϊ��\n"NOR);
		me->add("max_neili", 800); 
	}
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIC + me->name() + "˫��΢�գ���һ�ɾ�������Χ������" NOR,
                "start_my_msg" : HIC"���������£�˫Ŀ΢�գ�˫���������������̫�������˺�һ���������顣\n"NOR,
                "start_other_msg" : me->name() + "�������£�˫Ŀ΢�գ�˫���������������̫������紵����" + me->name() + "���ϵ����۾�Ȼ��Ϊ������\n",
                "end_my_msg" : HIC"�㽫��Ϣ������һ��С���죬�������뵤�˫��һ��վ��������\n"NOR,
                "end_other_msg" : me->name() + "�����϶�Ȼһ������������ȥ���漴˫��һ��վ��������\n"
        ]);
}
//�����ڹ�������ǣ��Ч��

mixed ob_hit(object ob, object me, int damage)
{
	string msg;
	int ap, dp, j, neili, neili1;
	object weapon;

	if( !me->query_temp("jiuyin/powerup")) return 0;
    if (me->query("env/�����湦")!="����") return 0;
   
	neili = me->query("neili");
	neili1 = ob->query("neili");

	if(me->query_skill_mapped("force")!="jiuyin-shengong") {
		
		return 0;
	}

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if (me->query_skill("parry",1) < 500
	 || me->query("combat_exp") < ob->query("combat_exp")/2
	 || neili < 400 ) return 0;

	weapon = ob->query_temp("weapon");

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	if ( weapon ) ap *= 2;
	if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;
        
	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
	if ( me->is_busy() ) dp /= 2;   
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;  
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;
         
	if ( random(10) < 5 ) me->set_temp("fanzhen", 1);

	ap = ABS(ap);
	dp = ABS(dp);

	if ( me->query_temp("jiuyin/powerup"))
		dp += ap/2 + random(ap/2);

	if ( wizardp(me))
		tell_object(me, sprintf("ap: %d, dp: %d\n", ap, dp));

	if( random(dp) > ap && random(2)) {
		msg = CYN "$NĬ�˾����澭�Ŀھ���������ת������������$N�����γ�һ���������ֵ����֡�\n" NOR;
		//tell_object(ob, WHT "��ֻ������ͻȻ����һ�࣬���������ӭ��������\n" NOR);
	   if (random(neili)>neili1/2 )
	   {
			msg +=HIW "$nһ�д���$N�����ϣ�ֻ���ƺ�����һ���޻��ϣ������澭�����������γɼ�ǿ�ķ���֮����\n"NOR;
			ob->receive_damage("qi",random(4000),me);
            ob->receive_wound("jing",random(500),me);
			ob->add_busy(2);
			ob->apply_condition("no_exert",1);
            me->set_temp("fanzhen",1);
			j=-damage;
	    }		
	    else if(neili >= neili1 + random(damage)) {
			msg +=HIC "���$n�Ĺ�����$N�ľ����湦�����ˣ�\n"NOR,
			j = -damage;
	    }
	    else if( neili > neili1 + random(damage) ) {
			msg += WHT"���$n�Ĺ�����$N�ľ������������˴�룡\n"NOR,
			j = -damage/3*2;
	    }
	    else {
			msg += WHT"���$Nֻ������$n��һС��������\n"NOR,
			j = -damage/2;
	    }
		message_vision(msg, me, ob);
		return j;
	}
}
