//qusheshu.c 驱蛇术
//cre buy sohu@xojh
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
	return notify_fail("驱蛇术无法传授，只能通过自己不断培养并指挥演练来提升。\n");
}

int practice_skill(object me)
{	
	
	return notify_fail("驱蛇术无法通过练习提升，只能通过自己不断培养并指挥演练来提升。\n");
}