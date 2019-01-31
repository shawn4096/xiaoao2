//hxfang.c ���᷿
#include <ansi.h>

inherit ROOM;
string look_hongzao();
int do_naqu(string arg);

void create()
{
	set("short", "���᷿");
	set("long", @LONG
���Ǵ��������һ��С���䣬��ȻҲ����ʯ���ɣ������õķǳ����ʡ���
���ù�̺��ס����¶һ��ʯ�ڵĺۼ�������תȦ�ڷ���һЩ���ӣ��������ź�
�����棬����ȥһ�������ʡ������ǰ�����������ճ�����ĵط�������ͨ
���Ժ�������Ϸ��˼������ӣ��������кܶ�����(hongzao)��
LONG
	);
	set("exits", ([
		"north" : __DIR__"hhyuan-1",
		"south" : __DIR__"wztang",
	]));
	set("objects", ([
		"/kungfu/class/tiezhang/qqren" : 1,

		__DIR__"npc/yahuan" : 1,
		
// __DIR__"npc/qqren" : 1,
	
		]));
	set("item_desc", ([ 
		"hongzao" : (: look_hongzao :),
	]));
	set("hongzao_count",5+random(10));
	setup();
}
int init()
{
	//
	add_action("do_naqu","na");
}
string look_hongzao()
{
    return
    "\n������з��˺ܶ����棬���������ɿڣ�Ҳ������Գ�����ȡЩ(na)������"
    "\n";
}

int do_naqu(string arg)
{
	int i;
	object ob;
	object me=this_player();
	if (!arg || (arg != "hongzao" && arg != "����"))
        {
			if (query("hongzao_count") < 1)
			{
				message_vision ("$N����ץ����Щ���棬���ֺ����Ѿ���������û�ˣ�\n",me);
				return 1;
			}
        return notify_fail("������ʲô��\n");
       // return 1;
		}
		else{
			write(HIC"����Ȼ���֣��ӵ����Ͻ���Щ����ץ���֣�Ȼ�����ĳ���������\n"NOR);
			//this_player()->set_temp("marks/ժ2", 1);
			for (i=0;i<1+random(5);i++ )
			{			
				ob=new("/d/tiezhang/obj/zaohe");
				ob->move(me);
				add("hongzao_count", -1);
			}

        return 1;
       }


}
