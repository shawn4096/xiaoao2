// sanpo6.c
// ɽ��6
inherit ROOM;
void create()
{
	set("short","ɽ��");
	set("long",@long
ɽ·���˴���Ȼ��ֹ�������������졣�˴�ɽ�µ�������һ���յأ�
�м�������ɫ��װ���������䣬�ڿյر����м������ݣ������м�һ��
��������д�š������š������֣���������涼���ͱڣ���������·������
��ȥ������������С·��ͨ����̳�������ǵ����Ǽ�����������
long);
	set("exits",([
	    "north" : __DIR__"sanroada",
            "westdown" : __DIR__"sanroad8",
          "enter" : __DIR__"blm",
			"east"  : __DIR__"xiaolu1",
]));
	set("outdoors", "������");
        set("coor/x",520);
  set("coor/y",420);
   set("coor/z",60);
   setup();
}
	    	
