#include <ansi.h>
inherit NPC;
void create()
{
        set_name("阿大", ({ "a da", "ada" }) );
        set("title", HBRED"八臂神魔"NOR);
        set("long", "他就是赵敏随行的三个仆人中老大。这人身材瘦长，满脸皱纹，愁眉苦脸，\m似乎刚才给人痛殴了一顿，要不然便是新死了妻子儿女，\n旁人只要瞧他脸上神情，几乎便要代他伤心落泪\n");
        set("gender", "男性" );
        set("age", 54);
		set("con",25);
        set("dex",25);
        set("unique", 1);
        set("per", 20);
        set("no_get", 1);
        set("max_qi", 30000);
        set("max_jing", 7000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 200);
        set("combat_exp", 13500000);
        set("eff_jingli", 7000);

        set_skill("force", 480);
        set_skill("hunyuan-yiqi", 480);
        set_skill("dodge", 480);
        set_skill("shaolin-shenfa", 480);
        set_skill("finger", 500);
        set_skill("jingang-zhi", 520);
        set_skill("parry", 480);
        set_skill("literate", 150);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "jingang-zhi");
        map_skill("parry", "jingang-zhi");
        prepare_skill("finger", "jingang-zhi");
    	set("chat_chance", 60);
    	set("chat_msg_combat", ({
        	(: perform_action, "finger.fumo" :),
        	(: perform_action, "finger.jingangzhi" :),
        	(: perform_action, "finger.lianhuan" :),
        }));
        setup();
        carry_object("/d/wudang/obj/white-robe")->wear();/**/
}
int greet_ada()
{
	command("heng ");
	command("say 那也好。我在殿外等候便是。!");
	command("say 老朽百死余生，过去的事说他作甚？我早不是丐帮的长老了。");
	command("say 八臂神剑方东白已经死了。");
	command("say 临阵学武，未免迟了罢？");
	command("say 有僭了！看招!");
	return 1;

}