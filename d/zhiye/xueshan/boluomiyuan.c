// Room: boluomiyuan.c

inherit ROOM;

void create()
{
	set("short", "������Ժ");
	set("long", @LONG
Ժ������������ΰ�������������ߣ�����Ъɽ�����ڹ�����֮��������
����������ޣ��ý���������ꪶ��ӣ����ƷǷ�������²�������������Ʋ�
�ø߸����ǳ�����ã���������ڲ����ƺ�֮�У������仯��
LONG
	);

        set("exits", ([
		"west" : __DIR__"huilang8",
	]));

	setup();
}