//wzfeng 98 10 13
//chuanfu.c
inherit NPC;
#include <ansi.h>

int ask_chuhai();
void create()
{
	set_name("船夫",({ "chuan fu","chuan","fu"}));
	set("long", "他是一名老船夫，专门负责发派神龙岛去中原的船只。\n");
	set("gender", "男性");
	set("attitude", "friendly");
	set("no_get_from", 1);
	set("unique", 1);
        set("age", 55);

	    set("per",15);
        set("shen", 0);
        set("str", 130);
        set("int", 125);
        set("con", 127);
        set("dex", 129);

        set("max_qi", 50000); 
        set("max_jing", 30000);
        set("neili", 50000);
        set("max_neili", 50000);
        set("jingli", 20000);
        set("eff_jingli", 20000);
        set("jiali", 10);
        set_skill("unarmed", 800);
        set_skill("dodge", 800);
		set_skill("taiji-quan",800);
        set_skill("cuff", 800);
		map_skill("cuff","taiji-quan");
        prepare_skill("cuff","taiji-quan");
        
	    set("combat_exp", 50000000);
    	create_family("神龙教",3, "弟子");

        set("inquiry", ([
		"chuhai" : (: ask_chuhai :),
		"出海" : (: ask_chuhai :),
	]));
        
	setup();
}

void init()
{
	::init();
	if(!objectp(find_object("/d/sld/md1"))) {
		load_object("/d/sld/md1");   
	}
}

int ask_chuhai()
{
	command("say 岛主有令，必须有通行令牌我才能发派船只,不然任何人不得擅自离岛！！！");
	return 1;
}

int accept_object(object who, object ob)
{
	if( ((string)ob->query("id") != "ling pai") || ob->query("sld") !=1 )
		return 0;
    //if (this_player()->query_temp("sld/givelp"))
         //return notify_fail(CYN"船夫对你说道：「你已经给了令牌，还是等会再说吧。」\n"NOR);
	//离开原位失效
	if ( file_name(environment(this_object())) != this_object()->query("startroom")) 
		return notify_fail(CYN"船夫对你说道：「还是等我回到神龙岛再说吧。」\n"NOR);
//等待时间5
	    who->start_busy(5);
		
		//this_player()->add_temp("sld/givelp",1);
		//this_player()->move("/d/sld/haitan");
	    remove_call_out("go_chuan");
        
		call_out("go_chuan", 0,who,ob);
        
	    call_out("destructing", 0, ob); //取消令牌
        
	    return 1;
}

void destructing(object ob)
{
	destruct(ob);
}

void go_chuan(object me,object ob)
{
	object fchuan;	
	int i;
	string *fcname=({ __DIR__"obj/fc1",__DIR__"obj/fc2",__DIR__"obj/fc3" ,__DIR__"obj/fc4",__DIR__"obj/fc5",__DIR__"obj/fc6",__DIR__"obj/fc7",__DIR__"obj/fc8",__DIR__"obj/fc9", });
//寻找空闲的船只
	for(i=0;i<sizeof(fcname);i++){
		if(!objectp(fchuan=find_object(fcname[i])))
			fchuan=load_object(fcname[i]);
		if(fchuan->query_temp("curstatus",1)!="run")
		   break;
	}
	//船不够等待
	if(i>=sizeof(fcname)){
		command("say 现在没船，请等一会吧。\n");
		remove_call_out("go_chuan");
		call_out("go_chuan", 2,me); 
		return;
	}
	command("say 既然有神龙教通行令牌，我这就带你上船！");
	if(fchuan->query_temp("curstatus",1) == "ready") {
		message_vision("\n只见$N向海上打了个手势，似乎是什么暗号。\n",this_object());
		message_vision("不一会儿，一艘小帆船从海上缓缓驶来。\n\n", this_object());
		message_vision(CYN"$N对$n说道：「海上风大，一切小心！」\n"NOR, this_object(),me);
		fchuan->set_temp("curstatus","ready2");
	}
	message_vision("$N轻轻一跃，上了小船。\n",me);
	me->move(fcname[i]);	
	tell_room(environment(me), me->name() + "跃上船来。\n", ({ me }));
	
		//call_out("destructing", 0, ob); 
	//me->delete_temp("sld/givelp");
}
