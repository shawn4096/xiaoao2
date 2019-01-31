// zhou-zhiruo.c
// Lklv 2001.10.18 update hehe 小妞

inherit F_MASTER;
inherit NPC;
#include <ansi.h>

int ask_zhang();
int ask_dragon();
int do_jiuyin();
void create()
{
	set_name("周芷若", ({ "zhou zhiruo", "zhou", "zhiruo"}));
	set("long", "她是灭绝师太的八大俗家第子之一，一副清色衣衫，显的楚楚动人。\n");
	set("gender", "女性");
	set("attitude", "friendly");
	set("age", 25);
	set("shen_type", -1);
	set("str", 42);
	set("int", 42);
	set("con", 42);
	set("dex", 42);
	set("per", 40);

        set("max_qi", 15000);
        set("max_jing", 5000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 250);
        set("combat_exp", 9500000);
        set("score", 100);

        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "claw.jiuyin" :),
					(: perform_action, "whip.chanrao" :),
					(: perform_action, "whip.feilong" :),
		}));

        set_skill("literate", 350);
	    set_skill("sword", 350);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 480);
        set_skill("strike", 350);
		set_skill("sixiang-zhang", 350);
		set_skill("hand", 350);
		set_skill("jieshou-jiushi", 350);
        set_skill("claw", 480);
        set_skill("anying-fuxiang", 450);
        set_skill("jiuyin-baiguzhua", 480);
	    set_skill("huifeng-jian", 350);
        set_skill("dacheng-fofa", 150);
        set_skill("linji-zhuang", 480);
		set_skill("yinlong-bian", 480);
		set_skill("whip", 450);
        set("apply/attack", 50);
        set("apply/dexerity", 50);
        create_family("峨嵋派", 3, "俗家新掌门");

        map_skill("force", "linji-zhuang");
        map_skill("parry", "yinlong-bian");
        map_skill("claw", "jiuyin-baiguzhua");
        map_skill("sword", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
		map_skill("whip", "yinlong-bian");
		map_skill("strike", "sixiang-zhang");
		map_skill("hand", "jiehshou-jiushi");
		  
        prepare_skill("claw", "jiuyin-baiguzhua");

        set("inquiry",([
		"张无忌" : (: ask_zhang :),
		"九阴银龙鞭技巧" : (: do_jiuyin() :),
		"光大峨嵋" : (: ask_dragon :),
		"光大我派" : (: ask_dragon :),
        ]) );
        //create_family("峨嵋派", 4, "弟子");

        setup();
		carry_object("clone/weapon/whip/whip")->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();
}
int prevent_learn(object ob, string skill)
{
	if (skill == "jiuyin-baiguzhua"||skill == "yinlong-bian")
		return 1;
	return 0;
}

void attempt_apprentice(object ob)
{
        if (! ob->query("family")) {
		command("say 你非我峨嵋派弟子，我不能收你。\n");
		return;
        }
        if ((int)ob->query_skill("claw", 1) < 100 ) {
		command("say 你基本爪法火候未到100，我不能收你。\n");
		return;
        }
        if ((int)ob->query_skill("strike", 1) < 100 ) {
		command("say 你基本掌法火候未到100，我不能收你。\n");
		return;
        }
	if (ob->query("class") == "bonze"){
		command ("blush");
		command ("say 我只收俗家弟子。");
		return;
	}
        if ((int)ob->query_skill("jiuyin-baiguzhua", 1) < 100 ) {
		command("say 你的爪子太弱了，不足100，我现在不想收徒。\n");
		return;
        }
        command("recruit " + ob->query("id"));
        command("chat* grin");
		command("chat "+ob->query("name")+"以后就是我的人了，还望江湖同道给小女子个薄面,行走江湖之际，多给与照顾!\n");
		command("chat* heng");
		command("chat 若有人胆敢欺负我的人，我大峨眉可不是好惹的！!\n");
        command("chat* grin");
}

int ask_zhang()
{
	object me=this_player();
	if( me->query_temp("jiuyin140") == 2 ) {
		command("blush");
		command("say 虽然我已经发誓不再喜欢他，但他的影子无时无刻不出现在我的脑海里。\n");
		command("say 我终究不能欺骗自己，更不能欺骗师父，师傅教给我的倚天屠龙的秘密和光大我派的想法终究是不能实现了。\n");
		command("sigh");
		me->set_temp("jiuyin140", 3 );
		return 1;
	}
	message_vision("周芷若瞪了$N一眼。\n", me);
	return 1;
}

int ask_dragon()
{
	object me=this_player();
	if( me->query_temp("jiuyin140") >= 3 ) {
		if( me->query("family/master_name") != "周芷若"
	 	 && !me->query_skill("jiuyin-baiguzhua",1) ) {
			command("say 你现在不是我的徒弟，也没有从我这里学到什么东西。就凭你现在的武功很难做到武林至尊的，也就更谈不上光大峨嵋了。\n");
			return 1;
		}
		command("say 既然如此，你到我师傅那里询问倚天屠龙的秘密吧。\n");
		command("say 光大峨嵋的希望只能寄托与你了。\n");
		command("sigh");
		me->set_temp("jiuyin140", 4 );
		return 1;
	}
	message_vision("周芷若淡淡地看了$N一眼，摇了摇头。\n", me);
	return 1;
}

//说明缘由，然后去找一个地方。。解密去

int do_jiuyin() 
{
	object me = this_player();
	
	if(this_object()->is_fighting()) return 0;
	
	if(me->query("family/family_name")!="峨嵋派")
		if (!me->query_temp("ryb/jiuyin_askdue")) //若经由渡厄推荐可以来一次
		{
			command("heng "+me->query_id());
			command("say 你和我门派有什么关系，赶紧给我滚！");
			return 1;
		}
	if(me->query("shen")<0)
	{
		command("heng "+me->query_id());
		command("say 峨嵋乃名门正派，赶紧给我滚！");
		return 1;
	}
	if(me->query("quest/em/zzr/pass"))
	{
		command("heng "+me->query_id());
		command("say 你已经将九阴银龙鞭的秘密融会贯通，来消遣我么？");
		return 1;
	}
	
	 message_vision(HIC"$N向$n请教有关银龙鞭法的使用技巧。\n"NOR, me, this_object());
	
	 command("look "+me->query("id"));	
	

	
    
	me->set("quest/em/zzr/ylb/time",time());
	me->set("quest/em/zzr/ylb/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("think ");
	command("consider ");
	if (me->query_temp("ryb/jiuyin_askdue"))
	{
		command("mei ");
		command("say 既然是少林渡厄大师的请求，那我就跟你讲解一下。\n\n\n");
	}
	command("say 这是九阴真经中所载的武功，既然你已经习得了这门武功，那我就把这当中的经过说给你听听。");
    command("say 徒儿啊，这招银龙鞭的使用技巧乃是为师多年心血所得，你要好好听好了。\n");
	command("say 当初我秉承师傅大志，誓把本门流落在外的武功都寻找回来，终于有一天，机缘巧合。\n");
	command("say 当我得到这屠龙宝刀和倚天剑后，终于知道了其中的秘密。帮助本门把失落的秘籍寻找回来\n");
	command("say 我想我对得起师傅的在天之灵了。\n");
	command("say 你若有心，我把这门心法都刻在藏经楼，可以去看看,能否得到就看你的机缘了。\n");
	command("whisper "+me->query("id"));
	
	command("smile "+me->query("id"));
	me->set_temp("quest/em/zzr/askzhou",1);
	return 1;
}