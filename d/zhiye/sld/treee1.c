// treee1.c
// ���ֶ�1
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@long
����������ö��ָ��д󣬴ִ����֦��������ཻ����һ����ס����
�⣬������ï�ܵ��Ӳݣ����������಻֪����Ұ����ɢ����������ܺ��ŵ���
���������Ϻ��Ӳ������������ڷ���˻˻��������
long);
	set("exits",([
	    "northwest" : __DIR__"treen2",
          "southwest" : __DIR__"trees2",
          "east" : __DIR__"sande",
	]));
	set("objects",([
		__DIR__"snake/dushe" : 2,
	]));
	set("outdoors", "������");
    set("canfindsnake",1);
    set("coor/x",500);
	set("coor/y",410);
	set("coor/z",0);
	setup();
}
	    	