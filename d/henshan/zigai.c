inherit ROOM;

void create()
{
       set("short", "�ϸǷ�");
        set("long", @LONG
������Ǻ�ɽ����е��ϸǷ壬������ȥ���������Ǻ�ɽ�����
����߷�ף�ڷ壬������ɽ���������ﺣ�νϸߣ�ÿ����ů����֮ʱ��
ɽ�ϵĻ�ѩ���ڻ������ϸ��ɶ��У�ˮ�����磬�������ϸǷ���ˮ��
������ٲ���
LONG );
	set("exits",([
	       "southdown":__DIR__"shanlu16",
	]));
	/*
        set("objects", ([
                CLASS_D("henshan") + "/xiang" : 1,
        ]));
     */
	set("outdoors","��ɽ");

     //   set("coor/x", 30);
	//set("coor/y", 40);
	//set("coor/z", 40);
	setup();
	//replace_program(ROOM);
}
