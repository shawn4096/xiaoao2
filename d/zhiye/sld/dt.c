// dt.c
//
// ����
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@long
����һ��˶����������ӣ����������ǧ��֮�ڡ������˶˾��в���
�����������Σ����˽��е��ӣ���Ȼ�Ǹ����������ġ��˴���������ƽ
������֮����
long);
	set("exits",([
	    "north" : __DIR__"th",
         "south" : __DIR__"slj",
		 "west" : __DIR__"shenlongtang",     
]));
set("objects",([
	"/kungfu/class/sld/hongantong" : 1,
	//"/kungfu/class/sld/sq" : 1,
	//"/kungfu/class/sld/ptt" : 1,
	//"/kungfu/class/sld/stt" : 1,
	__DIR__"npc/cyjz" : 2,
]));
	set("coor/x",520);
  set("coor/y",440);
   set("coor/z",90);
   setup();
}
	    	
