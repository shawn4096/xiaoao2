//�������
// by sohu
// �����ķ�

 
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me) 
{
        int lvl;
        
        lvl = (int)me->query_skill("tingfeng-bianqi", 1);
        
        if(me->query("gender") == "����" && lvl > 10)
                return notify_fail("�����һ����������޷��������ķ��������������\n");
        return 1;
}

int practice_skill(object me)
{       
        return notify_fail("�������ֻ�ܿ���������ߡ�\n");
}