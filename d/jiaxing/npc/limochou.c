
#include <ansi.h>
inherit NPC;

int do_look(string);
int ask_me();
string ask_skill();
string ask_sanwu();
void create()
{
	object ob;
	set_name("李莫愁", ({ "li mochou", "li", "mochou" }));
	set("long", "她生得极为美貌，但冰冷的目光让人不寒而立。\n");
	set("nickname", HIR"赤练仙子"NOR);
	set("gender", "女性");
	set("rank_info/respect", "道姑");
	create_family("古墓派", 3, "弟子");

	set("age", 27);
	set("attitude","heroism");
	set("str", 22);
	set("dex", 23);
	set("con", 20);
	set("int", 24);
	set("shen_type", -1);

	set_skill("parry", 150);
	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("sword", 150);
	set_skill("throwing",100);
	set_skill("poison", 50);
	set_skill("meinu-quanfa", 150);
	set_skill("cuff", 150);
	set_skill("meinu-quanfa", 150);
	set_skill("yunu-shenfa", 150);
	set_skill("yunu-jianfa", 150);
	set_skill("yunu-xinjing", 150);
	map_skill("force", "yunu-xinjing");
	map_skill("dodge", "yunu-shenfa");
	map_skill("cuff", "meinu-quanfa");
	map_skill("sword", "yunu-jianfa");
	prepare_skill("cuff", "meinu-quanfa");
	set("jiali", 30);

	set("combat_exp", 1100000);

	set("max_qi", 3000);
	set("max_jing", 2200);
	set("eff_jingli", 2000);
	set("neili", 3500);
	set("max_neili", 3500);

	set("inquiry", ([
		"name" : "站远点！",
		"here" : "我不是本地人，不知道。",
		"情" : "你如何能理解其中相思之苦、惆怅之意？",
		"陆展元" : "你问那个薄情的小畜生做什么？",
		"何沅君" : (: ask_me :),
		"三无三不手" : (: ask_sanwu :),
		"五毒神掌" : (: ask_skill :),
		"小龙女" : "那是我的师妹。你问她想干什么？",
		"林朝英" : "那是我的师祖，不该你问的你别问，小心我宰了你。",
	]));

	set("chat_chance", 2);
	set("chat_msg", ({
		"李莫愁纵声而歌，音调凄婉，歌道：「问世间，情是何物，直教生死相许？」\n",
		"李莫愁歌道：「天南地北双飞客，老翅几回寒暑？」\n",
		"李莫愁唱道：「欢乐趣，离别苦，就中更有痴儿女。」\n",
		"李莫愁唱道：「君应有语，渺万里层云，千山暮雪，只影向谁去？」\n",
		"李莫愁词意悲切，声调更是哀怨，唱道：「横汾路，寂寞当年箫鼓。荒烟依旧平楚。」\n",
		"李莫愁歌道：「招魂些何嗟及，山鬼自啼风雨。」\n",
		"李莫愁唱道：「天也妒，未信兴，莺儿燕子俱黄土。」\n",
		"李莫愁唱道：「千秋万古，为留待骚人，狂歌痛饮，来访雁丘处。」\n",
	}));
	setup();
	if (clonep()) {
		ob = unew(BINGQI_D("sword/zhen"));
		if (!ob) ob = unew(BINGQI_D("changjian"));
		ob->move(this_object());
		ob->wield();
		carry_object(BINGQI_D("bb_zhen"));
       	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
		carry_object("/d/wudang/obj/greenrobe")->wear();
	}
}

void init()
{
	::init();
	add_action("do_look","look");
	add_action("do_look","hug");
	add_action("do_look","mo");
	add_action("do_look","18mo");
	add_action("do_look","kiss");
	add_action("do_look","lean");
	add_action("do_look","interest");
	add_action("do_look","flirt");
	add_action("do_look","pretty");
	add_action("do_look","love");
}

int ask_me()
{
	object me;

	me = this_player();
	message_vision(HIR "李莫愁冷笑一声：『我这就送你去见她』！\n"NOR, me);
	kill_ob(me);
	return 1;
}

string *wheres=({
"/d/emei/xiaowu",		"/d/wudang/xiaolu1",		"/d/xiangyang/zhuquemen",
"/d/xiangyang/hanshui1",	"/d/fuzhou/road1",		"/d/xueshan/xuelu2",
"/d/xueshan/houzidong",		"/d/suzhou/lingyansi",		"/d/suzhou/liuyuan",
"/d/jiaxing/tieqiang",		"/d/hz/longjing",		"/d/hz/huanglong",
"/d/hz/yuhuang",		"/d/hz/tianxiang",		"/d/miaojiang/jiedao4",
"/d/foshan/duchang",		"/d/huanghe/shulin5",		"/d/hz/changlang1",
"/d/hz/yuquan",			"/d/hz/longjing",		"/d/xingxiu/shamo3",
"/d/wudang/xuanyue",		"/d/emei/guanyinqiao",		"/d/emei/basipan3",
"/d/tiezhang/shanmen",		"/d/tiezhang/hclu",		"/d/xueshan/huilang4",
"/d/emei/caopeng",		"/d/mingjiao/bishui",		"/d/mingjiao/shanting",
"/d/fuzhou/haigang",		"/d/fuzhou/laozhai",		"/d/xingxiu/shamo2",
"/d/jiaxing/nanhu",		"/d/village/caidi",		"/d/shaolin/songshu2",
"/d/xiangyang/tanxi",		"/d/huashan/husun",		"/d/huashan/yunu",
"/d/mr/yanziwu/xiaojing2",	"/d/mr/mtl/liulin",		"/d/suzhou/shihu",
"/d/suzhou/xuanmiaoguan",	"/d/suzhou/zijinan",		"/d/hengshan/cuiping2",
"/d/hengshan/guolaoling",	"/d/shaolin/talin1",		"/d/wudang/houshan/husunchou",
"/d/shaolin/shanlu8",		"/d/xueshan/shanlu7",		"/d/foshan/road10",
"/d/foshan/xiaolu2",		"/d/emei/jiulaodong",		"/d/hengshan/beiyuemiao",
"/d/gb/xinglin2",		"/d/city/shangang",		"/d/fuzhou/zhongxin",
"/d/huanghe/huanghe4",		"/d/lanzhou/shamo",		"/d/emei/gudelin3",
"/d/cangzhou/dongjie1",		"/d/tanggu/center",		"/d/putian/xl6",
"/d/dali/wuliang/songlin6",	"/d/gumu/xuantie/linhai8",	"/d/gumu/jqg/zhulin5",
});

string ask_skill()
{
	object me = this_player();
	object ob,room;
	int p, y=0;

	if (!me->query("family")
	 ||  me->query("family/family_name") != "古墓派"){
		command("sneer "+ me->query("id"));
		return "这五毒神掌乃是从五毒秘传中演化而来，虽然师傅不把我当古墓弟子，但我却从不这样认为！";
	}
	if ( time()-me->query("quest/gumu/wdsz/time") < 86400){
		command("sneer "+ me->query("id"));
		return RANK_D->query_respect(me) + "你来的也太勤快了。";
	}
	if ( me->query_skill("yunu-xinjing", 1) < 200 ){
		command("sneer "+ me->query("id"));
		return RANK_D->query_respect(me)+"的玉女心经还不够200熟练，学来也无用。";
	}

	if( me->query_temp("limochou/ask") && !wizardp(me))
		return "我不是已经告诉你了么，还不快去帮我找回《五毒秘传》。";

	if(me->query("quest/gumu/wdsz/pass") && !wizardp(me))
	{
		command("? " + me->query("id"));
		if (me->query("askwudu-shenzhang")) return "你已经用掉最后一次机会了。";
		if (!me->query_skill("wudu-shenzhang")) 	
           {
			   command("say " + "太蠢了，居然忘记了这么重要的绝学，最后再教你一次。");
			   me->set("askwudu-shenzhang",1);
			   me->improve_skill("wudu-shenzhang", 10+random(me->query_int()));
			   return "你重新获得五毒神掌。";
		    }
		return "你不是已经学会了五毒神掌么？";
	}

	y = sizeof( filter_array(children("/d/jiaxing/npc/lu"),(:clonep:)));
	
	if(y > 0)
		return "暂时我没有这个兴趣，你回去吧。";

	p = random(sizeof(wheres));
	room= find_object(wheres[p]);
	if (!room) room=load_object(wheres[p]);
	
	if(!objectp(room)) return "暂时我没有这个兴趣，你先回去吧！!";
	ob= new("/d/jiaxing/npc/lu");
	ob->move(room);
	me->set_temp("limochou/ask", 1);
	command("say 这小妮子一项机灵古怪，我方才听人说她在"+room->query("outdoors")+room->query("short")+"一带活动，你去替我找到她！\n");
	message_vision(CYN"李莫愁露出一脸的怨恨之色。\n"NOR,me);
	return "我那本《五毒秘传》被陆无双那小贱人给偷走了，如果你能帮我找回此书，我就传授你五毒神掌。";
}

int accept_object(object who, object ob,object me)
{
	me= this_object();

	if( ob->query("id") != "wudu mizhuan"){
		command("say 你给我这东西干吗？");
		return 0;
	}
	if( ob->query("owner") != who->query("id")
	 || !who->query_temp("limochou/ask"))
	{
		command("haha");
		command("say 哼，这个小贱人，居然把我的秘籍偷跑了,这下终于回来了。");
		command("say 多谢"+RANK_D->query_respect(who) + "帮忙，小女子多谢了。");
		who->delete_temp("limochou");
		call_out("dest", 1, ob);
		return 1;
	}
	command("say 好吧，看你如此勤快，听话，那我就传授你五毒神掌的心法吧。");
	command("whisper "+ who->query("id")+ " 掌分阴阳，气灌任督，以毒蛇、蜘蛛、蟾蜍、蜈蚣、蝎子毒液浸泡双手，徐徐吸之。");
	command("say 你听好了，能否学会就看你的本事了。\n");
	command("say 若学不会，还不如我一掌拍死你算了");
	
	remove_call_out("thinking_wudu");
	call_out("thinking_wudu",1,who);
	//who->set("quest/gumu/wdsz/pass", 1);
	who->delete_temp("limochou");
	call_out("dest", 1 ,ob);
	return 1;
}

void dest(object obj)
{
	if(! obj) return;
	destruct(obj);
}

int do_look(string target)
{
	object me;

	me = this_player();
	if ( target
	&& present(target, environment()) == this_object()
	&& living(this_object()) 
    &&!me->query_temp("lmc/throw"))
                if ((string)me->query("gender") == "男性" && me->query("combat_exp") >=200000) {
 
					message_vision(HIR "李莫愁大怒，喝道：我最恨你们这些薄情的臭男人！去死吧！\n"
+"李莫愁决心杀死$N！\n"NOR, me);
			if ( present("bingpo yinzhen", this_object()) && ! this_object()->is_busy())
				me->set_temp("lmc/throw", 1);
			command("throw yinzhen at " + me->query("id"));
			kill_ob(me);
		}
}

void kill_ob(object me)
{
	object li;
	command("haha");
	
        if ( present("bingpo yinzhen", this_object()) && ! this_object()->is_busy())
			me->set_temp("lmc/throw", 1);

			command("throw yinzhen at " + me->query("id"));
	//	li=new("kungfu/class/gumu/lmc");
		//li->move(environment(me));
	//	li->kill_ob(me);
	//	destruct(this_object());		
	   ::kill_ob(me);
	   return;
}

int thinking_wudu(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("canwu_wudu")<(10+random(5)))
  { 
	  me->add_temp("canwu_wudu",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才李莫愁所展示的五毒神掌的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
			 me->add_condition("snake_poison",1);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking_wudu");
	  call_out("thinking_wudu",3+random(3), me);
   } else
   {  
	  me->delete_temp("canwu_wudu");     
      
	  j = 18;
      if(me->query("m-card-vip")) j =  14;
      if(me->query("y-card-vip")) j =  12;
      if(me->query("buyvip"))     j =  10;
	  
	  i= random(j); 
 
     if(i<6 && random(me->query("kar"))>25)
	 {
		tell_object(me,HIG"\n你按照李莫愁的指点，对五毒神掌的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIY"你按照李莫愁所言，将掌法演练一遍，初始之时稍显生涩。\n+"+
							"旁边的李莫愁轻哼一声，指点了你几个关键要点，你逐渐演练熟练起来、\n"+
							"你忽然觉得手心一片麻痒难当，顿时剧痛传来。李莫愁喝道，“忍住”！\n"NOR);
		tell_object(me,HIR"\n你急忙收敛心神，寸关穴一阵剧痛，劲力奔涌而出，直奔劳宫穴而去！。\n"+
							"\n恭喜！因缘际会，你学会了这门五毒神掌绝技！\n"NOR);
       	me->improve_skill("wudu-shenzhang", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/gumu/wdsz/pass", 1);
		me->set("title",HIG"古墓李莫愁传人"NOR);
		me->start_busy(1);
		log_file("quest/wudushenzhang", sprintf("%8s(%8s) 失败%d次后，彻底领悟五毒神掌的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/gumu/wdsz/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gumu/wdsz/fail",1);
		me->set("quest/gumu/wdsz/time",time());
		command("heng ");
		tell_object(me,HIY"你听了李莫愁的指点，虽然听见了五毒神掌的奥秘，可是对五毒神掌的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/wudushenzhang", sprintf("%8s(%8s) 五毒神掌解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/gumu/wdsz/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}


string ask_sanwu()
{
	object me = this_player();
	

	if (!me->query("family")
	 ||  me->query("family/family_name") != "古墓派"){
		command("sneer "+ me->query("id"));
		return "这三无三不手乃是我古墓绝技，宵小之辈也敢！";
	}
	if ( time()-me->query("quest/gumu/sanwu/time") < 86400){
		command("sneer "+ me->query("id"));
		return RANK_D->query_respect(me) + "你来的也太勤快了。";
	}
	if ( me->query_skill("yunu-xinjing", 1) < 350 ){
		command("sneer "+ me->query("id"));
		return RANK_D->query_respect(me)+"的玉女心经还不够350熟练，学来也无用。";
	}

	if(me->query_skill("wudu-shenzhang",1)<1 && !wizardp(me))
		return "先学会五毒神掌，三无三不手才能融会贯通。";

	if(me->query("quest/gumu/sanwu/pass") && !wizardp(me))
	{
		command("? " + me->query("id"));
		me->set("mytitle/quest/lisanwu",HIG"三无三不"NOR);
		return "你不是已经学会了三无三不手了么？";
	}
	remove_call_out("thinking_sanwu");
	call_out("thinking_sanwu",1,me);
	me->start_busy(99);
	message_vision(CYN"李莫愁狠狠地说道，无所不为，无所不至，无孔不入，乃是三大绝招。\n"NOR,me);
	return "只要遇到这三招，没有几个不认输的，我大古墓威武的很呢。咯咯咯咯。。。";
}

int thinking_sanwu(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("canwu_sanwu")<(10+random(5)))
  { 
	  me->add_temp("canwu_sanwu",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才李莫愁所展示的三无三不手的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
			  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking_sanwu");
	  call_out("thinking_sanwu",3+random(3), me);
   } else
   {  
	  me->delete_temp("canwu_sanwu");     
      j = 20;
      if(me->query("m-card-vip")) j =  15;
      if(me->query("y-card-vip")) j =  12;
      if(me->query("buyvip"))     j =  10;
	  
	  i= random(j); 
 
     if(i<5 && random(me->query("kar"))>26)
	 {
		tell_object(me,HIG"\n你按照李莫愁的指点，对三无三不手的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIY"你按照李莫愁所言，将鞭法演练一遍，初始之时稍显生涩。\n+"+
							"旁边的李莫愁轻哼一声，指点了你几个关键要点，你逐渐演练熟练起来、\n"+
							"你忽然觉得手中的鞭子如臂使指，快活无比！\n"NOR);
		tell_object(me,HIR"\n恭喜！因缘际会，你学会了这门三无三不手绝技！\n"NOR);
       	me->improve_skill("yinsuo-jinling", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/gumu/sanwu/pass", 1);
		me->set("mytitle/quest/lisanwu",HIG"三无三不"NOR);
		me->start_busy(1);
		log_file("quest/sanwu", sprintf("%8s(%8s) 失败%d次后，彻底领悟三无三不手的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/gumu/sanwu/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gumu/sanwu/fail",1);
		me->set("quest/gumu/sanwu/time",time());
		command("heng ");
		tell_object(me,HIY"你听了李莫愁的指点，虽然听见了三无三不手的奥秘，可是对三无三不手的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/sanwu", sprintf("%8s(%8s) 三无三不手解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/gumu/sanwu/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}