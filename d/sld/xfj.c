// xfj.c
// 仙福居
#include <ansi.h>

inherit ROOM;
void create()
{
	set("short","仙福居");
	set("long",@long
这里是教主夫妇闲暇时休息怡乐之处，有时也用于留宿客人。
北面的书架(shelf)上摆放了一摞摞书籍，皆为各大门派精要，其中
左侧的上半书籍被一些封条封住,旁边一行小字，神龙岛武学精要。
long);
	set("no_fight", 1);
	set("exits",([
          "out" : __DIR__"pt",
]));
	//set("coor/x",490);
	//set("coor/y",430);
	set("book/dujing",1);
	set("book/yaoli",1);
	setup();
}
	    	
void init()
{
	object me=this_player();
	if (me->query_temp("clgf/suok")&& present("shenlong gou",me))
	{
		message_vision(HIC"$N平心静气，做在哪儿，远处山风呼啸，室内一片静谧。\n"NOR,me);
		message_vision(HIY"\n\n\n$N按照洪教主所说的奥义，静静体味(tiwei)。\n"NOR,me);
		me->set_temp("clgf/start1",1);
		me->delete_temp("clgf/suok");
		add_action("do_lw","tiwei");
	}	
	add_action("do_search","search");

}
int do_search(string arg)
{
	object me=this_player();
	
	if (!arg||arg!="shelf")
		return notify_fail("你要领悟什么？\n");
	if (present("shedu jing",me) || present("shenlong yaoli",me))
		return notify_fail("你身上带有此类书籍，不可贪得无厌。\n");
	if (arg=="shelf" && !random(3))
	{
		message_vision("$N撕掉书架上的封条，然后从书架中拿出一本书翻看。\n",me);
		switch (random(2))
		{
			case 0:		
			if (query("book/dujing")>0)
			{
				new("d/sld/obj/shedujing2")->move(me);
				message_vision("$N从书架中拿到一本《蛇毒经(下)》。\n",me);
				this_object()->add("book/dujing",-1);
			}
			break;
			case 1:

			if( query("book/yaoli")>0)
			{
				new("d/sld/obj/yaoli3")->move(me);
				message_vision("$N从书架中拿到一本《神龙药理经(三)》。\n",me);
				this_object()->add("book/yaoli",-1);			
			}
			break;
			default:break;
		}
	}
	
}
	    	
int do_lw(string arg)
{
	object me=this_player();
	me->start_busy(10);
	if (!arg||arg!="沧浪意")
		return notify_fail("你要领悟什么？\n");
	if (!present("shenlong gou",me))
		return notify_fail("你没有宝钩在身，要领悟什么？\n");

	if (me->query("quest/sld/clgf/canglang/pass"))
		return notify_fail("你已经全部领悟了沧浪钩法沧浪意的奥秘！\n");
	if (time()-me->query("quest/sld/clgf/canglang/time")<86400)
		return notify_fail("你来的太勤快了！\n");
	//if (me->query("quest/sld/clgf/canglang/pass"))
		//return notify_fail("你已经全部领悟了金蛇缠丝手的奥！\n");
	if (me->query_temp("clgf/start1")) 
	{
		   message_vision(HIR"你平心静气，盘膝静坐，拿出一对神龙宝钩横放在腿上，大脑一片空灵。\n"NOR,me);
		   message_vision(HIR"\n一边观察宝钩，一边开始体悟教主所提到的沧浪钩法的奥秘。\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
		   me->delete_temp("clgf/start1");
	}
	return;
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //杜绝男性，若有作弊，加大难度
  if (me->query("gender")=="男性") j=random(200);
  else j=random(10);
  me->set("quest/sld/clgf/canglang/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟沧浪意时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_canglang")<(30+random(10)))
   {  
	  me->add_temp("canwu_canglang",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
	  tell_room(environment(me),HIC"\n"+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>=25
			&& j==2
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N忽然「哈哈哈」仰天大笑几声，说道：“原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了教主所传授的沧浪意的奥秘，沧浪钩法豁然贯通！”\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟沧浪钩法的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/clgf/canglang/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/clgf/canglang/time",time());
		 me->set("quest/sld/clgf/canglang/pass",1);
		 me->delete_temp("canwu_canglang");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟沧浪意解密失败！\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) 失败！第%d次失败参悟沧浪意，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/clgf/canglang/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/clgf/canglang/fail",1);
		 me->set("quest/sld/clgf/canglang/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_canglang");
		 return 1;
   }

}