//观日峰

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", HIR "观日峰" NOR);
	set("long", 
"这里就是"HIG"嵩山观日峰"NOR"，往这里一站,你不禁有一种:\n\n"
"          渺万里层云,千山暮雪,只影向谁去?\n\n"
"的感觉,这里有几块石头,大概是练气士平时修炼打坐的地方!\n"
"却见万山叠掌，风吹松涛(songtao)，宛如万剑飞舞，心胸不禁一宽!\n\n"

);
	set("outdoors", "嵩山");

	set("exits",([
		"west":__DIR__"fengchantai",
	]));
	setup();
}

void init()
{
	add_action("do_guan", "guan");
	add_action("do_lingwu", "guanwu");
}

int do_guan(string arg)
{
	object me=this_player();
	if (me->is_busy())
		return notify_fail("你现在正忙着呢！\n");
	if( !arg || arg=="" ) return 0;
	if( arg=="sun" ){
		message_vision("$N往石头上一站,看着刚刚升起的太阳,渐渐进入冥思。\n", me);
		return 1;
	}
}

int do_lingwu(string arg)
{
	object me=this_player();
	if (me->query("family/family_name")!="嵩山派")
		return notify_fail("只有嵩山派弟子才可以领悟松涛飞舞\n");
	if (!me->query_temp("feiwu/askfei"))
	{
		return notify_fail("你领悟半天不得要领，看来是没得到师傅指点啊。\n");
	}

	if (!arg || arg!="songtao")
		return notify_fail("你要领悟什么\n");
	if (me->query_skill("songshan-jian",1)<200)
		return notify_fail("你的嵩山剑法等级太低,不足200，领悟不了什么内容。\n");

	if (me->query("quest/ss/ssjf/feiwu/pass"))
			return notify_fail("你已经解开了松涛飞舞绝技，别没事来骚扰我!\n");
      if (time()-me->query("quest/ss/ssjf/feiwu/time")<86400)
			return notify_fail("你也太勤快点了，还是需要继续努力才好!");
        //标记状态
		me->set("quest/ss/ssjf/feiwu/time",time());
		me->set("quest/ss/ssjf/feiwu/exp",me->query("combat_exp"));
		message_vision(HIC"风吹而过，松涛阵阵，宛如千军万马，$N联想起师傅所言的万壑松涛剑意，似乎有些心得。\n",me);
      if(random(me->query("kar"))> 25) 
	     {
			
		    message_vision(HIY"\n\n经过不断参悟$N终于领悟了松涛飞舞绝技的要旨。\n",me);
		    me->set("quest/ss/ssjf/feiwu/pass",1);
			log_file("quest/ssjffeiwu", sprintf("%s(%s) 失败%d次成功解开嵩山剑飞舞绝技。富源：%d；经验：%d。\n",   
             me->name(1),
             me->query("id"), 
             me->query("quest/ss/ssjf/feiwu/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			 me->start_busy(1);
			 return 1; 
			
		  }
		  else {
	   	    message_vision(HIG"领悟失败，你不禁有些灰心丧气，但松涛阵阵，兀自鸣响不绝，似乎在砥砺你继续向前。\n",me);
			me->set("quest/ss/ssjf/feiwu/time",time());
			me->set("quest/ss/ssjf/feiwu/exp",me->query("combat_exp"));	
			log_file("quest/ssjffeiwu", sprintf("%s(%s) 解嵩山剑飞舞失败%d次。富源：%d；经验：%d。\n",   
             me->name(1),
             me->query("id"), 
             me->query("quest/ss/ssjf/feiwu/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			me->add("quest/ss/ssjf/feiwu/fail",1);
			return 1;
		  }
		

	

}