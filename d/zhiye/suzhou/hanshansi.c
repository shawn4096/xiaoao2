inherit ROOM;

void create()
{
        set("short", "��ɽ����");
        set("long",@long
�ഫ����Ԫ����䣬�к�ɽ�������˾�ס��������ɮϣǨ��ʦ�ڴ��ؽ���
Ժʱ������Ϊ��ɽ�¡����أ��ƿ�Ԫ��䣬ʫ���ż̸���Ӧ����ڣ���;�۴�
ͣ�����ţ���ʫһ�ף�����������˪���죬�������Գ��ߣ����ճ��⺮ɽ�£�
ҹ��������ʹ������Ӵˣ�ʫ�������������˿ڣ�����ʫ���������¡�
long);
	set("exits",([
 		"enter" : __DIR__"zhengdian",
		"southeast" : __DIR__"qsgdao5",
	]));
	set("objects", ([
		NPC_D("youke") : 1,
	]));
	setup();
}