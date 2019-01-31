// azi.c 阿紫
// Update by caiji@SJ 8/27/2000

inherit NPC;
inherit F_MASTER;

string ask_san();
string ask_for(object);
string ask_you();
string ask_tietou();

void create()
{
        set_name("阿紫", ({ "azi", "a zi", "a" ,"zi"}));
        set("nickname", "星宿派小师妹");
        set("long", "星宿派小师妹。一个身穿紫衣的美貌少女。瓜子白净脸, 眼神中总是透出一股邪气。\n");
        set("gender", "女性");
        set("age", 15);
        set("attitude", "peaceful");
        set("env/wimpy", 110);
//	set("apprentice", 1);

        set("str", 18);
        set("int", 28);
        set("per", 30);
        set("con", 20);
        set("dex", 24);

        set("max_qi", 8400);
        set("max_jing", 15200);
        set("jiali", 100);
        set("combat_exp", 2000000);
        set("shen", -1000);

        set_skill("force", 220);
        set_skill("huagong-dafa", 220);
        set_skill("dodge", 220);
        set_skill("zhaixingshu", 220);
        set_skill("strike", 220);
        set_skill("chousui-zhang", 220);
        set_skill("parry", 220);
        set_skill("poison", 60);
        set_skill("literate", 80);
        set_skill("claw", 220);
        set_skill("sanyin-zhua", 220);

        map_skill("claw", "sanyin-zhua");
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixingshu");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");
        prepare_skill("strike", "chousui-zhang");

        create_family("星宿派", 2, "弟子");

        set("inquiry", ([
                "星宿派" : "你想加入，就拜我为师。\n",
                "深涧" : "从毒虫谷里就会走到天山后山深涧中去。\n",
               // "星宿海" : "去星宿海干什么？拜我为师就够你学的了。\n",
               // "丁春秋" : "丁春秋是你叫的吗？没大没小的。以后叫老仙！\n",
                //"老仙" : "你得多吹捧老仙，否则别想有出头之日。\n",
                "神王木鼎" : "神木王鼎放到后山山洞里了。有本事你自己去拿。\n",
                //"姐夫" : "连我姐夫萧峰都不知道，你真是个大呆瓜。\n",
                //"星宿" : "你问的可是星宿派？\n",
                //"吹捧" : "女的容易多了，我最讨老仙喜欢。男的得更加把劲。\n",
                "解药" : (: ask_san :), //add by caiji
				"清心散" : (: ask_san :), //add by caiji
				"披风" : (: ask_for, "pifeng" :),//add by caiji
				"游坦之" : (: ask_you:),
				"铁丑" : (: ask_tietou:),
        ]));
        setup();
        set("pifeng_count",6);
        set("san_count",6);
        carry_object("/d/xingxiu/obj/yao");
	//add by caiji        carry_object("/d/xingxiu/obj/qxs");
	carry_object(ARMOR_D("baihu-qiu"))->wear();
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") > -10000){
		command("say 你看上去真是个假正经，我才不想收你呢。不足10k负神别来找我。");
		return;
     }
	command("hehe " + ob->query("id"));
	ob->set("class","xingxiu");
	command("recruit " + ob->query("id"));
}

string ask_san()
{
        int exp;
        object drug, me, ob;
        mapping fam;

        me = this_object();
        ob = this_player();
        fam = (mapping)ob->query("family");
        exp=ob->query("combat_exp",1);

        if(!fam || exp < 200000 || fam["family_name"] != "星宿派")
                return "就凭你也想要星宿的独门解药？\n";
        if( (int)ob->query_skill("huagong-dafa", 1) < 150 )//....caiji
                return "你的化功大法功力太浅，不足150，我怎么能信任你呢？\n";
        if (!ob->query("quest/xx/dichuan"))
				return "你非我大星宿嫡传弟子，我怎么能信任你呢？\n";
		if(me->query("san_count") >= 1 && (!ob->query_temp("san_given"))){
                        me->add("san_count", -1);
                        drug = unew("/d/xingxiu/obj/qxs");
                        if (!clonep(drug)) return "你来晚啦，都被你师兄们拿走了。\n";
                        drug->move(ob);
                        ob->set_temp("san_given", 1);
                        message_vision("$N对$n点了点头，交给$n一小包清心散。\n", me, ob);
                        return "自己用就行了，千万不要交给外派弟子！\n";
        }
        if(ob->query_temp("san_given"))
                     return "我不是给过你了吗？\n";
        return "你来晚啦，都被你师兄们拿走了。\n";
}

string ask_for(string name)
{
        mapping fam;
        object ob;

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "星宿派")
                return RANK_D->query_rude(this_player()) +
                "又不是星宿弟子，凭什么向我要这要那的！";

        if (  present(name, this_player()) )
                return RANK_D->query_rude(this_player()) +
                "你现在身上不是有这样防具吗，怎麽又来要了？ 真是贪得无餍！";
       if (!this_player()->query("quest/xx/dichuan"))
				return "你非我大星宿嫡传弟子，我怎么能信任你呢？\n";

        if (query("pifeng_count") < 1)
                return "抱歉，你来得不是时候，披风已经发完了。";

        ob = new("/d/xingxiu/obj/" + name);
        ob->move(this_player());

        add("pifeng_count", -1);

	message_vision("$N给$n一件" + ob->query("name") + "。\n",this_object() ,this_player());

        return "这可是件好东西，别弄丢了。";
}
string ask_you()
{
	object me=this_player();

	
	command("say 游坦之？我不知道谁是游坦之！我只知道我们这儿有个铁丑!\n");
	command("xixi ");
	command("say 这个铁丑真是好玩，很有意思！\n");
	this_player()->set_temp("bingcan/askyou",1);
	return "游坦之？这名字好熟！\n";
}
string ask_tietou()
{
	if (!this_player()->query_temp("bingcan/askyou"))
	{
		command("say 铁丑是我的仆人，你来打听这个干啥？\n");
		return "他真是傻子\n";
	}
	command("say 上个月我让铁丑替我找了头天山冰蚕，由神木王鼎炼化，使得我功力大进！\n");
	command("xixi ");
	command("say 这个铁丑真是好玩，很有意思！\n");
	this_player()->set_temp("bingcan/asktietou",1);
	return "铁丑是我的仆人，他对我衷心不二！\n";
}