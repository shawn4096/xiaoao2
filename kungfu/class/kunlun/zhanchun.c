// zhanchun.c (kunlun)
// By Spiderii 暂时关闭，不收徒
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

int ask_maiyao();
int ask_tanwang();
int ask_fangqi();
int ask_qingmingyi();
//女玩家第二个师傅

mapping *yao_name = ({ (["name":"小金丹","id": "xiao jindan"]),(["name":"藏红花","id": "zang honghua"]),(["name":"回阳五龙膏","id": "wu longgao"]),
 (["name":"延年聚精丹","id": "jujing dan"]),(["name":"菊梗","id": "ju geng"]),(["name":"黄芪","id": "huang qi"]), (["name":"雪莲丹","id": "xuelian dan"]),
	(["name":"养精丹","id": "yang jingdan"]),(["name":"六壬集气丸","id": "liuren wan"]), (["name":"三黄宝蜡丸","id": "baola wan"]),(["name":"金元散","id": "jinyuan san"]),
	(["name":"药草","id": "yao cao"]), (["name":"玉真散","id": "yuzhen san"]),(["name":"何首乌","id": "heshou wu"]),(["name":"鲨胆散","id": "shadan san"]),
	 (["name":"小还丹","id": "xiaohuan dan"]),(["name":"内息丸","id": "neixi wan"]),(["name":"延年养精丹","id": "yannian dan"]),(["name":"茯苓补气丸","id": "fuling wan"]),
(["name":"当归续精丹","id": "danggui dan"]),(["name":"川贝内息丸","id": "chuanbei wan"]),(["name":"蝉蜕金疮药","id": "chantui yao"]),(["name":"活血疗精丹","id": "huoxue dan"]),
(["name":"解毒丸","id": "jiedu wan"]),(["name":"续精丹","id": "xujing dan"]),(["name":"莲子丸","id": "lianzi wan"]),(["name":"雪藤","id": "xue teng"]),(["name":"藤黄","id": "teng huang"]),
(["name":"玉真散","id": "yuzhen san"]),(["name":"麻黄","id": "ma huang"]),(["name":"血菩提","id": "xue puti"]),(["name":"雪藤","id": "xue teng"]),(["name":"藤黄","id": "teng huang"]),

}); 

void create()
{
	set_name("詹春", ({ "zhan chun", "zhan", "chun" }));
	set("long",
		"她是何太冲最喜欢的弟子，长得倒也颇为俏丽。\n");
	set("gender", "女性");
	set("age", 24);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 25);
	set("int", 24);
	set("con", 28);
	set("dex", 26);

	set("eff_jingli", 2850);
	set("max_qi", 5850);
	set("max_jing", 2600);
	set("neili", 5200);
	set("max_neili", 5200);
	set("jiali", 90);
	set("combat_exp", 3380000);
	set("score", 4000);

	set_skill("force", 300);
	set_skill("xuantian-wuji", 300);
	set_skill("dodge", 220);
	set_skill("taxue-wuhen", 300);
	set_skill("parry", 300);
	set_skill("sword", 300);
	set_skill("hand", 300);
	set_skill("sanyin-shou", 300);

	set_skill("liangyi-jian", 300);
	set_skill("leg", 300);
	set_skill("chuanyun-tui", 300);


	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("sword", "liangyi-jian");
	map_skill("leg", "chuanyun-tui");
    map_skill("parry", "liangyi-jian");
	map_skill("hand", "sanyin-shou");
	prepare_skill("hand", "sanyin-shou");
	prepare_skill("leg", "chuanyun-tui");
	
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.jinzhen" :),
  		(: perform_action, "sword.duanyun" :),
		(: perform_action, "sword.feipu" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
	set("inquiry", ([
		"买药" : (: ask_maiyao :),
		//"请名医" : (: ask_qingmingyi :),

		"探望" : (: ask_tanwang :),
		"放弃" : (: ask_fangqi :),

	]));


    create_family("昆仑派", 4, "弟子");
	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao3")->wear();
}
void attempt_apprentice(object ob)
{
       if(ob->query("gender")=="男性"){
	   command("fear");
	   command("say "+RANK_D->query_respect(ob)+"师傅不准我收男弟子，你去找我师兄去吧。");
   	   return;
	 }
 
	 if(ob->query("appren_hezudao", 1) == 1) {
	   command("say 前辈怎敢开这等玩笑，真是折杀做晚辈的了。");
	   return;
	 }
	 if(ob->query_skill("xuantian-wuji",1) < 160){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的玄天无极功太差,不足160级别，我可不想收你。");
		return;
	}
	if(ob->query_skill("chuanyun-tui",1) < 160){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的穿云腿太差,不足160级别，我可不想收你。");
		return;
	}
	if(ob->query_skill("taxue-wuhen",1) < 160){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的踏雪无痕太差,不足160级别，我可不想收你。");
		return;
	}

	 command("say 既然"+RANK_D->query_respect(ob)+"这么努力，我就收下你吧。");
	 command("recruit " + ob->query("id"));
	 ob->set("title","昆仑派第五代弟子");
}

int ask_tanwang()
{
	object me;
	me=this_player();
	message_vision(HIY"$N小心翼翼地向詹春打听关于五姑的病情！\n"NOR,me);
	if (me->query("family/family_name")!="昆仑派") //流出九阳接口
	{
		command("say 一看你如此猥琐，鬼鬼祟祟的样子就不是好人！\n");
		return 1;
	}
	if (me->query_temp("quest/kl/buyyao/name"))
	{
		command("say 我上次让你替我买的那份"+me->query_temp("quest/kl/buyyao/name")+"你为啥还不去买？\n");
		return 1;
	}
	
	if (me->query("combat_exp")>100000)
	{
		command("say 你的经验值如此高了，超过100k还来混经验，真是拿你没办法！\n");
		return 1;
	}
	if (me->query_condition("job_busy")||me->is_busy())
	{
		command("say 你正在忙碌中！\n");
		return 1;
	}

	command("say 五姑是师傅心爱的夫人，我一向跟五姑关系很好。\n");
	command("say 最近不知道为何，五姑的身体生病，越来越严重。\n");
	command("say 师傅已经请了很多名医，但都没看好。\n");
	command("say 师傅心情不好，甚是担心，我也很忧虑。\n");

	me->set_temp("quest/kl/buyyao/start",1);
	return 1;
}

int ask_maiyao()
{
	object me;
	mapping ob;
	int i;
	
	if (arrayp(yao_name))
		ob=yao_name[random(sizeof(yao_name))];		
	//write(ob["name"]);
	me=this_player();
	message_vision(HIC"$N说道，“我也想帮五姑尽一份心力，不知詹姑娘有什么吩咐！”\n"NOR,me);
	if (!me->query_temp("quest/kl/buyyao/start"))
	{
		command("say 一看你就是没心没肺的猥琐样，一边去！\n");
		return 1;
	}
	if (me->query_condition("job_busy"))
	{
		command("say 你现在正忙碌中,稍后片刻！\n");
		return 1;
	}
	me->delete_temp("quest/kl/buyyao/start");

	command("say 既然有此心，我非常开心，先代五姑谢谢你了。\n");
	command("say 我这里正好有一份要方子，有几味药都准备好了，但还是差一份主药引子。\n");
	command("say 那就麻烦你跑一趟，去替我买了，我将非常感谢。\n");
	
	command("say 我这里还差一份"HIY"["+ob["name"]+"]。\n");
	me->set_temp("quest/kl/buyyao/name",ob["id"]);
	me->set_temp("quest/kl/buyyao/buy",1);
	return 1;
}

int ask_fangqi()
{
	object me;
	mapping ob;
	string name;
	me=this_player();

	command("say 既然你完不成就暂时下去歇息去了，我算是记住你了。真懒！\n");
	if (!me->query_temp("quest/kl/buyyao/name"))
	{
		command("say 你什么都没做，瞎放弃什么？\n");
		return 1;
	}
	me->delete_temp("quest/kl/buyyao/name");
	me->delete_temp("quest/kl/buyyao/buy");
	me->apply_condtion("job_busy",15);

	return 1;
}


int accept_object(object who, object obj)
{
	int exp,pot,gold;
	object sil;
	exp=200+random(100);
	pot=40+random(10);
	
	gold=30+random(10);
	//赋予受益额，不能让玩家赔本
	gold=gold+(int)obj->query("value")/100;
	if (obj->query("id")==who->query_temp("quest/kl/buyyao/name")	)
	{
		
		command("say 非常不错，这真是我想要的那份药耶！\n");
		command("say 真是太感谢你了！\n");
		command("say 这是我的一点小心意，代表五姑感谢你了！\n");
		
		
		sil=new("clone/money/silver");
		
		sil->set_amount(gold);
		sil->move(who);
		

		who->add("combat_exp",exp);
		who->add("potiental",pot);
	//	command("give sil to "+who->query("id"));
		message_vision(HIY"$N获得了"+exp+"点经验和"+pot+"点潜能,和"+chinese_number(gold)+"两白银的奖励！\n"NOR,who);
		if (who->query_condition("db_exp"))
		{
			who->add("combat_exp",exp);

			message_vision(HBYEL+HIW"$N因双倍经验获取又获得了"+exp+"点经验奖励！\n"NOR,who);
		}
		who->apply_condition("job_busy",3);
		who->set("job_name","昆仑买药");
	//算作门派贡献值
	//	who->add("job_time/昆仑",1);
		who->add("job_time/昆仑买药",1);
		who->delete_temp("quest/kl/buyyao/name");
		who->delete_temp("quest/kl/buyyao/buy");
		
		//who->add_temp("quest/倚天屠龙记/昆仑奇遇篇/buyyao",1);
		destruct(obj);
		return 1;
	}
	
	
}
