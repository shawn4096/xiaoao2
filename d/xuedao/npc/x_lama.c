// x_lama.c С����

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("С����",({
		"xiao lama",
		"xiao",
		"lama",
	}));
	set("long",
                "����Ѫ��������ǰ��С���һ�������������������Ų��á�\n"
	);
	set("title", "Ѫ���ŵ������̷����");
	set("gender", "����");
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