// Room: /d/shaolin/banruo7.c
// Date: YZC 96/01/19

inherit ROOM;

#include <ansi.h>



void create()
{
	set("short", "般若堂七部");
	set("long", @LONG
这是一间极为简陋的禅房。环视四周，除了几幅佛竭外，室内空荡荡地
别无他物。地上整齐的摆放着几个破烂且发黑的黄布蒲团，几位须发花白的
老僧正在坐在上面闭目入定。这里是本寺十八罗汉参禅修行的地方，不少绝
世武功便是在此悟出。
LONG
	);

	set("exits", ([
		"south" : __DIR__"banruo6",
		"north" : __DIR__"banruo8",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/cheng-ling" : 1,
	]));
	set("coor/x",110);
	set("coor/y",290);
	set("coor/z",110);
	setup();
}
void init()
{
	object me=this_player();
	add_action("do_xiuxing","canchan");
}

int do_xiuxing(string arg)
{
	
	int j,t;
	object me=this_player();
	if (me->query("family/family_name")!="少林派")
	{
		return notify_fail("你不是少林弟子，参悟不了少林绝技！\n");
	}
	if (!me->query_temp("rysxt/askchengling"))
	{
		return notify_fail("你鬼鬼祟祟的来此参禅修炼不怕少林灭了你？\n");
	}
	if (time()-me->query("quest/sl/rysxt/tiezhou/time")<86400)
	{
		return notify_fail("少林武功大都需要参悟，你如此勤快反而违背了顿悟的本意！\n");
	}
	if (!arg||arg!="铁帚功")
	{
		return notify_fail("此间静室乃是少林集腿法大成之地，各种腿法武功汇集于此。只能参悟腿法精要！\n");
	}
	message_vision(CYN"\n\n你翻看各种腿法秘籍精要经卷，望着少林的武技精要，真是叹为观止。\n"NOR, me);
	message_vision(CYN"\你沉浸在浩瀚的腿法研究中，随手拿起一本不断翻看。\n"
			           +"这些招式对你来说你已经了然若胸，一时之间竟然呆立当场\n"
					   +"一时间又甚是不解，为何会出现这种情况？\n"NOR,me);
	
	j=random(me->query("kar"));
	
	t=20;
    if(me->query("m-card-vip")) t =  18;
    if(me->query("y-card-vip")) t =  15;
    if(me->query("buyvip"))     t =  10;
	t= random(t);
	
	if (me->query("kar")<31
		&& j>26
		&& t<3)
	{
       message_vision(HIC"$N忽然间睁开双眼，暗道这铁帚功要想练成绝非一日之功，对于腿法要求是很高的。\n"NOR,me);
	   message_vision(HIC"但一味的盲目修炼硬功也不是长久之计，人身终究不过是血肉之躯，若不将易筋经。\n"NOR,me);
	   message_vision(HIC"的功力运行在双腿之上，这功夫终究是练不成的，想明白了此节，你将浑身功力。\n"NOR,me);
	   message_vision(HIC"沿着经络运行，忽然间“尾中穴”一痛，继而“承山穴”一阵麻痒难当，运行在腿部的。\n"NOR,me);
	   message_vision(HIC"气血经络豁然贯通！\n"NOR,me);

	   message_vision(HIG"$N恭喜你，历经千难万险，终于领悟如影随形腿的铁帚功绝技。\n"NOR,me);
	  
	   log_file("quest/rysxttiezhou",sprintf("%s(%s) 在少林般若堂，领悟了铁帚功的精要，修成铁帚神功。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,t,me->query("quest/sl/rysxt/tiezhou/fail"),me->query("combat_exp"),me));
	   //me->set("title",HIC"少林派"HIY"如影随形腿传人"NOR);
	   me->set("quest/sl/rysxt/tiezhou/pass",1);
	   me->delete_temp("rysxt");
	   me->start_busy(1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N虽然朦胧知道这铁帚腿功的终极奥义，但对于如何使用的劲力法门一时之间却是难以理解。\n"
						+"铁帚功威力并没有发挥出来，看来你还是有待于重新参禅修习了。\n"NOR,me);
	    message_vision(HIR"参悟如影随形腿的铁帚功失败！\n"NOR,me);

		log_file("quest/rysxttiezhou",sprintf("%8s%-10s在少林般若堂，参悟铁帚功并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,t,me->query("quest/sl/rysxt/tiezhou/fail"),me->query("combat_exp"),me));
		me->add("quest/sl/rysxt/tiezhou/fail",1);
		me->set("quest/sl/rysxt/tiezhou/time",time());
		me->delete_temp("rysxt");
		me->start_busy(-1);
        return 1;
	}

}



