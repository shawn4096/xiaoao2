// yaopu1.c
// ҩ��
inherit ROOM;
void create()
{
	set("short","ҩ��");
	set("long",@long
��������������ҩ�ԣ�ԶԶ��ȥ��ҩ�����ư���ͼ���У�ÿ��
ҩ���Ա߲���һ�����ӣ�����д�ˡ�Ǭ�����������￿������������
�ʺ�����ҩ�ĳɳ���
long);
	set("exits",([
	    "south" : __DIR__"yaopu",
            "west" : __DIR__"yaopu6",
            "north" : __DIR__"yaopu2",
]));
	set("no_clean_up",1);
	set("can_zhong",1);
	set("8type","Ǭ");
	set("outdoors", "������");
	setup();
}
	    	
