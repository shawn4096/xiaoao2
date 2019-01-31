// bei.c 贝海石
// By River 2003.2.26
// 重要NPC.杀不死 by spiderii@ty
// 统一奖励算法  by lsxk@hsbbs 2008/1/10

#include <ansi.h>
#include <job_mul.h>
#include <get_place.h>
inherit NPC;
#define XKX_QUEST1 "quest/侠客行/摩天崖/"
#define XKX_QUEST2 "quest/侠客行/玄铁令/"
//#define XKX_QUEST3 "quest/侠客行/雪山奇缘/"
//#define XKX_QUEST4 "quest/侠客行/侠客岛/"


string ask_job();
string ask_times();
string ask_finish();
string ask_fail();
string ask_xtling();

int check(object ob);

void create()
{
	set_name("贝海石",({"bei haishi", "bei", "haishi"}));
	set("title", "长乐帮总管");
	set("nickname",HIY"着手回春"NOR);
	set("long", "他就是长乐帮总管，人称着手回春的贝海石。\n"+
		"他是一个脸有病容的老者。\n");
	set("age", 65);
	set("attitude", "friendly");
	set("shen", 0);
	set("str", 26);
	set("int", 29);
	set("con", 27);
	set("dex", 30);
	set("no_get", 1);
	set("no_bark", 1);
	set("job_npc", 1);
	set("no_ansuan", 1);

	set("max_qi", 34500);
	set("max_jing", 6200);
	set("eff_jingli", 8500);
	set("jiali", 220);
	set("combat_exp", 12500000); 
	set("unique", 1);

	set_skill("dodge",520);
	set_skill("force", 520);
	set_skill("literate", 300);
	set_skill("strike", 520);
	set_skill("kunlun-shenfa", 520);
	set_skill("banruo-zhang", 520);
	set_skill("shenzhao-jing", 520);
	set_skill("parry", 520);
	set_skill("medicine", 220);

	map_skill("force", "shenzhao-jing");
	map_skill("dodge", "kunlun-shenfa");
	map_skill("parry", "banruo-zhang");
	map_skill("strike", "banruo-zhang");
	prepare_skill("strike", "banruo-zhang");

	set("inquiry", ([
		"任务"	:	(: ask_job :),
		"job"	:	(: ask_job :),
		"完成"	:	(: ask_finish :),
		"finish":	(: ask_finish :),
		"功劳"	:	(: ask_times :),
		"放弃"	:	(: ask_fail :),
		"fangqi":	(: ask_fail :),
		"帮主"	:	"帮主已经失踪多日，我们正在到处寻找中。",
		"侠客岛":	"这个要等帮主回来后，才能商议。",
		"玄铁令":	(: ask_xtling :),

		"长乐帮":	"长乐帮分为龙灵堂、狮威堂、熊敏堂、虎猛堂和豹捷堂五堂。",
	]));

	setup();
	carry_object(ARMOR_D("changshan"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

string *party = ({"龙灵堂","狮威堂","熊敏堂","虎猛堂","豹捷堂"});

string ask_xtling()
{
	object me,bzling;
	me = this_player();
	
	if (!me->query(XKX_QUEST1+"over") 
		&& !present("bangzhu ling",me)
		&& !me->query_temp(XKX_QUEST1+"givebzling")
		&& me->query(XKX_QUEST1+"start"))
	{
		command("kick"+me->query("id"));
		command("say 真是废物，给你的令牌你居然掉了？这么点事都做不好，还能成什么大事！\n");
		command("say 看在SOHU密令我慈悲为怀的份上，就再给你次机会，你可要收好了！\n");
		bzling=new("d/changle/obj/bangzhuling");
		bzling->set("owner",me->query("id"));
		bzling->move(me);
		me->set_temp(XKX_QUEST1+"givebzling",1);

		tell_object(me,HIC"贝海石递给你一个神秘令牌！\n"NOR);
		return "哼！！";
	}
	if (!me->query(XKX_QUEST1+"over"))
	{
		command("say 帮主为人所掳走，我正在派帮中弟子四处打探！\n");
		return "哼";
	}
	
	if (time()-me->query("quest/侠客行/time")<86400)
	{
		command("say 我有些累了，明天再来！\n");
		return "哼";
	}
	if (me->query("combat_exp")-me->query(XKX_QUEST1+"exp")<500000)
	{
		command("say 光偷懒了，你武功再去提高500k经验值再来！\n");
		return "真懒！";
	}
	command("say 这玄铁令本是摩天居士谢烟客的信物");
	command("say 据江湖传言,谁得到这枚铁令，谢烟客可以替他完成一个愿望或要求。");
	command("say 因为谢烟客在江湖威名甚重，这枚玄铁令也就身价倍增了。");
	command("say 帮主既然没有回来，本帮即将遇到一桩极大凶险的事宜。");
	command("say 二十年之期即将到了，你要想替本帮解决大难，须得去帮本帮得到这枚玄铁令。");
	command("say 据帮众最近打探的消息，这枚玄铁令极有可能落在吴道通的手中。");
	command("say 他现在隐居在南阳打铁铺之中，你去替我把这枚玄铁令找来。");
//	command("say 需要是使用判官笔的高手，你要小心。。");
	me->set_temp(XKX_QUEST2+"start",1);
	me->set(XKX_QUEST2+"start",1);
	me->set("quest/侠客行/time",time());

	return "我担心消息走漏，此行甚是凶险，快去快回！\n";

}

string ask_job()
{
	object me, ob, *living, target;
	string str, str2, address;
	object objwhere;
	int i,j;

	me = this_player();
	str2 = party[random(sizeof(party))];

	if (me->query_temp("changle/changle_job") && !me->query_temp("changle/job_place"))
		return "啊……，对不起，地点有误，你放弃重新再来吧。";

	if (me->query_temp("changle/job_place1"))
		return "你不是已经知道了，杀害我帮帮众的仇人在"+me->query_temp("changle/job_place1")+CYN"一带出现过。";

	if ( me->query_temp("changle/done"))
		return "你不是已经进展到一定地步了，还是继续努力吧！";

	if (me->query_temp("changle/changle_job"))
		return "我不是告诉你了吗，我帮有人在"+me->query_temp("changle/job_place")+CYN"遇到袭击，你还不赶快前去救援！";

	if (me->query("job_name") =="长乐帮" && !wizardp(me))
		return "你刚做完长乐帮任务，还是先去休息一会吧。";

	if (me->query("combat_exp") < 100000 )
		return "这位" + RANK_D->query_respect(me) + "武功未成，我帮还不需要你的帮助。";

	if ( me->query_condition("job_busy"))
		return "我帮现在比较空闲，暂时还没有任务让你去做。";
	
	if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";

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
			|| str == "僧舍"
			|| str == HIR"心禅堂"NOR
			|| str == "金刚伏魔圈" ) continue;
			if( get_place(base_name(environment(target))) != "" ) break;
		}
	}

	if( !target )
		return "暂时没有任务需要做，你过一会儿再来吧。";

	ob = new(__DIR__"zhong");
	ob->set_temp("target", getuid(me));
	ob->set("title", HIR"长乐帮"+str2+"属下帮众"NOR);
	ob->move(objwhere);
	ob->set("env/invisibilty", 10);

	for ( j = 0; j < 5; j ++)
		ob->random_move();

	if ( environment(ob)->query("no_fight") || environment(ob)->query("quest") )
		ob->random_move();

	ob->delete("env/invisibilty");

	if (strsrch(file_name(environment(ob)), "/d/zhiye/") >= 0
	 || strsrch(file_name(environment(ob)), "/d/group/") >= 0) {
	 	if ( environment(ob)->query("outdoors"))
			me->set_temp("change/job_place", environment(ob)->query("outdoors")+environment(ob)->query("short"));
	 	else if ( environment(ob)->query("indoors"))
			me->set_temp("change/job_place", environment(ob)->query("indoors")+environment(ob)->query("short"));
		else me->set_temp("changle/job_place", environment(ob)->query("short"));
	}
	else me->set_temp("changle/job_place", get_place(base_name(environment(ob)))+environment(ob)->query("short"));

	if ( ! me->query_temp("changle/job_place"))
		return "暂时没有任务需要做，你就过一会儿再来吧。";

	address = strip(me->query_temp("changle/job_place"));
	me->set_temp("changle/changle_job",1);
	me->set_temp("changle/times", uptime());
	me->apply_condition("job_busy", 40 );
	me->set_temp("changle/npc_name", ob->name(1));
	command("bow "+ me->query("id"));
	command("whisper "+ me->query("id")+" 我接到飞鸽传书，"+str2+"属下帮众"+ob->query("name")+"在"+ address +"处遇到袭击，你赶快前去救援！");
	return "这位"+RANK_D->query_respect(me)+"肯为我帮出力，如能完成使命，必有重赏。";
}

string ask_finish()
{
	object bzling;
	object ob, me = this_player();
	int gold,jobs,x,i,j;
	string msg;
	
	jobs=me->query("job_time/长乐帮");
	x=jobs % 50;

	if (!me->query_temp("changle"))
		return "你根本就没有领任务，完成什么啊？";

	if ( !me->query_temp("changle/done"))
		return "你真的完成任务了么？";

	msg = me->query_temp("changle/target_family");
	switch(me->query_temp("changle/done")){
		case 1:
            TASKREWARD_D->get_reward(me,"长乐帮",0,0,0,-3,0,0,0);
			msg = "既然已经知道了是"+msg+"所为，哼，这个梁子算结上了。";
			//次数已经在函数中增加了
			//me->add("job_time/长乐帮", 1);
			//长乐帮1解密条件
			//jobs>2000 1m以上,jobs为50的倍数
			if (random(jobs) > 2000 
				&& me->query("combat_exp")>1000000
				&& random(me->query("kar")) > 26
				&& x==0
				&& random(10)==2
				&& !me->query(XKX_QUEST1+"start")
				&& !me->query_temp(XKX_QUEST1+"start")
				&& !me->query(XKX_QUEST1+"over"))
			{
				command("look "+me->query("id"));
				command("say 武林风云即将大变，问天下英豪谁终将引领风骚?\n");
				message_vision(HIY"$N从案后抬起头来，瞅了$n一眼，慢条斯理对$n说道，“既然你如此努力为本帮排忧解难，我就暂时把你列为帮中精英看待。”\n"+
									"本帮帮主石中玉为摩天崖主谢烟客所掠，你如果能把本帮帮主解救出来，我长乐帮必有重赏！为了你能找到帮主\n"
									"我先给你一枚帮主令牌,帮主一看就知道！路上小心。\n\n"NOR,this_object(),me);

				me->set_temp(XKX_QUEST1+"start",1);
				me->set(XKX_QUEST1+"start",1);
				bzling=new("d/changle/obj/bangzhuling");
				bzling->set("owner",me->query("id"));
				me->set_temp("quest/侠客行/time",time());
				bzling->set_temp(XKX_QUEST1+"start",1);
				bzling->move(me);

			}

			break;
		case 2:
            TASKREWARD_D->get_reward(me,"长乐帮",0,0,1,1,0,0,0);

			msg = "哎，可惜不能手刃此奸贼，但"+msg+"和我帮的梁子算结上了。";
			//次数已经在函数中增加了
			//me->add("job_time/长乐帮", -1);
			break;
		case 3:
            TASKREWARD_D->get_reward(me,"长乐帮",0,0,1+random(1),4,0,0,0,this_object());
			gold = 1 +random(3);
			MONEY_D->pay_player(me, gold * 10000);
			msg = "做的好！这些金子"+RANK_D->query_respect(me)+"先拿去零花，下次还需要您多为我帮出力。";			
			break;
		default:
			msg = "啊？出问题了，请报告开发人员检查。";
			//me->add("job_time/长乐帮", -1);
			break;
	}
		

	me->delete_temp("changle");
	me->clear_condition("job_busy");
	me->set("job_name", "长乐帮");
	if ( objectp(ob= present("cu bu", me)))
		destruct(ob);


	//tell_object(me,HIW"您被奖励了"+chinese_number(exp)+"点经验，"+chinese_number(pot)+"点潜能，您已经为长乐帮出力"+chinese_number(me->query("job_time/长乐帮"))+"次。\n"NOR);

	return msg;
}

string ask_fail()
{
	object ob, me = this_player();
	int i;

	if (!me->query_temp("changle"))
		return "你根本就没有领任务，完成什么啊？";

	i = 40 - me->query_condition("job_busy");
	if ( i > 8 ) i = 8;
		me->apply_condition("job_busy", 9-i );

	if ( objectp(ob= present("cu bu", me)))
		destruct(ob);

	command("disapp "+ me->query("id"));
	me->delete_temp("changle");
	me->add("combat_exp", -(30+random(10)));
	return "既然你无法完成，那也只能如此了。";
}

string ask_times()
{
	object me = this_player();

	if ( !me->query("job_time/长乐帮"))
		return "这位"+RANK_D->query_respect(me)+"好像还未为本帮出力过。";

	command("addoil "+ me->query("id"));
	return "这位"+RANK_D->query_respect(me)+"，您已经为本帮出力"+chinese_number(me->query("job_time/长乐帮"))+"次了。";
}

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	 || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || !objectp(room=environment(ob))
	 || room->query("no_fight")
	 || room->query("outdoors") == "昆仑翠谷"
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/group/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/changle/") == 0
	 || strsrch(room_name, "/d/city/") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
  //          || strsrch(room_name, "/d/xiaoyao/") == 0
   //|| strsrch(room_name, "/d/quanzhen") == 0
   //|| strsrch(room_name, "/d/menggu/") == 0
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
		ob = new("/d/changle/npc/bei");
		ob->move("/d/changle/xiaoting");
	}
	::die();
}

