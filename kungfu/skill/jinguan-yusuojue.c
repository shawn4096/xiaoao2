// jinguan-yusuojue.c ȫ��̺����ķ�
// by sohu
//


inherit SKILL;
#include <ansi.h>
void init();

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	int i;
	if(me->query_int() < 30)
		return notify_fail("ȫ��������֮�ף����ƺ�����̫����������Щ��\n");
    i=me->query("yusuo/degree");
	if((int)me->query("shen") < 0 )
		return notify_fail("ȫ����������µ�һ��̣��������ɣ������а��������ᱯ�����˵������\n");
//	if((int)me->query_skill("jinguan-yusuojue", 1) >= 200 && !me->query("quest/qz/biguan/pass"))
		//return notify_fail("�㲻����ѧϰ����������İ����ˡ�\n");
	if((int)me->query_skill("jinguan-yusuojue", 1) > me->query("max_pot")-100 )
		return notify_fail("���ܾ������ޣ��޷��ٽ����ˡ�\n");
	if((int)me->query_skill("jinguan-yusuojue", 1) > me->query_skill("xiantian-gong",1) )
		return notify_fail("�������칦���ޣ�����������޷��ٽ����ˡ�\n");
	if ((int)me->query_skill("jinguan-yusuojue",1)>100 && !me->query("yusuo/degree"))
		return notify_fail("������������������ƿ������Ҫ���Ƶ�һ�عؿڷ��ɼ���������\n");
	if (me->query_skill("jinguan-yusuojue",1)>200 && i<2){

		return notify_fail("������������������ƿ������Ҫ���Ƶڶ��عؿڷ��ɼ���������\n");
		}
	if (me->query_skill("jinguan-yusuojue",1)>300 && (int)me->query("yusuo/degree")<3)
		return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
	if (me->query_skill("jinguan-yusuojue",1)>400 && (int)me->query("yusuo/degree")<4)
		return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
	if (me->query_skill("jinguan-yusuojue",1)>500 && me->query("yusuo/degree")<5)
		return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
	if (me->query_skill("jinguan-yusuojue",1)>600 && me->query("yusuo/degree")<6)
		return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
	if (me->query_skill("jinguan-yusuojue",1)>700 && me->query("yusuo/degree")<7)
		return notify_fail("������������������ƿ������Ҫ���Ƶ����عؿڷ��ɼ���������\n");
	if (me->query_skill("jinguan-yusuojue",1)>800 && me->query("yusuo/degree")<8)
		return notify_fail("������������������ƿ������Ҫ���Ƶڰ��عؿڷ��ɼ���������\n");
	if (me->query_skill("jinguan-yusuojue",1)>900 && me->query("yusuo/degree")<9)
		return notify_fail("������������������ƿ������Ҫ���Ƶھ��عؿڷ��ɼ���������\n");
	return 1;
}


int practice_skill(object me)
{

	return notify_fail("���������ֻ�ܿ��������������ߡ�\n");
}
