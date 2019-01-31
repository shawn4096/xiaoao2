// lao-qiao.c 乔三槐

inherit NPC;

void create()
{
	set_name("乔三槐", ({ "lao qiao", "qiao" }));
	set("gender", "男性");
	set("age", 55 );
	set("long",
		"他是一位两鬓斑白的老人，身穿一袭青布衣服。他身材略高，\n"
		"乃是江湖好汉“北乔峰”的父亲。\n"
	);
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set("qi", 400);
	set("max_qi", 400);
	set("eff_qi", 400);
	set("jing", 300);
	set("max_jing", 300);

	setup();

}
	
