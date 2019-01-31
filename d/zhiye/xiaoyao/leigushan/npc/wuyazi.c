// NPC: /d/wizard/npc/wuyazi.c
inherit NPC;
#include <skill.h> 
#include <ansi.h>
#include <command.h>

void create()
{
	set_name("无崖子", ({ "wuyazi","wuya","zi" }));
    set("title", HBBLU"「逍遥派掌门」"NOR);
	set("gender", "男性" ); // 性别
        set("age", 40);
		set("per", 40);
        set("shen_type", 1);
	set("str", 50);
	set("int", 50);
	set("con", 50);
	set("dex", 50);
	set("max_qi", 62000);
	set("max_jing", 6000);
	set("eff_jingli", 9000);
	set("neili", 62000);
	set("max_neili", 62000);
	set("jiali", 250);
	set("combat_exp", 26400000);


			set_skill("force", 950);
			set_skill("beiming-shengong", 950);
			set_skill("dodge", 950);
			set_skill("parry", 950);
			set_skill("lingbo-weibu", 950);
			set_skill("hand", 950);
			set_skill("strike", 950);
			set_skill("zhemei-shou", 950);
			set_skill("liuyang-zhang", 950);
			map_skill("force","beiming-shengong");
			map_skill("dodge","lingbo-weibu");
			map_skill("parry","zhemei-shou");
			
			map_skill("hand","zhemei-shou");
			

			prepare_skill("hand", "zhemei-shou");
			prepare_skill("strike", "liuyang-zhang");			

        setup();
	carry_object(ARMOR_D("cloth"))->wear();
	carry_object(ARMOR_D("shoes"))->wear();


}

void init()
{
	object ob = this_player();
	add_action("do_ketou","ketou");


	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {

		if (ob->query("xiaoyao/zhenlong/pass"))
		{
		command("nod "+ob->query("id"));
		remove_call_out("chenggong");
	    call_out("chenggong", 3, ob);		
		}
		else
		{
		remove_call_out("shibai");
	    call_out("shibai", 3, ob);
		}
	}
}


void shibai(object ob)
{
	command("sigh");
	command("say 你便去罢！");
	ob->move("/d/leigushan/yabiqian");
}

void chenggong(object ob)
{
	command("say 你能解破我的棋局，聪明才智，自是非同小可，但相貌如此，却终究不行，难，难，难！唉，难，难，难！");
	command("look "+ob->query("id"));
	command("say 既是天意如此，你闭了眼睛，竟误打误撞的将我这棋局解开，足见福缘深厚，或能办我大事，亦未可知。好，好，乖孩子，你跪下磕头罢！");
}

int do_ketou(string arg)
{
	object ob = this_player();
if ( ! arg ) return 0;
if ( arg == "wuyazi" )
{
	message_vision("$N恭敬的跪倒，双膝及地，恭恭敬敬向无崖子磕了九个响头. \n", ob);
	remove_call_out("shoutu");
	call_out("shoutu", 0, ob);
	return 1;
}

}

void shoutu(object ob)
{
	
	 mapping skl = ob->query_skills();	
     string *sk;	
     int i;		
 	 sk = keys(skl);
     i = sizeof(sk);	 
	 
	 
	  while (i--) {
        if (		
		 sk[i] == "xiantian-gong" || sk[i] == "tianmo-gong" || sk[i] == "bahuang-gong" 
        || sk[i] == "yunu-xinjing"|| sk[i] == "huashan-qigong"|| sk[i] == "zixia-gong"|| sk[i] == "yinyun-ziqi"|| sk[i] == "bihai-chaosheng"
        || sk[i] == "hanbing-zhenqi"|| sk[i] == "longxiang-boruo"|| sk[i] == "huntian-qigong"|| sk[i] == "xuantian-wuji"|| sk[i] == "guiyuan-tunafa"
        || sk[i] == "yijin-jing"|| sk[i] == "qiantian-yiyang"|| sk[i] == "kurong-changong"|| sk[i] == "linji-zhuang"|| sk[i] == "huagong-dafa"||sk[i] == "baduan-jin" 
        || sk[i] == "shenyuan-gong"|| sk[i] == "shenghuo-shengong" || sk[i] == "dulong-dafa" || sk[i] == "hamagong"  || sk[i] == "xuedao-jing" ) 
		 {		   
		   ob->map_skill("force");
           ob->delete_skill(sk[i]);	//放弃特殊内功	   
           message_vision(HIY"$N只觉全身软洋洋地，便如泡在一大缸温水之中一般，周身毛孔之中，似乎都有热气冒出，说不出的舒畅。\n"NOR,ob);	
           message_vision(HIY"无涯子放开$N手腕，笑道：“行啦，我已用本门‘北冥神功’，将你的" + to_chinese(sk[i]) +"都化去啦。\n"NOR,ob);              
		  }
       continue; 		 	  
      }
	  
	  message_vision(HIY"无涯子哈哈一笑，突然身形拔起，在半空中一个筋斗，头上所戴方巾飞入屋角，左足在屋梁上一撑，头下脚上的倒落下来，脑袋顶在$N的头顶，两人天灵盖和天灵盖相接\n"NOR,ob);	
	  ob->delete("family");
	  
	  //这里不要拜师了学艺，因为已经无涯子是师傅了，其他武功通过解密获得
	   if (ob->query_skill("xixing-dafa")) {
		   command("say 哦？你似乎学过北冥神功的皮毛，但是并不完整，这对你有极大危害，我还是帮你化去吧。");
		   ob->map_skill("force");
		   ob->delete_skill("xixing-dafa");
	   }
		   
	  if (ob->query_skill("beiming-shengong")) command("say 哦？你居然已经学会‘北冥神功’，那倒省事不少。");
	  else ob->set_skill("beiming-shengong",220);
	  ob->set_skill("liuyang-zhang",300);	  
	  ob->set_skill("zhemei-shou",300);
	  ob->set_skill("lingbo-weibu",300);
	  ob->set_skill("ruyi-dao",300);
	  ob->create_family("逍遥派",2, "弟子");
	  ob->set("family/master_name","无涯子");     
	//"他说话之间，虚竹只觉全身软洋洋地，便如泡在一大缸温水之中一般，周身毛孔之中，似乎都有热气冒出，说不出的舒畅。过得片刻，那老人放开他手腕，笑道：“行啦，我已用本门‘北冥神功’，将你的少林内力都化去啦！”"
	//"那人哈哈一笑，突然身形拔起，在半空中一个筋斗，头上所戴方巾飞入屋角，左足在屋梁上一撑，头下脚上的倒落下来，脑袋顶在虚竹的头顶，两人天灵盖和天灵盖相接"
	//"这里有一幅图，上面绘的是我昔年大享清福之处，那是在大理国无量山中，你寻到我所藏武学典籍的所在，依法修习"
	command("say 好！好！我的乖徒儿！我逆运‘北冥神功’，已将七十余年的修为，尽数注入了你的体中");
	command("say 这里有一幅图，上面绘的是我昔年大享清福之处，那是在大理国无量山中，你寻到我所藏武学典籍的所在，依法修习。");
	ob->set("title",HBBLU"无涯子"NOR+HIY"关门弟子"NOR);
	ob->set("mytitle/quest/zhenlong",HBBLU"无涯子"NOR+HIY"关门弟子"NOR);
	//ob->set("quest/天龙八部/北冥神功/step2",1);

}
