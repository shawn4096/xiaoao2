// slj.c
// ������
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@long
����һ���ܳ������ȣ��������ȵ����߷��������������ʻ������ȵ�
ǰ�ߺ���߸���һ���š��Ҳ��ǽ���һƬ�޴�����ƺ�����ǻ�������
��ȥһ����������ʯ��ͨ����ɽ��
long);
	set("exits",([
	    "north" : __DIR__"dt",
           "west"  : __DIR__"road1",	
		"east"  : __DIR__"caoping",	
          "out" : __DIR__"sfd",
]));
	set("coor/x",520);
  set("coor/y",430);
   set("coor/z",90);
   setup();
}
	    	
