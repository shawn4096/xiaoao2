// Modify By River 98/08/29
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", HIR"练功房"NOR);
	set("long", @LONG
里面又是一室，却和先一间处处对称，而又处处相反，乃是后窄前宽，西圆东
角，室顶也是刻满了无数符号。此处乃是古墓派祖师林朝英的武功之秘。
LONG
     );      

	setup();
}

void init()
{
	add_action("do_xiulian", "xiulian");
	add_action("do_yanxi", "yanxi");
	add_action("do_tui","tui");
	add_action("do_guanwu", "guanwu");
}

int do_yanxi(string arg)
{
	mapping fam;
	object me = this_player();
	
	if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
		return notify_fail("你不是古墓传人，如何能领悟古墓武功？\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");

	if ((int)me->query_skill("literate", 1) < 10)
		return notify_fail("你斗字不识,领悟个啥? \n");            

	if (arg == "top"){
		if (me->query("gender") != "女性")
			return notify_fail("玉女素心剑呈阴柔之气，只适合女子练习。\n");
		if ((int)me->query_skill("sword", 1) < 10)
			return notify_fail("你基本剑法太差，无法研习玉女素心剑。\n"); 
		if (me->query_skill("yunu-jianfa", 1) >= 1)
			return notify_fail("你已经学会玉女素心剑，自己好好练吧。\n");      
		message_vision("$N仰视室顶的图纹，心中揣摩玉女素心剑的精妙之处。\n", me);
		me->receive_damage("jing", 5);
		me->receive_damage("jingli",15);
		me->improve_skill("yunu-jianfa", 2);
		return 1;
	}
	return 0;
}

int do_xiulian(string arg)
{
	mapping fam;
	object me = this_player();

	if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
		return notify_fail("你不是古墓传人，如何能领悟古墓武功？\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");          

	if (me->query("jing") < 40)
		return notify_fail("你精力不能集中,去稍作歇息吧. \n");

	if ((int)me->query_skill("literate", 1) < 10)
		return notify_fail("你斗字不识,领悟个啥? \n");

	if (arg == "backwall"){
		write("你抡掌劈向后方窄窄的石壁，蓬一声被震退数步，手臂一阵酸麻。\n");
		if (me->query_skill("strike", 1) < 51)
			return notify_fail("你看了半天只觉莫测高深，什么也没有学会。\n");
		if (me->query_skill("strike", 1) > 100)
			return notify_fail("你掌力雄浑，不该再死练蛮力了。\n");          
		me->receive_damage("jing", 15 + random(20));
		me->improve_skill("strike", (int)(me->query_int()/2)+(int)(me->query_skill("strike")/4));
		return 1;
	}
	if (arg == "frontwall"){
		write("你挥拳直击弧型前壁，石粉四溅,你也被自己的猛劲震退数步。\n");
		if (me->query_skill("cuff", 1) < 51)
			return notify_fail("你看了半天只觉莫测高深，什么也没有学会。\n");
		if (me->query_skill("cuff", 1) > 100)
			return notify_fail("你拳力已刚猛无比，却无甚招数。\n");
		me->receive_damage("jing",15 + random(20));
		me->improve_skill("cuff", (int)(me->query_int()/2)+(int)(me->query_skill("cuff",1)/ 4));
		return 1;
	}
	if (arg == "westwall"){
		write("你绕西面石壁踏着剑步，用心揣摩壁上剑法精髓。\n");
		if (me->query_skill("sword", 1) < 51)
			return notify_fail("你看了半天只觉莫测高深，什么也没有学会。\n");
		if (me->query_skill("sword", 1) > 100)
			return notify_fail("你对石壁上所述剑法已全然掌握,无须再费力了. \n");
		me->receive_damage("jing", 15 + random(20));
		me->improve_skill("sword", (int)(me->query_int()/2)+(int)(me->query_skill("sword", 1)/4) );
		return 1;
	}
	if (arg == "eastwall"){
		write("你虚拈手指,对着东面的三角形石壁,细心操练暗器的收发手势. \n");
		if (me->query_skill("throwing", 1) < 51)
			return notify_fail("你看了半天只觉莫测高深，什么也没有学会。\n");
		if (me->query_skill("throwing", 1) > 100 )
			return notify_fail("你暗器收发随心,再不能提高于此. \n");
		me->receive_damage("jing", 15 + random(20));
		me->improve_skill("throwing", (int)(me->query_int()/2)+(int)(me->query_skill("throwing", 1)/4 ));
		return 1;
	}
	return 0;
}

int do_tui(string arg)
{          
	object me=this_player();
	
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");
	if ( arg == "westwall"){  
		message_vision(YEL"$N伸手到半圆的弧底推了几下，一块大石缓缓移开，现出一扇洞门。\n"NOR,me);
		set("exits/out", __DIR__"gmlg2");            
		remove_call_out("close");
		call_out("close", 5, this_object());    
		return 1;
	}
	return notify_fail("你要推什么？\n");
}

void close(object room)
{
	message("vision",HIY"大石慢慢退回了原位，又挡住了出口。\n"NOR, room);
	room->delete("exits/out");
}

int do_guanwu(string arg)
{
	mapping fam;
	object me = this_player();
	if (!arg) return notify_fail("你要观悟什么？\n");
	
	if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
		return notify_fail("你不是古墓传人，如何能领悟古墓武功？\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");

	if ((int)me->query_skill("literate", 1) < 200)
		return notify_fail("你的literate不足200,根本就看不懂，你观悟个啥? \n");            
	if (me->query_temp("quest/gumu/gwml"))
		return notify_fail("你正在观悟这两招的奥秘，不能分心二用? \n");  
	if (arg == "top"){
		if (me->query("gender") != "女性")
			return notify_fail("玉女素心剑呈阴柔之气，只适合女子练习。\n");
		if ((int)me->query_skill("sword", 1) < 200)
			return notify_fail("你基本剑法太差，不足200，无法研习玉女素心剑。\n"); 
		if (time()-me->query("quest/gumu/ynjf/mulan/time")<86400)
			return notify_fail("你来的也太勤快了。\n");      
		if (me->query("quest/gumu/ynjf/mulan/pass"))
			return notify_fail("你已经学会玉女素心剑和木兰回射的融合，去征战江湖去吧。\n");      
		message_vision("$N仰视室顶的剑势，心中揣摩玉女素心剑的精妙之处。\n", me);
		message_vision(HIC"$N忽然见到一个奇怪的招式，玉女剑法和木兰回射居然可以融合一起使用！\n"NOR, me);
		message_vision(HIY"$N抬起头来，仔细揣摩这两个连招的奥妙，一时间不禁入神！\n"NOR,me);
		me->set_temp("quest/gumu/gwml",1);
		//remove_call_out("guanwu_mulan");
		call_out("guanwu_mulan",1,me);
		return 1;
	}
	return 0;
}


int guanwu_mulan(object me)
{
	int i,j;
	
	if(me->query_temp("guanwu_ml")<(10+random(5)))
    { 
	  me->add_temp("guanwu_ml",1);
      if(random(2)) tell_object(me,HIG"\n一招木兰回射，但如何能衔接玉女剑呢？你不禁陷入深思，不得其解，\n"NOR);
             else tell_object(me,HIY"\n先出玉女剑然后衔接木兰回射？...。突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  //remove_call_out("guanwu_ml");
	  call_out("guanwu_mulan",3+random(3), me);
	  return 0;
	}
   else
   {  
	  me->delete_temp("guanwu_ml");
      j = 15;
      if(me->query("m-card-vip")) j =  12;
      if(me->query("y-card-vip")) j =  10;
      if(me->query("buyvip"))     j =  8;
	 // if (me->query("gender")=="女性")
	    // j=j-2;
	 
	  i= random(j);

     if(i=4 
		&& random(me->query("kar"))>25)
	 {
		tell_object(me,HIM"\n你按照古墓中屋顶玉女剑法精要的指点，又有所了解，玉女剑法的奥妙似乎有些得心应手。\n"NOR);
        
		tell_object(me,HIY"\n你历尽千辛万苦，终于得偿所愿，将玉女剑法中两大杀招领会贯通。\n"NOR);
       	
		
		me->set("quest/gumu/ynjf/mulan/pass",1);
		me->set("quest/gumu/ynjf/mulan/time",time());
		me->start_busy(1);
		me->delete_temp("quest/gumu/gwml");
		log_file("quest/ynjfmulan", sprintf("%8s(%8s) 失败%d次后，领悟玉女剑法两大杀招的融合绝技第一段。i取值：%d|经验：%d。\n", me->query("name"),me->query("id"), me->query("quest/gumu/ynjf/mulan/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gumu/ynjf/mulan/fail",1);
		
		tell_object(me,HIY"你对照墙壁上的招式演练了玉女剑法融合的奥秘，始终全然不得要领。\n\n"NOR);
		tell_object(me,HIG"\n解密玉女剑法两大杀招融合失败。再接再厉！\n\n"NOR);
		me->start_busy(1);
		me->add("quest/gumu/ynjf/mulan/fail",1);
		me->set("quest/gumu/ynjf/mulan/time",time());
		me->delete_temp("quest/gumu/gwml");
		log_file("quest/ynjfmulan", sprintf("%8s(%8s) 玉女剑法两大杀招解密失败%d次。i取值：%d|经验：%d。\n", me->query("name"),me->query("id"),me->query("quest/gumu/ynjf/mulan/fail"),i,me->query("combat_exp")) );
	  }
	return 1; 
  }

}
