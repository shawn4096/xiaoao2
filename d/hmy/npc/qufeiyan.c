#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
        set_name("曲非烟", ({ "qu feiyan", "feiyan", "qu" }));
	//set("nickname", HIM "非非" NOR);
        //set("title", "日月神教");
	set("long", @LONG
这名女童约莫十三四岁年纪，穿一身翠绿衣衫，
皮肤雪白，一张脸蛋清秀可爱，无不对她生出同情之意。
LONG);
        set("gender", "女性");
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("per", 25);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
		set("age",14);

        set("max_qi", 9800);
        set("max_jing", 5600);
        set("eff_jingli", 5600);
        set("jiali", 50);
        set("combat_exp", 2500000);

        set_skill("hand", 220);
		//set_skill("sword", 200);

        set_skill("dodge", 220);
		set_skill("force", 220);
        set_skill("parry", 220);
        set_skill("tianmo-gong", 220);
        set_skill("huanmo-wubu", 220);
        set_skill("tianmo-shou", 220);
        set_skill("sword", 220);
        set_skill("qingxin-jian", 220);

        set_temp("apply/damage", 25);
        //set("combat_exp", 1800000);
		map_skill("dodge","huanmo-wubu");
		map_skill("force","tianmo-gong");
		map_skill("parry","qingxin-jian");

		map_skill("hand","tianmo-shou");
		map_skill("sword","qingxin-jian");
		prepare_skill("hand","tianmo-shou");

		create_family("日月神教",10,"弟子");

        setup();
        carry_object("/d/henshan/npc/obj/female-shoe")->wear();
		carry_object("/d/henshan/npc/obj/female1")->wear();
		carry_object("/clone/weapon/duanjian")->wield();

}
void attempt_apprentice(object ob)
{
     if(ob->query("str") < 25 ){
        command("say 练习天魔手需要高的臂力，你臂力不足25，我不收你！");
        return;
        }
	
	 if(ob->query("shen")>-10000 ){
        command("say 江湖异常惨烈，非奸即盗，你心肠太软若，小于-10k别来烦我？！");
        return;
        }
	 if(ob->query("gender") =="无性" ){
        command("say 你这种不男不女的货色来拜我为师？！");
        return;
        }
     command("haha");
	 command("say 真是好玩，为了光大日月神教，我就收下你了。");
     command("recruit " + ob->query("id"));
}