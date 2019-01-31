// Room: /d/xingxiu/ryd.c
// Update by caiji@SJ 8/25/2000

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"日月洞"NOR);
	set("long", @LONG
这里是星宿派总舵所在地日月洞。洞内灯火通明，正中一把虎皮椅上端坐
着星宿派掌门人丁春秋。两边各站列着数十位星宿派弟子，不断有各派人士走
进来献(xian)上各种宝物。一片歌功颂德之声，洋洋盈耳，丝竹箫管也跟着吹
奏。丁春秋每听到得意之时，禁不住挥动手中的羽扇，捋着白须，眯起了双眼，
薰薰然，飘飘然，有如饱醉醇酒。洞壁上装饰着虎皮、鹿头、雕羽，及一些字
画 (zihua)。
LONG
        );
        set("exits", ([
		"north" : __DIR__"yaolu",
		"south" : __DIR__"ryd1",
        ]));
        set("item_desc", ([
                "zihua" : "都是些吹捧星宿老仙的诗词和他的画像。似乎\n字画中有些深意，有弟子正在（guanwu）什么\n						

               ※※※※※※※※※※※※※※※※※
               ※※※※　　　　　　　　　※※※※
               ※※※※　古　威　德　星　※※※※
               ※※※※　今　震　配　宿　※※※※
               ※※※※　无　寰　天　老　※※※※
               ※※※※　比　宇　地　仙　※※※※
               ※※※※　　　　　　　　　※※※※
               ※※※※※※※※※※※※※※※※※\n"]));

	set("objects", ([
                __DIR__"npc/ding"  : 1,
                __DIR__"npc/zhaixing"  : 1,
                __DIR__"obj/huoyan"  : 1,
        ]));
        setup();
}

void init()
{
        object me = this_player();

        int lvl,lvl1,lvl2;
        lvl = me->query_skill("poison", 1);
        lvl1 = me->query_skill("huagong-dafa", 1);
        
		if (lvl > 500 && !me->query("cut/xingxiu"))
		{
                
			lvl2 = (lvl - 500)/ 4;
		    me->set_skill("poison", 500);
			
			me->set_skill("huagong-dafa", lvl1 + lvl2);
                me->set("cut/xingxiu", lvl2 * 4);
                write(HIG "系统已将您多余的「毒技」转换为「化功大法」。\n" NOR);
		}
		if ( me->query("xx_points")){
			me->add("job_time/星宿", me->query("xx_points"));
			me->delete("xx_points");
		}
		if ( me->query("xx_job5")){
			me->add("job_time/星宿叛徒", me->query("xx_job5"));
			me->delete("xx_job5");
		}
		if ( me->query("xx_job4")){
			me->add("job_time/星宿熬膏", me->query("xx_job4"));
			me->delete("xx_job4");
		}
		if (this_player()->query("family/family_name")=="星宿派")
			add_action("do_guanwu","guanwu");

}
int valid_leave(object me, string dir)
{
	if ( dir == "north" && !userp(me))
		return 0;
	if(dir == "north"
	 && me->query("family/family_name") != "星宿派"
	 && present("ding chunqiu", environment(me))){
		return notify_fail("丁春秋拦住你道：我星宿派的药庐重地，怎么能允许你进去！\n");
	}
	return ::valid_leave(me, dir);
}

int do_guanwu(string arg)
{
	object me=this_player();

	if (!arg||(arg!="zihua"&&arg!="字画"))
	{
		return notify_fail("你要观摩什么东西？\n");
	}
	if (me->query("family/family_name")!="星宿派")
	{
		return notify_fail("你不是星宿派弟子，来此观摩什么？\n");
	}
	if (me->query_skill("tianshan-zhang",1)<250)
	{
		return notify_fail("你的天山杖法级别不足250级,无法观摩出来什么。\n");
	}
	if (me->query_skill("huagong-dafa",1)<250)
	{
		return notify_fail("你的化功大法级别不足250级,无法观摩出来什么。\n");
	}
	if (me->query("quest/xx/tsz/luanpifeng/pass"))
	{
		return notify_fail("你已经融会贯通了字画中的乱披风绝技奥意。\n");
	}
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中，稍安勿躁！\n");
	}

	if (time()-me->query("quest/xx/tsz/luanpifeng/time")<86400)
	{
		return notify_fail("这字画全凭领悟，如果频繁来此有害无益。\n");
	}
	message_vision(HIY"$N抬眼打量那副字画，上面写了很多字，每一个字都写的极为张扬。\n"NOR,me);
	message_vision(HIY"状若疯狂，笔力虬劲，甚至有些字都宛如一条长蛇弯曲，根本就看不出什么来。\n"NOR,me);
	message_vision(HIG"而那副画更是宛如泼墨一般，东一团，西一团，状若麻团。\n"NOR,me);
	message_vision(HIR"你越看越投入，越看越觉得其中意蕴深长。\n"NOR,me);
	message_vision(HIW"忽然，你似乎从中发现这些画中似乎蕴含一门极其厉害的武功！\n"NOR,me);
	me->start_busy(99);
	
	if (me->query_temp("canwu_zihua"))
	{
		return notify_fail("你正在参悟中，稍安勿躁！\n");
	}
	remove_call_out("thinking");
	call_out("thinking",1,me);
	return 1;
}

int thinking(object me)
{
	int i,j;
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);

	if (me->query("kar")>30) 
	{
	  log_file("quest/bug", sprintf("%s(%s) 参悟乱披风绝技时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
	}
	if(me->query_temp("canwu_zihua")<(10+random(10)))
	{  
	  me->add_temp("canwu_zihua",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细观摩这幅字画，将这些武功彼此印证，只觉得耳目一新...\n"NOR);
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
   else if (i<5
			&& random(me->query("kar"))>22
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈」大笑，自言自语说道：“原来是这样啊，这位前辈居然将天山杖法融入到字画之中，真乃神技！”\n"NOR,me); 
		 message_vision(HIR"\n$N 从字画中悟出了天山杖法中的《乱披风绝技》的奥义。\n"NOR,me); 
        // message_vision(HIY"\n$N`心下恍悟，终于领悟了苏荃所传授的腾龙匕法这【美人三招】的奥秘！”\n"NOR,me); 
         log_file("quest/tszluanpifeng", sprintf("%s(%s) 解密成功！第%d次参悟，机缘巧合下，成功参悟天山杖法之乱披风绝技的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xx/tsz/luanpifeng/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/xx/tsz/luanpifeng/time",time());
		 me->set("quest/xx/tsz/luanpifeng/pass",1);
		 me->delete_temp("canwu_zihua");
		 me->start_busy(1);
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“这鬼字画中到底存在什么样的奥秘，真是奇了怪了。”\n"NOR,me); 
		 message_vision(HBYEL+HIR"\n参悟日月洞字画解密失败！\n"NOR,me); 
         log_file("quest/tszluanpifeng", sprintf("%s(%s) 失败！第%d次失败参悟天山杖法乱披风绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xx/tsz/luanpifeng/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/xx/tsz/luanpifeng/fail",1);
		 me->set("quest/xx/tsz/luanpifeng/time",time());// 这里少写一个/导致可以反复参悟  by renlai		 
		 me->start_busy(2);
		 me->delete_temp("canwu_zihua");
		 return 1;
   }
	

}