inherit ROOM;

void create()
{
        set("short", "é����");
        set("long", @LONG
�����ǰٻ����ڿ�������һ��é���ݡ�һ��������ɣ�é��ո��
��ȻΪ�´���á�����ڷ��˼������䣬�в��ٰ�����ڷ䷿����
��Щ��������ǹ��죬��Ȼ����Ѱ��Ʒ�֡�
LONG);
        //set("outdoors", "quanzhen");
        set("exits", ([
                "out" : __DIR__"baihuagu",
				      
        ]));
		set("objects", ([
              "kungfu/class/quanzhen/zhou" :1,
        ]) );

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}


