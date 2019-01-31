// h7g.c 洪七公
// Looklove@SJ 2000/8/25
// Looklove Modify at 2001/1/19
// Looklove Modify at 2001/4/7
// Looklove Modify at 2001/5/3
// River@SJ For 玉笛谁家听落梅 job 3.29.2002
// Update By lsxk@hsbbs 增加通宝物品提高解kanglong几率 2007/7/18
//Update By action@SJ 2008/12/5

inherit NPC;
#include <job_mul.h>
#include <ansi.h>
#include <get_place.h>
#include "h7g.h";

int ask_up();
int pass_chuanwei(object me, object ob);
int ask_kanglong();
string ask_job();
string ask_finish();
string ask_fangqi();

string *no_kill_list = ({
	"mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

int filldata(object obj1)
{
	if(wiz_level(obj1))
		return 0;
	if(!environment(obj1))
		return 0;
	else return 1;
}

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	 || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")
	 || member_array(ob->query("id"), no_kill_list) != -1
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || !objectp(room=environment(ob))
	 || room->query("no_fight")
	 || room->query("quest")
	 || room->query("outdoors") == "昆仑翠谷"
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/group/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/gb/") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
	 || strsrch(room_name, "/d/huashan/hamasuperquest") == 0
	 || strsrch(room_name, "/d/baituo/") == 0)
	 return 0;
	return 1;
}

void create()
{
	object ob;
	set_name("洪七公", ({"hong qigong", "hong", "qigong"}));
	set("nickname", HIY"九指神丐"NOR);
	set("gb/bags",10);
	set("gender", "男性");
	set("age", 65);
	set("per",24);
	set("long", "他就是丐帮第十七任帮主，号称“北丐”的洪七公老爷子。\n");
	set("attitude", "friendly");
	set("no_bark",1);
	set("dgb/wugou",6);

	set("str", 40);
	set("con", 35);
	set("dex", 30);
	set("int", 35);

	set("max_qi", 51000);
	set("max_jing", 9600);
	set("neili", 38500);
	set("max_neili", 38500);
	set("jiali", 250);
	set("eff_jingli", 96000);
	set("combat_exp", 15400000);

	set_skill("force", 530);
	set_skill("huntian-qigong", 550);    // 混天气功
	set_skill("strike", 530);            // 基本掌法
	set_skill("xianglong-zhang", 550);   // 降龙十八掌
	set_skill("literate", 200);           // 读写
	set_skill("dodge", 500);             // 基本躲闪
	set_skill("xiaoyaoyou", 500);        // 逍遥游
	set_skill("parry", 530);             // 基本招架
	set_skill("stick", 530);             // 基本棍杖
	set_skill("dagou-bang", 530);        // 打狗棒法
	set_skill("begging", 200);           // 叫化绝活
	set_skill("checking", 200);          // 道听途说
	set_skill("bangjue", 200);            // 棒决
	set_skill("dagou-zhen", 530);	     // 打狗阵
	set_skill("lianhua-zhang", 500);      // 莲花掌
   // set_skill("fengmo-zhang", 500); 
	//set_skill("staff", 500); 
	//set_skill("whip", 500); 
	//set_skill("huifeng-bian", 500); 
	//set_skill("blade", 500); 
	//set_skill("liuhe-dao", 500); 
	//set_skill("", 500); 
	set_skill("stealing", 200);           // hehe

	map_skill("force", "huntian-qigong");
	map_skill("strike", "xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "dagou-bang");
	map_skill("stick", "dagou-bang");
	prepare_skill("strike", "xianglong-zhang");

	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: perform_action, "strike.xiao" :),
        	(: perform_action, "strike.kanglong" :),
        	(: perform_action, "stick.chan" :),
		(: perform_action, "stick.zhuan" :),
        	(: exert_function, "huntian" :),
        	(: exert_function, "shentong" :),
	}));
	set("chat_chance", 1);
	set("chat_msg", ({
		CYN"洪七公叹了口气道：“唉……何时能再吃到蓉儿做的「叫化鸡」啊……”\n"NOR,
		CYN"洪七公说道：“老毒物的功夫日见精进，看来我得想点办法对付他。”\n"NOR,
		CYN"洪七公喃喃道：“我们丐帮的「降龙十八掌」是天下最霸道的掌法。”\n"NOR,
	}));

	set("inquiry", ([
		/*"老毒物" : "老毒物就是我的死对头，江湖上人称西毒的欧阳峰。\n",
		"欧阳峰" : "他是我的死对头，江湖上人称西毒。\n",
        	"西毒" : "这个...这个...\n",
        	"郭靖" : "那是我的好徒儿，就是人笨了点。\n",
        	"黄蓉" : "那小丫头可是个机灵鬼，菜做的可真不赖。\n",
        	"黄药师" : "他啊，够博学多才，不过我还是更喜欢他那个小丫头。\n",
        	"东邪" : "他啊，够博学多才，不过我还是更喜欢他那个小丫头。\n",
        	"南帝" : "大理皇族，不敢高攀。\n",
        	"王重阳" : "那可是个武学奇才，老叫化可不想和他打架。\n",
        	"中神通" : "江湖上现在很多人自命不凡，都以为自己是王重阳，哈哈！\n",
        	"丐帮" : "连我丐帮都不知道，我看你有点秀斗了！\n",
        	"打狗棒" : "这个...这个...你想如何？\n",
        	"降龙掌" : "没事别乱打听，小心我一掌拍死你。\n",
        	"莲花掌" : "没事别乱打听，小心我一掌拍死你。\n",*/
        	//"rumors" : "最近没听说什么消息。\n",
		    "亢龙有悔" : (: ask_kanglong :),
        	"叫化鸡" : (: ask_ji :),
        	"棒掌双绝" : (: ask_wugou :),
        	"传位":    (: ask_up :),
        	"玉笛谁家听落梅": (: ask_job :),
        	"job" : (: ask_job :),
        	"finish": (: ask_finish :),
        	"完成" : (: ask_finish :),
        	"放弃" : (: ask_fangqi :),
        	"fangqi" : (: ask_fangqi :),        	
	]));

	create_family("丐帮", 17, "帮主");
	set_temp("apply/damage", 70);
	set_temp("apply/dodge", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/armor", 120);
	setup();

	if (clonep()) {		
		object *ob_list = filter_array(users(), (: filldata :));
		for (int i=0;i<sizeof(ob_list);i++){
			if (ob_list[i]->query_temp("gb_chuanwei") ){
				set("long", "他就是丐帮的现任帮主，号称“北丐”的洪七公老爷子。\n");
				set("title","丐帮前帮主");
				break;
			}
		}
		ob = unew(BINGQI_D("yuzhu_bang"));
		if (!ob) ob = unew(BINGQI_D("zhubang"));
		ob->move(this_object());
		ob->wield();
		carry_object(ARMOR_D("bainayi"))->wear();
		carry_object(ARMOR_D("shoes"))->wear();
		carry_object(__DIR__"obj/gb_budai10")->wear();
	}
}

void reset()
{	
	if (clonep() ) {
		int i = 0;
		object *ob_list = filter_array(users(), (: filldata :));
		object ob = unew(BINGQI_D("yuzhu_bang"));
		for (i=0;i<sizeof(ob_list);i++){
			if (ob_list[i]->query_temp("gb_chuanwei") ){
				set("long", "他就是丐帮的帮主，号称“北丐”的洪七公老爷子。\n");
				set("title",CYN"丐帮前帮主"NOR);
				break;
			}
		}
		if(i==sizeof(ob_list))
		{
			set("long", "他就是丐帮第十七任帮主，号称“北丐”的洪七公老爷子。\n");
			delete("title");
		}
		if(ob){
			ob->move(this_object());
			command("unwield all");
			command("wield yuzhu bang");
		}		
	}
}
//收徒 

void attempt_apprentice(object ob)
{
	if ( ob->query("job_time/丐帮",1) < 400 && ob->query("job_time/抓蛇") < 400){
		command("say  做我的弟子要为丐帮出生入死，" + RANK_D->query_respect(ob) + "在帮中的积功似乎还少了一些。\n");
		return;
	}
	if ( !ob->query("gb/bags") ) {
		command("say " + RANK_D->query_respect(ob) + "你身上一袋也没有，不是我们丐帮弟子吧？\n");
		return;
	}
	if ( ob->query("gb/bags")<9) {
		command("say " + RANK_D->query_respect(ob) + "在帮中职位太低，先积累功劳升到九袋吧。\n");
		return;
    	}
	if ( ob->query_skill("huntian-qigong",1)< 400) {
		command("say " + RANK_D->query_respect(ob) + "我的弟子需要扎实的基础，你混天气功修炼到400级后再来找我。\n");
		return;
    	}
	if ( ob->query("shen")< 2000000) {
		command("say " + RANK_D->query_respect(ob) + "我丐帮号称天下第一帮，干的是除暴安良，保家卫国的事情，你小于2m正气，还是干点好事去。\n");
		return;
    	}
	if ( (ob->query("job_time/丐帮") + ob->query("job_time/抓蛇")) < 1000){
		command("say " + RANK_D->query_respect(ob) + "在帮中的抓蛇和吴长劳积功（合计1k）似乎还少了一些，我若收你恐怕难以折服众弟子。\n");
		return ;
	}
	if( (ob->query("job_time/报效国家")+ ob->query("job_time/刺杀")+ ob->query("job_time/颂摩崖"))< 400) {
		command("say 居然不到400次报效国家的任务，我丐帮乃堂堂名门正派，"+RANK_D->query_respect(ob)+"应该为国为民多做点贡献才好(400次)。");
		return ;
	}		
	command("chat 哈哈哈，老叫化入土之前还能找到"+ob->name()+"这样一个可造之才,丐帮后继有人了。\n");
	command("recruit " + ob->query("id"));
	ob->set("class", "beggar");
	ob->set("gb/fenduo","总舵");

	if (!ob->query("gb/baih7g")){
		ob->set("gb/baih7g",ob->query("combat_exp"));
		ob->set("title","丐帮洪七公亲传弟子");
	}
	return;
}
//传位部分

int ask_up()
{
	object obj1, me=this_player(),ob=this_object();
	int max, i, skill, bag = me->query("gb/bags");
	mixed *ob_list;

	skill = me->query_skill("xianglong-zhang",1);
	
	if( me->query_temp("gb_chuanwei") ){
		command("say " + RANK_D->query_respect(me) + "已经是丐帮帮主，何苦又来找我开玩笑。\n");
		return 1;
	}	
	if( !me->query("gb/bags")){
		command("say " + RANK_D->query_respect(me) + "与我丐帮素无来往，此话不知从何说起。\n");
		return 1;
	}
	if( bag < 9 ){
		command("say 你在帮中地位太低，传位给你恐怕无法说服众弟子。\n");
		return 1;
	}
	if ( (me->query("job_time/丐帮") + me->query("job_time/抓蛇")) < 2000){
		command("say " + RANK_D->query_respect(me) + "在帮中的积功似乎还少了一些，恐怕难以折服众弟子。\n");
		return 1;
	}
	if( me->query("shen") < 2000000){
		command("say " + RANK_D->query_respect(me) + "的侠义正气不足2m，恐怕无力领导丐帮数万弟子。\n");
		return 1;
	}
	
	if(mapp(me->query("job_time")))
		me->set("job_time/报效国家",me->query("job_time/草料场")+me->query("job_time/刺杀")+me->query("job_time/颂摩崖"));
	
	if( me->query("job_time/报效国家") < 500) {
		command("say 我丐帮乃堂堂名门正派，"+RANK_D->query_respect(me)
		+"应该为国为民多做点贡献才好。");
		return 1;
	}		
	if( me->query_skill("dagou-bang",1) < 450 || me->query_skill("xianglong-zhang",1) < 450 ){
		command("say 打狗棒法和降龙十八掌乃我丐帮祖传绝技，" + RANK_D->query_respect(me) + "在这方面的修为是否稍差了一点。\n");
		return 1;
	}
	if( !present("yuzhu bang",ob) )	{
		command("say 我的玉竹棒跑哪里去了？糟了，这下可没办法传位了。");
		return 1;
	}

	ob_list = users();
	ob_list = filter_array(ob_list, (: filldata :));
	max=sizeof(ob_list);
	for (i=0;i<max;i++){
		obj1 = ob_list[i];
		if (obj1->query_temp("gb_chuanwei") ){
			command( "say 我已经把帮主之位传给" + obj1->query("name") +"了。\n" ) ;
			return 1;
		}
	}
	command("look "+me->query("id"));
	command( "say 欲受我衣钵，先考考你的武功。" );

	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;

	me->set_temp("title",HIR "丐帮第十八代帮主" NOR);

	command("chat 老叫化今日将丐帮帮主之位传给"+me->query("name")+"，哈哈，丐帮后继有人了。");
	message_vision("洪七公交给$N一根玉竹棒。\n",me);
	me->set_temp("gb_chuanwei",1);
	me->add_temp("apply/strength", random(skill/10));//add up bl ciwei
	present("yuzhu bang", ob)->move(me);
	
	ob->set("long", "他就是丐帮的前帮主，号称“北丐”的洪七公老爷子。\n");
	ob->set("title",CYN"丐帮前帮主"NOR);
	return 1;
}

int pass_chuanwei(object me, object ob)
{
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);

	if (!present(me,environment(ob)) || me->query("qi") <= 0
	|| me->query("jing") <= 0 || me->query("jingli") <= 0){
		command("say 武功如此之差，如何传我衣钵？！");
		ob->reincarnate();
		return 0;
	}
	return 1;
}

string ask_job()
{
	object me, ob, *living, target;
	string str, food, food_id_list;
	string *food_name = ({"羊羔坐臀","小猪耳朵","小牛腰子","獐腿肉","兔肉"});
	string *food_id = ({"yanggao zuotun", "xiaozhu erduo", "xiaoniu yaozi", "zhangtui rou", "tu rou"});
	string *food_type;
	object objwhere, obj;
	mapping food_type_list;
	mapping skills;
	string *sk;
	int i, j, x, y, z, p;

	me = this_player();

	if (me->query("menggu"))
		return "哼，你已身属蒙古，还想做什么？";

	if (me->query_temp("potjob/job") && !wizardp(me))
		return "嗯？我不是告诉你了吗，快去取原料啊，不想做就算了！";

//	if (me->query("job_name") == "" && !wizardp(me))
//		return "我现在不饿，你还是先去休息一会吧。";

	if (me->query("combat_exp") < 100000 )
		return "这位" + RANK_D->query_respect(me) + "武功未成，让你去江湖闯荡，老叫化子我可不太放心。";

	skills = me->query_skills();
	if (mapp(skills)){
		sk = keys(skills);
		for (i=0; i < sizeof(sk); i++)
			if (skills[sk[i]] > (me->query("max_pot") - 90) && sk[i] != "beauty" && SKILL_D(sk[i])->type2() != "worker")
//			if (skills[sk[i]] > (me->query("max_pot") - 90) && SKILL_D(sk[i])->type() != "knowledge" && SKILL_D(sk[i])->type2() != "worker")
				return "你的"+to_chinese(sk[i])+"等级够高了，无法再做这个任务了。";
	}

	if ( me->query("potential") >= me->query("max_pot") && !wizardp(me))
		return "这位" + RANK_D->query_respect(me) + "的潜能已经这么多了，还是先去用完再来吧！";

	if ( me->query_condition("job_busy") || me->query_condition("pot_job"))
		return "我现在不饿，你还是先去休息一会吧。";

	me->delete_temp("potjob");
	command("say 这「玉笛谁家听落梅」是黄蓉这个小丫头片子做给老叫花子吃的一道菜，\n"+
		"还骗得老叫花子教了郭靖那个傻小子一套降龙十八掌。这道菜说起来也简单，就是由四条\n"+
		"小肉条拼成，一条是羊羔坐臀，一条是小猪耳朵，一条是小牛腰子，还有一条是獐腿肉加\n"+
		"兔肉揉在一起。不说了，不说了，口水都出来了。");

	command("taste");

	for(z=0; z < 5; z ++){
		me->set_temp("potjob/food_type/"+ food_name[z], food_id[z]);
	}

	food_type_list = me->query_temp("potjob/food_type");

	y = random(4) + 2;
	for (x = 0; x < y; x ++){
		living = livings();
		for (i=0;i < sizeof(living);i++){
			j = random(sizeof(living));
			if (!j || j == sizeof(living) -1) continue;
			if(check(living[j]) ){
				target = living[j];
				objwhere = environment(target);
				str = objwhere->query("short");
				if (!sizeof(objwhere->query("exits"))
				|| str == "武僧堂"
				|| str == HIR"心禅堂"NOR
				|| str == "僧舍"
				|| str == "休息室"
				|| str == "龙池"
				|| str == "凤池"
				|| str == "女休息室"
				|| str == "男休息室"
				|| str == "金刚伏魔圈" ) continue;
				if( get_place(base_name(environment(target)))!="" ) break;
			}
		}

		if( !target )
			return "我现在暂时还不饿，你还是先去休息一会吧。";

		p = random(sizeof(food_name));

		food = food_name[p];
		food_id_list = food_id[p];

		food_type = me->query_temp("potjob/type");

		if ( ! sizeof(food_type))
			me->set_temp("potjob/type", ({ food }));
		else {
			for(z=0; z < 5; z ++){
				if (member_array(food, food_type) != -1) {
					food = food_name[z];
					food_id_list = food_id[z];
				}
			}
			food_type = sort_array(food_type + ({ food }), 0);
			me->set_temp("potjob/type", food_type );
		}
		ob = new(__DIR__"pot_target");
		ob->set_temp("target", me);
		ob->set_temp("food_name", food);
		ob->set_temp("food_id", food_id_list);
		ob->move(objwhere);
		for (i=0; i<5; i++)
			ob->random_move();
		obj = new(__DIR__"obj/pot_food");
		obj->set_name(food, ({ food_id_list }));
		obj->set("long", "这是一条"+obj->query("name")+"，看起来味道不错。\n");
		obj->set_temp("food_id", food_id_list);
		obj->move(ob);
		if (me->query_temp("potjob/food_type/"+food))
			me->delete_temp("potjob/food_type/"+food);
		if (strsrch(file_name(environment(ob)), "/d/zhiye/") >= 0
		 || strsrch(file_name(environment(ob)), "/d/group/") >= 0){
		 	if ( environment(ob)->query("outdoors"))
				me->set_temp("potjob/pot_job_place/"+ ob->query("name"), environment(ob)->query("outdoors")+environment(ob)->query("short"));
		 	else if ( environment(ob)->query("indoors"))
				me->set_temp("potjob/pot_job_place/"+ ob->query("name"), environment(ob)->query("indoors")+environment(ob)->query("short"));
			else me->set_temp("potjob/pot_job_place/"+ ob->query("name"), environment(ob)->query("short"));
		}
		else me->set_temp("potjob/pot_job_place/"+ ob->query("name"), get_place(base_name(environment(ob)))+environment(ob)->query("short") );
		me->set_temp("potjob/for_menu/"+ ob->name(), food);
		command("whisper "+ me->query("id")+" 听说"+ me->query_temp("potjob/pot_job_place/"+ob->query("name")) +GRN"的"+ob->name()+"手中有"+food+"，你帮我去找来吧！");
	}

	me->set_temp("potjob/do_time", y);
	me->set_temp("potjob/time", uptime());
	me->set_temp("potjob/job",1);
	me->apply_condition("pot_job", 6);
	me->apply_condition("job_busy", 6);

	if ( !present("hong's menu", me)){
		new(__DIR__"obj/pot_paper")->move(me);
		message_vision("$N给了$n一本关于如何制作「玉笛谁家听落梅」的菜谱。\n", this_object(), me);
	}

	p = sizeof(keys(food_type_list));

	if ( p > 0 ){
		for(z=0; z < p; z ++){
			food = keys(food_type_list)[z];
			food_id_list = values(food_type_list)[z];
			obj = new(__DIR__"obj/pot_food");
			obj->set_name(food, ({ food_id_list }));
			obj->set("long", "这是一条"+obj->query("name")+"，看起来味道不错。\n");
			obj->set_temp("food_id", food_id_list);
			obj->set_temp("job_id", me);
			obj->move(me);
			me->set_temp("potjob/be_get/"+food, 1);
		}
		return "我这里已经有些原料，先给你，其余的你去找吧！";
	}
	else
		return "唉！我这里什么原料都没有，你速速帮我找来吧。";
}

string ask_finish()
{
	object me = this_player();
	object ob;
	int pot, i, times;

	if ( !me->query_temp("potjob/job"))
		return "我有叫你去做什么吗？你完成什么啊？";

	if ( !me->query_temp("potjob/finish"))
		return "你真的完成了？？";

	if ( ! ob =(present("yudi luomei", me)))
		return "你完成了，那么东西呢？";

	destruct(ob);
	message_vision(HIY"$N接过$n做的「玉笛谁家听落梅」，口中啧啧声不断，大笑道：今日可大饱口福了。\n"NOR, this_object(), me);

	command("pat "+ me->query("id"));
	i = me->query_temp("potjob/do_time");
	pot = 50 + i * 100 + random(50);
// 以后去除
	if( me->query("max_neili") < 3500)
		pot += pot/2;
		
       	//奖励控制开始
        if (me->query("registered")==3){
            		pot = pot * H7G_JOB_MUL * VIP_MUL /10000;
		}
		else
		{
           		pot = pot * H7G_JOB_MUL /100;
		}
		//奖励控制结束 


	tell_object(me, HIW"洪七公指点了你一些武学上的迷津，你获得了"+chinese_number(pot)+"点潜能。\n"NOR);
	times = uptime() - me->query_temp("potjob/time");
	me->delete_temp("potjob");
	me->add("potential", pot);
	me->add("job_time/洪七公",1);
	GIFT_D->check_count(me,this_object(),"洪七公");
	log_file("job/zuocai", sprintf("%8s%-10s 完成做菜，得到%3d点潜能，时间：%d",
		me->query("name"), "("+me->query("id")+")", pot, times), me);
	return "哈哈，下次再让你小子给老叫化子做菜。";
}

string ask_fangqi()
{
	object me = this_player();
	object meat1, meat2, meat3, meat4, meat5, meat6;
	meat1 = present("yanggao zuotun", me);
	meat2 = present("xiaozhu erduo", me);
	meat3 = present("xiaoniu yaozi", me);
	meat4 = present("zhangtui rou", me);
	meat5 = present("tu rou", me);
	meat6 = present("yudi luomei", me);

	if ( ! me->query_temp("potjob/job"))
		return "我有叫你去做什么吗？你放弃什么啊？";

	if ( meat1 ) destruct(meat1);
	if ( meat2 ) destruct(meat2);
	if ( meat3 ) destruct(meat3);
	if ( meat4 ) destruct(meat4);
	if ( meat5 ) destruct(meat5);
	if ( meat6 ) destruct(meat6);

	command("nod "+ me->query("id"));
	me->delete_temp("potjob");
	return "既然做不了，也就不勉强你了。";
}

void dest(object obj)
{
	if(!obj) return;
	destruct(obj);
}
//解密玉竹棒
int accept_object(object me, object obj)
{
	object ob_yzz, ob = this_object();
    object ob_yywzk;

	if (obj->query("food_supply") <= 0) return 0;
	if ((string)obj->query("name") != "叫化鸡" || me->query_temp("marks/get-ji")){
		command("say 老叫化对" + (string)obj->query("name") + "没什么兴趣……");
		return 0;
	}
	if (query("food") >= (max_food_capacity() - obj->query("food_supply"))){
		command("say 老叫化现在饱得很。");
		return 0;
	}
	command("say 啊……这正是我想吃的叫化鸡呀！");
	command("eat ji");
	command("say 想不到你小小年纪，心思却很细，就跟当年的蓉儿一样！");
	call_out("dest", 1, obj);

	if (!me->query("gb/bags")){
		command("say 你还呆在这里干什么？");
		return 1;
	}
	if( ob_yzz = present("yuzhu bang", ob) ){
		ob_yzz->move(me);
		command("say 这根竹棒跟随我多年了，就送给你作见面礼吧。");
		return 1;
	}
	else{
		if( (time()-me->query("gb/jitime")) >= 100 ) {
			me->add("combat_exp",random(200));
			me->add("potential",random(100));
			if(me->query("potential")>me->query("max_pot"))
				me->set("potential",me->query("max_pot"));
			me->set("gb/jitime",time());
		}
		if ( me->query("combat_exp") <= 2000000 ){
			command("say 你现在功夫还太弱，等以后练好了再来找我吧。");
			return 1;
		}

       if ( ! ob_yywzk =(present("yuanyang wuzhenkuai", me))){
           if ( !random(10)
		&& me->query_skill("xianglong-zhang", 1) >= 200
		&& !me->query("xlz/hang")
		&& !me->query_temp("xlz/hang"))
			call_out("kanglong", 10, me, ob);
       }
       else{
           if ( !random(3)
           && me->query_skill("xianglong-zhang", 1) >= 200
           && !me->query("xlz/hang")
           && !me->query_temp("xlz/hang"))
                   call_out("kanglong", 10, me, ob);
           message_vision(HIY"$N突然觉得身上少了一样东西，回头一看，发现$n竟然正在啃着$N的"HIW"鸳"HIM"鸯"HIY"五"HIG"珍"HIC"脍"HIY"。。。。\n"NOR, me, this_object());
           command("xixi "+me->query("id"));
           destruct(ob_yywzk);
       }
		return 1;
	}
	return 1;
}

int ask_kanglong()
{
   
    object me,ob;
	int i,j;
	
	me=this_player();
	ob=this_object();
	
	if (!me->query("xlz/hang"))
	{
	   command("say 让你去鸣沙山试炼，是为了让你体味力道的控制和把握，你居然没通过？\n");
	   return 1;
	}
    if (me->query("kanglong/pass"))
	{
	   command("say 你已经彻底了解了亢龙有悔的奥秘，再胡闹打你屁股。\n");
	   return 1;
	}
    if (time()-(int)me->query("xlz/kanglong/time")<86400)
	{
	   command("say 时间不到，你来的太勤快了。\n");
	   return 1;
	}
	
	message_vision(CYN"\n\n洪七公悠然一笑，乖徒儿，看来你这身子骨还不赖呢，居然通过了鸣沙山的试炼，不错，不错！\n"NOR, me,ob);
	message_vision(HIG"\n\n$N只听得$n在$N耳边轻声给自己讲解降龙十八掌中亢龙有悔的奥妙，能否领悟就看你自己的造化了。\n"
			              +"这样罢，我教你一招‘亢龙有悔’。看好了，。\n"
					+HIY"\n\n说着$n左腿微屈，右臂内弯，右掌划了个圆圈，呼的一声，向外推去，手掌扫到面前一棵松树，喀喇一响，松树应手断折。\n"NOR,me,ob);
	message_vision(HIC"\n\n$n道：“这棵树是死的，如果是活人，当然会退让闪避。学这一招，难就难在要对方退无可退，让无可让，你一招出去，喀喇一下，\n"
	                       +"敌人就像松树一样完蛋大吉。”当下把姿式演了两遍，又把内劲外铄之法、发招收势之道，仔仔细细解释了一通。虽只教得一招，\n"
						   +"却也费了一个多时辰功夫。\n"
						   +"\n\n\n$n见$N练习的不得要领，又说道：“我这掌力要是能发不能收，不能轻重刚柔随心所欲，怎称得上是天下掌法无双的‘降龙十八掌’？”\n"NOR,me,ob);
	
	message_vision(HIR"\n\n$N拉开式子，挑了一棵特别细小的松树，学着$n的姿势，对准树干，呼的就是一掌。那松树晃了几晃，竟是不断。\n"
	                 +HIB"\n\n$n骂道：“傻小子，你摇松树干甚么？捉松鼠么？捡松果么？”$N被他说得满脸通红，讪讪的笑着。洪七公道：\n"
					 +"我对你说过：要教对方退无可退，让无可让。你刚才这一掌，劲道不弱，可是松树一摇，就把你的劲力化解了。\n"
					 +"你先学打得松树不动，然后再能一掌断树。”\n"NOR,me,ob);
	  i = 18;
      if(me->query("m-card-vip")) i =  17;
      if(me->query("y-card-vip")) i =  14;
      if(me->query("buyvip"))     i =  10;
      if (random(me->query_int(1))>40) i=8;
	  i=random(i);
	

	//越聪明学习越快。。。
	j=random(me->query("kar"));
	if (me->query("kar")<31
		&&j>=23
		&&i<3)
	{
       message_vision(HIC"\n\n$N恍然大悟，欢然道：“那要着劲奇快，使对方来不及抵挡。”洪七公白眼道：“可不是么？那还用说？\n"
	   +"你满头大汗的练了这么久，原来连这点粗浅道理还刚想通。可真笨得到了姥姥家。”\n"
	   +"\n\n$n又道：“这一招叫作‘亢龙有悔’，掌法的精要不在‘亢’字而在‘悔”字。倘若只求刚猛狠辣，\n"
	   +"亢奋凌厉，只要有几百斤蛮力，谁都会使了。这招又怎能教黄药师佩服？‘亢龙有悔，盈不可久’，\n"
	   +"因此有发必须有收。打出去的力道有十分，留在自身的力道却还有二十分。哪一天你领会到了这‘悔’的味道，\n"
	   +"这一招就算是学会了三成。好比陈年美酒，上口不辣，后劲却是醇厚无比，那便在于这个‘悔’字。”\n"NOR,me,ob);
	    message_vision(HIR"\n\n恭喜你！你终于领悟了降龙十八掌的精髓武技，习得亢龙有悔绝技。\n"NOR,me);
	  command("chat* haha"+me->query("id"));
	   command("chat "+me->query("name")+"用了这么长时间终于领悟了亢龙有悔，真够笨的。");
	   command("chat "+"丐帮降龙十八掌乃是武林中最霸道的掌法,精髓之一在于亢龙有悔。");
	   command("chat* congra"+me->query("id"));
	   command("chat "+"东邪、西毒、南帝、北丐、中神通乃是武林五绝。乖徒儿你千万不能弱了我大丐帮的威风！");	   
	  
	   log_file("quest/xlzkanglong",sprintf("%s(%s) 在鸣沙山体炼后，得到洪七公的亲自指点亢龙有悔。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/kanglong/fail"),me->query("combat_exp"),me));
	   
	   me->set("kanglong/pass",1);
	   me->set("title",HIY"洪七公嫡传弟子"NOR);
	   return 1;
	}
	else
	{
		message_vision(HIC"\n\n$N虽然听洪七公说了亢龙有悔的精要，但对于如何使用的劲力法门一时之间却是难以理解。降龙十八掌的\n"
		+"威力并没有发挥出来，看来你还是有待于重新跟洪七公学习了。\n"NOR,me,ob);
		log_file("quest/xlzkanglong",sprintf("%8s%-10s得到洪七公的亲自指点亢龙有悔，但并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/kanglong/fail"),me->query("combat_exp"),me));
		me->add("xlz/kanglong/fail",1);
		me->set("xlz/kanglong/time",time());
		return 1;
	}     
   
}
