// hanbing-zhenqi.c ��������
// Created by Numa 1999
// Modified by Numa 2000.1.5
// Modified by Numa 2000.1.25
// Modified by darken@SJ
// Lklv@SJ 2001.10.22 modified

#include <ansi.h>
inherit FORCE;
#include "/kungfu/skill/force.h"
#include <combat.h>

#include <combat_msg.h>
mixed hit_ob(object me, object ob, int damage);
int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
	int i = me->query_skill("hanbing-zhenqi", 1);

	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");
	if ( i > me->query_skill("force", 1) + 10
	 && i >= 200 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");
        return 1;
}

void skill_improved(object me)
{
        int pl1,pl2;

        pl1 = me->query_skill("hanbing-zhenqi", 1);
        pl2 = me->query_skill("hanbing-shenzhang", 1);
        if (pl1>=220 && !me->query("ss/hbzq_220")){
                tell_object(me, HIW"\n��Ȼ����о����ں���Խ��Խʢ��ȫ���ƺ�������ѣ�����̹ǣ�\n"NOR);
                tell_object(me, HIW"\n����һ�ᣬ���ں����𽥾��ڵ��ﴦ��ȫ����Ϊ֮һ�񣬹�����Ϊ���������\n"NOR);
                me->delete("ss/hb_improve");
                me->add("max_neili", pl1 + random(pl2));
                me->set("ss/hbzq_220", 1);
        }
}

int ob_hit(object ob, object me, int damage)
{
	int skill, ap, dp, p;
	object weapon;
	string msg;

	skill = me->query_skill("hanbing-zhenqi", 1);
	
	if ( damage < 100 ) return 0;
	if ( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if ( skill < 220
	 || me->query("combat_exp") < ob->query("combat_exp")/2
	 || me->is_busy()
	 || ! me->query_temp("hbzq/huti")) return 0;

	weapon = ob->query_temp("weapon");

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;

	if ( weapon && !me->query_temp("weapon")) ap *= 2;

	if ( me->query_temp("weapon"))
		dp = dp *2/3;

	if ( wizardp(me))
		tell_object(me, sprintf("ap = %d, dp = %d.\n", ap ,dp));

	if ( random(dp + ap) > ap && !random(3)) {
		msg = HIB"ͻȻ֮�䣬$n����һ�Σ�һ�����������˿���һ�Բ����ĵ�����$N��\n"+
			"$n���ӷ��������㲻���������Ǹ��˷���Ѩ��һ�㣬ԭ���Ǳ�$N�Ļ��庮���������ˡ�\n"NOR;
		ob->receive_damage("jing", skill * 2, me);
		ob->receive_wound("jing", skill, me);
		//ob->add_condition("cold_poison",1);
		//������
		
		msg += COMBAT_D->damage_msg(damage, "����");
		if ( random(2))
		{
			ob->add_condition("cold_poison", 2);
            ob->add_busy(1+random(3));
		}
		else
			ob->add_busy(1+random(2));
		me->add_temp("fanzhen", 1);
		p = ob->query("eff_jing")*100/ob->query("max_jing");
		msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		message_vision(msg, me, ob);
		return -damage/2;
	}
	return 0;
}

int practice_skill(object me)
{
	int i = me->query_skill("hanbing-zhenqi", 1);

	if (i >= 200){
		if (i < 220)
			return notify_fail("��ĺ������أ���Ҫ������������ˡ�\n");
		if ((int)me->query("potential", 1) > 5
		 && (int)me->query("neili", 1) > 200){
			me->improve_skill("hanbing-zhenqi", (int)me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else
			return notify_fail("�����ڵ���Ϊ��������ߺ��������ˡ�\n");
	}
	return notify_fail("�����ڵĺ���������Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
       return __DIR__"hanbing-zhenqi/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"���Ϻ������֣�������΢������" NOR,
		"start_my_msg" : "�����󽣾���������������������������ת����\n",
		"start_other_msg" : HIB + me->name()+"���˸���ϥ���������ƣ�ȫ��������һƬ����֮�ڡ�\n"NOR,
		"halt_msg" : "$N˫��һ��������ѹ����Ϣվ��������\n",
		"end_my_msg" : "�㽫��������������֮�ư�����һ�ܣ��о����������ˡ�\n"NOR,
		"end_other_msg" : HIW"ֻ��"+me->name()+"��������˫��վ�𣬻���ɢ����һ�ɱ���ĺ�����\n"NOR,
		"heal_msg" : HIW"$N���𺮱���������ʼ�����������ˡ�\n"NOR,
		"heal_finish_msg" : HIY"$N��Ϣһͣ��ȴ�������Ѿ�ȫ���ˡ�\n"NOR,
		"heal_unfinish_msg" : "$Nüͷһ�壬���ۡ����³�һ����Ѫ���������˻�û��ȫ�á�\n",
		"heal_halt_msg" : "$N��������Ϣһѹ��Ҳ�������ϵ���������վ��������\n",
		]);
}


mixed hit_ob(object me, object ob, int damage)
{
	
	int busy,p;
	string msg;
    object weapon;
	weapon=me->query_temp("weapon");
	//û�⿪�����������Ӳ�����
	if (!me->query("quest/ss/hbzq/pass")) return 0;
	//������
	if( !me->query_temp("ss/hb")) return 0; 
	
	if( ob->is_busy() && !random(2) &&!me->query_temp("action_flag") )
	{
			message_vision(HBBLU+HIW"$N��$n����æ��֮�У������������Ķ�������Ȼ����һ�ɱ����ı�˪!\n"
			+"$n�̲�ס���˸������$N����ʧ���ɲ�ǣ���æ�������С�"NOR,me,ob);
	 		me->set_temp("action_flag",1);
	 		me->add_temp("apply/attack",me->query_skill("hanbing-zhenqi",1)/5);
	 		me->add_temp("apply/damage",me->query_skill("hanbing-zhenqi",1)/5);
	 	
	 		COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
			if (me->is_fighting(ob))
				COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
	 		me->add_temp("apply/attack",-me->query_skill("hanbing-zhenqi",1)/5);
	 		me->add_temp("apply/damage",-me->query_skill("hanbing-zhenqi",1)/5);
	 	
			me->delete_temp("action_flag");
	 		return;
	}
	else if( !ob->is_busy()
	       && me->query_str()*10/2+random(me->query_str()*10/2) > random(ob->query_con()*10) 
	       && random(me->query("neili"))>1000
	       && me->query("jingli")>1000
	       && !random(2))
	      // && me->query("hbzq/powerup")	     
	{
	        switch(random(2))
	        {
	          case 0:
		        if (weapon)
		            msg = HBWHT+HIB"$N��ʹ����������һ�ɺ���֮���ľ�����Ȼ��"+weapon->query("name")+HBWHT+HIB"�Ľ����ϴܳ�������$n��Ѩ����\n"NOR;
	   	        else msg = HBBLU+WHT"$N��ʹ����������һ�ɺ���֮���ľ���������������$n��������\n"NOR;
		        busy = me->query_str()-ob->query_con();
	 	        if(busy<=0) busy = 1+random(2);
	 	        if(busy>5) busy=5;
	 	        ob->add_busy(busy);
	 	        ob->add("neili", -busy*1000);
		        ob->apply_condition("no_exert",2);
                me->add("neili",busy*100); 
				ob->add_condition("cold_poison",1);
	 	        return msg;
		       break;
		       case 1:
                   msg = HBRED+HIW"$N�����ھۣ���ǿ�����������£�������������ʵ�ʣ����������������ֵı�׶����$n�������Ѩ��\n"NOR;
	   	           busy = me->query_str()-ob->query_con();
	 	           if(busy<=0) busy = 1+random(2);
	 	           if(busy>5) busy=5;
	 	           ob->add_busy(busy);
	 	           ob->add("jingli", -busy*1000);
		           ob->apply_condition("no_perform",2);
                   me->add("neili",busy*100); 
				   ob->add_condition("cold_poison",1);
	 	          return msg;
		        break;
		     }
	   }else if(random(me->query("neili"))>9000
	         && me->query("jingli")>500
	         && me->query("jiali") >=200
	         && !me->query_temp("weapon")
	         && !random(2))
	   {
		
	 	msg =HBBLU+HIW"$N˫�ֻӶ��䣬��������$nһʱ��֮��������$N���ؿ����ػ���һ�ơ�\n"NOR;
	 	damage = (me->query_str()*10+me->query_skill("force")-ob->query_skill("parry",1))*5;
	 	if(damage<=0) damage = 1;
	 	if(damage>4000) damage = 4000;
		if (userp(me)&&!userp(ob))
		   damage =damage*2;	 	
	 	ob->receive_wound("qi", damage - ob->query_temp("apply/armor"), me);
		ob->add_condition("cold_poison",1);
		p=(int)ob->query("qi")*100 / (int)ob->query("max_qi");
		msg += damage_msg(damage, "����");
		msg += "( $n"+eff_status_msg(p)+" )\n";
	 	return msg;
	    } 
  
}
