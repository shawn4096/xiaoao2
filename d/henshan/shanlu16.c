inherit ROOM;

void create()
{
	set("short","ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣����ǰ��Զ�����ϸǷ��ˡ�
LONG );
	set("exits",([
	        "southdown" : __DIR__"shanlu15",
	        "northup" : __DIR__"zigai",
	]));
	
	set("outdoors", "��ɽ");    
          
	//set("coor/x", 30);
	//set("coor/y", 30);
	//set("coor/z", 30);
	setup();
	//replace_program(ROOM);
}  	
