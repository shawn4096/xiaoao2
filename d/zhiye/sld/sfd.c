// fd.c
// �嶥
inherit ROOM;
void create()
{
	set("short","ɽ�嶥");
	set("long",@long
һ���������ǰ��ʱһ�����˴�����ɽ����ߴ���һ����ȥ��ֻ��
��ɽ��ˮ��������ӿ����Ŀ��֮��Զ�����ɼ�������Ӱ���˴��м������
�ŵ�������ͬ���Ĳ��ϴ����������ݣ��������ŵ�����Ҫ��ö࣬������
��һ���������д�š���������̳������֡�
long);
	set("exits",([
	    "down" : __DIR__"sanroadb",
          "enter" : __DIR__"slj",
]));
	set("outdoors", "������");
        set("coor/x",520);
  set("coor/y",430);
   set("coor/z",80);
   setup();
}
	    	