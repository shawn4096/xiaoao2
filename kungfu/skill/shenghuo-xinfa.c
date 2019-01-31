// music.c

inherit SKILL;

void create() 
{ 
	seteuid(getuid()); 
}

string type() 
{ 
	return "knowledge"; 
}

int valid_learn(object me) 
{
	return 1;
	//return notify_fail("圣火心法只能通过读书来学习提高!\n");
}

int practice_skill(object me)
{	
	//return 1;
	return notify_fail("圣火心法只能通过读书来学习提高。\n");
}