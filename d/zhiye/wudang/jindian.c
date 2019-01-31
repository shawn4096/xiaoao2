// /area/jiangbei/wudang/jindian.c 金殿
// By River@SJ

inherit ROOM;
#include <ansi.h>
int do_guanmo(string arg);

void create()
{
        set("short", HIY"金殿"NOR);
        set("long", @LONG
金殿建在天柱峰顶端，是武当山的象征，也是武当道教在皇室扶持下走向
鼎盛的结果。铜铸鎏金的金殿为重檐庑殿式仿木结构，仅面饰鎏金就耗黄金千
两，是武当山等级最高的古建筑。金殿的面阔进深均为三间，立柱上叠架着额、
枋及斗拱，正脊两端龙吻对峙，殿顶翼角飞举，上饰龙凤、天马、等灵禽瑞兽
栩栩如生。令人诧异的是，铜柱上有些剑痕甚是扎眼，显然有人曾在此打斗所
留。
LONG
        );

        set("exits", ([
                "east" : __DIR__"taihe",
        ]));

        set("no_clean_up", 0);

        set("objects",([
                __DIR__"npc/jxk" : 1,
        ]));

        setup();
}
void init()
{

	add_action("do_guanmo","guanmo");

}

int do_guanmo(string arg)
{
	object me=this_player();
	if (!arg || arg!="剑痕") return notify_fail("你要观摩什么？\n");
	if (me->query("family/family_name")!="武当派")
		return notify_fail("你不是武当派弟子，看不出什么门道。!\n");
	if (me->query_skill("taiji-jian",1)<350)
	{
		return notify_fail("你的太极剑等级太低，不足350级，看不懂这深奥的剑痕奥意！\n");
	}
	if (me->query_skill("yinyun-ziqi",1)<350)
	{
		return notify_fail("你的氤氲紫气等级太低，不足350级，看不懂这深奥的剑痕奥意！\n");
	}
	if (time()-me->query("quest/wd/tjj/sanhuan/time")<86400)
	{
		return notify_fail("你来的也太勤快了耶！\n");
	}
	if (me->query("quest/wd/tjj/sanhuan/pass"))
	{
		return notify_fail("你已经参悟透了这剑痕的奥意！\n");
	}
	message_vision(HIC"$N盘膝而坐，平心静气，运起氤氲紫气，慢慢开始打坐，进入到一种玄奥的境界之中。!\n"NOR,me);
	message_vision(HIC"当心静如水之镜，$N抬起头来，抬头看向那铜柱之上的剑痕，虽然斑驳陆离，但一看却知是武当高手所为!\n"NOR,me);
	message_vision(HIC"$N心中诧异，这是何等深厚的功力，才能在这铜柱上留下如此剑痕!\n"NOR,me);
	message_vision(HIC"忽然，$N发现这铜柱前面几道剑痕显然是三环套月的招式，而后面的连环三招却好像是连环诀导致的剑痕!\n"NOR,me);
	message_vision(HIC"这两招剑法为何会有如此奥妙，竟然衔接在一起，$N百思不得其解，陷入沉思之中!\n"NOR,me);
	me->set("quest/wd/tjj/sanhuan/time",time());
	me->start_busy(999);
	call_out("think_jianhen",1,me);
	
	return 1;
}

int think_jianhen(object me)
{
	int i,j;
	if(!me) return 0;
	
	if(me->query_temp("sanhuan/ask")<(10+random(3)))
    { 
	  me->add_temp("sanhuan/ask",1);
      if(random(2)) tell_object(me,HIG"\n你认真观察铜柱上的剑痕，观摩这铜柱上的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你脑中一阵电闪雷鸣，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("think_jianhen");
	  call_out("think_jianhen",3+random(1), me);
	}
   else
   {  
	  me->delete_temp("sanhuan/ask");
      j = 20;
      if(me->query("m-card-vip")) j =  17;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i=random(j);
 
 
     if(i=5 && random(me->query("kar"))>26)
	 {
		tell_object(me,HIG"\n你按照铜柱上的剑痕所留，对太极剑三环套月的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIW"忽然间你起身长啸，瞬间领悟了这太极剑三环套月和连环诀之间的关系，顺手施展起来！\n"NOR);
		tell_object(me, HIW"宛如行云流水，意念通达！\n"NOR);
		tell_object(me,HIY"\n恭喜你！历尽千辛万苦，终于得偿所愿，将三环套月融汇贯通。\n"NOR);
     
		me->set("quest/wd/tjj/sanhuan/pass",1);
		
		me->start_busy(1);
		log_file("quest/tjjsanhuan", sprintf("%8s(%8s) 失败%d次后，彻底领悟三环套月的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/wd/tjj/sanhuan/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/wd/tjj/sanhuan/fail",1);
		me->set("quest/wd/tjj/sanhuan/time",time());
		command("buddha ");
		tell_object(me,HIY"你对照铜柱上剑痕的路数，虽然知道这是太极剑三环套月招式，可是对这招的真正奥妙全然不得要领。\n\n"NOR);
		tell_object(me,HIG"解密三环套月秘技失败。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/tjjsanhuan", sprintf("%8s(%8s) 太极剑三环套月解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/wd/tjj/sanhuan/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }



}