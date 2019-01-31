#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIM"百花谷"NOR);
        set("long", @LONG
突然间眼前一亮，但觉青青翠谷，点缀着或红或紫、或黄 或白的鲜花。
这一路行来，遍地不是积雪，便是泥泞，此处竟是换 了一个世界。立即有
春暖花开，柳暗花明之境界，风吹过后，一片幽香袭来，令人沉醉。山崖
峭壁旁刻了三个大字“百花谷”，北面是一排三间茅草屋。
LONG                           
        );

        set("exits", ([
				"enter" : __DIR__"maocaowu",
                "south" : __DIR__"huajing3",
        ]));
        set("outdoors", "quanzhen");
        setup();
}

int init()
{
	object me=this_player();
	object yang;
	add_action("do_bishi","bishi");
	if (me->query_temp("quest/shendiao/大雪风陵渡/askyangzhou"))
	{
		if (!objectp(yang=present("yang guo",environment(me))))
		{
			yang=new("d/quanzhen/npc/yang");
			
			 if(!clonep(yang)) {
				 destruct(yang);				 
			 }
			
			yang->move(this_object());
		}
		message_vision(HIY"\n\n杨过冲$N微微一笑，说道，“这就是百花谷，你喊几嗓子老顽童试试，”\n"NOR,me);

		add_action("do_han","han");

	}
}

int do_han(string arg)
{
	object me=this_player();
	object zhou,room,yang;
	if (me->query_temp("quest/shendiao/大雪风陵渡/zhouok",1))
		return notify_fail("还不抓紧时间观悟绝学？\n");
	
	if (!arg ||(arg!="老顽童"&& arg!="周伯通"))
	{
		return notify_fail("空山寂寥，你瞎喊什么？\n");
	}
	
	if (me->query_temp("quest/shendiao/大雪风陵渡/hanzhou")) return notify_fail("周伯通已经来过了，你还喊啥。\n");
		
	
	me->add_busy(3);
	
	if (!objectp(yang=present("yang guo",environment(me))))
	{
		if (!present("yang guo",room))
				{
				    yang=new("d/quanzhen/npc/yang");
					
				}
				yang->move(environment(me));
	}

	if (arg=="老顽童" || arg=="周伯通")
	{
		message_vision(HIY"$N冲山谷中大喊，“老顽童~~~~，我和杨大侠来同你玩了啊？”\n"NOR,me);
		room=load_object("d/quanzhen/maocaowu");
	
		if (!objectp(zhou=present("zhou botong",room)))
		{
			if (!objectp(zhou=present("zhou botong",this_object())))
			{
				if (!present("zhou botong",room))
				{
				    zhou=new("kungfu/class/quanzhen/zhou");
				}
				
			}
			
		}
		zhou->move("d/quanzhen/baihuagu");		
		message_vision(HIC"老顽童伸了个懒腰，从花丛中钻了出来，嘻嘻笑道，“你来做甚”?\n"NOR,me);
		//me->delete_temp("quest/shendiao/大雪风陵渡");
		me->delete_temp("quest/shendiao/大雪风陵渡/askyangzhou");		
		me->set_temp("quest/shendiao/大雪风陵渡/hanzhou",1);
		call_out("do_say1",2+random(3),me,zhou,yang);
	}
	return 1;
}
int do_say1(object me,object zhou,object yang)
{
	message_vision(HIC"$N对$n说道，我这次来是请你去见一个人去，你敢不敢去？\n"NOR,me,zhou);
	zhou->zhou_say1();
	message_vision("\n\n$N对$n说道，难道他二人大祸临头，命在旦夕，你也不肯伸手相救么？？\n",me,zhou);
	zhou->zhou_say2();
	message_vision(HIG"$N说道，“老实跟你说了罢！瑛姑思念你的紧，无论如何要你去跟她 一会。”\n"NOR,me);
	message_vision(HIR"$n立即双手乱摇，说道，“千万别跟我提这事，否则休怪我翻脸无情！”\n"NOR,me,zhou);
	message_vision(HIR"\n\n杨过对$n笑道，若打败了你是不是你就跟我们走了？！”\n"NOR,me,zhou);
	
	zhou->fight_ob(yang);
	yang->fight_ob(zhou);
	call_out("check_fight",1,me);
	return 1;
}

int check_fight(object me)
{
	object zhou,yang;
	yang=present("yang guo",this_object());
	zhou=present("zhou botong",this_object());
	if (!zhou||!yang)
	{
		return notify_fail("核心NPC杨过或周伯通不在现场\n");
	}
	if (objectp(zhou=present("zhou botong",this_object()))&&zhou->is_fighting())
	{
		call_out("check_fight",1,me);
		return 1;
	}
	if (zhou->query_temp("last_damage_from")!=yang)
	{
		return notify_fail("周伯通说道，“不去，不去，就是不去！想让我去，除非杀了我！”\n");
	}
	
	message_vision(HIC"\n$N说道，黯然销魂掌果然了得，打败了我也不去！\n"NOR,zhou,me);
	message_vision(HIY"\n$n说道，$N难道你不想去看看你儿子么？！\n"NOR,zhou,me);
	message_vision(HIC"\n\n\n$N大吃一惊！！儿子！！我的儿子！！在哪儿？快带我去？！\n"NOR,zhou,me);
    //destruct(zhou);
	zhou->move("d/quanzhen/maocaowu");
	me->delete_temp("quest/shendiao/大雪风陵渡/hanzhou");
	me->set_temp("quest/shendiao/大雪风陵渡/zhouok",1);
	
	if (me->query("gender")=="女性") 
	{		
		message_vision(HIY"\n\n$N对$n说道，好了，你是一位女性，现在去找瑛姑去吧，这里没你什么事了！”\n"NOR,yang,me);
		return 1;
	}
    if (me->query("gender")=="男性")
	{
		message_vision(HIY"\n\n$N对$n说道，你要瞧仔细了，要用心观悟"HIR"(guanwu 黯然销魂掌)"HIY",别错失良机！”\n"NOR,yang,me);
		add_action("do_guanwu","guanwu");
		return 1;
	}	
	return 1;
}

int do_guanwu(string arg)
{
	object me=this_player();
	me->start_busy(3);
	if (!arg || arg!="黯然销魂掌")
	{
		return notify_fail("你要观悟什么？\n");
	}
	if (me->query_temp("guanwu_anranzhang"))
	{
		return notify_fail("你正在观悟黯然掌中，稍安勿躁？\n");
	}
	
	if (me->query("gender")!="男性")
	{
		return notify_fail("非纯种男性，无法修习黯然掌？\n");
	}
	if(me->query("quest/anran/pass"))
	{
		return notify_fail("你已经解开此谜题，来消遣老顽童和神雕侠么？");
	}
	if(me->query("quest/anran/fail")>=3 && me->query("registered")<3)
	{
		return notify_fail("已经多次传授，你怎么都还没有领悟,真够笨的！？");
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("quest/anran/time")<86400)
	{	
		return notify_fail("今天先教到这里吧，明天吧。？\n");
	}
	if(me->query_skill("force",1)<450)
	{
		return notify_fail("黯然掌需要深厚的内力，你的基本内功不足450，来此作甚？\n");
	}
	//一定要等到25秒后
	me->set_temp("guanwu_anranzhang",1);
	//call_out("check_fight",25,me);	

	me->set("quest/anran/time",time());
	me->set("quest/anran/combat_exp",me->query("combat_exp")); 
	me->start_busy(999);
	call_out("thinking",1,me);
	
	return 1;
}

int thinking(object me)
{
  int i,j,total;
  object zhou,yang;
  
	yang=present("yang guo",this_object());
	zhou=present("zhou botong",this_object());
  if(!me) return 0;
	
  if(me->query_temp("anran/guanwu")<(3+random(3)))
    { 
	  me->add_temp("anran/guanwu",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才杨过所施展黯然掌的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("anran/guanwu");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  if (me->query("family/family_name")=="古墓派")
	     i=random(j-3);
	  else i= random(j);
 

    if(i<4 && random(me->query("kar"))>25)
	 {
		tell_object(me,HIG"\n你按照杨过的指点，对黯然销魂掌的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIW"你内息起自“长强穴”，随后自腰俞、阳关、命门、悬枢\n+"+
"诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、\n"+
"灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
		tell_object(me,HIY"\n恭喜你！你历尽千辛万苦，终于得偿所愿，习得绝技<<黯然销魂掌>>。\n"NOR);
       	me->set("quest/anran/pass",1);
		me->set("title",HBBLU+HIW"*黯然销魂*"NOR);
		me->set("mytitle/quest/arztitle",HBBLU+HIW"*黯然销魂*"NOR);
		me->start_busy(1);
		log_file("quest/anranzhang", sprintf("%8s(%8s) 失败%d次后，彻底领悟黯然销魂掌的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/arz/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/anran/fail",1);
		me->set("quest/anran/time",time());
		me->delete_temp("guanwu_anranzhang");

		tell_object(me,HIY"\n\n你听了杨过的指点，虽然听见了黯然销魂掌的奥秘，可是对这掌法的真正奥妙全然不得要领。\n\n"NOR);
		tell_object(me,HIG"\n\n希望再接再厉，继续奋斗。\n\n"NOR);
		me->start_busy(1);
		log_file("quest/anranzhang", sprintf("%8s(%8s) 黯然销魂掌解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/arz/fail"),i,me->query("combat_exp")) );
	  }
    	 
  }
  //me->delete_temp("anran");
  me->start_busy(1);
  if (objectp(yang)) {
	 message_vision(HIC"杨过长啸一声，纵身而去。\n"NOR,me);
	 destruct(yang);
  }
  if (objectp(zhou))
  {
	 // destruct(zhou);
	 zhou->move("d/quanzhen/maocaowu");
  }
  
	return 1;
}
