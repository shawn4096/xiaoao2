// shanlu-1.c �ϼ�
#include <ansi.h>
//#include <room.h>

inherit ROOM;
string look_hongzao();

void create()
{
   set("short", GRN"�ϼ�"NOR);
	set("long", @LONG
ת��һ��С�䣬��Ȼ��ǰһ�̣���ǰ��һƬ�ܴ�Ĺϼܡ��ڸߴ��ľ���ԣ�
��ֲ��һЩ�߲˺͹��࣬�������������˸���ֲ���ï�ܵ�Ҷ���У����¸�
���Ѿ�����Ĺ�ʵ��˿�ϣ���ϣ���«....����һЩ�в������ƵĹϹ�Ҳ����
�����С��ϼ�һ���м���������������˲��ٵĴ����(hongzao)��

LONG
);


    set("outdoors", "tiezhang");

	set("exits", ([
		"southeast" : __DIR__"shuijing.c",
		"west" : __DIR__"guangchang.c",
		]));

    set("objects", ([
		__DIR__"npc/qqzhang" : 1,
	]));
	set("item_desc", ([ 
		"hongzao" : (: look_hongzao :),
	]));
	set("no_clean_up", 0);
    set("hulu_count", 10);
	set("hongzao_count", 100);
	setup();
}

void init()
{
        add_action("do_zhai","zhai");
		add_action("do_cai","caizhai");
}

int do_zhai(string arg)
{
        object me = this_player();
        object ob;

        if (me->query_temp("marks/ժ1") )
            return notify_fail("���Ѿ�ժ���ˣ���Ҫ��ô̰�ģ�\n");

        if (!arg || (arg != "hulu" && arg != "��«"))
        {
        if (query("hulu_count") < 1)
        {
			message_vision ("$N����֦Ҷ������ȥ�����ֺ�«�Ѿ�������ժû�ˣ�\n",this_player());
			return 1;
        }
			return notify_fail("����ժʲô��\n");
			return 1;
		}

{
        write("������ż⣬�Ӽ�����ժ����һ����«��\n");
        this_player()->set_temp("marks/ժ1", 1);

            ob=new("/d/tiezhang/obj/qingshui-hulu");
            ob->move(this_player());
            add("hulu_count", -1);

        return 1;
       }
}
string look_hongzao()
{
    return
    "\n�⼸�����ϳ��˺ܶ����棬Ҳ������Բ�ժЩ(caizhai)������"
    "\n";
}

int do_cai(string arg)
{
        object me = this_player();
        object ob;
		int i=0;

       //if (me->query_temp("marks/ժ2") )
           // return notify_fail("���Ѿ�ժ���ˣ���Ҫ��ô̰�ģ�\n");

        if (!arg || (arg != "hongzao" && arg != "����"))
        {
			if (query("hongzao_count") < 1)
			{
				message_vision ("$N����֦Ҷ������ȥ�����ֺ����Ѿ�������ժû�ˣ�\n",this_player());
				return 1;
			}
        return notify_fail("����ժʲô��\n");
        return 1;
		}
		else{
			write("��������������������ժ���˺ܶ����档\n");
			//this_player()->set_temp("marks/ժ2", 1);
			for (i=0;i<1+random(5);i++ )
			{			
				ob=new("/d/tiezhang/obj/hongzao");
				ob->move(this_player());
				add("hongzao_count", -1);
			}

        return 1;
       }
	
}