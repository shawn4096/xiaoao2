// shandong3.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
int do_watch(string arg);
void create()
{
        set("short",HIR"ɽ��"NOR);
        set("long",@LONG
����һ��СС��ɽ����Ѫ������Ĳ���֮�ء���춴˵رȽ����أ�
��Һ���Ѱ��������������һ�Ź��������湩��ʲ�ᶫ�����㿴���塣
���ϻ���һЩģ�����������ͼ����Ҳ��֪����Щʲô��
LONG );
        set("exits",([
                "out" : __DIR__"shandong2",
				"east" : __DIR__"shandong31", //������
                "west" : __DIR__"shandong32", 
			    "north" : __DIR__"cave", 

        ]));
		set("no_fight",1);
        set("objects", ([
               "/kungfu/class/xuedao/miaodi" :1,
                "/d/xuedao/npc/x_lama" :1,
               
        ]));
		set("item_desc", ([
			"ͼ��" : HIR"		Ѫ��������ƪ--������"NOR
						+CYN"\n\n\n����һ������ͼ����һ�����ݸɿݵ��������ӣ�һ��ָ�죬һ��ָ��\n"
							+"��Ŀ���ǹ��죬�Ա�ע����������ɫ�Ĺ��֣�������򽣬������\n"
							+"������ͼ�����ӣ�����������Ŀ�������߶�������������\n"
							+"ò���ǹŹ֣�������֮�У������̲���һ������֮�������˲�����\n"
							+"�������ҡ���������ᡣ����������������������������������\n"NOR
							+"\n\n\n\nĩβ����["HIR"         Ѫ������"NOR"] �ĸ����֡�\n",
		]));

        setup();
        "/clone/board/xuedao_b"->foo();
		replace_program(ROOM);
}
void init()
{
	add_action("do_watch","guankan");
	add_action("do_watch","yanxi");
	add_action("do_watch","guanwu");

}
//����������

int do_watch(string arg)
{
        object ob = this_player();
        int lvl = this_player()->query_skill("",1);
		
		if (!arg||arg!="ͼ��")
		{
			 message_vision("$N������������������֪��Ҫ��ʲô��\n",ob);
                return 1;
		}
        if (!ob->query("quest/xuedao/shoujie"))
        {
                message_vision("$N��δ�ܽ䣬û���ܹ���ϲ��ϴ��\n",ob);
                return 1;
        }

        if ((int)ob->query_skill("force", 1) < 20)
        {
                message_vision("$N�Ļ����ڹ�����������������̵���ʲô��\n",ob);
                return 1;
        }
        if ((int)ob->query_skill("jingang-liantishu", 1) > 100)
        {
                message_vision("$N�Ľ����������ͳ�Խ���������ˡ�\n",ob);
                return 1;
        }
        if((lvl * lvl * lvl) > (int)ob->query("combat_exp"))
        {
                message_vision("$N��ʵս���鲻�㣬�޷�����������ݡ�\n",ob);
                return 1;
        }
        if (ob->query("jing")<20)
        {
                 message_vision("$N̫���ˣ������޷�����������ݡ�\n",ob);
                 return 1;
        }
        message_vision("$N����ű���ͼ����Ħ���ã�����Ѫ���Ž����������������\n",ob);
        ob->improve_skill("jingang-liantishu", random(ob->query("int")));
        ob->receive_damage("jing", 20);
		ob->start_busy(random(1));
        return 1;
}
