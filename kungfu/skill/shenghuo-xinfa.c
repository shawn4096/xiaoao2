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
	//return notify_fail("ʥ���ķ�ֻ��ͨ��������ѧϰ���!\n");
}

int practice_skill(object me)
{	
	//return 1;
	return notify_fail("ʥ���ķ�ֻ��ͨ��������ѧϰ��ߡ�\n");
}