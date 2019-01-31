// shandong3.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
int do_watch(string arg);
void create()
{
        set("short",HIR"山洞"NOR);
        set("long",@LONG
这是一个小小的山洞，血刀老祖的藏身之地。由於此地比较隐秘，
仇家很难寻到这来。洞底有一张供桌，上面供了什麽东西，你看不清。
壁上画了一些模糊不清的文字图案，也不知道是些什么。
LONG );
        set("exits",([
                "out" : __DIR__"shandong2",
				"east" : __DIR__"shandong31", //兵器库
                "west" : __DIR__"shandong32", 
			    "north" : __DIR__"cave", 

        ]));
		set("no_fight",1);
        set("objects", ([
               "/kungfu/class/xuedao/miaodi" :1,
                "/d/xuedao/npc/x_lama" :1,
               
        ]));
		set("item_desc", ([
			"图案" : HIR"		血刀经初级篇--炼体术"NOR
						+CYN"\n\n\n那是一个人形图案，一个精瘦干枯的裸体男子，一手指天，一手指地\n"
							+"面目极是诡异，旁边注满了五颜六色的怪字，形若蝌蚪，或红或绿\n"
							+"你瞧着图中男子，见他钩鼻深目，曲发高额，不似中土人物，形\n"
							+"貌甚是古怪，而怪异之中，更似蕴藏着一股吸引之力，令人不由自\n"
							+"主地心旌摇动，神不守舍。。。。。。。。。。。。。。。。。。\n"NOR
							+"\n\n\n\n末尾刻着["HIR"         血刀老祖"NOR"] 四个大字。\n",
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
//修炼炼体术

int do_watch(string arg)
{
        object ob = this_player();
        int lvl = this_player()->query_skill("",1);
		
		if (!arg||arg!="图案")
		{
			 message_vision("$N东瞅西看，鬼鬼祟祟，不知道要看什么。\n",ob);
                return 1;
		}
        if (!ob->query("quest/xuedao/shoujie"))
        {
                message_vision("$N尚未受戒，没有受过欢喜佛法洗礼。\n",ob);
                return 1;
        }

        if ((int)ob->query_skill("force", 1) < 20)
        {
                message_vision("$N的基本内功不够，看不懂上面刻的是什么。\n",ob);
                return 1;
        }
        if ((int)ob->query_skill("jingang-liantishu", 1) > 100)
        {
                message_vision("$N的金刚炼体术早就超越壁上所刻了。\n",ob);
                return 1;
        }
        if((lvl * lvl * lvl) > (int)ob->query("combat_exp"))
        {
                message_vision("$N的实战经验不足，无法领悟壁上内容。\n",ob);
                return 1;
        }
        if (ob->query("jing")<20)
        {
                 message_vision("$N太累了，现在无法领悟壁上内容。\n",ob);
                 return 1;
        }
        message_vision("$N面对着壁上图案揣摩良久，对于血刀门金刚炼体术似有所悟。\n",ob);
        ob->improve_skill("jingang-liantishu", random(ob->query("int")));
        ob->receive_damage("jing", 20);
		ob->start_busy(random(1));
        return 1;
}
