// youtanzhi.c 游坦之
// Update by sohu@xojh
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;

string ask_azi();
string ask_bingcan();
string ask_duzhang();

void create()
{
        set_name("游坦之", ({ "you tanzhi", "you", "tanzhi"}));
        set("nickname", "铁丑");
        set("long", "一个带着铁头面具的怪人，整个脸都被一个铁套子套住，看不出是何人。\n");
        set("gender", "男性");
        set("age", 32);
        set("attitude", "peaceful");
        //set("env/wimpy", 100);
//	set("apprentice", 1);

        set("str", 35);
        set("int", 20);
        set("per", 10);
        set("con", 35);
        set("dex", 24);

        set("max_qi", 39000);
		set("qi",39000);
        set("max_jing", 6200);
		set("jing", 6200);
		set("max_jingli",7000);
		set("eff_jingli", 7000);
		set("quest/xx/csz/bingcan/pass",1);
		//set("jingli", 5000);
		set("max_neili",50000);
		set("neili",50000);
        set("jiali", 250);
        set("combat_exp", 15200000);
        set("shen", -2000000);

        set_skill("force", 550);
        set_skill("huagong-dafa", 550);
        set_skill("dodge", 450);
        set_skill("zhaixingshu", 450);
        set_skill("strike", 450);
        set_skill("chousui-zhang", 520);
        set_skill("parry", 500);
        set_skill("poison", 220);
        set_skill("literate", 180);
        set_skill("claw", 450);
        set_skill("sanyin-zhua", 450);

        map_skill("claw", "sanyin-zhua");
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixingshu");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");
        prepare_skill("strike", "chousui-zhang");

        create_family("星宿派", 2, "弟子");

        set("inquiry", ([
             	"阿紫" : (: ask_azi:),
				"冰蚕" : (: ask_bingcan:),
				"冰蚕毒掌" : (: ask_duzhang:),
        ]));
		set("chat_chance_combat", 80);
		set("chat_msg_combat", ({
			(: exert_function, "huadu" :),
			(: perform_action, "strike.chousui" :),
			(: perform_action, "strike.bingcan" :),
			(: perform_action, "strike.huoqiang" :),
			(: perform_action, "claw.wugong" :),
		}));
        setup();
		carry_object(ARMOR_D("baihu-qiu"))->wear();
}


string ask_azi()
{
	if (!this_player()->query_temp("bingcan/asktietou"))
	{
		command("say 铁头是我，你来打听这个干啥？\n");
		return "这人傻不愣登的一看就是傻子\n";
	}
	command("say 既然是阿紫姑娘让你来的，你来找我做什么!\n");
	command("sigh ");
	command("say 我本将心照明月，奈何明月照沟渠！\n");
	this_player()->set_temp("bingcan/askazi",1);
	return "我晓得了，看来是阿紫姑娘找你来又要让我去找那冰蚕去了！\n";
}
string ask_bingcan()
{
	if (!this_player()->query_temp("bingcan/askazi"))
	{
		command("say 我不认识你，你来打听这个干啥？\n");
		return "一看就是真是二货\n";
	}
	command("say 这冰蚕我也不知道在哪儿找到，上次那个冰蚕是我从少林寺慧净和尚哪儿偷来的！\n");
	command("blush ");
	command("say 你如果想打听这个信息，最好是去少林寻找慧净和尚询问！\n");
	this_player()->set_temp("bingcan/askbingcan",1);
	return "慧净和尚在少林寺浇菜园子，你去寻找看看！\n";
}
string ask_duzhang()
{
	object me=this_player();
	if (me->is_busy())
	{
		return "你正在忙碌中！\n";
	}
	if (!me->query("quest/xx/csz/bingcan/over"))
	{
		command("heng "+me->query("id"));
		command("consider ");
		command("say 你连神足经都打不通，我即便告诉你如何修炼这冰蚕毒掌，你也会被冻死！\n");
		command("say 只要你打通神足经脉，能抵抗初步的寒毒，再来我处。\n");
		return "哼！";
	}
	if (me->query_skill("huagong-dafa",1)<450)
	{
		command("say 你的化功大法功力太弱，不足450，抵抗不住这寒毒侵袭\n");
		return "哼！";
	}
	if (me->query("con")<40)
	{
		command("say 你的先天根骨太弱，不足40，抵抗不住这寒毒侵袭\n");
		return "哼！";
	}
	
	if (me->query_skill("poison",1)<200)
	{
		command("say 你的毒计不足200,太弱，抵抗不住这寒毒侵袭\n");
		return "哼！";
	}
	if (time()-me->query("quest/xx/csz/bingcan/time")<86400)
	{
		command("say 你来的太频繁了，吸毒过多，对身体不宜。\n");
		return "哼！";
	}
	if (me->query("quest/xx/csz/bingcan/pass"))
	{
		me->set("title",HBWHT+HIG"冰蚕毒掌真传"NOR);
		me->set("mytitle/quest/bingcan2title",HBWHT+HIG"冰蚕毒掌真传"NOR);
		command("say 你已经解开这冰蚕毒掌的奥秘了，开什么玩笑\n");
		return "哼！";
	}
	message_vision(HIC"$n对$N笑道，你上次给我的那条冰蚕，我已经放到瓦瓮中了，你自己去修炼吧。说完就交给$N一个大瓦瓮。\n"NOR,me,this_object());
	command("say 这冰蚕毒其实没什么大不了的，既然你已经打通了神足经经脉，能抵抗这初级寒毒，我就告诉你这修成冰蚕毒掌的奥秘吧!\n");
	command("say 如此这般这般。。。。");
	command("whisper "+me->query("id"));
	me->start_busy(99);
	remove_call_out("thinking");
	call_out("thinking",1,me);
	return "冰蚕毒掌不弱于人，即便丁春秋和乔峰，我也不惧！\n";
}

int thinking(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("bingcan_ask")<(10+random(3)))
    { 
	  me->add_temp("bingcan_ask",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才游坦之告诉你的心得体会...\n"NOR);
             else tell_object(me,HIW"\n突然间，一股寒毒沿着你的经脉如冰箭一般穿行..\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("bingcan_ask");
      total = me->query("con");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  16;
      if(me->query("buyvip"))     j =  12;
	  i= random(j);
 
 
	  if( i<3 
		  && random(total)>40
		  && random(me->query("kar"))>28)
	  {
		tell_object(me,HIB"\n你按照游坦之的指点，对冰蚕毒掌的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIW"你按照游坦之所言，内息起自“长强穴”，随后自腰俞、阳关、命门、悬枢\n+"+
"诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、\n"+
"灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
		tell_object(me,HBGRN+HIW"\n你历尽千辛万苦，终于得偿所愿，将冰蚕毒掌融汇贯通。\n恭喜你！笑傲江湖去吧!\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/xx/csz/bingcan/pass",1);
		me->set("title",HBWHT+HIG"冰蚕毒掌真传"NOR);
		me->set("mytitle/quest/bingcan2title",HBWHT+HIG"冰蚕毒掌真传"NOR);
		me->start_busy(1);
		log_file("quest/xxbingcan", sprintf("%8s(%8s) 失败%d次后，彻底领悟冰蚕毒掌的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/xx/csz/bingcan/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/xx/csz/bingcan/fail",1);
		me->set("quest/xx/csz/bingcan/time",time());
		command("heng ");
		tell_object(me,HBBLU+HIW"\n你听了游坦之的指点，虽然听见了冰蚕毒掌的奥秘，可是对冰蚕毒掌功的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/xxbingcan", sprintf("%8s(%8s) 冰蚕毒掌解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/xx/csz/bingcan/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}
