#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
         set("short",HIR"心禅堂"NOR);
       set("long", @LONG
一座宽敞的禅室，并非用土木建成，而是依山而建，四壁如仞，都是石
壁。如此山间石室，若非浑然天成，定是有前辈高僧，以禅心智慧，绝大佛
力开山而致了。室内烛火通明，终年不息，正中供奉着我佛的法像，与大殿
不同的是做千手如来收万宝势。职事僧在殿内四处巡视，以备所需。一位老
僧瞑目跌坐，内视参禅。
LONG
     );
	set("exits", ([
                "south" : __DIR__"xcping",
                "west" : __DIR__"xclang",
              "north"  : __DIR__"duanya",
	]));

        set("objects",([
           "/kungfu/class/shaolin/fangsheng" : 1,
        ]));

        set("coor/x",60);
  set("coor/y",420);
   set("coor/z",130);
   setup();
}
void init()
{
	add_action("do_canchan","canchan");
}


int do_canchan(string arg)
{
	int i,j,total;
	object me=this_player();

	if (!arg||arg!="如影随形腿绝技")
		return notify_fail("你要参悟什么？\n");
	if (!me->query_temp("rysxt/askfangsheng"))
	{
		return notify_fail("此地乃是少林寺般若堂刀法要地，你就不怕少林寺举寺追杀你么？\n");

	}
	if (me->query("quest/sl/rysxt/pass"))
	{
		return notify_fail("你已经将如影随形腿所有奥秘都解密成功了？\n");

	}

	if( time()- me->query("quest/sl/rysxt/time")<86400)
		return notify_fail("少林禅宗讲究的是顿悟，练功不宜太频繁！");

	message_vision(HIY"$N按照方生大师的指点，盘膝而坐，开始进入参禅状态！\n"NOR,me);
	total=random(me->query("str"));

	i = 20;
	if(me->query("m-card-vip")) i =  18;
	if(me->query("y-card-vip")) i =  15;
	if(me->query("buyvip"))     i =  10;
	i=random(i);

	j=random(me->query("kar"));

	if( i<3 
		&& me->query("kar")<31
		&& total>40
		&& j > 26 ) 
	{
		tell_object(me,HIY"\n你心中无数的腿法在纵横交错，对如影随形腿的理解颇有心得。\n"NOR);
		tell_object(me,HIG"\n顷刻之间，劲气贯通，你腿上经脉尽通，领悟了如影随形腿法的要旨。\n"NOR);
		tell_object(me,HIR"恭喜解密如影随形腿绝技成功!\n"NOR);
		me->set("quest/sl/rysxt/pass",1);
		log_file("quest/rysxt", sprintf("%8s(%8s) 失败%d次后，学到如影随形腿绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|随机先天臂力total取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/sl/rysxt/fail"),i,j,total,me->query("kar"),me->query("combat_exp")) );
		me->delete_temp("rysxt");
		return 1;
		
	}	
   else
	{
		log_file("quest/rysxt", sprintf("%8s(%8s) 解密如影随形腿绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|随机先天臂力total取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/sl/rysxt/fail"),i,j,total,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你仔细参禅放生大师的指点，可是对如影随形腿的奥妙全然不得要领。\n\n"NOR);
		me->add("quest/sl/rysxt/fail",1);
		me->set("quest/sl/rysxt/time",time());
		me->start_busy(1+random(3));
		me->delete_temp("rysxt");
		tell_object(me,"非常遗憾,解密如影随形腿失败"+me->query("quest/sl/rysxt/fail")+"次。\n");
		return 1;
	}

}


