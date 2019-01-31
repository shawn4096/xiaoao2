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
	
	  
	    if (fam1!="血刀门")
	          return notify_fail("密宗内功乃是喇嘛专修的法门，不得名师传授会走火入魔的。\n");
      
		 if ( me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的密宗内功。\n");

        //if ( !me->query("class") == "huanxi" )
                //return notify_fail("密宗内功乃是独特的一种修行法门，你不出家如何能理解其中深意？\n");

        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的基本内功火候还不够。\n");

        if ( i<200 && (lvl-i)<10)
                return notify_fail("你的欢喜禅等级不够，如何修习密宗内功？\n");
		if ((int)me->query_con() < 30 && i > 120 )
	        	return notify_fail("你的根骨不够，再修炼密宗内功恐怕会走火入魔。\n");

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
		else return notify_fail("你现在的修为不足以提高密宗内功了。\n");   
	}
	else return notify_fail("密宗内功只能用学(learn)的来增加熟练度。\n");
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
    //手印
	if(!me->query_temp("xuedao/shouyin"))
		return 1;
	
	skill = me->query_skill("mizong-neigong");

	i = damage_bonus * (skill+1) / 1000;
	i = i/2+ random(i);
	if(me->query_temp("weapon")) //带有武器，攻击力倍增
		i = i*3;
	//if(me->query_temp("apply/damage")>=100)
		//i = i/3;
	if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("hit_ob: %d  ",i));
	
	j = me->query_skill("mizong-neigong",1)/50;
	
	if ( j > 13) j = 13;
	message_vision(HIY"$N"+HIY+"陡然大喝一声，左手捏了一个宝瓶印，脸上一片邪气，淫笑着攻向$n！\n" NOR, me,victim);

	//i = i + ::force_hit(me,victim,damage_bonus,factor,attack_skill);

	return i;
} 
*/