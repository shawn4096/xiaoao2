// �޺���ħ�� luohan-fumogong.c
//By kingso

inherit FORCE;
#include <ansi.h>

#include <combat_msg.h>

int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("�㲻ɢȥ���վ�����ô�����޺���ħ����\n");
    
        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��Ȫ�񹦣���ô�����޺���ħ����\n");

        if((int)me->query_skill("jiuyin-zhengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����湦����ô�����޺���ħ����\n");

       if((int)me->query_skill("kuihua-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô�����޺���ħ����\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô�����޺���ħ����\n");  
     
       if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��󡹦����ô�����޺���ħ����\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ̫��������ô�����޺���ħ����\n");       

        if ((int)me->query("int") < 33)
                return notify_fail("���������Բ��㣬��������޺���ħ�񹦡�\n");

        if ((int)me->query("con") < 20)
                return notify_fail("����������������޷������޺���ħ�񹦡�\n");
       
        if ( me->query("gender") == "����" && me->query("luohan-fumogong", 1) > 29)
                return notify_fail("���޸����ԣ�����������������������޺���ħ�񹦡�\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ�����㣬����ѧ�޺���ħ�񹦡�\n");

        if ((int)me->query("max_neili", 1) < 1000)
                return notify_fail("���������Ϊ���㣬����ѧ�޺���ħ�񹦡�\n");
        if(!me->query("quest/Ħ����/luohan")) 
                return notify_fail("�����ڲ���ѧϰ�޺���ħ����\n");


        return ::valid_learn(me);
}

int practice_skill(object me) 
{      
       if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("�㲻ɢȥ���վ�����ô�����޺���ħ����\n");
    
        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��Ȫ�񹦣���ô�����޺���ħ����\n");

        if((int)me->query_skill("kuihua-mogong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ����ħ������ô�����޺���ħ����\n");

       if((int)me->query_skill("kuihua-shengong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô�����޺���ħ����\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ�����񹦣���ô�����޺���ħ����\n");  
     
       if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ��󡹦����ô�����޺���ħ����\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("�㲻ɢȥ̫��������ô�����޺���ħ����\n");       


       if((int)me->query_skill("luohan-fumogong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("luohan-fumogong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ����������޺���ħ���ˡ�\n");       }
        else return notify_fail("�����ڵ��޺���ħ����Ϊֻ����ѧ(learn)�������������ȡ�\n");

}

string exert_function_file(string func)
{
	return SKILL_D("luohan-fumogong/") + func;
}
mapping exercise_msg(object me)
{
  
    return ([
		"status_msg" : HBRED HIY + me->name()+"��ϥ�������ֽ��޺���ħӡ��ͷ�Ϸ�����֣������������Ķ���" NOR,
		"start_my_msg" : HBRED HIC "���ų�һ������ֽ��ħ�޺�ӡ��һ��ǿ�����Ϣ��ʼ��������ת��\n"NOR,
		"start_other_msg" : HBRED HIC + me->name()+"�ų�һ������ֽ��ħ�޺�ӡ����ʱ��Χ����һ��ǿ���������\n"NOR,
		"halt_msg" : "$N����һ����������Ϣ�������˻�ȥ��վ��������\n",
		"end_my_msg" : HBMAG HIY"�㽫��Ϣ��תһ�������죬���ص���չ�վ��������\n"NOR,
		"end_other_msg" :HBMAG HIY "ֻ������"+me->name()+"�������������ֵĽ�⣬������ʧ��\n"NOR,
		"heal_msg" : HBMAG HIY"$N�ֽ��޺���ħӡ���������£�����޺���ħ�䡱����ʼ�˹����ˡ�\n"NOR,
		"heal_finish_msg" : HBMAG HIY"$N����վ������������Ӱ���ֵĽ�⣬�����޺���������\n"NOR,
		"heal_unfinish_msg" : "$N�³���Ѫ������վ�𣬵���ɫ�԰ף���������������\n",
		"heal_halt_msg" : HBMAG HIY"$N��ϥ����������������Ӱ���ֵĽ�⣬�ֽ��޺���ħӡ�������޺�������\n"NOR,
	]);

}

mixed hit_ob(object me, object ob, int damage)
{
	
	int busy,p;
	string msg;

	if(!me->query("quest/Ħ����/luohan")) return;
	if(me->query_temp("luohan_power"))
	{
		me->add_temp("luohan_power",-1);
		return;
	}
     
	 if(random(7)==3 && random(3)  )
	 {
		me->set_temp("luohan_power",1);
	 	me->delete_temp("combat_time");
	 	message_vision(HBMAG HIY"$N�����޺���ħ�������ֽ��޺���ħӡ�����������֡�\n"NOR,me);
	 	me->set_temp("action_flag",1);
	 	me->add_temp("apply/attack",me->query_temp("combat_time")*10);
	 	me->add_temp("apply/damage",me->query_temp("combat_time")*10);
	 	me->add_temp("apply/parry",me->query_temp("combat_time")*10);
	 	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
	 	me->add_temp("apply/attack",-me->query_temp("combat_time")*10);
	 	me->add_temp("apply/damage",-me->query_temp("combat_time")*10);
	 	me->add_temp("apply/parry",-me->query_temp("combat_time")*10);
		me->delete_temp("action_flag");
	 	return;
	 }
	 
	 else 
		 if(random(me->query("neili"))>1800
	 && me->query("jingli")>500
	 && me->query("jiali") > 30
	 && random(6)==1 
	 ){
		me->set_temp("luohan_power",5);
	 	msg = HBMAG HIY"ֻ��$N�����â���֣������޺���ħӡ˳��һת��ͻȻ��������ϣ���û��$n��Ӧ������һ���ۻ���ھ�͸����롣\n"NOR;
	 	damage = (me->query_str()*10+me->query_skill("force")-ob->query_skill("parry",1))*5;
	 	if(damage<=0) damage = 1;
	 	if(damage>2000) damage = 3500 + random(2000);
	 	ob->receive_wound("qi", damage - ob->query_temp("apply/armor"), me);
		p=(int)ob->query("qi")*100 / (int)ob->query("max_qi");
              if( me->query("env/�޺���ħ") == "��ħ" ){ 
              ob->add_condition("luohan_hurt", random(me->query_con())); }
		msg += damage_msg(damage, "����");
		msg += "( $n"+eff_status_msg(p)+" )\n";
	 	return msg;
	 }
}


