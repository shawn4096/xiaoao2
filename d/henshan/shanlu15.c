inherit ROOM;

void create()
{
	set("short","ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣����ǰ��Զ�����ϸǷ��ˡ�
LONG );
	set("exits",([
	        "southwest" : __DIR__"shuiliandong",
	        "northup"   : __DIR__"shanlu16",
	]));
	
	set("outdoors", "��ɽ");  
             
	//set("coor/x", 30);
//	set("coor/y", 20);
	//set("coor/z", 20);
	setup();
	//replace_program(ROOM);
}  	
