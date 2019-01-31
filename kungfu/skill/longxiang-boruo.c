// longxiang-boruo.c ���������
// by iceland
// modefied by emnil@sj	2/2/2000

inherit FORCE;
#include <ansi.h>
#include "/kungfu/skill/force.h"
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>
int get_bouns(int damage,int t,int level,int flag);
int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
	int i = (int)me->query_skill("longxiang-boruo", 1);

	if (((string)me->query("class") != "mizong") && i > 20)
		return notify_fail("��û�г��ң�������������������������ֻ����������һ�㡣\n");     

	if ((int)me->query_skill("force", 1) < 10)
		return notify_fail("Ҫѧ����������ȴ������ڹ������ɡ�\n");

	if ( me->query("gender") == "����" && i > 40)
		return notify_fail("�����������¸��ӣ���ﲻ�����������������Ƿ��������ɡ�\n");

	if ((int)me->query_con() < 30 && i > 120 )
		return notify_fail("��ĸ��ǲ�����������������������»��߻���ħ��\n");

	if ((int)me->query_skill("mizong-fofa",1)<120 && (int)me->query_skill("mizong-fofa",1)<i)
		return notify_fail("������ڷ𷨵���ⲻ�����谭����������������������\n");

	return valid_public(me);        
}

int practice_skill(object me)
{
	if((int)me->query_skill("longxiang-boruo", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("longxiang-boruo", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ�������������������ˡ�\n");   
	}
	else return notify_fail("���������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"longxiang-boruo/" + func;
}

void skill_improved(object me)
{
	int i = (int)me->query_skill("longxiang-boruo", 1);   

	if (i == 100)
	{
		 tell_object(me,HIW"���������ʮ�������Ѿ��������˵�һ���ˡ�\n");
	     me->set("lx/gree",1);
	}
	if (i == 150)
	{
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵ڶ����ˡ�\n");
        me->set("lx/gree",2);
	}
	if (i == 200) 
	{
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵������ˡ�\n");
	    me->set("lx/gree",3);
	}
	if (i == 250)
	{
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵��Ĳ��ˡ�\n");
	    me->set("lx/gree",4);
	}
	if (i == 300)
    {
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵�����ˡ�\n");
	     me->set("lx/gree",5);
	}
	if (i == 350)
	{
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵������ˡ�\n");
	    me->set("lx/gree",6);
	}
	if (i == 400)
	{
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵��߲��ˡ�\n");
	    me->set("lx/gree",7);
	}
	if (i == 450)
    {
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵ڰ˲��ˡ�\n");
	     me->set("lx/gree",8);
	}
	if (i == 500)
	{
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵ھŲ��ˡ�\n");
	    me->set("lx/gree",9);
	}
	if (i == 550)
	{
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵�ʮ���ˣ��Ѿ��߱���ʮ��ʮ��Ĵ�����\n"
					+"�Ժ������Ϳ����������������,�Ǵ󳹴����������Դﵽ��Ⱦ���ġ�\n\n");
	    me->set("lx/gree",10);
	}
	return ;
	
}

mapping exercise_msg(object me)
{
	if (me->query("gender")=="����") {
		return ([
			"status_msg" : CYN + me->name()+"������ɫƽ�ͣ��������أ�����ɽ��"NOR,
			"start_my_msg" : CYN"�����������ϥ��������������������һƬ�������������Ҿ��磬һ�����ȵ���Ϣ���ζ�����֮�����ߡ�\n"NOR,
			"start_other_msg" : CYN + me->name() +"��ϥ����������������������£��ǰ��������ɫƽ�ͣ�һ˿�쳱�������֣��������أ�����ɽ����\n"NOR,
			"halt_msg" : CYN"$N�е��������ͣ�ֻ��и����Ϣ������������������͸�����亹��\n"NOR,
			"end_my_msg" : CYN"��ֻ����Ԫ��һ��ȫ�������������Ը��ӣ��̲�ס��Хһ��������վ��������\n"NOR,
			"end_other_msg" : CYN + me->name()+"һ����Х��˫������һ�֣�����վ�����������������˸�����˲��ɱ��ӡ�\n"NOR
		]);
	}
	else {
		return ([ 
			"status_msg" : MAG + me->name()+"������ɫ���ޣ�������ͣ�����ֹˮ"NOR,
			"start_my_msg" : MAG"�����������Ŀ�������ִ����������Ⱥ������������֮���䣬��Ȼ֮�������������Ҿ��硣\n"NOR,
			"start_other_msg" : MAG + me->name() +"��Ŀ��ϥ������˫��ʮָ����������ǰ�����������Ƴ�������ӿ��һ����Σ�������ͣ�����ֹˮ��\n"NOR,
			"halt_msg" : MAG"$N�е��������ң�ȫ�����ȣ�ֻ���չ�վ��������\n"NOR,
			"end_my_msg" : MAG"��е��Լ��������Ϊһ�壬ȫ����ˬ��ԡ���磬�̲�ס�泩��������һ���������������۾���\n"NOR,
			"end_other_msg" : MAG + me->name()+"���з���һ���泩�����������ۻ���վ����������������˲���ͷ�ĺ�ˮ��\n"NOR
		]);
	}
}
//int hit_ob(object me, object victim, int damage_bonus)

mixed hit_ob(object me, object victim, int damage_bonus, int factor, string attack_skill)
{
	//���ʮһ�������Ծ��ʮ���������Ծ��ʮ���������Ծ�������⣬Խ��Խǿ��
	int skill;
	int i,j;
	object tweapon=victim->query_temp("weapon");
   
	if(!me->query_temp("xs/longxiang")){
		//message_vision(HIR"no temp 1"NOR,me);
		return 1;
	}
	
	skill = me->query_skill("force",1);

	i = damage_bonus * (skill+1) / 1000;
	i = i/2+ random(i);
	if(me->query_temp("weapon"))
		i = i*3;
	if(me->query_temp("apply/damage")>=1000)
		i = i/3;

	if(wizardp(me) && me->query("env/test")) 
		tell_object(me,sprintf("hit_ob: %d  ",i));
	//j = me->query_skill("longxiang-boruo",1)/50;
	j=(int)me->query("lx/gree");
	if (j<1) j=1;
	if ( j > 13) j = 13;
	//�������󣬴�϶Է�����
	//message_vision(HIW"i="+i+"j="+j,me);
	if (tweapon 
		&& random(me->query_skill("longxiang-boruo",1))>victim->query_skill("force",1)/2
		&& random(me->query_str(1))>victim->query_str(1)/2
		&& j>10
		&& tweapon->query("imbued") < 3)
	{
       message_vision(HIR"$N�������������"+HIR+"��$n����һ��,$n��ǰ��֮��������������������֪$N������������ᣬ����һ��,\n"NOR
	   +victim->query("name")+HIR"���е�"NOR+tweapon->query("name")+HIR"��Ϊ���ء�\n"NOR, me,victim);
	   tweapon->move(environment(victim));
	   tweapon->broken("��ϵ�");
	   //return 0;
	}
   //��ͨ����
	if (j<11)
	{
        message_vision(MAG"$N"+MAG+"��Ȼ���һ������"+CHINESE_D->chinese_number(j)+"��"
		+CHINESE_D->chinese_number(j)+"��֮������$n��\n" NOR, me,victim);
		i=i*j/10;
		//return i;//ʮ������֮���������ӳɣ�
		return get_bouns(damage_bonus,j,me->query_skill("longxiang-boruo",1),1);
	}
	//������������	
	if (j>10 
		&& me->query("quest/dls/longxiang/pass"))
	{
		message_vision(HIM"$N"+HIM+"��Ȼ���һ����������������"+CHINESE_D->chinese_number(j)+"��"	+CHINESE_D->chinese_number(j)+"��֮������$n��\n"NOR, me,victim);
		i=get_bouns(damage_bonus,j,me->query_skill("longxiang-boruo",1),1);
		if (random(me->query("neili"))>victim->query("neili")/2 
			&& random(10)>7)
		{
           message_vision(HIR"$nһʱ���飬Ϊ$N�����������ˣ����������������¯�������쳣��\n"NOR,me,victim);
		   victim->receive_damage("qi",i/2,me);
		   //write(HIC"���󹥻�����Ϊ"+i+NOR);
		   victim->receive_wound("qi",i/5,me);
		  // write(HIR"���󹥻���������Ϊ"+i/4+NOR);
		   if (!random(4))
		       victim->apply_condition("no_exert",1);
		}
		return get_bouns(damage_bonus,j,me->query_skill("longxiang-boruo",1),1);
	}
	
	//i = i + ::force_hit(me,victim,damage_bonus,factor,attack_skill);

	return i;
} 
int ob_hit(object ob, object me, int damage)
{
	int skill = me->query_skill("force",1);
	int skill2= ob->query_skill("force",1);
	int neili = me->query("neili");
	int neili2= ob->query("neili");
	int i = 1;
	mixed p, j;
	string msg;

	if(!me->query_temp("xs/shield"))
		return 1;
    if (me->query_temp("fanzhen"))
        me->add_temp("fanzhen",-1);
	p = me->is_busy();

	if ( random(skill) > skill2/2 ) {
		    if( (intp(p) && p < 2) || random(3)==1 ) {
				msg = MAG"$N"+MAG+"����������Ѵﻯ����Ĭ�������������󷨣���ȥ��$n"MAG;
			if(neili > neili2*2){
                msg += "��ȫ��������\n"NOR;
				if (me->query("quest/longxiang/pass"))
				    me->set_temp("fanzhen",3);
				i = -damage;
			}
			else if(neili > neili2){
				msg += "�󲿷ֵĹ�����\n"NOR;
				i = -(damage/2 + random(damage));
			}
			else {
				if(neili < neili2/4) {
					msg += "���ٵ�һ�㹥����\n"NOR;
					i = -random(damage/4);
				}
				else {
					msg += "һ���ֵĹ�����\n"NOR;
					i = -(damage/3+random(damage/2));
				}
			}
			if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("ob_hit: %d  ",i));
			if( objectp(me) && objectp(ob) )
				message_vision(msg, me, ob);		

		}
		else {
			j = me->is_busy();
			if ( intp(j))
				j = j/4 + random(j/2);
			else 
				j = 3;
			if(j < 3) j = 3;
			if(j > 10) j = 10;
			if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("busy:%d , dec busy:%d  ",me->is_busy(),j));
			me->add_busy(-j);
			msg = MAG"$N"MAG"��ͼ������������Ȼû�гɹ������ֽ��ƺ�����˲��٣�\n"NOR;
			
			if( objectp(me) && objectp(ob) )
				message_vision(msg, me, ob);		
		}
	}

	if(random(4)!=1) {
		if( ((damage+i) > 500) && (me->query("jing")>200) ) {
			j = (damage+i)/2;
			if( j > me->query("jing")) 
				j = me->query("jing") - 100;
			i = i -j ;
			me->add("jing", -j/10);
			if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("jing:%d ",j));
			message_vision(MAG"$N"MAG"üͷ������Ŭ�����Լ��ľ�����������$n"MAG"�Ĺ��ƣ�\n"NOR, me, ob);		
		}
	}

	return i;
}


int get_bouns(int damage,int t,int level,int flag)
{
	object me=this_player();
	int dm;
	dm= (damage*(t+level/20)*flag)/(t+level/20+10);
	//if(flag && level>500) dm += dm/2;
	if (me->query("quest/dls/longxiang/pass")) dm=dm*1.5;
	
	return dm;
}
