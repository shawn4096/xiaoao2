// 渔人

inherit NPC;
#include <ansi.h>

string ask_fish();
string ask_yideng(string name);
int check_yuren(object me);

string ask_diao();

void create()
{
	set_name("渔人", ({ "yu ren", "yu", "ren" }) );
	set("long", "见他约莫四十来岁年纪，一张黑漆漆的锅底脸，虬髯满腮，根根如铁。\n");
	set("gender", "男性" );
	set("age", 45);
	set("str", 30);
	set("con", 30);
	set("dex", 25);
	set("int", 25);
	set("per", 20);
	set("unique", 1);
	set("attitude", "friendly");

	set("max_qi", 25000);
	set("max_jing", 12800);
	set("eff_jingli", 13600);
	set("neili", 18000);
	set("qi", 25000);
	set("jingli", 13600);
	set("max_neili", 18000);
	set("jiali", 200);

	set("combat_exp", 12300000);
	set("score", 5000);

	set_skill("parry", 400);
	set_skill("dodge", 400);
	set_skill("force", 400);
	set_skill("literate", 200);
	set_skill("qiantian-yiyang", 400);
	set_skill("tianlong-xiang", 400);
	set_skill("finger", 400);
	set_skill("yiyang-zhi", 400);
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
	map_skill("force", "qiantian-yiyang");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");

	set("inquiry", ([
		"金娃娃" : "金娃娃就是金色的娃娃鱼。",
		"一灯大师" :(: ask_yideng, "一灯大师" :),
		"段皇爷" : (: ask_yideng, "段皇爷" :),
		"钓叟绝技" :(: ask_diao:),

	]));
	setup();

	carry_object(ARMOR_D("b_cloth"))->wear();
	carry_object(ARMOR_D("caoxie"))->wear();
}
string ask_diao()
{
	object me;
	int i,j;

	me=this_player();
	if (!me->query_temp("quest/tls/askzhu"))
	{
		command("say 你和我认识么？\n");
		return "哼！\n";
	}
	//限制次数
	if (me->query("quest/tls/qxbf/diao/pass"))
		return "你不是已经把清虚鞭钓字诀学完了!\n";
	if (time()-me->query("quest/tls/qxbf/diao/time")<86400)
		return "你来的太频繁了\n";
	if (me->is_busy()) return "你正在忙碌中！\n";
	if (!me->query_temp("quest/tls/giveyu"))
	{
		command("say 原来是要想学钓鱼绝技啊？\n");
		command("say 好小子，既然你有如此癖好，你听好了！\n");
		  j = 20;
		  if(me->query("m-card-vip")) j =  18;
		  if(me->query("y-card-vip")) j =  15;
		  if(me->query("buyvip"))     j =  10;
		  i=random(j);

		  if (i<5 
			 && me->query("kar")<31
			 && random(me->query("kar"))>24)
		  {       
			  tell_object(me,HIM"\n你按照渔人的指点乾天一阳真气注入手腕中，手中的钓竿不由自主地一沉！\n"NOR);
			  message_vision(HIG"\n$N对如何使用这个钓竿的技巧一下子豁然贯通。”\n"NOR,me); 
			  tell_object(me,HIR"恭喜您解密钓叟钓字诀绝技成功！\n"NOR);
			  me->set("quest/tls/qxbf/diao/pass",1);
			  //me->set("title",HIC"全真教 先天功传人"NOR);
			  log_file("quest/tlsdiao", sprintf("%s(%s) 失败%d次成功解开钓字诀。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/qxbf/diao/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
			 message_vision(HIC"\n$N摇了摇头，深深地叹了口气,觉得自己真实笨死了。\n"NOR,me); 
			 tell_object(me,HBBLU"\n很可惜，你本次尝试钓字诀秘密失败！\n"NOR);
			 tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
			 tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
			 log_file("quest/tlsdiao", sprintf("%s(%s) 解密钓字诀失败%d次。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/qxbf/diao/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/tls/qxbf/diao/fail",1);
			 me->set("quest/tls/qxbf/diao/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/tls/qxbf/diao/time",time());
			}
		me->delete_temp("quest/tls");
		return "我的金娃娃！\n";
	 }
		
	
	command("say 别打扰我，我正在钓金娃娃！\n");
	command("say 得不到金娃娃我很不开心，别来烦我！\n");
	return "我要金娃娃！\n";
}
string ask_yideng(string name)
{
	object me= this_player();
    


	if ( name == "段皇爷" )
		return "段皇爷早已不在尘世了！";

	if ( me->query_temp("yideng/boat"))
		return "我不是已经告诉你上山的方法了么？";

	if ( me->query_temp("yideng/yuren"))
		return "我让你去找的金娃娃呢？";

	if ( name == "一灯大师" ){
		me->set_temp("yideng/yuren", 1);

		return "要见我师傅到也不难，可是我刚丢失了两条金娃娃，不知这位"+RANK_D->query_respect(me)+"能否帮我抓回。";
	}
}

int accept_object(object me, object ob)
{
	if ( ob->query("id") != "jin wawa" ){
		command("say 你把这个给我干吗？");
		return 0;
	}
	if ( ob->query_temp("owner") != me->query("id")){
		command("say 你从那里得到这对金娃娃啊？");
		return 1;
	}
	message_vision(CYN"$N看着两尾金娃娃在掌中翻腾挣扎，哇哇而叫，宛如儿啼，不由笑道：「怪不\n"+
			"得叫作娃娃鱼，果然像小孩儿哭叫一般。」\n"+
			HIW"\n$N伸手交给$n，那$n喜上眉梢，放下铁桨，伸手接了过去。\n\n"NOR, me, this_object());
	me->delete_temp("yideng");
	me->set_temp("yideng/boat", 1);
	if (me->query_temp("quest/tls/askzhu"))
	{
		command("pat "+me->query("id"));
		command("say 既然诸万里安排你到我这里来，有什么事就问我吧！\n");
		me->set_temp("quest/tls/giveyu",1);
	}
	me->add_busy(2);
	if (me->query_temp("nqg/askyingok"))
	{
		command("hehe ");
		command("hehe "+me->query("id"));
		command("say 好小子，还真不赖，居然没有被水给淹死。\n");
		command("say 纳命来吧！");
		tell_object(me,HIR"\n\n\n这个渔夫不知道发了什么疯，抡起手中的船桨向你砸去！\n"NOR);
		me->add_busy(2+random(2));
		this_object()->kill_ob(me);
		call_out("check_yuren",1,me);
		call_out("dest", 1, ob);
		return 1;

	}else call_out("give_bonus", 1, me, this_object());
	
	call_out("dest", 1, ob);
	return 1;
}

void dest(object ob)
{
	if ( !ob) return;
	destruct(ob);
}

int give_bonus(object me, object ob)
{
	object boat, jiang;

	message_vision("\n", me);
	command("say 这上山说难是难，说易却也容易得紧。从右首转过山角，已非瀑\n"+
		"布乃是一道急流，坐在这铁舟之中，扳动铁桨，在急湍中逆流而上就可以了。");
	boat = unew(__DIR__"../obj/boat");
	jiang= unew(__DIR__"../obj/jiang");
	boat->move(me);
	jiang->move(me);
	message_vision("$N给了$n一艘"HIB"铁舟"NOR"。\n",this_object(), me);
	message_vision("$N给了$n一柄"BLU"铁桨"NOR"。\n",this_object(), me);
	
	return 1;
}

void die()
{
	object ob,me;
	object boat, jiang;
	 me=this_player();
	
	if (!query_temp("living"))
	{

	
		if (!objectp(jiang=present("tie jiang",me))&& me->query_temp("nqg/askyingok"))
		{
			message_vision("你从渔夫藏身之处搜到一柄"BLU"铁桨"NOR"。\n", me);
			jiang= unew(__DIR__"../obj/jiang");
			jiang->move(me);
		}
		if (!objectp(boat=present("tie zhou",me))&& me->query_temp("nqg/askyingok"))
		{
			message_vision("你从渔夫藏身之处搜到一艘"HIB"铁舟"NOR"。\n", me);
			boat= unew(__DIR__"../obj/boat");
			boat->move(me);

		}
	

	}
	::die();
}


int check_yuren(object me)
{
	object yuren;
	object boat, jiang;
	yuren=present("yu ren",environment(me));
    if (objectp(yuren)&& me->is_fighting(yuren))
    {
		remove_call_out("check_yuren");
		call_out("check_yuren",2,me);
		return 0;
    }
	if (!objectp(me)) return 0;
	
		boat = unew(__DIR__"../obj/boat");
		jiang= unew(__DIR__"../obj/jiang");
		boat->move(me);
		jiang->move(me);
		message_vision("你从渔夫藏身之处搜到一艘"HIB"铁舟"NOR"。\n", me);
		message_vision("你从渔夫藏身之处搜到一柄"BLU"铁桨"NOR"。\n", me);
		return 1;
	
}