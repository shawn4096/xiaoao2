// treew1.c
// ������1
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@long��
����������ö��ָ��д󣬴ִ����֦��������ཻ����һ����ס����
�⣬������ï�ܵ��Ӳݣ����������಻֪����Ұ����ɢ����������ܺ��ŵ���
���������Ϻ��Ӳ������������ڷ���˻˻��������
long);
	set("exits",([
	    "northeast" : __DIR__"treen2",
          "southeast" : __DIR__"trees2",
          "west" : __DIR__"sandw",
	]));
	set("objects",([
		__DIR__"snake/dushe" : 2,
	]));
	 set("outdoors", "������");
       set("canfindsnake",1);
        set("coor/x",480);
    set("coor/y",400);
    set("coor/z",0);
    setup();
}
	    	