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
	return notify_fail("ʥ���ķ�ֻ��ͨ��������ѧϰ��ߡ�\n");
}

int practice_skill(object me)
{	
	return notify_fail("ʥ���ķ�ֻ��ͨ��������ѧϰ��ߡ�\n");
}