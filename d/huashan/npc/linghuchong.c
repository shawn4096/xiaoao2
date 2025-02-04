// NPC: /d/huashan/npc/linghuchong.c
// Date: Look 99/03/25
// Modified by Numa@JH 2000 For 黑木崖Job
// Lklv Modify at 2001.10.18
// update by lsxk@hsbbs 增加华山剑法苍松迎客 quest  2007/7/29

#include <ansi.h>
inherit NPC;
#include "skill1.h"

string ask_chongling();
string ask_ylj1();
string ask_ylj2();
string ask_ylj3();
int ask_ryy();
int ask_heimu();
int ask_follow();
int ask_cangsong();

void create()
{
        set_name("令狐冲", ({ "linghu chong", "linghu", "chong" }));
        set("nickname", "大师兄");
        set("long",
"令弧冲身材较瘦，长的浓眉阔眼，气宇暄昂，他在\n"
"同门中排行老大，是华山派年轻一代中的顶尖好手。\n"
"如果掌门人岳不群不在，就由他执掌日常事物。\n");
        set("gender", "男性");
        set("age", 28);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 50);
        set("con", 30);
        set("dex", 30);
        set("unique", 1);

        set("max_qi", 35000);
        set("max_jing", 8000);
        set("neili", 40000);
        set("max_neili", 40000);
        set("eff_jingli", 8000);

        set("jiali", 200);
        set("combat_exp", 9500000);
        set("score", 8000);
        set("startroom","/d/huashan/siguoya");

        set_skill("cuff", 400);
        set_skill("force", 400);
        set_skill("dodge", 400);
        set_skill("parry", 400);
        set_skill("sword", 460);
        set_skill("dugu-jiujian", 460);
        set_skill("huashan-qigong", 400);
        set_skill("poyu-quan", 400);
        set_skill("huashan-jianfa", 450);
        set_skill("huashan-shenfa",400);
        set_skill("zhengqi-jue", 200);
        set_skill("chongling-jian", 450);

        map_skill("force", "huashan-qigong");
        map_skill("cuff", "poyu-quan");
        map_skill("dodge", "huashan-shenfa");
        map_skill("parry", "dugu-jiujian");
        map_skill("sword", "dugu-jiujian");

        prepare_skill("cuff", "poyu-quan");

        create_family("华山派", 14, "弟子");
      
        set("chat_chance", 25);
        set("chat_chance_combat",90);
	    set("chat_msg_combat", ({
		    (: perform_action, "sword.poqi" :),
		    (: perform_action, "sword.zongjue" :),
		    (: exert_function, "yujianshi" :),
			(: perform_action, "sword.pozhao" :),
		   // (: perform_action, "sword.cangsong" :),
		//(: perform_action, "sword.shijiushi" :),
		
	}));

        set("inquiry", ([
                "风清扬" : "唉，已经很久没有见到他老人家了。你问这干嘛？\n",
                "岳灵珊" : "你找小师妹有什么事啊？\n",
                "仪琳" : "遇见尼姑，逢赌必输\n",
                "紫霞秘籍" : "那是我们华山的内功秘籍，我没有看过。\n",
                "宝剑" : (: ask_ylj3 :),
                "墨纹玄铁" : (: ask_ylj2 :),
                "冲灵剑法" : (: ask_chongling :),
                "遇见尼姑，逢赌必输" : (: ask_ylj1 :),
                 "苍松迎客" : (: ask_cangsong :),
// add here for ask
                
				"任盈盈" : (: ask_ryy :),
                "黑木令" : (: ask_heimu :),
                "跟我走" : (: ask_follow :),
        ]));
        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}
//令狐冲和盈盈相见

void init()
{
	object ob;
	::init();
	ob = this_player();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	
	
	me=this_player();
	if(!me) return;
   
	if (!me->query_temp("hostage/passed_l")) return;	
	
	if ( file_name(environment(this_object())) != "/d/changan/xiaoshe") return;
    
	
    if(present("ren yingying",environment(me))){
		command("chat* hug ren yingying");
		command("hug ren yingying");
		command("say 盈盈，我终于又见到你了！\n");		
        command("thank " + me->query("id"));
		//this_object()->delete_leader(me);
		command("follow none");
		//this_object()->move("/d/huashan");
		return ;
	}
	

}


int ask_cangsong()
{
    mapping fam;
    object me = this_player();
    fam = me->query("family");

    if (!fam || fam["family_name"] !="华山派"){
        command("say 这位" + RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？");
        return  1;
    }

    if (me->query("quest/huashan")!="气宗"){
 
	    command("say 我华山派正宗武学乃以气驭剑，在下看这位" + RANK_D->query_respect(me)+"修炼之道乃剑重于气，恐难领会这「苍松迎客」剑招精妙之处！");
        return 1;
    }

   
	if ((int)me->query_skill("huashan-jianfa",1)<180){
 
		command("say 我华山派剑法乃须循序渐进练习方有成效，这位" + RANK_D->query_respect(me)+"你的华山剑法尚不够纯熟，恐难领会这「苍松迎客」剑招精妙之处！");
        return 1;
    }
    if ((int)me->query("combat_exp")<400000){
        command("say 我华山派剑法注重平时练习，积累经验，这位" + RANK_D->query_respect(me)+"实战经验实在太浅，恐难领会这「苍松迎客」剑招精妙之处！");
        return 1;
    }
    if (me->query_condition("job_busy")){
        command("say 这位" + RANK_D->query_respect(me)+"现在这么忙，难道还有时间去领会「苍松迎客」这么精妙的剑招吗？");
        return 1;
    }
    if (me->query("quest/hsjf/cangsong")=="pass"){
        command("say 这位"+ RANK_D->query_respect(me)+"不是已经学会了么？难道又忘了？");
        command("admire " + me->query("id"));
        return 1;
    }
    if ((int)me->query("quest/hsjf/cs_time")+86400 > time()){
        command("shake "+ me->query("id"));
        command("say 你还是再多多花些时间来思考本门的武功吧！");
        return 1;
    }
    if (me->query_temp("quest/hsjf/cangsong/asked")){
        command("? " + me->query("id"));
        return 1;
    }
    command("haha");
    command("say 不错，五岳剑派各派剑法均各有特色，我华山派剑法之绝，一是我华山紫霞神功，二乃剑招轻盈灵动，变化无方！");
    command("say "+strip(me->query("name"))+"，你在我华山派习武也有不少日子了，可知道我华山剑法的精要是什么吗？");
    me->set_temp("quest/hsjf/cangsong/asked",1);
    add_action("do_answer","answer");
    return 1;
}


int do_answer(string arg)
{
    object me, ob, cs_npc;
    int i;

    me = this_player();
    ob = this_object();

    if(!objectp(me)) return 1;

    if(!me->query_temp("quest/hsjf/cangsong/asked")) return 0;

    if(!arg) return notify_fail("你想回答什么?\n");

    if(arg!="以气驭剑" && (int)me->query_temp("quest/hsjf/cs_answer_err") < 2){
        me->add_temp("quest/hsjf/cs_answer_err",1);
        command("shake " + me->query("id"));
        command("say 你再仔细想想。");
        return 1;
    }
    else if(arg!="以气驭剑" && (int)me->query_temp("quest/hsjf/cs_answer_err") >= 2){
        command("sigh " + me->query("id"));
        command("say 看来你对本派武功的认知尚浅，还需多多努力才是。这位"+ RANK_D->query_respect(me)+"还是请回吧！");
        me->set("quest/hsjf/cs_time",time());
        me->set("quest/hsjf/cangsong","fail");
        me->delete_temp("quest/hsjf/cs_answer_err");
        me->delete_temp("quest/hsjf/cangsong/asked");
        return 1;
    }
    command("pat " + me->query("id"));
    command("say 不错不错，正是如此，此招「苍松迎客」如能巧运灵活变招，再加上剑招上运紫霞神功内劲到妙处，威力绝不亚于当世任何一门武功绝招！");
    command("say 光说还是无法领会，这样，我听说有一伙恶人正欲去福州城作恶，你快去把他们都铲除了!");
    command("say 一来去惩恶扬善，二来领会下这「苍松迎客」剑招的精妙之处！切记，要多多练习使用才能有机会融会贯通！");
    //降低难度，npc弱化
	for(i=0;i<3;i++){
        cs_npc = new(__DIR__"cs_npc");
        cs_npc->set("cs_kill_id",me->query("id"));
        cs_npc->move("/d/fuzhou/zhongxin");
    }
    me->set("quest/hsjf/cs_time",time());
    me->set("quest/hsjf/cangsong","start_kill");
    me->delete_temp("quest/hsjf/cs_answer_err");
    me->delete_temp("quest/hsjf/cangsong/asked");
    return 1;
}

string ask_chongling()
{
        mapping fam;
        object me;
        me = this_player();
        fam = me->query("family");
	if (!fam || fam["family_name"] !="华山派")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";
	if (!me->query("hs/getchongling"))
		return "冲灵剑法？那是我和小师妹在朝阳峰舞剑时所创啊。";
	if ((int)me->query_skill("chongling-jian", 1) > 60 )
		return "冲灵剑法贵在独创，你还是自己领悟去吧。\n";
	if ((int)me->query("jingli", 1) < 100 )
		return "你现在身体状况太差了，你无法领悟冲灵剑法的绝妙之处。\n";
	if ((int)me->query("jing", 1) < 100 )
		return "你现在身体状况太差了，你无法领悟冲灵剑法的绝妙之处。\n";
	me->improve_skill("chongling-jian", 20);
	me->receive_damage("jingli",30);
	me->receive_damage("jing", 30);
	me->start_busy(3);
	tell_object(me, HIC"你不由自主跟着令狐冲比划着，对剑法的造诣又深了一层。\n"NOR);
	return  "好吧，既然你问起我冲灵剑法，我就告诉你一次。\n" ;
}

string ask_ylj1()
{
        object me;
        me = this_player();
        command("haha "+me->query("id"));
        me->set_temp("ylj/step1",1);
        return "兄台也知道这件事？这是当初兄弟我为救恒山派的仪琳师\n
妹，向采花大盗田伯光开的玩笑，事后恒山的定静师伯不但没怪我，还送我了\n
一块世间已绝迹的墨纹玄铁，要我用它铸成一把绝世宝剑，行侠处恶，笑傲江\n
湖.....\n";
}

string ask_ylj2()
{
        object me;
        me = this_player();
        if( !me->query_temp("ylj/step1") )
                return "这可是个天大的秘密。\n";
        me->set_temp("ylj/step2",1);
        me->delete_temp("ylj/step1");
        return "说来这墨纹玄铁也是一个宝物，我一直找不到铸剑名师，\n
不想浪费了这块玄铁...。\n";
}

string ask_ylj3()
{
        object me, obj;
        me = this_player();
        if (!me->query_temp("ylj/step2") )
                return "这可是个天大的秘密。\n";
        me->delete_temp("ylj/step2");
        command("look "+me->query("id"));
        if ((int)me->query("shen") > 100000 ){
                obj = unew(__DIR__"obj/xuantie");
                if( clonep(obj) ) {
                        obj->move(me);
                        me->set_temp("ylj/step3",1);
                        return "看兄台一身正气，这块玄铁就送与兄台，望兄台能找到铸\n
剑名师，铸成宝剑，行侠江湖，也不枉费定静师伯的一翻苦心.....\n";
                }
        }
        return "这可是个天大的秘密。\n";
}

//1、ask 盈盈
int ask_ryy()
{
        object ob = this_player();
       /* if (!ob->query_temp("hssb/shouxin"))
        {
			command("angry "+ob->query("id"));
			return 1;
        }*/
        if (ob->query_temp("hostage/job_1") != 2) {
                command("say 我很久没见到她了！");
                command("sigh");
                return 1;
        }
        ob->set_temp("hostage/ask_ling",1);
        command("ah " + ob->query("id"));
        command("say 你见到她了吗？她现在怎么样了？");
        command("say 她的黑木令还在我这里，我正想还给她呢。");
        return 1;
}
//2、 ask 黑木令。

int ask_heimu()
{
        object ob = this_player();
        object me = this_object();

        if (!ob->query_temp("hostage/ask_ling")){
                command("say "+RANK_D->query_respect(ob)+"，这种事不是你该打听的！");
                return 1;
        }

        command("say 想要黑木令？嘿嘿，来咱俩比试比试，赢了我就给你！");
        ob->set_temp("hostage/pass_l",1);
        call_out("do_clone",1,me,ob);
        return 1;
}
//双方比武较量
int accept_fight(object ob)
{
        object me = this_object();

        if ((int)ob->query_temp("hostage/passed_l")){
                command("say 咱们不是比试过了吗？");
                return 0;
        }
        if (me->query("eff_qi") < me->query("max_qi")
        || me->query("qi") < me->query("eff_qi")
        || me->query("neili") < me->query("max_neili")){
        	    me->reincarnate();
                message_vision(CYN"$N对$n说：我还没有休息好，你等一会儿吧。\n"NOR, ob, me);
                return 0;
        }
        if (ob->query_temp("hostage/pass_l")){
                message_vision(CYN"$N对$n说：好吧，那我就同你切搓几招吧，点到为止。\n"NOR, ob, me);
                remove_call_out("checking");
                call_out("checking", 1, me, ob);
                ob->delete_temp("hostage/pass_l");
                return 1;
        }
        else return 0;
}
//比较较量检查，必须赢了
int checking(object me, object ob)
{
        int my_max_qi,his_max_qi;
        my_max_qi  = (int)me->query("max_qi");
        his_max_qi = (int)ob->query("max_qi");

        if ( !present(ob, environment()) )
                return 1;
        if (( (int)me->query("qi")*100 / my_max_qi) <= 50 ){
                message_vision(CYN"$N对$n不住地赞叹："+RANK_D->query_respect(ob)+"果然好功夫，你就先带我去任盈盈那里吧。\n"NOR, me, ob);
                ob->set_temp("hostage/passed_l", 1);
                if (me->query("block_msg/all")>0) {
                        me->revive();
                }
                me->reincarnate();
                me->set_leader(ob);
                me->delete("chat_chance");
                me->set("location",1);
                me->set_temp("no_return",1);
                message_vision("$N决定跟随$n一起行动。\n"NOR, me, ob);
                return 1;
        }
        if (( (int)ob->query("qi")*100 / his_max_qi) < 50 ){
                message_vision(CYN"$N看了看$n，说道：你的功夫稀松平常，怎么带我去找任盈盈？\n"NOR, me,ob);
                message_vision("$N急急忙忙离开了。\n",me);
                ob->set_temp("hostage/passno_l", 1);
                me->move(__DIR__"siguoya");
                message_vision("$N急急忙忙走了过来。\n", me);
                return 1;
        }
        if (me->is_fighting()) {
                call_out("checking",1, me, ob);
                return 1;
        }
        return 1;
}

int ask_follow()
{
        object ob = this_object();
        object me = this_player();

        if (!me->query_temp("hostage/passed_l"))
                return 0;
        message_vision(CYN"$n哈哈大笑，对着$N说道：那就走吧！\n"NOR,me,ob);
        ob->set_leader(me);
        message_vision("$n决定跟随$N一起行动。\n"NOR,me,ob);
        ob->delete("chat_chance");
        return 1;
}
//接收东西

int accept_object(object who, object obj)
{
	object me,lh;
	obj =present("letter", who);
	me = this_player();
	lh = this_object();
    	

	if (me->query_temp("yy/songxin")&& obj->query("id")=="letter")
	{
		me->set_temp("hostage/job_1",2);
		me->delete_temp("yy/songxin");
		write(HIY"令狐冲将信拿在手中翻来覆去的看，似乎对你的好感大增。\n"NOR);
		//write(HIC"$N把碧水剑送给了小师妹，百无聊赖之际，伤痛发作，决定还是先回到休息室疗养一番。\n"NOR);
		command("say 盈盈能让你来送信，说明你还不错。\n");
		obj->move(this_object());
		destruct(obj);
		
		
		if (me->query("family/family_name")=="日月神教")	
		{
			command("haha \n");
			command("say 我就和你走一趟吧。\n");
		
             me->set_temp("hostage/passed_l", 1);//直接通过
             lh->set_leader(me);
             lh->delete("chat_chance");
             lh->set("location",1);
             lh->set_temp("no_return",1);
             message_vision("$n决定跟随$N一起行动。\n"NOR,me,lh);       
		}
		
		
		
		return 1;
	}
	else {

    command("say 你瞎折腾什么？");
	return 0;
	}

}
