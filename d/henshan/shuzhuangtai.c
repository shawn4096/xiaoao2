inherit ROOM;

void create()
{
        set("short", "��ױ̨");
        set("long", @LONG
�ؾ�����һ����Ȫ�羵���������Ȫ���ഫΪ�ϳº������ڴ˱�
��ʱ���Ա�ˮ��������ױ���ĵط�����ǰʤ�������գ���ʱҹ�䳣
���ɹ⣬���緱�ǵ�㣬������ө�ҷɣ�ɷ��׳�ۡ�
LONG );
        set("exits", ([ 
               "north"   : __DIR__"cangjingdian",
        ]));

         set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

      //  set("coor/x", -70);
	//set("coor/y", 70);
	//set("coor/z", 20);
	setup();
      //  replace_program(ROOM);
}

