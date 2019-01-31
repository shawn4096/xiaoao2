

#include "ansi.h"
inherit NPC;
inherit F_MASTER;


void create()
{
        set_name("欧阳锋", ({ "ouyang feng", "ouyang", "feng" }));
        set("long","你走过来一看，他满腮须髯，根根如戟，一张脸犹如刺□相似，\n"+
                "正是你分别已久的义父欧阳锋。\n" );
        set("nickname","西毒");
        set("title", "白驼山庄庄主");
        set("gender", "男性");
        set("age", 65);
        set("attitude", "heroism");

        set_skill("cuff", 550);
        set_skill("strike", 500);
        set_skill("dodge", 550);
        set_skill("hamabu", 550);
        set_skill("parry", 550);
        set_skill("force", 550);
        set_skill("hamagong", 550);
        set_skill("lingshe-zhangfa",550);
		set_skill("lingshe-quanfa",550);

        set_skill("staff",550);
        set_skill("poison",300);
        map_skill("strike","hamagong");
		map_skill("cuff","lingshe-quanfa");
        map_skill("dodge","hamabu");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("force","hamagong");
        map_skill("staff","lingshe-zhangfa");
        prepare_skill("cuff","lingshe-quanfa");
		//prepare_skill("strike","hamagong");

        set("str", 35);
        set("int", 28);
        set("con", 30);
        set("dex", 28);

        set("max_qi", 55000);
        set("qi",55000);
        set("max_jing", 9000);
        set("jing",9000);
        set("neili", 56000);
        set("max_neili", 56000);
        set("jiali", 250);
        set("combat_exp", 15600000);

                  set("attitude", "peaceful");
                  set("shen_type", -1);

        create_family("白驼山", 1 , "庄主");
        set("inquiry", ([
                "欧阳锋" : "欧阳锋、欧阳锋，听起来这名字挺熟的。。。\n",
			                //"" : "欧阳锋、欧阳锋，听起来这名字挺熟的。。。\n",

         ]));

        setup();
        carry_object("/d/baituo/obj/gs-zhang")->wield();
        carry_object(ARMOR_D("cloth"))->wear();

}

int feng_say()
{
	command("angry ");
	command("say 老叫花你不要轻叫，这叫花棍法如何能和我灵蛇杖相比呢？");
	command("heng ");
	command("say 乖儿子，过来，这天下无狗也没什么了不起的，我就把为父最厉害的功夫传给你。\n");
	command("say 你替为父把这九阴逆转后的万蛇噬体演示给他看看，让老叫花子死也瞑目。\n");
	command("heng");
	command("heng");
	command("heng");
	command("heng");
}
