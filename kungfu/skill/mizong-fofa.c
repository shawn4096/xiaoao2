// huanxi-chan.c ��ϲ��

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
    if( me->query("class") != "mizong")
        return notify_fail("��Ǵ����µ��ӣ�ѧϰ���ڷ��к��ã�\n");
    if( (int)me->query_skill("mizong-fofa", 1) < 200 )
        return notify_fail("���ڷ𷨱���ͨ��ڤ���޳ֲſ��Եõ���\n");
	if( (int)me->query_skill("mizong-fofa", 1) >= 200 )
        return notify_fail("�㲻����ѧϰ���ڷ𷨾�Ҫ�ˡ�\n");
    return 1;
}

int practice_skill(object me)
{       
        
		return notify_fail("���ڷ�ֻ�ܿ�ѧϰ����ߡ�\n");
}
