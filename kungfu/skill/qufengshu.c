//qufengshu.c
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
	return notify_fail("�������޷����ڣ�ֻ��ͨ���Լ�����������ָ��������������\n");
}

int practice_skill(object me)
{	
	
	return notify_fail("�������޷�ͨ����ϰ������ֻ��ͨ���Լ�����������ָ��������������\n");
}