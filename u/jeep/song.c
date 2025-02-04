// song.c 宋远桥
// 此文件为bonus的例子文件
// bonus/武当 bonus/雪山 这种保存方式保存不同Job下的bonus
// By Spiderii@ty 重要job npc.无法杀死!
// By Spiderii@ty 加入yttlg quest
// By lsxk@hsbbs 2008/1/11  统一任务奖励算法。

inherit NPC;
inherit F_MASTER;
//WD_JOB_ROUND 11
#include <jobround.h>
#include <job_mul.h>
#include <ansi.h>
#include <get_place.h>
string ask_me();
string ask_me1();
string ask_me2();
string ask_me3();
string ask_me4();
string ask_me5();
string ask_me6();
string ask_me7();
int check(object ob);

void create()
{
	set_name("宋远桥", ({ "song yuanqiao", "song" }));
	set("nickname", "武当首侠");
	set("long",
		"他就是张三丰的大弟子、武当七侠之首的宋远桥。\n"
		"身穿一件干干净净的灰色道袍。\n"
		"他已年过六十，身材瘦长，满脸红光。恬淡冲和，沉默寡言。\n");
	set("gender", "男性");
	set("age", 61);
	set("attitude", "peaceful");
	set("shen", 10000);
	set("str", 29);
	set("int", 27);
	set("con", 26);
	set("dex", 26);
	set("no_get","宋远桥对你而言太重了。");
	set("no_bark",1);
	set("job_npc", 1);

	set("max_qi", 35000);
	set("max_jing", 10000);
	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 200);
	set("combat_exp", 9000000);
	set_skill("blade", 400);
	set_skill("cuff", 400);
	set_skill("force", 400);
	set_skill("yinyun-ziqi", 400);
	set_skill("dodge", 400);
	set_skill("wudang-quan", 400);
	set_skill("tiyunzong", 400);
	set_skill("taoism", 180);
	set_skill("strike", 400);
	set_skill("zhenshan-mianzhang", 400);
	set_skill("parry", 400);
	set_skill("literate", 100);
	set_skill("xuanxu-daofa", 400);
	set_skill("sword", 400);
	set_skill("taiji-jian", 400);
	map_skill("sword", "taiji-jian");
	set_skill("wudang-quan", 140);
	map_skill("force", "yinyun-ziqi");
	map_skill("dodge", "tiyunzong");
	map_skill("strike", "zhenshan-mianzhang");
	map_skill("parry", "zhenshan-mianzhang");
	prepare_skill("strike", "zhenshan-mianzhang");
	create_family("武当派", 2, "弟子");

	set("inquiry", ([
		"秘籍" : (: ask_me :),
		"概要" : (: ask_me1 :),
		"工作" : (: ask_me2 :),
		"job" : (: ask_me2 :),
		"巡山" : (: ask_me2 :),
		"fangqi" : (: ask_me3 :),
		"放弃" : (: ask_me3 :),
		"abandon" : (: ask_me3 :),
		"贡献" : (: ask_me4 :),
		"次数" : (: ask_me4 :),
		"功劳" : (: ask_me4 :),
		"gongxian" : (: ask_me4 :),
		"gonglao" : (: ask_me4 :),
		"cishu" : (: ask_me4 :),
		"地点"  : (: ask_me5 :),
		"完成"  : (: ask_me6 :),
		"finish"  : (: ask_me6 :),
		"俞岱岩"  : (: ask_me7 :),
	]));

	set("book_count1", 1);
	set("book_count2", 1);
	setup();

	carry_object("/d/wudang/obj/white-robe")->wear();
}

int ask_me6()
{
	int e,shen,count,j,i,time,gold,gold2;
	int bo;
	mapping fam;
	object ob;
	ob = this_player();

	if (!ob) return; 

	fam = ob->query("family");
	count = ob->query("job_time/武当",1);

	bo = (int)ob->query("bonus/武当");
	j = ob->query("bonus/武当");

	e = 110*j + random(100);         //modify by campsun

	if(e <= 100) e = 100+random(25);
	if(e>=500) e = 400+random(20);
			
	if(ob->query_temp("wd/wd_job_lost2")) {
		command("faint "+ob->query("id"));
		command("say "+ob->name()+"，据门派弟子来报，"+ob->query_temp("wd/wd_job_lost2_man")+"已经帮你把那恶贼给赶跑了！");
		ob->delete_temp("wd/wd_job");
		ob->delete_temp("wd/wd_job_place");
		ob->delete_temp("wd/wd_job_lost2");
		ob->delete_temp("wd/wd_job_lost2_man");
		ob->add("bonus/武当",-3);
		ob->apply_condition("job_busy", 3);
		return 1;
	}
	if(ob->query_temp("wd/wd_job_lost") && !ob->query_temp("wd/wd_jobok") ) {
		command("sigh "+ob->query("id"));
		command("say "+ob->name()+"你怎么搞的，居然让那恶贼给跑了！");
		ob->delete_temp("wd/wd_job");
		ob->delete_temp("wd/wd_job_place");
		ob->delete_temp("wd/wd_job_lost");
		ob->add("bonus/武当",-3);
		ob->apply_condition("job_busy", 3);
		return 1;
	}
       
	if(ob->query_temp("wd/wd_jobok") ){        	
		command("thumb "+ob->query("id"));
		command("say 很好，祝贺你完成了任务，下去休息休息吧！");            
		count += 1;
		ob->set("job_name","武当锄奸");
		if( ob->query("family") && ob->query("family/family_name")!="桃花岛")
			shen = 1;
		else
			shen = 0;

		//新调整武当收益计算方式，随难度增加奖励增多模式
		switch(bo)
		{
			case 0..5:
				TASKREWARD_D->get_reward(ob,"武当",shen,0,0,1 + random(2),0,0,0,"宋远桥");                           
			break;
			case 6..7:
				bo = bo + 6;
				TASKREWARD_D->get_reward(ob,"武当",shen,0,0,bo,0,0,0,"宋远桥");                         
			break;
			case 8..9:
				bo = bo + 10;
				TASKREWARD_D->get_reward(ob,"武当",shen,0,0,bo,0,0,0,"宋远桥");    
			break;
			case 10..11:
				bo = bo * 2 + 1;
				TASKREWARD_D->get_reward(ob,"武当",shen,0,0,bo,0,0,0,"宋远桥");
			break;
			default:
				TASKREWARD_D->get_reward(ob,"武当",shen,0,0,1 + random(2),0,0,0,"宋远桥");
			break;
		}
			   
		ob->delete_temp("wd/wd_job");
		ob->delete_temp("wd/wd_job_place");
		ob->delete_temp("wd/wd_jobok");

		i = 40 - ob->query_condition("wd_job");
		if (i >= 18)
			ob->apply_condition("job_busy", 3);
		else
			ob->apply_condition("job_busy", (18-i)/3);
		ob->apply_condition("wd_job", e/100);
				
		// yttlg quest.
		// 经验值大于 10M 武当的随机数大于 2000
		// 福缘随机数大于 25 24小时一次 加入次数限制。
		time = time() - ob->query("quest/yttlg/time");                                           
		if (random(ob->query("job_time/武当")) > 2000 
		&& time > 86400
		&& ob->query("combat_exp")>1000000
		&& random(ob->query("kar")) > 25
		&& !ob->query_temp("quest/yttlg/story")
		&& !ob->query("quest/yttlg/pass")
		//&& (ob->query("quest/yttlg/fail") <= 3)
		&& ob->query("family/family_name")=="武当派") 
		{      
			ob->set_temp("quest/yttlg/story",1);
			ob->set("quest/yttlg/time", time());
			log_file("quest/yttlg", sprintf(HIR"%s(%s) 触发倚天屠龙功。富源：%d；经验：%d。\n"NOR, ob->name(1),ob->query("id"), ob->query("kar"),ob->query("combat_exp")) );

			command(HIW"say "+ob->query("name")+",今日是师傅九十寿辰之日,往常都是我们七个师兄弟集齐向师傅拜寿。\n"NOR);
			command(HIW"say 只是你三师兄俞岱岩前几日去南方诛灭一巨盗,迟迟不见回来。你不妨去山脚下迎迎,莫要误了时辰。\n"NOR);
		}
		return 1;
	}
	else {
		command("? "+ob->query("id"));
		command("kick "+ob->query("id"));
		command("say "+ob->name()+"你怎么搞的，任务都没做,我看你是捣乱来了！");  
		return 1;
	}
	return 1;
}

void kill_ob(object me)
{
	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "strike.bingdi" :),
		(: perform_action, "dodge.zong" :),
	}));
	::kill_ob(me);
}

int accept_fight(object me)
{
	if((int)me->query("shen") < 1) {
		command("say 习武之人应志在锄恶济善，"+RANK_D->query_respect(me)+"目露瘴气，有违武学之本？");
		return 0;
	}
	::fight_ob(me);
	return 1;
}

void attempt_apprentice(object ob)
{
	if ((int)ob->query("shen") < 10000) {
		command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) +
				"是否还做得不够？");
		return;
	}
	command("say 好吧，贫道就收下你了。");
	command("recruit " + ob->query("id"));
}

string ask_me()
{
	mapping fam;
	object ob;
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "武当派")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	if(query("book_count2") < 1)
		return "你来晚了，本派的内功心法不在此处。";
	add("book_count2",-1);
	ob = new(BOOK_D("force_book"));
	ob->move(this_player());
	return "好吧，这本「太极十三式」你拿回去好好钻研。";
}

string ask_me1()
{
	mapping fam;
	object ob,song;
	song = this_object();
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "武当派")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	if (query("book_count1") < 1)
		return "你来晚了，刀法概要已经不在此处了。";
	add("book_count1",-1);
	ob = new(BOOK_D("blade_book"));
	ob->move(this_player());
	return "这本书中讲述的刀法要领，你会去好好研究一下。";
}

string ask_me2()
{
	object me, ob, *living, target;
	string str,str2;
	string str_temp;
	object room, oroom, lastroom;
	int i, j, k, a, b,t;
	string * exits,*dirs;
	string far;

	me=this_player();
	str2 = me->query_temp("wd/wd_job_place");
	str_temp = "";

	if (me->query_temp("wd/wd_job") && !me->query_temp("wd/wd_job_place"))
		return "啊……，对不起，地点有误，你放弃重新再来吧。";

	if (me->query("combat_exp") < 100000 )
		return "这位" + RANK_D->query_respect(me) + "武功未成，还是去做别的工作吧！";

	if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";

	if(!wizardp(me)){
		if (me->query("menggu"))
			return "哼，你已身属蒙古，还想做什么？";

		if ( me->query_condition("killer"))
			return "你现在是官府捉拿的要犯，还想帮我武当锄奸？";

		if (me->query_temp("wd/wd_job"))
			return "我不是告诉你了吗，有人在捣乱。你就快去吧！";

		if (me->query("job_name") =="武当锄奸")
			return "你刚做完武当锄奸任务，还是先去休息一会吧。";

		if (me->query("shen") < 1 && !wizardp(me) )
			return RANK_D->query_respect(me) + "的正气还不够，我无法放心让你做这个任务！";

		if ( me->query_condition("job_busy")){
			if (me->query("job_name")=="武当锄奸")
				return "现在暂时还没有工作让你去做。";
			if( me->query("job_name"))
				return "你刚做完"+me->query("job_name")+"任务，还是先休息一会吧。";
			return "你正忙着别的事情呢。";
		}

		if (me->query_condition("wd_job"))
			return "现在暂时没有适合你的工作。";
  
	}

	ob=new(__DIR__"robber");
	ob->move(environment(this_object()));
		
	living = livings();
	for (i=0;i<sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		if( check(living[j]) ){
			target = living[j];
			room = environment(target);
			if( !mapp(room->query("exits")) || sizeof(room->query("exits"))<1 ) continue;

			if( get_place(base_name(room))!="" ) {
				oroom = room;
				if ( random(10)<3 && target->query("race")=="人类" ) {
					j = 0;
					break;
				}

				lastroom = room;
				j = 1+random(4);//改得好找些:)
				for(k=0;k<j;k++) {
					exits = values(room->query("exits"));
					dirs = keys(room->query("exits"));
					b = sizeof(exits);
					t =0;
					while( (a=random(b))>=0 && b>1 && t<10 ) {
						t++;
						if(!room->valid_leave(ob, dirs[a])) continue;
						if (b==2)
							if ((exits[0]==base_name(lastroom) && exits[1]==base_name(oroom))
							 || (exits[1]==base_name(lastroom) && exits[0]==base_name(oroom)))
								break;
						if (exits[a]==base_name(lastroom) || exits[a]==base_name(oroom)) continue;
						break;
					}
					//write(sprintf("%d\n",t));
					lastroom = room;
					if( !(room = find_object(exits[a])) )
						if( !(room = load_object(exits[a])) )
							break;
				}
				if(k<j) continue;
				break;
			}
		}
	}

	if( !target || !room )
		return "暂时没有任务需要做，你过一会儿再来吧。";

	me->set_temp("wd/wd_job",1);
	me->set_temp("wd/wd_job_place", get_place(base_name(oroom))+oroom->query("short"));
	me->apply_condition("wd_job",20+random(10));
	me->apply_condition("job_busy",20+random(10));
	command("nod "+me->query("id"));
        
	if (me->query("bonus/武当") >= WD_JOB_ROUND || !me->query("bonus/武当") || me->query("bonus/武当") < 1)
	{
		if (me->query("bonus/武当") == WD_JOB_ROUND)
			me->set("bonus/武当", 4);
		else
			me->set("bonus/武当", 1);
	}
	else
		me->add("bonus/武当", 1);        

	ob->set_temp("target", me->query("id") );
	ob->setparty(me->query("bonus/武当"),me->query("max_pot")-100,me->query("combat_exp"));
	ob->move(room); 

	log_file("job/wd_job",sprintf("%s(%s)开始做wd job,目前实战经验：%d\n", me->name(),me->query("id"),me->query("combat_exp")),me);
	str = strip(me->query_temp("wd/wd_job_place"));

	if(wizardp(me) && me->query("env/test")){
		tell_object(me,"目标Npc从 "+base_name(oroom)+" 移到-> "+base_name(room)+"    "+room->query("short")+"\n");
		tell_object(me,"Round:"+me->query("bonus/武当")+" !\n");
	}
	if (j)
		far = HIY+"周围方圆"+CHINESE_D->chinese_number(j)+"里之内"+GRN;
	else
		far = "";

	if (strlen(str)<=1) {
		tell_object(me, GRN"宋远桥在你的耳边悄声说道：据说"+ob->query("title")+HIC+ob->query("name")+GRN"正在\n"
			+HIY+ CHINESE_D->font(str) + GRN + far +"捣乱，你马上去给我巡视一圈。\n");
                
	} else
		tell_object(me, GRN"宋远桥在你的耳边悄声说道：据说"+ob->query("title")+GRN+ob->query("name")+"正在"+ me->query_temp("wd/wd_job_place") +GRN + far + "捣乱，你马上去给我巡视一圈。\n");
        
	if (ob->query("family/family_name")=="武当派")
		str_temp += GRN"宋远桥在你的耳边悄声说道："+RANK_D->query_self(this_object())+"已追查到此人是我武当出身，尤为擅长"HIC+to_chinese(ob->query("f_w_skill"))+GRN"的功夫。\n"+
			RANK_D->query_respect(ob)+"若能将其诛杀，不但为江湖除去一害，也能为"+RANK_D->query_self(this_object())+"讨个公道，自当感激不尽。\n";
	else {
		str_temp+=GRN"宋远桥在你的耳边悄声说道：据门派弟子来报，此人是来自"HIY+ob->query("family/family_name")+GRN"的";
		if (random(2)==0)
			str_temp+="叛徒，";
		else
			str_temp+="高手，";
		str_temp+= "尤为擅长"HIC+to_chinese(ob->query("f_w_skill"))+GRN"的功夫。\n";
	}

	switch ((int)me->query("bonus/武当"))
	{
		case 6..7:
			str_temp+=GRN"宋远桥在你的耳边悄声说道：此人的武功" + HIC + "颇为了得" + GRN + "，你可得小心对付哦。\n"NOR;
			break;
		case 8..9:
			str_temp+=GRN"宋远桥在你的耳边悄声说道：此人的武功" + HIC + "极其厉害" + GRN + "，你可得小心应付。\n"NOR;
			break;
		case 10..11:
			str_temp+=GRN"宋远桥在你的耳边悄声说道：此人的武功" + HIW + "已入化境" + GRN + "，打不过可不要逞能。\n"NOR;
	}	
       		
	tell_object(me, str_temp);
	tell_room( environment(this_object()), this_object()->name() + "在" + me->name() + "耳边小声地说了些话。\n", ({ me, this_object() }) );              
	return "你快去快回，一切小心啊。";
}

string ask_me3()
{
	object ob = this_player();

	if(ob->query_temp("wd/wd_job")){
		ob->delete_temp("wd/wd_job");
		ob->delete_temp("wd/wd_job_place");

		if (ob->query("bonus/武当")<=5)
		{
			ob->apply_condition("job_busy", 8);
			ob->set("bonus/武当",0); 
			return ob->name()+"，你太让我失望了，居然这么点活都干不好，先退下吧！";
		}
		else if (ob->query("bonus/武当")>5)
		{
			ob->apply_condition("job_busy", 4); 
			ob->add("bonus/武当",-3);
			return ob->name()+"，这个任务确实比较难完成，下次给你简单的，先退下吧！";                	
		}
	}
	return ob->name()+"，你又没在我这里领任务，瞎放弃什么呀！";
}

string ask_me4()
{
	object ob;
	ob = this_player();
	if(!ob->query("job_time/武当")){
		return "对不起，"+ob->name()+"，你好象还没有在我这里领过任务呢，加油干吧！";
	}
	return ""+ob->name()+"，你已经成功地铲除了"+CHINESE_D->chinese_number((int)ob->query("job_time/武当"))+"名恶贼！";
}

string ask_me5()
{
	object me;
	string str;
	me = this_player();
	str = strip(me->query_temp("wd/wd_job_place"));


	if (!me->query_temp("wd/wd_job"))
		return "你都没有领任务，我怎么知道你要杀的恶贼跑哪里去了呢？";
	if (strlen(str)<=1) {
		tell_object(me, GRN"宋远桥在你的耳边悄声说道：你要杀的恶贼正在\n"
			+ CHINESE_D->font(str) + GRN + "附近捣乱呢，你还不马上去巡视一圈。\n");

	} 
	else
		tell_object(me, GRN"宋远桥在你的耳边悄声说道：你要杀的恶贼正在"+ me->query_temp("wd/wd_job_place") + GRN +"附近捣乱呢，你还不马上去巡视一圈。\n");
	return "一路小心啊！";
}

string ask_me7()
{
	object me;
	me = this_player();

	if (!me->query_temp("quest/yttlg/story"))
		return "没看我在忙着么？";
	me->delete_temp("quest/yttlg/story");
	me->set_temp("quest/yttlg/asksong",1);
	tell_object(me,HIC"我三师弟应该快来了，赶紧到山脚下去迎接他看看，千万注意，小心歹人触摸。\n"NOR);
	return "宋远桥又嘱咐了$n一番，一副忧心冲冲的样子，似乎要发生什么事情一样。\n";
}

void destroying(object obj)
{
	if (!obj) return;
	if (userp(obj)) command("drop "+obj->parse_command_id_list()[0]);
		else destruct(obj);
}

string *no_kill_list = ({
	"mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

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
	|| room->query("short") == "地下黑拳市"
	|| room->query("short") == "武僧堂"
	|| strsrch(room_name = file_name(room),"/d/") != 0                    //modified by campsun 2004.2.4 为了和bx code兼容
	|| strsrch(room_name, "/d/wizard/") == 0
	|| strsrch(room_name, "/d/wuguan/") == 0
	|| strsrch(room_name, "/d/death/") == 0
	|| strsrch(room_name, "/d/mingjiao/lsd/") == 0
	|| strsrch(room_name, "/d/mingjiao/bhd/") == 0
	|| strsrch(room_name, "/d/shaolin/fumoquan") == 0
	|| strsrch(room_name, "/d/xiaoyao/") == 0
	|| strsrch(room_name, "/d/quanzhen") == 0
	|| strsrch(room_name, "/d/menggu/") == 0
	|| strsrch(room_name, "/d/xiakedao/") == 0
	|| strsrch(room_name, "/d/luoyang/") == 0    
	|| strsrch(room_name, "/d/beijing/") == 0
	|| strsrch(room_name, "/d/baituo/") == 0)
		return 0;
	return 1;
}

void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/kungfu/class/wudang/song");
		ob->move("/d/wudang/sanqing");
	}
	::die();
}
