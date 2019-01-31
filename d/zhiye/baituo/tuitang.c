#include <ansi.h>
inherit ROOM;
int look_zihua();

void create()
{
        set("short", "退堂");
        set("long", @LONG
这间退堂不大，只放有两个茶几，挂了两副字画(zihua)，一幅
画的是大漠风雪骆驼群奔图，一幅是一群蛇在蠕动。左右两边是睡房
再往后是个小院子。
LONG);
        set("exits", ([
              "south" : __DIR__"tangwu",
              "east" : __DIR__"shuifang",
              "north" : __DIR__"yuanzi",
        ]));
		set("item_desc", ([                    
                "zihua": (:look_zihua:),
				//"guan": "\n里面放了白驼山独有的剧毒怪蛇,可以吸毒来修炼(xidu)。\n",
        ]));
        setup(); 
}
int init()
{
	add_action("do_canwu",({"guanmo","canwu","yandu"}));
}

int look_zihua()
{
	object me=this_player();
	tell_object(me,"两幅泼墨山水画，左侧一幅为大漠骆驼奔腾的画面，气势磅礴，右面为大漠风雪画面！\n"
	"你定睛看去，发现这幅画写了两行小字，“留待有缘，白驼山主人”的字样。\n");
	me->set_temp("look/zihua",1);
	return 1;
}
int do_canwu(string arg)
{
	object me;
	me=this_player();
	if (!me->query_temp("look/zihua"))
	{
		return notify_fail("你要看什么？\n");
	}
	if (!arg)
	{
		return notify_fail("你要观悟什么？\n");
	}
	if (!(arg=="zihua"||arg=="字画"))
	{
		return notify_fail("你要观悟什么？\n");
	}
	if (me->query("family/family_name")!="白驼山庄")
	{
		return notify_fail("你非白驼山庄的弟子!\n");
	}
	if (me->query_skill("hamagong",1)<300)
	{
		return notify_fail("你的蛤蟆功不足300级!\n");
	}
	if (me->query_skill("shentuo-zhang",1)<350)
	{
		return notify_fail("你的神驼雪山掌威力不足350级");
	}
	if (me->query_skill("lingshe-quanfa",1)<350)
	{
		return notify_fail("你的灵蛇拳法威力不足350级");
	}
	if (time()-me->query("quest/bt/stxsz/hubei/time")<86400)
	{
		message_vision(YEL"你来的太频繁了！\n"NOR,me);
		return 1;
	}
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中！\n");
	}
	if (me->query("quest/bt/hubei/start"))
	{
		return notify_fail("你正在观悟中！\n");
	}

	tell_object(me,"你观看这两幅图画，越看越觉得有韵味，似乎隐隐有相容的趋势！\n");
	me->set_temp("quest/bt/hubei/start",1);
	remove_call_out("guan_wu");
	call_out("guan_wu",1,me);
	me->start_busy(99);
	return 1;
}


int guan_wu(object me)
{
	int i,j,total;
    if(!me) return 0;

    if(me->query_temp("guan_wu")<(10+random(3)))
    { 
	  me->add_temp("guan_wu",1);
      if(random(2)) tell_object(me,BLU"\n你仔细看去，似乎觉得这两图和灵蛇拳以及神驼雪山掌有莫大的联系..\n"NOR);
      else tell_object(me,HIY"\n突然间，你又掌握了一些在实战中运用这么两门武技的技巧..\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("guan_wu");
	  call_out("guan_wu",3+random(3), me);
    } else
    {  
	  me->delete_temp("guan_wu");
      total = me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
      i=random(j);

    	if (i < 5 
		&& random(me->query("kar"))>26) 		 
		{
       
			  message_vision(HIC"$N熟能生巧，陡然间你忽然明白了这两种拳法彼此配合的意境。”\n"NOR,me); 
			  tell_object(me,HIW"$N将方才的所得暗暗思索，顿觉脑中对灵蛇拳和神驼雪山掌的理解进入了一个前所未有的新境\n"NOR);
			  
			  me->set("quest/bt/stxsz/hubei/pass", 1);
			  me->set("quest/bt/stxsz/hubei/time",time());
			  log_file("quest/bthubei", sprintf("%s(%s) 失败%d次后，成功解开灵蛇拳与神驼雪山掌融合的奥秘。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/bt/stxsz/hubei/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
         }
         else
         {
			 tell_object(me,HIG"\n你沉思许久，脑子越来越混沌，始终不得要领。\n"NOR);
			 message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
			 message_vision(HIY"$N抓耳挠腮，苦思冥想，发现自己还是无法理解两门武功融合奥意所在，脸上一筹莫展。\n"NOR,me);
			 tell_object(me,HBBLU"\n很可惜，你本次尝试融合神驼雪山掌和灵蛇拳法解密秘密失败！\n"NOR);
			 tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
			 tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
			 log_file("quest/bthubei", sprintf("%s(%s) 解密灵蛇拳与神驼雪山掌融合绝技失败%d次。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/bt/stxsz/hubei/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/bt/stxsz/hubei/fail",1);
			 me->set("quest/bt/stxsz/hubei/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/bt/stxsz/hubei/time",time());
        }
		 me->delete_temp("quest");
		 return 1;

	}
}
