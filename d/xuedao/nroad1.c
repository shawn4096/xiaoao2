// nroad1.c
// Modified by Java Apr.27 1998

inherit ROOM;
void create()
{
        set("short","ɽ·");
        set("long",@LONG
ɽ·Խ��Խխ������������ǰ���ֳַ��˼�����·�������ƺ�����ɽ·��ͨ��ѩɽ���
�����ƺ���һƬȺɽ��������Լ������������š�
LONG );
        set("exits",([
                "westup"     : __DIR__"nroad2",
                "southup"    : __DIR__"sroad3",
                "northdown"  : __DIR__"nroad5",
        ]));
        set("outdoors", "xuedao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

