// lucf.c
// By jpei
// 加入可以bai lu guanying的code Modified by Numa 19990917
// Modified by Darken for taohua quest
// Modified by mxzhao 2004/05/12 for shen restrict to exp/10

#include "nadir.c"
#include <ansi.h>
inherit NPC;

int ask_ci();
int ask_yue();
string ask_book();
string ask_quest();
string ask_bagua();
string ask_zhujie();
void create()
{
	set_name("陆乘风", ({"lu chengfeng", "lu", "chengfeng"}) );
	set("title", "归云庄庄主");
	set("nickname", HIR"五湖废人"NOR);
	set("long", "他脸色枯瘦，身材甚高，坐在榻上一动不动，似乎双腿有残疾。\n");
	set("gender", "男性" );
	set("age", 42);
	set("attitude", "friendly");
	
	set("str",30);
	set("int",29);
	set("con",28);
	set("dex",5);
	set("max_qi", 9000);
	set("max_jing", 4000);
	set("eff_jingli", 4000);
	set("neili", 9400);
	set("max_neili", 9400);
	set("jiali", 120);
	set("combat_exp", 4800000);
	
	set_skill("force", 350);
	set_skill("bihai-chaosheng", 350);
	set_skill("qimen-baguazhen",100);
	set_skill("dodge", 350);
	set_skill("suibo-zhuliu", 350);
	set_skill("parry", 350);
	set_skill("strike", 350);
	set_skill("luoying-zhang", 350);
	set_skill("leg", 350);
	set_skill("xuanfeng-tui", 350);
	//set_skill("sword", 130);
	//set_skill("yuxiao-jian", 130);
	//set_skill("taoism", 120);
	set_skill("literate", 200);
	//set_skill("qimen-bagua", 140);
	
	map_skill("force", "bihai-chaosheng");
	map_skill("dodge", "suibo-zhuliu");
	map_skill("strike", "luoying-zhang");
	map_skill("leg", "xuanfeng-tui");
	map_skill("parry", "xuanfeng-tui");
	//map_skill("sword", "yuxiao-jian");
	prepare_skill("strike", "luoying-zhang");
	prepare_skill("leg", "xuanfeng-tui");
	
	set("rank_info/respect", "庄主");
	set("shen_type", 1);
	set("shen", 100);
	//	set("vendetta_mark", "桃花岛");
	
	create_family("桃花岛", 2, "弟子");
	set("class", "fighter");
	
	set("inquiry", ([
		//"rumors": "很久没有曲师兄的消息了，不知他是否出了意外？",
		//"here": "这里是归云庄，你随便转转吧，累了请到客房休息。",
		"画" : "这幅画上的词是一位大英雄、大豪杰所作。",
		"词" : (: ask_ci :),
		"字" : "这幅字是老朽写的，你看怎么样？",
		"大英雄": "你先看看词再说，难道你没有读过这首词吗？",
		"岳飞" : (: ask_yue :),
		"东邪": "那是恩师呀，虽然他打断我们的双腿，还逐我们出岛，但一日为师，终生为父呀！",
		"恩师" : "就是桃花岛主黄药师了，他聪明绝顶，文才武学，书画琴棋，算数韬略，医卜星相，奇门五行，无一不精。",
		"黄蓉": "嗯，那是小师妹，是家师的掌上明珠。",
		"桃花岛": "好怀念原来大家在那里的时光呀，曲师兄临离岛时还画了海图呢。",
		"陆冠英": "那是小犬，以前送在仙都派门下习艺，现在师父恩准在我门下学艺了。",
		"归云庄": "这里是花了我无数心血才建起来的，与别的庄院相比如何？",
		"易经": (: ask_book :),
		"骷髅头": (: ask_quest :),
		"八卦图": (: ask_bagua :),
		"易经注解": (: ask_zhujie :),
        ]) );
	
	set("chat_chance", 3);
	set("chat_msg",({
		"陆乘风对着那幅画长叹一声，默然不语，似有满腹心事。\n",
	}));
	set("book_count1", 2);
	set("book_count2", 2);
	setup();
	
	carry_object("/d/city/npc/obj/xiao.c")->wield();
	carry_object(__THD__"obj/grn-cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	object letter;
	string letter_desc;
	
	if (!ob->query("family") || ob->query("family/family_name")!= "桃花岛"){
		command("say "+RANK_D->query_respect(ob)+"武功根底太差，还是先跟小儿冠英学学吧！");
		return;
	}
	if ((int)ob->query_skill("bihai-chaosheng", 1) < 200){
		command("say 我桃花岛一派武功脱胎于道教，很重视内功心法,不足200不用找我。");
		command("say " + RANK_D->query_respect(ob) + "是否还应该在碧海潮生功上多下点功夫？");
		return;
	}
	if ((int)ob->query("family/generation")==2){
		command("say "+RANK_D->query_respect(ob)+"已经是桃花岛第二代弟子，我怎敢再收你为徒？");
		return;
	}
	if (!ob->query("thd/receive"))
	{
		command("say 没有家师的命令，陆某不敢擅自将恩师的武功转授他人！");
		if (ABS(ob->query("shen")) < 200000
			&&  ob->query("int") >= 28){
			command("say 不过我看" + RANK_D->query_respect(ob) + "的资质还不错，这样吧，我写一封推荐信，你拿去找家师吧。");
			letter = new(__GUI__"obj/tuijian_xin");
			letter->set("owner", ob->query("id"));
			letter_desc = "这是陆乘风写给黄药师的一封信，上面写着：\n恩师在上：今有" + ob->query("name") + "一名，欲拜入本派，弟子不敢擅专，又念其资质不错，特此推荐与恩师定夺。  乘风叩首\n";
			letter->set("long", letter_desc);
			letter->move(ob);
			message_vision("陆乘风掏出一封推荐信，写上$N的名字，交给了$N。\n", ob);
			command("say 家师是桃花岛主黄药师，你需要从临安附近坐船上岛。至于桃花岛的位置嘛，就在...在...让我想想看...");
			command("consider");
			command("doubt chengfeng");
			command("sigh");
			command("say 居然想不起来了！你去问我师兄曲灵风吧，他在临安东南的牛家村开了一间小店。");
		}
		return;
	}
	ob->delete("thd/receive");
	if (ob->query("gender") != "男性" && ob->query("gender") != "女性") {
		command("say 你不男不女的算什么东西？快滚！");
		return;
	}
	if (ob->query("shen") < -ob->query("combat_exp")/10 
		&& (int)ob->query("shen") < -200000) 
	{
		command("say 家师生平最讨厌两种人，你们这种无恶不作的邪魔外道就是其一，再去求家师吧！");
		return;
	}
	if (ob->query("shen") > ob->query("combat_exp")/10 
		&& (int)ob->query("shen") > 200000) 
	{
		command("say 家师生平最讨厌两种人，你们这种自命大侠的沽名钓誉之徒就是其一，再去求家师吧！");
		return;
	}
	if (ob->query("class") == "bonze") {
		command("say 家师比较讨厌少林和尚，我可不敢擅自收你。再去求家师吧！");
		return;
	}
	command("say 既然家师有令，我就收你为徒吧。");
	command("recruit " + ob->query("id"));
	ob->set("class", "fighter");
	ob->set("title","桃花岛第三代弟子");
}


void init()
{
	add_action("do_answer","answer");
	add_action("do_answer","huida");
	add_action("do_kill","kill");
}

int do_kill(string arg)
{
	object ob;
	object me = this_player();
	
	if (!arg) return 0;
	ob = present(arg, environment(me));
	if (ob == this_object() || ob == me) return 0;
	if (!ob || !ob->is_character()) return 0;
	if (ob->query("family/family_name") == "桃花岛") {
		if (me->query("family/family_name") == "桃花岛") {
			message_vision("陆乘风向$N喝道：小奴才，要造反吗？连自己的同门都杀？！\n", me);
		}
		else {
			message_vision("陆乘风向$N喝道：大胆狂徒，竟敢来归云庄撒野？！\n", me);
			message_vision("陆乘风对$N说道：你先让开，让我来收拾这个" + RANK_D->query_rude(me) + "！\n", ob);
			kill_ob(me);
		}
		me->set("vendetta/桃花岛", 1);
		return 1;
	}
	return 0;
}

int ask_ci()
{
	object ob = this_player();
	
	command("say 写这首词的大英雄、大豪杰就是岳武穆。\n");
	if(!ob->query_temp("guiyun_lutemp"))
		ob->set_temp("guiyun_lutemp", 1);
	return 1;
}

int ask_yue()
{
	object ob = this_player();
	
	if(ob->query_temp("guiyun_lutemp") >= 1) {
		command("say 可惜我的字意有一句与岳武穆原意不太相符，不知" + RANK_D->query_respect(ob) + "能否看出来？\n");
		ob->set_temp("guiyun_lutemp", 2);
	}
	else {
		command("say 岳武穆是我非常敬重的一位大英雄。\n");
	}
	return 1;
}

int do_answer(string arg)
{
	object ob = this_player();
	
	if (arg=="剑意")
	{
		command("laugh "+ob->query("id"));
		command("say 真心不错，居然能看出剑意来，既然你与这幅画有缘分，那就好好看吧。\n");
		command("smile "+ob->query("id"));
		ob->set_temp("gyz/askjianyi",1);
		ob->delete_temp("guiyun_lutemp");
		return 1;
	}

	if (ob->query_temp("guiyun_lutemp") == 2) {
		tell_room(environment(ob), ob->name() + "向着陆乘风侃侃而谈。\n", ({ob}));
		if (arg == "知音少,弦断有谁听?" || arg == "知音少，弦断有谁听？"
			|| arg == "知音少,弦断有谁听" || arg == "知音少，弦断有谁听") {
			if (!present("tuifa tujie", ob) && query_temp("tuifa_give") < 5) {
				say("陆乘风长嘘一声：我这番心情，今日才被你看破，可谓平生一知已，这本腿法就送给你吧。\n");
				new(__GUI__"obj/tuifa.c")->move(ob);
				ob->delete_temp("guiyun_lutemp");
				add_temp("tuifa_give",1);
			}
			else {
				say("陆乘风长嘘一声：我这番心情，今日才被你看破，可谓平生一知已，只可惜老夫我没有什么可以相赠的。\n");
			}
		}
		else {
			command("? " + ob->query("id"));
			message_vision("陆乘风疑惑地看着$N：" + RANK_D->query_respect(ob) + "似乎应该多学些书法绘画吧？\n", ob);
		}
		return 1;
	}
	return 0;
}

string ask_book()
{
	mapping fam;
	object ob;
	object me=this_player();
	if (!(fam = this_player()->query("family"))
		|| fam["family_name"] != "桃花岛")
        return RANK_D->query_respect(this_player()) +
		"不是本派弟子，要此书来做何用？";
	//if (me->query_skill("qimen-bagua",1)<30)
	//{
	   if (query("book_count1") < 1)
		return "你来晚了，「易经」已经不在此处了。";
	    add("book_count1",-1);
		ob = unew("/d/baituo/obj/book5");
		/*if(!clonep(ob))
			return "你来晚了，这本讲解伏羲六十四卦的奇书不在此处。";
		if(clonep(ob) && ob->violate_unique()){
			destruct(ob);
			return "你来晚了，这本讲解伏羲六十四卦的奇书不在此处。";
		}*/
		ob->move(this_player());
		return "好吧，这本「易经」你拿回去好好钻研。";

	//}
	//return "";

}
string ask_bagua()
{

	mapping fam;
	object ob;
	object me=this_player();
	if (!(fam = this_player()->query("family"))
		|| fam["family_name"] != "桃花岛")
        return RANK_D->query_respect(this_player()) +
		"不是本派弟子，要此书来做何用？";
	if (me->query_skill("qimen-bagua",1)>30)
	{
		command("pat "+me->query("id"));
		command("say 不错，你已经读完了易经，奇门八卦有了一定的根基，\n我这里还有一本关于九功八卦的书,你拿去好好读读。\n");
		if (query("book_count2") < 1)
		return "你来晚了，「易经」已经不在此处了。";
	    add("book_count2",-1);
		ob = unew("/d/thd/obj/tupu");
		/*if(!clonep(ob))
			return "你来晚了，这本讲解九宫八卦图谱的奇书不在此处。";
		if(clonep(ob) && ob->violate_unique())
		{
			destruct(ob);
			return "你来晚了，这本讲解九宫八卦图谱的奇书不在此处。";
		}*/
	 	ob->move(this_player());
		return "好吧，这本「九宫八卦图谱」你拿回去好好钻研。";

	}
	return "你的奇门八卦等级太低，给你这本九宫八卦图也没有用。\n";


}
string ask_zhujie()
{
	mapping fam;
	object ob;
	object me=this_player();

	if (me->query_skill("qimen-bagua",1)>50){
		command("congra "+me->query("id"));
		command("say 不错，你已经读完了九功八卦图谱，奇门八卦有了一定的提升，\n我这里还有一本关于易经注解的书,你拿去好好读读，这是你祖师爷的亲自标注，你要好好学习\n");
		ob = unew("/d/thd/guiyun/obj/yijing2");
		if(!clonep(ob))
			return "你来晚了，这本讲解易经注释的奇书不在此处。";
		if(clonep(ob) && ob->violate_unique()){
			destruct(ob);
		return "你来晚了，这本讲解易经注释的奇书不在此处。";
		}
	 	ob->move(this_player());
		return "好吧，这本「易经注释」你拿回去好好钻研。";
	}
	return "你的奇门八卦等级太低，给你这本书也没有用。\n";


}
string ask_quest()
{
	mapping fam;
	object obj;
	
	object me = this_player();
	if (!(fam = this_player()->query("family"))
		|| fam["family_name"] != "桃花岛")
		return RANK_D->query_respect(this_player()) +
		"不是本派弟子，还是快离开的好。";
	if (me->query_temp("thd/onquest")!=5)
		return RANK_D->query_respect(me) + "赶紧离开此地吧，别多问了。";
	command("say 冠英已经告诉你了？");
	command("sigh");
	command("say 这是我梅师姐送来的，你还是快些离开，否则......\n\n");
	message_vision(HIY"突然人影晃动，一人叫到“梅师姐早已在此！”\n", me);
	message_vision(HIY"便向陆乘风攻去。你“啊”的惊呼一声，不料梅超风\n", me);
	message_vision(HIY"一听到，便转身向你攻来！\n\n"NOR, me);
	message_vision(HIR"梅超风叫到：“杀了我贼汉子的小贼，今天要取你狗命！\n"NOR, me);
	obj = new("/d/lanzhou/npc/mei");
	obj->set_temp("target",me->query("id"));
	obj->move(environment(me));
	me->start_busy(random(2)+1);
	me->set_temp("thd/onquest",6);
}

