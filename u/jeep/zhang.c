// zhang.c 张三丰
// Modified by Lklv for raozhi Quest @@
// Update By lsxk@hsbbs for taiji_quest 2007/6/3
// By Spiderii@yt 加入yttlg quest
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_me_1();
string ask_me_2();
string ask_me_3();
string ask_me_4();
string ask_me_5();
string ask_raozhi();
string ask_no_save();
string ask_jueyuan();
string ask_jiuyang();
string ask_taiji();
int thinking_tjq(object me);
int ask_yttlg();

#define NO_SAVE_ID "/log/skills/no_lifesave"

void create()
{
        object weapon;
        set_name("张三丰", ({ "zhang sanfeng", "zhang", "sanfeng" }));
        set("nickname", "邋遢真人");
        set("long",
                "他就是武当派开山鼻祖、当今武林的泰山北斗张三丰真人。\n"
                "身穿一件污秽的白色道袍，不修边幅。\n"
                "身材高大，年满百岁，满脸红光，须眉皆白。\n");
        set("gender", "男性");
        set("age", 100);
        set("attitude", "peaceful");
        set("str", 33);
        set("int", 45);
        set("con", 33);
        set("dex", 33);
        set("per", 28);
        set("unique", 1);
        set("no_get", 1);
		set("max_qi", 65000);
        set("max_jing", 10500);
        set("eff_jingli", 8000);
        set("max_neili", 33000);
        set("neili", 33000);
        set("jiali", 200);
        set("combat_exp", 17000000);
        set("shen", 64000);
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: exert_function, "yinyun" :),
                (: perform_action, "cuff.dongjing" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "cuff.an" :),
                (: perform_action, "cuff.yinyang" :),
                (: perform_action, "cuff.gangrou" :),
                (: perform_action, "sword.sanhuan" :),
                (: perform_action, "cuff.zhannian" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "cuff.luanhuan" :),
                (: perform_action, "cuff.ji" :)
        }));
        set_skill("force", 550);
        set_skill("yinyun-ziqi", 551);
        set_skill("dodge", 550);
        set_skill("tiyunzong", 550);
        set_skill("cuff", 550);
        set_skill("taiji-quan", 551);
        set_skill("parry", 550);
        set_skill("sword", 550);
        set_skill("taiji-jian", 551);
        set_skill("taoism", 220);
        set_skill("blade", 550);
        set_skill("zhenwu-qijiezhen", 200);
        set_skill("literate", 300);
        set_skill("zhenshan-mianzhang", 550);
        set_skill("strike", 550);
        set_skill("wudang-quan", 550);
        set_skill("xuanxu-daofa", 550);
        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "zhenshan-mianzhang");
        map_skill("blade", "xuanxu-daofa");
        prepare_skill("cuff", "taiji-quan");
        set("inquiry", ([
                "真武剑" : (: ask_me_1 :),
                "考验" : (: ask_me_2 :),
                "太极拳理" : (: ask_me_3 :),
                "太极拳绝技" : (: ask_taiji :),
		        "离山" : (: ask_me_4 :),
                "下山" : (: ask_me_4 :),
                "教诲" : (: ask_me_5 :),
         //		"敌对" : (: ask_no_save :),
                "绕指柔剑" : (: ask_raozhi :),
                "倚天屠龙功" : (: ask_yttlg :),
        ]));
        set("wan_count", 1+random(2) );
        create_family("武当派", 1, "开山祖师");
        set("class", "taoist");
        set_temp("apply/damage", 70);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 100);
        set_temp("apply/armor", 70);
        set_temp("tj/taiji", 1);
        set("taiji_quest", 1);
        setup();
        if (clonep()){
                weapon = unew(BINGQI_D("sword/zhenwu-jian"));
                if (!weapon) weapon = new(BINGQI_D("zhujian"));
                weapon->move(this_object());
                weapon->wield();
                carry_object("/d/wudang/obj/white-robe")->wear();
                carry_object("/d/wudang/obj/daolv")->wear();
        }
}

void init()
{
        object ob;

        ::init();
        ob = this_player();
        if (interactive(ob = this_player()) && visible(ob) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }

}

void greeting(object me)
{
        mapping myfam;
        int shen;

        if (!me || !present(me)) return;

        if ( file_name(environment(this_object())) != this_object()->query("startroom")) return;

        myfam = (mapping)me->query("family");
        shen = me->query("shen");

        if (me->query("taiji_zsf") >= 6 && me->query("taiji_quest"))
                me->delete("taiji_quest");

        if(!myfam) return;
        else if(myfam["family_name"] != "武当派")
                command("say 老道在此清修，是什么风把这位"+RANK_D->query_respect(me)+"吹来了？");
        else if(shen < 0 && shen > -15000)
                command("say  想学好功夫，要先修正做人，你目光微带邪气，还是多去做几件侠义之事吧。");
        else if(shen < -15000){
                command("say 你身为武当弟子，行素不正，今天你就不在是我武当弟子了。");
                command("expell " + me->query("id"));
        }
        else command("nod");
}

void attempt_apprentice(object ob)
{
        mapping fam = ob->query("family");
        if ((!fam || fam["family_name"] != "武当派")
         && ob->query("expell/family_name") != "武当派"){
                command("say "+RANK_D->query_respect(ob)+"与本派素无来往，不知此话从何谈起？");
                return;
        }
        if ((int)ob->query_skill("yinyun-ziqi", 1) < 350) {
                command("say 我武当派乃内家武功，最重视内功心法。你的氤氲紫气还没小飞，尚需努力。");
                command("say " + RANK_D->query_respect(ob) + "是否还应该在氤氲紫气上多下点功夫？");
                return;
        }
        if ((int)ob->query("shen") < 2000000) {
                command("say 学武之人，德义为先，功夫的高低倒还在其次，未练武，要先学做人。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否还做得不够？(2M)");
                return;
        }
        if(fam["family_name"] == "武当派" 
			&& ob->query_skill("juehu-shou",1)>350 
            && ob->query_skill("yinyun-ziqi",1)<151 
            && random(10)< 2
			&& ob->query("juehu_nouse")<1){
                command("look " + ob->query("id"));
                message_vision(HIY"只见张三丰微微将袍袖一抖。\n"NOR, ob);
                write(HIR"你忽然觉得身体微微一热。\n"NOR,ob);
                ob->set("juehu_nouse",1);
                command("say 我武当素有侠名，择徒甚严，我封住你赤阳两穴，那绝户手过于阴毒，以后不要再练了。");
        }
		if (ob->query_int() < 32) {
                command("say 我武当派武功全从道藏悟出。");
                command("say 要能达到炉火纯青之境，体质什么的倒是无关紧要，悟性却是半点也马虎不得。");
                command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
                return;
        }
        command("say 哈哈哈哈！！！！");
        command("say 想不到老道在垂死之年，又觅得"+ob->name(1)+"这样一个可塑之才，真是可喜可贺。");
        command("recruit " + ob->query("id"));
}

void kill_ob(object me)
{
        if(!wizardp(me))
                command("crazy " + me->query("id"));
        if(!this_object()->query_temp("weapon"))
                command("enable parry taiji-quan");
        command("exert taiji");
        ::kill_ob(me);
}

void unconcious()
{
          command("say 贫道今日始信天外有天，人外有人！");
        ::unconcious();
}

string ask_taiji()
{
	object me = this_player();
	mapping fam;

     if (!(fam = me->query("family")) || fam["family_name"] !="武当派"||fam["master_name"] !="张三丰")
           return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
	 if ( time()-me->query("quest/tjq/time")<86400)
     {
		command("shake "+ (string)me->query("id"));
		return "你心浮气躁，如何能练好太极拳？!\n";
	  }
	 
	 if ( me->query("quest/tjq/taiji")=="pass")
		return "你不是已经领会了太极奥意了吗?切记要行侠仗义,不可到处炫耀!\n";
	 if ((int)me->query_skill("taiji-quan",1)<450)
		return "你太极拳还尚未熟练,怎能理解这高深莫测得太极奥意?\n";
	 if ((int)me->query_skill("cuff",1)<450)
		return "你基本拳法还尚未熟练,怎能理解这高深莫测得太极奥意?\n";
	 if ((int)me->query_skill("yinyun-ziqi",1)<450)
		return "这太极奥意乃要依靠浑厚得氤氲紫气才能发挥,你还是先将本门的氤氲紫气多多练习熟练!\n";
	 if ((int)me->query_skill("taoism",1)<200)
		return "你对道学心法参悟尚太低,若现在传授太极奥意与你,只会害你练功时走火入魔!\n";

		command("nod "+ (string)me->query("id"));
		command("say 不错,"+ (string)me->query("name") +"，太极乃是一门以慢打快，以静制动，以柔可刚的高深功夫，正所谓先发至于人，后发而制人讲的就是这个道理。");
        command("say 太极功夫，从招数开始练起，越练越精，太极有所成时，招数却成了阻碍太极修炼的一大因素，此时，习武者若能真正理解太极\n所谓招式的真正含义，则不难看出，太极招式乃“虚”招，太极厉害之处却是无招的境界！");
		command("say 无招，无破绽，人纯随意而动，随力而变，这才是真正的太极功夫。");
		command("say 太极大成者虽是无招，可所有动作均围绕“掤，捋，挤，按，采，挒，肘，靠。”这八个字而来。只有真正理解这八字真言，才能将太极奥意真正地发挥出来。");
		command("say "+ (string)me->query("name") +"你可听懂了么？");
     
	  tell_object(me,MAG"\n你开始认真的回忆张三丰的一招一式。。\n"NOR);
      me->start_busy(999);              
      remove_call_out("thinking_tjq");
      call_out("thinking_tjq",5, me );
	  return "";


/*


   if(!random(5) ||
      (me->query_temp("sj_credit/quest/wd/taiji") && !random(3))// 增加使用道具后，解quest的成功率
      ){
           me->delete_temp("sj_credit/quest/wd/taiji");
		me->set("quest/tjq/taiji","pass");
		message_vision(HIW"由尊师张三丰这么一说，$N当下暗暗思索，顿觉脑中对太极的理解进入了一个前所未有的新境界！！\n"NOR, me);
		message_vision(CYN"$N突然仰天大笑“哈,哈，哈！原来如此，原来如此啊，太极可真是深奥的很啊！”,显然已经参悟了师尊的教诲！\n"NOR,me);
           command("chat* haha "+ (string)me->query("id"));
           command("chat* congra "+ (string)me->query("id"));
		return "既然"+(string)me->query("name") +"已经领悟了太极奥意，今后行走江湖，更应当锄强扶弱，让武当派武功发扬光大！\n";
	}
	else{
           me->delete_temp("sj_credit/quest/wd/taiji");
		message_vision(HIY"$N抓耳挠腮，苦思冥想，发现自己还是无法理解太极奥意所在，脸上一筹莫展。\n"NOR,me);
		command("hoho "+ (string)me->query("id"));
		me->set("quest/tjq/taiji","faild");
		return "看来"+(string)me->query("name") +"你还需要多加练习才行！\n";
	}
	*/
}

int thinking_tjq(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("try_tjq")<(5+random(3)))
	{ 
		me->add_temp("try_tjq",1);
		if(random(2)) tell_object(me,HIG"\n你认真回想着刚才张三丰所传授太极拳的一招一式...\n"NOR);
		else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
		tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
		remove_call_out("thinking_tjq");
		call_out("thinking_tjq",3+random(3), me);
	}
	else
	{  
		me->delete_temp("try_tjq");
		total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
		j = 25;
		if(me->query("m-card-vip")) j =  22;
		if(me->query("y-card-vip")) j =  20;
		if(me->query("buyvip"))     j =  17;
		i=random(j);

		if (i == 4 && random(me->query("kar")) >= 27)
		// && random(total) >= 80 		 
		{
			tell_object(me,HIM"$N按照张三丰的指点，由起手式开始，一招一招演练起来，宛如行云流水！\n"NOR);
			message_vision(HIC"$N熟能生巧，陡然间你忽然明白了运转如长江大河，滔滔不绝的意境。”\n"NOR,me); 
			tell_object(me,HIR"$N又忽然懂得了太极拳的以慢打快，后发制人的诀窍，对于太极拳的认识大大不同！\n"NOR);
			tell_object(me,HIY"$N终于懂得了太极拳终极绝技奥秘，不禁连声大笑，原来如此，原来如此！\n"NOR);
			tell_object(me,HIW"$N将方才的所得暗暗思索，顿觉脑中对太极的理解进入了一个前所未有的新境\n"NOR);
			command("haha");
			command("chat 恭喜"+me->query("name")+"已经深明太极拳奥意，懂得了太极拳精意。");
			me->set("quest/tjq/taiji", "pass" );
			me->set("title",HIR"武当派太极拳高手"NOR);
			log_file("quest/taijiquan", sprintf("%s(%s) 失败%d次后，成功解开太极拳奥秘。富源：%d；经验：%d。\n",   
			me->name(1),
			me->query("id"), 
			me->query("quest/tjq/fail"),
			me->query("kar"),
			me->query("combat_exp")) );
			me->start_busy(1);
        }
        else
        {
			tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
			message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
			message_vision(HIY"$N抓耳挠腮，苦思冥想，发现自己还是无法理解太极奥意所在，脸上一筹莫展。\n"NOR,me);
			tell_object(me,HBBLU"\n很可惜，你本次尝试太极拳绝技秘密失败！\n"NOR);
			tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
			tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
			log_file("quest/taijiquan", sprintf("%s(%s) 解密太极拳绝技失败%d次。富源：%d；经验：%d。\n",   
			me->name(1),
			me->query("id"), 
			me->query("quest/tjq/fail"),
			me->query("kar"),
			me->query("combat_exp")) );
			me->add("quest/tjq/fail",1);
			me->set("quest/tjq/exp", me->query("combat_exp") );
			me->start_busy(1);
			me->set("quest/tjq/time",time());
		}
	}
	return 1;
}

string ask_me_1()
{
	object me=this_player();
	if (me->query("family/family_name") != "武当派")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";

	command("pat "+ me->query("id"));
		return "此剑乃本门镇山之宝！不经过考验我如何能放心交你保管？\n";
}

string ask_me_2()
{
	object me=this_player();
	if (me->query("family/family_name") != "武当派")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";
	command("thumb "+ me->query("id"));
		return "你把郭女侠送我的礼物找来，就算你通过考验！你到我年轻时练功的附近找吧。\n";
}

string ask_me_3()
{
	mapping fam;
	string msg;
	object me=this_player();
	fam = me->query("family");

	if (!fam || fam["family_name"] !="武当派")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";
	if (fam["master_name"] !="张三丰"){
		command("pat "+me->query("id"));
		return "太极拳理你现在还无法理解。\n";
	}

	if(me->query("taiji_quest")){
		if(me->query("taiji_quest") <= me->query("taiji_zsf"))
			return "我不是已经教了你歌诀吗？快去练习吧。\n";
		if(me->query("taiji_quest") == 1) msg = " 顺项贯顶两膀松，束肋下气把裆撑，威音开劲两捶争，五指抓地上弯弓。\n";
		if(me->query("taiji_quest") == 2) msg = " 举步轻灵神内缄，莫教断续一气研，左宜右有虚实处，意上寓下后天还。\n";
		if(me->query("taiji_quest") == 3) msg = " 拿主丹田练内功，哼哈二气妙无穷，动分静合屈伸就，缓应急随理贯通。\n";
		if(me->query("taiji_quest") == 4) msg = " 忽隐忽现进则长，一羽不加至道藏，手慢手快皆非似，四两拨千运化良。\n";
		if(me->query("taiji_quest") == 5) msg = " 极柔即刚极虚灵，运若抽丝处处明，开展紧凑乃缜密，待机而动如猫行。\n";
		if(me->query("taiji_quest") == 6){
			msg = " 棚履挤按四方正，采列肘靠斜角成，乾坤震兑乃八卦，进退顾盼定五行。\n";
			me->delete("taiji_quest");
		}

		command("nod "+me->query("id"));
		command("whisper "+me->query("id")+msg);
		tell_object(me,"你听了张三丰的讲解，对太极之道又领悟了不少。\n");
		me->add("max_neili", 10+random(20));
		me->add("max_jingli", 10+random(20));
		me->add("shen", random(3000)+1000);
		me->add("taiji_zsf", 1);
		return "这句歌诀，你要认真记住。\n";
	}
	return "太极之意你现在还无法理解。\n";
}

string ask_me_4()
{
	object me=this_player();

	if (me->query("family/family_name") != "武当派")
		return RANK_D->query_respect(me)+"施主既然要离山，贫道就不远送了。";
	command("pat "+ (string)me->query("id"));
	command("say 江湖险恶，身为正道，你要多为百姓做些行侠仗义的事。");
	me->set_temp("jian_quest",1);
	return "记得为师的教诲，若为非做歹，我定不饶你！。\n";
}

string ask_me_5()
{
	object me=this_player();
	object ob;
	string ob_desc;
	int i,j;

	i = me->query("combat_exp")/ 200000;
	if (i < 50)  i = 50;
	if (i > 100)  i = 100;
	j = me->query_skill("taiji-jian",1)/ 5;
	if (j < 50)  j = 50;
	if (j > 100)  j = 100;

	if (me->query("family/family_name") != "武当派")
		return RANK_D->query_respect(this_player())+"不是贫道弟子，何谈教诲？";

	if (! me->query_temp("jian_quest") || me->query("combat_exp")<100000)
		return "若为非做歹，我定不饶你！去吧。\n";

	if (present("songwen gujian",me))
		return "记住为师的话，多行侠仗义，给你的剑一定要收好。";

	command("nod "+ (string)me->query("id"));
	command("say 我武当乃侠义正道，当以匡扶正义为己任。");
	command("say 神兵利器，虽然锋利，对我等习武之人却无益处。");
	command("say 摘叶飞花，皆可伤人。树枝草叶，皆可为剑。我以千年松木制得此剑，虽不如干将、莫邪，");
	command("say 功力到深处，却也不输于倚天、屠龙。记得为师的教诲，去吧。");
	command("party* "+"wave "+(string)me->query("id"));
	me->delete_temp("jian_quest");
	me->add("shen",100+random(100));

	ob = new(BINGQI_D("sword/sw_jian"));

	ob_desc = sprintf("剑上刻着一行小字：武当秘藏,张三丰赠弟子%s(%s)佩用,见此物如见三清世尊。\n",me->query("name"),me->query("id"));

	ob->set("long",ob_desc);
	ob->set("rigidity", 5);
	ob->set("weapon_prop/parry", i);
	ob->set("weapon_prop/sword", j);
	ob->set("owner", me->query("id"));

	ob->move(me);
	message_vision("\n$N给了$n一把古意盎然的木剑。\n", this_object(), me);

	return "你好自为之。\n";
}

int accept_object(object who, object ob)
{
	object sword, me;
	mapping fam;
	me = this_object();

	if (!(fam = this_player()->query("family")) || fam["family_name"] !="武当派"){
		command("thank "+ (string)who->query("id"));
		command("say 你与本派素无来往，不知为何送如此厚礼？");
		return 0;
	}

	if (fam["generation"] == 2)
	if ((string)ob->query("id") == "tie luohan"){
		command("goodkid "+(string)who->query("id"));
		call_out("destroying", 1, ob);
		if (present("zhenwu jian", me)){
			command("give zhenwu to "+(string)who->query("id"));
			command("say 你如果用这剑为非做歹，我必取你性命！");
			return 1;
		}
		else{
			sword = unew(BINGQI_D("sword/zhenwu-jian"));
			if (!clonep(sword)) {
				command("say 啊！真老糊涂了，剑不知放哪了。");
				return 1;
			}
			sword->move(this_player());
			command("say 你如果用这剑为非做歹，我必取你性命！");
			return 1;
		}
	}
	command("? "+ (string)who->query("id"));
	command("say 今天不是老道的生日，你送什么礼呀！");
	return 0;
}

void destroying(object obj)
{
	if (!obj) return;
	if (userp(obj)) command("drop "+obj->parse_command_id_list()[0]);
	else destruct(obj);
}

string ask_no_save()
{
	object ob, me = this_player();
	string *no_save, id, tmp;

	me->add_busy(1);
	if (me->query("family/family_name") != "武当派")
		return RANK_D->query_respect(this_player())+"施主这样问是什么意思？";

	command("hmm "+ (string)me->query("id"));

	if( me->query("combat_exp") < 1000000 )
		return "本门弟子，只要行得正，还怕什么？\n";

	if( me->query("last_kzf") )
		return "你行为不正，还要来挑拨师门？\n";

	if( !stringp(id = me->query("last_killer")) )
		return "本门弟子，只要行得正，还怕什么？\n";

	if( sscanf(id, "%s(%s)", tmp, id) != 2 )
		return "本门弟子，只要行得正，还怕什么？\n";

	id = lower_case(id);

	ob = LOGIN_D->find_body(id);
	if ( !ob || !userp(ob) )
		return "此人是谁，你要查清楚了再来。\n";

	if( ob->query("family/family_name") == "武当派" )
		return "同门师兄弟，应该和睦相处，你们这样，老道十分伤心啊！\n";

	if( file_size(NO_SAVE_ID) > 0 )
		no_save = explode(read_file(NO_SAVE_ID), "\n");
	else no_save = ({});

	if( member_array(id, no_save) != -1 )
		return "此人老道已经知道了，你以后看见要小心应付！\n";
	no_save += ({ id });
	id = implode(no_save, "\n") + "\n";

	write_file(NO_SAVE_ID, id, 1);

	command("nod");
	return "江湖险恶，要小心应付，一定要记得为师的教诲啊！\n";
}

string ask_raozhi()
{
	object me=this_player();
	if (me->query("family/family_name") != "武当派")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";

	if (me->query("raozhi")){
		command("knock "+me->query("id"));
		return "臭记性！教过你的剑招怎么忘记了？";
	}

	if (!me->query_temp("raozhi"))
		return RANK_D->query_respect(me)+"为何有此一问？";

	if (me->query_skill("yinyun-ziqi", 1) < 200
	|| me->query_skill("taiji-jian", 1) < 200)
		return RANK_D->query_respect(me)+"功夫太低，这些你现在还无法领会。";

	if (random(3)>1 && me->query_temp("raozhi") > 2 && random(me->query("kar")) > 20){
		me->set_temp("raozhi",3);
		return YEL"我新创了一招剑法，不过今天不想教给你，你改天再来吧。\n"NOR;
	}
	me->set("raozhi",1);
	command("pat "+ me->query("id"));
	command("secret "+ me->query("id"));
	return HIC"那是我新创的一招剑法，还没有在对阵中用过，现在我就教给你吧。\n"NOR;
}

int ask_yttlg() 
{
	object me = this_player();
	object ob = this_object();

	if(!me->query_temp("quest/yttlg/ask"))
	{
		command("? "+me->query("id"));
		command("say 你问这个做什么?");
		return 1;
	}
	me->delete_temp("quest/yttlg/ask");
	command("pat "+me->query("id"));
	message_vision(HIC"\n\n$n微笑着对$N说道：「可要看仔细了!」,说罢重又打了遍倚天屠龙功!\n"NOR,me,ob); 
	remove_call_out("thinking");
	call_out("thinking",5, me, ob);
	tell_object(me,YEL"你拼命地回忆张三丰手指的走势，你开始认真思索着.........\n"NOR);
	me->start_busy(2);
	return 1;
}

int thinking(object me, object ob)
{
	int p;
	if(!me) return 0;
	if(me->query_temp("yttlg_thinking")<(3+random(3)))
	{
		me->add_temp("yttlg_thinking",1);
		if(random(2)) tell_object(me,HIG"\n你努力地回忆刚才张三丰手指的走势,只觉得眼花缭乱...\n"NOR);
		else tell_object(me,HIY"\n突然间，你似乎抓到了什么，你努力地回忆刚才张三丰手指的走势，你似乎感觉到了其中的变化所在...\n"NOR);
		tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，一服愁眉不展的样子。\n"NOR, ({}));
		remove_call_out("thinking");
		call_out("thinking",3+random(3), me, ob);
	}
	else
	{
		me->delete_temp("yttlg_thinking");

		p = random(10);

		if(p>5&&me->query("kar")>20 && me->query("kar")<31 )
		{
			tell_object(me,HIG"\n你此时生怕将刚才的精妙招式忘了，当即盘膝坐下，一笔一划、一招一式的默默记忆。\n"NOR);
			tell_object(me,HIG"\n你当兴之所至，便起身试演几手。也不知过了多少时候，才将那二十四字二百一十五笔中的腾挪变化尽数记在心中。\n");
			tell_object(me,HIG"\n你只觉扬波搏击，雁飞雕振，延颈协翼，势似凌云，全身都是轻飘飘的，有如腾云驾雾一般。\n");
			message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
			tell_object(me,HIR"你听了张三丰的指点,终于领悟了倚天屠龙功的精华所在。\n"NOR);
			me->set("quest/yttlg/pass",1);
			me->delete_temp("quest/yttlg/ask");
			me->set_skill("yitian-tulong",1);
			log_file("quest/yttlg", sprintf(HIR"%s(%s) 成功解开倚天屠龙功。富源：%d；经验：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
		}
		else
		{
			tell_object(me,HIG"\n你脑海里似乎抓住了什么，可是依然不是很明白。\n"NOR);
			message_vision(HIC"\n$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n"NOR,me); 
			command("poor "+me->query("id"));
			me->add("quest/yttlg/fail",1);
			me->delete("quest/yttlg/ask");
			log_file("quest/yttlg", sprintf(HIR"%s(%s) 解倚天屠龙功失败。富源：%d；经验：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
		}
	}
	return 1;
}

string ask_jueyuan()
{
	object me;
	mapping fam;
	me = this_player();
	if ( !me->query("can_learn/jiuyang/wudangjunbao"))
	{
		command("? "+me->query("id"));
		return "这位" + RANK_D->query_respect(me) + "觉远乃老道我当年的恩师。。。不知道郭襄最近可好啊！\n";
	}
	if ((int)me->query("combat_exp") < 1100000)
		return "你的经验还不足，还需再接再厉啊！\n";

	if((int)me->query_skill("jiuyang-gong", 1) >= 1
	||(int)me->query_skill("wudang-jiuyang", 1) >= 1
	||(int)me->query_skill("emei-jiuyang", 1) >= 1
	){
		return"你不是学会九阳神功了吗？怎么还来来消遣贫道我？\n";
	}

	if(me->query("can_learn/jiuyang-shengong/wudang"))
		return"嗯！觉远师傅当年传授我的部分九阳神功，我已经转化为武当九阳了！\n";

	command("say  既然是觉远师傅要你来找我的，那肯定是师傅的恩人。");
	me->add("can_learn/jiuyang-shengong/wudang", 1);

	return "你问觉远大师做什么？";
}

string ask_jiuyang()
{
    object me;
	mapping fam;
	me=this_player();
	if ( !me->query("can_learn/jiuyang-shengong/wudang"))
	{
		command("? "+me->query("id"));
		return "这位" + RANK_D->query_respect(me) + "觉远乃老道我当年的恩师。。。不知道郭襄最近可好啊！\n";
	}
	if ((int)me->query("combat_exp") < 4300000)
		return "你的经验还不足，还需再接再厉啊！\n";

	if((int)me->query_skill("jiuyang-gong", 1) >= 1
	||(int)me->query_skill("wudang-jiuyang", 1) >= 1
	||(int)me->query_skill("emei-jiuyang", 1) >= 1
	){
		return"你不是学会九阳神功了吗？怎么还来来消遣贫道我？\n";
	}

	if(me->query("can_learn/jiuyang/wudangkaishi"))
		return"嗯！觉远师傅当年传授我的部分九阳神功，我已经转化为武当九阳了！\n";

	command("say  既然是觉远师傅要你来找我的，那肯定是师傅的恩人。");
	me->add("can_learn/jiuyang-shengong/wudang", 1);
	me->add("can_learn/jiuyang-shengong/wudangkaishi", 1);
	return "我可以将武当九阳传授予你。";
}

int recognize_apprentice(object who, string skill)
{
	if (! who->query("can_learn/jiuyang-shengong/wudangkaishi"))
	{
		command("say 这位" + RANK_D->query_respect(who) + "言重了，贫道本事低微，何谈“指点”二字。");
		return -1;
	}

	if (skill != "wudang-jiuyang")
	{
		command("say 正所谓“知足而乐，能忍则安”，其它武功请恕贫道不能教授。");
		return -1;
	}
	return 1;
}

