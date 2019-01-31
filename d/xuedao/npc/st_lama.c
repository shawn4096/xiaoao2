// x_lama.c 小喇嘛

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("小喇嘛",({
		"xiao lama",
		"xiao",
		"lama",
	}));
	set("long",
                "这是专门负责血刀门吃喝的小喇嘛，长得五大三粗，膀大腰圆。\n"
	);
	set("title", "茶室主事");
	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "bonze");

        set("age", 13);
        set("shen_type", 0);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 100);
	set("max_jing", 100);
	set("neili", 100);
	set("max_neili", 100);
	set("combat_exp", 50);

	setup();
	carry_object("/d/xueshan/npc/obj/qinxiu-jiasha")->wear();
}
