// mizong-neigong
#include <ansi.h>
inherit FORCE;

#include "/kungfu/skill/force.h"
int valid_enable(string usage)
{
        return usage == "force";
}

int valid_learn(object me)
{
	int lvl, i;
	mapping fam = me->query("family");
	string fam1;
	fam1=fam->query("family/family_name");
      lvl = (int)me->query_skill("mizong-neigong", 1);
      i = (int)me->query_skill("huanxi-chan", 1);
	
	  
	    if (fam1!="Ѫ����")
	          return notify_fail("�����ڹ���������ר�޵ķ��ţ�������ʦ���ڻ��߻���ħ�ġ�\n");
      
		 if ( me->query("gender") == "����" && lvl > 49)
                return notify_fail("���޸����ԣ���������������������������ڹ���\n");

        //if ( !me->query("class") == "huanxi" )
                //return notify_fail("�����ڹ����Ƕ��ص�һ�����з��ţ��㲻�������������������⣿\n");

        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if ( i<200 && (lvl-i)<10)
                return notify_fail("��Ļ�ϲ���ȼ������������ϰ�����ڹ���\n");
		if ((int)me->query_con() < 30 && i > 120 )
	        	return notify_fail("��ĸ��ǲ����������������ڹ����»��߻���ħ��\n");

        return ::valid_learn(me);
				
}



int practice_skill(object me)
{
	if((int)me->query_skill("mizong-neigong", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("mizong-neigong", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ��������������ڹ��ˡ�\n");   
	}
	else return notify_fail("�����ڹ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"mizong-neigong/" + func;
}
/*
mixed hit_ob(object me, object victim, int damage_bonus, int factor, string attack_skill)
{
	int skill;
	int i = 1,j;	
    //��ӡ
	if(!me->query_temp("xuedao/shouyin"))
		return 1;
	
	skill = me->query_skill("mizong-neigong");

	i = damage_bonus * (skill+1) / 1000;
	i = i/2+ random(i);
	if(me->query_temp("weapon")) //��������������������
		i = i*3;
	//if(me->query_temp("apply/damage")>=100)
		//i = i/3;
	if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("hit_ob: %d  ",i));
	
	j = me->query_skill("mizong-neigong",1)/50;
	
	if ( j > 13) j = 13;
	message_vision(HIY"$N"+HIY+"��Ȼ���һ������������һ����ƿӡ������һƬа������Ц�Ź���$n��\n" NOR, me,victim);

	//i = i + ::force_hit(me,victim,damage_bonus,factor,attack_skill);

	return i;
} 
*/